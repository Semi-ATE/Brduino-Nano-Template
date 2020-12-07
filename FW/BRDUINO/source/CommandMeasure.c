/*
 * CommandMeasure.c
 *
 *  Created on: Dec 4, 2020
 *      Author: martin
 */

#include <string.h>

#include "common.h"
#include "uart.h"
#include "CommandDefs.h"
#include "CommandMeasure.h"
#include "CommandHandler.h"
#include "Board.h"
#include "System.h"
#include "Misc.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*!
 ******************************************************************************
 *	Initializes the Measurement Command Handler
 * \return     1 if success, 0 else
 ******************************************************************************
*/
int InitMeasureCommandHandler(void)
{
   return 1;
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the measurement values
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_MEASUREMENT(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_MEASUREMENT,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the boot stage
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_BOOT_STAGE(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_BOOT_STAGE,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the boot sequence
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_BOOT_SEQUENCE(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_BOOT_SEQUENCE,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the rails status
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_RAIL_STATUS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_RAIL_STATUS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the voltage gains
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_VOLT_GAINS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_VOLT_GAINS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the current gains
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_CURR_GAINS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_CURR_GAINS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the voltage offets
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_VOLT_OFFSETS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_VOLT_OFFSETS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the current offsets
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_CURR_OFFSETS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_CURR_OFFSETS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the voltage windows
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_VOLT_WINDOWS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_VOLT_WINDOWS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the current windows
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_CURR_WINDOWS(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_CURR_WINDOWS,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Get the notifications
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_GET_NOTIFICATION(uint8_t *data,int len)
{
uint8_t     buf[6 + 2 * 31];
uint16_t    value;

	if (!BOARD_get_ADC(data[0],&value))
		return(CMD_ERR_COMMAND_FAILED);
	MakeCommandHeader(buf,CMD_MEASUREMENT,CMD_ACK,SUB_MEA_GET_NOTIFICATION,CMD_RX,BOARD_GetOwnAddress());
	SetVal_16(buf+6,value);
	SendPacketCMD(buf,sizeof(buf));
	return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the boot stage
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_BOOT_STAGE(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_BOOT_STAGE,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the boot sequence
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_BOOT_SEQUENCE(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_BOOT_SEQUENCE,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the rail status
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_RAIL_STATUS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_RAIL_STATUS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the voltage gains
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_VOLT_GAINS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_VOLT_GAINS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the current gains
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_CURR_GAINS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_CURR_GAINS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the voltage offsets
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_VOLT_OFFSETS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_VOLT_OFFSETS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the current offsets
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_CURR_OFFSETS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_CURR_OFFSETS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the voltage windows
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_VOLT_WINDOWS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_VOLT_WINDOWS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Subcommand: Set the current windows
 *	\param[in]	data        parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int cmd_SUB_MEA_SET_CURR_WINDOWS(uint8_t *data,int len)
{
uint8_t     buf[6];
uint16_t    address;

   if (len < 2)
      return(CMD_ERR_INVALID_LENGTH);
   address = GetU16_Val(data);
   BOARD_SetOwnAddress(address);
   MakeCommandHeader(buf,CMD_SYSTEM,CMD_ACK,SUB_MEA_SET_CURR_WINDOWS,CMD_TX,BOARD_GetOwnAddress());
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	System Command: Calls the Measurement SUB-Command functions
 *	\param[in]	dev_nr      device number (index)
 *	\param[in]	command     parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int MeasureCommandHandler(int16_t dev_nr,uint8_t *command,int len)
{
   switch(*command)
   {
		case SUB_MEA_GET_MEASUREMENT:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_MEASUREMENT(command+1,len-1);
		case SUB_MEA_GET_BOOT_STAGE:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_BOOT_STAGE(command+1,len-1);
		case SUB_MEA_GET_BOOT_SEQUENCE:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_BOOT_SEQUENCE(command+1,len-1);
		case SUB_MEA_GET_RAIL_STATUS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_RAIL_STATUS(command+1,len-1);
		case SUB_MEA_GET_VOLT_GAINS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_VOLT_GAINS(command+1,len-1);
		case SUB_MEA_GET_CURR_GAINS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_CURR_GAINS(command+1,len-1);
		case SUB_MEA_GET_VOLT_OFFSETS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_VOLT_OFFSETS(command+1,len-1);
		case SUB_MEA_GET_CURR_OFFSETS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_CURR_OFFSETS(command+1,len-1);
		case SUB_MEA_GET_VOLT_WINDOWS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_VOLT_WINDOWS(command+1,len-1);
		case SUB_MEA_GET_CURR_WINDOWS:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_CURR_WINDOWS(command+1,len-1);
		case SUB_MEA_GET_NOTIFICATION:
			SendCommandType(CMD_RX);
			return cmd_SUB_MEA_GET_NOTIFICATION(command+1,len-1);
		case SUB_MEA_SET_BOOT_STAGE:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_BOOT_STAGE(command+1,len-1);
		case SUB_MEA_SET_BOOT_SEQUENCE:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_BOOT_SEQUENCE(command+1,len-1);
		case SUB_MEA_SET_RAIL_STATUS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_RAIL_STATUS(command+1,len-1);
		case SUB_MEA_SET_VOLT_GAINS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_VOLT_GAINS(command+1,len-1);
		case SUB_MEA_SET_CURR_GAINS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_CURR_GAINS(command+1,len-1);
		case SUB_MEA_SET_VOLT_OFFSETS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_VOLT_OFFSETS(command+1,len-1);
		case SUB_MEA_SET_CURR_OFFSETS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_CURR_OFFSETS(command+1,len-1);
		case SUB_MEA_SET_VOLT_WINDOWS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_VOLT_WINDOWS(command+1,len-1);
		case SUB_MEA_SET_CURR_WINDOWS:
			SendCommandType(CMD_TX);
			return cmd_SUB_MEA_SET_CURR_WINDOWS(command+1,len-1);
      default:
         return CMD_ERR_UNKNOWN_SUBCMD;    	// we should never get there!
   }
}

