#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include "usart.h"

static int usart_putchar(char c, FILE *fp);

/* Stream init for printf  */
FILE usart_str = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

FILE * USART_Init(uint16_t bauds){
	UBRR0H = (uint8_t) (bauds >> 8);
	UBRR0L = bauds;

	/* Disable double speed  */
	UCSR0A = 0;
	/* Enable TX and RX */
	UCSR0B = (1 << TXEN0);
	/* Asynchronous mode:
	 * - 8 data bits
	 * - 1 stop bit
	 * - no parity 	 */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    return &usart_str;
}

static int usart_putchar(char c, FILE *fp) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
	return 0;
}

