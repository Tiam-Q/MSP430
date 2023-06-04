#include <msp430.h> 
#include "bsp_uart.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	USART1_Config();
	_EINT ();          //打开全局中断

	send1_buf("测试\n");

	while(1)
	{

	}
}
