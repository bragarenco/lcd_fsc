/*
 * display_timer.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#include "display_timer.h"
#include "display_drv.h"
/*---------------------------- Timer0 Overflow Interruppt ----------------------------*/

void Init_DisplayTimer() {
	TCNT0 = F_OVF0_1000;
	TCCR0B = F_TIMER0;
	TIMSK |= 1<<TOIE0;
}


ISR(TIMER0_OVF_vect) {
	TCNT0 = F_OVF0_1000;
	drive_Display();
}

void Init_TimeBase() {
	TCNT1 = 0xFFFF - 20;
	TCCR1B = (0<<CS02) | (0<<CS01) | (1<<CS00);
	TIMSK |= 1<<TOIE1;
}


volatile unsigned long current_time_ms = 0;

ISR(TIMER1_OVF_vect) {
	TCNT1 = 0xFFFF - (F_CPU/1000)/10;
	current_time_ms++;
}

void DelayMs(unsigned int time_to_wait){
	unsigned long start_time = current_time_ms;
	while(current_time_ms - start_time < time_to_wait){
		asm("nop");
	}
}
