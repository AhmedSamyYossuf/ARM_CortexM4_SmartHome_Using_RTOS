/*
 * keypad.c
 *
 *  Created on: Nov 9, 2020
 *      Author: MahmoudH
 */
#include "keypad.h"

void 	Keypad_Init(void){
	/* RCC */
	RCC->AHB1ENR |= (KEY_ROWS_RCC|KEY_COLS_RCC);
	/* Rows -> Out , default high*/
	KEY_ROWS_GPIO->MODER	&= ~KEY_ROWS_MODER_MASK;
	KEY_ROWS_GPIO->MODER	|=  KEY_ROWS_MODER_OUT_MASK;
	KEY_ROWS_GPIO->ODR		|=  KEY_ROWS_ODR_MASK;
	/* Cols -> In , pullup*/
	KEY_COLS_GPIO->MODER	&= ~KEY_COLS_MODER_MASK;
	KEY_COLS_GPIO->PUPDR	&= ~KEY_COLS_PUPDR_MASK;
	KEY_COLS_GPIO->PUPDR	|=  KEY_COLS_PUPDR_UP_MASK;
}
/* Key -> 1:9
 * Key 1 -> R1 and C1
 * 0 -> No pressed key
 *  */
uint8_t	Keypad_GetKey(void){
	/*
	 * 	for each row
	 * 		activate this row
	 *		for each col
	 *			if col is pressed
	 *				calculate key
	 * 				de-activate this row
	 * 				return key
	 * 			endif
	 *		endfor
	 *		de-activate this row
	 *  endfor
	 *
	 *	return 0
	 * */
	uint8_t key = 0;
	uint8_t rowInd = 0;
	uint8_t colInd = 0;
	for (rowInd = 0; rowInd < 3; ++rowInd) {
		KEY_ROWS_GPIO->ODR &= ~(1<<(rowInd + KEY_ROWS_SHIFT));
		delayMs(1);
		for (colInd = 0; colInd < 3; ++colInd) {
			if( !((KEY_COLS_GPIO->IDR) & (1<<(colInd + KEY_COLS_SHIFT)) ) ){
				key = colInd*1 + rowInd*3 + 1;
				KEY_ROWS_GPIO->ODR |= (1<<(rowInd + KEY_ROWS_SHIFT));
				while( !((KEY_COLS_GPIO->IDR) & (1<<(colInd + KEY_COLS_SHIFT)) ) );
				return key;
			}
		}
		KEY_ROWS_GPIO->ODR |= (1<<(rowInd + KEY_ROWS_SHIFT));
	}
	return 0;
}
