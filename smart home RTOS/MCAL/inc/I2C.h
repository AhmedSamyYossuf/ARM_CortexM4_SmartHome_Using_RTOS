/*
 * I2C.h
 *
 *  Created on: Nov 23, 2020
 *      Author: MahmoudH
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f4xx.h"
#include "timer.h"
#include "delay.h"
/* I2C1:
 * SCK: PB6
 * SDA: PB7
 * EEPROM AT24C16
 *  */
void TWI_Init(void);
void 	I2C1_Init(void);
void 	I2C1_Start(void);
void 	I2C1_Stop(void);

void 	I2C1_WriteData(uint8_t data);
void 	I2C1_WriteAddress(uint8_t addr);
uint8_t I2C1_ReadData(void);

#endif /* INC_I2C_H_ */
