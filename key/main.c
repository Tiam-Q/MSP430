#include <msp430.h> 
#include "bsp_led.h"
#include "bsp_key.h"
#include"bsp_delay.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Led_Init ();
	Key_Init ();

	while(1)
	{
	    if(Key_Scan() == 1)
	    {
	       Led1_On();
	    }
	    else if(Key_Scan() == 2)
	    {
	        Led2_On();
	    }
	    else
	    {
	        Led1_Off();
	        Led2_Off();
	    }
	}

	return 0;
}





