#include <msp430.h> 
#include "motor.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	Motor_Config ();


	Car_Forward (50);


	while(1)
	{

	}

	return 0;
}
