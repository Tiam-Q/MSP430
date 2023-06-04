#include "bsp_motor.h"
#include "filter.h"


/**************************************************************************************
 * @电机驱动函数
 * @周期: 系统时钟周期/(TACCR0+1)    25MHZ/(TACCR0+1)   SMCLK经过升频达到25MHZ
 * @占空比计算: (TACCR0-TACCRX)/TACCR0
 * @电机参数：十一线编码器 48减速比电机 转一圈产生528个脉冲 轮子直径大约6.7cm 转动一周大约行驶21.048670779cm
 一个脉冲大约行驶0.03986490678cm
 *                                前
 * P1.2捕获     P2.0  P7.4  (A)-------------(B)  P2.4  P2.5    P1.3捕获
 *                          \_____________/
 *                          |             |
 *                          |_____________|
 *                          |____(。)_____|
 *                          /             \
 *                          ---------------
 *                                后
 **************************************************************************************/



/****************************************************
 * @函数系统时钟初始化 配置为25Mhz
****************************************************/
void SysTick_Init (void)
{
    /*************************核心升压***************************/
    PMMCTL0_H = 0xA5;                      //开启PMM电源管理，即开锁
    SVSMLCTL |= SVSMLRRL_1 + SVMLE;        //配置SVML电压
    PMMCTL0 = PMMPW +PMMCOREV_3;           //配置内核电压，选择3级
    while((PMMIFG & SVSMLDLYIFG)==0);      //等待配置完成
    PMMIFG &=~ (SVMLVLRIFG + SVMLIFG + SVSMLDLYIFG);
    if((PMMIFG & SVMLIFG)==1)
        while((PMMIFG & SVMLVLRIFG)==0);
    SVSMLCTL &=~ SVMLE;                    //关闭SVML
    PMMCTL0_H = 0x00;                     //锁存配置，即关锁
    /**************************时钟配置**************************/
    UCSCTL3 = SELREF_2;
    UCSCTL4 |= SELA_2;
    __bis_SR_register(SCG0);
    UCSCTL0 = 0x0000;
    UCSCTL1 = DCORSEL_7;//50Mhz范围
    UCSCTL2 = FLLD_0 + 762;    //(762+1)*32768==25MHZ
    __bic_SR_register(SCG0);

    __delay_cycles(782000);//延时

    while(SFRIFG1 & OFIFG)//等待设置完成
    {
        UCSCTL7 &=~ (XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &=~ OFIFG;

    }
}

void Motor_Time_Config (void)
{
    /*************************P2.5 TA2.2配置**********************************/
     TA2CTL |= TASSEL1;     // TA2时钟选择SMCLK   SMCLK的时钟为1MHZ   实际为1.05MHZ
     TA2CTL |= MC0;          // TA2选择为UP模式  即当从0计数到TACCR0时回到0，类似锯齿波

     TA2CCR0 = 2500-1;        // 设置TACCR0的值   最大为0xFFFH
     TA2CCR2 = 2500-1;        // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
     TA2CCTL0 &= ~CAP;
     TA2CCTL2 &= ~CAP;

    /*设置TA2.2为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
     TA2CCTL2 |= OUTMOD_6;

    /*设置P2.5 IO复用*/
     P2SEL |= BIT5;
     P2DIR |= BIT5;


    /*************************P2.4 TA2.1配置**********************************/
     TA2CCR1 = 2500-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
     TA2CCTL0 &= ~CAP;
     TA2CCTL1 &= ~CAP;

    /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
     TA2CCTL1 |= OUTMOD_6;

    /*设置P2.4 IO复用*/
     P2SEL |= BIT4;
     P2DIR |= BIT4;

    /*************************P2.0 TA1.1配置**********************************/
     TA1CTL |= TASSEL1;     // TA1时钟选择SMCLK   SMCLK的时钟为1MHZ   实际为1.05MHZ
     TA1CTL |= MC0;          // TA1选择为UP模式  即当从0计数到TACCR0时回到0，类似锯齿波

     TA1CCR0 = 2500-1;        // 设置TACCR0的值   最大为0xFFFH
     TA1CCR1 = 2500-1;        // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0

    /*设置为比较模式*/
     TA1CCTL0 &= ~CAP;
     TA1CCTL1 &= ~CAP;

    /*设置TA1.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
     TA1CCTL1 |= OUTMOD_6;

    /*设置P2.1 IO复用*/
     P2SEL |= BIT0;
     P2DIR |= BIT0;

    /*************************P7.4 TB0.2配置**********************************/

     TB0CTL |= TBSSEL1;
     TB0CTL |= CNTL0;
     TB0CTL |= MC0;
     TB0CCR0 = 2500-1;
     TB0CCR2 = 2500-1;
     /*设置为比较模式*/
     TB0CCTL0 &= ~CAP;
     TB0CCTL2 &= ~CAP;
     /*设置TA2.2为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
     TB0CCTL2 |= OUTMOD_6;

     /*设置P2.5 IO复用*/
     P7SEL |= BIT4;
     P7DIR |= BIT4;


//     /******************P1.2 TA0.1   P1.3 TA0.2输入捕获配置*********************/
//     TA0CCR0 = 2500-1;
//     TA0CTL = TASSEL1+TACLR+TAIE+MC1;  //时钟信号选择SMCLK,计数模式为连续增计模式
//     TA0CCTL1 = CM0+SCS+CAP+CCIE;      //输入下降沿捕获,CCI1A为捕获信号源
//     P1SEL |= BIT2;                    //设置P1.2端口为功能模块CCI1A输入捕获
//     TA0CCTL2 = CM0+SCS+CAP+CCIE;      //输入下降沿捕获,CCI1A为捕获信号源
//     P1SEL |= BIT3;                    //设置P1.3端口为功能模块CCI1A输入捕获

//     /*************************P1.5 TA0.4配置**********************************/
//     TA0CCR4 = 2500-1;       // 设置TACCRX的值   TACCRX的值与TACCR0的值相等，初始占空比为0
//
//     /*设置为比较模式*/
//     TA0CCTL4 &= ~CAP;
//     TA0CCTL4 &= ~CAP;
//
//     /*设置TA2.1为输出模式6 Toggle/Set模式 即定时器计数到TACCRX值时，输出反转；计数到TACCR0时，被置位*/
//     TA0CCTL4 |= OUTMOD_6;
//
//     /*设置P2.4 IO复用*/
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

//#pragma vector=TIMER0_A1_VECTOR  //Timer_A捕获中断向量
//__interrupt void Timer_A(void)
//{
//   // __bis_SR_register(GIE);//允许中断嵌套
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
//          capvalueA_1 = TA0CCR1;   //    保存第一次捕捉值
//          timestampA_1 = timestamp;
//          cntA++;
//      }
//      else
//      {
//          capvalueA_2 = TA0CCR1;   //    保存第二次捕捉值
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
//          capvalueB_1 = TA0CCR2;   //    保存第一次捕捉值
//          timestampB_1 = timestamp;
//          cntB++;
//      }
//      else
//      {
//          capvalueB_2 = TA0CCR2;   //    保存第二次捕捉值
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



static void MotorA_Forward (float speed)   // 电机A正转
{
    MotorA1_Pwm_Out = speed;
    MotorA2_Pwm_Out = 0;

}

static void MotorA_Backward (float speed)  //电机A反转
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = speed;
}

static void MotorB_Forward (float speed)   //电机B正转
{
    MotorB1_Pwm_Out = speed;
    MotorB2_Pwm_Out = 0;
}

static void MotorB_Backward (float speed)  //电机B反转
{
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = speed;
}



void Car_Right_CirCle (float speed)  //顺时针旋转
{
    MotorA_Forward (speed);
    MotorB_Backward (speed);
}
void Car_Left_CirCle (float speed)  //逆时针旋转
{
    MotorA_Backward (speed);
    MotorB_Forward (speed);
}
void Car_Forward (float speed) //小车前进
{
    MotorA_Forward (speed);
    MotorB_Forward (speed);
}


void Car_Backward (float speed) //小车后退
{
    MotorA_Backward (speed);
    MotorB_Backward (speed);
}


void Car_Turn_Left (float speed,float Turn_Speed) //右边的B电机比左边的A电机转速快实现左转
{
    MotorA_Forward (speed-Turn_Speed);
    MotorB_Forward (speed+Turn_Speed);

}


void Car_Turn_Right (float speed,float Turn_Speed) //右边的B电机比左边的A电机转速慢实现左转
{
    MotorA_Forward (speed+Turn_Speed);
    MotorB_Forward (speed-Turn_Speed);
}


void Car_Stop (void)            //小车停止
{
    MotorA1_Pwm_Out = 0;
    MotorA2_Pwm_Out = 0;
    MotorB1_Pwm_Out = 0;
    MotorB2_Pwm_Out = 0;
}






