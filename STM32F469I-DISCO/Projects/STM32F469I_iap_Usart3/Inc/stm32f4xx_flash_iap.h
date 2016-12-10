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


typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.   
#define FLASH_APP1_ADDR		0x08010000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
											//����0X08000000~0X0800FFFF�Ŀռ�ΪBootloaderʹ��(��64KB)	   
void iap_write_appbin(uint32_t appxaddr,uint8_t *appbuf,uint32_t applen);	//��ָ����ַ��ʼ,д��bin
void iap_load_app(uint32_t appxaddr);			//��ת��APP����ִ��


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
