/*
 * display_spi.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Andrei
 */

#ifndef DISPLAY_SPI_H_
#define DISPLAY_SPI_H_

#include "avr/io.h"


/*------------------------- SPI Configuration -----------------------------*/

/* SPI SCLK Pin Configuration */
#define _SPI_SCLK_GPIO_BIT_        			PB7
#define _SPI_CONFIG_SCLK_PIN_AS_OUTPUT()  	DDRB |= 1 << _SPI_SCLK_GPIO_BIT_

/* SPI DO Pin Configuration */
#define _SPI_DO_GPIO_BIT_        			PB6
#define _SPI_CONFIG_DO_PIN_AS_OUTPUT()  	DDRB |= 1 << _SPI_DO_GPIO_BIT_

/* SPI DI Pin Configuration */
//#define _SPI_DI_GPIO_BIT_        			PB5
//#define _SPI_CONFIG_DI_PIN_AS_INPUT()  	DDRB &=  ~BV(_SPI_DI_GPIO_BIT_)


/* LATCH Pin Configuration */
#define _LATCH_GPIO_BIT_        			PB1
#define _CONFIG_LATCH_PIN_AS_OUTPUT()  		DDRB |=	 1 << _LATCH_GPIO_BIT_
#define _DRIVE_LATCH_HIGH()     			PORTB |= 1 << _LATCH_GPIO_BIT_
#define _DRIVE_LATCH_LOW()      			PORTB &= ~ 1 << _LATCH_GPIO_BIT_

#define spi_OutEnable() 			\
	_DRIVE_LATCH_HIGH();			\
		asm("nop");					\
	_DRIVE_LATCH_LOW();				\



void spi_Transfer(unsigned char data);
void spi_Init();

#endif /* DISPLAY_SPI_H_ */
