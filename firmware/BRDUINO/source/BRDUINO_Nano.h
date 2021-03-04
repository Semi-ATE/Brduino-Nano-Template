/*
 * BRDUINO_Nano.h
 *
 *  Created on: Dec 1, 2020
 *      Author: martin
 */

#ifndef BRDUINO_NANO_H_
#define BRDUINO_NANO_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#define CommTask_PRIORITY          	(tskIDLE_PRIORITY + 2)
#define CommTask_STACK_SIZE	        1024

#endif /* BRDUINO_NANO_H_ */
