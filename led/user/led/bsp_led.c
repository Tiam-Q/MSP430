#include "bsp_led.h"

//引脚初始化
void Led_Init (void)
{
    //DIR寄存器，置0为输出模式，1为输入模式
    P1DIR |= BIT0;
    //输出低电平
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}

//共地接法，高电平点亮，P1.0引脚输出高电平
void Led1_On (void)
{
    P1OUT |= BIT0;
}

//p1.0输出低电平
void Led1_Off (void)
{
    P1OUT &= ~BIT0;
}

void Led2_On (void)
{
    P4OUT |= BIT7;
}

void Led2_Off (void)
{
    P4OUT &= ~BIT7;
}

//软件毫秒延时函数
void delay (int ms)
{
    int i,j;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<240;j++)
        {

        }
    }

}











