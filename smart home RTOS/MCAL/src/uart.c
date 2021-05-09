/*
 * uart.c
 *
 *  Created on: Nov 18, 2020
 *      Author: MahmoudH
 */

#include "uart.h"

/* UART2 */
void Uart_Init(USART_TypeDef* uart, uint32_t baudrate){
	uint8_t frac;
	uint16_t integ;
	float UARTDIV;

	if(uart == USART2){
		RCC->AHB1ENR	|=RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER	&= ~(3<<(2*2));
		GPIOA->MODER	&= ~(3<<(3*2));
		GPIOA->MODER	|= (2<<(2*2));
		GPIOA->MODER	|= (2<<(3*2));

		GPIOA->AFR[0]	&= ~(0xF<<(2*4));
		GPIOA->AFR[0]	&= ~(0xF<<(3*4));
		GPIOA->AFR[0]	|= (0x7<<(2*4));
		GPIOA->AFR[0]	|= (0x7<<(3*4));
		RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;
	}else if(uart == USART1){
		RCC->AHB1ENR	|=RCC_AHB1ENR_GPIOAEN;
		GPIOA->MODER	&= ~(3<<(9*2));
		GPIOA->MODER	&= ~(3<<(10*2));
		GPIOA->MODER	|= (2<<(9*2));
		GPIOA->MODER	|= (2<<(10*2));

		GPIOA->AFR[1]	&= ~(0xF<<(1*4));
		GPIOA->AFR[1]	&= ~(0xF<<(2*4));
		GPIOA->AFR[1]	|= (0x7<<(1*4));
		GPIOA->AFR[1]	|= (0x7<<(2*4));
		RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;

	}else if(uart == USART6){
		RCC->AHB1ENR	|=RCC_AHB1ENR_GPIOCEN;
		GPIOA->MODER	&= ~(3<<(6*2));
		GPIOA->MODER	&= ~(3<<(7*2));
		GPIOA->MODER	|= (2<<(6*2));
		GPIOA->MODER	|= (2<<(7*2));

		GPIOA->AFR[0]	&= ~(0xF<<(6*4));
		GPIOA->AFR[0]	&= ~(0xF<<(7*4));
		GPIOA->AFR[0]	|= (0x8<<(6*4));
		GPIOA->AFR[0]	|= (0x8<<(7*4));
		RCC->APB2ENR	|= RCC_APB2ENR_USART6EN;

	}

	UARTDIV			= (SystemCoreClock/(16.0*baudrate));
	integ			= (uint16_t)UARTDIV;
	frac			= (UARTDIV-integ)*16;
	uart->BRR		=(integ<<4)+frac;

	uart->CR1		|=((USART_CR1_TE)|(USART_CR1_RE)|(USART_CR1_UE));

}
void Uart_SendByte(USART_TypeDef* uart, uint8_t data){
	while(!(uart->SR &USART_SR_TXE));
	uart->DR 		= data;
}
void Uart_SendString(USART_TypeDef* uart, uint8_t* str){
	uint32_t i = 0;
	while(str[i])
	{
		Uart_SendByte(uart,str[i]);
		i++;
	}
}
void Uart_SendBytes(USART_TypeDef* uart, uint8_t* buf, uint32_t len){
	uint32_t i = 0;
	while(i<len)
	{
		Uart_SendByte(uart,buf[i]);
		i++;
	}
}

void Uart_ReceiveByte(USART_TypeDef* uart, uint8_t* pData){
	while(!(uart->SR &USART_SR_RXNE));
	(*pData)	=	uart->DR;
}
uint8_t Uart_ReceiveByte_Unblock(USART_TypeDef* uart, uint8_t* pData){
	uint8_t status = 0;
	if(uart->SR &USART_SR_RXNE)
	{
		(*pData) 	= uart->DR;
		status 		= 1;
	}
	return status;
}
/* Timeout in ms */
uint8_t Uart_ReceiveBytes(USART_TypeDef* uart, uint8_t* buf,uint32_t len, uint32_t timeout){
	uint8_t status =0;
	uint8_t i=0;
	uint32_t counter=0;
	while( i<len && counter <timeout )
	{
		if( Uart_ReceiveByte_Unblock(uart,(buf+i)))
		{
			i++;
		}
		else
		{
			counter++;
			delayMs(1);
		}
	}
	if( counter < timeout)
	{
		status = 1;
	}
	else
	{
		status = 0;
	}
	return status;

}
uint8_t Uart_ReceiveBytes_Del(USART_TypeDef* uart, uint8_t* buf,uint8_t delimeter, uint32_t*  pLen, uint32_t timeout){
	uint8_t status =0;
	uint32_t i=0;
	uint32_t counter=0;
	uint8_t data = delimeter+1;
	while( data != delimeter && counter <timeout )
	{
		if( Uart_ReceiveByte_Unblock(uart,(buf+i)))
		{
			data = buf[i];
			i++;
		}
		else
		{
			counter++;
			delayMs(1);
		}
	}
	(*pLen) = i;
	if( counter < timeout)
	{
		status = 1;
	}
	else
	{
		status = 0;
	}
	return status;

}
