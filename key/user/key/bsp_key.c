#include "bsp_key.h"
#include "bsp_delay.h"


void Key_Init (void)
{
    P1DIR &= ~BIT1;   //配置P1.1为输入
    P1REN |= BIT1;    //启用P1.1的上拉/下拉
    P1OUT |= BIT1;    //P1.1配置为上拉

    P2DIR &= ~BIT1;   //配置P1.1为输入
    P2REN |= BIT1;    //启用P1.1的上拉/下拉
    P2OUT |= BIT1;    //P1.1配置为上拉
}


unsigned char Key_Scan (void)
{
    if(key1 == 0||key2 == 0)
    {
        delay(20);   //延时20毫秒消抖
        if(key1 == 0)
        {
            return 1;
        }
        else if(key2 == 0)
        {
            return 2;
        }
        return 0;
    }

}




