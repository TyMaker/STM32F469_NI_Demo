/**
  ******************************************************************************
  * @file    
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __STM32F4XX_WKUP_MSP
#define __STM32F4XX_WKUP_MSP

#include "stm32f4xx_hal.h"


#define WKUP_KD HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //PA0 ����Ƿ��ⲿWK_UP��������

void LED_Init(void);             //��ʼ������
uint8_t Check_WKUP(void);  			 //���WKUP�ŵ��ź�
void Stm32f4xx_WKUP_Init(void);  //PA0 WKUP���ѳ�ʼ��
void Sys_Enter_Standby(void);	   //ϵͳ�������ģʽ


#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
