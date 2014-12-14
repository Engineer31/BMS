#include "tim3.h"

U32 TIM3_COUNT;
U32 TIM3_INTERRUPT_TIME;

void TIM3_InterruptInit(U32 time)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /*设置1ms 进入一次定时器溢出中跺*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;		/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);	/* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    NVIC_PriorityGroupConfig(Devices_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM3_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM3_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);			 /* 清除溢出中断标志 */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);							/* 开启时钟 */

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , DISABLE);		/*先关闭等待使用*/
	TIM3_COUNT=0;
	TIM3_INTERRUPT_TIME=time;
}


void TIM3_StartTime(void)
{
    TIM3_COUNT=0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

void TIM3_StopTime(void)
{
    TIM_Cmd(TIM3, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , DISABLE);
}

void TIM3_SetTimeCount(U32 count)
{
	TIM3_COUNT=count;
}

U32 TIM3_GetTimCount(void)
{
	return TIM3_COUNT; 
}

void TIM3_TimeCountAdd(void)
{
	TIM3_COUNT++;
}


void TIM3_SetTimeInterruptISR(TimerISRFunc fp)
{
    TIM3_ISR_HANDLER = fp;
}

U32 TIM3_GetInterruptTime(void)
{
	return TIM3_INTERRUPT_TIME;
}
