/*
 * CommandHandler.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#include "Board.h"
#include "Misc.h"
#include "crc.h"
#include "CommandDefs.h"
#include "virtual_com.h"
#include "CommandHandler.h"
#include "CmdInfo.h"
#include "CmdSystem.h"
#include "CommandMeasure.h"

SemaphoreHandle_t                   xMutex_CmdHandler;
SemaphoreHandle_t                   xSemaBin_CmdPollDevices;

static uint8_t                      t_cmd = CMD_NONE,t_subcmd = CMD_NO_SUB;
static volatile int                 poll_timer = 0;

static volatile uint8_t             rec_error = E_NO_ERROR;
static volatile uint8_t             sbuf_0[RS232_BUFFER_LEN];
static volatile uint8_t             rcv_buf_0[RS232_BUFFER_LEN];
static volatile int                 packet_len = 0;
static volatile uint8_t             packet_wait_proc_0 = 0;
static volatile uint8_t             packet_received_0 = 0;

typedef enum
{
	lrSource_UART = 0,
	lrSource_USB = 1
} lrSource_t;

static lrSource_t							lastReceiveSource = lrSource_USB;

/*!
 *********************************************************************************
 * Sends a command packet via UART or USB to the Command Interface
 * <SOP><Payload Byte> ... <16Byte Checksum><EOP>
 * \param[in]		packet	Packet to send
 * \param[in]		len		Length of packet
 *********************************************************************************
*/
void SendPacketCMD(uint8_t *packet,int len)
{
	if (lastReceiveSource == lrSource_UART)
	{
		UART_SendPacketCMD(packet,len);
	}
	else
	{
		USB_SendPacketCMD(packet,len);
	}
}

/*!
 ******************************************************************************
 *	Sets the command type to either TX or RX
 *	\param[in]	com_type    command type
 ******************************************************************************
*/
void SendCommandType(uint8_t com_type)
{
   t_cmd = com_type;
}

/*!
 ******************************************************************************
 *	Sends a NAK on the RS232 interface
 *	\param[in]	command     command that has issued the NAK
 *	\param[in]	subcommand  subcommand that has issued the NAK
 *	\param[in]	error_code  error code
 ******************************************************************************
*/
void SendNAK(uint8_t command,uint8_t subcommand,int16_t error_code)
{
uint8_t  buf[8];

   MakeCommandHeader(buf,command,CMD_NAK,subcommand,t_cmd,BOARD_GetOwnAddress());
   SetVal_16(buf+6,error_code);
   SendPacketCMD(buf,sizeof(buf));
}

/*!
 ******************************************************************************
 *	Initializes the Command Handler
 * \return     1 if success, 0 else
 ******************************************************************************
*/
int InitCommandHandler(void)
{
   xMutex_CmdHandler = xSemaphoreCreateMutex();
   if (xMutex_CmdHandler == NULL)
      return 0;
   xSemaBin_CmdPollDevices = xSemaphoreCreateBinary();
   if (xSemaBin_CmdPollDevices == NULL)
      return 0;
   InitInfoCommandHandler();
   InitSystemCommandHandler();
   InitMeasureCommandHandler();
   return 1;
}

/*!
 ******************************************************************************
 *	Reads a packet that has been received. Also performs a CRC check
 *	\param[out]	packet      Buffer for received packet
 *	\param[in]	len         Length of that buffer
 * \return  packet length if success, 0 if no packet pending, else error code < 0
 ******************************************************************************
*/
static int GetPacketCmdIF(uint8_t *packet,int len)
{
int         ret;
uint16_t    packet_crc,calc_crc;

   if (packet_received_0)
   {
      if (rec_error)
         ret = -((int)rec_error);
      else
         if (packet_len < 3)
            ret = -((int)E_INVALID_PACKET);
         else
         {
            ret = packet_len - 2;
            packet_crc = (uint16_t)(sbuf_0[ret]) + (((uint16_t)(sbuf_0[ret+1])) << 8);
            memcpy(packet,(void const *)sbuf_0,ret<=len?ret:len);
            CRC_Config(0x1021,0,0,0,0);
            calc_crc = CRC_Cal_16(0,packet,ret,0);
            if (calc_crc != packet_crc)
               ret = -((int)E_CRC_ERROR);
         }
      packet_wait_proc_0 = 0;
      packet_received_0 = 0;
      return(ret);
   }
   else
      return(0);
}

