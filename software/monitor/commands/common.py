#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 11 16:41:07 2020

@author: nerohmot
"""

from PyQt5 import QtCore, QtWidgets, uic

import abc

float_regex = "[+-]?([0-9]+(\\.[0-9]+)?)"

class command_dialog(QtWidgets.QDialog):
    
    def __init__(self, ui_file, parent):
        super().__init__()
        self.parent = parent
        print(parent.__class__.__name__)
        self.setWindowFlag(QtCore.Qt.WindowContextHelpButtonHint, on=False)
        self.setWindowFlag(QtCore.Qt.WindowCloseButtonHint, on=False)
        self.setWindowFlag(QtCore.Qt.WindowMinimizeButtonHint, on=False)
        self.setWindowFlag(QtCore.Qt.WindowMaximizeButtonHint, on=False)
        self.ui_file = ui_file.replace('.py', '.ui')
        uic.loadUi(self.ui_file, self)
        
        self.OKButton.pressed.connect(self.accept)
        self.CancelButton.pressed.connect(self.reject)
        #TODO: always on top
    
    def accept(self):
        self.done(QtWidgets.QDialog.Accepted)
    
    def reject(self):
        self.done(QtWidgets.QDialog.Rejected)

class command_ABC(metaclass=abc.ABCMeta):

    payload = b''
    
    def __init__(self, parent):
        self.parent = parent
        self.parent.register_command(self)

    def get_commands(self):
        return self.command, self.sub_command

    def write_to_terminal(self, message):
        if not self.parent.muteTerminalCheckBox.isChecked():
            self.parent.terminalTextEdit.append(message)
            
    def send(self):
        CMD, SCMD = self.get_commands()
        self.parent.send(CMD, SCMD, self.payload)

    @abc.abstractmethod
    def receive(self, DA, ACK, RXTX, payload):
        pass
