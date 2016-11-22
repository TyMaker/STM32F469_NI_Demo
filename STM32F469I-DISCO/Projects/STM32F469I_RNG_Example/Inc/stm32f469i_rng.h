/**
  ******************************************************************************
  * @file    
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-11-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __STM32F469I_RNG
#define __STM32F469I_RNG

#include "stm32f4xx_hal.h"


uint8_t  RNG_Init(void);			//RNG��ʼ�� 
uint32_t RNG_Get_RandomNum(void);//�õ������
int RNG_Get_RandomRange(int min,int max);//����[min,max]��Χ�������




#endif /* stm32f469i_rng */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
