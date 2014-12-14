#ifndef _MEMORY_H
#define _MEMORY_H

#include "TypeDef.h"




extern U32 GetMemUsed(void);

extern U8 *MemApply(U32 size);

extern void MemU16ToU8(U8 *dest, U16 *sour, U16 u8Len);

extern void MemU32ToU8(U8 *dest, U32 *sour, U16 u8Len);

extern void MemU8ToF32(F32 *dest, U8 *sour);



#endif
