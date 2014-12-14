#include "tim4.h"

U32 TIM4_COUNT;
U32	TIM4_INTERRUPT_TIME;

void TIM4_InterruptInit(U32 time)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /*设置1ms 进入一次定时器溢出中跺*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1;		/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);	/* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    NVIC_PriorityGroupConfig(Devices_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM4_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM4_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);			 /* 清除溢出中断标志 */
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);							/* 开启时钟 */

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , DISABLE);		/*先关闭等待使用*/
	TIM4_COUNT=0;
	TIM4_INTERRUPT_TIME=time;
}


void TIM4_StartTime(void)
{
    TIM4_COUNT=0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_StopTime(void)
{
    TIM_Cmd(TIM4, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , DISABLE);
}

void TIM4_SetTimeCount(U32 count)
{
	TIM4_COUNT=count;
}

U32 TIM4_GetTimCount(void)
{
	return TIM4_COUNT; 
}
void TIM4_TimeCountAdd(void)
{
	TIM4_COUNT++;
}

void TIM4_SetTimeInterruptISR(TimerISRFunc fp)
{
    TIM4_ISR_HANDLER = fp;
}

U32 TIM4_GetInterruptTime(void)
{
	return TIM4_INTERRUPT_TIME;
}


