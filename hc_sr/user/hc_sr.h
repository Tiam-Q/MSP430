#ifndef HC_SR_H_
#define HC_SR_H_


#include<msp430.h>
#include"type.h"


#define Trig1(a)  if(a==1) P1OUT |= BIT5; else P1OUT &= ~BIT5



void US_015_Init(void);
void Hc_sr_Open(void);           //����һ������10us�ĸߵ�ƽ










#endif





















