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

#include "stm32f469i_rng.h"


RNG_HandleTypeDef RNG_Handler;  //RNG���

//��ʼ��RNG
uint8_t RNG_Init(void)
{
    uint16_t retry=0;
    
    RNG_Handler.Instance=RNG;
    HAL_RNG_Init(&RNG_Handler);//��ʼ��RNG
    while(__HAL_RNG_GET_FLAG(&RNG_Handler,RNG_FLAG_DRDY)==RESET&&retry<10000)//�ȴ�RNG׼������
    {
        retry++;
        HAL_Delay(10);
    }
    if(retry>=10000) return 1;//���������������������
    return 0;
}
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
     __HAL_RCC_RNG_CLK_ENABLE();//ʹ��RNGʱ��
}

//�õ������
//����ֵ:��ȡ���������
uint32_t RNG_Get_RandomNum(void)
{
    return HAL_RNG_GetRandomNumber(&RNG_Handler);
}

//����[min,max]��Χ�������
int RNG_Get_RandomRange(int min,int max)
{ 
   return HAL_RNG_GetRandomNumber(&RNG_Handler)%(max-min+1) +min;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
