#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

import struct    

from PyQt5 import QtWidgets

from . import command_ABC, command_dialog
 
class SET_BOOT_STAGE_DIALOG(command_dialog):
    
    def accept(self):
    
        self.parent.payload = struct.pack('B', self.bootStageSpinBox.value())
        self.parent.send()
        self.done(QtWidgets.QDialog.Accepted)


class SET_BOOT_STAGE(command_ABC):
    '''
    Description: With this we can change the boot stage.
    
    Input: The new boot stage, an integer being 0, 1 or 2.
    
    Output: 
    
        | Index | Name        | Type    | Description |
        |:-----:|:------------|:--------|:------------|
        |0      | BOOT_STAGE  | uint8   | The resulting boot stage |
        |1      | N5V0A_VMON  | float32 | The voltage* on N5V0A |
        |2      | RAIL1_VMON  | float32 | The voltage* on RAIL1 |
        |3      | P3V3D_VMON  | float32 | The voltage* on P3V3D |
        |4      | P5V0D_VMON  | float32 | The voltage* on P5V0D |
        |5      | RAIL0_VMON  | float32 | The voltage* on RAIL0 |
        |6      | P5V0R_VMON  | float32 | The voltage* on P5V0R |
        |7      | PVLB_VMON   | float32 | The voltage* on PVLB |
        |8      | P12V0D_VMON | float32 | The voltage* on P12V0D |
        |9      | P5V0A_VMON  | float32 | The voltage* on P5V0A |
        |10     | RAIL2_VMON  | float32 | The voltage* on RAIL2 |
        |11     | N15V0A_VMON | float32 | The voltage* on N15V0A |
        |12     | P15V0A_VMON | float32 | The voltage* on P15V0A |
        |13     | P25V0D_VMON | float32 | The voltage* on P25V0D |
        |14     | P17V0D_VMON | float32 | The voltage* on P17V0D |
        |15     | N7V0D_VMON  | float32 | The voltage* on N7V0D |
        |16     | GND_VMON    | float32 | The voltage* on GND |
    
    * corrected by applying the gain and offset for each monitor. The unit is Volt.
    
    If we go from BootStage0 ➜ BootStage1, and something is wrong (eg: fuse is blown), then the resulting BOOT_STAGE will be still 0, 
    and the measured voltages are returned, this way we can (with the help of other commands) determine what went wrong. 
    
    If on the other hand everythin is ok, the BOOT_STAGE will be 1, and a voltage for each rail is returned.
    '''    
    
    command = 0x03
    sub_command = 0x03
    default_send_payload = struct.pack('B', 2)  # boot stage 2

    def __init__(self, parent):
        super().__init__(parent)
        self.dialog = SET_BOOT_STAGE_DIALOG(__file__, self.parent)

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        (current_boot_stage,
        N5V0A,
        RAIL1,
        P3V3D, 
        P5V0D, 
        RAIL0, 
        P5V0R, 
        PVLB,
        P12V0D,
        P5V0A, 
        RAIL2, 
        N15V0A,
        P15V0A,
        P25V0D,
        P17V0D,
        N7V0D, 
        GND) = struct.unpack('Bffffffffffffffff', PAYLOAD)

        line = f"set_boot_stage -> {current_boot_stage}"

        self.parent.output_te.append(line)

