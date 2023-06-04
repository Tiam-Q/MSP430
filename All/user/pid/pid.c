#include "pid.h"

/***********************************
 * @abstract: PID���㺯��
 * @Input:���ֵ
 * @Return:PID���ֵ
 **********************************/
float Pos_PID_CAL_OUT(Pid_Module *PID, float err)
{
    PID->integral += err;
    PID->differ = err-(PID->err);
    PID->err = err;

    if((PID->integral)>(PID->integral_limit)) //�����޷�
        PID->integral = PID->integral_limit;
    else if(PID->integral<-(PID->integral_limit))
        PID->integral = -(PID->integral_limit);

    PID->p_output = (PID->kp)*(PID->err);
    PID->i_output = (PID->ki)*(PID->integral);
    PID->d_output = (PID->kd)*(PID->differ);

    PID->output = PID->p_output + PID->i_output + PID->d_output;//PID�����Ҫ�޷�

    if((PID->output)>PID->output_limit)
            PID->output = PID->output_limit;
    else if(PID->output < 0)
            PID->output = 0;

    return PID->output;
}

//PID��ʼ��
void PID_Init(Pid_Module *PID)
{
    PID->err = 0;

    PID->integral = 0;
    PID->integral_limit = 0;
    PID->differ = 0;

    PID->kp = 0;
    PID->ki = 0;
    PID->kd = 0;
    PID->output = 0;
    PID->output_limit = 0;
}


void PID_Set_Kpid(Pid_Module *PID, float kp, float ki, float kd)
{
    PID->kp = kp;
    PID->ki = ki;
    PID->kd = kd;
}

void PID_Set_limit(Pid_Module *PID, float integral_limit,  float output_limit)
{
    PID->integral_limit = integral_limit;
    PID->output_limit = output_limit;

}


//���PID����
void PID_Clear(Pid_Module *PID)
{
    PID->differ = 0;
    PID->integral = 0;
    PID->err = 0;
    PID->output = 0;
}











