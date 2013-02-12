/*
 * display_drv.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#ifndef DISPLAY_DRV_H_
#define DISPLAY_DRV_H_

#include "display_color.h"
#include "display_spi.h"
#include "display_timer.h"



#define DISPLAY_TAB_SIZE 64

#define DE_LOGO_POS			32
#define FSEU_LOGO_POS		60
#define LEFT_UNHAPPY_POS	30
#define LEFT_HAPPY_POS		31
#define RIGHT_UNHAPPY_POS	61
#define RIGHT_HAPPY_POS		62
#define COM_1_POS 			63
#define COM_2_POS 			29

#define SEG_POS_0 			0
#define SEG_POS_1			7
#define SEPARATOR_POS 		14
#define SEG_POS_2 			15
#define SEG_POS_3 			22

#define CV 0x00

#define COLOR_BLUE  0x01 << 0
#define COLOR_RED   0x01 << 1
#define COLOR_GREEN 0x01 << 2

//#define COLOR_CYAN  		COLOR_GREEN	| COLOR_BLUE
//#define COLOR_YELOW  		COLOR_GREEN	| COLOR_RED
//#define COLOR_MAGENTA 	COLOR_RED	| COLOR_BLUE

void init_Display(void);
void drive_Display(void);


#endif /* DISPLAY_DRV_H_ */
