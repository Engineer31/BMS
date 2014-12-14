#include "UART1.h"
#include <stdio.h>

#include "PinCfgMap.h"

U8 Rx_Data[512];
U8 Rx_Data_Count;
typedef bool (*GetByteFunc)(byte *data);

void UART1_SetRxISRFunc(UARTRxISRFunc fp);

void UART1_SetTxISRFunc(UARTTxISRFunc fp);

bool UART1_TxDequeue(byte *data);
void UART1_RxData(byte data);

////////////////////////////////////////////////////硬件平台初始化
void UART1_HardwareInit(u32 baudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(UART1_RCC_APB2Periph, ENABLE);    //使能GPIO

    GPIO_InitStructure.GPIO_Pin = UART1_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART1_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = UART1_Rx_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(UART1_Port, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ClockStructInit(&USART_ClockInitStruct);    //之前没有填入缺省值，是不行的
    USART_ClockInit(USART1, &USART_ClockInitStruct);

    // Configure one bit for preemption priority
    NVIC_PriorityGroupConfig(Devices_PriorityGroup);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART1_PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART1_SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                            //使能中断

    USART_Cmd(USART1, ENABLE);

    //装载发送中断
    UART1_SetTxISRFunc(UART1_TxDequeue);	//存入发送队列

	//装载接收中断
	UART1_SetRxISRFunc(UART1_RxData);	//存入接收队列
}

void UART1_SetBaudRate(u32 baudRate)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baudRate;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
}

void UART1_IntTxByte(GetByteFunc fP)
{
    byte data;
    if( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET)
    {
        fP(&data);
        USART_SendData(USART1, data);
        USART_ITConfig(USART1, USART_IT_TXE, ENABLE);                            //使能中断
    }
}

/////////////////////////////////////////以下是与硬件平台无关的代码

QueueStruct UART1TxQueue; //串口发送队列
QueueStruct UART1RxQueue; //串口接收队列

void UART1_TxQueueInit(U16 length)
{
    QueueInit(&UART1TxQueue, length);
}

void UART1_RxDataInit(U16 length)
{
	Rx_Data_Count=5;
}

QueueStruct *UART1_GetTxQueue(void)
{
    return &UART1TxQueue;
}

QueueStruct *UART1_GetRxQueue(void)
{
    return &UART1RxQueue;
}

bool UART1_TxDequeue(byte *data)
{

    return (ByteDequeue(&UART1TxQueue, data));
}

void UART1_RxData(byte data)
{
	 Rx_Data[Rx_Data_Count]=data;
	 Rx_Data_Count++;
}

bool UART1_TxBytes(U8 *data, U16 length)
{
    bool flag = FALSE;
    //	U16 i;
    //	byte temp;
    if(length == 0)
        return FALSE;
    flag = BytesEnqueue(&UART1TxQueue, data, length);
    if(flag == TRUE)
        UART1_IntTxByte(UART1_TxDequeue);
    return TRUE;
}

void UART1_SetRxISRFunc(UARTRxISRFunc fp)
{
    UART1_RX_ISR_HANDLER = fp;
}

void UART1_SetTxISRFunc(UARTTxISRFunc fp)
{
    UART1_TX_ISR_HANDLER = fp;
}

