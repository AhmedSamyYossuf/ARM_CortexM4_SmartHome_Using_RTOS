/*
 * delay.c
 *
 *  Created on: Nov 5, 2020
 *      Author: MahmoudH
 */
#include "delay.h"

void delayMs(uint32_t delay_ms){
	uint32_t ind1 = 0;
	uint32_t ind2 = 0;
	for (ind1 = 0; ind1 < delay_ms; ++ind1) {
		for (ind2 = 0; ind2 < 1250; ++ind2) {
			asm("nop");
		}
	}
}
