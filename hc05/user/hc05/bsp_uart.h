#ifndef BSP_UART_H_
#define BAP_UART_H_


#include<msp430.h>
#include "type.h"
#include "bsp_delay.h"


void USART0_Config(void);              //P3.3(TX)  P3.4(RX)
void USART1_Config(void);              //P4.4(TX)  P4.5(RX)   Á¬½ÓUSB
void send0_buf(unsigned char *ptr);    //·¢ËÍ×Ö·û´®
void send1_buf(unsigned char *ptr);    //·¢ËÍ×Ö·û´®
void Print_Number0(u16 num);
void Print_Number1(u16 num);



#endif /*BAP_UART_H_*/


