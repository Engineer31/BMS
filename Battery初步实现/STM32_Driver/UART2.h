#ifndef __UART2_H
#define __UART2_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "ISRHandler.h"
#include "Queue.h"

#define UART2_RX_ISR_HANDLER 		ISRHandler.UART2Rx
#define UART2_TX_ISR_HANDLER 		ISRHandler.UART2Tx


extern void UART2_HardwareInit(u32 baudRate);

extern void UART2_SetBaudRate(u32 baudRate);

extern void UART2_TxQueueInit(U16 length);

extern QueueStruct *UART2_GetTxQueue(void);

extern bool UART2_TxBytes(byte *data, U16 length);

extern void UART2_SetRxISRFunc(UARTRxISRFunc fp);

#endif

