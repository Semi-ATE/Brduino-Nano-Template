#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

from . import command_ABC

class SET_CURR_WINDOWS(command_ABC):
    '''
    Description: set the current windows for all rails
    
    Input: The desired current windows
    
        | Index | Name         | Type    | Description               |             
        |:-----:|:-------------|:--------|:--------------------------|             
        |0      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
        |1      | P12V0D_IHLIM | float32 | P12V0D High Current Limit |
        |2      | RAIL1_ILLIM  | float32 | RAIL1 Low Current Limit   |   
        |3      | RAIL1_IHLIM  | float32 | RAIL1 High Current Limit  |  
        |4      | RAIL2_ILLIM  | float32 | RAIL2 Low Current Limit   |
        |5      | RAIL2_IHLIM  | float32 | RAIL2 High Current Limit  |  
        |6      | P25V0D_ILLIM | float32 | P25V0D Low Current Limit  |
        |7      | P25V0D_IHLIM | float32 | P25V0D High Current Limit |
        |8      | P17V0D_ILLIM | float32 | P17V0D Low Current Limit  |
        |9      | P17V0D_IHLIM | float32 | P17V0D High Current Limit |
        |10     | N7V0D_ILLIM  | float32 | N7V0D Low Current Limit   |
        |11     | N7V0D_IHLIM  | float32 | N7V0D High Current Limit  |
        |12     | P15V0A_ILLIM | float32 | P15V0A Low Current Limit  |
        |13     | P15V0A_IHLIM | float32 | P15V0A High Current Limit |
        |14     | N15V0A_ILLIM | float32 | N15V0A Low Current Limit  |
        |15     | N15V0A_IHLIM | float32 | N15V0A High Current Limit |
        |16     | P5V0D_ILLIM  | float32 | P5V0D Low Current Limit   |
        |17     | P5V0D_IHLIM  | float32 | P5V0D High Current Limit  |
        |18     | P5V0A_ILLIM  | float32 | P5V0A Low Current Limit   |
        |19     | P5V0A_IHLIM  | float32 | P5V0A High Current Limit  |
        |20     | N5V0A_ILLIM  | float32 | N5V0A Low Current Limit   |
        |21     | N5V0A_IHLIM  | float32 | N5V0A High Current Limit  | 
        |22     | P3V3D_ILLIM  | float32 | P3V3D Low Current Limit   |
        |23     | P3V3D_IHLIM  | float32 | P3V3D High Current Limit  |
        |24     | PVLB_ILLIM   | float32 | PVLB Low Current Limit    |
        |25     | PVLB_IHLIM   | float32 | PVLB High Current Limit   |
        |26     | P5V0R_ILLIM  | float32 | P5V0R Low Current Limit   |
        |27     | P5V0R_IHLIM  | float32 | P5V0R High Current Limit  |
    
    Output: The new current windows (should be the same as input)
    
        | Index | Name         | Type    | Description               |             
        |:-----:|:-------------|:--------|:--------------------------|             
        |0      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
        |1      | P12V0D_IHLIM | float32 | P12V0D High Current Limit |
        |2      | RAIL1_ILLIM  | float32 | RAIL1 Low Current Limit   |   
        |3      | RAIL1_IHLIM  | float32 | RAIL1 High Current Limit  |  
        |4      | RAIL2_ILLIM  | float32 | RAIL2 Low Current Limit   |
        |5      | RAIL2_IHLIM  | float32 | RAIL2 High Current Limit  |  
        |6      | P25V0D_ILLIM | float32 | P25V0D Low Current Limit  |
        |7      | P25V0D_IHLIM | float32 | P25V0D High Current Limit |
        |8      | P17V0D_ILLIM | float32 | P17V0D Low Current Limit  |
        |9      | P17V0D_IHLIM | float32 | P17V0D High Current Limit |
        |10     | N7V0D_ILLIM  | float32 | N7V0D Low Current Limit   |
        |11     | N7V0D_IHLIM  | float32 | N7V0D High Current Limit  |
        |12     | P15V0A_ILLIM | float32 | P15V0A Low Current Limit  |
        |13     | P15V0A_IHLIM | float32 | P15V0A High Current Limit |
        |14     | N15V0A_ILLIM | float32 | N15V0A Low Current Limit  |
        |15     | N15V0A_IHLIM | float32 | N15V0A High Current Limit |
        |16     | P5V0D_ILLIM  | float32 | P5V0D Low Current Limit   |
        |17     | P5V0D_IHLIM  | float32 | P5V0D High Current Limit  |
        |18     | P5V0A_ILLIM  | float32 | P5V0A Low Current Limit   |
        |19     | P5V0A_IHLIM  | float32 | P5V0A High Current Limit  |
        |20     | N5V0A_ILLIM  | float32 | N5V0A Low Current Limit   |
        |21     | N5V0A_IHLIM  | float32 | N5V0A High Current Limit  | 
        |22     | P3V3D_ILLIM  | float32 | P3V3D Low Current Limit   |
        |23     | P3V3D_IHLIM  | float32 | P3V3D High Current Limit  |
        |24     | PVLB_ILLIM   | float32 | PVLB Low Current Limit    |
        |25     | PVLB_IHLIM   | float32 | PVLB High Current Limit   |
        |26     | P5V0R_ILLIM  | float32 | P5V0R Low Current Limit   |
        |27     | P5V0R_IHLIM  | float32 | P5V0R High Current Limit  |
    '''
    
    command = 0x03
    sub_command = 0x13
    default_send_payload = b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'  # all values to 0.0
    
    def receive(self, DA, ACK, RXTX, PAYLOAD):
        line = f"DA={DA} CMD={self.command} SCMD={self.sub_command} ACK={ACK} RXTX={RXTX} PAYLOAD={PAYLOAD}"
        self.parent.output_te.append(line)

