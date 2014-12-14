#ifndef _SPI_H
#define _SPI_H

#include "SPI1.h"

extern Bool SPI_DriverInit(u8);
extern U8 SPI_ReadWriteByte(U8 channel,U8 TxData);

#endif
