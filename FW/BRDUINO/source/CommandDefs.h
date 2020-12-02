/*
 * CommandDefs.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef COMMANDDEFS_H_
#define COMMANDDEFS_H_

// Command Errors
#define CMD_NO_COMMAND_AVAILABLE             0
#define CMD_OK                               1
#define CMD_ERR_COMMAND_PENDING              -1
#define CMD_ERR_INVALID_LENGTH               -2
#define CMD_ERR_INVALID_PACKET               -3
#define CMD_ERR_INVALID_OW_DEVICE            -4
#define CMD_ERR_INVALID_OW_RESPONSE          -5
#define CMD_ERR_UNKNOWN_CMD                  -6
#define CMD_ERR_UNKNOWN_SUBCMD               -7
#define CMD_ERR_COMMAND_FAILED               -8
#define CMD_ERR_INVALID_ADDRESS              -9
#define CMD_ERR_BUFFER_OVERFLOW              -10
#define CMD_ERROR_MUTEX_SYNC                 -11
#define CMD_ERR_NO_MORE_DEVICES              -12

#define CMD_RETRY                            10
#define CMD_RETRY_WAIT                       50

#define CMD_ACK                              0x01                    //!< COMMAND: Acknowledge
#define CMD_NAK                              0x02                    //!< COMMAND: No Acknowledge

#define CMD_NONE                             0x00                    //!< COMMAND: Unknown command
#define CMD_TX                               0x01                    //!< COMMAND: TX command, no responsed besides ACK/NAK
#define CMD_RX                               0x02                    //!< COMMAND: RX command, ther is a responsed besides ACK/NAK

#define CMD_NO_CMD                           0x00                    //!< COMMAND: No Command specified
#define CMD_NO_SUB                           0x00                    //!< COMMAND: No Subcommand specified

// Main Commands
#define CMD_INFO                             0x01                    //!< COMMAND: Info Command
#define CMD_SYSTEM                           0x02                    //!< COMMAND: System Command

// System Subcommands
#define SUB_SYS_SET_DEVICE_OWN_ADDR				0x01							//!< SUBCOMMAND: Set the Address of the Board
#define SUB_SYS_REQUEST_PING                	0x02                    //!< SUBCOMMAND: Request ping command
#define SUB_SYS_GET_DEVICE_TYPE					0x03                    //!< SUBCOMMAND: Get the Device Type

#define SUB_SYS_GET_CLOCKS							0x70							//!< SUBCOMMAND: Get All System Clocks
#define SUB_SYS_GET_ADC_VALUE						0x7E							//!< SUBCOMMAND: Get the actual value of an ADC channel
#define SUB_SYS_GET_ALL_ADC_VALUES				0x7F							//!< SUBCOMMAND: Get all actual ADC values
#define SUB_SYS_GET_ALL_DIG_VALUES				0x80							//!< SUBCOMMAND: Get all digital values
#define SUB_SYS_GET_ALL_ADC_VAL_FLOAT			0x82							//!< SUBCOMMAND: Get all actual ADC values as floating point values

// Info Subcommands
#define SUB_INFO_GET_SYSTEM_INFO            	0x01                 	//!< SUBCOMMAND: Get System Info

/*! @} */

//! <a href="CommandDescription.htm"> Detailed Command Description</a>

/**@}*/

typedef struct __attribute__((packed))
{
   int16_t        length;                    //!< Length of the packet
   uint16_t       device;                    //!< Device Number
   uint8_t        command;                   //!< Command
   uint8_t        subcommand;                //!< Subcommand
   uint8_t        acknak;                    //!< ACK or NAK
   uint8_t        flags;                     //!< Flags;
}  t_ProtocolPacketHeaderResponse;

typedef struct __attribute__((packed))
{
   int16_t        length;                    //!< Length of the packet
   uint16_t       device;                    //!< Device Number
   uint16_t       deviceclass;               //!< Device Class
   uint8_t        command;                   //!< Command
   uint8_t        subcommand;                //!< Subcommand
   uint8_t        flags;                     //!< Flags;
}  t_ProtocolPacketHeaderRequest;

#endif /* COMMANDDEFS_H_ */
