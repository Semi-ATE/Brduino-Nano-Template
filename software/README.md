# Commands

The description of the commands is done from the point of view of a PC (over USB) or from the point of view of the SCT8-Board.


## GET_MEASUREMENT (CMD=0x03, SCMD=0x01)

Description: get all measurements (gains & offsets already applied)

Input: None

Output:

| Index | Name        | Type    | BootStage | Description                |             
|:-----:|:------------|:--------|:----------|:---------------------------|
|0      | P12V0D_VMON | float32 | 0         | Voltage on the P12V0D rail |
|1      | P12V0D_IMON | float32 | 0         | Current in the P12V0D rail |   
|2      | RAIL1_VMON  | float32 | 1         | Voltage on the RAIL1 rail  |
|3      | RAIL1_IMON  | float32 | 1         | Current in the RAIL1 rail  |
|4      | RAIL2_VMON  | float32 | 1         | Voltage on the RAIL2 rail  |
|5      | RAIL2_IMON  | float32 | 1         | Current in the RAIL2 rail  |
|6      | P25V0D_VMON | float32 | 1         | Voltage on the P25V0D rail |
|7      | P25V0D_IMON | float32 | 1         | Current in the P25V0D rail |
|8      | P17V0D_VMON | float32 | 1         | Voltage on the P17V0D rail |
|9      | P17V0D_IMON | float32 | 1         | Current in the P17V0D rail |
|10     | N7V0D_VMON  | float32 | 1         | Voltage on the N7V0D rail  |
|11     | N7V0D_IMON  | float32 | 1         | Current in the N7V0D rail  |
|12     | P15V0A_VMON | float32 | 1         | Voltage on the P15V0A rail |
|13     | P15V0A_IMON | float32 | 1         | Current in the P15V0A rail |
|14     | N15V0A_VMON | float32 | 1         | Voltage on the N15V0A rail |
|15     | N15V0A_IMON | float32 | 1         | Current in the N15V0A rail |
|16     | P5V0D_VMON  | float32 | 1         | Voltage on the P5V0D rail  |
|17     | P5V0D_IMON  | float32 | 1         | Current in the P5V0D rail  |
|18     | P5V0A_VMON  | float32 | 1         | Voltage on the P5V0A rail  |
|19     | P5V0A_IMON  | float32 | 1         | Current in the P5V0A rail  |
|20     | N5V0A_VMON  | float32 | 1         | Voltage on the N5V0A rail  |
|21     | N5V0A_IMON  | float32 | 1         | Current in the N5V0A rail  |
|22     | P3V3D_VMON  | float32 | 1         | Voltage on the P3V3D rail  |
|23     | P3V3D_IMON  | float32 | 1         | Current in the P3V3D rail  |
|24     | PVLB_VMON   | float32 | 2         | Voltage on the PVLB rail   |
|25     | PVLB_IMON   | float32 | 2         | Current in the PVLB rail   |
|26     | P5V0R_VMON  | float32 | 2         | Voltage on the P5V0R rail  |
|27     | P5V0R_IMON  | float32 | 2         | Current in the P5V0R rail  |
|28     | GND_VMON    | float32 | X         | Voltage on the GND         |


Note: rails that are not on will return 0.0

## GET_BOOT_STAGE (CMD=0x03, SCMD=0x02)

Description: Returns the current boot stage.

Input: None

Output: The current boot stage, it is an integer being 0,1 or 2.

## SET_BOOT_STAGE	(CMD=0x03, SCMD=0x03)

Description: With this we can change the boot stage.

Input: The new boot stage, an integer being 0, 1 or 2.

Output: 

| Index | Name        | Type  | Description |
|:-----:|:------------|:------|:------------|
|0      | BOOT_STAGE  | uint8 | The resulting boot stage |
|1      | N5V0A_VMON  | uint8 | The voltage* on N5V0A |
|2      | RAIL1_VMON  | uint8 | The voltage* on RAIL1 |
|3      | P3V3D_VMON  | uint8 | The voltage* on P3V3D |
|4      | P5V0D_VMON  | uint8 | The voltage* on P5V0D |
|5      | RAIL0_VMON  | uint8 | The voltage* on RAIL0 |
|6      | P5V0R_VMON  | uint8 | The voltage* on P5V0R |
|7      | PVLB_VMON   | uint8 | The voltage* on PVLB |
|8      | P12V0D_VMON | uint8 | The voltage* on P12V0D |
|9      | P5V0A_VMON  | uint8 | The voltage* on P5V0A |
|10     | RAIL2_VMON  | uint8 | The voltage* on RAIL2 |
|11     | N15V0A_VMON | uint8 | The voltage* on N15V0A |
|12     | P15V0A_VMON | uint8 | The voltage* on P15V0A |
|13     | P25V0D_VMON | uint8 | The voltage* on P25V0D |
|14     | P17V0D_VMON | uint8 | The voltage* on P17V0D |
|15     | N7V0D_VMON  | uint8 | The voltage* on N7V0D |
|16     | GND_VMON    | uint8 | The voltage* on GND |

