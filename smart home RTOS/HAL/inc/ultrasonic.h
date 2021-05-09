/*
 * ultrasonic.h
 *
 *  Created on: Nov 16, 2020
 *      Author: MahmoudH
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "stm32f4xx.h"
#include "timer.h"
#include "delay.h"

/* Distance in cm (2 - 400)
 * TIM1_CH1_IC
 * */
void 		Ultra_Init(void);
uint16_t 	Ultra_GetDistance(void);

#endif /* INC_ULTRASONIC_H_ */
