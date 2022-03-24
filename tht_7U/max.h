/*
 * max.h
 *
 * Created: 24-03-2022 21:48:50
 *  Author: GUNJAN
 */ 
#include <avr/io.h>

#ifndef MAX_H_
#define MAX_H_

#define MAX31865_FAULT_DETECTION_NONE					(0x00 <<2)

void MAX31865_RTD_configure(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, uint8_t, uint8_t, uint16_t, uint16_t);
void MAX31865_RTD_reconfigure(uint8_t);
uint8_t status(void);
uint16_t resistance(void);
uint16_t high_threshold(void);
uint16_t low_threshold(void);

uint8_t configure_control_bits;
uint16_t configure_low_threshold;
uint16_t configure_high_threshold;
uint8_t measured_configuration;
uint16_t measured_resistance;
uint16_t measured_high_threshold;
uint16_t measured_low_threshold;
uint8_t measured_status;

#endif /* MAX_H_ */