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
 * @file    MK22FN512xxx12_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "virtual_com.h"
#include "CommandHandler.h"

#include "BRDUINO_Nano.h"


/* TODO: insert other definitions and declarations here. */
TaskHandle_t               	TaskComm,TaskCtl;
uint8_t					  	bInitialized = 0;

traceString					dbgChannel;

extern int cmd_SUB_SYS_GET_CLOCKS(void);

/*!
 ******************************************************************************
 *	This is the Communication Task
 * \param[in]     pvParameters   Task parameters
 ******************************************************************************
*/
void CommunicationTask(void *pvParameters)
{
uint32_t            ulNotify;

   for( ;; )
   {
//	   cmd_SUB_SYS_GET_CLOCKS();
      if (xTaskNotifyWait(0x00,UINT32_MAX,&ulNotify,(TickType_t)500) == pdTRUE)
      {
         if ((ulNotify & (1 << 0)) != 0)
         {
            CommandHandler();
         }
         if ((ulNotify & (1 << 1)) != 0)
         {
            CommandHandler();
         }
         if ((ulNotify & (1 << 2)) != 0)
         {
//         	HandleCommEvent();
         }
      }
   }
}

/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_Init();

#ifdef USE_TRACEALYZER
#if (configUSE_TRACE_FACILITY == 1)
   vTraceEnable(TRC_START);         // Percepio Tracealyzer
   dbgChannel = xTraceRegisterString("BRDUINO");
#endif
#endif

    printf("This is BRDUINO-Nano ...\n\n");

    printf("Core Clock Frequency        : %lu Hz\n",CLOCK_GetFreq(kCLOCK_CoreSysClk));
    printf("Bus Clock Frequency         : %lu Hz\n",CLOCK_GetFreq(kCLOCK_BusClk));
    printf("Flash Clock Frequency       : %lu Hz\n",CLOCK_GetFreq(kCLOCK_FlashClk));
    printf("External Reference Frequency: %lu Hz\n",g_xtal0Freq);
    printf("USB Clock Frequency         : %lu Hz\n\n",CLOCK_GetFreq(kCLOCK_McgIrc48MClk));

	 printf("   Initialize Command Handler ... ");
	 if (InitCommandHandler())
	 {
		 printf("SUCCESS\n");
	 }
	 else
	 {
		 printf("FAILED\n");
	 }

	printf("   Creating Communication Task ... ");
	if (xTaskCreate(CommunicationTask, "COM-TASK", CommTask_STACK_SIZE, NULL, CommTask_PRIORITY, &TaskComm) != pdPASS)
	{
		printf("FAILED\n");
	}
	else
	{
		printf("SUCCESS\n");
	}
	 printf("Initializing USB stack ...\n");
	 if (usb_main_init())
		 printf(" ... SUCCESS\n\n");
	 else
		 printf(" ... FAILED\n\n");
	vTaskStartScheduler();
	/* Enter an infinite loop, just incrementing a counter. */
	for(;;) {
	}
	return 0;
}

void vApplicationMallocFailedHook(void)
{
	 printf("<<< Malloc failed\n");
}

void vApplicationStackOverflowHook( TaskHandle_t xTask,signed char *pcTaskName )
{
	 printf("<<<Stack Overflow\n");
}
