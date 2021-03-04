#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 10 18:08:52 2020

@author: nerohmot
"""

def pkg_dump(pkg):
    '''
    This function returns a nice formatted version of the package.
    '''
    retval = ''
    for element in pkg:
        retval += f"{element:02X} "
    return retval[:-1]
