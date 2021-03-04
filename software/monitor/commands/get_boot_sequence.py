#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

import struct

from .common import command_ABC
     
class GET_BOOT_SEQUENCE(command_ABC):
    '''
    Description: With this we can get the current boot sequence and timing.
    
    Input: None
    
    Output:
    
        | Index | Name       | Type    | Default | BOOT_STAGE | Description                        |             
        |:-----:|:-----------|:--------|:--------|:-----------|:-----------------------------------|             
        |0      | RAIL1_SEQ  | uint8   | 1       | 1          | RAIL1 sequence number              |   
        |1      | RAIL1_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on RAIL1  |  
        |2      | RAIL2_SEQ  | uint8   | 2       | 1          | RAIL2 sequence number              |
        |3      | RAIL2_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on RAIL2  |  
        |4      | P25V0D_SEQ | uint8   | 3       | 1          | P25V0D sequence number             |
        |5      | P25V0D_DEL | uint8   | 100     | 1          | Wait 100ms after turning on P25V0D | 
        |6      | P17V0D_SEQ | uint8   | 3       | 1          | P17V0D sequence number             |
        |7      | P17V0D_DEL | uint8   | 100     | 1          | Wait 100ms after turning on P17V0D | 
        |8      | N7V0D_SEQ  | uint8   | 3       | 1          | N7V0D sequence number              |
        |9      | N7V0D_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on N7V0D  |  
        |10     | P15V0A_SEQ | uint8   | 4       | 1          | P15V0A sequence number             |
        |11     | P15V0A_DEL | uint8   | 100     | 1          | Wait 100ms after turning on P15V0A | 
        |12     | N15V0A_SEQ | uint8   | 4       | 1          | N15V0A sequence number             |
        |13     | N15V0A_DEL | uint8   | 100     | 1          | Wait 100ms after turning on N15V0A | 
        |14     | P5V0D_SEQ  | uint8   | 5       | 1          | P5V0D sequence number              |
        |15     | P5V0D_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on P5V0D  |  
        |16     | P5V0A_SEQ  | uint8   | 5       | 1          | P5V0A sequence number              |
        |17     | P5V0A_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on P5V0A  |  
        |18     | N5V0A_SEQ  | uint8   | 5       | 1          | N5V0A sequence number              |
        |19     | N5V0A_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on N5V0A  |  
        |20     | P3V3D_SEQ  | uint8   | 6       | 1          | P3V3D sequence number              |
        |21     | P3V3D_DEL  | uint8   | 100     | 1          | Wait 100ms after turning on P3V3D  |  
        |22     | PVLB_SEQ   | uint8   | 7       | 2          | PVLB sequence number               |
        |23     | PVLB_DEL   | uint8   | 100     | 2          | Wait 100ms after turning on PVLB   |   
        |24     | P5V0R_SEQ  | uint8   | 8       | 2          | P5V0R sequence number              |
        |25     | P5V0R_DEL  | uint8   | 100     | 2          | Wait 100ms after turning on P5V0R  |  
    
    Note: It is possible to switch some rails on together! In such case one needs to wait the longest of the delays before continuing 
    (in case the the DELays are not the same).
    '''
    
    command = 0x03
    sub_command = 0x04
    payload = b''
    
    def receive(self, DA, ACK, RXTX, PAYLOAD):
        (RAIL1_SEQ, RAIL1_DEL, 
        RAIL2_SEQ,  RAIL2_DEL, 
        P25V0D_SEQ, P25V0D_DEL,
        P17V0D_SEQ, P17V0D_DEL,
        N7V0D_SEQ,  N7V0D_DEL, 
        P15V0A_SEQ, P15V0A_DEL,
        N15V0A_SEQ, N15V0A_DEL,
        P5V0D_SEQ,  P5V0D_DEL, 
        P5V0A_SEQ,  P5V0A_DEL, 
        N5V0A_SEQ,  N5V0A_DEL, 
        P3V3D_SEQ,  P3V3D_DEL, 
        PVLB_SEQ,   PVLB_DEL,  
        P5V0R_SEQ,  P5V0R_DEL) = struct.unpack('BBBBBBBBBBBBBBBBBBBBBBBBBB', PAYLOAD)
        
        line = "Get Boot Sequence Reply :"
        line += f"   RAIL1 sequence # is {RAIL1_SEQ} and delay is {RAIL1_DEL} ms" 
        line += f"   RAIL2 sequence # is {RAIL2_SEQ} and delay is {RAIL2_DEL} ms" 
        line += f"   P25V0D sequence # is {P25V0D_SEQ} and delay is {P25V0D_DEL} ms"
        line += f"   P17V0D sequence # is {P17V0D_SEQ} and delay is {P17V0D_DEL} ms"
        line += f"   N7V0D sequence # is {N7V0D_SEQ} and delay is {N7V0D_DEL} ms" 
        line += f"   P15V0A sequence # is {P15V0A_SEQ} and delay is {P15V0A_DEL} ms"
        line += f"   N15V0A sequence # is {N15V0A_SEQ} and delay is {N15V0A_DEL} ms"
        line += f"   P5V0D sequence # is {P5V0D_SEQ} and delay is {P5V0D_DEL} ms" 
        line += f"   P5V0A sequence # is {P5V0A_SEQ} and delay is {P5V0A_DEL} ms" 
        line += f"   N5V0A sequence # is {N5V0A_SEQ} and delay is {N5V0A_DEL} ms" 
        line += f"   P3V3D sequence # is {P3V3D_SEQ} and delay is {P3V3D_DEL} ms" 
        line += f"   PVLB sequence # is {PVLB_SEQ} and delay is {PVLB_DEL} ms"  
        line += f"   P5V0R sequence # is {P5V0R_SEQ} and delay is {P5V0R_DEL} ms"
        
        line = f"DA={DA} CMD={self.command} SCMD={self.sub_command} ACK={ACK} RXTX={RXTX} PAYLOAD={PAYLOAD}"

        self.parent.output_te.append(line)

