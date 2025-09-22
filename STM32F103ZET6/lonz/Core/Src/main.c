/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "lcd.h"
#include "key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

char send   [1024];
	
char IP     [100] = "IP is None";

int ADC[3];

char TXT_temperature[100];
float temperature = 54;

char TXT_humidity[100];
long int  humidity = 10;

char TXT_light[100];
long int  light = 54;

char combine[100];
void LCD_show()
{
		 sprintf(TXT_light,"light is %ld   ",light);
		 LCD_ShowString(30,40,210,16,16,TXT_light);	
		 
	   sprintf(TXT_humidity,"humidity is %ld%%   ",humidity);
		 LCD_ShowString(30,70,200,16,16,TXT_humidity);
	
	   sprintf(TXT_temperature,"temperature is %.0f   ",temperature);
		 LCD_ShowString(30,100,200,16,16,TXT_temperature);
	
	   //memset(IP,0,sizeof(IP));
		 LCD_ShowString(30,130,200,16,16,IP);	      				
}

void UART_Send()
{
		 sprintf(combine,"h%d~l%d~t%.0f~",humidity,light,temperature);
	   HAL_UART_Transmit_IT((UART_HandleTypeDef* ) &huart1		     , 
		 										 (uint8_t*             ) combine	       ,
		 										 (uint16_t						 ) strlen(combine));      //×èÈûÊä³ö
		 HAL_UART_Transmit_IT((UART_HandleTypeDef* ) &huart3		     , 
		 										 (uint8_t*             ) combine	       ,
		 										 (uint16_t						 ) strlen(combine));      //×èÈûÊä³ö
}

char receive[50];
void UART_Receive()
{
		 if (HAL_UART_Receive(&huart3, (uint8_t *)receive, sizeof(receive),20) == HAL_OK)
		 {
	       //HAL_UART_Transmit_IT((UART_HandleTypeDef* ) &huart1		     , 
		     //										  (uint8_t*            ) receive	       ,
		     //										  (uint16_t						 ) strlen(receive));      //×èÈûÊä³ö
				 if(receive[0] == 'I')
				 {
					 memset(IP,0,sizeof(IP));
					 strcat(IP,"IP is ");
					 memcpy(IP+6,receive+1,15);
				 }
		 }
}

char key_flag;

void Key_()
{		
		unsigned char key=KEY_Scan(0);            //°´¼üÉ¨Ãè
		switch(key)
		{				 
			case KEY0_PRES:
				   key_flag = !key_flag;
				   break;
			default:
				delay_ms(10);	
		}
    delay_ms(10);
}


void receive_ADC()
{
	   int i = 0;
	   for(i = 0; i < 3; i++)
	   {
				 HAL_ADC_Start(&hadc1);
				 HAL_ADC_PollForConversion(&hadc1 ,50);
				 ADC[i] = HAL_ADC_GetValue( (ADC_HandleTypeDef*) &hadc1); 
				
		 }
		 humidity		 = ADC[0];
		 light		   = ADC[1];
		 temperature = ADC[2];
		 
		 humidity = ((4095 - humidity) * 100)/ 4096;
		 light    = ((4095 - light   ) * 100)/ 4096;
		 temperature = (( 1.43 -(temperature * (3.3/4096))) /0.0043 + 25 );
		 
     HAL_ADC_Stop( (ADC_HandleTypeDef*) &hadc1);
	
		 
}

void scan()
{
	   if (humidity < 5)
		 {
				 HAL_GPIO_WritePin( (GPIO_TypeDef*) GPIOA , 
											 (uint16_t		 ) GPIO_PIN_1 , 
											 (GPIO_PinState) 1         );
		 }
		 else
		 {
			   HAL_GPIO_WritePin( (GPIO_TypeDef*) GPIOA , 
											 (uint16_t		 ) GPIO_PIN_1 , 
											 (GPIO_PinState) 0         );
		 }
}

//void receive_temperature()
//{
//		 HAL_ADC_Start(&hadc2);
//		 HAL_ADC_PollForConversion(&hadc2,50);
//		 temperature = HAL_ADC_GetValue(&hadc2); 
//	   HAL_Delay(5);
//		 temperature = ((4095 - temperature) * 100)/ 4096;
//		 
//		 //HAL_ADC_Stop( (ADC_HandleTypeDef*) &hadc2);
//
//}


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
  MX_USART3_UART_Init();
  MX_USART1_UART_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
	
	//HAL_ADC_Start(&hadc1);    
	//HAL_ADC_Start(&hadc2);    
	HAL_ADCEx_Calibration_Start(&hadc1);
	//HAL_ADCEx_Calibration_Start(&hadc2);
	KEY_Init();
  delay_init(72);
	LCD_Init();           				//³õÊ¼»¯LCD FSMC½Ó¿Ú
	LCD_Clear(WHITE);
  POINT_COLOR=RED;     				//»­±ÊÑÕÉ«£ººìÉ«
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(key_flag)
		{
			 scan();
		}
		receive_ADC();
		//receive_humidity();
		LCD_show();
		UART_Send();
		UART_Receive();
		Key_();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
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

#ifdef  USE_FULL_ASSERT
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
