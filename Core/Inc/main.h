/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NW_SW_Pin GPIO_PIN_0
#define NW_SW_GPIO_Port GPIOA
#define NW_SW_EXTI_IRQn EXTI0_1_IRQn
#define WW_SW_Pin GPIO_PIN_1
#define WW_SW_GPIO_Port GPIOA
#define WW_SW_EXTI_IRQn EXTI0_1_IRQn
#define INCR_SW_Pin GPIO_PIN_2
#define INCR_SW_GPIO_Port GPIOA
#define INCR_SW_EXTI_IRQn EXTI2_3_IRQn
#define DECR_SW_Pin GPIO_PIN_3
#define DECR_SW_GPIO_Port GPIOA
#define DECR_SW_EXTI_IRQn EXTI2_3_IRQn
#define POWER_Pin GPIO_PIN_4
#define POWER_GPIO_Port GPIOA
#define POWER_EXTI_IRQn EXTI4_15_IRQn
#define CW_SW_Pin GPIO_PIN_5
#define CW_SW_GPIO_Port GPIOA
#define CW_SW_EXTI_IRQn EXTI4_15_IRQn
#define CW_Pin GPIO_PIN_6
#define CW_GPIO_Port GPIOA
#define ON_OFF_Pin GPIO_PIN_7
#define ON_OFF_GPIO_Port GPIOA
#define WW_Pin GPIO_PIN_0
#define WW_GPIO_Port GPIOB
#define NW_Pin GPIO_PIN_1
#define NW_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_8
#define D5_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_9
#define D4_GPIO_Port GPIOA
#define D3_Pin GPIO_PIN_10
#define D3_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_11
#define D2_GPIO_Port GPIOA
#define D1_Pin GPIO_PIN_12
#define D1_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
