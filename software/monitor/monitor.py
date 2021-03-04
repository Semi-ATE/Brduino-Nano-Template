from PyQt5 import QtCore, QtWidgets, QtSerialPort, uic

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas 
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar 
import matplotlib.pyplot as plt 

import sys
import os
import pathlib
import struct
import crcmod
import time
import numpy as np
import pandas as pd

from utils import pkg_dump
from commands import command_ABC as is_command

ESC = b'\xF0'
SOP = b'\xA0'
EOP = b'\x05'
ESCESC = ESC + ESC
ESCSOP = ESC + b'\x01'
ESCEOP = ESC + b'\x02'


class Monitor(QtWidgets.QWidget):
    
    ID = 'BRDUINO NANO'
    ChunkSize = 3600 # number of rows to grow pandas dataframe with.
    debug = False
    
    def __init__(self, parent=None):
        super(Monitor, self).__init__(parent)

        uic.loadUi(__file__.replace('.py', '.ui'), self)

        self.terminalTextEdit.clear()
        self.commandTab.setDisabled(True)
        self.autoMeasureCheckBox.setDisabled(True)
        self.autoMeasureSpinBox.setDisabled(True)
        self.executeButton.clicked.connect(self.execute_command)
        self.connectionButton.clicked.connect(self.connection_button_clicked)
        self.clearTerminalPushButton.clicked.connect(self.clear_terminal_button_clicked)
        self.muteTerminalCheckBox.toggled.connect(self.terminal_mute_toggled)

        self.fileSystemWatcher = QtCore.QFileSystemWatcher()
        if self.detect_OS() == 'linux':
            self.fileSystemWatcher.addPath(r'/dev')
            self.fileSystemWatcher.directoryChanged.connect(self.linux_watchdog)        

        self.serial = QtSerialPort.QSerialPort()
        self.serial.readyRead.connect(self.receive)
        self.serial_receive_buffer = b''
        self.serialPortInfo = QtSerialPort.QSerialPortInfo()

        self.commands_by_code = {}
        self.commands_by_name = {}
        display_list = self.load_commands()
        self.commandComboBox.clear()
        self.commandComboBox.insertItems(0, display_list)
        self.commandComboBox.adjustSize()
        self.commandComboBox.setCurrentText('get measurement')

        self.CRC_CCITT = crcmod.mkCrcFun(0x11021,0,False,0)
        
        self.rail_list = ['RAIL0', 'P12V0D', 'RAIL1', 'RAIL2', 'P25V0D', 'P17V0D', 
                 'N7V0D', 'P15V0A', 'N15V0A', 'P5V0D', 'P5V0A', 'N5V0A',
                 'P3V3D', 'P5V0R', 'GND']
        self.setting_list = ['VGAIN', 'VOFFSET', 'IGAIN', 'IOFFSET', 
                    'VLLIM', 'VHLIM', 'ILLIM', 'IHLIM']
        self.df_columns = []
        self.settings = {}
        for rail in self.rail_list:
            self.settings[rail] = {}
            self.df_columns.append(rail+'_VMON')
            self.df_columns.append(rail+'_IMON')
            for setting in self.setting_list:
                if not (rail == 'GND' and setting.endswith('LIM') and setting.startswith('I')): 
                    self.settings[rail][setting] = 0.0

        print(self.settings)

        self.df = pd.DataFrame(columns=self.df_columns, index=range(self.ChunkSize)).astype(np.float32)
        self.df_row = 0

    def load_settings(self):
        '''
        This method is called upon 'connecting', then it should get the settings from the CortexM4
        '''
        print("TODO: implement the loading of the settings")

    def load_commands(self):
        '''
        This mentod will load all commands in the 'commands' directory.
        '''
        display_list = []
        load_exclusions = ['common.py']
        display_exclusions = ['notification']
        default = 'get_measurement.py'
        has_default = False
        command_directory = os.path.join(os.path.dirname(__file__), 'commands')
        if not os.path.exists(command_directory):
            raise Exception(f"Couldn't find the commands directory '{command_directory}'")
        for possible_command in os.listdir(command_directory):
            if not possible_command.endswith('.py'):
                continue
            if possible_command in load_exclusions:
                continue
            if possible_command.startswith('_'):
                continue
            
            if possible_command == default:
                has_default = True
                
            class_name = possible_command.upper().replace('.PY', '')
            object_name = class_name.lower()

            importer = f"from commands.{object_name} import {class_name}"
            if self.debug:
                print(f"{importer} ... ", end='')                
            exec(importer)
            if self.debug:
                print('Done.')

            loader = f"{class_name}(self)"
            if self.debug:
                print(f"{loader} ... ", end='')
            exec(loader)
            if self.debug:
                print('Done.\n')
                
            if object_name not in display_exclusions:
                display_list.append(object_name.replace('_', ' '))
                
        if not has_default:
            raise Exception(f"Didn't find the default command '{default}'")
            
        return sorted(display_list)

    def execute_command(self):
        command_name = self.commandComboBox.currentText()
        command_object = self.commands_by_name[command_name]
        CMD, SCMD = command_object.get_commands()
        if 'get' in command_name:
            self.send(CMD, SCMD, command_object.payload)
        else:  # set 
            command_object.dialog.exec()

    def register_command(self, command_object):
        '''
        With this method a command registers itself to the monitor.
        '''
        if not isinstance(command_object, is_command):
            raise TypeError
        command, sub_command = command_object.get_commands()
        self.commands_by_code[(command, sub_command)] = command_object
        command_name = str(command_object.__class__).split('.')[-1].replace("'>", "").replace("_", " ").lower()
        self.commands_by_name[command_name] = command_object

    def detect_OS(self):
        '''
        This method will return one of ['linux', 'windows', 'macOS'] depending 
        of the operating system. An exception will be raised on other operating systems.
        '''
        if 'LINUX' in sys.platform.upper():
            return 'linux'
        elif 'WIN' in sys.platform.upper():
            return 'windows'
        elif 'DARWIN' in sys.platform.upper():
            return 'macOS'
        else:
            raise Exception("Couldn't determine the operating system.")

    def linux_watchdog(self):
        '''
        This slot is called whenever '/dev' changes.
        
        It is used to automatically disconnect when we lose the serial connection.
        '''
        def serial_port_available():
            for port in self.serialPortInfo.availablePorts():
                if self.ID in port.description():
                    return True
            return False

        if self.tabWidget.isEnabled():
            if self.serial.isOpen() and not serial_port_available():
                self.serial.close()
                self.commandTab.setDisabled(True)
                self.autoMeasureCheckBox.setDisabled(True)
                self.autoMeasureSpinBox.setDisabled(True)
                self.connectionButton.setText('Connect')

    def receive(self):
        def packet_available():
            if len(self.serial_receive_buffer) == 0:
                return False
            if not self.serial_receive_buffer[0] == SOP:
                if self.serial_receive_buffer.find(SOP) != -1:
                    self.serial_receive_buffer = self.serial_receive_buffer[self.serial_receive_buffer.find(SOP):]
                else:
                    self.serial_receive_buffer = b''
            if self.serial_receive_buffer.find(EOP) == -1:
                return False
            return True

        def consume_packet():
            split_index = self.serial_receive_buffer.find(EOP) + 1
            pkg = self.serial_receive_buffer[:split_index]
            self.serial_receive_buffer = self.serial_receive_buffer[split_index:]
            return pkg

        self.serial_receive_buffer += self.serial.read(self.serial.bytesAvailable())
        while packet_available():
            escaped_packet = consume_packet()
            if self.showPacketsInTerminalCheckBox.isChecked():
                self.terminalTextEdit.append(f"➜ {pkg_dump(escaped_packet)}")   
            unescaped_packet = escaped_packet.replace(ESCESC, ESC).replace(ESCSOP, SOP).replace(ESCEOP, EOP) 
            header = unescaped_packet[1:7]
            (DA, CMD, ACK, SCMD, RXTX) = struct.unpack('HBBBB', header)
            payload = unescaped_packet[7:-3]
            crc = unescaped_packet[-3:-1]
            crc_unpacked = struct.unpack('<H', crc)[0]
            checksum_calculated = self.CRC_CCITT(header+payload)

            if self.debug:
                print(f"  escaped_packet = {pkg_dump(escaped_packet)}")
                print(f"unescaped_packet = {pkg_dump(unescaped_packet)}")
                print(f"          header =    {pkg_dump(header)}")
                print(f"              DA =    {pkg_dump(header[:2])}                      {' '*(len(payload*3))}({DA})")
                print(f"             CMD =          {pkg_dump(header[2:3])}                   {' '*(len(payload*3))}({CMD})")
                print(f"             ACK =             {pkg_dump(header[3:4])}                {' '*(len(payload*3))}({ACK})")
                print(f"            SCMD =                {pkg_dump(header[4:5])}             {' '*(len(payload*3))}({SCMD})")
                print(f"            RXTX =                   {pkg_dump(header[5:6])}          {' '*(len(payload*3))}({RXTX})")
                print(f"         payload =                      {pkg_dump(payload)}          ({len(payload)})")            
                print(f"             crc ={pkg_dump(crc):>{(len(header+payload)*3)+9}}    (0x{crc_unpacked:04X})")
                print(f"   crc caculated ={' '*(len(unescaped_packet)*3)} (0x{checksum_calculated:04X})")
           
            if crc_unpacked != checksum_calculated:
                print(f"Checksum failure : {crc_unpacked} <-> {checksum_calculated}")

            self.commands_by_code[(CMD, SCMD)].receive(DA, ACK, RXTX, payload)

    def send(self, CMD, SCMD, payload):
        def do_escaping(unescaped):
            escaped = unescaped.replace(ESC, ESCESC).replace(SOP, ESCSOP).replace(EOP, ESCEOP)
            return escaped
        
        if not isinstance(payload, bytes):
            raise TypeError("payload must be of type 'bytes'")
        message = struct.pack('HHBB', self.deviceIDSpinBox.value(), 0, CMD, SCMD) + payload
        package = SOP + do_escaping(message + struct.pack('H', self.CRC_CCITT(message))) + EOP  
        if self.debug:
            print(f"sending : '{pkg_dump(package)}'")
        if not self.muteTerminalCheckBox.isChecked() and self.showPacketsInTerminalCheckBox.isChecked():
            self.terminalTextEdit.append(f"{pkg_dump(package)} ➜")
        if self.serial.isOpen():    
            self.serial.write(package)
        else:
            print("WTF, why isn't the serial port open ?!?")

    def clear_terminal_button_clicked(self):
        self.terminalTextEdit.clear()

    def connection_button_clicked(self):
        def detect_serial_port():
            retval = ''
            for port in self.serialPortInfo.availablePorts():
                if self.ID in port.description():
                    retval = port.portName()
                    break
            return retval
        
        if self.connectionButton.text() == 'Connect':
            if self.serial.isOpen():
                raise Exception("trying to open an already open connection ?!?")
            port_name = detect_serial_port()
            if port_name == '':
                msgBox = QtWidgets.QMessageBox(self)
                msgBox.setIcon(QtWidgets.QMessageBox.Information)
                msgBox.setText(f"Unable to find '{self.ID}'")
                msgBox.setWindowTitle("Information")
                msgBox.setStandardButtons(QtWidgets.QMessageBox.Ok)
                msgBox.exec()
            else: 
                self.serial.setPortName(port_name)
                self.serial.setBaudRate(QtSerialPort.QSerialPort.Baud115200)
                self.serial.setDataBits(QtSerialPort.QSerialPort.Data8)
                self.serial.setParity(QtSerialPort.QSerialPort.NoParity)
                self.serial.setStopBits(QtSerialPort.QSerialPort.OneStop)
                self.serial.setFlowControl(QtSerialPort.QSerialPort.NoFlowControl)
                try:
                    retval = self.serial.open(QtCore.QIODevice.ReadWrite)
                except:
                    msgBox = QtWidgets.QMessageBox(self)
                    msgBox.setIcon(QtWidgets.QMessageBox.Information)
                    msgBox.setText(f"Something went wrong opening the serial port '{self.ID}'")
                    msgBox.setWindowTitle(retval)
                    msgBox.setStandardButtons(QtWidgets.QMessageBox.Ok)
                    msgBox.exec()
                else:
                    self.commandTab.setEnabled(True)
                    self.autoMeasureCheckBox.setEnabled(True)
                    self.autoMeasureSpinBox.setEnabled(True)
                    self.connectionButton.setText('Disconnect')
            self.load_settings()
        else:
            if self.serial.isOpen():
                self.serial.close()
            self.commandTab.setDisabled(True)
            self.autoMeasureCheckBox.setDisabled(True)
            self.autoMeasureSpinBox.setDisabled(True)
            self.connectionButton.setText('Connect')

    def terminal_mute_toggled(self, checked):
        if checked:
            self.commandGroupBox.setDisabled(True)
            self.terminalTextEdit.setDisabled(True)
            self.showPacketsInTerminalCheckBox.setDisabled(True)
        else:
            self.commandGroupBox.setEnabled(True)
            self.terminalTextEdit.setEnabled(True)
            self.showPacketsInTerminalCheckBox.setEnabled(True)

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    monitor = Monitor()
    monitor.show()
    sys.exit(app.exec_())