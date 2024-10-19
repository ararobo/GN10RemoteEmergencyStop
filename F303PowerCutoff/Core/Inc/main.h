/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

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
#define DISCHARGE_Pin GPIO_PIN_1
#define DISCHARGE_GPIO_Port GPIOA
#define RELAY_EN_Pin GPIO_PIN_2
#define RELAY_EN_GPIO_Port GPIOA
#define LED_WIRED_STOP_Pin GPIO_PIN_4
#define LED_WIRED_STOP_GPIO_Port GPIOA
#define LED_REMOTE_STOP_Pin GPIO_PIN_5
#define LED_REMOTE_STOP_GPIO_Port GPIOA
#define LED_MODE_Pin GPIO_PIN_6
#define LED_MODE_GPIO_Port GPIOA
#define LED_ID1_Pin GPIO_PIN_7
#define LED_ID1_GPIO_Port GPIOA
#define ENABLE_Pin GPIO_PIN_8
#define ENABLE_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define DIP_1_Pin GPIO_PIN_3
#define DIP_1_GPIO_Port GPIOB
#define DIP_2_Pin GPIO_PIN_4
#define DIP_2_GPIO_Port GPIOB
#define SW_1_Pin GPIO_PIN_5
#define SW_1_GPIO_Port GPIOB
#define SW_2_Pin GPIO_PIN_6
#define SW_2_GPIO_Port GPIOB
#define SW_3_Pin GPIO_PIN_7
#define SW_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
