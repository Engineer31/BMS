#ifndef _UART_H
#define _UART_H

#include "stm32f10x.h"
#include "TypeDef.h"
#include "Queue.h"
#include "ISRHandler.h"
#include "UART1.h"
#include "UART2.h"
#include "UART3.h"
#include "UART4.h"


extern void UART_DriverInit(U8 uart_channel, U32 baudRate, U16 txBufLength);
extern void UART_Write(U8 uart_channel,U8 *data, U16 length);
extern void UART_SetRxISRFunc(U8 uart_channel,UARTRxISRFunc fp);

#endif

