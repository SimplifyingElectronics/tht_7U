/*
 * max.h
 *
 * Created: 24-03-2022 21:48:50
 *  Author: GUNJAN
 */ 
#include <avr/io.h>

#ifndef MAX_H_
#define MAX_H_

#define CS_PIN											(1<<0)
#define CS_PORT											PORTA
#define READ_RTD_MSB									0b00000001	// 0x01H
#define READ_RTD_LSB									0b00000010	// 0x02H
#define NTC_A											1.0263e-3
#define NTC_B											2.3520e-4
#define NTC_C											0.7427e-7
#define MAX31865_FAULT_DETECTION_NONE					( 0x00 <<2 )

void MAX31865_RTD_configure(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, uint8_t, uint8_t, uint16_t, uint16_t);
void MAX31865_RTD_reconfigure(uint8_t);
float NTC_read_resistance(void);
uint8_t status(void);
uint16_t high_threshold(void);
uint16_t low_threshold(void);
uint8_t MAX31865_read_all(void);
uint8_t status(void);
float resistance(void);
uint16_t high_threshold(void);
uint16_t low_threshold(void);
uint8_t max_spi_read(uint8_t);

uint8_t configure_control_bits;
uint16_t configure_low_threshold;
uint16_t configure_high_threshold;
uint8_t measured_configuration;
volatile uint16_t measured_resistance;
uint16_t measured_high_threshold;
uint16_t measured_low_threshold;
uint8_t measured_status;

uint8_t lsb_rtd, msb_rtd;

#endif /* MAX_H_ */