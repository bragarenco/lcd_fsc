/*
 * main.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */
#include <avr/io.h>
#include "display_drv.h"
#include "display_timer.h"


int main(void){


	init_Display();
	Init_DisplayTimer();
	Init_TimeBase();

	DDRD |=   1<<PD6;

	sei();
	while(1){
		DelayMs(500);
		DriveDemo();
		//PORTD++;

	}
}
