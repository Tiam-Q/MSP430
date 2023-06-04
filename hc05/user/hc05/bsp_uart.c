#include "bsp_uart.h"
#include "bsp_led.h"

void USART0_Config(void)
{
    //���ڳ�ʼ��
     P3SEL    |=  BIT3+BIT4 ;                  // P5.6,7 = USCI_A1 TXD/RXD
     UCA0CTL1 |=  UCSWRST;                     // **Put state machine in reset**
     UCA0CTL1 |=  UCSSEL_1;                    // ACLK
     UCA0BR0   =  0x03;                        // 32768Hz 9600 ������Ϊ9600
     UCA0BR1   =  0x00;                        // 32768Hz 9600
     UCA0MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
     UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
     UCA0IE   |=  UCRXIE;                      // Enable USCI_A1 RX interrupt ʹ���ж�
     UCA0IFG &= ~UCRXIFG;                       // ��������жϱ�־
}


void USART1_Config(void)
{
    //���ڳ�ʼ��
     P4SEL    |=  BIT4+BIT5 ;                   // P5.6,7 = USCI_A1 TXD/RXD
     UCA1CTL1 |=  UCSWRST;                      // **Put state machine in reset**
     UCA1CTL1 |=  UCSSEL_1;                     // ACLK
     UCA1BR0   =  0x03;                         // 32768Hz 9600 ������Ϊ9600
     UCA1BR1   =  0x00;                         // 32768Hz 9600
     UCA1MCTL |=  UCBRS_3 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
     UCA1CTL1 &= ~UCSWRST;                      // �����λλ ʹ��UART
     UCA1IE   |=  UCRXIE;                       // ʹ���ж�
     UCA1IFG &= ~UCRXIFG;                       // ��������жϱ�־
}

void send0_buf(unsigned char *ptr)    //�����ַ���
{
    while(*ptr != '\0')
    {
        while(!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *ptr;
        ptr++;
        delay(10);
    }
}
void send1_buf(unsigned char *ptr)    //�����ַ���
{
    while(*ptr != '\0')
    {
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = *ptr;
        ptr++;
        delay(10);
    }
}

/*
 * @fn:     void PrintNumber(uint16_t num)
 * @brief:  ͨ�����ڷ�������
 * @para:   num:����
 * @return: none
 * @comment:ͨ�����ڷ�������
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



#pragma vector = USCI_A1_VECTOR      //�жϷ�����
__interrupt void usci_a1_receive (void)
{
    if (UCA1IFG & UCRXIFG)          // �ж�����
    {
        Led2_On ();
        if(UCA1TXBUF == "48")
        {
            Led1_On ();
        }
    }
    UCA1TXBUF &= ~UCRXIFG;
}





#pragma vector = USCI_A0_VECTOR      //�жϷ�����
__interrupt void usci_a0_receive (void)
{
    if( UCA0IFG & UCRXIFG)        //�����ж�
      {
        UCA0TXBUF &= ~UCRXIFG;    //����ж�

        UCA1TXBUF = UCA0RXBUF;
        }
}



