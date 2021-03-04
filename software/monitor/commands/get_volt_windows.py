#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

from . import command_ABC

class GET_VOLT_WINDOWS(command_ABC):
    '''
    Description: A window is a set of upper and lower limits that determine if a rail is considered OK or not. A measurement is considered OK if (after applying the appropriate gain and offset) it is in the interval LLIM <= MEAS <= HLIM.
    
    Input: None
    
    Output:
    
        | Index | Name         | Type    | Description               |             
        |:-----:|:-------------|:--------|:--------------------------|             
        |0      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
        |1      | P12V0D_VHLIM | float32 | P12V0D Low Voltage Limit  |
        |2      | RAIL1_VLLIM  | float32 | RAIL1 Low Voltage Limit   |   
        |3      | RAIL1_VHLIM  | float32 | RAIL1 High Voltage Limit  |  
        |4      | RAIL2_VLLIM  | float32 | RAIL2 Low Voltage Limit   |
        |5      | RAIL2_VHLIM  | float32 | RAIL2 High Voltage Limit  |  
        |6      | P25V0D_VLLIM | float32 | P25V0D Low Voltage Limit  |
        |7      | P25V0D_VHLIM | float32 | P25V0D High Voltage Limit |
        |8      | P17V0D_VLLIM | float32 | P17V0D Low Voltage Limit  |
        |9      | P17V0D_VHLIM | float32 | P17V0D High Voltage Limit |
        |10     | N7V0D_VLLIM  | float32 | N7V0D Low Voltage Limit   |
        |11     | N7V0D_VHLIM  | float32 | N7V0D High Voltage Limit  |
        |12     | P15V0A_VLLIM | float32 | P15V0A Low Voltage Limit  |
        |13     | P15V0A_VHLIM | float32 | P15V0A High Voltage Limit |
        |14     | N15V0A_VLLIM | float32 | N15V0A Low Voltage Limit  |
        |15     | N15V0A_VHLIM | float32 | N15V0A High Voltage Limit |
        |16     | P5V0D_VLLIM  | float32 | P5V0D Low Voltage Limit   |
        |17     | P5V0D_VHLIM  | float32 | P5V0D High Voltage Limit  |
        |18     | P5V0A_VLLIM  | float32 | P5V0A Low Voltage Limit   |
        |19     | P5V0A_VHLIM  | float32 | P5V0A High Voltage Limit  |
        |20     | N5V0A_VLLIM  | float32 | N5V0A Low Voltage Limit   |
        |21     | N5V0A_VHLIM  | float32 | N5V0A High Voltage Limit  | 
        |22     | P3V3D_VLLIM  | float32 | P3V3D Low Voltage Limit   |
        |23     | P3V3D_VHLIM  | float32 | P3V3D High Voltage Limit  |
        |24     | PVLB_VLLIM   | float32 | PVLB Low Voltage Limit    |
        |25     | PVLB_VHLIM   | float32 | PVLB High Voltage Limit   |
        |26     | P5V0R_VLLIM  | float32 | P5V0R Low Voltage Limit   |
        |27     | P5V0R_VHLIM  | float32 | P5V0R High Voltage Limit  |
        |28     | GND_VLLIM    | float32 | GND Low Voltage Limit     |
        |29     | GND_VHLIM    | float32 | GND High Voltage Limit    |
    '''
    
    command = 0x03
    sub_command = 0x10
    default_send_payload = b''

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        line = f"DA={DA} CMD={self.command} SCMD={self.sub_command} ACK={ACK} RXTX={RXTX} PAYLOAD={PAYLOAD}"
        self.parent.output_te.append(line)

