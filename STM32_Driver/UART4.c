
#include "UART4.h"
#include <stdio.h>
#include "PinCfgMap.h"

typedef bool (*GetByteFunc)(byte *data);

void UART4_SetRxISRFunc(UARTRxISRFunc fp);

void UART4_SetTxISRFunc(UARTTxISRFunc fp);

bool UART4_TxDequeue(byte *data);

////////////////////////////////////////////////////硬件平台初始化

void UART4_HardwareInit(u32 baudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB2PeriphClockCmd(UART4_RCC_APB2Periph, ENABLE);

    GPIO_InitStructure.GPIO_Pin = UART4_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART4_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = UART4_Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(UART4_Port, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART4, &USART_InitStructure);

    USART_ClockStructInit(&USART_ClockInitStruct);	  //之前没有填入缺省值，是不行的
    USART_ClockInit(UART4, &USART_ClockInitStruct);

    /* Configure one bit for preemption priority */
    //NVIC_PriorityGroupConfig(UART4_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART4_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART4_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    USART_Cmd(UART4, ENABLE);

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);                            //使能中断

    //装载发送中断
    UART4_SetTxISRFunc(UART4_TxDequeue);
}

void UART4_SetBaudRate(u32 baudRate)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART4, &USART_InitStructure);
}

void UART4_IntTxByte(GetByteFunc fP)
{
    byte data;
    if( USART_GetFlagStatus(UART4, USART_FLAG_TXE) == SET)
    {
        fP(&data);
        USART_SendData(UART4, data);
        USART_ITConfig(UART4, USART_IT_TXE, ENABLE);                            //使能中断
    }
}

/////////////////////////////////////////以下是与硬件平台无关的代码

QueueStruct UART4TxQueue;

void UART4_TxQueueInit(U16 length)
{
    QueueInit(&UART4TxQueue, length);
}

QueueStruct *UART4_GetTxQueue(void)
{
    return &UART4TxQueue;
}

bool UART4_TxDequeue(byte *data)
{

    return (ByteDequeue(&UART4TxQueue, data));
}

bool UART4_TxBytes(byte *data, U16 length)
{
    bool flag = FALSE;
    //	U16 i;
    //	byte temp;
    if(length == 0)
        return FALSE;
    flag = BytesEnqueue(&UART4TxQueue, data, length);
    if(flag == TRUE)
        UART4_IntTxByte(UART4_TxDequeue);
    return TRUE;
}

void UART4_SetRxISRFunc(UARTRxISRFunc fp)
{
    UART4_RX_ISR_HANDLER = fp;
}

void UART4_SetTxISRFunc(UARTTxISRFunc fp)
{
    UART4_TX_ISR_HANDLER = fp;
}

