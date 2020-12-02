/*
 * Misc.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#include "FreeRTOS.h"
#include "task.h"
#include "Misc.h"

static   uint8_t     sysclk_in_use = 0;

/******************************************************************************
 *	Writes a 16Bit-Value into a Bytewide Buffer (Little Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
void SetVal_16(uint8_t *buf,uint16_t val)
{
   buf[0] = val & 0xFF;
   buf[1] = val >> 8;
}

/******************************************************************************
 *	Writes a 32Bit-Value into a Bytewide Buffer (Little Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
void SetVal_32(uint8_t *buf,uint32_t val)
{
   buf[0] = val & 0xFF;
   buf[1] = (val >> 8) & 0xFF;
   buf[2] = (val >> 16) & 0xFF;
   buf[3] = val >> 24;
}

/******************************************************************************
 *	Writes a Float-Value into a Bytewide Buffer (Little Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
void SetVal_Float(uint8_t *buf,float val)
{
uint32_t		uval;

	uval = *((uint32_t *)(&val));
	SetVal_32(buf,uval);
}

/******************************************************************************
 *	Writes a 16Bit-Value into a Bytewide Buffer (Big Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
void SetVal_16B(uint8_t *buf,uint16_t val)
{
   buf[1] = val & 0xFF;
   buf[0] = val >> 8;
}

/******************************************************************************
 *	Writes a 32Bit-Value into a Bytewide Buffer (Big Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
void SetVal_32B(uint8_t *buf,uint32_t val)
{
   buf[3] = val & 0xFF;
   buf[2] = (val >> 8) & 0xFF;
   buf[1] = (val >> 16) & 0xFF;
   buf[0] = val >> 24;
}

/******************************************************************************
 *	Writes a Float-Value into a Bytewide Buffer (Big Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
void SetVal_FloatB(uint8_t *buf,float val)
{
uint32_t		uval;

	uval = *((uint32_t *)(&val));
	SetVal_32B(buf,uval);
}

/******************************************************************************
 *	Gets a Float-Value from a Bytewide Buffer (Little Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
float GetVal_Float(uint8_t *buf)
{
uint32_t		val;

	val = GetU32_Val(buf);
	return *((float *)(&val));

   buf[3] = val & 0xFF;
   buf[2] = (val >> 8) & 0xFF;
   buf[1] = (val >> 16) & 0xFF;
   buf[0] = val >> 24;
}

/******************************************************************************
 *	Gets a Float-Value from a Bytewide Buffer (Big Endian)
 * \param[out]		buf   ByteWide Buffer
 * \param[in]		val   value that should be written
 ******************************************************************************/
float GetVal_FloatB(uint8_t *buf)
{
uint32_t		val;

	val = GetU32_ValB(buf);
	return *((float *)(&val));

   buf[3] = val & 0xFF;
   buf[2] = (val >> 8) & 0xFF;
   buf[1] = (val >> 16) & 0xFF;
   buf[0] = val >> 24;
}

/******************************************************************************
 *	Assembles a command header (Command Response, 6 Bytes)
 * \param[out]		buf         Command Buffer (min length is 6 Bytes)
 * \param[in]		cmd         Command
 * \param[in]		acknak      ACK or NAK
 * \param[in]		subcmd      Subcommand
 * \param[in]		cmd_rxtx    CMD_RX or CMD_TX
 * \param[in]		OwnAddress  Command
 ******************************************************************************/
void MakeCommandHeader(uint8_t *buf,uint8_t cmd,uint8_t acknak,uint8_t subcmd,
                       uint8_t cmd_rxtx,uint16_t OwnAddress)
{
   SetVal_16(buf,OwnAddress);
   buf[2] = cmd;
   buf[3] = acknak;
   buf[4] = subcmd;
   buf[5] = cmd_rxtx;
}

/******************************************************************************
 *	Reorders a (16Bit) Array into 16Bit and changes Endianess. Little Endian
 * becomes Big Endian and Big Endian becomes Little Endian
 * \param[in,out] buf   ByteWide Buffer that shall be reordered
 * \param[in]     size  Size of ByteWide Buffer in Bytes
 ******************************************************************************/
void SwapEndianessVector(uint8_t *buf,int size)
{
int      i;
uint8_t  h;

   for (i = 0;i < size;i++)
   {
      h = buf[i*2];
      buf[i*2] = buf[i*2+1];
      buf[i*2+1] = h;
   }
}

/*!
 ******************************************************************************
 *	Gets the bit number from the bit position
 * \param[in]  bitpos   bit position
 *	\return     bit number
 ******************************************************************************
*/
int GetBitNumber(uint8_t bitpos)
{
int      i;

   for (i=0;i<8;i++)
      if ((1 << i) & bitpos)
         return(i);
   return(0);
}

/*!
 ******************************************************************************
 *	Gets s sysclk timer handle.
 *	\return     sysclk handle or -1 if error
 ******************************************************************************
*/
int GetSysclkTimerHandle(void)
{
int      i;

   for (i=0;i<4;i++)
      if (!(sysclk_in_use & (1 << i)))
      {
         sysclk_in_use |= (1 << i);
         return(i);
      }
   return(-1);
}

/*!
 ******************************************************************************
 *	Releases a sysclk timer handle.
 *	\param[in]  handle   sysclk handle
 ******************************************************************************
*/
void ReleaseSysclkTimerHandle(int handle)
{
   sysclk_in_use &= ~(1 << handle);
}

/*!
 ******************************************************************************
 *	Releases all sysclk timer handle.
 ******************************************************************************
*/
void ReleaseAllSysclkTimerHandles(void)
{
   sysclk_in_use = 0;
}

/*!
 ******************************************************************************
 *	Sets a sysclk timer.
 *	\param[in]  handle   sysclk handle
 *	\param[in]  value    new timer value
 ******************************************************************************
*/
void SetSysclkTimer(int handle,uint32_t value)
{
//   if (handle >= 0 && handle < 4)
//      tc_counter[handle] = value;
}

/*!
 ******************************************************************************
 *	Gets a sysclk timer value.
 *	\param[in]  handle   sysclk handle
 *	\return     timer value
 ******************************************************************************
*/
uint32_t GetSysclkTimer(int handle)
{
//   if (handle >= 0 && handle < 4)
//      return(tc_counter[handle]);
//   else
      return(0);
}

/*!
 ******************************************************************************
 *	Delays the execution by a given number of milliseconds.
 *	\param[in]  delay    delay in msec
 ******************************************************************************
*/
void Sleep(int delay)
{
   vTaskDelay(delay / portTICK_PERIOD_MS);
}

/*!
 ******************************************************************************
 *	Gets the Bit Position of the first non zero bit in an uint16_t sized array.
 *	\param[in]  buf      the array (uint16_t[])
 *	\param[in]  size     the array size
 * \return  bit position of first non zero bit, -1 if none has been found
 ******************************************************************************
*/
int GetBitPositionInArray(uint16_t *buf,int size)
{
int      i,j;

   for (i = 0;i < size;i++)
      for (j = 0;j < 16;j++)
         if (((buf[i] >> j) & 1) != 0)
              return i * 16 + j;
   return -1;
}
