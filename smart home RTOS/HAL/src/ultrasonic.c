/*
 * ultrasonic.c
 *
 *  Created on: Nov 16, 2020
 *      Author: MahmoudH
 */

#include "ultrasonic.h"

extern volatile uint32_t pulse_width;

void Ultra_Init(void){
	/* setup trigger */
	RCC->AHB1ENR		|= 	RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER		&= ~(3<<(4*2));
	GPIOA->MODER		|=  (1<<(4*2));
	GPIOA->ODR			&= ~GPIO_ODR_ODR_4;
	/* setup timer 1 channel 1 to be ready */
	Timer_CaptureInit();
}
uint16_t 	Ultra_GetDistance(void){
	uint16_t distance 	= 0; /* in cm */
	uint32_t delay 		= 0; /* in ms */
	pulse_width = 0;
	/* Send the trigger pulse on PA4*/
	GPIOA->ODR			|=  GPIO_ODR_ODR_4;
	delayMs(1);
	GPIOA->ODR			&= ~GPIO_ODR_ODR_4;
	/* wait for pulse width measurement to be completed */
	while(pulse_width == 0 && delay < 50){
		delayMs(1);
		delay++;
	}
	/* Calculate Distance (2 to 400), where distance = width/58*/
	distance = pulse_width/58;
	/* return  the distance */
	return distance;
}
