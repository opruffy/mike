/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f4xx_hal.h"

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
#define DB3_Pin GPIO_PIN_2
#define DB3_GPIO_Port GPIOE
#define DB2_Pin GPIO_PIN_4
#define DB2_GPIO_Port GPIOE
#define DB0_Pin GPIO_PIN_5
#define DB0_GPIO_Port GPIOE
#define DB1_Pin GPIO_PIN_6
#define DB1_GPIO_Port GPIOE
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define LEFT_Pin GPIO_PIN_10
#define LEFT_GPIO_Port GPIOB
#define LEFT_EXTI_IRQn EXTI15_10_IRQn
#define PUSH_Pin GPIO_PIN_11
#define PUSH_GPIO_Port GPIOB
#define PUSH_EXTI_IRQn EXTI15_10_IRQn
#define UP_Pin GPIO_PIN_12
#define UP_GPIO_Port GPIOB
#define UP_EXTI_IRQn EXTI15_10_IRQn
#define DOWN_Pin GPIO_PIN_13
#define DOWN_GPIO_Port GPIOB
#define DOWN_EXTI_IRQn EXTI15_10_IRQn
#define RIGHT_Pin GPIO_PIN_14
#define RIGHT_GPIO_Port GPIOB
#define RIGHT_EXTI_IRQn EXTI15_10_IRQn
#define GREEN_LED_Pin GPIO_PIN_12
#define GREEN_LED_GPIO_Port GPIOD
#define ORANGE_LED_Pin GPIO_PIN_13
#define ORANGE_LED_GPIO_Port GPIOD
#define RED_LED_Pin GPIO_PIN_14
#define RED_LED_GPIO_Port GPIOD
#define BLUE_LED_Pin GPIO_PIN_15
#define BLUE_LED_GPIO_Port GPIOD
#define GLCD_RESET_Pin GPIO_PIN_9
#define GLCD_RESET_GPIO_Port GPIOC
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define GLCD_FONT_Pin GPIO_PIN_10
#define GLCD_FONT_GPIO_Port GPIOC
#define DB7_Pin GPIO_PIN_2
#define DB7_GPIO_Port GPIOD
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOD
#define GLCD_CD_Pin GPIO_PIN_7
#define GLCD_CD_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define GLCD_CE_Pin GPIO_PIN_4
#define GLCD_CE_GPIO_Port GPIOB
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOB
#define DB4_Pin GPIO_PIN_7
#define DB4_GPIO_Port GPIOB
#define GLCD_RD_Pin GPIO_PIN_8
#define GLCD_RD_GPIO_Port GPIOB
#define GLCD_WR_Pin GPIO_PIN_0
#define GLCD_WR_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
