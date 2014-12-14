#ifndef _UART1_H
#define _UART1_H

#include"stm32f10x.h"
#include"TypeDef.h"
#include"ISRHandler.h"
#include"Queue.h"

#define UART1_RX_ISR_HANDLER 		ISRHandler.UART1Rx
#define UART1_TX_ISR_HANDLER 		ISRHandler.UART1Tx

#define BUF_SIZE  512

extern void UART1_HardwareInit(u32 baudRate);

extern void UART1_SetBaudRate(u32 baudRate);

extern void UART1_TxQueueInit(U16 length);

extern void UART1_RxDataInit(U16 length);

extern QueueStruct *UART1_GetTxQueue(void);

extern QueueStruct *UART1_GetRxQueue(void);//获取数据接收队列

extern bool UART1_TxBytes(byte *data, U16 length);

extern void UART1_SetRxISRFunc(UARTRxISRFunc fp);

#endif
