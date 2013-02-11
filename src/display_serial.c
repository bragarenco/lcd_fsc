/*
 * display_serial.c
 *
 *  Created on: Feb 11, 2013
 *      Author: Radu
 */

#include "display_serial.h"

unsigned char rx_Pack[7];	// receive data buffer
unsigned char tx_Pack[1];	// transmit data buffer

/*-------------------------- SERIAL Receiver Interrupt --------------------------*/

ISR(USART_RX_vect)
{

	unsigned char *curent_Pos = rx_Pack + 6;
	unsigned char *next_Pos = rx_Pack + 7;
	unsigned char counter = 6;

	/* shift receive buffer */
	do{
		*--next_Pos = *--curent_Pos;
	} while(counter--);

	/* read UART Data Register */
	rx_Pack[0] = UDR;

	/* check for start bit, stop bit and check sum */
	if((rx_Pack[6] ==  0x02) && (rx_Pack[0] == 0x03)){
		print_Char(0xDD);
		/* check for sum */
		if(get_Sum(rx_Pack) == rx_Pack[1]){
			print_Char(0xDD);
//			print_String("OK!");
		}
			//command_Interpreter(rx_Pack);
	}

}

/*---------------------------- Check for Sum Function -------------------------*/

unsigned int get_Sum(unsigned char *pack){

	register char counter = 4;
	register char sum = 0;

	pack = pack + 2;

	/* check for sum */
	do{
		sum = sum + *pack++;
	} while(--counter);

	return sum;

}

/*------------------------- SERIAL Print Char Function -------------------------*/

void print_Char(unsigned char data){

	/* wait for empty transmit buffer */
	while(!(UCSRA & (1 << UDRE)));
		/* put data into buffer, sends the data */
		UDR = data;

}

/*------------------------ SERIAL Print String Function -----------------------*/

void print_String(char *string){

	for(int i = 0; i < sizeof (string); i++)
		print_Char(*string++);

}

/*------------------------- Command Interpreter Function -----------------------*/

void command_Interpreter(unsigned char *pack){

	switch(pack[4]){

		case SET:	print_String("OK!");
					break;

		case CLEAR: print_String("OK!");
					break;

		case WRITE: print_String("OK!");
					break;

		case READ: 	print_String("OK!");
					break;

		case DEMO: 	print_String("OK!");
					break;

		default: break;

	}

}

//////////////////////////////////////////////////////////////////////////////////
