/*
 * Servo.h
 *
 *  Created on: Nov 17, 2020
 *      Author: MahmoudH
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx.h"
#include "timer.h"
#include "delay.h"

typedef enum{
	POS_DEG_0,POS_DEG_90,POS_DEG_180
}Servo_Position;

void Servo_Init(void);
void Servo_SetPosition(Servo_Position position);

#endif /* INC_SERVO_H_ */
