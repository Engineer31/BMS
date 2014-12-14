#ifndef _ISRHANDLER_H
#define _ISRHANDLER_H

#include "TypeDef.h"
#include "stm32f10x.h"

#define Devices_PriorityGroup           NVIC_PriorityGroup_3

#define UART1_PriorityGroup				NVIC_PriorityGroup_3
#define UART1_PreemptionPriority			0
#define UART1_SubPriority					0

#define UART2_PriorityGroup				NVIC_PriorityGroup_3
#define UART2_PreemptionPriority			5
#define UART2_SubPriority					0

#define UART3_PriorityGroup				NVIC_PriorityGroup_3
#define UART3_PreemptionPriority			1
#define UART3_SubPriority					0

#define UART4_PriorityGroup				NVIC_PriorityGroup_3
#define UART4_PreemptionPriority			4
#define UART4_SubPriority					0

#define TIM1_PriorityGroup				NVIC_PriorityGroup_3
#define TIM1_PreemptionPriority			    3
#define TIM1_SubPriority					0

#define TIM2_PriorityGroup				NVIC_PriorityGroup_3
#define TIM2_PreemptionPriority			    1
#define TIM2_SubPriority					0

#define TIM3_PriorityGroup				NVIC_PriorityGroup_3
#define TIM3_PreemptionPriority			    3
#define TIM3_SubPriority					0

#define TIM4_PriorityGroup				NVIC_PriorityGroup_3
#define TIM4_PreemptionPriority			    2
#define TIM4_SubPriority					0

#define EXTI10_PriorityGroup			NVIC_PriorityGroup_3
#define EXTI10_PreemptionPriority			6
#define EXTI10_SubPriority					0

//ISR 中断服务程序
//IRQ 中断请求

typedef void (*UARTRxISRFunc)(byte data);
typedef bool (*UARTTxISRFunc)(byte *data);

//typedef void (*TimerISRFunc)(U32 cnt);
typedef void (*TimerISRFunc)(void);
typedef void (*SystemTickISRFunc)(U32 cnt);
typedef void (*EXTIISRFunc)(U32 cnt);
typedef struct
{
    UARTRxISRFunc UART1Rx;
    UARTRxISRFunc UART2Rx;
    UARTRxISRFunc UART3Rx;
    UARTRxISRFunc UART4Rx;
    UARTRxISRFunc UART5Rx;
    UARTRxISRFunc UART6Rx;

    UARTTxISRFunc UART1Tx;
    UARTTxISRFunc UART2Tx;
    UARTTxISRFunc UART3Tx;
    UARTTxISRFunc UART4Tx;
    UARTTxISRFunc UART5Tx;
    UARTTxISRFunc UART6Tx;

    TimerISRFunc Timer1;
    TimerISRFunc Timer2;
    TimerISRFunc Timer3;
    TimerISRFunc Timer4;

    SystemTickISRFunc SystemTick;

    EXTIISRFunc EXTI0;
    EXTIISRFunc EXTI1;
    EXTIISRFunc EXTI10;
} ISRHandlerStruct;

extern ISRHandlerStruct ISRHandler;

extern void ISRHandler_Init(void);

#endif

