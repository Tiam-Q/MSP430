#ifndef PID_H_
#define PID_H_


#include<msp430.h>
#include "type.h"


typedef struct Pid_Module
{
    //err值相关计算值
    float err;

    float differ;
    float integral;
    float integral_limit;
    //PID参数
    float kp;
    float ki;
    float kd;
    //输出相关
    float output;
    float output_limit; //输出限幅
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







