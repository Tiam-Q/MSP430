#include <msp430.h> 
#include "digtal_route.h"
#include "bsp_uart.h"
#include <stdio.h>
#include<string.h>


void delay (int ms)        //��ʱ����
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
	    case 0x00:                    //00000ȫ��ֱ��
	        a =0;
	        err = 0;
	        break;
	    case 0x01:                    //00001���ұ�������ɫ  ��ת
	        a = 1;
	        err = 4;
	        break;
	    case 0x02:                    //00010�ұߵڶ���������ɫ  ��ת
	        a = 2;
	        break;
	    case 0x04:                    //00100�м�������ɫֱ��
	        a = 3;
	        err = 2;
	        break;
	    case 0x08:                    //01000��ߵڶ���������ɫ��ת
	        a = 4;
	        break;
	    case 0x10:                    //10000�����������ɫ��ת
	        a = 5;
	        err = 0;
	        break;
	    case 0x1f:                    //11111ȫ��ֹͣ
	        break;
	    default:
	        break;

	    }
	    printf("%d\n",a);
	    delay(5000);
	}
}
