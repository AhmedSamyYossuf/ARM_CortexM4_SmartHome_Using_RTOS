/*
 * EEPROM.c
 *
 *  Created on: Nov 23, 2020
 *      Author: MahmoudH
 */

#include "EEPROM.h"

void EEPROM_Init(void){
	//I2C1_Init();
	TWI_Init();
}
void EEPROM_WriteByte(uint16_t romAddr, uint8_t dataByte){
	/* Calculate: page:3, romAddr byte:8, slave byte */
	uint8_t page 			= ((romAddr&0x7FF)>>8);
	uint8_t romAddrByte		= (uint8_t)romAddr;
	uint8_t slaveByte		= (0xA0) | (page<<1); /* default write */
	I2C1_Start();
	I2C1_WriteAddress(slaveByte);
	I2C1_WriteData(romAddrByte);
	I2C1_WriteData(dataByte);
	I2C1_Stop();
	delayMs(15);
}
void EEPROM_ReadByte(uint16_t romAddr, uint8_t* pDataByte){
	/* Calculate: page:3, romAddr byte:8, slave byte */
	uint8_t page 			= ((romAddr&0x7FF)>>8);
	uint8_t romAddrByte		= (uint8_t)romAddr;
	uint8_t slaveByte		= (0xA0) | (page<<1); /* default write */
	I2C1_Start();
	I2C1_WriteAddress(slaveByte);
	I2C1_WriteData(romAddrByte);
	I2C1_Start();
	I2C1_WriteAddress(slaveByte|1);
	(*pDataByte) = I2C1_ReadData();
	I2C1_Stop();
	delayMs(15);
}
