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


void Hc_sr_Open(void)           //生成一个持续10us的高电平
{
    Trig1(1);//这里就是把P1.2置1，即P1OUT |= BIT2
    __delay_cycles(250);//这里我把系统时钟升为25MHZ，因此250/25000000=10us
    Trig1(0);           //置0
}


unsigned int cap_new = 0;           // 首次捕捉的ta0r值
unsigned int cap_old = 0;           // 第二次捕捉的ta0r值

char cap_N = 0;                     // 溢出次数
char state = 0x00;                  // 状态
float cap_data ;                  // 距离值，u16

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{

    switch(__even_in_range(TA0IV,14))//采用这个range函数就是为了使switch函数效率高
    {
      case  0:break;                                 // No interrupt
      case  2:break;                           // CCR1 not used
      case  4: break;                          // CCR2 not used
      case  6:
          state =  TA0CCTL3 >> 14;
          TA0CCTL3 &= ~CCIFG;//标志位清零
          if( TA0CCTL3 & CM_1){//开始捕获高电平时间
              cap_new = TA0CCR3;
              TA0CCTL3 &= ~CM_1;
              TA0CCTL3 |=  CM_2;
          }else if ( TA0CCTL3 & CM_2)
          {
              cap_old = TA0CCR3;
              cap_data =(float)( ( cap_old - cap_new ) * 0.34/10/6.25);//这里外面解释！
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






