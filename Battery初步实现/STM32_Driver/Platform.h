#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "stm32f10x.h"
#include "TypeDef.h"

typedef GPIO_TypeDef* PORT;     
typedef U16           PIN;

#define ADS8341_SPI    SPI1
#define ADS8341_CS     SPI1_CS1

#endif
