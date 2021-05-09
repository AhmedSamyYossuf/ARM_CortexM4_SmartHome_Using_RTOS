/*
 * segment.c
 *
 *  Created on: Nov 9, 2020
 *      Author: MahmoudH
 */
#include	"segment.h"

const uint8_t  numbers[11] = {
		NUM_0,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		DOT
};


void Segment_Init(void){
	/* RCC -> Data and POS */
	RCC->AHB1ENR |= (SEG_DATA_RCC|SEG_POS_RCC);
	/* Data port -> Out and default low */
	SEG_DATA_GPIO->MODER	&= ~SEG_DATA_MODER_MASK;
	SEG_DATA_GPIO->MODER	|=	SEG_DATA_MODER_OUT_MASK;
	SEG_DATA_GPIO->ODR		&= ~SEG_DATA_ODR_MASK;
	/* POS port -> Out and default high */
	SEG_POS_GPIO->MODER		&= ~SEG_POS_MODER_MASK;
	SEG_POS_GPIO->MODER		|=	SEG_POS_MODER_OUT_MASK;
	SEG_POS_GPIO->ODR		|=	SEG_POS_ODR_MASK;

}
/* numbers -> 0:9 decimal
 * DOT -> '.'
 * position -> 1:4
 * */
void Segment_Display(uint8_t value, uint8_t position){
	if(value == '.'){
		SEG_DATA_GPIO->ODR	&= ~SEG_DATA_ODR_MASK;
		SEG_DATA_GPIO->ODR 	|=  (numbers[10]<<SEG_DATA_SHIFT);
	}else{
		SEG_DATA_GPIO->ODR	&= ~SEG_DATA_ODR_MASK;
		SEG_DATA_GPIO->ODR 	|=  (numbers[value]<<SEG_DATA_SHIFT);
	}
	SEG_POS_GPIO->ODR		|=	SEG_POS_ODR_MASK;
	SEG_POS_GPIO->ODR		&= ~(1<<(SEG_POS_SHIFT + (position - 1)));
	delayMs(1);
}

