#ifndef MOTOR_H_
#define MOTOR_H_


#include<msp430.h>


#define MotorA1_Pwm_Out              TA0CCR1
#define MotorA2_Pwm_Out              TA0CCR2
#define MotorB1_Pwm_Out              TA0CCR3
#define MotorB2_Pwm_Out              TA0CCR4
#define MotorC1_Pwm_Out              TA1CCR1
#define MotorC2_Pwm_Out              TA1CCR2
#define MotorD1_Pwm_Out              TA2CCR1
#define MotorD2_Pwm_Out              TA2CCR2



void Motor_Config (void);                              //初始化
void Car_Forward (int speed);                          //小车前进
void Car_Backward (int speed);                         //小车后退
void Car_Turn_Left (int speed);                        //向左转
void Car_Turn_Right (int speed);                       //向右转
void Car_Stop (void);                                  //小车停止


#endif /*MOTOR_H_*/













