#include "digtal_route.h"


void DigtalRoute_GPIO_ConFig (void)
{
    P6DIR &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //����Ϊ����
    P6REN |= (BIT0+BIT1+BIT2+BIT3+BIT4);       //����/����ʹ��
    P6OUT &= ~(BIT0+BIT1+BIT2+BIT3+BIT4);      //��������
}


/*****************************************************
 * @�������Ҷȼ��
 * @���������err�����    right����ת��ʶ       left:��ת��ʶ
 * @����ֵ��1����ת    0��ֱ��    2����ת    -1��ֹͣ
 *****************************************************/
int Read_Situation (void)
{
    if((P6IN & 0x1f) == 0x00)  //ȫ��
    {

    }
    else if((P6IN & 0x1f) == 0x1f)  //ȫ��
    {

    }

    else if(P6IN & BIT0)            //���ұ�������ɫ
    {

    }

    else if(P6IN & BIT1)            //�ұߵڶ���������ɫ
    {

    }

    else if(P6IN & BIT3)            //��ߵڶ���������ɫ
    {

    }
    else if(P6IN & BIT4)            //�����������ɫ
    {

    }

}









