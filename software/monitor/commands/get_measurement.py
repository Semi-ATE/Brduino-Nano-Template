#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  4 14:49:27 2020

@author: nerohmot
"""

import struct

from . import command_ABC

class GET_MEASUREMENT(command_ABC):
    '''
    Description: get all measurements (gains & offsets already applied)

    Input: None

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

    Note: rails that are not turned ON will return a 'NaN' (numpy.NaN = b'\x00\x00\xc0\x7f')
    '''

    command = 0x03
    sub_command = 0x01
    payload = b''
 
    def receive(self, DA, ACK, RXTX, PAYLOAD):
        (P12V0D_VMON, P12V0D_IMON,
        RAIL1_VMON, RAIL1_IMON, 
        RAIL2_VMON, RAIL2_IMON, 
        P25V0D_VMON, P25V0D_IMON,
        P17V0D_VMON, P17V0D_IMON,
        N7V0D_VMON, N7V0D_IMON, 
        P15V0A_VMON,P15V0A_IMON,
        N15V0A_VMON, N15V0A_IMON,
        P5V0D_VMON, P5V0D_IMON, 
        P5V0A_VMON, P5V0A_IMON, 
        N5V0A_VMON, N5V0A_IMON, 
        P3V3D_VMON, P3V3D_IMON, 
        PVLB_VMON, PVLB_IMON,  
        P5V0R_VMON, P5V0R_IMON, 
        GND_VMON) = struct.unpack('fffffffffffffffffffffffffffff', PAYLOAD)   

        self.parent.df.at[self.parent.df_row, 'P12V0D_VMON'] = P12V0D_VMON 
        self.parent.df.at[self.parent.df_row, 'P12V0D_IMON'] = P12V0D_IMON
        self.parent.df.at[self.parent.df_row, 'RAIL1_VMON'] = RAIL1_VMON
        self.parent.df.at[self.parent.df_row, 'RAIL1_IMON'] = RAIL1_IMON
        self.parent.df.at[self.parent.df_row, 'RAIL2_VMON'] = RAIL2_VMON
        self.parent.df.at[self.parent.df_row, 'RAIL2_IMON'] = RAIL2_IMON
        self.parent.df.at[self.parent.df_row, 'P25V0D_VMON'] = P25V0D_VMON
        self.parent.df.at[self.parent.df_row, 'P25V0D_IMON'] = P25V0D_IMON
        self.parent.df.at[self.parent.df_row, 'P17V0D_VMON'] = P17V0D_VMON
        self.parent.df.at[self.parent.df_row, 'P17V0D_IMON'] = P17V0D_IMON
        self.parent.df.at[self.parent.df_row, 'N7V0D_VMON'] = N7V0D_VMON
        self.parent.df.at[self.parent.df_row, 'N7V0D_IMON'] = N7V0D_IMON
        self.parent.df.at[self.parent.df_row, 'P15V0A_VMON'] = P15V0A_VMON
        self.parent.df.at[self.parent.df_row, 'P15V0A_IMON'] = P15V0A_IMON
        self.parent.df.at[self.parent.df_row, 'N15V0A_VMON'] = N15V0A_VMON
        self.parent.df.at[self.parent.df_row, 'N15V0A_IMON'] = N15V0A_IMON
        self.parent.df.at[self.parent.df_row, 'P5V0D_VMON'] = P5V0D_VMON
        self.parent.df.at[self.parent.df_row, 'P5V0D_IMON'] = P5V0D_IMON
        self.parent.df.at[self.parent.df_row, 'P5V0A_VMON'] = P5V0A_VMON
        self.parent.df.at[self.parent.df_row, 'P5V0A_IMON'] = P5V0A_IMON
        self.parent.df.at[self.parent.df_row, 'N5V0A_VMON'] = N5V0A_VMON
        self.parent.df.at[self.parent.df_row, 'N5V0A_IMON'] = N5V0A_IMON
        self.parent.df.at[self.parent.df_row, 'P3V3D_VMON'] = P3V3D_VMON
        self.parent.df.at[self.parent.df_row, 'P3V3D_IMON'] = P3V3D_IMON
        self.parent.df.at[self.parent.df_row, 'PVLB_VMON'] = PVLB_VMON
        self.parent.df.at[self.parent.df_row, 'PVLB_IMON'] = PVLB_IMON
        self.parent.df.at[self.parent.df_row, 'P5V0R_VMON'] = P5V0R_VMON
        self.parent.df.at[self.parent.df_row, 'P5V0R_IMON'] = P5V0R_IMON
        self.parent.df.at[self.parent.df_row, 'GND_VMON'] = GND_VMON 

        self.parent.df_row += 1

        if self.parent.df.shape[0] == self.parent.df_row:
            chunk = pd.DataFrame(columns=self.parent.df_columns, index=range(self.parent.ChunkSize)).astype(np.float32)
            self.parent.df.append(chunk, ignore_index=True)

        line = "Get Measurement Reply :\n"
        line +=  "  +--------+--------+----------+\n"
        line +=  "  | Rail   |    [V] |     [mA] |\n"
        line +=  "  +--------+--------+----------+\n"
        line += f"  | P12V0D | {P12V0D_VMON:>6.3f} | {P12V0D_IMON:>8.3f} |\n"
        line += f"  | RAIL1  | {RAIL1_VMON:>6.3f} | {RAIL1_IMON:>8.3f} |\n" 
        line += f"  | RAIL2  | {RAIL2_VMON:>6.3f} | {RAIL2_IMON:>8.3f} |\n" 
        line += f"  | P25V0D | {P25V0D_VMON:>6.3f} | {P25V0D_IMON:>8.3f} |\n"
        line += f"  | P17V0D | {P17V0D_VMON:>6.3f} | {P17V0D_IMON:>8.3f} |\n"
        line += f"  | N7V0D  | {N7V0D_VMON:>6.3f} | {N7V0D_IMON:>8.3f} |\n" 
        line += f"  | P15V0A | {P15V0A_VMON:>6.3f} | {P15V0A_IMON:>8.3f} |\n"
        line += f"  | N15V0A | {N15V0A_VMON:>6.3f} | {N15V0A_IMON:>8.3f} |\n"
        line += f"  | P5V0D  | {P5V0D_VMON:>6.3f} | {P5V0D_IMON:>8.3f} |\n" 
        line += f"  | P5V0A  | {P5V0A_VMON:>6.3f} | {P5V0A_IMON:>8.3f} |\n" 
        line += f"  | N5V0A  | {N5V0A_VMON:>6.3f} | {N5V0A_IMON:>8.3f} |\n" 
        line += f"  | P3V3D  | {P3V3D_VMON:>6.3f} | {P3V3D_IMON:>8.3f} |\n" 
        line += f"  | PVLB   | {PVLB_VMON:>6.3f} | {PVLB_IMON:>8.3f} |\n"  
        line += f"  | P5V0R  | {P5V0R_VMON:>6.3f} | {P5V0R_IMON:>8.3f} |\n" 
        line += f"  | GND    | {GND_VMON:>6.3f} |          |\n"
        line +=  "  +--------+--------+----------+\n"

        self.parent.output_te.append(line)
