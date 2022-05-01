/*
 * max.c
 *
 * Created: 24-03-2022 21:48:25
 *  Author: GUNJAN
 */ 
#include <math.h>

#include "max.h"
#include "spi.h"
#include "define.h"
#include "USART.h"

void MAX31865_RTD_configure(uint8_t v_bias, uint8_t conversion_mode, uint8_t single_shot, uint8_t three_wire, uint16_t fault_detection, uint8_t fault_status, uint8_t filter, uint16_t low_threshold, uint16_t high_threshold)
{
	uint8_t control_bits = 0;
	control_bits |= (v_bias ? 0x80 : 0);
	control_bits |= (conversion_mode ? 0x40 : 0);
	control_bits |= (single_shot ? 0x20 : 0);
	control_bits |= (three_wire ? 0x10 : 0);
	control_bits |= (fault_detection & 0x001100);
	control_bits |= (fault_status ? 0x02 : 0);
	control_bits |= (filter ? 0x01 : 0);
	
	configure_control_bits = control_bits;
	configure_low_threshold = low_threshold;
	configure_high_threshold = high_threshold;
	
	MAX31865_RTD_reconfigure(True);
}

void MAX31865_RTD_reconfigure(uint8_t all)
{
	if(all)
	{
		uint8_t threshold = 0;
		PORTA &= ~(1<<0);
		spi_transmit(0x83);
		spi_transmit(0xff);
		spi_transmit(0xff);

// 		threshold = (uint8_t) ((configure_high_threshold >> 8) & 0xff);
// 		spi_transmit(threshold);
// 		threshold = (uint8_t) (configure_high_threshold);
// 		spi_transmit(threshold);
// 		threshold = (configure_low_threshold);
// 		spi_transmit((threshold >> 8) & 0x00ff);
// 		threshold |= (configure_low_threshold);
// 		spi_transmit((threshold) & 0x00ff);
		spi_transmit(0x00);
		spi_transmit(0x00);
		PORTA |= (1<<0);
	}
	
	PORTA &= ~(1<<0);
	spi_transmit(0x80);
	spi_transmit(configure_control_bits);
	PORTA |= (1<<0);
}

uint8_t MAX31865_read_all(void)
{
	uint16_t combined_bytes = 0;

	PORTA &= ~(1<<0);	// CS_LOW - activate slave
	
	spi_transmit(0x00);
	measured_configuration = spi_tranciever(0x00);
	
	combined_bytes = (spi_tranciever(0x00) << 8);
	combined_bytes |= (spi_tranciever(0x00));
	measured_resistance = (combined_bytes >> 1);
	
	combined_bytes = (spi_tranciever(0x00) << 8);
	combined_bytes |= (spi_tranciever(0x00));
	measured_high_threshold = combined_bytes;
	
	combined_bytes = (spi_tranciever(0x00) << 8);
	combined_bytes |= (spi_tranciever(0x00));
	measured_low_threshold = combined_bytes;
	
	measured_status = spi_tranciever(0x00);
	
	PORTA |= (1<<0);
	
	if((measured_resistance == 0) || (measured_status != 0))
	{
		MAX31865_RTD_reconfigure(True);
	}
	
	return(status());
}
float NTC_read_resistance()
{
	double logR = log(resistance());
	double logR3 = logR * logR * logR;
	double Temp = 1/(NTC_A + NTC_B * logR + NTC_C * logR3);
	return (Temp - 273.15);
}

uint8_t status(void)
{
	return(measured_status);
}

float resistance(void)
{
	return((double)measured_resistance*18000/(double)32767);
}

uint16_t high_threshold(void)
{
	return(measured_high_threshold);
}

uint16_t low_threshold(void)
{
	return(measured_low_threshold);
}

uint8_t max_spi_read(uint8_t addr){
	
	CS_PORT &= ~(CS_PIN);	// CS_LOW - activate slave
	
	SPDR = addr;				// register address to read
	while(!(SPSR & (1<<SPIF)));	// wait for complete sending

	SPDR = 0xFF;				// dummy data to provide SPI clock signals to read
	while(!(SPSR & (1<<SPIF)));	// wait for complete sending
	
	CS_PORT |= (CS_PIN);		// CS_HIGH - deactivate slave
	return SPDR;				// delete flag SPIF and return data
}