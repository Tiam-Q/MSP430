#include "digtal_route.h"


void DigtalRoute_GPIO_ConFig (void)
{
    P6DIR &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //����Ϊ����
    P6REN |= (BIT0+BIT1+BIT2+BIT3+BIT4);       //����/����ʹ��
    P6OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //��������
}













