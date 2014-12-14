#include "LED.h"

void LED_DriverInit(U8 ledx)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if(ledx&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED1_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED1_Pin;
    GPIO_Init(LED1_Port, &GPIO_InitStructure);
    }

    if((ledx>>1)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED2_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED2_Pin;
    GPIO_Init(LED2_Port, &GPIO_InitStructure);
    }

    if((ledx>>2)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED3_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED3_Pin;
    GPIO_Init(LED3_Port, &GPIO_InitStructure);
    }

    if((ledx>>3)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED4_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED4_Pin;
    GPIO_Init(LED4_Port, &GPIO_InitStructure);
    }


    if((ledx>>5)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED5_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED5_Pin;
    GPIO_Init(LED5_Port, &GPIO_InitStructure);
    }

    if((ledx>>5)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED6_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED6_Pin;
    GPIO_Init(LED6_Port, &GPIO_InitStructure);
    }

    if((ledx>>6)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED7_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED7_Pin;
    GPIO_Init(LED7_Port, &GPIO_InitStructure);
    }

    if((ledx>>7)&0x01!=0x00)
    {
    RCC_APB2PeriphClockCmd(LED8_RCC_APB2Periph, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED8_Pin;
    GPIO_Init(LED8_Port, &GPIO_InitStructure);
    }

}

void LED_ON(U8 ledx)
{
    if(ledx&0x01!=0x00)
    {
    GPIO_ResetBits(LED1_Port, LED1_Pin);
    }
    
    if((ledx>>1)&0x01!=0x00)
    {
    GPIO_ResetBits(LED2_Port, LED2_Pin);
    }

    if((ledx>>2)&0x01!=0x00)
    {
    GPIO_ResetBits(LED3_Port, LED3_Pin);
    }

    if((ledx>>3)&0x01!=0x00)
    {
    GPIO_ResetBits(LED4_Port, LED4_Pin);
    }

    if((ledx>>4)&0x01!=0x00)
    {
    GPIO_ResetBits(LED5_Port, LED5_Pin);
    }

    if((ledx>>5)&0x01!=0x00)
    {
    GPIO_ResetBits(LED6_Port, LED6_Pin);
    }

    if((ledx>>6)&0x01!=0x00)
    {
    GPIO_ResetBits(LED7_Port, LED7_Pin);
    }

    if((ledx>>7)&0x01!=0x00)
    {
    GPIO_ResetBits(LED8_Port, LED8_Pin);
    }
}

void LED_OFF(U8 ledx)
{
    if(ledx&0x01!=0x00)
    {
    GPIO_SetBits(LED1_Port, LED1_Pin);
    }
    
    if((ledx>>1)&0x01!=0x00)
    {
    GPIO_SetBits(LED2_Port, LED2_Pin);
    }

    if((ledx>>2)&0x01!=0x00)
    {
    GPIO_SetBits(LED3_Port, LED3_Pin);
    }

    if((ledx>>3)&0x01!=0x00)
    {
    GPIO_SetBits(LED4_Port, LED4_Pin);
    }

    if((ledx>>4)&0x01!=0x00)
    {
    GPIO_SetBits(LED5_Port, LED5_Pin);
    }

    if((ledx>>5)&0x01!=0x00)
    {
    GPIO_SetBits(LED6_Port, LED6_Pin);
    }

    if((ledx>>6)&0x01!=0x00)
    {
    GPIO_SetBits(LED7_Port, LED7_Pin);
    }

    if((ledx>>7)&0x01!=0x00)
    {
    GPIO_SetBits(LED8_Port, LED8_Pin);
    }
}

void LED_Change(U8 ledx)
{
    U8 LED_State;

    if(ledx&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED1_Port, LED1_Pin);
        if(LED_State == 1)
        {
            GPIO_ResetBits(LED1_Port, LED1_Pin);
        }
        else
        {
            GPIO_SetBits(LED1_Port, LED1_Pin);
        }
    }
    
    if((ledx>>1)&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED2_Port, LED2_Pin);
        if(LED_State == 1)
        {
            GPIO_ResetBits(LED2_Port, LED2_Pin);
        }
        else
        {
            GPIO_SetBits(LED2_Port, LED2_Pin);
        }
    }

    if((ledx>>2)&0x01!=0x00)
    {
       LED_State = GPIO_ReadOutputDataBit(LED3_Port, LED3_Pin);
    if(LED_State == 1)
    {
        GPIO_ResetBits(LED3_Port, LED3_Pin);
    }
    else
    {
        GPIO_SetBits(LED3_Port, LED3_Pin);
    }
    }

    if((ledx>>3)&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED4_Port, LED4_Pin);
    if(LED_State == 1)
    {
        GPIO_ResetBits(LED4_Port, LED4_Pin);
    }
    else
    {
        GPIO_SetBits(LED4_Port, LED4_Pin);
    }
    }

    if((ledx>>4)&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED5_Port, LED5_Pin);
        if(LED_State == 1)
        {
        GPIO_ResetBits(LED5_Port, LED5_Pin);
        }
        else
        {
        GPIO_SetBits(LED5_Port, LED5_Pin);
        }
    }

    if((ledx>>5)&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED6_Port, LED6_Pin);
        if(LED_State == 1)
        {
            GPIO_ResetBits(LED6_Port, LED6_Pin);
        }
        else
        {
            GPIO_SetBits(LED6_Port, LED6_Pin);
        }
    }

    if((ledx>>6)&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED7_Port, LED7_Pin);
        if(LED_State == 1)
        {
            GPIO_ResetBits(LED7_Port, LED7_Pin);
        }
        else
        {
            GPIO_SetBits(LED7_Port, LED7_Pin);
        }
    }

    if((ledx>>7)&0x01!=0x00)
    {
        LED_State = GPIO_ReadOutputDataBit(LED8_Port, LED8_Pin);
        if(LED_State == 1)
        {
            GPIO_ResetBits(LED8_Port, LED8_Pin);
        }
        else
        {
         GPIO_SetBits(LED8_Port, LED8_Pin);
        }
    }

}
