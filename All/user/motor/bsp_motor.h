#ifndef BSP_MOTOR_H_
#define BSP_MOTOR_H_

#include<msp430.h>
#include<type.h>


#define MotorA1_Pwm_Out              TA1CCR1
#define MotorA2_Pwm_Out              TB0CCR2
#define MotorB1_Pwm_Out              TA2CCR1
#define MotorB2_Pwm_Out              TA2CCR2


void SysTick_Init (void);
void Motor_Init (void);
void Car_Forward (float speed);        //小车前进
void Car_Backward (float speed);       //小车后退
void Car_Turn_Left (float speed,float Turn_Speed);      //右边的B电机比左边的A电机转速快实现左转
void Car_Turn_Right (float speed,float Turn_Speed);     //右边的B电机比左边的A电机转速慢实现左转
void Car_Stop (void);                                   //小车停止
void Car_Right_CirCle (float speed);                    //顺时针旋转
void Car_Left_CirCle (float speed);                     //逆时针旋转


#endif /*BSP_MOTOR_H_*/



