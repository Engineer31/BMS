
#include "UART2.h"
#include <stdio.h>
#include "PinCfgMap.h"


typedef bool (*GetByteFunc)(byte *data);

void UART2_SetRxISRFunc(UARTRxISRFunc fp);

void UART2_SetTxISRFunc(UARTTxISRFunc fp);

bool UART2_TxDequeue(byte *data);

////////////////////////////////////////////////////硬件平台初始化

void UART2_HardwareInit(u32 baudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(UART2_RCC_APB2Periph, ENABLE);

    GPIO_InitStructure.GPIO_Pin = UART2_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART2_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = UART2_Rx_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(UART2_Port, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ClockStructInit(&USART_ClockInitStruct);    //之前没有填入缺省值，是不行的
    USART_ClockInit(USART2, &USART_ClockInitStruct);

    //Configure one bit for preemption priority
    //NVIC_PriorityGroupConfig(UART2_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART2_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART2_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2, ENABLE);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                            //使能中断

    //装载发送中断
    UART2_SetTxISRFunc(UART2_TxDequeue);
}
////////////////////////////////////////////////////硬件平台初始化


void UART2_SetBaudRate(u32 baudRate)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
}

void UART2_IntTxByte(GetByteFunc fP)
{
    byte data;
    if( USART_GetFlagStatus(USART2, USART_FLAG_TXE) == SET)
    {
        fP(&data);
        USART_SendData(USART2, data);
        USART_ITConfig(USART2, USART_IT_TXE, ENABLE);                            //使能中断
    }
}

/////////////////////////////////////////以下是与硬件平台无关的代码

QueueStruct UART2TxQueue;

void UART2_TxQueueInit(U16 length)
{
    QueueInit(&UART2TxQueue, length);
}

QueueStruct *UART2_GetTxQueue(void)
{
    return &UART2TxQueue;
}

bool UART2_TxDequeue(byte *data)
{
    return (ByteDequeue(&UART2TxQueue, data));
}

bool UART2_TxBytes(byte *data, U16 length)
{
    bool flag = FALSE;
    //	U16 i;
    //	byte temp;
    if(length == 0)
        return FALSE;
    flag = BytesEnqueue(&UART2TxQueue, data, length);
    if(flag == TRUE)
        UART2_IntTxByte(UART2_TxDequeue);
    return TRUE;
}

void UART2_SetRxISRFunc(UARTRxISRFunc fp)
{
    UART2_RX_ISR_HANDLER = fp;
}

void UART2_SetTxISRFunc(UARTTxISRFunc fp)
{
    UART2_TX_ISR_HANDLER = fp;
}

