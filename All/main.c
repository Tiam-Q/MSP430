#include <msp430.h> 
#include "bsp_hc05.h"
#include "digtal_route.h"
#include "bsp_uart.h"
#include "bsp_delay.h"
#include "filter.h"
#include "bsp_motor.h"
#include "type.h"
#include "pid.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	float speed = 1000;
	float turn_speed = 0;
	int flag = 0;
	int state = 1;

	SysTick_Init ();
	OLED_Init ();
	Motor_Init ();
	USART0_Config();              //P3.3(TX)  P3.4(RX)
	USART1_Config();              //P4.4(TX)  P4.5(RX)   连接USB
	DigtalRoute_GPIO_ConFig ();


	OLED_Clear();                 //OLED清屏

	_EINT ();                     //打开全局中断


	while(1)
	{

	}
}



