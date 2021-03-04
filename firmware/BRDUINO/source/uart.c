/*
 * uart.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

/*
 * File:        uart.c
 * Purpose:     Provide common UART routines for serial IO
 *
 * Notes:
 *
 */

#include <string.h>

#include "Board.h"
#include "uart.h"
#include "misc.h"
#include "crc.h"
#include "common.h"

#include "CommandHandler.h"

//volatile uint8_t              	packet_received_0 = 0;
//volatile uint8_t              	packet_wait_proc_0 = 0;

volatile int packet_len = 0, h1 = 0, h2 = 0;

const UART_descriptor_t UART_descriptor_default[UART_NO_OF_UARTS] = {
	{
		.IF_number = 0,
		.UART_number = 1,
		.IF_ptr = CONSOLE_UART,
		.IF_function = eUARTtype_CommandIF,
		.IF_RS484_DE_nRE = ePin_IF_RS484_DE_nRE,
		.CMD_IF_enable = true,
		.baudrate = CONSOLE_UART_BAUDRATE,
		.parity = kUART_ParityDisabled,
		.IRQ_enabled = true,
		.IRQ_number = UART1_RX_TX_IRQn,
		.IRQ_priority = UART1_INT_PRIORITY,
		.IF_isRS485 = true
	}
};

UART_descriptor_t UART_descriptor[UART_NO_OF_UARTS];

static UART_descriptor_t *Cmd_IF_Uart = &(UART_descriptor[0]);

/*!
 ******************************************************************************
 *	Restores the default UART descriptors
 ******************************************************************************
 */
void UART_RestoreDefaultIFdescriptors(void) {
	memcpy(UART_descriptor, UART_descriptor_default, UART_DESC_ARRAY_SIZE);
}

/*!
 ******************************************************************************
 *	Gets a pointer to the UART interface array (UART_descriptor_t *)
 * \return        pointer to the UART interface array
 ******************************************************************************
 */
UART_descriptor_t* GetIFdescriptorPtr(void) {
	return UART_descriptor;
}

/*!
 ******************************************************************************
 *	Copies the content of an interface descriptor into the selected
 * UART interface descriptor (selected by its ID)
 * \param[in]     ID          Target UART descriptor ID
 * \param[in]     desc        Pointer to Source UART descriptor
 * \return        1 if success, 0 else
 ******************************************************************************
 */
int WriteIFdescriptorID(int ID, UART_descriptor_t *desc) {
	if (desc == NULL || ID >= UART_NO_OF_UARTS)
		return 0;
	memcpy(&(UART_descriptor[ID]), desc, sizeof(UART_descriptor_t));
	return 1;
}

/*!
 ******************************************************************************
 *	Gets the selected Command Interface
 * \param[out]    CMD_IFnr        Command interface UART number (0..UART_NO_OF_UARTS-1)
 * \param[out]    isRS485         1 if this is a RS485 interface, 0 else
 * \return        0 if error, 1 else
 ******************************************************************************
 */
UART_descriptor_t* GetSelectCmdIF(void) {
	return Cmd_IF_Uart;
}

/*!
 ******************************************************************************
 *	Gets the selected Command Interface UART number
 * \param[out]    CMD_IFnr        Command interface UART number (0..UART_NO_OF_UARTS-1)
 * \return        0 if error, 1 else
 ******************************************************************************
 */
int GetSelectCmdIFnr(uint8_t *CMD_IFnr) {
	*CMD_IFnr = Cmd_IF_Uart->IF_number;
	return 1;
}

/*!
 ******************************************************************************
 *	Checks if a Command Interface UART number is valid (only UART0, UART1 and
 * UART5 are allowed as Command Interface
 * \param[in]     cmd_if_nr       Command Interface UART number (0..UART_NO_OF_UARTS-1)
 * \return        0 if not allowed, 1 else
 ******************************************************************************
 */
int CheckCmdIF(int cmd_if_nr) {
	UART_descriptor_t *ptr = GetUARTdescriptor(cmd_if_nr);
	if (ptr == NULL)
		return 0;
	return (ptr->CMD_IF_enable);
}

/*!
 ******************************************************************************
 *	Gets the UART pointer from the Interface Number
 * \param[in]     ID       UART ID (number), 0..UART_NO_OF_UARTS-1
 * \return        selected UART Pointer, NULL if not found (Error)
 ******************************************************************************
 */
UART_Type* GetUARTfromIF(unsigned ID) {
	if (ID >= UART_NO_OF_UARTS)
		return NULL;
	return UART_descriptor[ID].IF_ptr;
}

