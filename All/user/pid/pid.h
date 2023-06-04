#ifndef PID_H_
#define PID_H_


#include<msp430.h>
#include "type.h"


typedef struct Pid_Module
{
    //errֵ��ؼ���ֵ
    float err;

    float differ;
    float integral;
    float integral_limit;
    //PID����
    float kp;
    float ki;
    float kd;
    //������
    float output;
    float output_limit; //����޷�
    float p_output;
    float i_output;
    float d_output;
}Pid_Module;


float Pos_PID_CAL_OUT(Pid_Module *PID, float err);
void PID_Init(Pid_Module *PID);
void PID_Set_Kpid(Pid_Module *PID, float kp, float ki, float kd);
void PID_Set_limit(Pid_Module *PID, float integral_limit,  float output_limit);
void PID_Clear(Pid_Module *PID);



#endif /*PID_H_*/







