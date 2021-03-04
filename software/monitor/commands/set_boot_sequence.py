#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

import struct

from PyQt5 import QtWidgets

from . import command_ABC, command_dialog
    
class SET_BOOT_SEQUENCE_DIALOG(command_dialog):

    def exec(self):
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
        P5V0R_SEQ,  P5V0R_DEL) = struct.unpack('BBBBBBBBBBBBBBBBBBBBBBBBBB', self.parent.payload)

        self.RAIL1_SEQ.setValue(RAIL1_SEQ)
        self.RAIL2_SEQ.setValue(RAIL2_SEQ)
        self.P25V0D_SEQ.setValue(P25V0D_SEQ)
        self.P17V0D_SEQ.setValue(P17V0D_SEQ)
        self.N7V0D_SEQ.setValue(N7V0D_SEQ)
        self.P15V0A_SEQ.setValue(P15V0A_SEQ)
        self.N15V0A_SEQ.setValue(N15V0A_SEQ)
        self.P5V0D_SEQ.setValue(P5V0D_SEQ)
        self.P5V0A_SEQ.setValue(P5V0A_SEQ)
        self.N5V0A_SEQ.setValue(N5V0A_SEQ)
        self.P3V3D_SEQ.setValue(P3V3D_SEQ)
        self.PVLB_SEQ.setValue(PVLB_SEQ)
        self.P5V0R_SEQ.setValue(P5V0R_SEQ)
                                           
        self.RAIL1_DEL.setValue(RAIL1_DEL)
        self.RAIL2_DEL.setValue(RAIL2_DEL)
        self.P25V0D_DEL.setValue(P25V0D_DEL)
        self.P17V0D_DEL.setValue(P17V0D_DEL)
        self.N7V0D_DEL.setValue(N7V0D_DEL)
        self.P15V0A_DEL.setValue(P15V0A_DEL)
        self.N15V0A_DEL.setValue(N15V0A_DEL)
        self.P5V0D_DEL.setValue(P5V0D_DEL)
        self.P5V0A_DEL.setValue(P5V0A_DEL)
        self.N5V0A_DEL.setValue(N5V0A_DEL)
        self.P3V3D_DEL.setValue(P3V3D_DEL)
        self.PVLB_DEL.setValue(PVLB_DEL)
        self.P5V0R_DEL.setValue(P5V0R_DEL)

        super().exec()

    def accept(self):
    
        self.parent.payload = struct.pack('BBBBBBBBBBBBBBBBBBBBBBBBBB',
                                          self.RAIL1_SEQ.value(), self.RAIL1_DEL.value(),    # RAIL1
                                          self.RAIL2_SEQ.value(), self.RAIL2_DEL.value(),    # RAIL2
                                          self.P25V0D_SEQ.value(), self.P25V0D_DEL.value(),  # P25V0
                                          self.P17V0D_SEQ.value(), self.P17V0D_DEL.value(),  # P17V0
                                          self.N7V0D_SEQ.value(), self.N7V0D_DEL.value(),    # N7V0D
                                          self.P15V0A_SEQ.value(), self.P15V0A_DEL.value(),  # P15V0
                                          self.N15V0A_SEQ.value(), self.N15V0A_DEL.value(),  # N15V0
                                          self.P5V0D_SEQ.value(), self.P5V0D_DEL.value(),    # P5V0D
                                          self.P5V0A_SEQ.value(), self.P5V0A_DEL.value(),    # P5V0A
                                          self.N5V0A_SEQ.value(), self.N5V0A_DEL.value(),    # N5V0A
                                          self.P3V3D_SEQ.value(), self.P3V3D_DEL.value(),    # P3V3D
                                          self.PVLB_SEQ.value(), self.PVLB_DEL.value(),      # PVLB 
                                          self.P5V0R_SEQ.value(), self.P5V0R_DEL.value())    # P5V0R
        self.parent.send()
        self.done(QtWidgets.QDialog.Accepted)

