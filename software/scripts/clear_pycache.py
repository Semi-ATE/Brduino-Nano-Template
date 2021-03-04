#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 11 16:47:38 2020

@author: nerohmot
"""
import os
import shutil

project_root = os.path.sep.join(__file__.split(os.path.sep)[:-2])
project_name = __file__.split(os.path.sep)[-3]
project_src = os.path.join(project_root, project_name)


def clear_cache(start_point):
    for Root, Dirs, Files in os.walk(start_point):
        for Dir in Dirs:
            if Dir == '__pycache__':
                rm_target = os.path.join(Root, Dir)
                print(f"removing '{rm_target}' ... ", end='')
                shutil.rmtree(rm_target, ignore_errors=True)
                print('Done')

if __name__ == '__main__':
    clear_cache(project_src)