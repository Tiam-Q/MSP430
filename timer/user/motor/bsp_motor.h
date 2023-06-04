#ifndef BSP_MOTOR_H_
#define BSP_MOTOR_H_


#include<msp430.h>


#define MotorA_Pwm_Out              TA0CCR2
#define MotorB_Pwm_Out              TA1CCR1
#define MotorC_Pwm_Out              TA2CCR1
#define MotorD_Pwm_Out              TA2CCR2


#define MotorA_IN1_DIR             P1DIR |= BIT4       // P1.4
#define MotorA_IN1_REN             P1REN |= BIT4       // P1.4��������
#define MotorA_IN1_OUT_Set         P1OUT |= BIT4       // P1.4����ߵ�ƽ
#define MotorA_IN1_OUT_ReSet       P1OUT &= ~BIT4      // P1.4����͵�ƽ

#define MotorA_IN2_DIR             P1DIR |= BIT5       // P1.5
#define MotorA_IN2_REN             P1REN |= BIT5       // P1.5��������
#define MotorA_IN2_OUT_Set         P1OUT |= BIT5       // P1.5����ߵ�ƽ
#define MotorA_IN2_OUT_ReSet       P1OUT &= ~BIT5       // P1.5����͵�ƽ



#define MotorB_IN1_DIR             P3DIR |= BIT0       // P3.0
#define MotorB_IN1_REN             P3REN |= BIT0       // P3.0��������
#define MotorB_IN1_OUT_Set         P3OUT |= BIT0       // P3.0����ߵ�ƽ
#define MotorB_IN1_OUT_ReSet       P3OUT &= ~BIT0      // P3.0����͵�ƽ

#define MotorB_IN2_DIR             P3DIR |= BIT1       // P3.1
#define MotorB_IN2_REN             P3REN |= BIT1       // P3.1��������
#define MotorB_IN2_OUT_Set         P3OUT |= BIT1       // P3.1����ߵ�ƽ
#define MotorB_IN2_OUT_ReSet       P3OUT &= ~BIT1      // P3.1����͵�ƽ



#define MotorC_IN1_DIR             P4DIR |= BIT0       // P4.0
#define MotorC_IN1_REN             P4REN |= BIT0       // P4.0��������
#define MotorC_IN1_OUT_Set         P4OUT |= BIT0       // P4.0����ߵ�ƽ
#define MotorC_IN1_OUT_ReSet       P4OUT &= ~BIT0      // P4.0����͵�ƽ

#define MotorC_IN2_DIR             P4DIR |= BIT1       // P4.1
#define MotorC_IN2_REN             P4REN |= BIT1       // P4.1��������
#define MotorC_IN2_OUT_Set         P4OUT |= BIT1       // P4.1����ߵ�ƽ
#define MotorC_IN2_OUT_ReSet       P4OUT &= ~BIT1      // P4.1����͵�ƽ



#define MotorD_IN1_DIR             P4DIR |= BIT2       // P4.2
#define MotorD_IN1_REN             P4REN |= BIT2       // P4.2��������
#define MotorD_IN1_OUT_Set         P4OUT |= BIT2       // P4.2������ߵ�ƽ
#define MotorD_IN1_OUT_ReSet       P4OUT &= ~BIT2      // P4.2������͵�ƽ

#define MotorD_IN2_DIR             P4DIR |= BIT3       // P4.3
#define MotorD_IN2_REN             P4REN |= BIT3       // P4.3��������
#define MotorD_IN2_OUT_Set         P4OUT |= BIT3       // P4.3����ߵ�ƽ
#define MotorD_IN2_OUT_ReSet       P4OUT &= ~BIT3      // P4.3����͵�ƽ


void Motor_Config (void);                              //��ʼ��
void Car_Forward (int speed);                          //С��ǰ��
void Car_Backward (int speed);                         //С������
void Car_Turn_Left (int speed);                        //����ת
void Car_Turn_Right (int speed);                       //����ת
void Car_Stop (void);                                  //С��ֹͣ


#endif /*BSP_MOTOR_H_*/




















