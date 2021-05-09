/*
 * WIFI.h
 *
 *  Created on: Nov 24, 2020
 *      Author: MahmoudH
 */

#ifndef INC_WIFI_H_
#define INC_WIFI_H_

#include "stm32f4xx.h"
#include "uart.h"
#include "delay.h"

uint8_t WIFI_SendCmd(uint8_t* cmd, uint8_t* expResp, uint32_t timeout);

#endif /* INC_WIFI_H_ */
