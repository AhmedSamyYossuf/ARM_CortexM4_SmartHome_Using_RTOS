/*
 * App.c
 *
 *  Created on: Nov 25, 2020
 *      Author: asmy2
 */
#include <Task.h>

char g_myPassword[ PASS_LEN ];

void getPassword( char * password )
{
	uint8_t i;
	for( i = 0 ; i<PASS_LEN; i++ )
	{
		xQueueReceive(Q_keypad,&password[i],portMAX_DELAY);
		vTaskDelay(1000);
		LCD_DispCharXY(1,i,'*');
	}
}

uint8_t confirmPassword( char const * password )
{
	uint8_t i = 0;
	uint8_t result = CONFIRM_SUCCESS;
	uint8_t new_key;

	for( i = 0; i<PASS_LEN; i++ )
	{
		xQueueReceive(Q_keypad,&new_key,portMAX_DELAY);
		vTaskDelay(1000);
		LCD_DispCharXY(1,i,'*');
		if( new_key != password[i] )
		{
			result = CONFIRM_FAIL;
		}
	}
	return result;
}


void FirstTimePassword(void)
{
	uint8_t i = 0;
	do
	{
		LCD_Clear();
		LCD_DispStrXY(0,0,"Enter pass: ");
		getPassword( g_myPassword );
		LCD_Clear();
		LCD_DispStrXY(0,0,"Confirm pass: ");
	}
	while( confirmPassword( g_myPassword ) != CONFIRM_SUCCESS );

	LCD_Clear();
	LCD_DispStrXY(0,0,"Success ");
	delayMs(2000);
	EEPROM_WriteByte(0xFF, PASSWORD_SAVED );
	/* Add the new password to the EEPROM */
	for(i=0; i<PASS_LEN; i++)
	{
		EEPROM_WriteByte(0xF0+i,g_myPassword[i]);
	}
}


void SavedPassword(void)
{
	uint8_t i = 0;
	uint8_t Password_count = 0;
	/*
	for(i=0; i<PASS_LEN; i++)
	{
		EEPROM_ReadByte(0xF0+i,&g_myPassword[i]);
	}
	*/
	LCD_Clear();
	LCD_DispStrXY(0,0,"Check pass: ");
	while( (confirmPassword(g_myPassword) != CONFIRM_SUCCESS ) )
	{
		/* Check if the user entered it incorrectly or not in 3 times */
		if( Password_count >=3 )
		{
			LCD_Clear();
			LCD_DispStrXY(0,0,"Unauthorized ");
			Buz_On();
			vTaskDelay(5000);
			Buz_Off();
			Password_count = 0;
		}
		Password_count++;
		LCD_Clear();
		LCD_DispStrXY(0,0,"Check pass: ");
	}
	LCD_Clear();
	LCD_DispStrXY(0,0,"Confirmed ");
	vTaskDelay(2000);

}

void ChangePassword(void)
{
	SavedPassword();
	FirstTimePassword();
}

void DoorLock(void){
	uint8_t key = 0;
	/* Clock -> Internal 16 MHz */

	/*LCD_displayXY(0,0,"1. Enter pw");
	 * LCD_dispalyXY(1,0,"2. Change pw");
	 *
	 */
	LCD_Clear();
	LCD_DispStrXY(0,0,"4. Enter PW");
	LCD_DispStrXY(1,0,"5. Change PW");

	xQueueReceive(Q_keypad,&key,portMAX_DELAY);
	vTaskDelay(1000);
	switch(key)
	{
	case 4: SavedPassword();
	//Servo_SetPosition(POS_DEG_90);
	xEventGroupSetBits(egOutput,E_RELAY);
	LCD_Clear();
	LCD_DispStr("House is opened");
	//Servo_SetPosition(POS_DEG_0);
	vTaskDelay(2000);
	xEventGroupSetBits(egOutput,E_RELAY);
	LCD_Clear();
	LCD_DispStr("House is closed");

	xEventGroupSetBits(egOutput,E_REC_LED);





	break;
	case 5: ChangePassword();
	break;
	default:
		break;
	}

	/* get the password from EEPROM */


}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void Temp_Sensor(void){
	uint32_t adcValue = 0;
	uint8_t str[30];
	ADC1_SelectChannel(CH1);

	/* 4096 > 3.3v
	 * adc_read > x
	 * 3300 mv / 10
	 */
	adcValue = ADC1_Read();
	adcValue = adcValue*(330)/4096;

	sprintf(str,"Room Temp = %d\n ",adcValue);
	Uart_SendString(USART2,str);

	if(adcValue>TEMP_THRESH){
		Buz_On();
		//if(WIFI_SendCmd("AT+CIPSEND=29\r\n","OK",1000)){
			sprintf(str,"The Temp. is too high  %d  C\n",adcValue);
			Uart_SendString(USART2,str);
		//}
		vTaskDelay(3000);
		Buz_Off();
	}else{
		Buz_Off();
	}
	vTaskDelay(5000);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void System_Init(void)
{


	RCC_DeInit();				/* Adapt PLL to the internal 16 MHz RC oscillator */
	SystemCoreClockUpdate();	/* Update SystemCoreClock */
	LCD_Init();
	Keypad_Init();
	EEPROM_Init();
	Buz_Init();
	ADC1_Init();
	Relay_Init();
	Leds_Init(0xFF);
	Uart_Init(USART2,9600);
	Btn_Init(BTN_RIGHT);
	Btn_Init(BTN_LEFT);
	Btn_Init(BTN_UP);
	Btn_Init(BTN_DOWN);
}
