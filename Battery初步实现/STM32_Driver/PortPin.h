#ifndef PORT_PIN_H
#define PORT_PIN_H

#include "stm32f10x.h"
#include "TypeDef.h"

typedef U16 PIN;
typedef GPIO_TypeDef* PORT;

extern void PortPin_Init(PORT port,PIN pin);
extern void PortPin_Write(PORT port,PIN pin,U8 pin_state);
extern void PortPin_Read(PORT port,PIN pin);
#endif

