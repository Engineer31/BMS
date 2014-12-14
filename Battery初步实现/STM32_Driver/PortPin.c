#include "PortPin.h"

void PortPin_Init(PORT port,PIN pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	if(port==GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(port==GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(port==GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if(port==GPIOD)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if(port==GPIOE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	}
	else if(port==GPIOF)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	else
	{
	}
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_Init(port, &GPIO_InitStructure);
}

void PortPin_Write(PORT port,PIN pin,U8 pin_state)
{
	if(pin_state==0)
	{
		GPIO_ResetBits(port,pin);
	}
	else
	{
		GPIO_SetBits(port,pin);
	}
}

void PortPin_Read(PORT port,PIN pin)
{

}
