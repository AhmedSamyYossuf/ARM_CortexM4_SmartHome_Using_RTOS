/*
 * uart.h
 *
 *  Created on: Nov 18, 2020
 *      Author: MahmoudH
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f4xx.h"
#include "timer.h"
#include "delay.h"

/* UART2 */
void Uart_Init(USART_TypeDef* uart, uint32_t baudrate);
void Uart_SendByte(USART_TypeDef* uart, uint8_t data);
void Uart_SendString(USART_TypeDef* uart, uint8_t* str);
void Uart_SendBytes(USART_TypeDef* uart, uint8_t* buf, uint32_t len);

void Uart_ReceiveByte(USART_TypeDef* uart, uint8_t* pData);
uint8_t Uart_ReceiveByte_Unblock(USART_TypeDef* uart, uint8_t* pData);
/* Timeout in ms */
uint8_t Uart_ReceiveBytes(USART_TypeDef* uart, uint8_t* buf,uint32_t len, uint32_t timeout);
uint8_t Uart_ReceiveBytes_Del(USART_TypeDef* uart, uint8_t* buf,uint8_t delimeter, uint32_t*  pLen, uint32_t timeout);

#endif /* INC_UART_H_ */
