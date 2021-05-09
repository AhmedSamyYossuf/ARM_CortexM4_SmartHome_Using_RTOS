/*
 * board.c
 *
 *  Created on: Nov 5, 2020
 *      Author: MahmoudH
 */

#include "board.h"

/*
 * 	Leds 	(PC5 to PC12)
 * 	Buzzer 	(PC4)
 *  Relay	(PC13)
 *  Buttons	(PD2, PA11, PA12, PC0, PC1)
 * */

/* Buzzer */
void Buz_Init(void){
	/* RCC Clock GPIOC */
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
	/* PC4 Out */
	GPIOC->MODER &= ~GPIO_MODER_MODER4;
	GPIOC->MODER |=  GPIO_MODER_MODER4_0;
	Buz_Off();
}
void Buz_On(void){
	GPIOC->ODR |= GPIO_ODR_ODR_4;
}
void Buz_Off(void){
	GPIOC->ODR &= ~GPIO_ODR_ODR_4;
}
void Buz_Toggle(void){
	GPIOC->ODR ^= GPIO_ODR_ODR_4;
}

/* Relay */
void Relay_Init(void){
	/* RCC Clock GPIOC */
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
	/* PC13 Out */
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	GPIOC->MODER |=  GPIO_MODER_MODER13_0;
	Relay_Off();
}
void Relay_On(void){
	GPIOC->ODR |= GPIO_ODR_ODR_13;
}
void Relay_Off(void){
	GPIOC->ODR &= ~GPIO_ODR_ODR_13;
}
void Relay_Toggle(void){
	GPIOC->ODR ^= GPIO_ODR_ODR_13;
}

/* 	Leds PC5:12
 * 	ledNO: 0-7
 *
 * 	*/
void Led_Init(LED_Type ledNo){
	/* RCC Clock GPIOC */
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
	/* PCx Out */
	GPIOC->MODER &= ~(3<<(ledNo*2));
	GPIOC->MODER |=  (1<<(ledNo*2));
	Relay_Off();
}
void Led_On(LED_Type ledNo){
	GPIOC->ODR |= (1<<ledNo);
}
void Led_Off(LED_Type ledNo){
	GPIOC->ODR &= ~(1<<ledNo);
}
void Led_Toggle(LED_Type ledNo){
	GPIOC->ODR ^= (1<<ledNo);
}
/* Group of leds */
void Leds_Init(uint8_t ledsMask){
	/* RCC Clock GPIOC */
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(0xFFFF<<(5*2));
	GPIOC->MODER |=  (0x5555<<(5*2));
	Leds_Off(ledsMask);
}
void Leds_On(uint8_t ledsMask){
	GPIOC->ODR |= (ledsMask<<5);
}
void Leds_Off(uint8_t ledsMask){
	GPIOC->ODR &= ~(ledsMask<<5);
}
void Leds_Toggle(uint8_t ledsMask){
	GPIOC->ODR ^= (ledsMask<<5);
}

/* Buttons	(PD2 C, PA11 R, PA12 L, PC0 D, PC1 U)*/
void Btn_Init(BTN_Type btnNo){
	switch (btnNo) {
	case BTN_CENTER:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIODEN;
		GPIOD->MODER	&= ~GPIO_MODER_MODER2;
		GPIOD->PUPDR	&= ~GPIO_PUPDR_PUPDR2;
		GPIOD->PUPDR	|=  GPIO_PUPDR_PUPDR2_0;
		break;
	case BTN_LEFT:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER	&= ~GPIO_MODER_MODER12;
		GPIOA->PUPDR	&= ~GPIO_PUPDR_PUPDR12;
		GPIOA->PUPDR	|=  GPIO_PUPDR_PUPDR12_0;
		break;
	case BTN_RIGHT:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER	&= ~GPIO_MODER_MODER11;
		GPIOA->PUPDR	&= ~GPIO_PUPDR_PUPDR11;
		GPIOA->PUPDR	|=  GPIO_PUPDR_PUPDR11_0;
		break;
	case BTN_UP:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
		GPIOC->MODER	&= ~GPIO_MODER_MODER1;
		GPIOC->PUPDR	&= ~GPIO_PUPDR_PUPDR1;
		GPIOC->PUPDR	|=  GPIO_PUPDR_PUPDR1_0;
		break;
	case BTN_DOWN:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
		GPIOC->MODER	&= ~GPIO_MODER_MODER0;
		GPIOC->PUPDR	&= ~GPIO_PUPDR_PUPDR0;
		GPIOC->PUPDR	|=  GPIO_PUPDR_PUPDR0_0;
		break;
	default:
		break;
	}
}

void (*handler_up)(void);
void (*handler_down)(void);
void (*handler_left)(void);
void (*handler_right)(void);
void (*handler_center)(void);

