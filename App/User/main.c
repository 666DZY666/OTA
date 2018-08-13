/**
************************************************************
* @file         main.c
* @brief        MCU entry file
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <string.h>
#include "Hal_key/hal_key.h"
#include "Hal_Usart/hal_uart.h"
#include "Hal_Watchdog/hal_watchdog.h"
#include "gizwits_product.h"
#include "common.h"
#include "Hal_rgb_led.h"
#include "Hal_led.h"
#include "Hal_motor.h"
#include "timer.h"

uint8_t NetConfigureFlag = 0;

void KEY_Handle(void);

int main(void)
{
    SystemInit();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃNVICÖÐ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	  TIM3_PWM_Init();
		RGB_KEY_GPIO_Init();
		RGB_LED_Init();	
		LED_GPIO_Init();
		KEY_GPIO_Init();
    uartxInit();        //print serial port init
	  timerInit();
    uartInit();         //communication serial port init
    watchdogInit(2);    //watchdog reset time :2s

    userInit();
    gizwitsInit();

    GIZWITS_LOG("MCU Init Success \n");
	
		printf("MCU mmmmmmInit Success , SoftVersion = %s\r\n",SOFTWARE_VERSION);
	
		Pro_D2W_Ask_Module_Reboot();
	
    while(1)
    {
				watchdogFeed();
				KEY_Handle();	
       
        userHandle();//用户采集
        
        gizwitsHandle((dataPoint_t *)&currentDataPoint);//协议处理
    }
}

/*******************************************************************************
* Function Name  : KEY_Handle
* Description    : Key processing function
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void KEY_Handle(void)
{
	uint8_t Key_return =0;	
	Key_return = Get_Key();	
	if(Key_return & PRESS_KEY1)
	{
			printf("KEY1 PRESS,Wifi Reset\r\n");
		  LED_RGB_Control(254,0,0);
			gizwitsSetMode(WIFI_RESET_MODE);
	}
	if(Key_return & PRESS_KEY2)
	{
			//AirLink mode, RGB Green
			printf("KEY2 PRESS,AirLink mode\r\n");
			LED_RGB_Control(0,254,0);
			gizwitsSetMode(WIFI_AIRLINK_MODE);
			NetConfigureFlag = 1;
	}
}

