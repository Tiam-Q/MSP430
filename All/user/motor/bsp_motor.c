#include "bsp_motor.h"
#include "filter.h"


/**************************************************************************************
 * @�����������
 * @����: ϵͳʱ������/(TACCR0+1)    25MHZ/(TACCR0+1)   SMCLK������Ƶ�ﵽ25MHZ
 * @ռ�ձȼ���: (TACCR0-TACCRX)/TACCR0
 * @���������ʮһ�߱����� 48���ٱȵ�� תһȦ����528������ ����ֱ����Լ6.7cm ת��һ�ܴ�Լ��ʻ21.048670779cm
 һ�������Լ��ʻ0.03986490678cm
 *                                ǰ
 * P1.2����     P2.0  P7.4  (A)-------------(B)  P2.4  P2.5    P1.3����
 *                          \_____________/
 *                          |             |
 *                          |_____________|
 *                          |____(��)_____|
 *                          /             \
 *                          ---------------
 *                                ��
 **************************************************************************************/



/****************************************************
 * @����ϵͳʱ�ӳ�ʼ�� ����Ϊ25Mhz
****************************************************/
void SysTick_Init (void)
{
    /*************************������ѹ***************************/
    PMMCTL0_H = 0xA5;                      //����PMM��Դ����������
    SVSMLCTL |= SVSMLRRL_1 + SVMLE;        //����SVML��ѹ
    PMMCTL0 = PMMPW +PMMCOREV_3;           //�����ں˵�ѹ��ѡ��3��
    while((PMMIFG & SVSMLDLYIFG)==0);      //�ȴ��������
    PMMIFG &=~ (SVMLVLRIFG + SVMLIFG + SVSMLDLYIFG);
    if((PMMIFG & SVMLIFG)==1)
        while((PMMIFG & SVMLVLRIFG)==0);
    SVSMLCTL &=~ SVMLE;                    //�ر�SVML
    PMMCTL0_H = 0x00;                     //�������ã�������
    /**************************ʱ������**************************/
    UCSCTL3 = SELREF_2;
    UCSCTL4 |= SELA_2;
    __bis_SR_register(SCG0);
    UCSCTL0 = 0x0000;
    UCSCTL1 = DCORSEL_7;//50Mhz��Χ
    UCSCTL2 = FLLD_0 + 762;    //(762+1)*32768==25MHZ
    __bic_SR_register(SCG0);

    __delay_cycles(782000);//��ʱ

    while(SFRIFG1 & OFIFG)//�ȴ��������
    {
        UCSCTL7 &=~ (XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &=~ OFIFG;

    }
}

void Motor_Time_Config (void)
{
    /*************************P2.5 TA2.2����**********************************/
     TA2CTL |= TASSEL1;     // TA2ʱ��ѡ��SMCLK   SMCLK��ʱ��Ϊ1MHZ   ʵ��Ϊ1.05MHZ
     TA2CTL |= MC0;          // TA2ѡ��ΪUPģʽ  ������0������TACCR0ʱ�ص�0�����ƾ�ݲ�

     TA2CCR0 = 2500-1;        // ����TACCR0��ֵ   ���Ϊ0xFFFH
     TA2CCR2 = 2500-1;        // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
     TA2CCTL0 &= ~CAP;
     TA2CCTL2 &= ~CAP;

    /*����TA2.2Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
     TA2CCTL2 |= OUTMOD_6;

    /*����P2.5 IO����*/
     P2SEL |= BIT5;
     P2DIR |= BIT5;


    /*************************P2.4 TA2.1����**********************************/
     TA2CCR1 = 2500-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
     TA2CCTL0 &= ~CAP;
     TA2CCTL1 &= ~CAP;

    /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
     TA2CCTL1 |= OUTMOD_6;

    /*����P2.4 IO����*/
     P2SEL |= BIT4;
     P2DIR |= BIT4;

    /*************************P2.0 TA1.1����**********************************/
     TA1CTL |= TASSEL1;     // TA1ʱ��ѡ��SMCLK   SMCLK��ʱ��Ϊ1MHZ   ʵ��Ϊ1.05MHZ
     TA1CTL |= MC0;          // TA1ѡ��ΪUPģʽ  ������0������TACCR0ʱ�ص�0�����ƾ�ݲ�

     TA1CCR0 = 2500-1;        // ����TACCR0��ֵ   ���Ϊ0xFFFH
     TA1CCR1 = 2500-1;        // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0

    /*����Ϊ�Ƚ�ģʽ*/
     TA1CCTL0 &= ~CAP;
     TA1CCTL1 &= ~CAP;

    /*����TA1.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
     TA1CCTL1 |= OUTMOD_6;

    /*����P2.1 IO����*/
     P2SEL |= BIT0;
     P2DIR |= BIT0;

    /*************************P7.4 TB0.2����**********************************/

     TB0CTL |= TBSSEL1;
     TB0CTL |= CNTL0;
     TB0CTL |= MC0;
     TB0CCR0 = 2500-1;
     TB0CCR2 = 2500-1;
     /*����Ϊ�Ƚ�ģʽ*/
     TB0CCTL0 &= ~CAP;
     TB0CCTL2 &= ~CAP;
     /*����TA2.2Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
     TB0CCTL2 |= OUTMOD_6;

     /*����P2.5 IO����*/
     P7SEL |= BIT4;
     P7DIR |= BIT4;


//     /******************P1.2 TA0.1   P1.3 TA0.2���벶������*********************/
//     TA0CCR0 = 2500-1;
//     TA0CTL = TASSEL1+TACLR+TAIE+MC1;  //ʱ���ź�ѡ��SMCLK,����ģʽΪ��������ģʽ
//     TA0CCTL1 = CM0+SCS+CAP+CCIE;      //�����½��ز���,CCI1AΪ�����ź�Դ
//     P1SEL |= BIT2;                    //����P1.2�˿�Ϊ����ģ��CCI1A���벶��
//     TA0CCTL2 = CM0+SCS+CAP+CCIE;      //�����½��ز���,CCI1AΪ�����ź�Դ
//     P1SEL |= BIT3;                    //����P1.3�˿�Ϊ����ģ��CCI1A���벶��

//     /*************************P1.5 TA0.4����**********************************/
//     TA0CCR4 = 2500-1;       // ����TACCRX��ֵ   TACCRX��ֵ��TACCR0��ֵ��ȣ���ʼռ�ձ�Ϊ0
//
//     /*����Ϊ�Ƚ�ģʽ*/
//     TA0CCTL4 &= ~CAP;
//     TA0CCTL4 &= ~CAP;
//
//     /*����TA2.1Ϊ���ģʽ6 Toggle/Setģʽ ����ʱ��������TACCRXֵʱ�������ת��������TACCR0ʱ������λ*/
//     TA0CCTL4 |= OUTMOD_6;
//
//     /*����P2.4 IO����*/
//     P1SEL |= BIT5;
//     P1DIR |= BIT5;
     //__bis_SR_register(GIE);
}


void Motor_Init (void)
{
    Motor_Time_Config ();
    Car_Stop ();
}


//u16 capvalueA_1 = 0;
//u16 capvalueA_2 = 0;
//u32 timestamp = 0;
//u32 timestampA_1 = 0;
//u32 timestampA_2 = 0;
//u32 totaltimeA = 0;
//
//u16 capvalueB_1 = 0;
//u16 capvalueB_2 = 0;
//u32 timestampB_1 = 0;
//u32 timestampB_2 = 0;
//u32 totaltimeB = 0;

//#pragma vector=TIMER0_A1_VECTOR  //Timer_A�����ж�����
//__interrupt void Timer_A(void)
//{
//   // __bis_SR_register(GIE);//�����ж�Ƕ��
//
//  switch(TA0IV)
//  {
//  static uint8_t cntA = 0;
//  static float v_arrA[9] = {0};
//  static unsigned int indexA = 0;
//  static uint8_t cntB = 0;
//  static float v_arrB[9] = {0};
//  static unsigned int indexB = 0;
//  case 0x02:
//      TA0CCTL1 &= ~CCIFG;
//
//      if(cntA==0)
//      {
//          capvalueA_1 = TA0CCR1;   //    �����һ�β�׽ֵ
//          timestampA_1 = timestamp;
//          cntA++;
//      }
//      else
//      {
//          capvalueA_2 = TA0CCR1;   //    ����ڶ��β�׽ֵ
//          timestampA_2 = timestamp;
//          cntA=0;
//          totaltimeA = (timestampA_2-timestampA_1)*2500+capvalueA_2-capvalueA_1;
//          v_arrA[indexA] = (float)(398649.0678/totaltimeA);
//          indexA++;                                // Increment results index, modulo; Set Breakpoint1 here
//          if (indexA == 9)
//          {
//             indexA = 0;
//          }
//          V_1 = Median_Filter(v_arrA,9);
//      }
//      break;
//  case 0x04 :
//      TA0CCTL2 &= ~CCIFG;
//
//      if(cntB==0)
//      {
//          capvalueB_1 = TA0CCR2;   //    �����һ�β�׽ֵ
//          timestampB_1 = timestamp;
//          cntB++;
//      }
//      else
//      {
//          capvalueB_2 = TA0CCR2;   //    ����ڶ��β�׽ֵ
//          timestampB_2 = timestamp;
//          cntB=0;
//          totaltimeB = (timestampB_2-timestampB_1)*2500+capvalueB_2-capvalueB_1;
//          v_arrB[indexB] = (float)(398649.0678/totaltimeB);
//          indexB++;                                // Increment results index, modulo; Set Breakpoint1 here
//          if (indexB == 9)
//          {
//              indexB = 0;
//          }
//          V_2 = Median_Filter(v_arrB,9);
//      }
//      break;
//  case 0x0E :
//      TA0CTL &= ~TAIFG;
//      timestamp++;
//      break;
//  default:
//      break;
//  }
//}



static void MotorA_Forward (float speed)   // ���A��ת
{
    MotorA1_Pwm_Out = speed;
    MotorA2_Pwm_Out = 0;

}

static void MotorA_Backward (float speed)  //���A��ת
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = speed;
}

