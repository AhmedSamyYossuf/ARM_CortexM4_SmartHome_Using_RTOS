/*
 * board.h
 *
 *  Created on: Nov 5, 2020
 *      Author: MahmoudH
 */

#ifndef INC_BOARD_H_
#define INC_BOARD_H_

#include "stm32f4xx.h"

/*
 * 	Leds 	(PC5 to PC12)
 * 	Buzzer 	(PC4)
 *  Relay	(PC13)
 *  Buttons	(PD2, PA11, PA12, PC0, PC1)
 * */

#define 	ALL_LEDS	0xFF

typedef enum{
	LED0 = 5, LED1, LED2, LED3, LED4, LED5, LED6, LED7
}LED_Type;

typedef enum{
	BTN_CENTER, BTN_RIGHT, BTN_LEFT, BTN_UP, BTN_DOWN
}BTN_Type;

/* Buzzer */
void Buz_Init(void);
void Buz_On(void);
void Buz_Off(void);
void Buz_Toggle(void);

/* Relay */
void Relay_Init(void);
void Relay_On(void);
void Relay_Off(void);
void Relay_Toggle(void);

/* 	Leds
 * 	ledNO: 0-7
 *
 * 	*/
void Led_Init(LED_Type ledNo);
void Led_On(LED_Type ledNo);
void Led_Off(LED_Type ledNo);
void Led_Toggle(LED_Type ledNo);
/* Group of leds */
void Leds_Init(uint8_t ledsMask);
void Leds_On(uint8_t ledsMask);
void Leds_Off(uint8_t ledsMask);
void Leds_Toggle(uint8_t ledsMask);

/* Buttons */
void Btn_Init(BTN_Type btnNo);
void Btn_Init_EXTI(BTN_Type btnNo, void (*handler)(void));
/* returns 1 if pressed */
uint32_t Btn_isPressed(BTN_Type btnNo);


#endif /* INC_BOARD_H_ */
