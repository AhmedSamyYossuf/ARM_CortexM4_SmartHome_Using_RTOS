/*
 * Servo.c
 *
 *  Created on: Nov 17, 2020
 *      Author: MahmoudH
 */
#include "Servo.h"

void Servo_Init(void){
	Timer_PWMInit();
}
void Servo_SetPosition(Servo_Position position){
	switch (position) {
	case POS_DEG_0:
		Timer_PWMSetDuty(7);
		break;
	case POS_DEG_90:
		Timer_PWMSetDuty(12);
		break;
	case POS_DEG_180:
		Timer_PWMSetDuty(2);
		break;
	default:
		break;
	}
	delayMs(600);
	Timer_PWMSetDuty(0);
}
