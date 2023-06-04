#ifndef BSP_HC05_H_
#define BSP_HC05_H_


#include<msp430.h>
#include "type.h"
#include "bsp_delay.h"


#define      Usart_SendString      send0_buf
#define      hc05_delay_ms         delay
#define      HC05_USART_Config     USART0_Config

#define      STATE                 P1IN&BIT6
//��������豸����
#define      BLTDEV_MAX_NUM        10
/* �����������ݻ�����󳤶� */
#define      UART_BUFF_SIZE        1024



/*������ַ��������ʽ����NAP��UAP��LAP��*/
typedef  struct
{
    uint8_t num;        //ɨ�赽�������豸����

    char unpraseAddr[BLTDEV_MAX_NUM][50];   //�����豸��ַ���ַ�����ʽ������ɨ��ʱ������ʱʹ��

    char name[BLTDEV_MAX_NUM][50];  //�����豸������

}BLTDev;



uint8_t HC05_Init(void);
uint8_t HC05_Send_CMD(char* cmd,uint8_t clean);
void HC05_SendString(char* str);
uint8_t parseBltAddr(void);
uint8_t getRemoteDeviceName(void);
uint8_t linkHC05(void);



#endif /*BSP_HC05_H_*/










