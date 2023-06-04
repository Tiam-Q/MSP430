#include "bsp_key.h"
#include "bsp_delay.h"


int mode = 0;
int go = 0;

void Key_Exti_Config (void)
{
    P1IE |=BIT1;      //�����ж�
    P1IES |= BIT1;    //�½���
    P1IFG &= ~BIT1;   //�����жϱ�־λ

    P2IE |=BIT1;      //�����ж�
    P2IES |= BIT1;    //�½���
    P2IFG &= ~BIT1;   //�����жϱ�־λ
}


void Key_Init (void)
{
    P1DIR &= ~BIT1;   //����P1.1Ϊ����
    P1REN |= BIT1;    //����P1.1������/����
    P1OUT |= BIT1;    //P1.1����Ϊ����

    P2DIR &= ~BIT1;   //����P2.1Ϊ����
    P2REN |= BIT1;    //����P2.1������/����
    P2OUT |= BIT1;    //P2.1����Ϊ����
}


//unsigned char Key_Scan (void)
//{
//    if(key1 == 0||key2 == 0)
//    {
//        delay(20);   //��ʱ20��������
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



#pragma vector = PORT1_VECTOR    //�жϷ�����
__interrupt void Port1_ISR (void)
{
    P1IFG &= ~BIT1;          //�����жϱ�־λ
    if (P1IFG & BIT1)            //�ж�����
    {
        delay(20);               //��ʱ����
        if (P1IFG & BIT1)        //�ж�����
        {
            mode++;
            if(mode>2)
            {
                mode = 0;
            }
        }

    }
}


#pragma vector = PORT2_VECTOR    //�жϷ�����
__interrupt void Port2_ISR (void)
{
    P2IFG &= ~BIT1;          //�����жϱ�־λ
    if (P2IFG & BIT1)            //�ж�����
    {
        delay(20);               //��ʱ����
        if (P2IFG & BIT1)        //�ж�����
        {
            go = 1;
        }

    }
}

