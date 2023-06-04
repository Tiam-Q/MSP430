#include <msp430.h> 
#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_led.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Led_Init ();
	Key_Init ();
	Key_Exti_Config ();

	_EINT ();          //打开全局中断

	while(1)
	{

	}

	return 0;
}



