#include <msp430.h> 
#include "bsp_motor.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	Motor_Config ();

	Car_Forward (80);
	//Car_Backward (80);                         //Ð¡³µºóÍË

	while(1)
	{

	}

	return 0;
}
