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