/*!
 ******************************************************************************
 *	Gets the UART descriptor from a UART index (number)
 * \param[in]     UARTid         UART index
 * \return        Pointer to UART descriptor, NULL if an error occured
 ******************************************************************************
 */
UART_descriptor_t* GetUARTdescriptor(unsigned UARTid) {
	if (UARTid >= UART_NO_OF_UARTS)
		return NULL;
	return &(UART_descriptor[UARTid]);
}

/*!
 ******************************************************************************
 *	Gets the UART descriptor from a UART pointer
 * \param[in]     UARTptr        UART pointer
 * \return        Pointer to UART descriptor, NULL if an error occured
 ******************************************************************************
 */
UART_descriptor_t* GetUARTdescriptorFromPtr(UART_Type *UARTptr) {
	for (int i = 0; i < UART_NO_OF_UARTS; i++)
		if (UART_descriptor[i].IF_ptr == UARTptr)
			return &(UART_descriptor[i]);
	return NULL;
}

/*!
 ******************************************************************************
 *	Gets the UART function from a UART index (number)
 * \param[in]     UARTid         UART index
 * \return        UART fuction if success, eUARTtype_None if an error occured
 ******************************************************************************
 */
eUARTfunction_t GetUARTfunction(unsigned UARTid) {
	if (UARTid >= UART_NO_OF_UARTS)
		return eUARTtype_None;
	return UART_descriptor[UARTid].IF_function;
}

/*!
 ******************************************************************************
 *	Change the parameters of a UART. If an input parameter is set to -1
 * it is not changed
 * \param[in]     cmd_IF_ID         UART ID (number), 0..UART_NO_OF_UARTS-1
 * \param[in]     function          UART function
 * \param[in]     baudrate          UART baudrate
 * \param[in]     parity            UART parity
 * \return        1 if success, 0 else
 ******************************************************************************
 */
int ChangeUARTParameters(unsigned ID, int function, int baudrate, int parity) {
	UART_descriptor_t *ptr = GetUARTdescriptor(ID);
	if (ptr == NULL)
		return 0;
	if (function != -1)
		ptr->IF_function = (eUARTfunction_t) function;
	if (baudrate != -1)
		UART_ChangeBaudrate(ptr, baudrate);
	if (parity != -1)
		UART_ChangeParity(ptr, parity);
	return 1;
}

/*!
 ******************************************************************************
 *	Checks for UART errors and handles them
 * \param[in]     UART     UART pointer
 * \return  -1 if error,  status of UART (Register S1) else
 ******************************************************************************
 */
