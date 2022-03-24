/*
 * spi.c
 *
 * Created: 24-03-2022 21:48:13
 *  Author: GUNJAN
 */ 
#include <avr/io.h>
#include "spi.h"

void spi_init_master(void)
{
	/* Slave select as PA4 and PB0 */
	DDRA |= (1<<4);
	DDRB |= (1<<0);
	
	/* MOSI and clock as output */
	DDRB |= ((1<<5) | (1<<7));
	
	/* SPI init */
	SPCR |= ((1<<SPE) | (1<<MSTR) | (1<<CPHA) | (1<<SPR0));
	
	/* Disable interrupt */
	SPSR &= ~(1<<SPI2X);
}

void spi_transmit(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t spi_tranciever(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
	/* return data register */
	return(SPDR);
}