/*!
 ******************************************************************************
 *	Command Handler for RS232 commands. Handles all commands and returns either
 * an error code if failed, CMD_NO_COMMAND_AVAILABLE if no command is pending
 * or CMD_OK if command was pending and has been successfully processed
 * \return     CMD_OK or CMD_NO_COMMAND_AVAILABLE if success, Errorcode else
 ******************************************************************************
*/
int CommandHandler(void)
{
uint8_t              buf[RS232_BUFFER_LEN];
static uint8_t       command_pending = 0;
uint8_t              cmd;
int                  len,ret,retry;
uint16_t             dev_class,dev_nr;
uint8_t              *command;

   len = GetPacketCmdIF(buf,sizeof(buf));
   command = buf;
   if (len == 0)
   {
      return(CMD_NO_COMMAND_AVAILABLE);
   }
   if (len < 0)
   {
      SendNAK(CMD_NO_CMD,CMD_NO_SUB,CMD_ERR_INVALID_PACKET);
      return(CMD_ERR_INVALID_PACKET);
   }
   if (command_pending && command != NULL)
      return(CMD_ERR_COMMAND_PENDING);
   if (command != NULL)
   {
      if (len < 5)
      {
         SendNAK(CMD_NO_CMD,CMD_NO_SUB,CMD_ERR_INVALID_LENGTH);
         ret = CMD_ERR_INVALID_LENGTH;
      }
      dev_class = *((uint16_t *)command + 2);
      dev_nr = *((uint16_t *)(command));
      // Check for correct device address
      if (dev_nr != 0 && dev_nr != BOARD_GetOwnAddress())
         return CMD_NO_COMMAND_AVAILABLE;
      cmd = *(command + 4);
      command += 5;
      len -= 5;
      retry = CMD_RETRY;
      do
      {
         switch(cmd)
         {
				case CMD_INFO:
					t_subcmd = *command;
					ret = InfoCommandHandler(dev_nr,command,len);
					break;
				case CMD_SYSTEM:
					t_subcmd = *command;
					ret = SystemCommandHandler(dev_nr,command,len);
					break;
				case CMD_MEASUREMENT:
					t_subcmd = *command;
					ret = MeasureCommandHandler(dev_nr,command,len);
					break;
            default:
               t_cmd = CMD_NONE;
               t_subcmd = CMD_NO_SUB;
               ret = CMD_ERR_UNKNOWN_CMD;
         }
         if (ret != CMD_ERROR_MUTEX_SYNC)
            break;
         else
            vTaskDelay((TickType_t)CMD_RETRY_WAIT);
      }
      while(retry--);
      if (ret != CMD_OK)
         SendNAK(cmd,t_subcmd,ret);
   }
   return(ret);
}

