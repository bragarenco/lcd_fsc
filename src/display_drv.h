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


void init_Display(void);
void drive_Display(void);

void DriveDemo(void);
void UpdateTimer(void);

#endif /* DISPLAY_DRV_H_ */
