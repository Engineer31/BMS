#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);

void Delay_us(vu32 nTime);
void Delay_ms(vu32 nTime);
void Delay_s(vu32 nTime);


#endif
