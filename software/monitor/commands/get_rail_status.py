#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

from . import command_ABC
    
class GET_RAIL_STATUS(command_ABC):
    '''
    Description: gets the status (on/off) of all rails
    
    Input: None
    
    Output: 
    
        | Index | Name        | Type    | Description                        |             
        |:-----:|:------------|:--------|:-----------------------------------|             
        |0      | RAIL1_STAT  | uint8   | RAIL1 status (0=off, 1=on)         |   
        |1      | RAIL2_STAT  | uint8   | RAIL2 status (0=off, 1=on)         |
        |2      | P25V0D_STAT | uint8   | P25V0D status (0=off, 1=on)        |
        |3      | P17V0D_STAT | uint8   | P17V0D status (0=off, 1=on)        |
        |4      | N7V0D_STAT  | uint8   | N7V0D status (0=off, 1=on)         |
        |5      | P15V0A_STAT | uint8   | P15V0A status (0=off, 1=on)        |
        |6      | N15V0A_STAT | uint8   | N15V0A status (0=off, 1=on)        |
        |7      | P5V0D_STAT  | uint8   | P5V0D status (0=off, 1=on)         |
        |8      | P5V0A_STAT  | uint8   | P5V0A status (0=off, 1=on)         |
        |9      | N5V0A_STAT  | uint8   | N5V0A status (0=off, 1=on)         |
        |10     | P3V3D_STAT  | uint8   | P3V3D status (0=off, 1=on)         |
        |11     | PVLB_STAT   | uint8   | PVLB status (0=off, 1=on)          |
        |12     | P5V0R_STAT  | uint8   | P5V0R status (0=off, 1=on)         |
    '''
    
    command = 0x03
    sub_command = 0x06
    default_send_payload = b''

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        line = f"DA={DA} CMD={self.command} SCMD={self.sub_command} ACK={ACK} RXTX={RXTX} PAYLOAD={PAYLOAD}"
        self.parent.output_te.append(line)

