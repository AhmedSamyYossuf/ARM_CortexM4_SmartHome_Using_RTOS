/*
 * ADC.c
 *
 *  Created on: Nov 11, 2020
 *      Author: MahmoudH
 */

#include "ADC.h"

void ADC1_Init(void){
	/* ADC1 RCC */
	RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;
	/* ADC ON */
	ADC1->CR2		|=	ADC_CR2_ADON;
	/* SQR1 -> Number of total conversions  = 1 */
	ADC1->SQR1		&= ~ADC_SQR1_L;
}
void ADC1_SelectChannel(ADC_CH channel){
	switch (channel) {
	case CH0:
		/* PA0 */
		RCC->AHB1ENR 	|=  RCC_AHB1ENR_GPIOAEN;
		/* Analog */
		GPIOA->MODER	|=  GPIO_MODER_MODER0;
		break;
	case CH1:
		/* PA1 */
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		/* Analog */
		GPIOA->MODER	|=  GPIO_MODER_MODER1;
		break;
	default:
		break;
	}
	ADC1->SQR3		&= ~ADC_SQR3_SQ1;
	ADC1->SQR3		|=  channel;
}
uint16_t ADC1_Read(void){
	/* Start Conversion */
	ADC1->CR2		|=	ADC_CR2_SWSTART;
	/* Wait until conversion is completed */
	while( !(ADC1->SR & ADC_SR_EOC) );
	/* return the conversion result */
	return ADC1->DR;
}