/*!
 ******************************************************************************
 *	USB Low Level Command Handler
 * \param[in]     ch     	received character
 ******************************************************************************
*/
void UART_CmdIF_HandleUSB(uint8_t *buf,int count)
{
uint8_t                       ch;
static int                    len = 0,packet_pending = 0,escape_seq = 0;
BaseType_t                    xHigherPriorityTaskWoken = pdFALSE;

	while (count--)
	{
		ch = *buf++;
		if (ch == SOP)						// Start of Packet
		{
			if (packet_pending)			// premature SOP detected
			{
				rec_error = E_PREM_SOP;
				packet_received_0 = 1;  // signal that a packet has been received
			}
			else
				rec_error = 0;
			len = 0;							// reset the buffer length
			escape_seq = 0;				// reset escape sequencing
			packet_pending = 1;		   // set the packet pending flag
		}
		else
		{
			if (ch == EOP)				// End of Packet
			{
				strcpy((void *)rcv_buf_0,(void *)sbuf_0);		// save the buffer
				packet_len = len;
				rec_error = E_NO_ERROR;
				packet_wait_proc_0 = 1;								// wait for packet processing
				packet_received_0 = 1;				            // signal that a packet has been received
				packet_pending = 0;									// reset the packet pending flag
			}
			else
				if (packet_pending)									// just receiving a packet
				{
					if (ch == ESC && !escape_seq)					// Escape sequence detected (byte stuffing)
					{
						escape_seq = 1;								// signal that
					}
					else
						if (len < RS232_BUFFER_LEN)			   // if the buffer length has not exceeded
						{
							if (escape_seq)							// escape char
							{
								switch (ch)								// decode the byte stuffed char
								{
									case ESC_ESC:
										ch	= ESC;
										break;
									case ESC_SOP:
										ch	= SOP;
										break;
									case ESC_EOP:
										ch	= EOP;
										break;
									default:
										rec_error = E_ESCAPE_SEQ;	// wrong escape sequence
										packet_received_0 = 1;	   // signal that a packet has been received
										packet_pending = 0;
								}
								escape_seq = 0;
							}
							sbuf_0[len++] = ch;						// store the character in the packet buffer
						}
						else
						{
							rec_error = E_BUFFER_OVERFLOW;		// Buffer overflow occured
							packet_received_0 = 1;				   // signal that a packet has been received
							packet_pending = 0;
						}
				}
	      }
	   }
	#ifdef TASK_EVENT_DRIVEN
	if (packet_received_0)
	{
		if (TaskComm != NULL)
		{
	   	lastReceiveSource = lrSource_USB;
			xTaskNotifyFromISR(TaskComm,(1 << 1),eSetBits,&xHigherPriorityTaskWoken);
		}
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	#endif
}

/*!
 ******************************************************************************
 *	UART command handler interrupt routine
 * \param[in]     UART_desc     UART interface descriptor
 ******************************************************************************
*/
void UART_CmdIF_IRQHandler(UART_descriptor_t *UART_desc)
{
uint8_t                       ch;
int                           count;
static int                    len = 0,packet_pending = 0,escape_seq = 0;
BaseType_t                    xHigherPriorityTaskWoken = pdFALSE;
UART_Type                     *UART = UART_desc->IF_ptr;

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
   count = UART->RCFIFO;
#else
   count = 1;
#endif
   while (count--)
   {
      ch = UART->D;
      if (ch == SOP)						// Start of Packet
      {
         if (packet_pending)			// premature SOP detected
         {
            rec_error = E_PREM_SOP;
            packet_received_0 = 1;  // signal that a packet has been received
         }
         else
            rec_error = 0;
         len = 0;							// reset the buffer length
         escape_seq = 0;				// reset escape sequencing
         packet_pending = 1;		   // set the packet pending flag
      }
      else
      {
         if (ch == EOP)				// End of Packet
         {
            strcpy((void *)rcv_buf_0,(void *)sbuf_0);		// save the buffer
            packet_len = len;
            rec_error = E_NO_ERROR;
            packet_wait_proc_0 = 1;								// wait for packet processing
            packet_received_0 = 1;				            // signal that a packet has been received
            packet_pending = 0;									// reset the packet pending flag
         }
         else
            if (packet_pending)									// just receiving a packet
            {
               if (ch == ESC && !escape_seq)					// Escape sequence detected (byte stuffing)
               {
                  escape_seq = 1;								// signal that
               }
               else
                  if (len < RS232_BUFFER_LEN)			   // if the buffer length has not exceeded
                  {
                     if (escape_seq)							// escape char
                     {
                        switch (ch)								// decode the byte stuffed char
                        {
                           case ESC_ESC:
                              ch	= ESC;
                              break;
                           case ESC_SOP:
                              ch	= SOP;
                              break;
                           case ESC_EOP:
                              ch	= EOP;
                              break;
                           default:
                              rec_error = E_ESCAPE_SEQ;	// wrong escape sequence
                              packet_received_0 = 1;	   // signal that a packet has been received
                              packet_pending = 0;
                        }
                        escape_seq = 0;
                     }
                     sbuf_0[len++] = ch;						// store the character in the packet buffer
                  }
                  else
                  {
                     rec_error = E_BUFFER_OVERFLOW;		// Buffer overflow occured
                     packet_received_0 = 1;				   // signal that a packet has been received
                     packet_pending = 0;
                  }
            }
      }
   }
#ifdef TASK_EVENT_DRIVEN
   if (packet_received_0)
   {
	   lastReceiveSource = lrSource_UART;
	   xTaskNotifyFromISR(TaskComm,(1 << 0),eSetBits,&xHigherPriorityTaskWoken);
   }
// if (packet_received_0 && xSemaBin_UART0 != NULL)
// {
//    xSemaphoreGiveFromISR(xSemaBin_UART0,&xHigherPriorityTaskWoken);
//    xSemaphoreGiveFromISR(xSemaBin_UART0,&xHigherPriorityTaskWoken);
//    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
// }
   portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#endif
}
