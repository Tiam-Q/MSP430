#include "digtal_route.h"


void DigtalRoute_GPIO_ConFig (void)
{
    P6DIR &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //配置为输入
    P6REN |= (BIT0+BIT1+BIT2+BIT3+BIT4);       //上拉/下拉使能
    P6OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //引脚下拉
}













