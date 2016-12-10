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
	
#include "stm32f4xx_hal_Inside_msp.h"

ADC_HandleTypeDef ADC1_Handler;//ADC���


void MY_ADC_Init(void)
{   
    ADC1_Handler.Instance=ADC1;
    ADC1_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;  //4��Ƶ��ADCCLK=PCLK2/4=90/4=22.5MHZ
    ADC1_Handler.Init.Resolution=ADC_RESOLUTION_12B;            //12λģʽ
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;            //�Ҷ���
    ADC1_Handler.Init.ScanConvMode=DISABLE;                     //��ɨ��ģʽ
    ADC1_Handler.Init.EOCSelection=DISABLE;                     //�ر�EOC�ж�
    ADC1_Handler.Init.ContinuousConvMode=DISABLE;               //�ر�����ת��
    ADC1_Handler.Init.NbrOfConversion=1;                        //1��ת���ڹ��������� Ҳ����ֻת����������1 
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;            //��ֹ����������ģʽ
    ADC1_Handler.Init.NbrOfDiscConversion=0;                    //����������ͨ����Ϊ0
    ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;      //�������
    ADC1_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//ʹ���������
    ADC1_Handler.Init.DMAContinuousRequests=DISABLE;            //�ر�DMA����
    HAL_ADC_Init(&ADC1_Handler);                                //��ʼ��     
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC1_CLK_ENABLE();            //ʹ��ADC1ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_5;            //PA5
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}

uint16_t Get_Adc(uint32_t ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;
    
    ADC1_ChanConf.Channel=ch;                                   //ͨ��
    ADC1_ChanConf.Rank=1;                                       //1������
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //����ʱ��
    ADC1_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC1_ChanConf);        //ͨ������
	
    HAL_ADC_Start(&ADC1_Handler);                               //����ADC
	
    HAL_ADC_PollForConversion(&ADC1_Handler,10);                //��ѯת��
   
	return (uint16_t)HAL_ADC_GetValue(&ADC1_Handler);	            //�������һ��ADC1�������ת�����
}

uint16_t Get_Adc_Average(uint32_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		HAL_Delay(5);
	}
	return temp_val/times;
} 

short Get_Temprate(void)
{
	uint32_t adcx;
	short result;
 	double temperate;
	adcx=Get_Adc_Average(ADC_CHANNEL_TEMPSENSOR,10);//��ȡ�ڲ��¶ȴ�����ͨ��,10��ȡƽ��
	temperate=(float)adcx*(3.3/4096);		//��ѹֵ
	temperate=(temperate-0.76)/0.0025 + 25; //ת��Ϊ�¶�ֵ 
	result=temperate*=100;					//����100��.
	return result;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
