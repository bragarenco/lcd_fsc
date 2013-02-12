/*
 * main.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */
#include <avr/io.h>
#include "display_drv.h"
#include "display_serial.h"
#include "display_demo.h"


int main(void){


	init_Display();
	Init_DisplayTimer();
	Init_TimeBase();
	//Init_UART(51);

	DDRD |=   1<<PD6;

	sei();
	while(1){
		DelayMs(150);
		DriveDemo();
		UpdateTimer();
		//PORTD++;
	}
}
