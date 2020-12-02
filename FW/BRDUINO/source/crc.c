/*
 * crc.c
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

/*
 * File:		crc.c
 * Purpose:		crc algorithm routine for CRC16 and CRC32
 * Description:
 *
 *
 */


#include "common.h"
#include "crc.h"

//#define BYTE_ENABLES_7_E
//#define BYTE_ENABLES_3_6_C
//#define BYTE_ENABLES_1_2_4_8


/*!
 ******************************************************************************
 *	Initializes the CRC peripheral
 ******************************************************************************
*/
void CRC_init(void)
{
   // Enable clock gating to CRC
   SIM->SCGC6 |= SIM_SCGC6_CRC_MASK;
}

/*!
 ******************************************************************************
 *	Configure the CRC peripheral
 * \param[in]		poly	   CRC polynomial
 * \param[in]		tot	   defines if input data is bit and/or byte reversed
 * \param[in]		totr	   defines if result is bit and/or byte reversed
 * \param[in]		fxor	   defines if result is complemented
 * \param[in]		tcrc	   0 for 16Bit CRC, 1 for 32Bit CRC
 * \return        0 if success, error code else
 ******************************************************************************
*/
int CRC_Config (uint32_t poly,uint32_t tot,uint32_t totr,uint32_t fxor,uint32_t tcrc)
{
uint32_t    ctrl_reg;
int         error = CRC_ERR_SUCCESS;

   // Configure CRC_CTRL Register
   if (tot > 3)
   {
  	   error = CRC_ERR_TOT_VAL;
   }
   else
      if (totr > 3)
      {
  	      error = CRC_ERR_TOTR_VAL;
      }
      else
         if (fxor > 1)
         {
  	         error = CRC_ERR_FXOR_VAL;
         }
         else
            if (tcrc > 1)
            {
  	            error = CRC_ERR_TCRC_VAL;
            }
            else
            {
  	            ctrl_reg = CRC_CTRL_TOT(tot) | CRC_CTRL_TOTR(totr) | (fxor << CRC_CTRL_FXOR_SHIFT) | (tcrc << CRC_CTRL_TCRC_SHIFT);
  	            CRC0->CTRL = ctrl_reg;
            }
   // Configure Polynomial Register
   CRC0->GPOLY = poly;
   return(error);
}

/*!
 ******************************************************************************
 *	Calculates a 16Bit CRC
 * \param[in]		seed	      starting value
 * \param[in]		msg	      Buffer with data
 * \param[in]		sizeBytes	Length of Buffer in Bytes
 * \param[in]		reverse	   if 1 the result is bit and byte reversed
 * \return        result of CRC calculation
 ******************************************************************************
*/
uint32_t CRC_Cal_16(uint32_t seed,void *msg, uint32_t sizeBytes,uint8_t reverse)
{
uint32_t    ctrl_reg;
uint32_t    i;
uint8_t     *p;


   // Input seed, Set WaS=1
   ctrl_reg = CRC0->CTRL;
   CRC0->CTRL = ctrl_reg | CRC_CTRL_WAS_MASK;
   CRC0->DATA = seed;

   // Input data, Set WaS=0
   CRC0->CTRL = ctrl_reg & ~CRC_CTRL_WAS_MASK;

   // Wait for calculation completion
   p = (uint8_t *)msg;
   for (i=0;i<sizeBytes;i++)
   {
      CRC0->ACCESS8BIT.DATALL = *p++;
   }
   if (reverse)
      return(CRC0->DATA >> 16);
   else
      return(CRC0->DATA);
}