* corrected by applying the gain and offset for each monitor. The unit is Volt.

If we go from BootStage0 ➜ BootStage1, and something is wrong (eg: fuse is blown), then the resulting BOOT_STAGE will be still 0, 
and the measured voltages are returned, this way we can (with the help of other commands) determine what went wrong. 

If on the other hand everythin is ok, the BOOT_STAGE will be 1, and a voltage for each rail is returned.

## GET_BOOT_SEQUENCE	(CMD=0x03, SCMD=0x04)

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

## SET_BOOT_SEQUENCE	(CMD=0x03, SCMD=0x05)

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

## GET_RAIL_STATUS (CMD=0x03, SCMD=0x06)

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

## SET_RAIL_STATUS (CMD=0x03, SCMD=0x07)

Description: set the desired status (on/off) of all rails

Input: the desired status of the rails

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


Output: the new (current) status of the rails 

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


## GET_VOLT_GAINS	(CMD=0x03, SCMD=0x08)

Description: get a list of the voltage gains for all rails.

Input: None

Output:

| Index | Name         | Type    | Description             |             
|:-----:|:-------------|:--------|:------------------------|             
|0      | P12V0D_VGAIN | float32 | Voltage gain for P12V0D |
|1      | RAIL1_VGAIN  | float32 | Voltage gain for RAIL1  |   
|2      | RAIL2_VGAIN  | float32 | Voltage gain for RAIL2  |
|3      | P25V0D_VGAIN | float32 | Voltage gain for P25V0D |
|4      | P17V0D_VGAIN | float32 | Voltage gain for P17V0D |
|5      | N7V0D_VGAIN  | float32 | Voltage gain for N7V0D  |
|6      | P15V0A_VGAIN | float32 | Voltage gain for P15V0A |
|7      | N15V0A_VGAIN | float32 | Voltage gain for N15V0A |
|8      | P5V0D_VGAIN  | float32 | Voltage gain for P5V0D  |
|9      | P5V0A_VGAIN  | float32 | Voltage gain for P5V0A  |
|10     | N5V0A_VGAIN  | float32 | Voltage gain for N5V0A  |
|11     | P3V3D_VGAIN  | float32 | Voltage gain for P3V3D  |
|12     | PVLB_VGAIN   | float32 | Voltage gain for PVLB   |
|13     | P5V0R_VGAIN  | float32 | Voltage gain for P5V0R  |
|14     | GND_VGAIN    | float32 | Voltage gain for GND    |  


## SET_VOLT_GAINS	(CMD=0x03, SCMD=0x09)

Description: set the voltage gains for all rails.

Input: The desired voltage gains for the rails

| Index | Name         | Type    | Description             |             
|:-----:|:-------------|:--------|:------------------------|             
|0      | P12V0D_VGAIN | float32 | Voltage gain for P12V0D |
|1      | RAIL1_VGAIN  | float32 | Voltage gain for RAIL1  |   
|2      | RAIL2_VGAIN  | float32 | Voltage gain for RAIL2  |
|3      | P25V0D_VGAIN | float32 | Voltage gain for P25V0D |
|4      | P17V0D_VGAIN | float32 | Voltage gain for P17V0D |
|5      | N7V0D_VGAIN  | float32 | Voltage gain for N7V0D  |
|6      | P15V0A_VGAIN | float32 | Voltage gain for P15V0A |
|7      | N15V0A_VGAIN | float32 | Voltage gain for N15V0A |
|8      | P5V0D_VGAIN  | float32 | Voltage gain for P5V0D  |
|9      | P5V0A_VGAIN  | float32 | Voltage gain for P5V0A  |
|10     | N5V0A_VGAIN  | float32 | Voltage gain for N5V0A  |
|11     | P3V3D_VGAIN  | float32 | Voltage gain for P3V3D  |
|12     | PVLB_VGAIN   | float32 | Voltage gain for PVLB   |
|13     | P5V0R_VGAIN  | float32 | Voltage gain for P5V0R  |
|14     | GND_VGAIN    | float32 | Voltage gain for GND    |  

