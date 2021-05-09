/*
 * timer.c
 *
 *  Created on: Nov 15, 2020
 *      Author: MahmoudH
 */

#include "timer.h"

/* Timer 2 for time management
 * Timer 1 CH 1 (IC) for ultrasonic echo
 * Timer 4 CH 4 (OC-PWM) for servo
 * */
volatile uint32_t overflows = 0;

void Timer_BaseInit(void){
	/* RCC */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	/* Timer PSC 1 ms*/
	TIM3->PSC	= 16000 - 1;
	TIM3->DIER	|= TIM_DIER_UIE;
	/* Enable CEN */
	TIM3->CR1	|= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);
	__enable_irq();
}
void Timer_DelayMS(uint32_t delay_ms){
	TIM3->CNT = 0;
	overflows = 0;
	TIM3->ARR = 0xFFFF;
	while( (TIM3->CNT + overflows*(0xFFFF+1)) < (delay_ms));
}
void Timer_DelayUS(uint32_t delay_us){
	/*TIM2->CNT = 0;
	TIM2->ARR = delay_us;
	while( TIM2->CNT < TIM2->ARR);*/
	/*TIM3->CNT = 0;
	overflows = 0;
	TIM3->ARR = 0xFFFF;
	while( (TIM3->CNT + overflows*(0xFFFF+1)) < delay_us);*/
}
void (*notifyHandle)(void);
void Timer_SetNotification(void (*ptf)(void),uint16_t notifyPeriod){
	notifyHandle = ptf;
	TIM3->CNT = 0;
	TIM3->ARR = notifyPeriod;

}

/* Input Capture */
void Timer_CaptureInit(void){
	/* GPIOA PA8 (RCC, TIM1 alterate) */
	RCC->AHB1ENR 		|=  RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER		&= ~(3<<(8*2));
	GPIOA->MODER		|=  (2<<(8*2));

	GPIOA->AFR[1]		&= ~(0xF<<(0*4));
	GPIOA->AFR[1]		|=  (0x1<<(0*4));

	/* TIM1 RCC (APB2) */
	RCC->APB2ENR		|= RCC_APB2ENR_TIM1EN;

	/* TIM1 tick time - 1us (PSC). */
	TIM1->PSC			=  16 - 1;

	/* ARR is MAX. */
	TIM1->ARR			= 0xFFFFFFFF;

	/* CH1 is input IC1 (CCMR1_CC1S :01) */
	TIM1->CCMR1			|=  TIM_CCMR1_CC1S_0;
	TIM1->CCMR1			&= ~TIM_CCMR1_CC1S_1;

	/* select rising and falling edges (CCER_CC1NP/CC1P: 11) */
	TIM1->CCER			|=  TIM_CCER_CC1P;
	TIM1->CCER			|=  TIM_CCER_CC1NP;

	/* Enable: Channel (CCER_CC1E) */
	TIM1->CCER			|= TIM_CCER_CC1E;

	/* Enable: Timer   (CR1_CEN) */
	TIM1->CR1 			|= TIM_CR1_CEN;

	/* Capture/compare interrupt with TIM (DIER_CC1IE */
	TIM1->DIER			|= TIM_DIER_CC1IE;

	/* Capture/compare interrupt with NVIC and Global. */
	NVIC_EnableIRQ(TIM1_CC_IRQn);
	__enable_irq();
}

/* Output Compare and PWM */
void Timer_PWMInit(void){
	/* GPIOB PB9 (RCC, TIM1 alterate) */
	RCC->AHB1ENR 		|=  RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER		&= ~(3<<(9*2));
	GPIOB->MODER		|=  (2<<(9*2));

	GPIOB->AFR[1]		&= ~(0xF<<(1*4));
	GPIOB->AFR[1]		|=  (0x2<<(1*4));

	/* TIM4 RCC (APB1) */
	RCC->APB1ENR		|= RCC_APB1ENR_TIM4EN;

	/* TIM4 tick time - 1ms (PSC). */
	TIM4->PSC			=  (SystemCoreClock/1000000UL) - 1;

	/* ARR is 20. */
	TIM4->ARR			= 20000;

	/* CH4 is Output OC4 (CCMR2_CC4S :00) */
	TIM4->CCMR2			&= ~TIM_CCMR2_CC4S;

	 /* Select PWM Mode 1 (CCMR2_OC4M :110) */
	TIM4->CCMR2			|=  TIM_CCMR2_OC4M;
	TIM4->CCMR2			&= ~TIM_CCMR2_OC4M_0;

	/* preload enable  CCMR2_OC4PE and CR1_ARPE */
	TIM4->CCMR2			|=  TIM_CCMR2_OC4PE;
	TIM4->CR1			|=  TIM_CR1_ARPE;

	/* set update event EGR_UG */
	TIM4->EGR			|=  TIM_EGR_UG;

	/* Enable: Main Output Unit		(BDTR_MOE) */
	TIM4->BDTR			|=  TIM_BDTR_MOE;

	/* Enable: Channel (CCER_CC4E) */
	TIM4->CCER			|= TIM_CCER_CC4E;

	/* Enable: Timer   (CR1_CEN) */
	TIM4->CR1 			|= TIM_CR1_CEN;
}
void Timer_PWMSetDuty(uint8_t duty){
	TIM4->CCR4			 = (TIM4->ARR) * (duty/100.0);
}
void Timer_PWMIncDuty(uint8_t incDuty){
	if( (incDuty + ((100*TIM4->CCR4)/TIM4->ARR)) < 100)
	{
		TIM4->CCR4	+= ((TIM4->ARR)*(incDuty/100.0));
	}
	else{
		TIM4->CCR4   = TIM4->ARR;
	}
}
void Timer_PWMDecDuty(uint8_t decDuty){
	if( ((100*TIM4->CCR4)/TIM4->ARR) > decDuty )
	{
		TIM4->CCR4	-= ((TIM4->ARR)*(decDuty/100.0));
	}
	else{
		TIM4->CCR4   = 0;
	}
}




volatile uint32_t pulse_width = 0;
static volatile uint8_t  edge_state  = 0; /* 0: Rising, 1: Falling */
void TIM1_CC_IRQHandler(void){
	TIM1->SR &= ~TIM_SR_CC1IF;
	if(edge_state == 0){
		/* Rising */
		TIM1->CNT = 0;
		edge_state = 1;
	}else if(edge_state == 1){
		/* Falling */
		pulse_width = TIM1->CCR1;
		edge_state = 0;
	}
}
void TIM3_IRQHandler(void){
	if(TIM3->SR & TIM_SR_UIF){
		TIM3->SR &= ~TIM_SR_UIF;
		notifyHandle();
		//TIM3->CR1	&= ~TIM_CR1_CEN;
	}
}
