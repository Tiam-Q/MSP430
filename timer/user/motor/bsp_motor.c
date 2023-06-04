#include "bsp_motor.h"

/****************************************************************************************
 * @电机驱动函数
 * @周期: 系统时钟周期\(TACCR0+1)    1MHZ\(TACCR0+1)理论为10000hz 实测10526.32hz
 * @占空比计算: (TACCR0-TACCRX)/TACCR0
 * @输出端口: P2.5   P2.4   P2.0    P1.3
 *                                前
 *                  P1.3  (A)-------------(B)  P2.0
 *                          \_____________/
 *                          |             |
 *                          |_____________|
 *                          /              \
 *                  P2.4  (C)-------------(D)  P2.5
 *                                 后
 * @MotorA IN1 P1.4    IN2 P1.5
 * @MotorB IN1 P3.0    IN2 P3.1
 * @MotorC IN1 P4.0    IN2 P4.1
 * @MotorD IN1 P4.2    IN2 P4.3
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

    /*设置TA1.2为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
    TA1CCTL1 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
    P2SEL |= BIT0;
    P2DIR |= BIT0;



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

static void MotorA_Forward (void)   // 电机A正转
{
    MotorA_IN1_OUT_Set;
    MotorA_IN2_OUT_ReSet;
}

static void MotorA_Backward (void)  //电机A反转
{
    MotorA_IN1_OUT_ReSet;
    MotorA_IN2_OUT_Set;
}

static void MotorB_Forward (void)   //电机B正转
{
    MotorB_IN1_OUT_Set;
    MotorB_IN2_OUT_ReSet;
}

static void MotorB_Backward (void)  //电机B反转
{
    MotorB_IN1_OUT_ReSet;
    MotorB_IN2_OUT_Set;
}

static void MotorC_Forward (void)   //电机C正转
{
    MotorC_IN1_OUT_Set;
    MotorC_IN2_OUT_ReSet;
}

static void MotorC_Backward (void)  //电机C反转
{
    MotorC_IN1_OUT_ReSet;
    MotorC_IN2_OUT_Set;
}

static void MotorD_Forward (void)   //电机D正转
{
    MotorD_IN1_OUT_Set;
    MotorD_IN2_OUT_ReSet;
}

static void MotorD_Backward (void)  //电机D反转
{
    MotorD_IN1_OUT_ReSet;
    MotorD_IN2_OUT_Set;
}

void Car_Speed (int speed)   //设置四个电机速度
{
    if(speed < 0)            //速度小于0置0
    {
        speed = 0;
    }
    else if(speed > 99)      //速度大于99置99
    {
        speed = 99;
    }
    MotorA_Pwm_Out = speed;
    MotorB_Pwm_Out = speed;
    MotorC_Pwm_Out = speed;
    MotorD_Pwm_Out = speed;
}

void Car_Forward (int speed) //小车前进
{
    MotorA_Forward ();
    MotorB_Forward ();
    MotorC_Forward ();
    MotorD_Forward ();
    Car_Speed (speed);
}


void Car_Backward (int speed) //小车后退
{
    MotorA_Backward ();
    MotorB_Backward ();
    MotorC_Backward ();
    MotorD_Backward ();
    Car_Speed (speed);
}


void Car_Turn_Left (int speed) //B D电机正转   A C电机反转实现向左转
{
    MotorA_Backward ();
    MotorB_Forward ();
    MotorC_Backward ();
    MotorD_Forward ();
    Car_Speed (speed);
}


void Car_Turn_Right (int speed) //A C电机正转   B D电机反转实现向右转
{
    MotorA_Forward ();
    MotorB_Backward ();
    MotorC_Forward ();
    MotorD_Backward ();
    Car_Speed (speed);
}


void Car_Stop (void)            //小车停止
{
    Car_Speed (0);
}







