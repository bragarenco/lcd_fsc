/*
 * display_spi.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */


#include "display_spi.h"

void spi_Init(){
	_SPI_CONFIG_SCLK_PIN_AS_OUTPUT();
	_SPI_CONFIG_DO_PIN_AS_OUTPUT();
	_CONFIG_LATCH_PIN_AS_OUTPUT();

}

void spi_Transfer(unsigned char data)
{
	USIDR = data;

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

	USICR = (1 << USIWM0) | (1 << USITC);
	USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);

}

void spi_OutEnable(char pulseWidth){
	_DRIVE_LATCH_HIGH();
	for(int i = 0; i < pulseWidth; i++)
		asm("nop");
	_DRIVE_LATCH_LOW();

}
void display_Delay(char pulseWidth){
	for(int i = 0; i < pulseWidth; i++)
		asm("nop");
}
