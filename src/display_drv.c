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


#define COLOR_BLUE  0x01 << 0
#define COLOR_RED   0x01 << 1
#define COLOR_GREEN 0x01 << 2

char trig_flag = 0 ;
char current_collor = COLOR_BLUE;
char gpio_collor = 1<<_BLUE_GPIO_BIT_;
char color_periods = 0;

#define PERIODS_TO_LIGHT 3


void init_Display(void){
	spi_Init();
	init_ColorPin();
}

#define FIRST_POS_RUN	33
#define LAST_POS_RUN	46

#define DE_LOGO_POS	32
#define FSEU_LOGO_POS	60
char slow_cnt = 0;

#define FIRST_POS_BAR	47 //47
#define LAST_POS_BAR	59

int bar_cnt = FIRST_POS_BAR-1;//(FIRST_POS_BAR+LAST_POS_BAR)/2;
char up_down_bar = 1;

#define LEFT_UNHAPPY_POS	30
#define LEFT_HAPPY_POS		31
#define RIGHT_UNHAPPY_POS	61
#define RIGHT_HAPPY_POS		62

void DriveDemo(void){
	int i;

	// running ligts demo
	register char temp = display_tab[FIRST_POS_RUN];
	for (i = FIRST_POS_RUN; i < LAST_POS_RUN; i++) {
		display_tab[i]=display_tab[i+1];
	}
	display_tab[LAST_POS_RUN]=temp;

	slow_cnt++;
	display_tab[FSEU_LOGO_POS] = slow_cnt>>1;
	//display_tab[DE_LOGO_POS] = slow_cnt>>2;

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


void Set7SegValue(char value, int pos){
	register int i;
	for (i = pos; i < pos+7; i++) {
		if (value & 0x01)
			display_tab[i]&=~0x80;
		else
			display_tab[i]|=0x80;
		value>>=1;

	}
}


#define SEPARATOR_POS 14
#define SEG_POS_0 0
#define SEG_POS_1 7
#define SEG_POS_2 15
#define SEG_POS_3 22
#define SEG_CHAR_0 0b1011111
#define SEG_CHAR_1 0b0000110
#define SEG_CHAR_2 0b0111011
#define SEG_CHAR_3 0b0101111
#define SEG_CHAR_4 0b1100110
#define SEG_CHAR_5 0b1101101
#define SEG_CHAR_6 0b1111101
#define SEG_CHAR_7 0b0000111
#define SEG_CHAR_8 0b1111111
#define SEG_CHAR_9 0b1101111
#define SEG_NONE   0b0100000



char ValTo7Seg(char val){

	if (val == 0 ) return SEG_CHAR_0;
	else if (val == 1 )	return SEG_CHAR_1;
	else if (val == 2 )	return SEG_CHAR_2;
	else if (val == 3 )	return SEG_CHAR_3;
	else if (val == 4 )	return SEG_CHAR_4;
	else if (val == 5 )	return SEG_CHAR_5;
	else if (val == 6 )	return SEG_CHAR_6;
	else if (val == 7 )	return SEG_CHAR_7;
	else if (val == 8 )	return SEG_CHAR_8;
	else if (val == 9 )	return SEG_CHAR_9;
	else return SEG_NONE;

//	switch (val) {
//	case 0: return SEG_CHAR_0;
//	case 1:	return SEG_CHAR_1;
//	case 2:	return SEG_CHAR_2;
//	case 3:	return SEG_CHAR_3;
//	case 4:	return SEG_CHAR_4;
//	case 5:	return SEG_CHAR_5;
//	case 6:	return SEG_CHAR_6;
//	case 7:	return SEG_CHAR_7;
//	case 8:	return SEG_CHAR_8;
//	case 9:	return SEG_CHAR_9;
//	default:return SEG_NONE;
//	}
}

extern volatile unsigned long current_time_ms;
//extern volatile char ms_timer_count;

extern volatile char sec_l;
extern volatile char sec_h;
extern volatile char min_l;
extern volatile char min_h;


void UpdateTimer(void) {

//if (ms_timer_count > 500) {
	if ((current_time_ms / 500) & 0x01) {
		display_tab[SEPARATOR_POS] |= 0x80;
	} else {
		display_tab[SEPARATOR_POS] &= ~0x80;
	}

	Set7SegValue(ValTo7Seg(sec_l), SEG_POS_0);
	Set7SegValue(ValTo7Seg(sec_h), SEG_POS_1);
	Set7SegValue(ValTo7Seg(min_l), SEG_POS_2);
	Set7SegValue(ValTo7Seg(min_h), SEG_POS_3);

	if ((current_time_ms / 500) & 0x01) {
		display_tab[LEFT_UNHAPPY_POS] |= 0x80;
		display_tab[LEFT_HAPPY_POS] &= ~0x80;
		display_tab[RIGHT_UNHAPPY_POS] |= 0x80;
		display_tab[RIGHT_HAPPY_POS] &= ~0x80;
	} else {
		display_tab[LEFT_UNHAPPY_POS] &= ~0x80;
		display_tab[LEFT_HAPPY_POS] |= 0x80;
		display_tab[RIGHT_UNHAPPY_POS] &= ~0x80;
		display_tab[RIGHT_HAPPY_POS] |= 0x80;	}

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