Output: The new list of voltage gains.

| Index | Name         | Type    | Description             |             
|:-----:|:-------------|:--------|:------------------------|             
|0      | P12V0D_VGAIN | float32 | Voltage gain for P12V0D |
|1      | RAIL1_VGAIN  | float32 | Voltage gain for RAIL1  |   
|2      | RAIL2_VGAIN  | float32 | Voltage gain for RAIL2  |
|3      | P25V0D_VGAIN | float32 | Voltage gain for P25V0D |
|4      | P17V0D_VGAIN | float32 | Voltage gain for P17V0D |
|5      | N7V0D_VGAIN  | float32 | Voltage gain for N7V0D  |
|6      | P15V0A_VGAIN | float32 | Voltage gain for P15V0A |
|7      | N15V0A_VGAIN | float32 | Voltage gain for N15V0A |
|8      | P5V0D_VGAIN  | float32 | Voltage gain for P5V0D  |
|9      | P5V0A_VGAIN  | float32 | Voltage gain for P5V0A  |
|10     | N5V0A_VGAIN  | float32 | Voltage gain for N5V0A  |
|11     | P3V3D_VGAIN  | float32 | Voltage gain for P3V3D  |
|12     | PVLB_VGAIN   | float32 | Voltage gain for PVLB   |
|13     | P5V0R_VGAIN  | float32 | Voltage gain for P5V0R  |
|14     | GND_VGAIN    | float32 | Voltage gain for GND    |  

## GET_CURR_GAINS	(CMD=0x03, SCMD=0x0A)

Description: get a list of the current gains for all rails.

Input: None

Output:

| Index | Name         | Type    | Description             |             
|:-----:|:-------------|:--------|:------------------------|             
|0      | P12VoD_IGAIN | float32 | Current gain for P12V0D |
|1      | RAIL1_IGAIN  | float32 | Current gain for RAIL1  |   
|2      | RAIL2_IGAIN  | float32 | Current gain for RAIL2  |
|3      | P25V0D_IGAIN | float32 | Current gain for P25V0D |
|4      | P17V0D_IGAIN | float32 | Current gain for P17V0D |
|5      | N7V0D_IGAIN  | float32 | Current gain for N7V0D  |
|6      | P15V0A_IGAIN | float32 | Current gain for P15V0A |
|7      | N15V0A_IGAIN | float32 | Current gain for N15V0A |
|8      | P5V0D_IGAIN  | float32 | Current gain for P5V0D  |
|9      | P5V0A_IGAIN  | float32 | Current gain for P5V0A  |
|10     | N5V0A_IGAIN  | float32 | Current gain for N5V0A  |
|11     | P3V3D_IGAIN  | float32 | Current gain for P3V3D  |
|12     | PVLB_IGAIN   | float32 | Current gain for PVLB   |
|13     | P5V0R_IGAIN  | float32 | Current gain for P5V0R  |

## SET_CURR_GAINS	(CMD=0x03, SCMD=0x0B)

Description: set the current gains for all rails.

Input: The desired voltage gains for the rails

| Index | Name         | Type    | Description             |             
|:-----:|:-------------|:--------|:------------------------|             
|0      | P12VoD_IGAIN | float32 | Current gain for P12V0D |
|1      | RAIL1_IGAIN  | float32 | Current gain for RAIL1  |   
|2      | RAIL2_IGAIN  | float32 | Current gain for RAIL2  |
|3      | P25V0D_IGAIN | float32 | Current gain for P25V0D |
|4      | P17V0D_IGAIN | float32 | Current gain for P17V0D |
|5      | N7V0D_IGAIN  | float32 | Current gain for N7V0D  |
|6      | P15V0A_IGAIN | float32 | Current gain for P15V0A |
|7      | N15V0A_IGAIN | float32 | Current gain for N15V0A |
|8      | P5V0D_IGAIN  | float32 | Current gain for P5V0D  |
|9      | P5V0A_IGAIN  | float32 | Current gain for P5V0A  |
|10     | N5V0A_IGAIN  | float32 | Current gain for N5V0A  |
|11     | P3V3D_IGAIN  | float32 | Current gain for P3V3D  |
|12     | PVLB_IGAIN   | float32 | Current gain for PVLB   |
|13     | P5V0R_IGAIN  | float32 | Current gain for P5V0R  |

