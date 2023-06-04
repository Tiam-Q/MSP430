#include "bsp_route.h"


/******************接线********************/
//
//               MSP430F5529
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//    Vin0 -->|P6.0/CB0/A0  P3.6|-->SDA
//    Vin1 -->|P6.1/CB1/A1  P3.5|-->SCL
//    Vin2 -->|P6.2/CB2/A2      |
//    Vin3 -->|P6.3/CB3/A3      |
//    Vin4 -->|P6.4             |
/**************************************/


void Adc_Init (void)
{
    P6SEL = 0x0F;                             // 使能 A/D
    ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8; // 打开ADC12，延长采样时间以避免结果溢出。
    ADC12CTL1 = ADC12SHP+ADC12CONSEQ_3;       // 使用采样定时器，多通道重复顺序转化。
    ADC12MCTL0 = ADC12INCH_0;                 // ref+=AVcc, channel = A0
    ADC12MCTL1 = ADC12INCH_1;                 // ref+=AVcc, channel = A1
    ADC12MCTL2 = ADC12INCH_2;                 // ref+=AVcc, channel = A2
    ADC12MCTL3 = ADC12INCH_3;                 // ref+=AVcc, channel = A3, end seq.
    ADC12MCTL4 = ADC12INCH_4+ADC12EOS;
    ADC12IE = 0x08;                           // Enable ADC12IFG.3
    ADC12CTL0 |= ADC12ENC;                    // 启用转换
    ADC12CTL0 |= ADC12SC;                     // 启用转换 -软件触发
}



#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR

__interrupt void ADC12ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12ISR (void)
#else
#error Compiler not supported!
#endif

{
  static unsigned int index = 0;

  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6: break;                           // Vector  6:  ADC12IFG0
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12:                                  // Vector 12:  ADC12IFG3
    A0results[index] = ADC12MEM0;           // Move A0 results, IFG is cleared
    A1results[index] = ADC12MEM1;           // Move A1 results, IFG is cleared
    A2results[index] = ADC12MEM2;           // Move A2 results, IFG is cleared
    A3results[index] = ADC12MEM3;           // Move A3 results, IFG is cleared
    A4results[index] = ADC12MEM4;
    Print_Number1(ADC12MEM4);
    delay(50);
    index++;                                // Increment results index, modulo; Set Breakpoint1 here
    if (index == 8)
    {
      (index = 0);
    }
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}












