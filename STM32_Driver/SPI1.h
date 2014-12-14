#ifndef _SPI1_H
#define _SP1_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "PinCfgMap.h"

void SPI1_HardwareInit(void);
U8 SPI1_ReadWriteByte(U8 TxData);
void SPI1_SetCS(U8 , U8 );
U8 SPI1_ReadByte(void);
void SPI1_WriteByte(U8 TxData);


#endif
