#include "motor.h"

/****************************************************************************************
 * @电机驱动函数
 * @周期: 系统时钟周期\(TACCR0+1)    1MHZ\(TACCR0+1)理论为10000hz 实测10526.32hz
 * @占空比计算: (TACCR0-TACCRX)/TACCR0
 *
 *                                前
 *            P1.2  P1.3  (A)-------------(B)  P1.4  P1.5
 *                          \_____________/
 *                          |             |
 *                          |_____________|
 *                          /              \
 *            P2.0  P2.1  (C)-------------(D)  P2.4  P2.5
 *                                 后
 *
****************************************************************************************/




static void Motor_Tim_Init (void)
{
    /*************************P2.5 TA2.2配置**********************************/
    TA2CTL |= TASSEL1;      // TA2时钟选择SMCLK   SMCLK的时钟为1MHZ   实际为1.05MHZ
    TA2CTL |= MC0;          // TA2选择为UP模式  即当从0计数到TACCR0时回到0，类似锯齿波

    TA2CCR0 = 100-1;       // 设置TACCR0的值   最大为0xFFFH
    TA2CCR2 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA2CCTL0 &= ~CAP;
    TA2CCTL2 &= ~CAP;

    /*设置TA2.2为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA2CCTL2 |= OUTMOD_6;

    /*设置P2.5 IO复用*/
    P2SEL |= BIT5;
    P2DIR |= BIT5;


    /*************************P2.4 TA2.1配置**********************************/
    TA2CCR1 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA2CCTL0 &= ~CAP;
    TA2CCTL1 &= ~CAP;

    /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA2CCTL1 |= OUTMOD_6;

    /*设置P2.4 IO复用*/
    P2SEL |= BIT4;
    P2DIR |= BIT4;



    /*************************P2.0 TA1.1配置**********************************/
    TA1CTL |= TASSEL1;      // TA1时钟选择SMCLK   SMCLK的时钟为1MHZ   实际为1.05MHZ
    TA1CTL |= MC0;          // TA1选择为UP模式  即当从0计数到TACCR0时回到0，类似锯齿波

    TA1CCR0 = 100-1;       // 设置TACCR0的值   最大为0xFFFH
    TA1CCR1 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA1CCTL0 &= ~CAP;
    TA1CCTL1 &= ~CAP;

    /*设置TA1.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA1CCTL1 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P2SEL |= BIT0;
    P2DIR |= BIT0;

    /*************************P2.1 TA1.2配置**********************************/
    TA1CCR2 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA1CCTL2 &= ~CAP;

    /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA1CCTL2 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P2SEL |= BIT1;
    P2DIR |= BIT1;



    /*************************P1.3 TA0.2配置**********************************/
    TA0CTL |= TASSEL1;      // TA0时钟选择SMCLK   SMCLK的时钟为1MHZ   实际为1.05MHZ
    TA0CTL |= MC0;          // TA0选择为UP模式  即当从0计数到TACCR0时回到0，类似锯齿波

    TA0CCR0 = 100-1;       // 设置TACCR0的值   最大为0xFFFH
    TA0CCR2 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA0CCTL0 &= ~CAP;
    TA0CCTL2 &= ~CAP;

    /*设置TA1.2为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA0CCTL2 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P1SEL |= BIT3;
    P1DIR |= BIT3;

    /*************************P1.2 TA0.1配置**********************************/
    TA0CCR1 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA0CCTL1 &= ~CAP;

    /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA0CCTL1 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P1SEL |= BIT2;
    P1DIR |= BIT2;

    /*************************P1.4 TA0.3配置**********************************/
    TA0CCR3 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA0CCTL3 &= ~CAP;

    /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA0CCTL3 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P1SEL |= BIT4;
    P1DIR |= BIT4;

    /*************************P1.5 TA0.4配置**********************************/
    TA0CCR4 = 100-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
    TA0CCTL4 &= ~CAP;

    /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA0CCTL4 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P1SEL |= BIT5;
    P1DIR |= BIT5;
}



void Motor_Config (void)
{
    Motor_Tim_Init ();
    Car_Stop ();            //小车停止
}

static void MotorA_Forward (int speed)   // 电机A正转
{
    MotorA1_Pwm_Out = speed;
    MotorA2_Pwm_Out = 0;

}

static void MotorA_Backward (int speed)  //电机A反转
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = speed;
}

static void MotorB_Forward (int speed)   //电机B正转
{
    MotorB1_Pwm_Out = speed;
    MotorB2_Pwm_Out = 0;
}

static void MotorB_Backward (int speed)  //电机B反转
{
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = speed;
}

static void MotorC_Forward (int speed)   //电机C正转
{
    MotorC1_Pwm_Out = speed;
    MotorC2_Pwm_Out = 0;
}

static void MotorC_Backward (int speed)  //电机C反转
{
    MotorC1_Pwm_Out = 0;
    MotorC2_Pwm_Out = speed;
}

static void MotorD_Forward (int speed)   //电机D正转
{
    MotorD1_Pwm_Out = speed;
    MotorD2_Pwm_Out = 0;
}

static void MotorD_Backward (int speed)  //电机D反转
{
    MotorD1_Pwm_Out = 0;
    MotorD2_Pwm_Out = speed;
}


void Car_Forward (int speed) //小车前进
{
    MotorA_Forward (speed);
    MotorB_Forward (speed);
    MotorC_Forward (speed);
    MotorD_Forward (speed);
}


void Car_Backward (int speed) //小车后退
{
    MotorA_Backward (speed);
    MotorB_Backward (speed);
    MotorC_Backward (speed);
    MotorD_Backward (speed);
}


void Car_Turn_Left (int speed) //B D电机正转   A C电机反转实现向左转
{
    MotorA_Backward (speed);
    MotorB_Forward (speed);
    MotorC_Backward (speed);
    MotorD_Forward (speed);
}


void Car_Turn_Right (int speed) //A C电机正转   B D电机反转实现向右转
{
    MotorA_Forward (speed);
    MotorB_Backward (speed);
    MotorC_Forward (speed);
    MotorD_Backward (speed);
}


void Car_Stop (void)            //小车停止
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
















