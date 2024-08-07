#ifndef _USART_H
#define _USART_H

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

/* Baudrates */
#define B9600  (F_CPU/16/9600-1)
#define B38400  (F_CPU/16/38400-1)
#define B57600  (F_CPU/16/57600-1)
#define B115200  (F_CPU/16/115200-1)

FILE* USART_Init(uint16_t bauds);
#endif