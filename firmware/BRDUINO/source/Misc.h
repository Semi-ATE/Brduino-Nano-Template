/*
 * Misc.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef MISC_H_
#define MISC_H_

#include <stdint.h>
#include "common.h"

#define GetU8_Val(a)       (((uint8_t *)(a))[0])
#define GetI8_Val(a)       (((int8_t *)(a))[0])
#define GetU16_Val(a)      (((uint8_t *)(a))[0] + (((uint16_t)((uint8_t *)(a))[1]) << 8))
#define GetU32_Val(a)      (((uint8_t *)((a)))[0] + (((uint32_t)((uint8_t *)((a)))[1]) << 8) + (((uint32_t)((uint8_t *)(a))[2]) << 16) + (((uint32_t)((uint8_t *)(a))[3]) << 24))
#define GetI16_Val(a)      ((int16_t)(((uint8_t *)(a))[0] + (((uint16_t)((uint8_t *)(a))[1]) << 8)))
#define GetI32_Val(a)      ((int32_t)(((uint8_t *)(a))[0] + (((uint32_t)((uint8_t *)(a))[1]) << 8) + (((uint32_t)((uint8_t *)(a))[2]) << 16) + (((uint32_t)((uint8_t *)(a))[3]) << 24)))

#define GetU16_ValB(a)     (((uint8_t *)(a))[1] + (((uint16_t)((uint8_t *)(a))[0]) << 8))
#define GetU32_ValB(a)     (((uint8_t *)(a))[3] + (((uint32_t)((uint8_t *)(a))[2]) << 8) + (((uint32_t)((uint8_t *)(a))[1]) << 16) + (((uint32_t)((uint8_t *)(a))[0]) << 24))
#define GetI16_ValB(a)     ((int16_t)(((uint8_t *)(a))[3] + (((uint16_t)((uint8_t *)(a))[2]) << 8)))
#define GetI32_ValB(a)     ((int32_t)(((uint8_t *)(a))[3] + (((uint32_t)((uint8_t *)(a))[2]) << 8) + (((uint32_t)((uint8_t *)(a))[1]) << 16) + (((uint32_t)((uint8_t *)(a))[0]) << 24)))

#define SwapVal_16(a)      (((a >> 8) & 0xFF) | ((a & 0xFF) << 8))

#ifdef DEBUG
#define dbgprintf(...)     printf(__VA_ARGS__)
#else
#define dbgprintf(...)
#endif

#define  TASK_EVENT_DRIVEN
// #undef  TASK_EVENT_DRIVEN

#define MODBUSHANDLERTICKCNT     10
#define TASK_LONG_TIME           0xFFFF

void     SetVal_16(uint8_t *buf,uint16_t val);
void     SetVal_32(uint8_t *buf,uint32_t val);
void 		SetVal_Float(uint8_t *buf,float val);
float 	GetVal_Float(uint8_t *buf);
void     SetVal_16B(uint8_t *buf,uint16_t val);
void     SetVal_32B(uint8_t *buf,uint32_t val);
void 		SetVal_FloatB(uint8_t *buf,float val);
float 	GetVal_FloatB(uint8_t *buf);
void     MakeCommandHeader(uint8_t *buf,uint8_t cmd,uint8_t acknak,uint8_t subcmd,
                           uint8_t cmd_rxtx,uint16_t OwnAddress);
void     SwapEndianessVector(uint8_t *buf,int size);
int      GetBitNumber(uint8_t bitpos);
int      GetSysclkTimerHandle(void);
void     ReleaseSysclkTimerHandle(int handle);
void     SetSysclkTimer(int handle,uint32_t value);
uint32_t GetSysclkTimer(int handle);
void     ReleaseAllSysclkTimerHandles(void);
void     Sleep(int delay);
int      GetBitPositionInArray(uint16_t *buf,int size);

#endif /* MISC_H_ */
