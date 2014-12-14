#ifndef _TIM4_H
#define _TIM4_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "ISRHandler.h"

#define TIM4_ISR_HANDLER 		ISRHandler.Timer4

void TIM4_InterruptInit(U32 time);
void TIM4_StartTime(void);
void TIM4_StopTime(void);
void TIM4_SetTimeCount(U32 count);
U32 TIM4_GetTimCount(void);
void TIM4_TimeCountAdd(void);
void TIM4_SetTimeInterruptISR(TimerISRFunc fp);
U32 TIM4_GetInterruptTime(void);

#endif

