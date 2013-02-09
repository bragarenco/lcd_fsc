/*
 * display_timer.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#ifndef DISPLAY_TIMER_H_
#define DISPLAY_TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define PRESCALER0    256

#if(PRESCALER0 == 1)
	#define F_TIMER0 (0<<CS02) | (0<<CS01) | (1<<CS00);
#elif(PRESCALER0 == 8)
	#define F_TIMER0 (0<<CS02) | (1<<CS01) | (0<<CS00);
#elif(PRESCALER0 == 64)
	#define F_TIMER0 (0<<CS02) | (1<<CS01) | (1<<CS00);
#elif(PRESCALER0 == 256)
	#define F_TIMER0 (1<<CS02) | (0<<CS01) | (0<<CS00);
#elif(PRESCALER0 == 1024)
	#define F_TIMER0 (1<<CS02) | (0<<CS01) | (1<<CS00);
#else
	#define F_TIMER0 0
	#error TIMER0 prescaler not supported
#endif

#ifndef F_OVF0_200
#define F_OVF0_200   195	// Timer0 overflow frequency - 200 Hz
#define F_OVF0_1000	 225	// Timer0 overflow frequency -   1 KHz
#endif

#define OVF0_ON() TIMSK |= 1<<TOIE0
#define OVF0_OFF() TIMSK &= ~(1<<TOIE0)

void Init_DisplayTimer();
void display_Delay(char pulseWidth);

void DelayMs(unsigned int time_to_wait);
void Init_TimeBase();

#endif /* DISPLAY_TIMER_H_ */
