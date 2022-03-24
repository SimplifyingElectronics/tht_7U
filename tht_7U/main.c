/*
 * tht_7U.c
 *
 * Created: 24-03-2022 21:47:37
 * Author : GUNJAN
 */ 

#include <avr/io.h>
#include "spi.h"
#include "max.h"
#include "define.h"

int main(void)
{
	spi_init_master();
	MAX31865_RTD_configure(True, True, False, False, MAX31865_FAULT_DETECTION_NONE, True, True, 0x0000, 0x00ff);
    /* Replace with your application code */
    while (1) 
    {
    }
}

