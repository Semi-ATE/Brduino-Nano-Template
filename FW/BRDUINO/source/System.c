/*
 * System.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#include "common.h"
#include "System.h"

static const SysInfo_t  SysInfoStruct =
{
   SYS_INFO_STRUCT_N_ENTRIES,
   sizeof(SYS_DEVICE_NAME),
   SYS_DEVICE_NAME,
   sizeof(SYS_SW_VERSION),
   SYS_SW_VERSION,
   sizeof(SYS_LAST_CHANGE),
   SYS_LAST_CHANGE
};

/*!
 ******************************************************************************
 *	Gets a Pointer ot the SysInfo Structure
 * \return     1 if success, 0 else
 ******************************************************************************
*/
SysInfo_t *GetSystemInfoStructPtr(void)
{
   return (SysInfo_t *)(&SysInfoStruct);
}

/*!
 ******************************************************************************
 *	Gets the System Device Type
 * \return     System Device Type
 ******************************************************************************
*/
uint16_t GetSystemDeviceType(void)
{
   return SYS_DEVICE_TYPE;
}
