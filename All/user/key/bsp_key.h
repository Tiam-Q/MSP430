#ifndef BSP_KEY_H_
#define BSP_KEY_H_


#include <msp430.h>


#define key1   (P1IN&BIT1)
#define key2   (P2IN&BIT1)


void Key_Init (void);
unsigned char Key_Scan (void);
void Key_Exti_Config (void);


#endif /*BSP_KEY_H_*/









