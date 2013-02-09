/*
 * diplay_drv.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#include "display_drv.h"

#define DISPLAY_TAB_SIZE 64
#define DISPLAY_COM_1 63
#define DISPLAY_COM_2 29
#define CV 0x00
//char display_tab[DISPLAY_TAB_SIZE] = {
//		1,1,1,1,1,1,1,1,				//0..7
//		1,1,1,1,1,1,1,1,			    //8..15
//		1,1,1,1,1,1,1,1,				//16..23
//		1,1,1,1,1,CV,1,1,				//24..31
//		1,1,1,1,1,1,1,1,				//32..39
//		1,1,1,1,1,1,1,1,				//40..47
//		1,1,1,1,1,1,1,1,				//48..53
//		1,1,1,1,1,1,1,CV				//56..63
//};
char display_tab[DISPLAY_TAB_SIZE] = {
		7,4,4,7,7,7,7,7,				//0..7
		1,2,3,4,5,6,7,7,			    //8..15
		1,2,3,4,5,6,7,7,				//16..23
		1,1,7,2,2,CV,5,7,				//24..31
		7,1,2,3,4,5,6,7,				//32..39
		7,1,2,3,4,5,6,7,				//40..47
		2,2,2,2,4,4,4,4,				//48..53
		1,1,1,1,1,1,3,CV				//56..63
};


#define COLOR_BLUE  0x01 << 0
#define COLOR_RED   0x01 << 1
#define COLOR_GREEN 0x01 << 2

char trig_flag = 0 ;
char current_collor = COLOR_BLUE;
char gpio_collor = 1<<_BLUE_GPIO_BIT_;
char color_periods = 0;

#define PERIOFS_TO_LIGHT 3


void init_Display(void){
	spi_Init();
	init_ColorPin();
}

#define FIRST_POS_RUN	33
#define LAST_POS_RUN	45

#define SLOW_POS	60
char slow_cnt = 0;

#define FIRST_POS_BAR	47
#define LAST_POS_BAR	59

int bar_cnt=(FIRST_POS_BAR+LAST_POS_BAR)/2;
char up_down_bar = 1;

void DriveDemo(void){
	int i;

	// running ligts demo
	char temp = display_tab[FIRST_POS_RUN];
	for (i = FIRST_POS_RUN; i < LAST_POS_RUN; i++) {
		display_tab[i]=display_tab[i+1];
	}
	display_tab[LAST_POS_RUN]=temp;

	slow_cnt++;
	display_tab[SLOW_POS] = slow_cnt>>1;

	// Bar demo
	if(up_down_bar){
		if(++bar_cnt>LAST_POS_BAR)
			up_down_bar=0;
		else
			display_tab[bar_cnt]^=0x80;

	}else{
		if(--bar_cnt<FIRST_POS_BAR)
			up_down_bar=1;
		else
			display_tab[bar_cnt]^=0x80;

	}

}



void drive_Display(void){


	int i = DISPLAY_TAB_SIZE - 1;
	char byte_to_send = 0;
	char current_byte = 0;

//char byte_count = 0;
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

//			byte_count = (byte_count+1)&0x07;

			byte_to_send = 0;
		}

	}while(--i>=0);

	led_ColorOff();
	display_Delay(2);
	spi_OutEnable(1);
	display_Delay(2);
	led_ColorSet(gpio_collor);

	if (trig_flag) {

		switch (current_collor) {
		case COLOR_BLUE:
					gpio_collor = 1 << _BLUE_GPIO_BIT_;
				if (++color_periods >= PERIOFS_TO_LIGHT) {
					current_collor = COLOR_RED;
					color_periods = 0;
				}
			break;
		case COLOR_RED:
					gpio_collor = 1 << _RED_GPIO_BIT_;
				if (++color_periods >= PERIOFS_TO_LIGHT) {
					current_collor = COLOR_GREEN;
					color_periods = 0;
				}
			break;
		case COLOR_GREEN:
					gpio_collor = 1 << _GREEN_GPIO_BIT_;
				if (++color_periods >= PERIOFS_TO_LIGHT) {
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
