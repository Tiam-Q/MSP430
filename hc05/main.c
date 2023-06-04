#include <msp430.h> 
#include "bsp_hc05.h"
#include "bsp_uart.h"
#include <stdio.h>
#include <string.h>

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	HC05_Init();
	Led_Init ();

	_EINT();

	while(1)
	{
	}

}
