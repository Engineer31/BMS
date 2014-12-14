/*******************************************************************************
* 文件名	: ADS8341.c
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 10/13/2014
* 描述		: 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "ADS8341.h"

/* Function ------------------------------------------------------------------*/
void ADS8341_Init(void)
{
	ADS8341_CS_INIT;
	ADS8341_CS_HIGH;
	SPI_DriverInit(ADS8341_SPI_CHANNEL);
}

U16 ADS8341_GetChannelData(U8 ch)
{
    U8 temp[3];
	U16 data;

    ADS8341_CS_LOW;
    Delay_us(30);
    if(ch == 1)
    {
        SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0x94);
    }
    else if(ch == 2)
    {
        SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0xD4);
    }
    else if(ch == 3)
    {
        SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0xA4);
    }
    else if(ch == 4)
    {
        SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0xE4);
    }
    else
    {
        return 0;
    }

    temp[0] = SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0x00);
    temp[1] = SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0x00);
    temp[2] = SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0x00);
    SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0xff);
    SPI_ReadWriteByte(ADS8341_SPI_CHANNEL,0xff);

    ADS8341_CS_HIGH;

	if((temp[0]>>15)==0x01 || (temp[1]>>15)==0x01 || (temp[2]>>15)==0x01)
	{
		data=0xFFFF;
	}
	else
	{
	data=ADS8341_VREF*(((u32)(temp[0])) << 9 | ((u32)(temp[1])) << 1 | temp[2] >> 7)/(1<<16);
	}

    return data;
}

/*****************************END OF FILE**************************************/
