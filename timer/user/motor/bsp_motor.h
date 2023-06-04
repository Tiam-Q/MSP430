#ifndef BSP_MOTOR_H_
#define BSP_MOTOR_H_


#include<msp430.h>


#define MotorA_Pwm_Out              TA0CCR2
#define MotorB_Pwm_Out              TA1CCR1
#define MotorC_Pwm_Out              TA2CCR1
#define MotorD_Pwm_Out              TA2CCR2


#define MotorA_IN1_DIR             P1DIR |= BIT4       // P1.4
#define MotorA_IN1_REN             P1REN |= BIT4       // P1.4下拉启用
#define MotorA_IN1_OUT_Set         P1OUT |= BIT4       // P1.4输出高电平
#define MotorA_IN1_OUT_ReSet       P1OUT &= ~BIT4      // P1.4输出低电平

#define MotorA_IN2_DIR             P1DIR |= BIT5       // P1.5
#define MotorA_IN2_REN             P1REN |= BIT5       // P1.5下拉启用
#define MotorA_IN2_OUT_Set         P1OUT |= BIT5       // P1.5输出高电平
#define MotorA_IN2_OUT_ReSet       P1OUT &= ~BIT5       // P1.5输出低电平



#define MotorB_IN1_DIR             P3DIR |= BIT0       // P3.0
#define MotorB_IN1_REN             P3REN |= BIT0       // P3.0下拉启用
#define MotorB_IN1_OUT_Set         P3OUT |= BIT0       // P3.0输出高电平
#define MotorB_IN1_OUT_ReSet       P3OUT &= ~BIT0      // P3.0输出低电平

#define MotorB_IN2_DIR             P3DIR |= BIT1       // P3.1
#define MotorB_IN2_REN             P3REN |= BIT1       // P3.1下拉启用
#define MotorB_IN2_OUT_Set         P3OUT |= BIT1       // P3.1输出高电平
#define MotorB_IN2_OUT_ReSet       P3OUT &= ~BIT1      // P3.1输出低电平



#define MotorC_IN1_DIR             P4DIR |= BIT0       // P4.0
#define MotorC_IN1_REN             P4REN |= BIT0       // P4.0下拉启用
#define MotorC_IN1_OUT_Set         P4OUT |= BIT0       // P4.0输出高电平
#define MotorC_IN1_OUT_ReSet       P4OUT &= ~BIT0      // P4.0输出低电平

#define MotorC_IN2_DIR             P4DIR |= BIT1       // P4.1
#define MotorC_IN2_REN             P4REN |= BIT1       // P4.1下拉启用
#define MotorC_IN2_OUT_Set         P4OUT |= BIT1       // P4.1输出高电平
#define MotorC_IN2_OUT_ReSet       P4OUT &= ~BIT1      // P4.1输出低电平



#define MotorD_IN1_DIR             P4DIR |= BIT2       // P4.2
#define MotorD_IN1_REN             P4REN |= BIT2       // P4.2下拉启用
#define MotorD_IN1_OUT_Set         P4OUT |= BIT2       // P4.2下输出高电平
#define MotorD_IN1_OUT_ReSet       P4OUT &= ~BIT2      // P4.2下输出低电平

#define MotorD_IN2_DIR             P4DIR |= BIT3       // P4.3
#define MotorD_IN2_REN             P4REN |= BIT3       // P4.3下拉启用
#define MotorD_IN2_OUT_Set         P4OUT |= BIT3       // P4.3输出高电平
#define MotorD_IN2_OUT_ReSet       P4OUT &= ~BIT3      // P4.3输出低电平


void Motor_Config (void);                              //初始化
void Car_Forward (int speed);                          //小车前进
void Car_Backward (int speed);                         //小车后退
void Car_Turn_Left (int speed);                        //向左转
void Car_Turn_Right (int speed);                       //向右转
void Car_Stop (void);                                  //小车停止


#endif /*BSP_MOTOR_H_*/




