/* Buttons	(PD2 C, PA11 R, PA12 L, PC0 D, PC1 U)*/
void Btn_Init_EXTI(BTN_Type btnNo, void (*handler)(void)){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	switch (btnNo) {
	case BTN_CENTER:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIODEN;
		GPIOD->MODER	&= ~GPIO_MODER_MODER2;
		GPIOD->PUPDR	&= ~GPIO_PUPDR_PUPDR2;
		GPIOD->PUPDR	|=  GPIO_PUPDR_PUPDR2_0;

		handler_center = handler;
		SYSCFG->EXTICR[0]	&= ~SYSCFG_EXTICR1_EXTI2;
		SYSCFG->EXTICR[0]	|=  SYSCFG_EXTICR1_EXTI2_PD;
		EXTI->FTSR			|=  EXTI_FTSR_TR2;
		EXTI->IMR			|=  EXTI_IMR_MR2;
		NVIC_EnableIRQ(EXTI2_IRQn);
		break;
	case BTN_LEFT:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER	&= ~GPIO_MODER_MODER12;
		GPIOA->PUPDR	&= ~GPIO_PUPDR_PUPDR12;
		GPIOA->PUPDR	|=  GPIO_PUPDR_PUPDR12_0;

		handler_left = handler;
		SYSCFG->EXTICR[3]	&= ~SYSCFG_EXTICR4_EXTI12;
		SYSCFG->EXTICR[3]	|=  SYSCFG_EXTICR4_EXTI12_PA;
		EXTI->FTSR			|=  EXTI_FTSR_TR12;
		EXTI->IMR			|=  EXTI_IMR_MR12;
		NVIC_EnableIRQ(EXTI15_10_IRQn);
		break;
	case BTN_RIGHT:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER	&= ~GPIO_MODER_MODER11;
		GPIOA->PUPDR	&= ~GPIO_PUPDR_PUPDR11;
		GPIOA->PUPDR	|=  GPIO_PUPDR_PUPDR11_0;

		handler_right 		 = handler;
		SYSCFG->EXTICR[2]	&= ~SYSCFG_EXTICR3_EXTI11;
		SYSCFG->EXTICR[2]	|=  SYSCFG_EXTICR3_EXTI11_PA;
		EXTI->FTSR			|=  EXTI_FTSR_TR11;
		EXTI->IMR			|=  EXTI_IMR_MR11;
		NVIC_EnableIRQ(EXTI15_10_IRQn);
		break;
	case BTN_UP:
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
		GPIOC->MODER	&= ~GPIO_MODER_MODER1;
		GPIOC->PUPDR	&= ~GPIO_PUPDR_PUPDR1;
		GPIOC->PUPDR	|=  GPIO_PUPDR_PUPDR1_0;

		handler_up		 = handler;
		SYSCFG->EXTICR[0]	&= ~SYSCFG_EXTICR1_EXTI1;
		SYSCFG->EXTICR[0]	|=  SYSCFG_EXTICR1_EXTI1_PC;
		EXTI->FTSR			|=  EXTI_FTSR_TR1;
		EXTI->IMR			|=  EXTI_IMR_MR1;
		NVIC_EnableIRQ(EXTI1_IRQn);
		break;
	case BTN_DOWN:
		RCC->AHB1ENR 	|=  RCC_AHB1ENR_GPIOCEN;
		GPIOC->MODER	&= ~GPIO_MODER_MODER0;
		GPIOC->PUPDR	&= ~GPIO_PUPDR_PUPDR0;
		GPIOC->PUPDR	|=  GPIO_PUPDR_PUPDR0_0;

		handler_down 		 =  handler;
		SYSCFG->EXTICR[0]	&= ~SYSCFG_EXTICR1_EXTI0;
		SYSCFG->EXTICR[0]	|=  SYSCFG_EXTICR1_EXTI0_PC;
		EXTI->FTSR			|=  EXTI_FTSR_TR0;
		EXTI->IMR			|=  EXTI_IMR_MR0;
		NVIC_EnableIRQ(EXTI0_IRQn);
		break;
	default:
		break;
	}
}
/* returns 1 if pressed */
/* Buttons	(PD2 C, PA11 R, PA12 L, PC0 D, PC1 U)*/
uint32_t Btn_isPressed(BTN_Type btnNo){
	uint32_t result = 0;
	switch (btnNo) {
	case BTN_CENTER:
		result = (GPIOD->IDR & GPIO_IDR_IDR_2);
		break;
	case BTN_LEFT:
		result = (GPIOA->IDR & GPIO_IDR_IDR_12);
		break;
	case BTN_RIGHT:
		result = (GPIOA->IDR & GPIO_IDR_IDR_11);
		break;
	case BTN_UP:
		result = (GPIOC->IDR & GPIO_IDR_IDR_1);
		break;
	case BTN_DOWN:
		result = (GPIOC->IDR & GPIO_IDR_IDR_0);
		break;
	default:
		break;
	}
	return (result == 0);
}
void EXTI0_IRQHandler(void){
	EXTI->PR	|=  EXTI_PR_PR0;
	handler_down();
}
/*
void EXTI1_IRQHandler(void){
	EXTI->PR	|=  EXTI_PR_PR1;
	handler_up();
}
*/
void EXTI2_IRQHandler(void){
	EXTI->PR	|=  EXTI_PR_PR2;
	handler_center();
}
/*
void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR11){
		EXTI->PR	|=  EXTI_PR_PR11;
		handler_right();
	}
	else if(EXTI->PR & EXTI_PR_PR12){
		EXTI->PR	|=  EXTI_PR_PR12;
		handler_left();
	}
}
*/
