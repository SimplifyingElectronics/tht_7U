/*
 * tht_7U.c
 *
 * Created: 24-03-2022 21:47:37
 * Author : GUNJAN
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "spi.h"
#include "max.h"
#include "define.h"
#include "USART.h"
#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
uint16_t r = 65;

int main(void)
{
// 	DDRA |= (1<<0);
	DDRA |= (1<<1);
	
	USART_init(115200);
 	
	spi_init_master();
	
	MAX31865_RTD_configure(True, True, False, False, MAX31865_FAULT_DETECTION_NONE, True, True, 0x0000, 0x00ff);
	
	timer2_init();
	
    /* Replace with your application code */
    while (1) 
    {
		if(fcnt_millis >= 10)
		{
			fcnt_millis = 0;
			
			PORTA ^= (1<<1);
			MAX31865_read_all();
			
			uint16_t tmp = (NTC_read_resistance() * 10);
			
			if(tmp >= 550)
			tmp = 550;
			UWriteData((tmp >> 8) & (0x00ff));
			UWriteData(tmp & (0x00ff));
		}
// 		MAX31865_read_all();
// 
// 		uint16_t tmp = (NTC_read_resistance() * 10);
// 		UWriteData((tmp >> 8) & (0x00ff));
// 		UWriteData(tmp & (0x00ff));
// 		_delay_ms(1000);

    }
}
void callback(void)
{
	
}

