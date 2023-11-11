#include "uart.h"


/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */

 UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void)
{
  
  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_UART_Receive_IT(&huart1 , (uint8_t*)Rx_data , 22);
    while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE));
    if(huart1.Instance == USART1)
    {
        uart_flag = 1;
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{


    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE) != RESET) 
    {
        // 重新初始化串口
        HAL_UART_DeInit(&huart1);
        HAL_UART_Init(&huart1);

        // 重新启动串口接收
        HAL_UART_Receive_IT(&huart1, (uint8_t*)Rx_data, 22);

        //__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_OREF);
        //__HAL_UART_CLEAR_OREFLAG(&huart1);
    }
}



