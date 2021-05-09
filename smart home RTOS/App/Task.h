/*
 * App.h
 *
 *  Created on: ???/???/????
 *      Author: User
 */

#ifndef TASK_H_
#define TASK_H_

#include "stm32f4xx.h"
#include "board.h"
#include "keypad.h"
#include "LCD.h"
#include "delay.h"
#include "EEPROM.h"
#include "Servo.h"
#include "ADC.h"
#include "ultrasonic.h"
#include "WIFI.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "event_groups.h"
#include "semphr.h"


#define PASS_LEN 			5
#define CONFIRM_SUCCESS		1
#define CONFIRM_FAIL		0
#define PASSWORD_SAVED		0x52
#define InDoorDis			20

extern EventGroupHandle_t	egOutput;
extern EventBits_t			eOut_Bits;
extern QueueHandle_t		Q_keypad;

extern	char g_myPassword[ PASS_LEN ];


#define		E_BTN_RIGHT		(1<<0)
#define		E_BTN_LEFT		(1<<1)
#define		E_BTN_UP		(1<<2)
#define		E_BUZZER		(1<<3)

#define		E_REC_LED		(1<<4)	//LED1
#define		E_LIV_LED		(1<<5)	//LED2
#define		E_BED_LED		(1<<6)	//LED3
#define		E_RELAY			(1<<7)

#define 	TEMP_THRESH		25



/*	Prototypes	*/
void T_Input (void* pvData);

void T_Temp (void* pvData);

void T_Door_Lock (void* pvData);

void T_Lights (void* pvData);

void T_Network (void* pvData);

void T_Memory (void* pvData);

void Task_Init(void);

/**********************Function************************/

void getPassword( char * password );

uint8_t confirmPassword( char const * password );

void FirstTimePassword(void);

void SavedPassword(void);

void ChangePassword(void);

void DoorLock(void);

void Temp_Sensor(void);

#endif /* TASK_H_ */
