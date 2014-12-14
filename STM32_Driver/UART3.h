#ifndef __UART3_H
#define __UART3_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "ISRHandler.h"
#include "Queue.h"

#define UART3_RX_ISR_HANDLER 		ISRHandler.UART3Rx
#define UART3_TX_ISR_HANDLER 		ISRHandler.UART3Tx


extern void UART3_HardwareInit(u32 baudRate);

extern void UART3_SetBaudRate(u32 baudRate);

extern void UART3_TxQueueInit(U16 length);

extern QueueStruct *UART3_GetTxQueue(void);

extern bool UART3_TxBytes(byte *data, U16 length);

extern void UART3_SetRxISRFunc(UARTRxISRFunc fp);

#endif

