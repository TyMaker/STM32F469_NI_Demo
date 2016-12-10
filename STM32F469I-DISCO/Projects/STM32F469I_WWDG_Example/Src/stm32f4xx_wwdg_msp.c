/**
  ******************************************************************************
  * @file    stm32f4xx_wwdg_msp.c
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

#include "stm32f4xx_wwdg_msp.h"

WWDG_HandleTypeDef WWDG_Handler;     //���ڿ��Ź����

//����WWDG������������ֵ��Ĭ��Ϊ���
uint8_t WWDG_CNT=0X7F;


/**
  * @brief  This function Init WWDG
  * @param  None
  * @retval None
	* tr    :T[6:0]������ֵ
	* wr    :W[6:0]����ֵ
	* fprer :��Ƶϵ��(WDGTB)
	* fwwdg=PCLK1/(4096*2^fprer). һ��PCLK1=45Mhz
  */
void MX_WWDG_Init(uint8_t tr,uint8_t wr,uint32_t fprer)
{
    WWDG_Handler.Instance=WWDG;
    WWDG_Handler.Init.Prescaler=fprer;   //���÷�Ƶϵ��
    WWDG_Handler.Init.Window=wr;         //���ô���ֵ
    WWDG_Handler.Init.Counter=tr;        //���ü�����ֵ
    HAL_WWDG_Init(&WWDG_Handler);        //��ʼ��WWDG
    HAL_WWDG_Start_IT(&WWDG_Handler);    //�������ڿ��Ź�  
}


/**
  * @}
  */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{   
    __HAL_RCC_WWDG_CLK_ENABLE();    //ʹ�ܴ��ڿ��Ź�ʱ��
        
    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);    //��ռ���ȼ�2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(WWDG_IRQn);          //ʹ�ܴ��ڿ��Ź��ж�
}

/**
  * @}
  * �жϷ������������
  * �˺����ᱻHAL_WWDG_IRQHandler()����
  */
void HAL_WWDG_WakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
    HAL_WWDG_Refresh(&WWDG_Handler,WWDG_CNT);//���´��ڿ��Ź�ֵ
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
