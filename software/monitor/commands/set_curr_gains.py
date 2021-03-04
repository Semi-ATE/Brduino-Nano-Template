#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

import struct
import numpy as np

from PyQt5 import QtWidgets

from . import command_ABC, command_dialog
    
class SET_CURR_GAINS_DIALOG(command_dialog):

    precision = 6    

    def exec(self):
        self.setWindowTitle('Set Current Gains')
        
        (RAIL0_IGAIN,
        P12V0D_IGAIN,
        RAIL1_IGAIN, 
        RAIL2_IGAIN, 
        P25V0D_IGAIN,
        P17V0D_IGAIN,
        N7V0D_IGAIN,
        P15V0A_IGAIN,
        N15V0A_IGAIN,
        P5V0D_IGAIN, 
        P5V0A_IGAIN, 
        N5V0A_IGAIN, 
        P3V3D_IGAIN, 
        PVLB_IGAIN,  
        P5V0R_IGAIN) = struct.unpack('fffffffffffffff', self.parent.payload) 

        self.RAIL0_IGAIN.setText(f"{RAIL0_IGAIN:.{self.precision}f}")
        self.P12V0D_IGAIN.setText(f"{P12V0D_IGAIN:.{self.precision}f}")
        self.RAIL1_IGAIN.setText(f"{RAIL1_IGAIN:.{self.precision}f}")
        self.RAIL2_IGAIN.setText(f"{RAIL2_IGAIN:.{self.precision}f}") 
        self.P25V0D_IGAIN.setText(f"{P25V0D_IGAIN:.{self.precision}f}")
        self.P17V0D_IGAIN.setText(f"{P17V0D_IGAIN:.{self.precision}f}")
        self.N7V0D_IGAIN.setText(f"{N7V0D_IGAIN:.{self.precision}f}")
        self.P15V0A_IGAIN.setText(f"{P15V0A_IGAIN:.{self.precision}f}")
        self.N15V0A_IGAIN.setText(f"{N15V0A_IGAIN:.{self.precision}f}")
        self.P5V0D_IGAIN.setText(f"{P5V0D_IGAIN:.{self.precision}f}")
        self.P5V0A_IGAIN.setText(f"{P5V0A_IGAIN:.{self.precision}f}")
        self.N5V0A_IGAIN.setText(f"{N5V0A_IGAIN:.{self.precision}f}") 
        self.P3V3D_IGAIN.setText(f"{P3V3D_IGAIN:.{self.precision}f}") 
        self.PVLB_IGAIN.setText(f"{PVLB_IGAIN:.{self.precision}f}")
        self.P5V0R_IGAIN.setText(f"{P5V0R_IGAIN:.{self.precision}f}") 

        super().exec()

    def accept(self):
    
        self.parent.payload = struct.pack('fffffffffffffff',
                                          float(self.RAIL0_IGAIN.text()),
                                          float(self.P12V0D_IGAIN.text()),
                                          float(self.RAIL1_IGAIN.text()),
                                          float(self.RAIL2_IGAIN.text()),
                                          float(self.P25V0D_IGAIN.text()),
                                          float(self.P17V0D_IGAIN.text()),
                                          float(self.N7V0D_IGAIN.text()),
                                          float(self.P15V0A_IGAIN.text()),
                                          float(self.N15V0A_IGAIN.text()),
                                          float(self.P5V0D_IGAIN.text()),
                                          float(self.P5V0A_IGAIN.text()),
                                          float(self.N5V0A_IGAIN.text()),
                                          float(self.P3V3D_IGAIN.text()),
                                          float(self.PVLB_IGAIN.text()),
                                          float(self.P5V0R_IGAIN.text()))
        self.parent.send()
        self.done(QtWidgets.QDialog.Accepted)

