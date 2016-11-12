/**
  ******************************************************************************
  * @file    stm32f4xx_Usart.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    12-11-2016
  * @brief   stm32f4xx_Usart.c
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "stm32f4xx_Usart.h"

UART_HandleTypeDef UartHandle;

//__IO ITStatus UartReady = RESET;
//__IO uint32_t UserButtonStatus = 0;  /* set to 1 after User Button interrupt  */

uint8_t aTxBuffer[] = "Hello World!\n";
uint8_t aRxBuffer[RXBUFFERSIZE];

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	while((USART6->SR&0X40)==0);//ѭ������,ֱ���������   
	USART6->DR = (uint8_t) ch;      
	return ch;
}
#endif 


void Init_Usart6(void){
  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 115200 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance        = USART6;

  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B; //8λ����
  UartHandle.Init.StopBits   = UART_STOPBITS_1;    //һλֹͣλ
  UartHandle.Init.Parity     = UART_PARITY_NONE;   //
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;//
  UartHandle.Init.Mode       = UART_MODE_TX_RX;    //
	//��λ����
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    //Error_Handler();
  }  
	
	//��ʼ������
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    //Error_Handler();
  }
	//__HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE); //ʹ�ܽ����ж�
	//__HAL_UART_ENABLE_IT(&UartHandle, UART_IT_TXE); //ʧ�ܷ����ж�
	HAL_UART_Receive_IT(&UartHandle, (uint8_t *)aRxBuffer, 1);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������

}


/**
  * @brief  Tx Transfer completed callback
  * @param  UartHandle: UART handle. 
  * @note   This example shows a simple way to report end of IT Tx transfer, and 
  *         you can add your own implementation. 
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
  //UartReady = SET;
  /*
	 * �����ж�
	 */
}


/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of DMA Rx transfer, and 
  *         you can add your own implementation.
  * @retval �����жϺ���
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */

	if(UartHandle->Instance == USART6){
			HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_RESET);
	}
  
}


/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  /* Turn LED4 on: Transfer error in reception/transmission process */
  //BSP_LED_On(LED4); 
}


/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Enable USARTx clock */
  __HAL_RCC_USART6_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
    
  /*##-3- Configure the NVIC for UART ########################################*/
  /* NVIC for USART �������ȼ���ʹ�����ȼ�����*/
  HAL_NVIC_EnableIRQ(USART6_IRQn);
  HAL_NVIC_SetPriority(USART6_IRQn, 3, 3);
}

/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
  
  /*##-3- Disable the NVIC for UART ##########################################*/
  HAL_NVIC_DisableIRQ(USARTx_IRQn);
}
