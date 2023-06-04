#include "bsp_key.h"
#include "bsp_delay.h"


void Key_Init (void)
{
    P1DIR &= ~BIT1;   //����P1.1Ϊ����
    P1REN |= BIT1;    //����P1.1������/����
    P1OUT |= BIT1;    //P1.1����Ϊ����

    P2DIR &= ~BIT1;   //����P1.1Ϊ����
    P2REN |= BIT1;    //����P1.1������/����
    P2OUT |= BIT1;    //P1.1����Ϊ����
}


unsigned char Key_Scan (void)
{
    if(key1 == 0||key2 == 0)
    {
        delay(20);   //��ʱ20��������
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




