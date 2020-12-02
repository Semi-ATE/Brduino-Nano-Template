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
 * @file    board.c
 * @brief   Board initialization file.
 */
 
/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/

#include <stdint.h>
#include "uart.h"
#include "board.h"
#include "crc.h"

static const uint32_t		PIT_Period0 = 1U;	   	// Pit-timeout = 1ms
static const uint32_t		PIT_Period1 = 10U;		// Pit-timeout = 10ms

static uint16_t		      	ADC_conversion_value[BOARD_ADC_NumberOfChannels];
static float		      	ADC_conversion_val_F[BOARD_ADC_NumberOfChannels];

static volatile int		   	gADC0channel_ctr = 0;

static volatile uint64_t	JiffyCntr = 0;

static uint16_t            	DeviceOwnAddress = 0;

int							gCnt = 0;

traceString 				adc_channel;

static volatile ADC_Conversion_Ptr_t 	ADC_Conversion_ADC0_Ptr[ADC0_N_CHANNEL] =
{
	{
		.value_ptr = &(ADC_conversion_value[0]),
		.adc_mux = 0,
		.adc_channel = ADC_CH0
	},
	{
		.value_ptr = &(ADC_conversion_value[1]),
		.adc_mux = 0,
		.adc_channel = ADC_CH1
	},
	{
		.value_ptr = &(ADC_conversion_value[2]),
		.adc_mux = 0,
		.adc_channel = ADC_CH2
	},
	{
		.value_ptr = &(ADC_conversion_value[3]),
		.adc_mux = 0,
		.adc_channel = ADC_CH3
	},
	{
		.value_ptr = &(ADC_conversion_value[4]),
		.adc_mux = 0,
		.adc_channel = ADC_CH4
	},
	{
		.value_ptr = &(ADC_conversion_value[5]),
		.adc_mux = 0,
		.adc_channel = ADC_CH5
	}
};

static adc16_board_channel_t		adc16BoardChannel[BOARD_ADC_NumberOfChannels] =
{
	{
		.ADC = ADC_CH0_ADC,			// ADC0-DP0 = OUT-LLC
		.ChannelConfig =
		{
				.channelNumber = ADC_CH0,
				.enableDifferentialConversion = false,
				.enableInterruptOnConversionCompleted = true
		},
		.voltage = 1.2,
		.integer_fac = 1,				// Unit is V
		.gain = 0.09982144,			// Unit is V
		.offset = 0
	},
	{
		.ADC = ADC_CH1_ADC,			// ADC0-DM0 = V-VIS
		.ChannelConfig =
		{
				.channelNumber = ADC_CH1,
				.enableDifferentialConversion = false,
				.enableInterruptOnConversionCompleted = true
		},
		.voltage = 1.2,
		.integer_fac = 1000.0,		// Unit is mV
		.gain = 0.00016846,			// Unit is V
		.offset = 0
	},
	{
		.ADC = ADC_CH2_ADC,			// ADC0-PTB0 (ADC0_SE8) = IOUT-SH
		.ChannelConfig =
		{
				.channelNumber = ADC_CH2,
				.enableDifferentialConversion = false,
				.enableInterruptOnConversionCompleted = true
		},
		.voltage = 1.2,
		.integer_fac = 1E6,			// Unit is uA
		.gain = 0.00000183,			// Unit is A
		.offset = 0
	},
	{
		.ADC = ADC_CH3_ADC,			// ADC0-PTB2 (ADC0_SE12) = VIN-LLC
		.ChannelConfig =
		{
				.channelNumber = ADC_CH3,
				.enableDifferentialConversion = false,
				.enableInterruptOnConversionCompleted = true
		},
		.voltage = 1.2,
		.integer_fac = 1000.0,		// Unit is mV
		.gain = 0.00016846,			// Unit is V
		.offset = 0
	},
	{
		.ADC = ADC_CH4_ADC,			// ADC0-PTB3 (ADC0_SE13) = VIN
		.ChannelConfig =
		{
				.channelNumber = ADC_CH4,
				.enableDifferentialConversion = false,
				.enableInterruptOnConversionCompleted = true
		},
		.voltage = 1.2,
		.integer_fac = 1000.0,		// Unit is mV
		.gain = 0.00020142,			// Unit is V
		.offset = 0
	},
	{
		.ADC = ADC_CH5_ADC,			// ADC0-PTB3 (ADC0_SE13) = VIN
		.ChannelConfig =
		{
				.channelNumber = ADC_CH5,
				.enableDifferentialConversion = false,
				.enableInterruptOnConversionCompleted = true
		},
		.voltage = 1.2,
		.integer_fac = 1000.0,		// Unit is mV
		.gain = 0.00020142,			// Unit is V
		.offset = 0
	}
};

