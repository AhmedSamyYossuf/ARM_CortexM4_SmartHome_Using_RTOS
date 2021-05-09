/*
 * segment.h
 *
 *  Created on: Nov 9, 2020
 *      Author: MahmoudH
 */

#ifndef INC_SEGMENT_H_
#define INC_SEGMENT_H_

#include	"stm32f4xx.h"
#include	"delay.h"

/*
 * 			a
 * 		f		b
 * 			g
 * 		e		c
 * 			d		.
 *
 * */
/* 0b.gfedcba */
/* Numbers */
#define NUM_0	0x3F
#define NUM_1	0x06
#define NUM_2	0x5B
#define NUM_3	0x4F
#define NUM_4	0x66
#define NUM_5	0x6D
#define NUM_6	0x7D
#define NUM_7	0x07
#define NUM_8	0x7F
#define NUM_9	0x6F
#define DOT		0x80

/*
 * Data (Active High)-> 	PC5 :12
 * POS (Active Low)->		PB12:15
 * */
#define	SEG_DATA_SHIFT				5
#define	SEG_POS_SHIFT				12

#define	SEG_DATA_RCC				RCC_AHB1ENR_GPIOCEN
#define	SEG_DATA_GPIO				GPIOC
#define	SEG_DATA_ODR_MASK			(0xFF<<SEG_DATA_SHIFT)
#define SEG_DATA_MODER_MASK			(0xFFFF<<(SEG_DATA_SHIFT*2))
#define SEG_DATA_MODER_OUT_MASK		(0x5555<<(SEG_DATA_SHIFT*2))

#define	SEG_POS_RCC					RCC_AHB1ENR_GPIOBEN
#define SEG_POS_GPIO				GPIOB
#define	SEG_POS_ODR_MASK			(0xF<<SEG_POS_SHIFT)
#define SEG_POS_MODER_MASK			(0xFF<<(SEG_POS_SHIFT*2))
#define SEG_POS_MODER_OUT_MASK		(0x55<<(SEG_POS_SHIFT*2))

void Segment_Init(void);
void Segment_Display(uint8_t value, uint8_t position);
#endif /* INC_SEGMENT_H_ */
