#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

from . import command_ABC
    
class NOTIFICATION(command_ABC):
    '''
    Description: The PowerBoard controller will send this package if he encounters something wrong in the regular Voltage/Current monitoring.
    
    Input: N/A
    
    Output:
    
        | Index | Name        | Type    | Description                |             
        |:-----:|:------------|:--------|:---------------------------|
        |0      | P12V0D_VMON | float32 | Voltage on the P12V0D rail |
        |1      | P12V0D_IMON | float32 | Current in the P12V0D rail |   
        |2      | RAIL1_VMON  | float32 | Voltage on the RAIL1 rail  |
        |3      | RAIL1_IMON  | float32 | Current in the RAIL1 rail  |
        |4      | RAIL2_VMON  | float32 | Voltage on the RAIL2 rail  |
        |5      | RAIL2_IMON  | float32 | Current in the RAIL2 rail  |
        |6      | P25V0D_VMON | float32 | Voltage on the P25V0D rail |
        |7      | P25V0D_IMON | float32 | Current in the P25V0D rail |
        |8      | P17V0D_VMON | float32 | Voltage on the P17V0D rail |
        |9      | P17V0D_IMON | float32 | Current in the P17V0D rail |
        |10     | N7V0D_VMON  | float32 | Voltage on the N7V0D rail  |
        |11     | N7V0D_IMON  | float32 | Current in the N7V0D rail  |
        |12     | P15V0A_VMON | float32 | Voltage on the P15V0A rail |
        |13     | P15V0A_IMON | float32 | Current in the P15V0A rail |
        |14     | N15V0A_VMON | float32 | Voltage on the N15V0A rail |
        |15     | N15V0A_IMON | float32 | Current in the N15V0A rail |
        |16     | P5V0D_VMON  | float32 | Voltage on the P5V0D rail  |
        |17     | P5V0D_IMON  | float32 | Current in the P5V0D rail  |
        |18     | P5V0A_VMON  | float32 | Voltage on the P5V0A rail  |
        |19     | P5V0A_IMON  | float32 | Current in the P5V0A rail  |
        |20     | N5V0A_VMON  | float32 | Voltage on the N5V0A rail  |
        |21     | N5V0A_IMON  | float32 | Current in the N5V0A rail  |
        |22     | P3V3D_VMON  | float32 | Voltage on the P3V3D rail  |
        |23     | P3V3D_IMON  | float32 | Current in the P3V3D rail  |
        |24     | PVLB_VMON   | float32 | Voltage on the PVLB rail   |
        |25     | PVLB_IMON   | float32 | Current in the PVLB rail   |
        |26     | P5V0R_VMON  | float32 | Voltage on the P5V0R rail  |
        |27     | P5V0R_IMON  | float32 | Current in the P5V0R rail  |
        |28     | GND_VMON    | float32 | Voltage on the GND         |
    '''

    command = 0x03
    sub_command = 0x14

    def send(self, payload=None):
        pass  # This is an unsolicted command, so we disable the send for it.

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        line = f"DA={DA} CMD={self.command} SCMD={self.sub_command} ACK={ACK} RXTX={RXTX} PAYLOAD={PAYLOAD}"
        self.parent.output_te.append(line)

