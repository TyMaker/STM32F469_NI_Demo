/**
  ******************************************************************************
  * @file    IAP/IAP_USART/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    12-07-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */


#include "stm32f4xx_hal.h"


typedef  void (*iapfun)(void);				//定义一个函数类型的参数.   
#define FLASH_APP1_ADDR		0x08010000  	//第一个应用程序起始地址(存放在FLASH)
											//保留0X08000000~0X0800FFFF的空间为Bootloader使用(共64KB)	   
void iap_write_appbin(uint32_t appxaddr,uint8_t *appbuf,uint32_t applen);	//在指定地址开始,写入bin
void iap_load_app(uint32_t appxaddr);			//跳转到APP程序执行


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
