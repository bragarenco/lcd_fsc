/*
 * diplay_drv.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#include "display_drv.h"


char display_tab[DISPLAY_TAB_SIZE] = {
		// 7 segment
		7,7,7,7,7,7,7,1,				//0..7
		1,1,1,1,1,1,3,2,			    //8..15
		2,2,2,2,2,2,4,4,				//16..23
		4,4,4,4,4,CV,5,6,				//24..31
		// bar
		7,1,3,2,6,4,5,7,				//32..39
		1,3,2,6,4,5,7,2,				//40..47
		2,2,2,2,4,4,4,4,				//48..53
		1,1,1,1,7,5,6,CV				//56..63
};



char trig_flag = 0 ;
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
		if(~current_byte&0x80){		// check if disabled
		if(current_byte & current_collor){
			byte_to_send|=0x01;
		}
		}
		if((i&7) == 0){
			if(trig_flag)
				byte_to_send^=0xFF;

			spi_Transfer(byte_to_send);

			byte_to_send = 0;
		}

	}while(--i>=0);

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
