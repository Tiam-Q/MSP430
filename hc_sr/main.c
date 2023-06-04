#include <msp430.h> 
#include "oled.h"
#include "hc_sr.h"

extern float cap_data ;                  // ����ֵ��u16

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
	    Hc_sr_Open();           //����һ������10us�ĸߵ�ƽ
	    OLED_ShowNum(0,10,cap_data,1,30);
	}

}

