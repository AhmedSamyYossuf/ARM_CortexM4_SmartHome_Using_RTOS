/*
 * ADC.h
 *
 *  Created on: Nov 11, 2020
 *      Author: MahmoudH
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f4xx.h"

typedef enum{
	CH0,CH1,CH2,CH3,CH4,
	CH5,CH6,CH7,CH8,CH9,
	CH10,CH11,CH12,CH13,
	CH14,CH15,CH16,CH17,
	CH18
}ADC_CH;

void ADC1_Init(void);
void ADC1_SelectChannel(ADC_CH channel);
uint16_t ADC1_Read(void);

#endif /* INC_ADC_H_ */
