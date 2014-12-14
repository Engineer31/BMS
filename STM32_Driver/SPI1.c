#include "SPI1.h"

void SPI1_HardwareInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | SPI1_RCC_APB2Periph , ENABLE);

    //	RCC_APB2PeriphClockCmd(SPI1_CS1_RCC_APB2Periph | SPI1_CS2_RCC_APB2Periph |SPI1_CS3_RCC_APB2Periph |
    //	SPI1_CS4_RCC_APB2Periph |SPI1_CS5_RCC_APB2Periph |SPI1_CS6_RCC_APB2Periph ,ENABLE);
    RCC_APB2PeriphClockCmd(SPI1_CS1_RCC_APB2Periph | SPI1_CS2_RCC_APB2Periph | SPI1_CS3_RCC_APB2Periph
                           | SPI1_CS4_RCC_APB2Periph | SPI1_CS5_RCC_APB2Periph | SPI1_CS6_RCC_APB2Periph, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //CS1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_CS1_Pin;
    GPIO_Init(SPI1_CS1_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //CS2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_CS2_Pin;
    GPIO_Init(SPI1_CS2_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				 //CS3
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_CS3_Pin;
    GPIO_Init(SPI1_CS3_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//CS4
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_CS4_Pin;
    GPIO_Init(SPI1_CS4_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//CS5
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_CS5_Pin;
    GPIO_Init(SPI1_CS5_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				 //CS6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_CS6_Pin;
    GPIO_Init(SPI1_CS6_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_SCK_Pin;
    GPIO_Init(SPI1_SCK_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_Pin;
    GPIO_Init(SPI1_MOSI_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = SPI1_MISO_Pin;
    GPIO_Init(SPI1_MISO_Port, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;					 //
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);

}



void delay1(u16 ms)
{
    u8 i;
    while(ms--)
    {
        for(i = 0; i < 250; i++);
    }
}

void SPI1_WriteByte(U8 TxData)
{ 
    U16 retry = 0;

    //	delay1(30);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0) 
    { 
    ;
    } //等待发送数据寄存器空
    retry = 0;
    SPI_I2S_SendData(SPI1, TxData);
}

U8 SPI1_ReadByte(void)
{ 
    U32 cnt=0;	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == 0)
    {
    	if((cnt++)>10000000)  
            return 0;
    }
	
	return SPI_I2S_ReceiveData(SPI1);
}

U8 SPI1_ReadWriteByte(U8 TxData)
{
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0)  
	{
		;
	}
    SPI_I2S_SendData(SPI1, TxData);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == 0)
	{
		;
	}
    return SPI_I2S_ReceiveData(SPI1);

}

void SPI1_SetCS(U8 cs_number, U8 state)
{
    if(cs_number == 1)
    {
        if(state == 0)
        {
            GPIO_ResetBits(SPI1_CS1_Port, SPI1_CS1_Pin);
        }
        else
        {
            GPIO_SetBits(SPI1_CS1_Port, SPI1_CS1_Pin);
        }
    }
    else if(cs_number == 2)
    {
        if(state == 0)
        {
            GPIO_ResetBits(SPI1_CS2_Port, SPI1_CS2_Pin);
        }
        else
        {
            GPIO_SetBits(SPI1_CS2_Port, SPI1_CS2_Pin);
        }
    }
    else if(cs_number == 3)
    {
        if(state == 0)
        {
            GPIO_ResetBits(SPI1_CS3_Port, SPI1_CS3_Pin);
        }
        else
        {
            GPIO_SetBits(SPI1_CS3_Port, SPI1_CS3_Pin);
        }
    }
    else if(cs_number == 4)
    {
        if(state == 0)
        {
            GPIO_ResetBits(SPI1_CS4_Port, SPI1_CS4_Pin);
        }
        else
        {
            GPIO_SetBits(SPI1_CS4_Port, SPI1_CS4_Pin);
        }
    }
    else if(cs_number == 5)
    {
        if(state == 0)
        {
            GPIO_ResetBits(SPI1_CS5_Port, SPI1_CS5_Pin);
        }
        else
        {
            GPIO_SetBits(SPI1_CS5_Port, SPI1_CS5_Pin);
        }
    }
    else if(cs_number == 6)
    {
        if(state == 0)
        {
            GPIO_ResetBits(SPI1_CS6_Port, SPI1_CS6_Pin);
        }
        else
        {
            GPIO_SetBits(SPI1_CS6_Port, SPI1_CS6_Pin);
        }
    }
    else
    {
    }


}