static const adc16_config_t				adc16ConfigStruct =
{
	.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt,
	.clockSource = kADC16_ClockSourceAlt0,
	.enableAsynchronousClock = false,
	.clockDivider = kADC16_ClockDivider8,
	.resolution = kADC16_ResolutionSE16Bit,
	.longSampleMode = kADC16_LongSampleCycle24,
	.enableHighSpeed = false,
	.enableLowPower = false,
	.enableContinuousConversion = false
};

const strGPIOattrib_t sGPIOconfig[BOARD_N_GPIO] = {
   // MCU-IN [0], PTB19
   {
      .Base = PORTB,
      .GPIO = GPIOB,
      .Offset = 19,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [1], PTB16
   {
      .Base = PORTB,
      .GPIO = GPIOB,
      .Offset = 16,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [2], PTC3
   {
      .Base = PORTC,
      .GPIO = GPIOC,
      .Offset = 3,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [3], PTD3
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 3,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [4], PTD2
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 2,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [5], PTC4
   {
      .Base = PORTC,
      .GPIO = GPIOC,
      .Offset = 4,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [6], PTA12
   {
      .Base = PORTA,
      .GPIO = GPIOA,
      .Offset = 12,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [7], PTA13
   {
      .Base = PORTA,
      .GPIO = GPIOA,
      .Offset = 13,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [8], PTB17
   {
      .Base = PORTB,
      .GPIO = GPIOB,
      .Offset = 17,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [9], PTD4
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 4,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [10], PTD6
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 6,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [11], PTD7
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 7,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [12], PTD5
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 5,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   },
   // MCU-IN [13], PTB18
   {
      .Base = PORTD,
      .GPIO = GPIOD,
      .Offset = 4,
      .Direction = kGPIO_DigitalInput,
      .InitialState = 0,
      .Config = {
      .driveStrength = kPORT_LowDriveStrength,
      .lockRegister = kPORT_UnlockRegister,
      .mux = kPORT_MuxAsGpio,
      .openDrainEnable = kPORT_OpenDrainDisable,
      .passiveFilterEnable = kPORT_PassiveFilterDisable,
      .pullSelect = kPORT_PullDisable,
       .slewRate = kPORT_FastSlewRate
      }
   }
};

static const pit_config_t	pitConfig =
{
	.enableRunInDebug = false
};

static const vref_config_t	VrefConfigStruct =
{
    .bufferMode = kVREF_ModeHighPowerBuffer
};

static void InitPin(const strGPIOattrib_t *config)
{
gpio_pin_config_t    cfg;

   cfg.pinDirection = config->Direction;
   cfg.outputLogic = config->InitialState;
   GPIO_PinInit(config->GPIO, config->Offset, &cfg);
}

static void BOARD_setPinAttributes(void)
{
int      n;

	n = sizeof(sGPIOconfig) /  sizeof(strGPIOattrib_t);
	for (int i = 0;i < n;i++)
	{
	   PORT_SetPinConfig(sGPIOconfig[i].Base, sGPIOconfig[i].Offset, &(sGPIOconfig[i].Config));
	   InitPin(&(sGPIOconfig[i]));
	}
	// UART 1 (RS232 1)
	PORT_SetPinMux(PORTE,0,kPORT_MuxAlt3);       // TX
	PORT_SetPinMux(PORTE,1,kPORT_MuxAlt3);       // RX
}

static void BOARD_setClockAttributes(void)
{
   // Turn on the ADC0 and ADC1 clocks as well as the PDB (ADC triggered by PDB)
   CLOCK_EnableClock(kCLOCK_Adc0);
   CLOCK_EnableClock(kCLOCK_Adc1);
   CLOCK_EnableClock(kCLOCK_Pdb0);
   // Turn on the VREF clocks
   CLOCK_EnableClock(kCLOCK_Vref0);
   // Turn on the DAC clocks
   CLOCK_EnableClock(kCLOCK_Dac0);
   // Turn on the PORT clocks
   CLOCK_EnableClock(kCLOCK_PortA);
   CLOCK_EnableClock(kCLOCK_PortB);
   CLOCK_EnableClock(kCLOCK_PortC);
   CLOCK_EnableClock(kCLOCK_PortD);
   CLOCK_EnableClock(kCLOCK_PortE);
   // Turn on the UART clocks
   CLOCK_EnableClock(kCLOCK_Uart1);
   // Turn on the I2C clocks
   CLOCK_EnableClock(kCLOCK_I2c0);
   // Turn on the SPI clocks
   CLOCK_EnableClock(kCLOCK_Spi0);
   CLOCK_EnableClock(kCLOCK_Spi1);
   // Turn on the CRC clocks
   CLOCK_EnableClock(kCLOCK_Crc0);
   CLOCK_EnableClock(kCLOCK_Pit0);
   // Turn on the FlexTimer clocks
   CLOCK_EnableClock(kCLOCK_Ftm0);
   CLOCK_EnableClock(kCLOCK_Ftm1);
   CLOCK_EnableClock(kCLOCK_Ftm2);
}

static void BOARD_UART_InitUart1(void)
{
UART_descriptor_t    *desc;

	desc = GetUARTdescriptorFromPtr(UART1);
	if (desc)
	{
		desc->baudrate = CONSOLE_UART_BAUDRATE;
		UART_InitIRQ(desc,desc->IRQ_enabled);
		UART_InitUart(desc);
	}
}

void ADC0_IRQHandler(void)
{
volatile uint32_t		status,value;

	status = ADC0->SC1[0];
	if ((status & ADC_SC1_COCO_MASK) != 0)
	{
		ADC_conversion_value[gADC0channel_ctr] = value = ADC0->R[0];
		vTracePrintF(adc_channel,"Gptr %d, ADCctr %d, Value %d",gCnt,gADC0channel_ctr,value);
		gADC0channel_ctr++;
		if (gADC0channel_ctr >= ADC0_N_CHANNEL)
			gADC0channel_ctr = 0;
		ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;
		ADC0->SC1[0] |= ADC_SC1_ADCH(ADC_Conversion_ADC0_Ptr[gADC0channel_ctr].adc_channel);
	}
	else
	{
		vTracePrintF(adc_channel,"Status = %u",status);
	}
	gCnt++;
}

static int BOARD_InitADC(void)
{
int      ret = 0;

	for (int i = 0;i < 5;i++)
	{
		ADC_conversion_value[i] = 0;
		ADC_conversion_val_F[i] = 0.0;
	}
	// update configuration
	ADC16_Init(ADC0,&adc16ConfigStruct);

	// do self calibration
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
	if (ADC16_DoAutoCalibration(ADC0) == kStatus_Success)
	{
		ret = 1;
	}
#endif
//	BOARD_ADC_SetHWaverage(32);
	// set channel mux mode
	ADC16_SetChannelMuxMode(ADC0,kADC16_ChannelMuxA);

	// update channel config
	for (int i = 0;i < BOARD_ADC_NumberOfChannels;i++)
	{
		ADC16_SetChannelConfig(adc16BoardChannel[i].ADC, BOARD_ADC_ChannelGroup,
                             &(adc16BoardChannel[i].ChannelConfig));
	}

	// Select PIT0 as external trigger;
	SIM->SOPT7 &= ~(SIM_SOPT7_ADC0TRGSEL_MASK | SIM_SOPT7_ADC1TRGSEL_MASK);
	SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN_MASK | SIM_SOPT7_ADC1ALTTRGEN_MASK |
      SIM_SOPT7_ADC0TRGSEL(4);
	ADC16_EnableHardwareTrigger(ADC0, true);
	EnableIRQ(ADC0_IRQn);

   return ret;
}

static void BOARD_InitDAC(void)
{
//   DAC0->C0 = DAC_C0_DACSWTRG_MASK | DAC_C0_DACRFS_MASK;
   DAC0->C0 = DAC_C0_DACSWTRG_MASK;
   DAC0->C1 = 0x00;
   DAC0->C2 = 0x00;
   DAC0->DAT[0].DATH = 0x0;
   DAC0->DAT[0].DATL = 0x0;
   DAC0->C0 |= DAC_C0_DACEN_MASK;
}

/*!
 ******************************************************************************
 *	Sets the DAC
 * \param[in]		dac      Pointer to DAC0 or DAC1
 * \param[in]		value    Value to write
 * \return        1 if success, 0 else
 ******************************************************************************
*/
bool BOARD_set_DAC(DAC_Type * dac,uint16_t value)
{
   dac->DAT[0].DATL = value & 0xFF;
   dac->DAT[0].DATH = value >> 8;
   return true;
}

/*!
 ******************************************************************************
 *	Gets the actual value (setting) from the DAC
 * \param[in]		dac      Pointer to DAC0 or DAC1
 * \return        actual DAC value in uA (this controls a current source)
 ******************************************************************************
*/
uint16_t BOARD_get_DAC(DAC_Type * dac)
{
uint32_t    value;

   value = (uint16_t)(dac->DAT[0].DATH & 0xFF) << 8;
   value += dac->DAT[0].DATL & 0xFF;
   return value;
}

/*!
 ******************************************************************************
 *	Gets the actual value of an ADC channel
 * \param[in]		channel 	Selected channel
 * \param[out]		value 	Actual value of the selected ADC channel
 * \return        true if success, false else
 ******************************************************************************
*/
bool BOARD_get_ADC(uint8_t channel,uint16_t *value)
{

	if (channel >= BOARD_ADC_NumberOfChannels)
		return false;
   *value =  (int)(ADC_conversion_value[channel] *
   		adc16BoardChannel[channel].gain *
			adc16BoardChannel[channel].integer_fac +
			adc16BoardChannel[channel].offset + 0.5);
   return true;
}

/*!
 ******************************************************************************
 *	Gets the actual value of an ADC channel as a float value
 * \param[in]		channel 	Selected channel
 * \param[out]		value 	Actual value of the selected ADC channel
 * \return        true if success, false else
 ******************************************************************************
*/
bool BOARD_get_ADC_float(uint8_t channel,float *value)
{

	if (channel >= BOARD_ADC_NumberOfChannels)
		return false;
   *value =  ADC_conversion_value[channel] *
   		adc16BoardChannel[channel].gain +
			adc16BoardChannel[channel].offset;
   return true;
}

static void BOARD_FTM0_enable_isr(void)
{
   NVIC_SetPriority(FTM0_IRQn,FTM0_INT_PRIORITY);
   NVIC_EnableIRQ(FTM0_IRQn);
   FTM_EnableInterrupts(FTM0,kFTM_TimeOverflowInterruptEnable);
}

static void BOARD_FTM1_enable_isr(void)
{
   NVIC_SetPriority(FTM1_IRQn,FTM1_INT_PRIORITY);
   NVIC_EnableIRQ(FTM1_IRQn);
   FTM_EnableInterrupts(FTM1,kFTM_TimeOverflowInterruptEnable);
}

static void BOARD_FTM2_enable_isr(void)
{
   NVIC_SetPriority(FTM2_IRQn,FTM2_INT_PRIORITY);
   NVIC_EnableIRQ(FTM2_IRQn);
   FTM_EnableInterrupts(FTM2,kFTM_TimeOverflowInterruptEnable);
}

bool BOARD_InitFTM0(void)
{
ftm_config_t 						ftmInfo;
ftm_chnl_pwm_signal_param_t 	ftmParam[2];

	FTM_GetDefaultConfig(&ftmInfo);
//   ftmInfo.pwmSyncMode = FTM_SYNC_SWSYNC_MASK;
   ftmInfo.bdmMode = kFTM_BdmMode_3;

   ftmParam[0].chnlNumber = kFTM_Chnl_2;
	ftmParam[0].level = kFTM_HighTrue;
	ftmParam[0].dutyCyclePercent = 0;
	ftmParam[0].firstEdgeDelayPercent = 0U;
   ftmParam[1].chnlNumber = kFTM_Chnl_7;
	ftmParam[1].level = kFTM_HighTrue;
	ftmParam[1].dutyCyclePercent = 0;
	ftmParam[1].firstEdgeDelayPercent = 0U;

	FTM_Init(FTM0, &ftmInfo);
   FTM_SetupPwm(FTM0,ftmParam,2U,kFTM_EdgeAlignedPwm,PWM_FREQUENCY_FTM0_HZ,CLOCK_GetFreq(kCLOCK_BusClk));

	FTM_StartTimer(FTM0, kFTM_SystemClock);

	FTM_UpdateChnlEdgeLevelSelect(FTM0,kFTM_Chnl_2,kFTM_LowTrue);
	FTM_UpdateChnlEdgeLevelSelect(FTM0,kFTM_Chnl_7,kFTM_LowTrue);
	return true;
}

bool BOARD_InitFTM1(void)
{
uint32_t								deadtime;
uint32_t								ftmClock;
uint32_t								mod,reg;

   deadtime = ((uint64_t)CLOCK_GetFreq(kCLOCK_BusClk) * PWM_DEADTIME) / 1000000000;
   FTM1->MODE = FTM_MODE_FTMEN_MASK | FTM_MODE_WPDIS_MASK;
   FTM1->SC = FTM_SC_PS(kFTM_Prescale_Divide_1);
   FTM1->CONF = FTM_CONF_BDMMODE(kFTM_BdmMode_3);
   FTM1->DEADTIME = FTM_DEADTIME_DTPS(kFTM_Deadtime_Prescale_1) | deadtime;
   ftmClock = (CLOCK_GetFreq(kCLOCK_BusClk) / (1UL << (FTM1->SC & FTM_SC_PS_MASK)));
   FTM1->SC &= ~FTM_SC_CPWMS_MASK;
   mod = (ftmClock / PWM_FREQUENCY_FTM1_HZ) - 1U;
   if (mod > 65535U)
   {
       return 0;
   }
   FTM1->MOD = mod;
   reg = FTM1->CONTROLS[0].CnSC;
   reg &= ~(FTM_CnSC_MSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK);
   reg |= (uint32_t)kFTM_HighTrue << FTM_CnSC_ELSA_SHIFT;
   FTM1->CONTROLS[0].CnSC = reg;
   reg = FTM1->CONTROLS[1].CnSC;
   reg &= ~(FTM_CnSC_MSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK);
   reg |= (uint32_t)kFTM_HighTrue << FTM_CnSC_ELSA_SHIFT;
   FTM1->CONTROLS[1].CnSC = reg;
   FTM1->COMBINE |= (1UL << (FTM_COMBINE_COMBINE0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)kFTM_Chnl_0)));
   FTM1->CONTROLS[0].CnV = 0;
   FTM1->CONTROLS[1].CnV = 0;
   FTM1->COMBINE |= (1UL << FTM_COMBINE_COMP0_SHIFT) | (1UL << FTM_COMBINE_DTEN0_SHIFT);
   FTM1->CONTROLS[0].CnSC |= FTM_CnSC_MSB_MASK;
   FTM1->CONTROLS[1].CnSC |= FTM_CnSC_MSB_MASK;
   FTM1->MODE |= FTM_MODE_FTMEN_MASK;
   FTM1->SYNCONF |= FTM_SYNCONF_SYNCMODE_MASK;
   FTM1->COMBINE |= FTM_COMBINE_SYNCEN0_MASK;

   FTM_StartTimer(FTM1, kFTM_SystemClock);

   return true;
}

bool BOARD_InitFTM2(void)
{
   return true;
}


/*!
 ******************************************************************************
 *	Sets the Own Address of the device
 * \param[in]     address     Own Address
 ******************************************************************************
*/
void BOARD_SetOwnAddress(uint16_t address)
{
   DeviceOwnAddress = address;
}

/*!
 ******************************************************************************
 *	Gets the Own Address of the device
 * \return        Own Address of the device
 ******************************************************************************
*/
uint16_t BOARD_GetOwnAddress(void)
{
   return DeviceOwnAddress;
}

/*!
 ******************************************************************************
 *	Flextimer 0 interrupt routine
 ******************************************************************************
*/
void FTM0_IRQHandler(void)
{
   FTM0->STATUS = 0;
   FTM0->SC &= ~FTM_SC_TOF_MASK;
}

/*!
 ******************************************************************************
 *	Flextimer 1 interrupt routine
 ******************************************************************************
*/
void FTM1_IRQHandler(void)
{
   FTM1->SC &= ~FTM_SC_TOF_MASK;
}

/*!
 ******************************************************************************
 *	Flextimer 2 interrupt routine
 ******************************************************************************
*/
void FTM2_IRQHandler(void)
{
   FTM2->SC &= ~FTM_SC_TOF_MASK;
}

void PIT0_IRQHandler(void)
{
static int			   ADC0channel_ctr_old = 0;
volatile uint16_t	   dummy;

	JiffyCntr++;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	if (ADC0channel_ctr_old == gADC0channel_ctr)
	{
		dummy = ADC0->R[0];
		dummy = ADC0->R[1];
		ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;
		ADC0->SC1[0] |= ADC_SC1_ADCH(ADC_Conversion_ADC0_Ptr[gADC0channel_ctr].adc_channel);
		if (ADC_Conversion_ADC0_Ptr[gADC0channel_ctr].adc_mux)
			ADC0->CFG2 |= ADC_CFG2_MUXSEL_MASK;
		else
			ADC0->CFG2 &= ~ADC_CFG2_MUXSEL_MASK;
	}
	else
		ADC0channel_ctr_old = gADC0channel_ctr;
}

void PIT1_IRQHandler(void)
{
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
}

bool BOARD_InitPIT(void)
{
	PIT_Init(PIT,&pitConfig);
	PIT_SetTimerPeriod(PIT,kPIT_Chnl_0,MSEC_TO_COUNT(PIT_Period0,CLOCK_GetBusClkFreq()));
	PIT_SetTimerPeriod(PIT,kPIT_Chnl_1,MSEC_TO_COUNT(PIT_Period1,CLOCK_GetBusClkFreq()));
	PIT_SetTimerPeriod(PIT,kPIT_Chnl_2,0xFFFFFFFF);    // Full resolution
	NVIC_SetPriority(PIT0_IRQn,PIT0_INT_PRIORITY);
	NVIC_SetPriority(PIT1_IRQn,PIT1_INT_PRIORITY);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0,kPIT_TimerInterruptEnable);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_1,kPIT_TimerInterruptEnable);
#ifdef BOARD_PIT0_IRQ_ENA
	EnableIRQ(PIT0_IRQn);
#endif
#ifdef BOARD_PIT1_IRQ_ENA
	EnableIRQ(PIT1_IRQn);
#endif
	PIT_StartTimer(PIT, kPIT_Chnl_0);
	PIT_StartTimer(PIT, kPIT_Chnl_1);
//   PIT_StartTimer(PIT, kPIT_Chnl_2);
	return true;
}

/*!
 ******************************************************************************
 *	Inits the Voltage Reference
 ******************************************************************************
*/
void BOARD_InitVREF(void)
{
	// init reference
	VREF_Init(VREF,&VrefConfigStruct);
}

void BOARD_Init(void)
{
	adc_channel = xTraceRegisterString("ADC");
	BOARD_setClockAttributes();
	BOARD_setPinAttributes();
	BOARD_UART_InitUart1();
	BOARD_InitPIT();
	BOARD_InitFTM0();
	BOARD_InitFTM1();
	BOARD_InitFTM2();
	BOARD_InitVREF();
	BOARD_InitADC();
	BOARD_InitDAC();
    CRC_init();
}

bool BOARD_SetGPIOpin(eGPIO_t pin,bool value)
{
int		ptr;

	ptr = (int)pin;
	if (ptr >= BOARD_N_GPIO)
		return false;
	GPIO_PinWrite(sGPIOconfig[pin].GPIO,sGPIOconfig[pin].Offset,value);
	return true;
}

bool BOARD_GetGPIOpin(eGPIO_t pin)
{
int		ptr;

	ptr = (int)pin;
	if (ptr >= BOARD_N_GPIO)
		return false;
	else
		return (bool)(GPIO_PinRead(sGPIOconfig[pin].GPIO,sGPIOconfig[pin].Offset));
}

uint64_t BOARD_GetJiffyCounter(void)
{
	return JiffyCntr;
}

/**
 * @brief Set up and initialize all required blocks and functions related to the board hardware.
 */
void BOARD_InitDebugConsole(void) {
	/* The user initialization should be placed here */
}
