/*
 * CmdInfo.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#include <string.h>
#include "common.h"
#include "uart.h"
#include "CommandDefs.h"
#include "System.h"
#include "CmdInfo.h"
#include "CommandHandler.h"
#include "Misc.h"
#include "BRDUINODefs.h"
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*!
 ******************************************************************************
 *	Initializes the Debug Command Handler
 * \return     1 if success, 0 else
 ******************************************************************************
*/
int InitInfoCommandHandler(void)
{
   return 1;
}

/*!
 ******************************************************************************
 *	Gets the digital input port lines levels and send the result
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int SUB_GetSystemInfo(void)
{
uint8_t  buf[sizeof(SysInfo_t)+6];

   MakeCommandHeader(buf,CMD_INFO,CMD_ACK,SUB_INFO_GET_SYSTEM_INFO,CMD_RX,BOARD_GetOwnAddress());
   memcpy(buf+6,GetSystemInfoStructPtr(),sizeof(SysInfo_t));
   SendPacketCMD(buf,sizeof(buf));
   return(CMD_OK);
}

/*!
 ******************************************************************************
 *	Info Command: Calls the Info SUB-Command functions
 *	\param[in]	dev_nr      device number (index)
 *	\param[in]	command     parameter buffer
 *	\param[in]	len         length of paramter buffer
 * \return     CMD_OK if success, Errorcode else
 ******************************************************************************
*/
int InfoCommandHandler(int16_t dev_nr,uint8_t *command,int len)
{
   switch(*command)
   {
      case SUB_INFO_GET_SYSTEM_INFO:
         SendCommandType(CMD_RX);
         return(SUB_GetSystemInfo());
      default:
         return(CMD_ERR_UNKNOWN_SUBCMD);     // we should never get there!
   }
}
