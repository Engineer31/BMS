#include "UART3.h"
#include <stdio.h>
#include "PinCfgMap.h"


typedef bool (*GetByteFunc)(byte *data);

void UART3_SetRxISRFunc(UARTRxISRFunc fp);

void UART3_SetTxISRFunc(UARTTxISRFunc fp);

bool UART3_TxDequeue(byte *data);

////////////////////////////////////////////////////硬件平台初始化

void UART3_HardwareInit(u32 baudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(UART3_RCC_APB2Periph, ENABLE);



    /* Configure one bit for preemption priority */
    //NVIC_PriorityGroupConfig(UART3_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART3_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART3_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    GPIO_InitStructure.GPIO_Pin = UART3_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART3_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = UART3_Rx_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(UART3_Port, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ClockStructInit(&USART_ClockInitStruct);    //之前没有填入缺省值，是不行的
    USART_ClockInit(USART3, &USART_ClockInitStruct);

    USART_Cmd(USART3, ENABLE);

    //USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                            //使能中断
    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);                            //使能中断

    //USART_Cmd(USART1, ENABLE);
    //USART_ClearFlag(USART1, USART_FLAG_TC);

    //装载发送中断
    UART3_SetTxISRFunc(UART3_TxDequeue);
}

void UART3_SetBaudRate(u32 baudRate)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
}

void UART3_IntTxByte(GetByteFunc fP)
{
    byte data;
    if( USART_GetFlagStatus(USART3, USART_FLAG_TXE) == SET)
    {
        fP(&data);
        USART_SendData(USART3, data);
        USART_ITConfig(USART3, USART_IT_TXE, ENABLE);                            //使能中断
    }
}

/////////////////////////////////////////以下是与硬件平台无关的代码

QueueStruct UART3TxQueue;

void UART3_TxQueueInit(U16 length)
{
    QueueInit(&UART3TxQueue, length);
}

QueueStruct *UART3_GetTxQueue(void)
{
    return &UART3TxQueue;
}

bool UART3_TxDequeue(byte *data)
{
    return (ByteDequeue(&UART3TxQueue, data));
}

bool UART3_TxBytes(byte *data, U16 length)
{
    bool flag = FALSE;
    //	U16 i;
    //	byte temp;
    if(length == 0)
        return FALSE;
    flag = BytesEnqueue(&UART3TxQueue, data, length);
    if(flag == TRUE)
        UART3_IntTxByte(UART3_TxDequeue);
    return TRUE;
}

void UART3_SetRxISRFunc(UARTRxISRFunc fp)
{
    UART3_RX_ISR_HANDLER = fp;
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                            //使能中断
}

void UART3_SetTxISRFunc(UARTTxISRFunc fp)
{
    UART3_TX_ISR_HANDLER = fp;
}

