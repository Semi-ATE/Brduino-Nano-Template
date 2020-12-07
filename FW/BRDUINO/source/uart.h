/*
 * uart.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef UART_H_
#define UART_H_

#include "board.h"

#define     DEBUG_PROTOCOL
#undef      DEBUG_PROTOCOL

#define	SOP			         0xA0				///< Start of package
#define	EOP			         0x05				///< End of package
#define	ESC			         0xF0				///< Escape sequence
#define	ESC_ESC		         0xF0				///< Byte stuffing of ESC
#define	ESC_SOP		         0x01				///< Byte stuffing of SOP
#define	ESC_EOP		         0x02				///< Byte stuffing of EOP

#define E_NO_ERROR           0x00           	///< Packet Error: No Error
#define	E_PREM_SOP	         0x01				///< Packet Error: Premature received SOP
#define	E_BUFFER_OVERFLOW    0x02				///< Packet Error: Receive Buffer Overflow
#define	E_ESCAPE_SEQ		 0x03	        	///< Packet Error: Wrong Escape Sequence
#define E_CRC_ERROR          0x04           	///< Packet Error: CRC Error
#define E_INVALID_PACKET     0x05           	///< Packet Error: CRC Error

#define  UART_NO_OF_UARTS     1              	///< Number of UART Interfaces
#define  UART_NO_RS232        0              	///< Number of UART RS232 Interfaces

#define  RS232_BUFFER_LEN     128             	///< RS232 receiver buffer length

#define		BAUDRATE_2400					    1
#define		BAUDRATE_4800					    2
#define		BAUDRATE_9600					    3
#define		BAUDRATE_14400					    4
#define		BAUDRATE_19200					    5
#define		BAUDRATE_28800					    6
#define		BAUDRATE_38400					    7
#define		BAUDRATE_57600					    8
#define		BAUDRATE_76800					    9
#define		BAUDRATE_115200					   	10

#define     PARITY_NONE                      	0
#define     PARITY_EVEN                      	1
#define     PARITY_ODD                       	2

typedef enum
{
   eUARTtype_None       = 0,
   eUARTtype_CommandIF  = 1
} eUARTfunction_t;

typedef struct
{
   UART_Type * const    IF_ptr;
   int                  IRQ_priority;
   const IRQn_Type      IRQ_number;
   int                  baudrate;
   uart_parity_mode_t   parity;
   eUARTfunction_t      IF_function;
   const eGPIO_t        IF_RS484_DE_nRE;
   const uint8_t        IF_number;
   const uint8_t        UART_number;
   const uint8_t        CMD_IF_enable;
   uint8_t              IRQ_enabled;
   const bool			IF_isRS485;
} UART_descriptor_t;

#define UART_DESC_ARRAY_SIZE        (UART_NO_OF_UARTS * sizeof(UART_descriptor_t))

void UART_RestoreDefaultIFdescriptors(void);
UART_descriptor_t *GetIFdescriptorPtr(void);
int WriteIFdescriptorID(int ID,UART_descriptor_t *desc);
UART_descriptor_t *GetSelectCmdIF(void);
int GetSelectCmdIFnr(uint8_t *CMD_IFnr);
int CheckCmdIF(int cmd_if_nr);
UART_Type *GetUARTfromIF(unsigned ID);
UART_descriptor_t *GetUARTdescriptor(unsigned UARTid);
UART_descriptor_t *GetUARTdescriptorFromPtr(UART_Type *UARTptr);
eUARTfunction_t GetUARTfunction(unsigned UARTid);
int ChangeUARTParameters(unsigned ID,int function,int baudrate,int parity);
int UART_InitIRQ(UART_descriptor_t *IFdesc,uint8_t enabled);
int UART_EnableIRQ(UART_descriptor_t *IFdesc);
int UART_DisableIRQ(UART_descriptor_t *IFdesc);
int UART_ChangeBaudrate(UART_descriptor_t *IFdesc,int baudrate);
int UART_GetBaudrate(UART_descriptor_t *IFdesc);
int UART_ChangeParity(UART_descriptor_t *IFdesc, int parity);
int UART_GetParity(UART_descriptor_t *IFdesc);
int UART_InitUart(UART_descriptor_t *IFdesc);
void UART_SendPacket(UART_descriptor_t *desc,uint8_t *packet,int len);
void UART_SendPacketCMD(uint8_t *packet,int len);

#endif /* UART_H_ */