Output: The new list of current gains.

| Index | Name         | Type    | Description             |             
|:-----:|:-------------|:--------|:------------------------|             
|0      | P12VoD_IGAIN | float32 | Current gain for P12V0D |
|1      | RAIL1_IGAIN  | float32 | Current gain for RAIL1  |   
|2      | RAIL2_IGAIN  | float32 | Current gain for RAIL2  |
|3      | P25V0D_IGAIN | float32 | Current gain for P25V0D |
|4      | P17V0D_IGAIN | float32 | Current gain for P17V0D |
|5      | N7V0D_IGAIN  | float32 | Current gain for N7V0D  |
|6      | P15V0A_IGAIN | float32 | Current gain for P15V0A |
|7      | N15V0A_IGAIN | float32 | Current gain for N15V0A |
|8      | P5V0D_IGAIN  | float32 | Current gain for P5V0D  |
|9      | P5V0A_IGAIN  | float32 | Current gain for P5V0A  |
|10     | N5V0A_IGAIN  | float32 | Current gain for N5V0A  |
|11     | P3V3D_IGAIN  | float32 | Current gain for P3V3D  |
|12     | PVLB_IGAIN   | float32 | Current gain for PVLB   |
|13     | P5V0R_IGAIN  | float32 | Current gain for P5V0R  |

## GET_VOLT_OFFSETS (CMD=0x03, SCMD=0x0C)

Description: get a list of the voltage offsets for all rails.

Input: None

Output:

| Index | Name           | Type    | Description               |             
|:-----:|:---------------|:--------|:--------------------------|             
|0      | P12V0D_VOFFSET | float32 | Voltage offset for P12V0D |
|1      | RAIL1_VOFFSET  | float32 | Voltage offset for RAIL1  |   
|2      | RAIL2_VOFFSET  | float32 | Voltage offset for RAIL2  |
|3      | P25V0D_VOFFSET | float32 | Voltage offset for P25V0D |
|4      | P17V0D_VOFFSET | float32 | Voltage offset for P17V0D |
|5      | N7V0D_VOFFSET  | float32 | Voltage offset for N7V0D  |
|6      | P15V0A_VOFFSET | float32 | Voltage offset for P15V0A |
|7      | N15V0A_VOFFSET | float32 | Voltage offset for N15V0A |
|8      | P5V0D_VOFFSET  | float32 | Voltage offset for P5V0D  |
|9      | P5V0A_VOFFSET  | float32 | Voltage offset for P5V0A  |
|10     | N5V0A_VOFFSET  | float32 | Voltage offset for N5V0A  |
|11     | P3V3D_VOFFSET  | float32 | Voltage offset for P3V3D  |
|12     | PVLB_VOFFSET   | float32 | Voltage offset for PVLB   |
|13     | P5V0R_VOFFSET  | float32 | Voltage offset for P5V0R  |
|14     | GND_VOFFSET    | float32 | Voltage offset for GND    |  

## SET_VOLT_OFFSETS (CMD=0x03, SCMD=0x0D)

Description: set the voltage offsets for all rails.

Input: The desired voltage gains for the rails

| Index | Name           | Type    | Description               |             
|:-----:|:---------------|:--------|:--------------------------|             
|0      | P12V0D_VOFFSET | float32 | Voltage offset for P12V0D |
|1      | RAIL1_VOFFSET  | float32 | Voltage offset for RAIL1  |   
|2      | RAIL2_VOFFSET  | float32 | Voltage offset for RAIL2  |
|3      | P25V0D_VOFFSET | float32 | Voltage offset for P25V0D |
|4      | P17V0D_VOFFSET | float32 | Voltage offset for P17V0D |
|5      | N7V0D_VOFFSET  | float32 | Voltage offset for N7V0D  |
|6      | P15V0A_VOFFSET | float32 | Voltage offset for P15V0A |
|7      | N15V0A_VOFFSET | float32 | Voltage offset for N15V0A |
|8      | P5V0D_VOFFSET  | float32 | Voltage offset for P5V0D  |
|9      | P5V0A_VOFFSET  | float32 | Voltage offset for P5V0A  |
|10     | N5V0A_VOFFSET  | float32 | Voltage offset for N5V0A  |
|11     | P3V3D_VOFFSET  | float32 | Voltage offset for P3V3D  |
|12     | PVLB_VOFFSET   | float32 | Voltage offset for PVLB   |
|13     | P5V0R_VOFFSET  | float32 | Voltage offset for P5V0R  |
|14     | GND_VOFFSET    | float32 | Voltage offset for GND    |  

