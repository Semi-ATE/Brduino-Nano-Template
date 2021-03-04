/*
 * CommandDefs.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef COMMANDDEFS_H_
#define COMMANDDEFS_H_

// Command Errors
#define CMD_NO_COMMAND_AVAILABLE          0
#define CMD_OK                            1
#define CMD_ERR_COMMAND_PENDING           -1
#define CMD_ERR_INVALID_LENGTH            -2
#define CMD_ERR_INVALID_PACKET            -3
#define CMD_ERR_INVALID_OW_DEVICE         -4
#define CMD_ERR_INVALID_OW_RESPONSE       -5
#define CMD_ERR_UNKNOWN_CMD               -6
#define CMD_ERR_UNKNOWN_SUBCMD            -7
#define CMD_ERR_COMMAND_FAILED            -8
#define CMD_ERR_INVALID_ADDRESS           -9
#define CMD_ERR_BUFFER_OVERFLOW           -10
#define CMD_ERROR_MUTEX_SYNC              -11
#define CMD_ERR_NO_MORE_DEVICES           -12

#define CMD_RETRY                         10
#define CMD_RETRY_WAIT                    50

#define CMD_ACK                           0x01                 //!< COMMAND: Acknowledge
#define CMD_NAK                           0x02                 //!< COMMAND: No Acknowledge

#define CMD_NONE                          0x00                 //!< COMMAND: Unknown command
#define CMD_TX                            0x01                 //!< COMMAND: TX command, no responsed besides ACK/NAK
#define CMD_RX                            0x02                 //!< COMMAND: RX command, ther is a responsed besides ACK/NAK

#define CMD_NO_CMD                        0x00                 //!< COMMAND: No Command specified
#define CMD_NO_SUB                        0x00                 //!< COMMAND: No Subcommand specified

// Main Commands
#define CMD_INFO                          0x01                 //!< COMMAND: Info Command
#define CMD_SYSTEM                        0x02                 //!< COMMAND: System Command
#define CMD_MEASUREMENT                   0x03                 //!< COMMAND: Measurement Command

// System Subcommands
#define SUB_SYS_SET_DEVICE_OWN_ADDR			0x01						//!< SUBCOMMAND: Set the Address of the Board
#define SUB_SYS_REQUEST_PING              0x02                 //!< SUBCOMMAND: Request ping command
#define SUB_SYS_GET_DEVICE_TYPE				0x03                 //!< SUBCOMMAND: Get the Device Type

#define SUB_SYS_GET_CLOCKS					 	0x70						//!< SUBCOMMAND: Get All System Clocks
#define SUB_SYS_GET_ADC_VALUE				 	0x7E						//!< SUBCOMMAND: Get the actual value of an ADC channel
#define SUB_SYS_GET_ALL_ADC_VALUES			0x7F						//!< SUBCOMMAND: Get all actual ADC values
#define SUB_SYS_GET_ALL_DIG_VALUES			0x80						//!< SUBCOMMAND: Get all digital values
#define SUB_SYS_GET_ALL_ADC_VAL_FLOAT		0x82						//!< SUBCOMMAND: Get all actual ADC values as floating point values

// Info Subcommands
#define SUB_INFO_GET_SYSTEM_INFO          0x01                 //!< SUBCOMMAND: Get System Info

// Measurement Subcommands
#define SUB_MEA_GET_MEASUREMENT				0x01						//!< SUBCOMMAND: Get all measurements
#define SUB_MEA_GET_BOOT_STAGE			 	0x02						//!< SUBCOMMAND: Get the Boot Stage
#define SUB_MEA_SET_BOOT_STAGE			 	0x03						//!< SUBCOMMAND: Set the Boot Stage
#define SUB_MEA_GET_BOOT_SEQUENCE		 	0x04						//!< SUBCOMMAND: Get the Boot Sequence
#define SUB_MEA_SET_BOOT_SEQUENCE		 	0x05						//!< SUBCOMMAND: Set the Boot Sequence
#define SUB_MEA_GET_RAIL_STATUS			 	0x06						//!< SUBCOMMAND: Get the Rail Status
#define SUB_MEA_SET_RAIL_STATUS			 	0x07						//!< SUBCOMMAND: Set the Rail Status
#define SUB_MEA_GET_VOLT_GAINS			 	0x08						//!< SUBCOMMAND: Get the Voltage Gains
#define SUB_MEA_SET_VOLT_GAINS			 	0x09						//!< SUBCOMMAND: Set the Voltage Gains
#define SUB_MEA_GET_CURR_GAINS			 	0x0A						//!< SUBCOMMAND: Get the Current Gains
#define SUB_MEA_SET_CURR_GAINS			 	0x0B						//!< SUBCOMMAND: Set the Current Gains
#define SUB_MEA_GET_VOLT_OFFSETS				0x0C						//!< SUBCOMMAND: Get the Voltage Offsets
#define SUB_MEA_SET_VOLT_OFFSETS				0x0D						//!< SUBCOMMAND: Set the Voltage Offsets
#define SUB_MEA_GET_CURR_OFFSETS				0x0E						//!< SUBCOMMAND: Get the Current Offsets
#define SUB_MEA_SET_CURR_OFFSETS				0x0F						//!< SUBCOMMAND: Set the Current Offsets
#define SUB_MEA_GET_VOLT_WINDOWS				0x10						//!< SUBCOMMAND: Get the Voltage Windows
#define SUB_MEA_SET_VOLT_WINDOWS				0x11						//!< SUBCOMMAND: Set the Voltage Windows
#define SUB_MEA_GET_CURR_WINDOWS				0x12						//!< SUBCOMMAND: Get the Current Windows
#define SUB_MEA_SET_CURR_WINDOWS				0x13						//!< SUBCOMMAND: Set the Current Windows
#define SUB_MEA_GET_NOTIFICATION			 	0x14						//!< SUBCOMMAND: Get the Notifications

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
