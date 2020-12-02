/*
 * CmdSystem.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#include <string.h>

#include "common.h"
#include "uart.h"
#include "CommandDefs.h"
#include "CmdSystem.h"
#include "CommandHandler.h"
#include "Board.h"
#include "System.h"
#include "uart.h"
#include "Misc.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// static uint8_t						rx_buffer[80];

/*!
 ******************************************************************************
 *	Initializes the System Command Handler
 * \return     1 if success, 0 else
 ******************************************************************************
*/
int InitSystemCommandHandler(void)
{
   return 1;
}

/*!
 ******************************************************************************
 *	System Subcommand: Send Ping
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_REQUEST_PING(uint8_t *data,int len)
{
uint8_t     buf[10];
int         i;

   if (len < 4)
      return(CMD_ERR_INVALID_LENGTH);
   for (i=0;i<4;i++)
      buf[i+6] = data[i] ^ 0xFF;
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_REQUEST_PING,CMD_RX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the value of an ADC channel
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_GET_ADC_VALUE(uint8_t *data,int len)
{
uint8_t     buf[8];
uint16_t    value;

   if (len < 1)
      return(CMD_ERR_INVALID_LENGTH);
   if (!BOARD_get_ADC(data[0],&value))
   	return(CMD_ERR_COMMAND_FAILED);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_GET_ADC_VALUE,CMD_RX,BOARD_GetOwnAddress());
   SetVal_16(buf+6,value);
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get all ADC values
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_GET_ALL_ADC_VALUES(uint8_t *data,int len)
{
uint8_t     buf[BOARD_ADC_NumberOfChannels * 2 + 8];
uint16_t    value;

   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_GET_ALL_ADC_VALUES,CMD_RX,BOARD_GetOwnAddress());
   SetVal_16(buf+6,(uint16_t)BOARD_ADC_NumberOfChannels);
   for (int i = 0;i < BOARD_ADC_NumberOfChannels;i++)
   {
      if (!BOARD_get_ADC(i,&value))
      {
      	return(CMD_ERR_COMMAND_FAILED);
      }
   	SetVal_16(buf+i*2+8,value);
   }
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get all ADC values as floating point values
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_GET_ALL_ADC_VAL_FLOAT(uint8_t *data,int len)
{
uint8_t     buf[BOARD_ADC_NumberOfChannels * 4 + 8];
float    	value;

   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_GET_ALL_ADC_VAL_FLOAT,CMD_RX,BOARD_GetOwnAddress());
   SetVal_16(buf+6,(uint16_t)BOARD_ADC_NumberOfChannels);
   for (int i = 0;i < BOARD_ADC_NumberOfChannels;i++)
   {
      if (!BOARD_get_ADC_float(i,&value))
      {
      	return(CMD_ERR_COMMAND_FAILED);
      }
      SetVal_Float(buf+i*4+8,value);
   }
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get all system clock frequencies
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_GET_CLOCKS(void)
{
uint8_t     buf[26];

	MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_GET_CLOCKS,CMD_RX,BOARD_GetOwnAddress());
   SetVal_32(buf+6,CLOCK_GetFreq(kCLOCK_CoreSysClk));
   SetVal_32(buf+10,CLOCK_GetFreq(kCLOCK_BusClk));
   SetVal_32(buf+14,CLOCK_GetFreq(kCLOCK_FlashClk));
   SetVal_32(buf+18,g_xtal0Freq);
   SetVal_32(buf+22,CLOCK_GetFreq(kCLOCK_McgIrc48MClk));
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	Gets the Device Type
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_GET_DEVICE_TYPE(void)
{
uint8_t  buf[8];

   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_GET_DEVICE_TYPE,CMD_RX,BOARD_GetOwnAddress());
   SetVal_16(buf+6,GetSystemDeviceType());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set own address
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_SYS_SET_DEVICE_OWN_ADDR(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_SYS_SET_DEVICE_OWN_ADDR,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Command: Calls the System SUB-Command functions
 *	\param[in]	dev_nr      device number (index)
 *	\param[in]	command     parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int SystemCommandHandler(int16_t dev_nr,uint8_t *command,int len)
{
   switch(*command)
   {
		case SUB_SYS_REQUEST_PING:
			SendCommandType(CMD_RX);
			return cmd_SUB_SYS_REQUEST_PING(command+1,len-1);
		case SUB_SYS_SET_DEVICE_OWN_ADDR:
			SendCommandType(CMD_TX);
			return cmd_SUB_SYS_SET_DEVICE_OWN_ADDR(command+1,len-1);
		case SUB_SYS_GET_DEVICE_TYPE:
			SendCommandType(CMD_RX);
			return cmd_SUB_SYS_GET_DEVICE_TYPE();
		case SUB_SYS_GET_ADC_VALUE:
			SendCommandType(CMD_RX);
			return cmd_SUB_SYS_GET_ADC_VALUE(command+1,len-1);
		case SUB_SYS_GET_ALL_ADC_VALUES:
			SendCommandType(CMD_RX);
			return cmd_SUB_SYS_GET_ALL_ADC_VALUES(command+1,len-1);
		case SUB_SYS_GET_ALL_ADC_VAL_FLOAT:
			SendCommandType(CMD_RX);
			return cmd_SUB_SYS_GET_ALL_ADC_VAL_FLOAT(command+1,len-1);
		case SUB_SYS_GET_CLOCKS:
			SendCommandType(CMD_RX);
			return cmd_SUB_SYS_GET_CLOCKS();
      default:
         return CMD_ERR_UNKNOWN_SUBCMD;    	// we should never get there!
   }
}

