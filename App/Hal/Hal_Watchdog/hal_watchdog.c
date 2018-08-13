/**
************************************************************
* @file         hal_watchdog.c
* @brief        看门狗驱动
* @author       Gizwits
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include "hal_watchdog.h"

/**
* @brief Watchdog init

*Tout=((4×2^prer) ×rlr) /40 = ((4 * 2^4) * 625) / 40 = 1000ms = 1s

*prer Watchdog clock prescale value,range is 0~7

*rlr Watchdog reload value

* @param timeoutS : reset time,unit second
* @return none
*/
void watchdogInit(uint8_t timeoutS)
{
#ifdef  WATCHDOG
    uint8_t prer = 4;
    uint16_t rlr = timeoutS * 625;
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); /* Register IWDG_PR and IWDG_RLR enable write operation*/
    IWDG_SetPrescaler(prer);    /*Set IWDG prescale value*/
    IWDG_SetReload(rlr);     /*Set IWDG re-load value*/
    IWDG_ReloadCounter();    /*Reload the IWDG counter according to the IWDG reload register value*/
    IWDG_Enable();        /*IWDG enable*/
#endif
}

/**
* @brief Watchdog feed function

* @param  none
* @return none
*/
void watchdogFeed(void)
{
#ifdef  WATCHDOG
    IWDG->KR=0xaaaa;
#endif
}

