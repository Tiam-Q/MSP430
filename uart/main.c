#include <msp430.h> 
#include "bsp_uart.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	USART1_Config();
	_EINT ();          //��ȫ���ж�

	send1_buf("����\n");

	while(1)
	{

	}
}