Output: The new list of voltage gains.

| Index | Name           | Type    | Description               |             
|:-----:|:---------------|:--------|:--------------------------|             
|0      | P12V0D_VOFFSET | float32 | Voltage offset for P12V0D |
|1      | RAIL1_VOFFSET  | float32 | Voltage offset for RAIL1  |   
|2      | RAIL2_VOFFSET  | float32 | Voltage offset for RAIL2  |
|3      | P25V0D_VOFFSET | float32 | Voltage offset for P25V0D |
|4      | P17V0D_VOFFSET | float32 | Voltage offset for P17V0D |
|5      | N7V0D_VOFFSET  | float32 | Voltage offset for N7V0D  |
|6      | P15V0A_VOFFSET | float32 | Voltage offset for P15V0A |
|7      | N15V0A_VOFFSET | float32 | Voltage offset for N15V0A |
|8      | P5V0D_VOFFSET  | float32 | Voltage offset for P5V0D  |
|9      | P5V0A_VOFFSET  | float32 | Voltage offset for P5V0A  |
|10     | N5V0A_VOFFSET  | float32 | Voltage offset for N5V0A  |
|11     | P3V3D_VOFFSET  | float32 | Voltage offset for P3V3D  |
|12     | PVLB_VOFFSET   | float32 | Voltage offset for PVLB   |
|13     | P5V0R_VOFFSET  | float32 | Voltage offset for P5V0R  |
|14     | GND_VOFFSET    | float32 | Voltage offset for GND    |  

## GET_CURR_OFFSETS (CMD=0x03, SCMD=0x0E)

Description: get a list of the current offsets for all rails.

Input: None

Output:

| Index | Name           | Type    | Description               |             
|:-----:|:---------------|:--------|:--------------------------|             
|0      | P12V0D_IOFFSET | float32 | Current offset for P12V0D |
|1      | RAIL1_IOFFSET  | float32 | Current offset for RAIL1  |   
|2      | RAIL2_IOFFSET  | float32 | Current offset for RAIL2  |
|3      | P25V0D_IOFFSET | float32 | Current offset for P25V0D |
|4      | P17V0D_IOFFSET | float32 | Current offset for P17V0D |
|5      | N7V0D_IOFFSET  | float32 | Current offset for N7V0D  |
|6      | P15V0A_IOFFSET | float32 | Current offset for P15V0A |
|7      | N15V0A_IOFFSET | float32 | Current offset for N15V0A |
|8      | P5V0D_IOFFSET  | float32 | Current offset for P5V0D  |
|9      | P5V0A_IOFFSET  | float32 | Current offset for P5V0A  |
|10     | N5V0A_IOFFSET  | float32 | Current offset for N5V0A  |
|11     | P3V3D_IOFFSET  | float32 | Current offset for P3V3D  |
|12     | PVLB_IOFFSET   | float32 | Current offset for PVLB   |
|13     | P5V0R_IOFFSET  | float32 | Current offset for P5V0R  |

## SET_CURR_OFFSETS (CMD=0x03, SCMD=0x0F)

Description: set the current offsets for all rails.

Input: The desired current offsets for the rails

