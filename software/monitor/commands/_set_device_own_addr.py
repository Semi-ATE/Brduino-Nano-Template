#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 11 13:12:00 2020

@author: nerohmot
"""

import struct

from . import command_ABC

class SYS_GET_CLOCKS(command_ABC):
    '''
    TODO: add docstring
    '''

    command = 0x02
    sub_command = 0x70 
    payload = b''

    def receive(self, DA, ACK, RXTX, PAYLOAD):
        (CoreSysClk,
        BusClk,
        FlashClk,
        xtal0Freq,
        McgIrc48MClk) = struct.unpack('IIIII', PAYLOAD)

        line = "sys get clocks:\n"
        line += f"   CoreSysClk = {CoreSysClk}\n"
        line += f"   BusClk = {BusClk}\n"
        line += f"   FlashClk = {FlashClk}\n"
        line += f"   xtal0Freq = {xtal0Freq}\n"
        line += f"   McgIrc48MClk = {McgIrc48MClk}\n"
        self.write_to_terminal(line)
