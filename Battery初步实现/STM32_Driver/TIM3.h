#ifndef _TIM3_H
#define _TIM3_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "ISRHandler.h"

#define TIM3_ISR_HANDLER 		ISRHandler.Timer3

void TIM3_InterruptInit(U32 time);
void TIM3_StartTime(void);
void TIM3_StopTime(void);
void TIM3_SetTimeCount(U32 count);
U32 TIM3_GetTimCount(void);
void TIM3_TimeCountAdd(void);
void TIM3_SetTimeInterruptISR(TimerISRFunc fp);	  
U32 TIM3_GetInterruptTime(void);

#endif
