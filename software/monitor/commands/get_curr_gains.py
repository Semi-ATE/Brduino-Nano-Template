#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

from . import command_ABC

class GET_CURR_GAINS(command_ABC):
    '''
    Description: get a list of the current gains for all rails.
    
    Input: None
    
    Output:
    
        | Index | Name         | Type    | Description             |             
        |:-----:|:-------------|:--------|:------------------------|             
        |0      | P12VoD_IGAIN | float32 | Current gain for P12V0D |
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
    sub_command = 0x0A
    default_send_payload = b''
    
    def receive(self, DA, ACK, RXTX, PAYLOAD):
        line = f"DA={DA} CMD={self.command} SCMD={self.sub_command} ACK={ACK} RXTX={RXTX} PAYLOAD={PAYLOAD}"
        self.parent.output_te.append(line)

