/*
 * EEPROM.h
 *
 *  Created on: Nov 23, 2020
 *      Author: MahmoudH
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "I2C.h"

void EEPROM_Init(void);
void EEPROM_WriteByte(uint16_t romAddr, uint8_t dataByte);
void EEPROM_ReadByte(uint16_t romAddr, uint8_t* pDataByte);


#endif /* INC_EEPROM_H_ */
