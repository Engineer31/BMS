#ifndef _I2C_H
#define _I2C_H

#include "I2C1.h"

void I2C_DriverInit(u8 ch);
void I2C_WriteByte(u8 ch,u8 DevAddr,u8 WData);
void I2C_Read(u8 ch,u8 DevAddr,u8* pBuffer,u16 no);
#endif
