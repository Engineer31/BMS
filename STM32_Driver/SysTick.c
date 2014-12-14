#include "SysTick.h"

vu32 TimingDelay;

void SysTick_Init()
{
    /* SystemFrequency / 1000    1ms中断一次
     * SystemFrequency / 100000	 10us中断一次
     * SystemFrequency / 1000000 1us中断一次
     */
    if (SysTick_Config(SystemCoreClock / 1000000))
    {
        /* Capture error */
        while (1);
    }
    // 关闭滴答定时器
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;

    NVIC_SetPriority(SysTick_IRQn, 0x0);//SysTick中断优先级设置
}


/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,1us为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  :外部调用
 */
void Delay_us(vu32 nTime)
{

    TimingDelay = nTime;

    // 使能滴答定时器
    SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

    while(TimingDelay != 0);

}

 /*
 * 函数名：Delay_ms
 * 描述  ：ms延时程序,1ms为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  :外部调用
 */
void Delay_ms(vu32 nTime)
{
    u32 i;

    for(i=0;i<nTime;i++)
    {
        Delay_us(1000);
    }
}

 /*
 * 函数名：Delay_s
 * 描述  ：s延时程序,1s为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  :外部调用
 */
void Delay_s(vu32 nTime)
{
    u32 i;

    for(i=0;i<nTime;i++)
    {
        Delay_ms(1000);
    }
}

/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}
