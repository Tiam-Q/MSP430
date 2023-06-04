#include <msp430.h> 
#include "oled.h"
#include "hc_sr.h"

extern float cap_data ;                  // 距离值，u16

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
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer


	SysTick_Init ();

	OLED_Init();
	OLED_Clear();

	US_015_Init();

	_EINT();
	while(1)
	{
	    Hc_sr_Open();           //生成一个持续10us的高电平
	    OLED_ShowNum(0,10,cap_data,1,30);
	}

}