static void MotorB_Forward (float speed)   //���B��ת
{
    MotorB1_Pwm_Out = speed;
    MotorB2_Pwm_Out = 0;
}

static void MotorB_Backward (float speed)  //���B��ת
{
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = speed;
}



void Car_Right_CirCle (float speed)  //˳ʱ����ת
{
    MotorA_Forward (speed);
    MotorB_Backward (speed);
}
void Car_Left_CirCle (float speed)  //��ʱ����ת
{
    MotorA_Backward (speed);
    MotorB_Forward (speed);
}
void Car_Forward (float speed) //С��ǰ��
{
    MotorA_Forward (speed);
    MotorB_Forward (speed);
}


void Car_Backward (float speed) //С������
{
    MotorA_Backward (speed);
    MotorB_Backward (speed);
}


void Car_Turn_Left (float speed,float Turn_Speed) //�ұߵ�B�������ߵ�A���ת�ٿ�ʵ����ת
{
    MotorA_Forward (speed-Turn_Speed);
    MotorB_Forward (speed+Turn_Speed);

}


void Car_Turn_Right (float speed,float Turn_Speed) //�ұߵ�B�������ߵ�A���ת����ʵ����ת
{
    MotorA_Forward (speed+Turn_Speed);
    MotorB_Forward (speed-Turn_Speed);
}


void Car_Stop (void)            //С��ֹͣ
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = 0;
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = 0;
}






