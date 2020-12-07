/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    board.h
 * @brief   Board initialization header file.
 */

/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/

#ifndef _BOARD_H_
#define _BOARD_H_

/**
 * @brief	The board name 
 */
#define BOARD_NAME "BRDUINO_Nano"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "clock_config.h"

#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"
#include "fsl_ftm.h"
#include "fsl_uart.h"
#include "fsl_adc16.h"
#include "fsl_dac.h"
#include "fsl_vref.h"

#include "common.h"

#define CONSOLE_UART             	UART1
#define CONSOLE_UART_BAUDRATE    	115200

#define  UART0_INT_PRIORITY         11
#define  UART1_INT_PRIORITY         11
#define  UART2_INT_PRIORITY         11
#define  UART3_INT_PRIORITY         11
#define  UART4_INT_PRIORITY         8
#define  UART5_INT_PRIORITY         12

#define  BOARD_N_GPIO            	14

#define  PWM_FREQUENCY_FTM0_HZ      10000
#define  PWM_FREQUENCY_FTM1_HZ      100000
#define  TIMER0_FREQUENCY_HZ        10
#define  TIMER1_FREQUENCY_HZ        1000
#define  TIMER2_FREQUENCY_HZ        1000

#define PWM_DEADTIME						50				// Deadtime in ns

#define FTM0_INT_PRIORITY           14
#define FTM1_INT_PRIORITY           14
#define FTM2_INT_PRIORITY           14

#define BOARD_PIT0_IRQ_ENA
#define BOARD_PIT1_IRQ_ENA

#define PIT0_INT_PRIORITY           4
#define PIT1_INT_PRIORITY           4
#define PIT2_INT_PRIORITY           4

#define RTC_INT_PRIORITY            5

#define PORTA_INT_PRIORITY          7
#define PORTB_INT_PRIORITY          7
#define PORTC_INT_PRIORITY          7
#define PORTD_INT_PRIORITY          7
#define PORTE_INT_PRIORITY          7

#define  UART0_INT_PRIORITY         11
#define  UART1_INT_PRIORITY         11
#define  UART2_INT_PRIORITY         11
#define  UART3_INT_PRIORITY         11
#define  UART4_INT_PRIORITY         8
#define  UART5_INT_PRIORITY         12

#define BOARD_ADC_NumberOfChannels	6
#define BOARD_ADC_ChannelGroup		0
#define ADC0_N_CHANNEL	            6
#define ADC1_N_CHANNEL	            0

#define ADC_CH0			            0x00     // ADC0-PTB0 (ADC0_SE8)
#define ADC_CH1			            0x13     // ADC0-PTB1 (ADC0_SE9)
#define ADC_CH2			            0x08     // ADC0-PTB2 (ADC0_SE12)
#define ADC_CH3			            0x0C     // ADC0-PTB3 (ADC0_SE13)
#define ADC_CH4			            0x0D     // ADC0-PTC0 (ADC0_SE15)
#define ADC_CH5			            0x0D     // ADC0-PTD1 (ADC0_SE5b)

#define ADC_CH0_ADC		            ADC0
#define ADC_CH1_ADC		            ADC0
#define ADC_CH2_ADC		            ADC0
#define ADC_CH3_ADC		            ADC0
#define ADC_CH4_ADC		            ADC0
#define ADC_CH5_ADC		            ADC0

#define N_SUPPLY_RAILS					15

