/*
 * spi.h
 *
 *  Created on: Nov 22, 2020
 *      Author: MahmoudH
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f4xx.h"
#include "timer.h"
#include "delay.h"

typedef enum{
	MASTER_MODE, SLAVE_MODE
}SPI_Mode;

void SPI2_Init(SPI_Mode mode);
uint8_t SPI_Tranceive(uint8_t data);

#endif /* INC_SPI_H_ */
