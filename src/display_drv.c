/*
 * diplay_drv.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#include "display_drv.h"


char display_tab[DISPLAY_TAB_SIZE] = {
		// 7 segment
		0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x11,				//0..7
		0x11,0x11,0x11,0x11,0x11,0x11,0x33,0x22,			    //8..15
		0x22,0x22,0x22,0x22,0x22,0x22,0x44,0x44,				//16..23
		0x44,0x44,0x44,0x44,0x44, CV ,0x55,0x66,				//24..31
		// bar
		0x77,0x11,0x33,0x22,0x66,0x44,0x55,0x77,				//32..39
		0x01,0x03,0x02,0x06,0x04,0x05,0x07,0x22,				//40..47
		0x22,0x22,0x22,0x22,0x44,0x44,0x44,0x44,				//48..53
		0x11,0x11,0x11,0x11,0x77,0x55,0x66, CV					//56..63
};



char trig_flag = 0 ;
char color_set_flag = 0;
char current_collor = COLOR_BLUE;

char gpio_collor = 1<<_BLUE_GPIO_BIT_;
char color_periods = 0;

#define PERIODS_TO_LIGHT 3


void init_Display(void){
	spi_Init();
	init_ColorPin();
}



void drive_Display(void){

	register int i = DISPLAY_TAB_SIZE - 1;
	register char byte_to_send = 0;
	register char current_byte = 0;




	do{
		// extract byte
		current_byte = display_tab[i];

		byte_to_send<<=1;
		if (~current_byte & 0x80) {		// check if disabled

			if(color_set_flag)
				current_byte>>=4;

			if (current_byte & current_collor) {
				byte_to_send |= 0x01;
			}
		}
		if((i&7) == 0){
			if(trig_flag)
				byte_to_send^=0xFF;

			spi_Transfer(byte_to_send);

			byte_to_send = 0;
		}

	}while(--i>=0);

	if(color_set_flag){
		color_set_flag = 0;
	}else{
		color_set_flag = 1;
	}


	led_ColorOff();
	display_Delay(2);
	spi_OutEnable();
//	display_Delay(2);
	led_ColorSet(gpio_collor);

	if (trig_flag) {

		switch (current_collor) {
		case COLOR_BLUE:
					gpio_collor = 1 << _BLUE_GPIO_BIT_;
				if (++color_periods >= PERIODS_TO_LIGHT) {
					current_collor = COLOR_RED;
					color_periods = 0;
				}
			break;
		case COLOR_RED:
					gpio_collor = 1 << _RED_GPIO_BIT_;
				if (++color_periods >= PERIODS_TO_LIGHT) {
					current_collor = COLOR_GREEN;
					color_periods = 0;
				}
			break;
		case COLOR_GREEN:
					gpio_collor = 1 << _GREEN_GPIO_BIT_;
				if (++color_periods >= PERIODS_TO_LIGHT) {
					current_collor = COLOR_BLUE;
					color_periods = 0;
				}
			break;
		default:
			current_collor = COLOR_RED;
			break;
		}

		PORTD |= 1 << PD6;
		trig_flag = 0;
	}else{
		PORTD &= ~(1<<PD6);
		trig_flag = 1;
	}

}
