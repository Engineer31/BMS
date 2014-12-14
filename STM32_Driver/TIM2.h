#ifndef _TIM2_H
#define _TIM2_H

#include "stm32f10x.h"
#include "ISRHandler.h"

#define TIM2_ISR_HANDLER 		ISRHandler.Timer2

void TIM2_InterruptInit(U32 time);
void TIM2_StartTime(void);
void TIM2_StopTime(void);
void TIM2_SetTimeCount(U32 count);
U32 TIM2_GetTimCount(void);
void TIM2_TimeCountAdd(void);
void TIM2_SetTimeInterruptISR(TimerISRFunc fp);
U32 TIM2_GetInterruptTime(void);

U32 TIM2_GetHandlerCount(void);

void TIM2_AddHandlerCount(void);

void TIM2_TimeCountAdd(void);

#endif
