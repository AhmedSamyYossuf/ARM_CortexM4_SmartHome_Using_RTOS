/*
 * I2C.c
 *
 *  Created on: Nov 23, 2020
 *      Author: MahmoudH
 */

#include "I2C.h"

/* I2C1:
 * SCK: PB6
 * SDA: PB7
 * EEPROM AT24C16
 *  */
void TWI_Init(void){
	RCC->AHB1ENR 	|= 	RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR 	|= 	RCC_APB1ENR_I2C1EN;

	GPIOB->MODER 	&= 	~(0xF << (6 * 2));
	GPIOB->MODER 	|= 	 (0xA << (6 * 2));

	GPIOB->OTYPER	|= 	(3<<6); /* Open drain */


	//GPIOB->AFR[0] |= 0x4<<(6*4);
	//GPIOB->AFR[0] |= 0x4<<(7*4);

	GPIOB->AFR[0] 	&= ~(0xFF << (6 * 4));
	GPIOB->AFR[0] 	|=  (0x4 << (6 * 4));
	GPIOB->AFR[0] 	|=  (0x4 << (7 * 4));

	I2C1->CR1		&=	~(I2C_CR1_PE);

	/* Frequency Setup */
	I2C1->CCR 		&=	~I2C_CCR_FS; 	/* standard mode */

	I2C1->CR2		&=	~I2C_CR2_FREQ;	/* Fpclk1 = 2MHz */
	I2C1->CR2		|=   (2<<0);

	/*
	 	 Tp = Th + TL = 2*CCR*Tpclk
		CCR = Tp/(2*Tpclk1)
		CCR = Fpclk1/(2*Fsm)
       	   	= 20/2 = 10
	 */
	I2C1->CCR		&=	~I2C_CCR_CCR;
	I2C1->CCR		|=   (10<<0);
	/* Enable I2C */
	I2C1->CR1		|=   (I2C_CR1_PE);
	delayMs(100);
}
void 	I2C1_Init(void){
	RCC->AHB1ENR 	|= 	RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR 	|= 	RCC_APB1ENR_I2C1EN;

	GPIOB->MODER 	&= 	~(0xF << (6 * 2));
	GPIOB->MODER 	|= 	 (0xA << (6 * 2));

	GPIOB->OTYPER	|= 	(3<<6); /* Open drain */

	GPIOB->AFR[0] 	&= ~(0xFF << (6 * 4));
		GPIOB->AFR[0] 	|=  (0x4 << (6 * 4));
		GPIOB->AFR[0] 	|=  (0x4 << (7 * 4));

	I2C1->CR1		&=	~(I2C_CR1_PE);

	/* Frequency Setup */
	I2C1->CCR 		&=	~I2C_CCR_FS; 	/* standard mode */

	I2C1->CR2		&=	~I2C_CR2_FREQ;	/* Fpclk1 = 2MHz */
	I2C1->CR2		|=   (2<<0);

	/*
	 	 Tp = Th + TL = 2*CCR*Tpclk
		CCR = Tp/(2*Tpclk1)
		CCR = Fpclk1/(2*Fsm)
       	   	= 20/2 = 10
	 */
	I2C1->CCR		&=	~I2C_CCR_CCR;
	I2C1->CCR		|=   (10<<0);
	/* Enable I2C */
	I2C1->CR1		|=   (I2C_CR1_PE);
	delayMs(100);
}
void 	I2C1_Start(void){
	I2C1->CR1		|= I2C_CR1_START;
	while(!( I2C1->SR1 & I2C_SR1_SB));
}
void 	I2C1_Stop(void){
	I2C1->CR1		|= I2C_CR1_STOP;
}

void 	I2C1_WriteData(uint8_t data){
	I2C1->DR	 = data;
	while(!( I2C1->SR1 & I2C_SR1_TXE));
}
void 	I2C1_WriteAddress(uint8_t addr){
	I2C1->DR	 = addr;
	while(!( I2C1->SR1 & I2C_SR1_ADDR));
	/* dummy read to SR2 register to clear the address flag */
	(uint32_t)I2C1->SR2;
}
uint8_t I2C1_ReadData(void){
	/* ACK
	 * CR1_ACK
	 *  */
	while(!( I2C1->SR1 & I2C_SR1_RXNE));
	return I2C1->DR;
}
