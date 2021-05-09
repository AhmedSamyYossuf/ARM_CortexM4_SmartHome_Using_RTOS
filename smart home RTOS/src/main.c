
/* Includes */
#include <Task.h>
#include "stm32f4xx.h"
#include "delay.h"
#include "board.h"
#include "segment.h"
#include "keypad.h"
#include "LCD.h"
#include "ADC.h"
#include "timer.h"
#include "ultrasonic.h"
#include "Servo.h"
#include "uart.h"
#include "spi.h"
#include "EEPROM.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "event_groups.h"
#include "semphr.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */

/*	Objects	*/
extern	char g_myPassword[ PASS_LEN ];





int main(void)
{
	System_Init();

	Task_Init();

	while(1)
	{

	}


}

