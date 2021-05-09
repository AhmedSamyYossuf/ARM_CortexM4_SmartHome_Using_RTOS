/*
 * systick.h
 *
 *  Created on: Nov 24, 2020
 *      Author: MahmoudH
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32f4xx.h"

void 		SysTick_Init(uint32_t underFlowValue);
void 		SysTick_Restart(void);
uint32_t 	SysTick_GetTicks(void);

#endif /* INC_SYSTICK_H_ */
