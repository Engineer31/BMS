#ifndef __UART4_H
#define __UART4_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "ISRHandler.h"
#include "Queue.h"

#define UART4_RX_ISR_HANDLER 		ISRHandler.UART4Rx
#define UART4_TX_ISR_HANDLER 		ISRHandler.UART4Tx


extern void UART4_HardwareInit(u32 baudRate);

extern void UART4_SetBaudRate(u32 baudRate);

extern void UART4_TxQueueInit(U16 length);

extern QueueStruct *UART4_GetTxQueue(void);

extern bool UART4_TxBytes(byte *data, U16 length);

extern void UART4_SetRxISRFunc(UARTRxISRFunc fp);

#endif

