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

void display_Delay(char delayWidth){
	for(int i = 0; i < delayWidth; i++)
		asm("nop");
}


/*---------------------------- Timer1 Overflow Interruppt ----------------------------*/

void Init_TimeBase() {
	TCNT1 = 0xFFFF - 20;
	TCCR1B = (0<<CS02) | (0<<CS01) | (1<<CS00);
	TIMSK |= 1<<TOIE1;
}

volatile unsigned long current_time_ms = 0;
void IncTimer(void);

ISR(TIMER1_OVF_vect) {
	TCNT1 = 0xFFFF - (F_CPU/1000);
	IncTimer();
	current_time_ms++;
}

volatile int ms_timer_count=0;
volatile char sec_l = 0;
volatile char sec_h = 0;
volatile char min_l = 0;
volatile char min_h = 0;

void IncTimer(void) {
	if (++ms_timer_count > 999) {
		ms_timer_count = 0;
		if (++sec_l > 9) {
			sec_l = 0;
			if (++sec_h > 5) {
				sec_h = 0;
				if (++min_l > 9) {
					min_l = 0;
					if (++min_h > 5) {
						min_h = 0;
					}
				}
			}
		}
	}
}



void DelayMs(unsigned int time_to_wait){
	unsigned long start_time = current_time_ms;
	while(current_time_ms - start_time < time_to_wait){
		asm("nop");
	}
}
