/*
 * Task.c
 *
 *  Created on: Dec 11, 2020
 *      Author: ahmed
 */
#include "Task.h"

EventGroupHandle_t	egOutput;
EventBits_t			eOut_Bits;

QueueHandle_t		Q_keypad;

void Task_Init(void){

	/*	Objects Initialization	*/
	egOutput = xEventGroupCreate();
	Q_keypad = xQueueCreate(PASS_LEN , sizeof(char));

	/* Task Creation */
	xTaskCreate(T_Input,NULL,100,NULL,1,NULL);
	xTaskCreate(T_Temp,NULL,100,NULL,6,NULL);
	xTaskCreate(T_Door_Lock,NULL,100,NULL,5,NULL);
	xTaskCreate(T_Lights,NULL,100,NULL,4,NULL);
	//xTaskCreate(T_Network,NULL,100,NULL,3,NULL);
	//xTaskCreate(T_Memory,NULL,100,NULL,2,NULL);


	/*	Start Scheduler	*/
	vTaskStartScheduler();
}

void T_Input (void* pvData)
{
	uint8_t key ;
	while(1)
	{
		if( Keypad_GetKey() != 0){

			key = Keypad_GetKey();
			xQueueSend(Q_keypad,&key,1000);
		}
		if(Btn_isPressed(BTN_RIGHT))
			{
				xEventGroupSetBits(egOutput,E_BTN_RIGHT);
				while(Btn_isPressed(BTN_RIGHT))
				{
					vTaskDelay(10);
				}
			}
		if(Btn_isPressed(BTN_LEFT))
			{
				xEventGroupSetBits(egOutput,E_BTN_LEFT);
				while(Btn_isPressed(BTN_LEFT))
				{
					vTaskDelay(10);
				}
			}
		if(Btn_isPressed(BTN_UP))
			{
				xEventGroupSetBits(egOutput,E_BTN_UP);
				while(Btn_isPressed(BTN_UP))
				{
					vTaskDelay(10);
				}
			}

		vTaskDelay(100);

	}
}

void T_Temp (void* pvData)
{
	while(1)
	{
		Temp_Sensor();
	}
}

void T_Door_Lock (void* pvData)
{
	uint8_t EEPROM_checkByte = 0;
	EEPROM_ReadByte(0xFF,&EEPROM_checkByte);
	/* If its first time initializing the system, ask the user for a new password */
	if( EEPROM_checkByte != PASSWORD_SAVED )
	{
		FirstTimePassword();
	}
	else{
		for(uint8_t i=0; i<PASS_LEN; i++)
			{
				EEPROM_ReadByte(0xF0+i,&g_myPassword[i]);
			}
	}

	while(1)
	{
		eOut_Bits = xEventGroupWaitBits(
						egOutput,
						E_BTN_UP,
						1,
						1,
						1000
				);

		if(eOut_Bits & (E_BTN_UP))
		{
			DoorLock();
		}

		vTaskDelay(50);

	}
}

void T_Lights (void* pvData)
{
	while(1)
	{

		eOut_Bits = xEventGroupWaitBits(
					egOutput,
					(E_BTN_RIGHT|E_BTN_LEFT|E_BUZZER|E_REC_LED|E_LIV_LED|E_BED_LED|E_RELAY),
					0,
					0,
					1000
			);

			if(eOut_Bits & (E_BTN_RIGHT))
				{
					Leds_Toggle(0x01);
					xEventGroupClearBits(egOutput,E_BTN_RIGHT);
				}
			if(eOut_Bits & (E_BTN_LEFT))
				{
					Leds_Toggle(0x02);
					xEventGroupClearBits(egOutput,E_BTN_LEFT);
				}

			if(eOut_Bits & (E_REC_LED))
			{
				Leds_On(0x01);
				xEventGroupClearBits(egOutput,E_REC_LED);
			}
			if(eOut_Bits & (E_RELAY))
				{
					Relay_Toggle();
					xEventGroupClearBits(egOutput,E_RELAY);
				}

			vTaskDelay(100);

	}
}

void T_Network (void* pvData)
{
	while(1);
}

void T_Memory (void* pvData)
{
	while(1);
}


