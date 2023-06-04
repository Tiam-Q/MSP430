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
void Car_Forward (float speed);        //С��ǰ��
void Car_Backward (float speed);       //С������
void Car_Turn_Left (float speed,float Turn_Speed);      //�ұߵ�B�������ߵ�A���ת�ٿ�ʵ����ת
void Car_Turn_Right (float speed,float Turn_Speed);     //�ұߵ�B�������ߵ�A���ת����ʵ����ת
void Car_Stop (void);                                   //С��ֹͣ
void Car_Right_CirCle (float speed);                    //˳ʱ����ת
void Car_Left_CirCle (float speed);                     //��ʱ����ת


#endif /*BSP_MOTOR_H_*/