class SET_CURR_GAINS(command_ABC):
    '''
    Description: set the current gains for all rails.
    
    Input: The desired voltage gains for the rails
    
        | Index | Name         | Type    | Description             |             
        |:-----:|:-------------|:--------|:------------------------|             
        |0      | P12V0D_IGAIN | float32 | Current gain for P12V0D |
        |1      | RAIL1_IGAIN  | float32 | Current gain for RAIL1  |   
        |2      | RAIL2_IGAIN  | float32 | Current gain for RAIL2  |
        |3      | P25V0D_IGAIN | float32 | Current gain for P25V0D |
        |4      | P17V0D_IGAIN | float32 | Current gain for P17V0D |
        |5      | N7V0D_IGAIN  | float32 | Current gain for N7V0D  |
        |6      | P15V0A_IGAIN | float32 | Current gain for P15V0A |
        |7      | N15V0A_IGAIN | float32 | Current gain for N15V0A |
        |8      | P5V0D_IGAIN  | float32 | Current gain for P5V0D  |
        |9      | P5V0A_IGAIN  | float32 | Current gain for P5V0A  |
        |10     | N5V0A_IGAIN  | float32 | Current gain for N5V0A  |
        |11     | P3V3D_IGAIN  | float32 | Current gain for P3V3D  |
        |12     | PVLB_IGAIN   | float32 | Current gain for PVLB   |
        |13     | P5V0R_IGAIN  | float32 | Current gain for P5V0R  |
    
    Output: The new list of current gains.
    
        | Index | Name         | Type    | Description             |             
        |:-----:|:-------------|:--------|:------------------------|             
        |0      | P12V0D_IGAIN | float32 | Current gain for P12V0D |
        |1      | RAIL1_IGAIN  | float32 | Current gain for RAIL1  |   
        |2      | RAIL2_IGAIN  | float32 | Current gain for RAIL2  |
        |3      | P25V0D_IGAIN | float32 | Current gain for P25V0D |
        |4      | P17V0D_IGAIN | float32 | Current gain for P17V0D |
        |5      | N7V0D_IGAIN  | float32 | Current gain for N7V0D  |
        |6      | P15V0A_IGAIN | float32 | Current gain for P15V0A |
        |7      | N15V0A_IGAIN | float32 | Current gain for N15V0A |
        |8      | P5V0D_IGAIN  | float32 | Current gain for P5V0D  |
        |9      | P5V0A_IGAIN  | float32 | Current gain for P5V0A  |
        |10     | N5V0A_IGAIN  | float32 | Current gain for N5V0A  |
        |11     | P3V3D_IGAIN  | float32 | Current gain for P3V3D  |
        |12     | PVLB_IGAIN   | float32 | Current gain for PVLB   |
        |13     | P5V0R_IGAIN  | float32 | Current gain for P5V0R  |
    '''

    command = 0x03
    sub_command = 0x0B
    payload = struct.pack('fffffffffffffff',
                          np.float32(1.0), # RAIL0
                          np.float32(1.0), # P12V0D
                          np.float32(1.0), # RAIL1 
                          np.float32(1.0), # RAIL2 
                          np.float32(1.0), # P25V0D
                          np.float32(1.0), # P17V0D
                          np.float32(1.0), # N7V0D 
                          np.float32(1.0), # P15V0A
                          np.float32(1.0), # N15V0A
                          np.float32(1.0), # P5V0D 
                          np.float32(1.0), # P5V0A 
                          np.float32(1.0), # N5V0A 
                          np.float32(1.0), # P3V3D 
                          np.float32(1.0), # PVLB  
                          np.float32(1.0)) # P5V0R 

    def __init__(self, parent):
        super().__init__(parent)
        self.dialog = SET_CURR_GAINS_DIALOG(__file__, self)

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        (RAIL0_IGAIN,  # self.parent.settings['RAIL0']['IGAIN']
        P12V0D_IGAIN,
        RAIL1_IGAIN, 
        RAIL2_IGAIN, 
        P25V0D_IGAIN,
        P17V0D_IGAIN,
        N7V0D_IGAIN,
        P15V0A_IGAIN,
        N15V0A_IGAIN,
        P5V0D_IGAIN, 
        P5V0A_IGAIN, 
        N5V0A_IGAIN, 
        P3V3D_IGAIN, 
        PVLB_IGAIN,  
        P5V0R_IGAIN) = struct.unpack('ffffffffffffff'. self.parent.payload) 
        
        line  = "Set Boot Sequence Reply :"
        line += f"   P12V0D current gain is {P12V0D_IGAIN} mA/mA"
        line += f"   RAIL1 current gain is {RAIL1_IGAIN} mA/mA"  
        line += f"   RAIL2 current gain is {RAIL2_IGAIN} mA/mA"  
        line += f"   P25V0D current gain is {P25V0D_IGAIN} mA/mA"
        line += f"   P17V0D current gain is {P17V0D_IGAIN} mA/mA"
        line += f"   N7V0D current gain is {N7V0D_IGAIN} mA/mA"  
        line += f"   P15V0A current gain is {P15V0A_IGAIN} mA/mA"
        line += f"   N15V0A current gain is {N15V0A_IGAIN} mA/mA"
        line += f"   P5V0D current gain is {P5V0D_IGAIN} mA/mA"  
        line += f"   P5V0A current gain is {P5V0A_IGAIN} mA/mA"  
        line += f"   N5V0A current gain is {N5V0A_IGAIN} mA/mA"  
        line += f"   P3V3D current gain is {P3V3D_IGAIN} mA/mA"  
        line += f"   PVLB current gain is {PVLB_IGAIN} mA/mA"    
        line += f"   P5V0R current gain is {P5V0R_IGAIN}  mA/mA"

        self.write_to_terminal(line)

