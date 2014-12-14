#ifndef _PINCFGMAP_H
#define _PINCFGMAP_H

#include "stm32f10x.h"
///////////////////////////////////////////////////////////////////////UART1
#define UART1_Port				GPIOA
#define UART1_RCC_APB2Periph		RCC_APB2Periph_GPIOA
#define UART1_Tx_Pin				GPIO_Pin_9
#define UART1_Tx_PinSource		GPIO_PinSource9
#define UART1_Rx_Pin				GPIO_Pin_10
#define UART1_Rx_PinSource		GPIO_PinSource10

///////////////////////////////////////////////////////////////////////UART2
#define UART2_Port				GPIOA
#define UART2_RCC_APB2Periph		RCC_APB2Periph_GPIOA
#define UART2_Tx_Pin				GPIO_Pin_2
#define UART2_Tx_PinSource		GPIO_PinSource2
#define UART2_Rx_Pin				GPIO_Pin_3
#define UART2_Rx_PinSource		GPIO_PinSource3

///////////////////////////////////////////////////////////////////////UART3
#define UART3_Port				GPIOB
#define UART3_RCC_APB2Periph		RCC_APB2Periph_GPIOB
#define UART3_Tx_Pin				GPIO_Pin_10
#define UART3_Tx_PinSource		GPIO_PinSource10
#define UART3_Rx_Pin				GPIO_Pin_11
#define UART3_Rx_PinSource		GPIO_PinSource11

///////////////////////////////////////////////////////////////////////UART4
#define UART4_Port				GPIOC
#define UART4_RCC_APB2Periph		RCC_APB2Periph_GPIOC
#define UART4_Tx_Pin				GPIO_Pin_10
#define UART4_Tx_PinSource		GPIO_PinSource10
#define UART4_Rx_Pin				GPIO_Pin_11
#define UART4_Rx_PinSource		GPIO_PinSource11

///////////////////////////////////////////////////////////////////////UART6
#define UART6_Port				GPIOG
#define UART6_RCC_APB2Periph		RCC_APB2Periph_GPIOG
#define UART6_Tx_Pin				GPIO_Pin_14
#define UART6_Tx_PinSource		GPIO_PinSource14
#define UART6_Rx_Pin				GPIO_Pin_9
#define UART6_Rx_PinSource		GPIO_PinSource9

/*LED½Ó¿ÚÒý½Å*/
///////////////////////////////////////////////////////////////////////LED1
#define LED1_Port					GPIOB
#define LED1_Pin					GPIO_Pin_5
#define LED1_RCC_APB2Periph		RCC_APB2Periph_GPIOB
///////////////////////////////////////////////////////////////////////LED2
#define LED2_Port					GPIOB
#define LED2_Pin					GPIO_Pin_6
#define LED2_RCC_APB2Periph		RCC_APB2Periph_GPIOB
///////////////////////////////////////////////////////////////////////LED3
#define LED3_Port					GPIOB
#define LED3_Pin					GPIO_Pin_7
#define LED3_RCC_APB2Periph		RCC_APB2Periph_GPIOB
///////////////////////////////////////////////////////////////////////LED4
#define LED4_Port					GPIOC
#define LED4_Pin					GPIO_Pin_11
#define LED4_RCC_APB2Periph		RCC_APB2Periph_GPIOC
///////////////////////////////////////////////////////////////////////LED5
#define LED5_Port					GPIOC
#define LED5_Pin					GPIO_Pin_12
#define LED5_RCC_APB2Periph		RCC_APB2Periph_GPIOC
///////////////////////////////////////////////////////////////////////LED6
#define LED6_Port					GPIOC
#define LED6_Pin					GPIO_Pin_13
#define LED6_RCC_APB2Periph		RCC_APB2Periph_GPIOC
///////////////////////////////////////////////////////////////////////LED7
#define LED7_Port					GPIOC
#define LED7_Pin					GPIO_Pin_14
#define LED7_RCC_APB2Periph		RCC_APB2Periph_GPIOC
///////////////////////////////////////////////////////////////////////LED7
#define LED8_Port					GPIOC
#define LED8_Pin					GPIO_Pin_14
#define LED8_RCC_APB2Periph		RCC_APB2Periph_GPIOC


//////////////////////////////////////////////////////////////////////SWITCH
#define SWITCH_Port				GPIOB
#define SWITCH_Pin				GPIO_Pin_12
#define SWITCH_RCC_APB2Periph	RCC_APB2Periph_GPIOB
#define SWITCH_PinSource		EXTI_PinSource12
#define SWITCH_PortSource		EXTI_PortSourceGPIOB


///////////////////////////////////////////////////////////////////////SPI1
#define SPI1_CS1_Port				GPIOC
#define SPI1_CS1_Pin				GPIO_Pin_7
#define SPI1_CS1_RCC_APB2Periph		RCC_APB2Periph_GPIOC

#define SPI1_CS2_Port				GPIOC
#define SPI1_CS2_Pin				GPIO_Pin_6
#define SPI1_CS2_RCC_APB2Periph		RCC_APB2Periph_GPIOC

