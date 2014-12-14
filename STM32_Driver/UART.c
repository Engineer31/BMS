#include "UART.h"

void UART_DriverInit(U8 uart_channel, U32 baudRate, U16 txBufLength)

{
	if(uart_channel==1)
	{
		UART1_HardwareInit(baudRate);
		UART1_TxQueueInit(txBufLength);
		UART1_RxDataInit(txBufLength);	 //
	}
	else if(uart_channel==2)
	{
		UART2_HardwareInit(baudRate);
		UART2_TxQueueInit(txBufLength);
	}
	else if(uart_channel==3)
	{
		UART3_HardwareInit(baudRate);
		UART3_TxQueueInit(txBufLength);
	}
	else if(uart_channel==4)
	{
		UART4_HardwareInit(baudRate);
		UART4_TxQueueInit(txBufLength);
	}
	else
	{
	}
}

void UART_Write(U8 uart_channel,U8 *data, U16 length)
{
	if(uart_channel==1)
	{
		UART1_TxBytes(data, length);
	}
	else if(uart_channel==2)
	{
		UART2_TxBytes(data, length);
	}
	else if(uart_channel==3)
	{
		UART3_TxBytes(data, length);
	}
	else if(uart_channel==4)
	{
		UART4_TxBytes(data,length);
	}
	else
	{
	}
}

void UART_SetRxISRFunc(U8 uart_channel,UARTRxISRFunc fp)
{
	if(uart_channel==1)
	{
		UART1_SetRxISRFunc(fp);
	}
	else if(uart_channel==2)
	{
		UART2_SetRxISRFunc(fp);
	}
	else if(uart_channel==3)
	{
		UART3_SetRxISRFunc(fp);
	}
	else if(uart_channel==4)
	{
		UART4_SetRxISRFunc(fp);
	}
	else
	{
	}
}

