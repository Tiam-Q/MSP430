#include "bsp_led.h"

//���ų�ʼ��
void Led_Init (void)
{
    //DIR�Ĵ�������0Ϊ���ģʽ��1Ϊ����ģʽ
    P1DIR |= BIT0;
    //����͵�ƽ
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}

//���ؽӷ����ߵ�ƽ������P1.0��������ߵ�ƽ
void Led1_On (void)
{
    P1OUT |= BIT0;
}

//p1.0����͵�ƽ
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

//���������ʱ����
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











