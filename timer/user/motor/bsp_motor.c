#include "bsp_motor.h"

/****************************************************************************************
 * @�����������
 * @����: ϵͳʱ������\(TACCR0+1)    1MHZ\(TACCR0+1)����Ϊ10000hz ʵ��10526.32hz
 * @ռ�ձȼ���: (TACCR0-TACCRX)/TACCR0
 * @����˿�: P2.5   P2.4   P2.0    P1.3
 *                                ǰ
 *                  P1.3  (A)-------------(B)  P2.0
 *                          \_____________/
 *                          |             |
 *                          |_____________|
 *                          /              \
 *                  P2.4  (C)-------------(D)  P2.5
 *                                 ��
 * @MotorA IN1 P1.4    IN2 P1.5
 * @MotorB IN1 P3.0    IN2 P3.1
 * @MotorC IN1 P4.0    IN2 P4.1
 * @MotorD IN1 P4.2    IN2 P4.3
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

    /*����TA1.2Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
    TA1CCTL1 |= OUTMOD_6;

    /*����P2.1 IO����*/
    P2SEL |= BIT0;
    P2DIR |= BIT0;



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
}

static void Motor_Gpio_Init (void)
{
    MotorA_IN1_DIR;
    MotorA_IN2_DIR;
    MotorB_IN1_DIR;
    MotorB_IN2_DIR;
    MotorC_IN1_DIR;
    MotorC_IN2_DIR;
    MotorD_IN1_DIR;
    MotorD_IN2_DIR;

    MotorA_IN1_REN;
    MotorA_IN2_REN;
    MotorB_IN1_REN;
    MotorB_IN2_REN;
    MotorC_IN1_REN;
    MotorC_IN2_REN;
    MotorD_IN1_REN;
    MotorD_IN2_REN;

    MotorA_IN1_OUT_ReSet;
    MotorA_IN2_OUT_ReSet;
    MotorB_IN1_OUT_ReSet;
    MotorB_IN2_OUT_ReSet;
    MotorC_IN1_OUT_ReSet;
    MotorC_IN2_OUT_ReSet;
    MotorD_IN1_OUT_ReSet;
    MotorD_IN2_OUT_ReSet;
}


void Motor_Config (void)
{
    Motor_Tim_Init ();
    Motor_Gpio_Init ();
}

static void MotorA_Forward (void)   // ���A��ת
{
    MotorA_IN1_OUT_Set;
    MotorA_IN2_OUT_ReSet;
}

static void MotorA_Backward (void)  //���A��ת
{
    MotorA_IN1_OUT_ReSet;
    MotorA_IN2_OUT_Set;
}

static void MotorB_Forward (void)   //���B��ת
{
    MotorB_IN1_OUT_Set;
    MotorB_IN2_OUT_ReSet;
}

static void MotorB_Backward (void)  //���B��ת
{
    MotorB_IN1_OUT_ReSet;
    MotorB_IN2_OUT_Set;
}

static void MotorC_Forward (void)   //���C��ת
{
    MotorC_IN1_OUT_Set;
    MotorC_IN2_OUT_ReSet;
}

static void MotorC_Backward (void)  //���C��ת
{
    MotorC_IN1_OUT_ReSet;
    MotorC_IN2_OUT_Set;
}

static void MotorD_Forward (void)   //���D��ת
{
    MotorD_IN1_OUT_Set;
    MotorD_IN2_OUT_ReSet;
}

static void MotorD_Backward (void)  //���D��ת
{
    MotorD_IN1_OUT_ReSet;
    MotorD_IN2_OUT_Set;
}

void Car_Speed (int speed)   //�����ĸ�����ٶ�
{
    if(speed < 0)            //�ٶ�С��0��0
    {
        speed = 0;
    }
    else if(speed > 99)      //�ٶȴ���99��99
    {
        speed = 99;
    }
    MotorA_Pwm_Out = speed;
    MotorB_Pwm_Out = speed;
    MotorC_Pwm_Out = speed;
    MotorD_Pwm_Out = speed;
}

void Car_Forward (int speed) //С��ǰ��
{
    MotorA_Forward ();
    MotorB_Forward ();
    MotorC_Forward ();
    MotorD_Forward ();
    Car_Speed (speed);
}


void Car_Backward (int speed) //С������
{
    MotorA_Backward ();
    MotorB_Backward ();
    MotorC_Backward ();
    MotorD_Backward ();
    Car_Speed (speed);
}


void Car_Turn_Left (int speed) //B D�����ת   A C�����תʵ������ת
{
    MotorA_Backward ();
    MotorB_Forward ();
    MotorC_Backward ();
    MotorD_Forward ();
    Car_Speed (speed);
}


void Car_Turn_Right (int speed) //A C�����ת   B D�����תʵ������ת
{
    MotorA_Forward ();
    MotorB_Backward ();
    MotorC_Forward ();
    MotorD_Backward ();
    Car_Speed (speed);
}


void Car_Stop (void)            //С��ֹͣ
{
    Car_Speed (0);
}







