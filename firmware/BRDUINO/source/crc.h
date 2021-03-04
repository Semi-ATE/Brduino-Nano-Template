/*
 * crc.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef CRC_H_
#define CRC_H_

// Type definitions
typedef volatile uint16_t vuint16_t;
typedef volatile uint32_t vuint32_t;
typedef volatile uint8_t  vuint8_t;

// Error code definition
#define CRC_ERR_SUCCESS       0
#define CRC_ERR_CODE_BASE    (0x2000)
#define CRC_ERR_TOT_VAL      (CRC_ERR_CODE_BASE+1)
#define CRC_ERR_TOTR_VAL     (CRC_ERR_CODE_BASE+2)
#define CRC_ERR_FXOR_VAL     (CRC_ERR_CODE_BASE+3)
#define CRC_ERR_TCRC_VAL     (CRC_ERR_CODE_BASE+4)

// Prototypes
void     CRC_init(void);
int      CRC_Config(uint32_t poly,uint32_t tot,uint32_t totr,uint32_t fxor,uint32_t tcrc);
uint32_t CRC_Cal_16(uint32_t seed,void *msg, uint32_t sizeBytes,uint8_t reverse);

#endif /* CRC_H_ */
