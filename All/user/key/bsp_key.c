#include "bsp_key.h"
#include "bsp_delay.h"


int mode = 0;
int go = 0;

void Key_Exti_Config (void)
{
    P1IE |=BIT1;      //启用中断
    P1IES |= BIT1;    //下降沿
    P1IFG &= ~BIT1;   //清零中断标志位

    P2IE |=BIT1;      //启用中断
    P2IES |= BIT1;    //下降沿
    P2IFG &= ~BIT1;   //清零中断标志位
}


void Key_Init (void)
{
    P1DIR &= ~BIT1;   //配置P1.1为输入
    P1REN |= BIT1;    //启用P1.1的上拉/下拉
    P1OUT |= BIT1;    //P1.1配置为上拉

    P2DIR &= ~BIT1;   //配置P2.1为输入
    P2REN |= BIT1;    //启用P2.1的上拉/下拉
    P2OUT |= BIT1;    //P2.1配置为上拉
}


//unsigned char Key_Scan (void)
//{
//    if(key1 == 0||key2 == 0)
//    {
//        delay(20);   //延时20毫秒消抖
//        if(key1 == 0)
//        {
//            return 1;
//        }
//        else if(key2 == 0)
//        {
//            return 2;
//        }
//        return 0;
//    }
//
//}



#pragma vector = PORT1_VECTOR    //中断服务函数
__interrupt void Port1_ISR (void)
{
    P1IFG &= ~BIT1;          //清零中断标志位
    if (P1IFG & BIT1)            //中断来临
    {
        delay(20);               //延时消抖
        if (P1IFG & BIT1)        //中断来临
        {
            mode++;
            if(mode>2)
            {
                mode = 0;
            }
        }

    }
}


#pragma vector = PORT2_VECTOR    //中断服务函数
__interrupt void Port2_ISR (void)
{
    P2IFG &= ~BIT1;          //清零中断标志位
    if (P2IFG & BIT1)            //中断来临
    {
        delay(20);               //延时消抖
        if (P2IFG & BIT1)        //中断来临
        {
            go = 1;
        }

    }
}

