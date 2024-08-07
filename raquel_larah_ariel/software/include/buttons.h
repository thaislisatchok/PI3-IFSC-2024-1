#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#include <stdint.h>
#include "main.h"

#define BUTTONS_UP_PORT PORTC
#define BUTTONS_UP_DDR DDRC
#define BUTTONS_UP_PINR PINC
#define BUTTONS_UP_PCMSK PCMSK1
#define BUTTONS_UP_PCICR_MASK (1 << PCIE1)
#define BUTTONS_UP_MASK (1 << PINC0)

#define BUTTONS_DW_PORT PORTC
#define BUTTONS_DW_DDR DDRC
#define BUTTONS_DW_PINR PINC
#define BUTTONS_DW_PCMSK PCMSK1
#define BUTTONS_DW_PCICR_MASK (1 << PCIE1)
#define BUTTONS_DW_MASK (1 << PINC1)

#define BUTTONS_OK_PORT PORTC
#define BUTTONS_OK_DDR DDRC
#define BUTTONS_OK_PINR PINC
#define BUTTONS_OK_PCMSK PCMSK1
#define BUTTONS_OK_PCICR_MASK (1 << PCIE1)
#define BUTTONS_OK_MASK (1 << PINC2)

#define BUTTONS_HOLD_TIME_MS 2000
#define BUTTONS_BURST_TIME_MS 1000

void buttons_Init();
uint8_t buttons_StateCall(fsm_handleType *);
uint8_t buttons_StateNext(fsm_handleType *);


#endif
