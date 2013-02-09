/*
 * display_color.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#ifndef DISPLAY_COLOR_H_
#define DISPLAY_COLOR_H_

#include "avr/io.h"

/*-------------------------- RGB Configuration ----------------------------*/

/* RGB Port Configuration */
#define RGB_PORT 							PORTB

/* BLUE Pin Configuration */
#define _BLUE_GPIO_BIT_        				PB2
#define _CONFIG_BLUE_PIN_AS_OUTPUT()  		DDRB |= 1 << _BLUE_GPIO_BIT_

/* RED Pin Configuration */
#define _RED_GPIO_BIT_        				PB3
#define _CONFIG_RED_PIN_AS_OUTPUT()  		DDRB |= 1 << _RED_GPIO_BIT_

/* GREEN Pin Configuration */
#define _GREEN_GPIO_BIT_        			PB4
#define _CONFIG_GREEN_PIN_AS_OUTPUT()  		DDRB |=  1 <<_GREEN_GPIO_BIT_

/* COLOR BIT MASK */
#define COLOR_BIT_MASK 						((1<<PB2) | (1<<PB3) | (1<<PB4))

/* Shift value*/
#define RGB_SHIFT_VALUE						PB2

#define _DRIVE_RED_HIGH()     			PORTB |= 1 << _RED_GPIO_BIT_
#define _DRIVE_RED_LOW()      			PORTB &= ~ 1 << _RED_GPIO_BIT_


#define led_ColorOff() RGB_PORT &=~COLOR_BIT_MASK
#define led_ColorSet(colorMASK) RGB_PORT |= colorMASK

#define  init_ColorPin() \
	_CONFIG_RED_PIN_AS_OUTPUT();\
	_CONFIG_GREEN_PIN_AS_OUTPUT();\
	_CONFIG_BLUE_PIN_AS_OUTPUT();



//void init_ColorPin(void);
//void led_ColorOff(void );
//void led_ColorSet(char colorMASK );

#endif /* DISPLAY_COLOR_H_ */
