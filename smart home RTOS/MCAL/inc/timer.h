/*
 * timer.h
 *
 *  Created on: Nov 15, 2020
 *      Author: MahmoudH
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f4xx.h"

/* Time Management */
void Timer_BaseInit(void);
void Timer_DelayMS(uint32_t delay_ms);
void Timer_DelayUS(uint32_t delay_us);
void Timer_SetNotification(void (*ptf)(void),uint16_t notifyPeriod);

/* Input Capture */
void Timer_CaptureInit(void);

/* Output Compare and PWM */
void Timer_PWMInit(void);
void Timer_PWMSetDuty(uint8_t duty);
void Timer_PWMIncDuty(uint8_t incDuty);
void Timer_PWMDecDuty(uint8_t decDuty);

#endif /* INC_TIMER_H_ */
