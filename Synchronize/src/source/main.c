/*
	* File: main.c
	* Author: Le Quang
	* Date: 27/05/2023
	* Description: operate project
*/

#include "Synchronize.h"

int main() 
{
		gpioConfig();
		interruptTIM1Config();
		interruptTIM3Config();
		interruptConfig();
		initPWM();
		initADC();
		lcd_init();

		while(1)
		{
			updateSpeed();
			updatePWM(pidController());
			controlStepper (150, 80);
		}
    
}