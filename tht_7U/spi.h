/*
 * spi.h
 *
 * Created: 24-03-2022 21:48:40
 *  Author: GUNJAN
 */ 


#ifndef SPI_H_
#define SPI_H_

void spi_init_master(void);
void spi_transmit(uint8_t);
uint8_t spi_tranciever(uint8_t);


#endif /* SPI_H_ */