/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define MOTORE_USE_PD

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t TrackData = 0x00;
uint8_t _preTrackData = 0x00;
uint8_t _trackDataUtil = 0x00;

volatile uint8_t rx_len;        //接收一帧数据的长度
volatile uint8_t recv_end_flag; //一帧数据接收完成标志
uint8_t rx_buffer[16];          //接收数据缓存数组
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  // HAL_UART_Receive_DMA(&huart1, &ubuff, 8);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (recv_end_flag == 1) //接收完成标志
    {
      HAL_UART_Transmit_DMA(&huart1, rx_buffer, rx_len);
      rx_len = 0;        //清除计数
      recv_end_flag = 0; //清除接收结束标志位
      for (uint8_t i = 0; i < rx_len; i++)
      {
        rx_buffer[i] = 0; //清接收缓存
      }
    }
    HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE); //重新打开DMA接收
    if (rx_buffer[0] < 101)
    {
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, rx_buffer[0]);
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 0);
    }
    else
    {
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0);
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, rx_buffer[0] - 100);
    }

    if (rx_buffer[1] < 101)
    {
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, rx_buffer[1]);
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, 0);
    }
    else
    {
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 0);
      __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, rx_buffer[1] - 100);
    }
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, rx_buffer[2]); // PA6 S_PWM1
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, rx_buffer[3]); // PA7 S_PWM2
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, rx_buffer[4]); // PB0 S_PWM3
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, rx_buffer[5]); // PB1 S_PWM4
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, rx_buffer[6]); // PB10 S_PWM5
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, rx_buffer[7]); // PB11 S_PWM6
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  _trackDataUtil = 0x01;
  switch (GPIO_Pin)
  {
  case GPIO_PIN_5:
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
    {
      TrackData = TrackData | _trackDataUtil;
    }
    else
    {
      TrackData = TrackData & ~_trackDataUtil;
    }
    break;
  case GPIO_PIN_4:
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
    {
      TrackData = TrackData | (_trackDataUtil << 1);
    }
    else
    {
      TrackData = TrackData & ~(_trackDataUtil << 1);
    }
    break;

  case GPIO_PIN_3:
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
    {
      TrackData = TrackData | (_trackDataUtil << 2);
    }
    else
    {
      TrackData = TrackData & ~(_trackDataUtil << 2);
    }
    break;

  case GPIO_PIN_15:
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15))
    {
      TrackData = TrackData | (_trackDataUtil << 3);
    }
    else
    {
      TrackData = TrackData & ~(_trackDataUtil << 3);
    }
    break;

  case GPIO_PIN_12:
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
    {
      TrackData = TrackData | (_trackDataUtil << 4);
    }
    else
    {
      TrackData = TrackData & ~(_trackDataUtil << 4);
    }
    break;
  default:
    break;
  }
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
