/*
 * LCD.c
 *
 *  Created on: Nov 10, 2020
 *      Author: MahmoudH
 */

#include "LCD.h"
/* Static Declarations */
static void LCD_GotoXY(uint8_t line, uint8_t col);
static void LCD_SendCMD(uint8_t cmd);
static void LCD_SendData(uint8_t data);

static void LCD_GotoXY(uint8_t line, uint8_t col){
	/* send command of DDRAM Address
	 * First Line: 	0x00
	 * Second Line: 0x40
	 * */
	if (line ==0){
		LCD_SendCMD(LCD_CMD_DDRAM + LCD_L1_ADDR +col );
	}else if(line == 1){
		LCD_SendCMD(LCD_CMD_DDRAM + LCD_L2_ADDR +col );
	}
}
static void LCD_SendCMD(uint8_t cmd){
	/* Set command mode (clear RS)
	 * Send high nibble cmd
	 * Start latching
	 * Send low nibble cmd
	 * Start latching
	 * Delay for 40 micro sec
	 */
	/* Command Mode */
	LCD_GPIO->ODR			&= ~(1<<LCD_CTRL_RS);
	/* Send Most 4 bits */
	LCD_GPIO->ODR			&= ~LCD_DATA_ODR_MASK;
	LCD_GPIO->ODR			|=  ( (cmd >> 4) << LCD_DATA_SHIFT );

	LCD_GPIO->ODR			|=  (1<<LCD_CTRL_EN);
	LCD_GPIO->ODR			&= ~(1<<LCD_CTRL_EN);
	/* Send Least 4 bits */
	LCD_GPIO->ODR			&= ~LCD_DATA_ODR_MASK;
	LCD_GPIO->ODR			|=  ( (cmd) << LCD_DATA_SHIFT );

	LCD_GPIO->ODR			|=  (1<<LCD_CTRL_EN);
	LCD_GPIO->ODR			&= ~(1<<LCD_CTRL_EN);
	/* wait for command to be executed */
	delayMs(1);
}
void LCD_Clear(void){
	LCD_SendCMD(LCD_CMD_CLEAR);
	delayMs(5);
}

static void LCD_SendData(uint8_t data){
	/* Set data mode (set RS)
	 * Send high nibble data
	 * Start latching
	 * Send low nibble data
	 * Start latching
	 * Delay for 40 micro sec
	 */
	/* Command Mode */
	LCD_GPIO->ODR			|=  (1<<LCD_CTRL_RS);
	/* Send Most 4 bits */
	LCD_GPIO->ODR			&= ~LCD_DATA_ODR_MASK;
	LCD_GPIO->ODR			|=  ( (data >> 4) << LCD_DATA_SHIFT );

	LCD_GPIO->ODR			|=  (1<<LCD_CTRL_EN);
	LCD_GPIO->ODR			&= ~(1<<LCD_CTRL_EN);
	/* Send Least 4 bits */
	LCD_GPIO->ODR			&= ~LCD_DATA_ODR_MASK;
	LCD_GPIO->ODR			|=  ( (data) << LCD_DATA_SHIFT );

	LCD_GPIO->ODR			|=  (1<<LCD_CTRL_EN);
	LCD_GPIO->ODR			&= ~(1<<LCD_CTRL_EN);
	/* wait for command to be executed */
	delayMs(1);
}
void LCD_Init(void){
	/* Initiate clock,I/O
	 * Wait for 50Ms
	 * Select 4 Bit, 5*7,2 lines (Function Set)
	 * No cursor, Blink (Display CMD)
	 * Auto Inc with no Shift (Entry )
	 * Clear LCD
	 */
	RCC->AHB1ENR 			|=  LCD_RCC;

	LCD_GPIO->MODER			&= ~LCD_DATA_MODER_MASK;
	LCD_GPIO->MODER			|=  LCD_DATA_MODER_OUT_MASK;
	LCD_GPIO->ODR			&= ~LCD_DATA_ODR_MASK;

	LCD_GPIO->MODER			&= ~LCD_CTRL_MODER_MASK;
	LCD_GPIO->MODER			|=  LCD_CTRL_MODER_OUT_MASK;
	LCD_GPIO->ODR			&= ~((1<<LCD_CTRL_EN)|(1<<LCD_CTRL_RS));



	delayMs(500);
	LCD_SendCMD(LCD_CMD_FUN_SET);
	LCD_SendCMD(LCD_CMD_DISP);
	LCD_SendCMD(LCD_CMD_ENTRY_INC);
	LCD_Clear();

	//	LCD_SendCMD(0x01);
	//	delayMs(5);
}
void LCD_DispChar(uint8_t data){
	LCD_SendData(data);
}
void LCD_DispCharXY(uint8_t line, uint8_t col,uint8_t data){
	LCD_GotoXY(line,col);
	LCD_DispChar(data);
}
void LCD_DispStr(uint8_t* str){
	uint8_t	 ind = 0;
	while(str[ind]){
		LCD_DispChar(str[ind]);
		ind++;
	}
}
void LCD_DispStrXY(uint8_t line, uint8_t col,uint8_t* str){
	LCD_GotoXY(line,col);
	LCD_DispStr(str);
}
void LCD_DispInt(uint32_t num){
	uint8_t i=0,arr[100],j;
	while(num>0)
	{
		arr[i]=num%10+'0';
		i++;
		num/=10;
	}
	arr[i]='\0';
	for(j=i;j>0;j--)
	{
		LCD_DispChar(arr[j-1]);
	}
	/*uint8_t numStr[21] = {0};
	sprintf(numStr, "%u",num);
	LCD_DispStr(numStr);*/
}
void LCD_DispIntXY(uint8_t line, uint8_t col,uint32_t num){
	LCD_GotoXY(line,col);
	LCD_DispInt(num);
}
