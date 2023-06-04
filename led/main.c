#include <msp430.h> 
#include "./led/bsp_led.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	Led_Init ();
	while(1)
	{
	    Led1_On ();
	    delay (50);        //��ʱ����
	    Led1_Off ();
	    delay (50);        //��ʱ����
	    Led2_On ();
	    delay (50);        //��ʱ����
	    Led2_Off ();
	    delay (50);        //��ʱ����
	}

	return 0;
}


