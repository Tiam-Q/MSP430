#include <msp430.h> 
#include "bsp_route.h"
#include "bsp_uart.h"
#include "bsp_delay.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	USART1_Config();              //P4.4(TX)  P4.5(RX)   ����USB
	Adc_Init ();


	__bis_SR_register(LPM0_bits + GIE);       // ����Enter LPM0, ʹ���ж�
	__no_operation();


	while(1)
	{

	}

	return 0;
}
