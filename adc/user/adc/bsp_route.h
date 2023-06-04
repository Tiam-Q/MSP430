#ifndef BSP_ROUTE_H_
#define BAP_ROUTE_H_

#include "bsp_uart.h"
#include "bsp_delay.h"
#include <msp430.h>


#define   Num_of_Results   8

volatile unsigned int A0results[Num_of_Results];
volatile unsigned int A1results[Num_of_Results];
volatile unsigned int A2results[Num_of_Results];
volatile unsigned int A3results[Num_of_Results];
volatile unsigned int A4results[Num_of_Results];

void Adc_Init (void);


#endif /*BAP_ROUTE_H_*/














