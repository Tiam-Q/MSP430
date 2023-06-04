#include <msp430.h> 
#include "digtal_route.h"
#include "bsp_uart.h"
#include <stdio.h>
#include<string.h>


void delay (int ms)        //延时函数
{
    int i,j;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<240;j++)
        {

        }
    }

}


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int err = 0;
	int a =0;

	DigtalRoute_GPIO_ConFig ();
	USART1_Config();

	while(1)
	{
	    switch(P6IN&0x1f)
	    {
	    case 0x00:                    //00000全白直行
	        a =0;
	        err = 0;
	        break;
	    case 0x01:                    //00001最右边碰到黑色  左转
	        a = 1;
	        err = 4;
	        break;
	    case 0x02:                    //00010右边第二个碰到黑色  左转
	        a = 2;
	        break;
	    case 0x04:                    //00100中间碰到黑色直行
	        a = 3;
	        err = 2;
	        break;
	    case 0x08:                    //01000左边第二个碰到黑色右转
	        a = 4;
	        break;
	    case 0x10:                    //10000最左边碰到黑色右转
	        a = 5;
	        err = 0;
	        break;
	    case 0x1f:                    //11111全黑停止
	        break;
	    default:
	        break;

	    }
	    printf("%d\n",a);
	    delay(5000);
	}
}
