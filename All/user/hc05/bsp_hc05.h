#ifndef BSP_HC05_H_
#define BSP_HC05_H_


#include<msp430.h>
#include "type.h"
#include "bsp_delay.h"


#define      Usart_SendString      send0_buf
#define      hc05_delay_ms         delay
#define      HC05_USART_Config     USART0_Config

#define      STATE                 P1IN&BIT6
//最大蓝牙设备数量
#define      BLTDEV_MAX_NUM        10
/* 蓝牙串口数据缓存最大长度 */
#define      UART_BUFF_SIZE        1024



/*蓝牙地址，数字形式，分NAP，UAP，LAP段*/
typedef  struct
{
    uint8_t num;        //扫描到的蓝牙设备数量

    char unpraseAddr[BLTDEV_MAX_NUM][50];   //蓝牙设备地址，字符串形式，方便扫描时和连接时使用

    char name[BLTDEV_MAX_NUM][50];  //蓝牙设备的名字

}BLTDev;



uint8_t HC05_Init(void);
uint8_t HC05_Send_CMD(char* cmd,uint8_t clean);
void HC05_SendString(char* str);
uint8_t parseBltAddr(void);
uint8_t getRemoteDeviceName(void);
uint8_t linkHC05(void);



#endif /*BSP_HC05_H_*/










