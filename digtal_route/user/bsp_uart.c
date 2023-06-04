#include "bsp_uart.h"
#include <stdio.h>
#include <string.h>


float       Roll;
float       Pitch;
float       Yaw;
float       Version;


void USART0_Config(void)
{
    //串口初始化
     P3SEL    |=  BIT3+BIT4 ;                  // P5.6,7 = USCI_A1 TXD/RXD
     UCA0CTL1 |=  UCSWRST;                     // **Put state machine in reset**
     UCA0CTL1 |=  UCSSEL_1;                    // ACLK
     UCA0BR0   =  0x03;                        // 32768Hz 9600 波特率为9600
     UCA0BR1   =  0x00;                        // 32768Hz 9600
     UCA0MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
     UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
     UCA0IE   |=  UCRXIE;                      // Enable USCI_A1 RX interrupt 使能中断
     UCA0IFG &= ~UCRXIFG;                       // 清除接收中断标志
}


void USART1_Config(void)
{
    //串口初始化
     P4SEL    |=  BIT4+BIT5 ;                   // P5.6,7 = USCI_A1 TXD/RXD
     UCA1CTL1 |=  UCSWRST;                      // **Put state machine in reset**
     UCA1CTL1 |=  UCSSEL_1;                     // ACLK
     UCA1BR0   =  0x03;                         // 32768Hz 9600 波特率为9600
     UCA1BR1   =  0x00;                         // 32768Hz 9600
     UCA1MCTL |=  UCBRS_3 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
     UCA1CTL1 &= ~UCSWRST;                      // 清除复位位 使能UART
     UCA1IE   |=  UCRXIE;                       // 使能中断
     UCA1IFG &= ~UCRXIFG;                       // 清除接收中断标志
}

void send0_buf(unsigned char *ptr)    //发送字符串
{
    while(*ptr != '\0')
    {
        while(!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *ptr;
        ptr++;
    }
}
void send1_buf(unsigned char *ptr)    //发送字符串
{
    while(*ptr != '\0')
    {
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = *ptr;
        ptr++;
    }
}

/*
 * @fn:     void PrintNumber(uint16_t num)
 * @brief:  通过串口发送数字
 * @para:   num:变量
 * @return: none
 * @comment:通过串口发送数字
 */
void Print_Number0(u16 num)
{
    u8 buff[6] = {0,0,0,0,0,'\n'};
    u8 cnt = 0;
    for(cnt = 0;cnt < 5;cnt ++)
    {
        buff[4 - cnt] = (u8)(num % 10 + '0');
        num /= 10;
    }
    send0_buf(buff);
}

void Print_Number1(u16 num)
{
    u8 buff[6] = {0,0,0,0,0,'\n'};
    u8 cnt = 0;
    for(cnt = 0;cnt < 5;cnt ++)
    {
        buff[4 - cnt] = (u8)(num % 10 + '0');
        num /= 10;
    }
    send1_buf(buff);
}
int fputc(int ch,FILE *f)
{
    UCA1TXBUF = ch&0xff;
    while(!(UCA1IFG & UCTXIFG));//等待发送完成
     return ch;
}
int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++){
    UCA1TXBUF = _ptr[i]&0xff;
    while(!(UCA1IFG & UCTXIFG));//等待发送完成

  }

  return len;
}


#pragma vector = USCI_A1_VECTOR      //中断服务函数
__interrupt void usci_a1_receive (void)
{
    if (UCA1IFG & UCRXIFG)          // 中断来临
    {
        UCA1TXBUF = UCA1RXBUF;      // 发送接收数据
    }
    UCA1TXBUF &= ~UCRXIFG;
}





#pragma vector = USCI_A0_VECTOR      //中断服务函数
__interrupt void usci_a0_receive (void)
{
    if (UCA0IFG & UCRXIFG)          // 中断来临
        {
            UCA0TXBUF = UCA0RXBUF;      // 发送接收数据
        }
        UCA0TXBUF &= ~UCRXIFG;
}










