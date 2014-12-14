#include "tim2.h"

U32 TIM2_COUNT;
U32 TIM2_INTERRUPT_TIME;
U32 TIM2_HANDLER_COUNT;	   //中断函数调用次数

void TIM2_InterruptInit(U32 time)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /*设置1ms 进入一次定时器溢出中跺*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;		/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);	/* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    NVIC_PriorityGroupConfig(Devices_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM2_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM2_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);			 /* 清除溢出中断标志 */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);							/* 开启时钟 */

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/
	TIM2_COUNT=0;
	TIM2_INTERRUPT_TIME=time;
	TIM2_HANDLER_COUNT=0;
}


void TIM2_StartTime(void)
{
    TIM2_COUNT = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_StopTime(void)
{
    TIM_Cmd(TIM2, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);
}

void TIM2_SetTimeCount(U32 count)
{
	TIM2_COUNT=count;
}

U32 TIM2_GetTimCount(void)
{
	return TIM2_COUNT; 
}

void TIM2_SetHandlerCount(U32 count)
{
	TIM2_HANDLER_COUNT=count;
}

U32 TIM2_GetHandlerCount(void)
{
	return TIM2_HANDLER_COUNT; 
}

void TIM2_AddHandlerCount(void)
{
	TIM2_HANDLER_COUNT++;
}

void TIM2_TimeCountAdd(void)
{
	TIM2_COUNT++;
}

void TIM2_SetTimeInterruptISR(TimerISRFunc fp)
{
    TIM2_ISR_HANDLER = fp;
}

U32 TIM2_GetInterruptTime(void)
{
	return TIM2_INTERRUPT_TIME;
}
