#ifndef _TEST_H
#define _TEST_H
#include"Stm32_Driver.h"
#include"stdio.h"

#ifdef __GNUC__																	//´®¿Úprintf
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#endif
