#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

import struct    

from .common import command_ABC

class GET_BOOT_STAGE(command_ABC):
    '''
    Description: Returns the current boot stage.
    
    Input: None
    
    Output: The current boot stage (it is an integer being 0,1 or 2) and the
            last measurements of the rails.
    
    | Index | Name        | Type    | Description              |
    |:-----:|:------------|:--------|:-------------------------|
    |0      | BOOT_STAGE  | uint8   | The resulting boot stage |
    |1      | N5V0A_VMON  | float32 | The voltage* on N5V0A    | 
    |2      | RAIL1_VMON  | float32 | The voltage* on RAIL1    |
    |3      | P3V3D_VMON  | float32 | The voltage* on P3V3D    |  
    |4      | P5V0D_VMON  | float32 | The voltage* on P5V0D    |
    |5      | RAIL0_VMON  | float32 | The voltage* on RAIL0    |
    |6      | P5V0R_VMON  | float32 | The voltage* on P5V0R    |
    |7      | PVLB_VMON   | float32 | The voltage* on PVLB     |
    |8      | P12V0D_VMON | float32 | The voltage* on P12V0D   |
    |9      | P5V0A_VMON  | float32 | The voltage* on P5V0A    |
    |10     | RAIL2_VMON  | float32 | The voltage* on RAIL2    |
    |11     | N15V0A_VMON | float32 | The voltage* on N15V0A   |
    |12     | P15V0A_VMON | float32 | The voltage* on P15V0A   |
    |13     | P25V0D_VMON | float32 | The voltage* on P25V0D   |
    |14     | P17V0D_VMON | float32 | The voltage* on P17V0D   |
    |15     | N7V0D_VMON  | float32 | The voltage* on N7V0D    |
    |16     | GND_VMON    | float32 | The voltage* on GND      |
    
    * corrected by applying the gain and offset for each monitor. The unit is Volt.
    
    If we go from BootStage0 ➜ BootStage1, and something is wrong (eg: fuse is blown), then the resulting BOOT_STAGE will be still 0, 
    and the measured voltages are returned, this way we can (with the help of other commands) determine what went wrong. 
    
    If on the other hand everythin is ok, the BOOT_STAGE will be 1, and a voltage for each rail is returned.
    '''
    
    command = 0x03
    sub_command = 0x02
    payload = b''

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        (BOOT_STAGE, 
        N5V0A_VMON, 
        RAIL1_VMON, 
        P3V3D_VMON, 
        P5V0D_VMON, 
        RAIL0_VMON, 
        P5V0R_VMON, 
        PVLB_VMON,  
        P12V0D_VMON,
        P5V0A_VMON, 
        RAIL2_VMON, 
        N15V0A_VMON,
        P15V0A_VMON,
        P25V0D_VMON,
        P17V0D_VMON,
        N7V0D_VMON, 
        GND_VMON) = struct.unpack('Bfffffffffffffff', PAYLOAD)   

        line = "Get Boot Stage Reply :"
        line += f"   Current Boot Level = {BOOT_STAGE}"
        line += f"   RAIL0 = {RAIL0_VMON} V" 
        line += f"   RAIL1 = {RAIL1_VMON} V" 
        line += f"   RAIL2 = {RAIL2_VMON} V" 
        line += f"   P25V0D = {P25V0D_VMON} V"
        line += f"   P17V0D = {P17V0D_VMON} V"
        line += f"   N7V0D = {N7V0D_VMON} V" 
        line += f"   P15V0A = {P15V0A_VMON} V"
        line += f"   N15V0A = {N15V0A_VMON} V"
        line += f"   P5V0D = {P5V0D_VMON} V" 
        line += f"   P5V0A = {P5V0A_VMON} V" 
        line += f"   N5V0A = {N5V0A_VMON} V" 
        line += f"   P3V3D = {P3V3D_VMON} V" 
        line += f"   PVLB = {PVLB_VMON} V"  
        line += f"   P5V0R = {P5V0R_VMON} V" 
        line += f"   GND = {GND_VMON} V"   

        self.parent.output_te.append(line)

