#include "TypeDef.h"


//#define MEM_BUF_SIZE		78000
#define MEM_BUF_SIZE  		10000		//ÄÚ´æ²»×ã


U8 MemBuf[MEM_BUF_SIZE];
U32 MemP = 0x00;

U32 GetMemUsed(void)
{
    return MemP;
}

U8 *MemApply(U32 size)
{
    U8 *p;
    p = &MemBuf[MemP];
    MemP += size;

    if(MemP > MEM_BUF_SIZE)
    {
        while(1);
//        return 0;
    }
    else
        return p;
}


void MemU16ToU8(U8 *dest, U16 *sour, U16 u8Len)
{
    U16 i = 0, j = 0;
    while(i < u8Len)
    {
        dest[i++] = (sour[j] & 0x00ff);
        if(i == u8Len)
            break;
        dest[i++] = ((sour[j] >> 8) & 0x00ff);
        j++;
    }
}
void MemU32ToU8(U8 *dest, U32 *sour, U16 u8Len)
{
    U16 i = 0, j = 0;
    while(i < u8Len)
    {
        dest[i++] = (sour[j] & 0x000000ff);
        if(i == u8Len)
            break;
        dest[i++] = ((sour[j] >> 8) & 0x000000ff);
        if(i == u8Len)
            break;
        dest[i++] = ((sour[j] >> 16) & 0x000000ff);
        if(i == u8Len)
            break;
        dest[i++] = ((sour[j] >> 24) & 0x000000ff);
        j++;
    }
}

void MemU8ToF32(F32 *dest, U8 *sour)
{
    U32 *p;
    U32 q;
    p = (U32 *)dest;

    *p = 0;
    q = sour[3];
    *p += (q << 24);
    q = sour[2];
    *p += (q << 16);
    q = sour[1];
    *p += (q << 8);
    q = sour[0];
    *p += q;
}






















