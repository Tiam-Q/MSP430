#include "digtal_route.h"


void DigtalRoute_GPIO_ConFig (void)
{
    P6DIR &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //配置为输入
    P6REN |= (BIT0+BIT1+BIT2+BIT3+BIT4);       //上拉/下拉使能
    P6OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //引脚下拉
}


/*****************************************************
 * @函数：灰度检测
 * @输入参数：err：误差    right：右转标识       left:左转标识
 * @返回值：1：右转    0：直行    2：左转    -1：停止
 *****************************************************/
int Read_Situation (void)
{
    if((P6IN & 0x1f) == 0x00)  //全白
    {

    }
    else if((P6IN & 0x1f) == 0x1f)  //全黑
    {

    }

    else if(P6IN & BIT0)            //最右边碰到黑色
    {

    }

    else if(P6IN & BIT1)            //右边第二个碰到黑色
    {

    }

    else if(P6IN & BIT3)            //左边第二个碰到黑色
    {

    }
    else if(P6IN & BIT4)            //最左边碰到黑色
    {

    }

}









