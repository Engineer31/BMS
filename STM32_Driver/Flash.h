#ifndef _FLASH_H
#define _FLASH_H

#include "stm32f10x.h"
#include "TypeDef.h"

Bool Flash_Write_U32(u32 StartAddr,u32 *p_data,u32 size);
Bool Flash_Read_U32(u32 StartAddr,u32 *p_data,u32 size);

void Flash_Write_F32(U32 StartAddr,F32 *p_data,u32 size);
void Flash_Read_F32(U32 StartAddr,F32 *p_data,u32 size);

u8 FLASH_WriteHalfWord(u32 faddr, u16 dat);
u8 FLASH_Write_U16(u32 faddr, u16* pdata,u16 length);

u16 FLASH_ReadHalfWord(u32 faddr);

#endif
