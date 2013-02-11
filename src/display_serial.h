/*
 * display_serial.h
 *
 *  Created on: Feb 11, 2013
 *      Author: Radu
 */

#ifndef DISPLAY_SERIAL_H_
#define DISPLAY_SERIAL_H_

#include "avr/io.h"
#include <avr/interrupt.h>

/*------------------------- Command Definition ----------------------------*/

#define SET		0x0A
#define CLEAR	0x0B
#define WRITE	0x0C
#define READ	0x0D
#define DEMO	0x0E

/*------------------------- SERIAL Configuration -------------------------*/

/* Receive enable, Transmit enable, 8 bit, 1 stop bit */
#define Init_UART(baud){											\
		UBRRH = (unsigned char) (baud >> 8);/*((F_CPU / (16 * baud) - 1) >> 8);	*/\
		UBRRL = (unsigned char) (baud);								\
		UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);			\
		UCSRC = (0 << USBS)|(3 << UCSZ0);							\
}

/* Prototypes functions*/
void print_Char(unsigned char data);
void print_String(char *string);
unsigned int get_Sum(unsigned char *pack);
void command_Interpreter(unsigned char *recive_Pack);

#endif /* DISPLAY_SERIAL_H_ */

/////////////////////////////////////////////////////////////////////////////
