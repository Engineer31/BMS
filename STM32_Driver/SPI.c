#include "SPI.h"

Bool SPI_DriverInit(u8 ch)
{
    if(ch == 1)
    {
        SPI1_HardwareInit();
    }
    else if(ch == 2)
    {
    }
    else
    {
        return TRUE;
    }
    return 1;
}

U8 SPI_ReadWriteByte(U8 channel,U8 TxData)
{
	U16 data=0;
 	if(channel == 1)
    {
        data=SPI1_ReadWriteByte(TxData);
    }
    else if(channel == 2)
    {
    }
    else
    {
    }
	return data;
}