| Index | Name           | Type    | Description               |             
|:-----:|:---------------|:--------|:--------------------------|             
|0      | P12V0D_IOFFSET | float32 | Current offset for P12V0D |
|1      | RAIL1_IOFFSET  | float32 | Current offset for RAIL1  |   
|2      | RAIL2_IOFFSET  | float32 | Current offset for RAIL2  |
|3      | P25V0D_IOFFSET | float32 | Current offset for P25V0D |
|4      | P17V0D_IOFFSET | float32 | Current offset for P17V0D |
|5      | N7V0D_IOFFSET  | float32 | Current offset for N7V0D  |
|6      | P15V0A_IOFFSET | float32 | Current offset for P15V0A |
|7      | N15V0A_IOFFSET | float32 | Current offset for N15V0A |
|8      | P5V0D_IOFFSET  | float32 | Current offset for P5V0D  |
|9      | P5V0A_IOFFSET  | float32 | Current offset for P5V0A  |
|10     | N5V0A_IOFFSET  | float32 | Current offset for N5V0A  |
|11     | P3V3D_IOFFSET  | float32 | Current offset for P3V3D  |
|12     | PVLB_IOFFSET   | float32 | Current offset for PVLB   |
|13     | P5V0R_IOFFSET  | float32 | Current offset for P5V0R  |

Output: The new list of current offsets.

| Index | Name           | Type    | Description               |             
|:-----:|:---------------|:--------|:--------------------------|             
|0      | P12V0D_IOFFSET | float32 | Current offset for P12V0D |
|1      | RAIL1_IOFFSET  | float32 | Current offset for RAIL1  |   
|2      | RAIL2_IOFFSET  | float32 | Current offset for RAIL2  |
|3      | P25V0D_IOFFSET | float32 | Current offset for P25V0D |
|4      | P17V0D_IOFFSET | float32 | Current offset for P17V0D |
|5      | N7V0D_IOFFSET  | float32 | Current offset for N7V0D  |
|6      | P15V0A_IOFFSET | float32 | Current offset for P15V0A |
|7      | N15V0A_IOFFSET | float32 | Current offset for N15V0A |
|8      | P5V0D_IOFFSET  | float32 | Current offset for P5V0D  |
|9      | P5V0A_IOFFSET  | float32 | Current offset for P5V0A  |
|10     | N5V0A_IOFFSET  | float32 | Current offset for N5V0A  |
|11     | P3V3D_IOFFSET  | float32 | Current offset for P3V3D  |
|12     | PVLB_IOFFSET   | float32 | Current offset for PVLB   |
|13     | P5V0R_IOFFSET  | float32 | Current offset for P5V0R  |

## GET_VOLT_WINDOWS (CMD=0x03, SCMD=0x10)

Description: A window is a set of upper and lower limits that determine if a rail is considered OK or not. A measurement is considered OK if (after applying the appropriate gain and offset) it is in the interval LLIM <= MEAS <= HLIM.

Input: None

Output:

| Index | Name         | Type    | Description               |             
|:-----:|:-------------|:--------|:--------------------------|             
|0      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
|1      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
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

## SET_VOLT_WINDOWS (CMD=0x03, SCMD=0x11)

Description: set the desired voltage windows

Input: The desired voltage windows

| Index | Name         | Type    | Description               |             
|:-----:|:-------------|:--------|:--------------------------|             
|0      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
|1      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
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

Output: the voltage windows that will be applied from now on (should be same as input)

| Index | Name         | Type    | Description               |             
|:-----:|:-------------|:--------|:--------------------------|             
|0      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
|1      | P12V0D_VLLIM | float32 | P12V0D Low Voltage Limit  |
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

## GET_CURR_WINDOWS (CMD=0x03, SCMD=0x12)

Description: A window is a set of upper and lower limits that determine if a rail is considered OK or not. 
A measurement is considered OK if (after applying the appropriate gain and offset) it is in the interval LLIM <= MEAS <= HLIM.

Input: None

Output:

| Index | Name         | Type    | Description               |             
|:-----:|:-------------|:--------|:--------------------------|             
|0      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
|1      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
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

## SET_CURR_WINDOWS (CMD=0x03, SCMD=0x13)

Description: set the current windows for all rails

Input: The desired current windows

| Index | Name         | Type    | Description               |             
|:-----:|:-------------|:--------|:--------------------------|             
|0      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
|1      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
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
|1      | P12V0D_ILLIM | float32 | P12V0D Low Current Limit  |
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

## NOTIFICATION (CMD=0x03, SCMD=0x14)

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

# Packages

## send (from PC -> controller)

    A0 DeciveID_LO DeviceID_HI DeviceClass_LO DeviceClass_HI CMD SCMD `payload` Checksum_LO Checksum_HI 05


## receive (from controller --> PC)

    A0 DeviceID_LO DeviceID_HI CMD ACK SCMD `payload` Checksum_LO Checksum_HI 05
    
    
