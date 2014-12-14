#ifndef _I2C1_H
#define _I2C1_H

#include "Stm32f10x.h"

extern void I2C1_HardwareInit(void);
extern void I2C1_Read(u8 DevAddr,u8* pBuffer,u16 no);
extern void I2C1_WriteByte(u8 DevAddr,u8 WData);

#endif