static int UART_CheckAndHandleError(UART_Type *UART) {
	int ret = 1;
	uint8_t status;

	status = UART->S1;
	/* If RX framing error */
	if (UART_S1_FE_MASK & status) {
		/* Read UART_S1->D to clear framing error flag, otherwise the RX does not work. */
		while (UART->S1 & UART_S1_RDRF_MASK) {
			(void) UART->D;
		}
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
		/* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
		UART->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif
		ret = 0;
	}

	/* If RX parity error */
	if (UART_S1_PF_MASK & status) {
		/* Read UART->D to clear parity error flag, otherwise the RX does not work. */
		while (UART->S1 & UART_S1_RDRF_MASK) {
			(void) UART->D;
		}
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
		/* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
		UART->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif
		ret = 0;
	}

	/* If RX overrun. */
	if (UART_S1_OR_MASK & status) {
		/* Read UART->D to clear overrun flag, otherwise the RX does not work. */
		while (UART->S1 & UART_S1_RDRF_MASK) {
			(void) UART->D;
		}
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
		/* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
		UART->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif
		ret = 0;
	}
	if (ret != 0)
		return status;
	else
		return -1;
}

/*!
 ******************************************************************************
 *	UART command handler interrupt dispacher
 * \param[in]     UART     UART interface generating the interrupt
 ******************************************************************************
 */
static void UART_CmdIF_IRQDispatcher(int IFnum) {
	int status;

	if ((status = UART_CheckAndHandleError(UART_descriptor[IFnum].IF_ptr))
			== -1)
		return;
	eUARTfunction_t UA_function = UART_descriptor[IFnum].IF_function;
	if (status & UART_S1_RDRF_MASK) {
		switch (UA_function) {
		case eUARTtype_CommandIF:
			UART_CmdIF_IRQHandler(&(UART_descriptor[IFnum]));
			break;
		case eUARTtype_None:
			break;
		}
	}
}

/*!
 ******************************************************************************
 *	UART0 interrupt routine
 ******************************************************************************
 */
void UART0_RX_TX_DriverIRQHandler(void) {
	UART_CmdIF_IRQDispatcher(4);
}

/*!
 ******************************************************************************
 *	UART1 interrupt routine
 ******************************************************************************
 */
void UART1_RX_TX_DriverIRQHandler(void) {
	UART_CmdIF_IRQDispatcher(0);
}

/*!
 ******************************************************************************
 *	Initializes an UART interrupt and sets its priority
 * \param[in]  IFdesc     selected interface descriptor
 * \param[in]  enabled    selects if the interrupt is enabled or disabled
 * \return     1 if success, 0 else
 ******************************************************************************
 */
int UART_InitIRQ(UART_descriptor_t *IFdesc, uint8_t enabled) {
	if (IFdesc == NULL)
		return 0;
	IFdesc->IRQ_enabled = enabled;
	NVIC_SetPriority(IFdesc->IRQ_number, IFdesc->IRQ_priority);
	if (enabled)
		NVIC_EnableIRQ(IFdesc->IRQ_number);
	else
		NVIC_DisableIRQ(IFdesc->IRQ_number);
	return 1;
}

/*!
 ******************************************************************************
 *	Enables an UART interrupt and sets its priority
 * \param[in]  IFdesc     selected interface descriptor
 * \return     1 if success, 0 else
 ******************************************************************************
 */
int UART_EnableIRQ(UART_descriptor_t *IFdesc) {
	volatile uint8_t ch;

	if (IFdesc == NULL)
		return 0;
	NVIC_SetPriority(IFdesc->IRQ_number, IFdesc->IRQ_priority);
	while ((IFdesc->IF_ptr->S1 & UART_S1_RDRF_MASK) != 0)
		ch = IFdesc->IF_ptr->D;
	NVIC_EnableIRQ(IFdesc->IRQ_number);
	IFdesc->IF_ptr->C2 |= UART_C2_RIE_MASK;
	return 1;
}

/*!
 ******************************************************************************
 *	Disables an UART interrupt and sets its priority
 * \param[in]  IFdesc     selected interface descriptor
 * \return     1 if success, 0 else
 ******************************************************************************
 */
int UART_DisableIRQ(UART_descriptor_t *IFdesc) {
	if (IFdesc == NULL)
		return 0;
	NVIC_DisableIRQ(IFdesc->IRQ_number);
	IFdesc->IF_ptr->C2 &= ~UART_C2_RIE_MASK;
	return 1;
}

/*!
 ******************************************************************************
 *	Sets the baudrate of a UART
 * \param[in]     IFdesc      selected interface descriptor
 *	\return     1 if success, 0 else
 ******************************************************************************
 */
int UART_ChangeBaudrate(UART_descriptor_t *IFdesc, int baudrate) {
	if (IFdesc == NULL)
		return 0;
	if (UART_SetBaudRate(IFdesc->IF_ptr, baudrate, CLOCK_GetBusClkFreq())
			== kStatus_Success) {
		IFdesc->baudrate = baudrate;
	} else
		return 0;
	return 1;
}

/*!
 ******************************************************************************
 *	Gets the actual baudrate from the global array CurrentBaudrate[] using the
 * \param[in]     IFdesc      selected interface descriptor
 * \return     actual Baudrate, -1 if error
 ******************************************************************************
 */
int UART_GetBaudrate(UART_descriptor_t *IFdesc) {
	if (IFdesc == NULL)
		return -1;
	return IFdesc->baudrate;
}

/*!
 ******************************************************************************
 *	Changes the parity of a UART
 * parity = 0 => No Parity
 * parity = 1 => Even Parity
 * parity = 2 => Odd Parity
 * \param[in]     IFdesc      selected interface descriptor
 * \param[in]     parity      parity
 *	\return     1 if success, 0 else
 ******************************************************************************
 */
int UART_ChangeParity(UART_descriptor_t *IFdesc, int parity) {
	uint32_t reg_C1, reg_C2;
	register UART_Type *uartprt;

	if (IFdesc == NULL)
		return 0;
	uartprt = IFdesc->IF_ptr;
	while (0 != uartprt->TCFIFO)
		;
	while (0 == (uartprt->S1 & UART_S1_TC_MASK))
		;
	// stop UART
	reg_C2 = uartprt->C2;
	uartprt->C2 = 0;
	switch (parity) {
	case PARITY_NONE:
		reg_C1 = uartprt->C1;
		reg_C1 &= ~(UART_C1_PE_MASK | UART_C1_PT_MASK | UART_C1_M_MASK);
		uartprt->C1 = reg_C1;
		break;
	case PARITY_EVEN:
		reg_C1 = uartprt->C1;
		reg_C1 &= ~UART_C1_PT_MASK;
		reg_C1 |= (UART_C1_PE_MASK | UART_C1_M_MASK);
		uartprt->C1 = reg_C1;
		break;
	case PARITY_ODD:
		reg_C1 = uartprt->C1;
		reg_C1 |= (UART_C1_PE_MASK | UART_C1_PT_MASK | UART_C1_M_MASK);
		uartprt->C1 = reg_C1;
		break;
	default:
		return false;
	}
	// start UART
	uartprt->C2 = reg_C2;
	return 1;
}

/*!
 ******************************************************************************
 *	Gets the parity of a UART
 * parity = 0 => No Parity
 * parity = 1 => Even Parity
 * parity = 2 => Odd Parity
 * \param[in]     IFdesc      selected interface descriptor
 *	\return        parity
 ******************************************************************************
 */
int UART_GetParity(UART_descriptor_t *IFdesc) {
	register uint8_t reg_C1;

	if (IFdesc == NULL)
		return 0;
	reg_C1 = IFdesc->IF_ptr->C1;
	if ((reg_C1 & UART_C1_PE_MASK) != 0) {
		if ((reg_C1 & UART_C1_PT_MASK) != 0)
			return PARITY_ODD;
		else
			return PARITY_EVEN;
	} else
		return PARITY_NONE;
}

/*!
 ******************************************************************************
 *	Initialize the UART with interrupts disabled, and no hardware flow-control.
 * If parameter modbus is set the interface is enable with 8Bits + even parity,
 * else with 8Bits no parity. In both cases 1 Stopbit is used.
 * enabling the corresponding IRQ
 * \param[in]  IFdesc   selected interface descriptor
 * \return     1 if success, 0 else
 ******************************************************************************
 */
int UART_InitUart(UART_descriptor_t *IFdesc) {
	uart_config_t uart_config;
	int sysclk;

	if (IFdesc == NULL)
		return 0;
	if (IFdesc->UART_number == 0 || IFdesc->UART_number == 1)
		sysclk = CLOCK_GetCoreSysClkFreq();
	else
		sysclk = CLOCK_GetBusClkFreq();
	uart_config.enableTx = true;
	uart_config.enableRx = true;
	uart_config.parityMode = IFdesc->parity;
	uart_config.rxFifoWatermark = 1;
	uart_config.txFifoWatermark = 0;
	uart_config.baudRate_Bps = IFdesc->baudrate;
	uart_config.enableRxRTS = false;
	uart_config.enableTxCTS = false;
	uart_config.idleType = kUART_IdleTypeStartBit;
	UART_Init(IFdesc->IF_ptr, &uart_config, sysclk);
	if (IFdesc->IRQ_enabled)
		UART_EnableInterrupts(IFdesc->IF_ptr,
				kUART_RxDataRegFullInterruptEnable);
	return 1;
}
#ifndef DEBUG_PROTOCOL

/*!
 ******************************************************************************
 *	Sets the RS485 data enable signal for the selected interface
 * \param[in]     IFdesc      selected interface descriptor
 ******************************************************************************
 */
void set_rs485_data_enable(UART_descriptor_t *IFdesc) {
	BOARD_SetGPIOpin(IFdesc->IF_RS484_DE_nRE,true);      	// enable DE and disable nRE
	for (volatile int i = 0; i < 100; i++)
		;        // wait
}

/*!
 ******************************************************************************
 *	Clears the RS485 data enable signal for the selected interface
 * \param[in]     IFdesc      selected interface descriptor
 ******************************************************************************
 */
void clr_rs485_data_enable(UART_descriptor_t *IFdesc) {
	if (IFdesc == NULL)
		return;
	BOARD_SetGPIOpin(IFdesc->IF_RS484_DE_nRE,false);    	// disable DE and enable nRE
	for (volatile int i = 0; i < 100; i++)
		;         // wait
}

/*!
 ******************************************************************************
 *	Send data via the selected RS485 channel
 * \param[in]     IFdesc      selected interface descriptor
 *	\param[in]	   ch          Byte to send
 ******************************************************************************
 */
void send_rs485_char(UART_descriptor_t *IFdesc, uint8_t ch) {
	if (IFdesc == NULL)
		return;
	register UART_Type *uart = IFdesc->IF_ptr;
	/* Wait until space is available in the FIFO */
	while (!(uart->S1 & UART_S1_TDRE_MASK))
		;
	/* Send the character */
	uart->D = (uint8_t) ch;
	/* Wait until char is transmitted */
	while (!(uart->S1 & UART_S1_TC_MASK))
		;
}

/*!
 ******************************************************************************
 *	Waits until data via the selected RS485 channel has been sent
 * \param[in]     IFdesc      selected interface descriptor
 ******************************************************************************
 */
void wait_rs485_tx_done(UART_descriptor_t *IFdesc) {
	if (IFdesc == NULL)
		return;
	while (!(IFdesc->IF_ptr->S1 & UART_S1_TC_MASK))
		;
}

/*!
 ******************************************************************************
 *	Wait for space in the UART Tx FIFO and then send a character
 *	\param[in]	UART     pointer to selected UART
 *	\param[in]	ch       character to send
 ******************************************************************************
 */
static void UART_SendChar(UART_Type *UART, uint8_t ch) {
	/* Wait until space is available in the FIFO */
	while (!(UART->S1 & UART_S1_TDRE_MASK))
		;

	/* Send the character */
	UART->D = ch;
}

/*!
 *********************************************************************************
 * Sends a packet via the specified interface
 * \param[in]     desc     Pointer to UART descriptor
 * \param[in]		packet	Packet to send
 * \param[in]		len		Length of packet
 *********************************************************************************
 */
void UART_SendPacket(UART_descriptor_t *desc, uint8_t *packet, int len) {
	if (desc->IF_isRS485)
		set_rs485_data_enable(desc);
	while (len-- > 0) {
		UART_SendChar(desc->IF_ptr, *packet++);
	}
	if (desc->IF_isRS485) {
		wait_rs485_tx_done(desc);
		clr_rs485_data_enable(desc);
	}
}

/*!
 *********************************************************************************
 * Sends a command packet via RS232 or RS485 to the Command Interface
 * <SOP><Payload Byte> ... <16Byte Checksum><EOP>
 * \param[in]		packet	Packet to send
 * \param[in]		len		Length of packet
 *********************************************************************************
 */
void UART_SendPacketCMD(uint8_t *packet, int len) {
	uint16_t checksum;
	register UART_Type *ptrIF;

	CRC_Config(0x1021, 0, 0, 0, 0);
	checksum = CRC_Cal_16(0, packet, len, 0);
	ptrIF = Cmd_IF_Uart->IF_ptr;
	if (Cmd_IF_Uart->IF_isRS485)
		set_rs485_data_enable(Cmd_IF_Uart);
	UART_SendChar(ptrIF, SOP);								// Start of Packet;
	len += 2;
	while (len) {
		if (len == 2)
			packet = (uint8_t*) (&checksum);
		switch (*packet) {
		case SOP:
			UART_SendChar(ptrIF, ESC);
			UART_SendChar(ptrIF, ESC_SOP);
			break;
		case EOP:
			UART_SendChar(ptrIF, ESC);
			UART_SendChar(ptrIF, ESC_EOP);
			break;
		case ESC:
			UART_SendChar(ptrIF, ESC);
			UART_SendChar(ptrIF, ESC_ESC);
			break;
		default:
			UART_SendChar(ptrIF, *packet);
		}
		len--;
		packet++;
	}
	UART_SendChar(ptrIF, EOP);								// End of Packet;
	if (Cmd_IF_Uart->IF_isRS485) {
		wait_rs485_tx_done(Cmd_IF_Uart);
		clr_rs485_data_enable(Cmd_IF_Uart);
	}
}

/*!
 ******************************************************************************
 *	Wait for space in the UART Tx FIFO and then send a character
 *	\param[in]	channel  UART channel to send to
 *	\param[in]	ch       character to send
 ******************************************************************************
 */
int UART_Putchar(UART_Type *channel, char ch) {
	/* Wait until space is available in the FIFO */
	while (!(channel->S1 & UART_S1_TDRE_MASK))
		;

	/* Send the character */
	channel->D = (uint8_t) ch;

	return 1;
}

/*!
 ******************************************************************************
 *	Check to see if a character has been received
 *	\param[in]	channel  UART channel to check for a character
 *	\return              1 if character has been received, 0 else
 ******************************************************************************
 */
int UART_Getchar_present(UART_Type *channel) {
	return (channel->S1 & UART_S1_RDRF_MASK);
}

size_t _write(int handle, const unsigned char *buffer, size_t size) {
	size_t nChars = 0;

	if (buffer == 0) {
		/*
		 * This means that we should flush internal buffers.  Since we
		 * don't we just return.  (Remember, "handle" == -1 means that all
		 * handles should be flushed.)
		 */
		return 0;
	}

	for (/* Empty */; size != 0; --size) {
		if (*buffer == '\n') {
			if (UART_Putchar(CONSOLE_UART, '\r') < 0) {
				return size;
			}
		}
		if (UART_Putchar(CONSOLE_UART, *buffer++) < 0) {
			return size;
		}

		++nChars;
	}

	return nChars;
}

#endif
