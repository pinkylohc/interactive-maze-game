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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//*** start_x, start_y. rows, columns -> need to be odd(for generate_maze algo)***

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
#define LCD_touch_Pin GPIO_PIN_2
#define LCD_touch_GPIO_Port GPIOE
#define LCD_touchE3_Pin GPIO_PIN_3
#define LCD_touchE3_GPIO_Port GPIOE
#define LCD_touchE4_Pin GPIO_PIN_4
#define LCD_touchE4_GPIO_Port GPIOE
#define LCD_touchE4_EXTI_IRQn EXTI4_IRQn
#define ADC1_IN13_Pin GPIO_PIN_3
#define ADC1_IN13_GPIO_Port GPIOC
#define K1_button_Pin GPIO_PIN_0
#define K1_button_GPIO_Port GPIOA
#define K1_button_EXTI_IRQn EXTI0_IRQn
#define blue_button_Pin GPIO_PIN_2
#define blue_button_GPIO_Port GPIOA
#define green_LED_Pin GPIO_PIN_0
#define green_LED_GPIO_Port GPIOB
#define blue_LED_Pin GPIO_PIN_1
#define blue_LED_GPIO_Port GPIOB
#define LCD_Pin GPIO_PIN_12
#define LCD_GPIO_Port GPIOD
#define red_LED_Pin GPIO_PIN_5
#define red_LED_GPIO_Port GPIOB
#define LCD_touchE0_Pin GPIO_PIN_0
#define LCD_touchE0_GPIO_Port GPIOE
#define LCDE1_Pin GPIO_PIN_1
#define LCDE1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
