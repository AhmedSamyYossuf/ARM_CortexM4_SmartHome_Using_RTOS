/*
 * spi.c
 *
 *  Created on: Nov 22, 2020
 *      Author: MahmoudH
 */

#include "spi.h"

void SPI2_Init(SPI_Mode mode){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

	GPIOB->MODER &= ~(3 << (10 * 2));
	GPIOB->MODER |= (2 << (10 * 2));
	GPIOC->MODER &= ~(0xF << (2 * 2));
	GPIOC->MODER |= (0xA << (2 * 2));

	GPIOC->AFR[0] &= ~(0xFF << (2 * 4));
	GPIOC->AFR[0] |= (0x55 << (2 * 4));
	GPIOB->AFR[1] &= ~(0xF << (2 * 4));
	GPIOB->AFR[1] |= (0x5 << (2 * 4));

	switch (mode) {
	case MASTER_MODE:
		SPI2->CR1 |= SPI_CR1_BR;
		SPI2->CR1 |= SPI_CR1_SSM;
		SPI2->CR1 |= SPI_CR1_SSI;
		SPI2->CR1 |= SPI_CR1_MSTR;
		break;

	case SLAVE_MODE:
		SPI2->CR1 &= ~SPI_CR1_MSTR;
		break;

	default:
		break;
	}
	SPI2->CR1 |= SPI_CR1_SPE;
	delayMs(100);
}
uint8_t SPI_Tranceive(uint8_t data){
	SPI2->DR=data;
	while(!(SPI2->SR&SPI_SR_TXE));
	while(!(SPI2->SR&SPI_SR_RXNE));
	return  SPI2->DR;
}