#define SPI1_CS3_Port				GPIOC
#define SPI1_CS3_Pin				GPIO_Pin_2
#define SPI1_CS3_RCC_APB2Periph		RCC_APB2Periph_GPIOC

#define SPI1_CS4_Port				GPIOC
#define SPI1_CS4_Pin				GPIO_Pin_9
#define SPI1_CS4_RCC_APB2Periph		RCC_APB2Periph_GPIOC

#define SPI1_CS5_Port				GPIOC
#define SPI1_CS5_Pin				GPIO_Pin_4
#define SPI1_CS5_RCC_APB2Periph		RCC_APB2Periph_GPIOC

#define SPI1_CS6_Port				GPIOC
#define SPI1_CS6_Pin				GPIO_Pin_5
#define SPI1_CS6_RCC_APB2Periph		RCC_APB2Periph_GPIOC


#define SPI1_RCC_APB2Periph   	       	 RCC_APB2Periph_GPIOA

#define SPI1_SCK_Pin                     GPIO_Pin_5
#define SPI1_SCK_Port             	     GPIOA
#define SPI1_SCK_PinSource               GPIO_PinSource5
#define SPI1_SCK_AF                    	 GPIO_AF_SPI1

#define SPI1_MISO_Pin                    GPIO_Pin_6
#define SPI1_MISO_Port           		 GPIOA
#define SPI1_MISO_PinSource              GPIO_PinSource6
#define SPI1_MISO_AF                   	GPIO_AF_SPI1


#define SPI1_MOSI_Pin                	GPIO_Pin_7
#define SPI1_MOSI_Port            		GPIOA
#define SPI1_MOSI_PinSource              GPIO_PinSource7
#define SPI1_MOSI_AF                   	GPIO_AF_SPI1



///////////////////////////////////////////////////////////////////////SPI2
#define SPI2_CS1_Port				GPIOA
#define SPI2_CS1_Pin					GPIO_Pin_15
#define SPI2_CS1_RCC_AHBPeriph		RCC_AHB1Periph_GPIOA

#define SPI2_CS2_Port				GPIOG
#define SPI2_CS2_Pin					GPIO_Pin_4
#define SPI2_CS2_RCC_AHBPeriph		RCC_AHB1Periph_GPIOG

#define SPI2_RCC_AHBPeriph   	       		RCC_APB1Periph_SPI2

#define SPI2_SCK_Pin                   		GPIO_Pin_13
#define SPI2_SCK_Port             			GPIOB
#define SPI2_SCK_RCC_AHBPeriph          RCC_AHB1Periph_GPIOB
#define SPI2_SCK_PinSource               	GPIO_PinSource13
#define SPI2_SCK_AF                    		GPIO_AF_SPI2

#define SPI2_MISO_Pin                     	GPIO_Pin_14
#define SPI2_MISO_Port           			GPIOB
#define SPI2_MISO_RCC_AHBPeriph        RCC_AHB1Periph_GPIOB
#define SPI2_MISO_PinSource               	GPIO_PinSource14
#define SPI2_MISO_AF                   		GPIO_AF_SPI2

#define SPI2_MOSI_Pin                		GPIO_Pin_15
#define SPI2_MOSI_Port            		GPIOB
#define SPI2_MOSI_RCC_AHBPeriph        RCC_AHB1Periph_GPIOB
#define SPI2_MOSI_PinSource               	GPIO_PinSource15
#define SPI2_MOSI_AF                   		GPIO_AF_SPI2



///////////////////////////////////////////////////////////////////////SPI3
#define SPI3_CS1_Port				GPIOB
#define SPI3_CS1_Pin					GPIO_Pin_12
#define SPI3_CS1_RCC_AHBPeriph		RCC_AHB1Periph_GPIOB

#define SPI3_RCC_AHBPeriph   	       		RCC_APB1Periph_SPI3

#define SPI3_SCK_Pin                   		GPIO_Pin_10
#define SPI3_SCK_Port             			GPIOC
#define SPI3_SCK_RCC_AHBPeriph          RCC_AHB1Periph_GPIOC
#define SPI3_SCK_PinSource               	GPIO_PinSource10
#define SPI3_SCK_AF                    		GPIO_AF_SPI3

#define SPI3_MISO_Pin                     	GPIO_Pin_11
#define SPI3_MISO_Port           			GPIOC
#define SPI3_MISO_RCC_AHBPeriph        RCC_AHB1Periph_GPIOC
#define SPI3_MISO_PinSource               	GPIO_PinSource11
#define SPI3_MISO_AF                   		GPIO_AF_SPI3

#define SPI3_MOSI_Pin                		GPIO_Pin_12
#define SPI3_MOSI_Port            		GPIOC
#define SPI3_MOSI_RCC_AHBPeriph        RCC_AHB1Periph_GPIOC
#define SPI3_MOSI_PinSource               	GPIO_PinSource12
#define SPI3_MOSI_AF                   		GPIO_AF_SPI3

#endif

