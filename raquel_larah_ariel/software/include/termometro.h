#ifndef TERMOMETRO_H_INCLUDED
#define TERMOMETRO_H_INCLUDED

#include <stdint.h>
#include <avr/io.h>

#include "main.h"

#define TERMO_PORT PORTB
#define TERMO_DDR DDRB
#define TERMO_PORTIN PINB
#define TERMO_MASK (1 << PORTB0)

extern int16_t termo_temperatura;
uint8_t termo_process(fsm_handleType *);
uint8_t termo_next(fsm_handleType *);
void termo_StartRead();

#endif
