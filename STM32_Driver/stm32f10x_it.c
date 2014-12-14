/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "TypeDef.h"
#include "ISRHandler.h"

extern void TimingDelay_Decrement(void);

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void USART1_IRQHandler(void)
{
    U8 data;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) //判断为接收中断
    {
        data = USART_ReceiveData(USART1);
        if(ISRHandler.UART1Rx != 0x00)
        {
            ISRHandler.UART1Rx(data);
        }
    }
    if (USART_GetITStatus(USART1, USART_IT_TXE) == SET) //判断为发送中断
    {
        if(ISRHandler.UART1Tx != 0x00)
        {
            if(ISRHandler.UART1Tx(&data) == TRUE)
            {
                USART_SendData(USART1, data);
            }
            else
            {
                USART_ITConfig(USART1, USART_IT_TXE, DISABLE);							  //使能中断

            }
        }
    }

}

void USART2_IRQHandler(void)
{
    U8 data;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //判断为接收中断
    {
        data = USART_ReceiveData(USART2);
        if(ISRHandler.UART2Rx != 0x00)
        {
            ISRHandler.UART2Rx(data);
        }
    }
    if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) //判断为发送中断
    {
        if(ISRHandler.UART2Tx != 0x00)
        {
            if(ISRHandler.UART2Tx(&data) == TRUE)
            {
                USART_SendData(USART2, data);

            }
            else
                USART_ITConfig(USART2, USART_IT_TXE, DISABLE);							  //使能中断
        }
    }

}

void USART3_IRQHandler(void)
{
    U8 data;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //判断为接收中断
    {

        data = USART_ReceiveData(USART3);
        if(ISRHandler.UART3Rx != 0x00)
        {
            ISRHandler.UART3Rx(data);
        }
    }
    if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET) //判断为发送中断
    {
        if(ISRHandler.UART3Tx != 0x00)
        {
            if(ISRHandler.UART3Tx(&data) == TRUE)
            {
                USART_SendData(USART3, data);

            }
            else
                USART_ITConfig(USART3, USART_IT_TXE, DISABLE);                            //使能中断
        }
    }
}

void UART4_IRQHandler(void)
{
    U8 data;
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //判断为接收中断
    {
        data = USART_ReceiveData(UART4);
        if(ISRHandler.UART4Rx != 0x00)
        {
            ISRHandler.UART4Rx(data);
        }
    }
    if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET) //判断为发送中断
    {
        if(ISRHandler.UART4Tx != 0x00)
        {
            if(ISRHandler.UART4Tx(&data) == TRUE)
            {
                USART_SendData(UART4, data);

            }
            else
                USART_ITConfig(UART4, USART_IT_TXE, DISABLE);                            //使能中断
        }
    }
}

void TIM2_IRQHandler(void)
{
    if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET )
    {
        TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
        TIM2_TimeCountAdd();
        if((TIM2_GetTimCount())>= (TIM2_GetInterruptTime()))
        {
            TIM2_SetTimeCount(0);;
            ISRHandler.Timer2();
        }
    }
}

void TIM3_IRQHandler(void)
{
    if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET )
    {
        TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);
        TIM3_TimeCountAdd();
        if((TIM3_GetTimCount()) >= (TIM2_GetInterruptTime()))
        {
            TIM3_SetTimeCount(0);
            ISRHandler.Timer3();
        }
    }
}

void TIM4_IRQHandler(void)
{
    if ( TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET )
    {
        TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
        TIM4_TimeCountAdd();
        if((TIM4_GetTimCount()) >= (TIM4_GetInterruptTime()))
        {
            TIM4_SetTimeCount(0);
            ISRHandler.Timer4();
        }
    }
}


/*void PPP_IRQHandler(void)
{
}*/


/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
