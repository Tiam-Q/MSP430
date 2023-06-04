#include "motor.h"

/****************************************************************************************
 * @�����������
 * @����: ϵͳʱ������\(TACCR0+1)    1MHZ\(TACCR0+1)����Ϊ10000hz ʵ��10526.32hz
 * @ռ�ձȼ���: (TACCR0-TACCRX)/TACCR0
 *
 *                                ǰ
 *            P1.2  P1.3  (A)-------------(B)  P1.4  P1.5
 *                          \_____________/
 *                          |             |
 *                          |_____________|
 *                          /              \
 *            P2.0  P2.1  (C)-------------(D)  P2.4  P2.5
 *                                 ��
 *
****************************************************************************************/




static void Motor_Tim_Init (void)
{
    /*************************P2.5 TA2.2����**********************************/
    TA2CTL |= TASSEL1;      // TA2ʱ��ѡ��SMCLK   SMCLK��ʱ��Ϊ1MHZ   ʵ��Ϊ1.05MHZ
    TA2CTL |= MC0;          // TA2ѡ��ΪUPģʽ  ������0������TACCR0ʱ�ص�0�����ƾ�ݲ�

    TA2CCR0 = 100-1;       // ����TACCR0��ֵ   ���Ϊ0xFFFH
    TA2CCR2 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA2CCTL0 &= ~CAP;
    TA2CCTL2 &= ~CAP;

    /*����TA2.2Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA2CCTL2 |= OUTMOD_6;

    /*����P2.5 IO����*/
    P2SEL |= BIT5;
    P2DIR |= BIT5;


    /*************************P2.4 TA2.1����**********************************/
    TA2CCR1 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA2CCTL0 &= ~CAP;
    TA2CCTL1 &= ~CAP;

    /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA2CCTL1 |= OUTMOD_6;

    /*����P2.4 IO����*/
    P2SEL |= BIT4;
    P2DIR |= BIT4;



    /*************************P2.0 TA1.1����**********************************/
    TA1CTL |= TASSEL1;      // TA1ʱ��ѡ��SMCLK   SMCLK��ʱ��Ϊ1MHZ   ʵ��Ϊ1.05MHZ
    TA1CTL |= MC0;          // TA1ѡ��ΪUPģʽ  ������0������TACCR0ʱ�ص�0�����ƾ�ݲ�

    TA1CCR0 = 100-1;       // ����TACCR0��ֵ   ���Ϊ0xFFFH
    TA1CCR1 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA1CCTL0 &= ~CAP;
    TA1CCTL1 &= ~CAP;

    /*����TA1.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA1CCTL1 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P2SEL |= BIT0;
    P2DIR |= BIT0;

    /*************************P2.1 TA1.2����**********************************/
    TA1CCR2 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA1CCTL2 &= ~CAP;

    /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA1CCTL2 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P2SEL |= BIT1;
    P2DIR |= BIT1;



    /*************************P1.3 TA0.2����**********************************/
    TA0CTL |= TASSEL1;      // TA0ʱ��ѡ��SMCLK   SMCLK��ʱ��Ϊ1MHZ   ʵ��Ϊ1.05MHZ
    TA0CTL |= MC0;          // TA0ѡ��ΪUPģʽ  ������0������TACCR0ʱ�ص�0�����ƾ�ݲ�

    TA0CCR0 = 100-1;       // ����TACCR0��ֵ   ���Ϊ0xFFFH
    TA0CCR2 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA0CCTL0 &= ~CAP;
    TA0CCTL2 &= ~CAP;

    /*����TA1.2Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA0CCTL2 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P1SEL |= BIT3;
    P1DIR |= BIT3;

    /*************************P1.2 TA0.1����**********************************/
    TA0CCR1 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA0CCTL1 &= ~CAP;

    /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA0CCTL1 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P1SEL |= BIT2;
    P1DIR |= BIT2;

    /*************************P1.4 TA0.3����**********************************/
    TA0CCR3 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA0CCTL3 &= ~CAP;

    /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA0CCTL3 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P1SEL |= BIT4;
    P1DIR |= BIT4;

    /*************************P1.5 TA0.4����**********************************/
    TA0CCR4 = 100-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
    TA0CCTL4 &= ~CAP;

    /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA0CCTL4 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P1SEL |= BIT5;
    P1DIR |= BIT5;
}



void Motor_Config (void)
{
    Motor_Tim_Init ();
    Car_Stop ();            //С��ֹͣ
}

static void MotorA_Forward (int speed)   // ���A��ת
{
    MotorA1_Pwm_Out = speed;
    MotorA2_Pwm_Out = 0;

}

static void MotorA_Backward (int speed)  //���A��ת
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = speed;
}

static void MotorB_Forward (int speed)   //���B��ת
{
    MotorB1_Pwm_Out = speed;
    MotorB2_Pwm_Out = 0;
}

static void MotorB_Backward (int speed)  //���B��ת
{
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = speed;
}

static void MotorC_Forward (int speed)   //���C��ת
{
    MotorC1_Pwm_Out = speed;
    MotorC2_Pwm_Out = 0;
}

static void MotorC_Backward (int speed)  //���C��ת
{
    MotorC1_Pwm_Out = 0;
    MotorC2_Pwm_Out = speed;
}

static void MotorD_Forward (int speed)   //���D��ת
{
    MotorD1_Pwm_Out = speed;
    MotorD2_Pwm_Out = 0;
}

static void MotorD_Backward (int speed)  //���D��ת
{
    MotorD1_Pwm_Out = 0;
    MotorD2_Pwm_Out = speed;
}


void Car_Forward (int speed) //С��ǰ��
{
    MotorA_Forward (speed);
    MotorB_Forward (speed);
    MotorC_Forward (speed);
    MotorD_Forward (speed);
}


void Car_Backward (int speed) //С������
{
    MotorA_Backward (speed);
    MotorB_Backward (speed);
    MotorC_Backward (speed);
    MotorD_Backward (speed);
}


void Car_Turn_Left (int speed) //B D�����ת   A C�����תʵ������ת
{
    MotorA_Backward (speed);
    MotorB_Forward (speed);
    MotorC_Backward (speed);
    MotorD_Forward (speed);
}


void Car_Turn_Right (int speed) //A C�����ת   B D�����תʵ������ת
{
    MotorA_Forward (speed);
    MotorB_Backward (speed);
    MotorC_Forward (speed);
    MotorD_Backward (speed);
}


void Car_Stop (void)            //С��ֹͣ
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = 0;
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = 0;
    MotorC1_Pwm_Out = 0;
    MotorC2_Pwm_Out = 0;
    MotorD1_Pwm_Out = 0;
    MotorD2_Pwm_Out = 0;
}
















