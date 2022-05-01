/*
 * spi.h
 *
 * Created: 24-03-2022 21:48:40
 *  Author: GUNJAN
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MOSI				(7)
#define SCK					(8)
#define SS					(5)
#define MISO				(6)

void SPI_Init(void);
void SPI_Write(char);
char SPI_Read(void);

void spi_init_master(void);
void spi_transmit(uint8_t);
uint8_t spi_tranciever(uint8_t);


#endif /* SPI_H_ */