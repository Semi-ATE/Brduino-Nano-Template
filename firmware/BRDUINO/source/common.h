/*
 * common.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef COMMON_H_
#define COMMON_H_

/*
 * Debug prints ON (#define) or OFF (#undef)
 */
#ifndef DEBUG
#define DEBUG
#endif

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define DEBUG_PRINT

#define COMM_ENABLE
// #undef  COMM_ENABLE

#define USE_RTT
#undef  USE_RTT

#ifdef USE_RTT
#include "SEGGER_RTT.h"
#endif

#define USE_TRACEALYZER
// #undef  USE_TRACEALYZER

/*
 * Include the platform specific header file
 */
// #include "BRDUINODevice.h"

/*
 * Include the cpu specific header file
 */
#include "fsl_device_registers.h"


/*
 * Include common utilities
 */
#include "assert.h"
#include "stdlib.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


#if (defined(IAR))
	#include "intrinsics.h"
#endif

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"
#include "fsl_crc.h"
#include "fsl_clock.h"

#include "core_cm4.h"

#ifdef USE_TRACEALYZER
extern traceString dbgChannel;
#endif

/********************************************************************/

#endif /* COMMON_H_ */