class SET_BOOT_SEQUENCE(command_ABC):
    '''
    Description: With this we can configure the boot sequence.
    
    Input: The desired sequence and delay for each rail
    
        | Index | Name       | Type    | Description                        |             
        |:-----:|:-----------|:--------|:-----------------------------------|             
        |0      | RAIL1_SEQ  | uint8   | RAIL1 sequence number              |   
        |1      | RAIL1_DEL  | uint8   | Wait 100ms after turning on RAIL1  |  
        |2      | RAIL2_SEQ  | uint8   | RAIL2 sequence number              |
        |3      | RAIL2_DEL  | uint8   | Wait 100ms after turning on RAIL2  |  
        |4      | P25V0D_SEQ | uint8   | P25V0D sequence number             |
        |5      | P25V0D_DEL | uint8   | Wait 100ms after turning on P25V0D | 
        |6      | P17V0D_SEQ | uint8   | P17V0D sequence number             |
        |7      | P17V0D_DEL | uint8   | Wait 100ms after turning on P17V0D | 
        |8      | N7V0D_SEQ  | uint8   | N7V0D sequence number              |
        |9      | N7V0D_DEL  | uint8   | Wait 100ms after turning on N7V0D  |  
        |10     | P15V0A_SEQ | uint8   | P15V0A sequence number             |
        |11     | P15V0A_DEL | uint8   | Wait 100ms after turning on P15V0A | 
        |12     | N15V0A_SEQ | uint8   | N15V0A sequence number             |
        |13     | N15V0A_DEL | uint8   | Wait 100ms after turning on N15V0A | 
        |14     | P5V0D_SEQ  | uint8   | P5V0D sequence number              |
        |15     | P5V0D_DEL  | uint8   | Wait 100ms after turning on P5V0D  |  
        |16     | P5V0A_SEQ  | uint8   | P5V0A sequence number              |
        |17     | P5V0A_DEL  | uint8   | Wait 100ms after turning on P5V0A  |  
        |18     | N5V0A_SEQ  | uint8   | N5V0A sequence number              |
        |19     | N5V0A_DEL  | uint8   | Wait 100ms after turning on N5V0A  |  
        |20     | P3V3D_SEQ  | uint8   | P3V3D sequence number              |
        |21     | P3V3D_DEL  | uint8   | Wait 100ms after turning on P3V3D  |  
        |22     | PVLB_SEQ   | uint8   | PVLB sequence number               |
        |23     | PVLB_DEL   | uint8   | Wait 100ms after turning on PVLB   |   
        |24     | P5V0R_SEQ  | uint8   | P5V0R sequence number              |
        |25     | P5V0R_DEL  | uint8   | Wait 100ms after turning on P5V0R  |  
    
    Output: The new (current) sequence and delay (should match the input)
    
        | Index | Name       | Type    | Description                        |             
        |:-----:|:-----------|:--------|:-----------------------------------|             
        |0      | RAIL1_SEQ  | uint8   | RAIL1 sequence number              |   
        |1      | RAIL1_DEL  | uint8   | Wait 100ms after turning on RAIL1  |  
        |2      | RAIL2_SEQ  | uint8   | RAIL2 sequence number              |
        |3      | RAIL2_DEL  | uint8   | Wait 100ms after turning on RAIL2  |  
        |4      | P25V0D_SEQ | uint8   | P25V0D sequence number             |
        |5      | P25V0D_DEL | uint8   | Wait 100ms after turning on P25V0D | 
        |6      | P17V0D_SEQ | uint8   | P17V0D sequence number             |
        |7      | P17V0D_DEL | uint8   | Wait 100ms after turning on P17V0D | 
        |8      | N7V0D_SEQ  | uint8   | N7V0D sequence number              |
        |9      | N7V0D_DEL  | uint8   | Wait 100ms after turning on N7V0D  |  
        |10     | P15V0A_SEQ | uint8   | P15V0A sequence number             |
        |11     | P15V0A_DEL | uint8   | Wait 100ms after turning on P15V0A | 
        |12     | N15V0A_SEQ | uint8   | N15V0A sequence number             |
        |13     | N15V0A_DEL | uint8   | Wait 100ms after turning on N15V0A | 
        |14     | P5V0D_SEQ  | uint8   | P5V0D sequence number              |
        |15     | P5V0D_DEL  | uint8   | Wait 100ms after turning on P5V0D  |  
        |16     | P5V0A_SEQ  | uint8   | P5V0A sequence number              |
        |17     | P5V0A_DEL  | uint8   | Wait 100ms after turning on P5V0A  |  
        |18     | N5V0A_SEQ  | uint8   | N5V0A sequence number              |
        |19     | N5V0A_DEL  | uint8   | Wait 100ms after turning on N5V0A  |  
        |20     | P3V3D_SEQ  | uint8   | P3V3D sequence number              |
        |21     | P3V3D_DEL  | uint8   | Wait 100ms after turning on P3V3D  |  
        |22     | PVLB_SEQ   | uint8   | PVLB sequence number               |
        |23     | PVLB_DEL   | uint8   | Wait 100ms after turning on PVLB   |   
        |24     | P5V0R_SEQ  | uint8   | P5V0R sequence number              |
        |25     | P5V0R_DEL  | uint8   | Wait 100ms after turning on P5V0R  |  
    '''
    
    command = 0x03
    sub_command = 0x05
    payload = struct.pack('BBBBBBBBBBBBBBBBBBBBBBBBBB',
                          0, 250, # RAIL1
                          1, 250, # RAIL2
                          2, 100, # P25V0
                          2, 100, # P17V0
                          2, 100, # N7V0D
                          3, 100, # P15V0
                          3, 100, # N15V0
                          4, 100, # P5V0D
                          4, 100, # P5V0A
                          4, 100, # N5V0A
                          5, 100, # P3V3D
                          0, 100, # PVLB 
                          1, 100) # P5V0R

    def __init__(self, parent):
        super().__init__(parent)
        self.dialog = SET_BOOT_SEQUENCE_DIALOG(__file__, self)
        
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
        
        line = "Set Boot Sequence Reply :"
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

        self.write_to_terminal(line)

