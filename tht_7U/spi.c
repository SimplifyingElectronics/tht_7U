/*
 * spi.c
 *
 * Created: 24-03-2022 21:48:13
 *  Author: GUNJAN
 */ 
#include <avr/io.h>
#include "spi.h"

void SPI_Init()								/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);		/* Make MOSI, SCK, SS as Output pin */
	DDRB &= ~(1<<MISO);						/* Make MISO pin as input pin */
	PORTB |= (1<<SS);						/* Make high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI in master mode with Fosc/16 */
	SPSR &= ~(1<<SPI2X);					/* Disable speed doubler */
}

void SPI_Write(char data)		/* SPI write data function */
{
	char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}
char SPI_Read()					/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);				/* Return received data */
}
void spi_init_master(void)
{
	/* Slave select as PA4 and PB0 */
	DDRA |= (1<<0);
	DDRB |= (1<<4);
	
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
	return (SPDR);
}