#define RAIL1_VMON  						0       // float32  Voltage on RAIL1
#define RAIL1_IMON  						1       // float32  Current in RAIL1
#define RAIL2_VMON  						2       // float32  Voltage on RAIL2
#define RAIL2_IMON  						3       // float32  Current in RAIL2
#define P25V0D_VMON 						4       // float32  Voltage on P25V0D
#define P25V0D_IMON 						5       // float32  Current in P25V0D
#define P17V0D_VMON 						6       // float32  Voltage on P17V0D
#define P17V0D_IMON 						7       // float32  Current in P17V0D
#define N7V0D_VMON  						8       // float32  Voltage on N7V0D
#define N7V0D_IMON  						9       // float32  Current in N7V0D
#define P15V0A_VMON 						10      // float32  Voltage on P15V0A
#define P15V0A_IMON 						11      // float32  Current in P15V0A
#define N15V0A_VMON 						12      // float32  Voltage on N15V0A
#define N15V0A_IMON 						13      // float32  Current in N15V0A
#define P5V0D_VMON  						14      // float32  Voltage on P5V0D
#define P5V0D_IMON  						15      // float32  Current in P5V0D
#define P5V0A_VMON  						16      // float32  Voltage on P5V0A
#define P5V0A_IMON  						17      // float32  Current in P5V0A
#define N5V0A_VMON  						18      // float32  Voltage on N5V0A
#define N5V0A_IMON  						19      // float32  Current in N5V0A
#define P3V3D_VMON  						20      // float32  Voltage on P3V3D
#define P3V3D_IMON  						21      // float32  Current in P3V3D
#define PVLB_VMON   						22      // float32  Voltage on PVLB
#define PVLB_IMON   						23      // float32  Current in PVLB
#define P5V0R_VMON  						24      // float32  Voltage on P5V0R
#define P5V0R_IMON  						25      // float32  Current in P5V0R
#define GND_VMON    						26      // float32  Voltage on GND

typedef struct __attribute__((packed)) {
	uint16_t	turn_on_delay;
	uint8_t	on_off;
	uint8_t	sequence_pos;
	float		gain_volt;
	float		offset_volt;
	float		gain_current;
	float		offset_current;
	float		low_limit_volt;
	float		high_limi_volt;
	float		low_limit_curr;
	float		high_limit_curr;
	float		actual_voltage;
	float		actual_current;
} SupplyRail_t;

typedef struct {
	uint16_t *value_ptr;
	uint8_t adc_channel;
	uint8_t adc_mux;
} ADC_Conversion_Ptr_t;

typedef struct {
	adc16_channel_config_t ChannelConfig;		// Channel Configuration
	ADC_Type *ADC;				// Device ADC
	float voltage;				// voltage V
	float integer_fac;			// Integer Factor
	float gain;					// gain;
	float offset;				// offset
} adc16_board_channel_t;

extern TaskHandle_t TaskComm;

typedef enum {
	ePin_IF_RS484_DE_nRE = 1,	// PTB19
	ePin_GPIO1 = 2,				// PTB16
	ePin_GPIO2 = 3,				// PTC3
	ePin_GPIO3 = 4,				// PTC2
	ePin_GPIO4 = 5,				// PTC4
	ePin_GPIO5 = 6,				// PTA12
	ePin_GPIO6 = 7,				// PTA13
	ePin_GPIO7 = 8,				// PTB17
	ePin_GPIO8 = 9,				// PTD4
	ePin_GPIO9 = 10,			// PTD6
	ePin_GPIO10 = 11,			// PTD7
	ePin_GPIO11 = 12,			// PTD5
	ePin_GPIO12 = 13			// PTB18
} eGPIO_t;

typedef struct {
	PORT_Type *Base;
	GPIO_Type *GPIO;
	uint8_t Offset;
	uint8_t InitialState;
	gpio_pin_direction_t Direction;
	port_pin_config_t Config;
} strGPIOattrib_t;

typedef struct {
	PORT_Type *PORT;
	GPIO_Type *GPIO;
	uint8_t Offset;
} GPIO_IO_t;

/**
 * @brief 	Initialize board specific settings.
 */
void BOARD_InitDebugConsole(void);

void BOARD_SetOwnAddress(uint16_t address);
uint16_t BOARD_GetOwnAddress(void);
bool BOARD_set_DAC(DAC_Type *dac, uint16_t value);
bool BOARD_get_ADC(uint8_t channel, uint16_t *value);
bool BOARD_get_ADC_float(uint8_t channel, float *value);
bool BOARD_InitFTM0(void);
bool BOARD_InitFTM1(void);
bool BOARD_InitFTM2(void);
bool BOARD_InitPIT(void);
void BOARD_InitVREF(void);
void BOARD_Init(void);
bool BOARD_SetGPIOpin(eGPIO_t pin,bool value);
bool BOARD_GetGPIOpin(eGPIO_t pin);
uint64_t BOARD_GetJiffyCounter(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */

