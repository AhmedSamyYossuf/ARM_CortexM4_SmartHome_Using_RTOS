/*
 * keypad.h
 *
 *  Created on: Nov 9, 2020
 *      Author: MahmoudH
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include	"stm32f4xx.h"
#include	"delay.h"

#define	KEY_ROWS_SHIFT				5
#define	KEY_COLS_SHIFT				0

#define	KEY_ROWS_RCC				RCC_AHB1ENR_GPIOAEN
#define	KEY_ROWS_GPIO				GPIOA
#define	KEY_ROWS_ODR_MASK			(0x7<<KEY_ROWS_SHIFT)
#define KEY_ROWS_MODER_MASK			(0x3F<<(KEY_ROWS_SHIFT*2))
#define KEY_ROWS_MODER_OUT_MASK		(0x15<<(KEY_ROWS_SHIFT*2))

#define	KEY_COLS_RCC				RCC_AHB1ENR_GPIOBEN
#define	KEY_COLS_GPIO				GPIOB
//#define	KEY_COLS_ODR_MASK			(0x7<<KEY_COLS_SHIFT)
#define KEY_COLS_MODER_MASK			(0x3F<<(KEY_COLS_SHIFT*2))
#define KEY_COLS_PUPDR_MASK			(0x3F<<(KEY_COLS_SHIFT*2))
#define KEY_COLS_PUPDR_UP_MASK		(0x15<<(KEY_COLS_SHIFT*2))

void 	Keypad_Init(void);
/* Key -> 1:9
 * Key 1 -> R1 and C1
 *  */
uint8_t	Keypad_GetKey(void);

#endif /* INC_KEYPAD_H_ */
