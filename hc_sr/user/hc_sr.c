#include "hc_sr.h"


/****************************************************
 * P1.4:echo
 * P1.5:Trig
****************************************************/
void US_015_Init(void)
{

    P1OUT &= ~( BIT4 + BIT5 );
    P1DIR |=  BIT5;
    P1SEL |=  BIT4;

    TA0CTL   = TASSEL__SMCLK + ID__8 + MC_2 + TACLR + TAIE;
    TA0CCTL3 = CM_1 + SCS +CAP + CCIE + CCIS_0;
}


void Hc_sr_Open(void)           //����һ������10us�ĸߵ�ƽ
{
    Trig1(1);//������ǰ�P1.2��1����P1OUT |= BIT2
    __delay_cycles(250);//�����Ұ�ϵͳʱ����Ϊ25MHZ�����250/25000000=10us
    Trig1(0);           //��0
}


unsigned int cap_new = 0;           // �״β�׽��ta0rֵ
unsigned int cap_old = 0;           // �ڶ��β�׽��ta0rֵ

char cap_N = 0;                     // �������
char state = 0x00;                  // ״̬
float cap_data ;                  // ����ֵ��u16

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{

    switch(__even_in_range(TA0IV,14))//�������range��������Ϊ��ʹswitch����Ч�ʸ�
    {
      case  0:break;                                 // No interrupt
      case  2:break;                           // CCR1 not used
      case  4: break;                          // CCR2 not used
      case  6:
          state =  TA0CCTL3 >> 14;
          TA0CCTL3 &= ~CCIFG;//��־λ����
          if( TA0CCTL3 & CM_1){//��ʼ����ߵ�ƽʱ��
              cap_new = TA0CCR3;
              TA0CCTL3 &= ~CM_1;
              TA0CCTL3 |=  CM_2;
          }else if ( TA0CCTL3 & CM_2)
          {
              cap_old = TA0CCR3;
              cap_data =(float)( ( cap_old - cap_new ) * 0.34/10/6.25);//����������ͣ�
              TA0CCTL3 &= ~CM_2;
              TA0CCTL3 |=  CM_1;
          }else
          break;                          // reserved
      case  8: break;                          // reserved
      case 10: break;                          // reserved
      case 12: break;                          // reserved
      case 14:
          TA0CTL &= ~TAIFG;
          if(cap_old   < cap_new ){
              cap_N += 1;
          }
          break;                          // overflow
      default: break;
    }
}






