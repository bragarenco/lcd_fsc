/*
 * display_demo.c
 *
 *  Created on: Feb 11, 2013
 *      Author: MCU-LAB2
 */

#include "display_demo.h"
#include "display_drv.h"


#define FIRST_POS_RUN	33
#define LAST_POS_RUN	46

char slow_cnt = 0;

#define FIRST_POS_BAR	47 //47
#define LAST_POS_BAR	59

int bar_cnt = FIRST_POS_BAR-1;//(FIRST_POS_BAR+LAST_POS_BAR)/2;
char up_down_bar = 1;

extern char display_tab[DISPLAY_TAB_SIZE];

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

// Timmer Demo


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


char ValTo7Seg(char val){
	switch (val) {
	case 0: return SEG_CHAR_0;
	case 1:	return SEG_CHAR_1;
	case 2:	return SEG_CHAR_2;
	case 3:	return SEG_CHAR_3;
	case 4:	return SEG_CHAR_4;
	case 5:	return SEG_CHAR_5;
	case 6:	return SEG_CHAR_6;
	case 7:	return SEG_CHAR_7;
	case 8:	return SEG_CHAR_8;
	case 9:	return SEG_CHAR_9;
	default:return SEG_NONE;
	}
}




extern volatile int ms_timer_count;
extern volatile char sec_l;
extern volatile char sec_h;
extern volatile char min_l;
extern volatile char min_h;


void UpdateTimer(void) {

	if (ms_timer_count > 500) {
		display_tab[SEPARATOR_POS] |= 0x80;
	} else {
		display_tab[SEPARATOR_POS] &= ~0x80;
	}

	Set7SegValue(ValTo7Seg(sec_l), SEG_POS_0);
	Set7SegValue(ValTo7Seg(sec_h), SEG_POS_1);
	Set7SegValue(ValTo7Seg(min_l), SEG_POS_2);
	Set7SegValue(ValTo7Seg(min_h), SEG_POS_3);

	if (ms_timer_count > 500) {
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
