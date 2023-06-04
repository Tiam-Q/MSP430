#include "bsp_led.h"


void Led_Init (void)
{
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}


void Led1_On (void)
{
    P1OUT |= BIT0;
}

void Led1_Off (void)
{
    P1OUT &= ~BIT0;
}

void Led2_On (void)
{
    P4OUT |= BIT7;
}

void Led2_Off (void)
{
    P4OUT &= ~BIT7;
}

void Led1_Toggle (void)
{
    P1OUT ^= BIT0;
}

void Led2_Toggle (void)
{
    P4OUT ^= BIT7;
}











