/*
 * systick.c
 *
 *  Created on: Nov 24, 2020
 *      Author: MahmoudH
 */
#include "systick.h"

volatile static uint32_t ticks = 0;

void 		SysTick_Init(uint32_t underFlowValue){
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk|SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk);
	SysTick->LOAD = underFlowValue - 1;
	SysTick->VAL  = SysTick->LOAD;
}
void 		SysTick_Restart(void){
	SysTick->VAL  = SysTick->LOAD;
	ticks = 0;
}
uint32_t 	SysTick_GetTicks(void){
	return ticks;
}

void SysTick_Handler(void)
{
	osSystickHandler();
}
