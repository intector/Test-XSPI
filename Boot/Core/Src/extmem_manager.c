/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : extmem_manager.c
  * @version        : 1.0.0
  * @brief          : This file implements the extmem configuration
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

/* Includes ------------------------------------------------------------------*/
#include "extmem_manager.h"
#include <string.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Init External memory manager
  * @retval None
  */
void MX_EXTMEM_MANAGER_Init(void)
{

  /* USER CODE BEGIN MX_EXTMEM_Init_PreTreatment */

  /* USER CODE END MX_EXTMEM_Init_PreTreatment */
  HAL_RCCEx_EnableClockProtection(RCC_CLOCKPROTECT_XSPI);

  /* Initialization of the memory parameters */
  memset(extmem_list_config, 0x0, sizeof(extmem_list_config));

  /* EXTMEMORY_1 */
  extmem_list_config[0].MemType = EXTMEM_NOR_SFDP;
  extmem_list_config[0].Handle = (void*)&hxspi2;
  extmem_list_config[0].ConfigType = EXTMEM_LINK_CONFIG_8LINES;

  /* EXTMEMORY_2 */
  extmem_list_config[1].MemType = EXTMEM_PSRAM;
  extmem_list_config[1].Handle = (void*)&hxspi1;
  extmem_list_config[1].ConfigType = EXTMEM_LINK_CONFIG_16LINES;

  extmem_list_config[1].PsramObject.psram_public.MemorySize = HAL_XSPI_SIZE_256MB;
  extmem_list_config[1].PsramObject.psram_public.FreqMax = 200 * 1000000u;
  extmem_list_config[1].PsramObject.psram_public.NumberOfConfig = 3u;

  /* Config */
  extmem_list_config[1].PsramObject.psram_public.config[0].WriteMask = 0x30u;
  extmem_list_config[1].PsramObject.psram_public.config[0].WriteValue = 0x30u;
  extmem_list_config[1].PsramObject.psram_public.config[0].REGAddress = 0x00u;

  extmem_list_config[1].PsramObject.psram_public.config[1].WriteMask = 0x20u;
  extmem_list_config[1].PsramObject.psram_public.config[1].WriteValue = 0x20u;
  extmem_list_config[1].PsramObject.psram_public.config[1].REGAddress = 0x04u;

  extmem_list_config[1].PsramObject.psram_public.config[2].WriteMask = 0x4Bu;
  extmem_list_config[1].PsramObject.psram_public.config[2].WriteValue = 0x4Bu;
  extmem_list_config[1].PsramObject.psram_public.config[2].REGAddress = 0x08u;

  /* Memory command configuration */
  extmem_list_config[1].PsramObject.psram_public.ReadREG           = 0x40u;
  extmem_list_config[1].PsramObject.psram_public.WriteREG          = 0xC0u;
  extmem_list_config[1].PsramObject.psram_public.ReadREGSize       = 2u;
  extmem_list_config[1].PsramObject.psram_public.REG_DummyCycle    = 6u;
  extmem_list_config[1].PsramObject.psram_public.Write_command     = 0x80u;
  extmem_list_config[1].PsramObject.psram_public.Write_DummyCycle  = 7u;
  extmem_list_config[1].PsramObject.psram_public.Read_command      = 0x00u;
  extmem_list_config[1].PsramObject.psram_public.WrapRead_command  = 0x00u;
  extmem_list_config[1].PsramObject.psram_public.Read_DummyCycle   = 7u;

  // get frequency for PSRAM
  uint32_t PERIPHCLK_XSPI1 = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1);
  // get frequency for FLASH
  uint32_t PERIPHCLK_XSPI2 = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2);

  // initialize FLASH
  if (EXTMEM_Init(EXTMEMORY_1, PERIPHCLK_XSPI2) != EXTMEM_OK)
  {
	  Error_Handler();
  }
  // firmware fix for clock Pre-scaler, activate next line if you want to use your Pre-scaler factor
  // MODIFY_REG(hxspi2.Instance->DCR2, XSPI_DCR2_PRESCALER, hxspi2.Init.ClockPrescaler << XSPI_DCR2_PRESCALER_Pos);


  // initialize PSRAM
  if (EXTMEM_Init(EXTMEMORY_2, PERIPHCLK_XSPI1) != EXTMEM_OK)
  {
	  Error_Handler();
  }
  // firmware fix for clock Pre-scaler, activate next line if you want to use your Pre-scaler factor
  // MODIFY_REG(hxspi1.Instance->DCR2, XSPI_DCR2_PRESCALER, hxspi1.Init.ClockPrescaler << XSPI_DCR2_PRESCALER_Pos);

  /* USER CODE BEGIN MX_EXTMEM_Init_PostTreatment */

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // keeping this backup to prevent deletion on STM32Cube32 rebuild
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
  extmem_list_config[1].PsramObject.psram_public.MemorySize = HAL_XSPI_SIZE_256MB;
  extmem_list_config[1].PsramObject.psram_public.FreqMax = 200 * 1000000u;

  // Config
  extmem_list_config[1].PsramObject.psram_public.NumberOfConfig = 3u;

  extmem_list_config[1].PsramObject.psram_public.config[0].WriteMask = 0x30u;
  extmem_list_config[1].PsramObject.psram_public.config[0].WriteValue = 0x30u;
  extmem_list_config[1].PsramObject.psram_public.config[0].REGAddress = 0x00u;

  extmem_list_config[1].PsramObject.psram_public.config[1].WriteMask = 0x20u;
  extmem_list_config[1].PsramObject.psram_public.config[1].WriteValue = 0x20u;
  extmem_list_config[1].PsramObject.psram_public.config[1].REGAddress = 0x04u;

  extmem_list_config[1].PsramObject.psram_public.config[2].WriteMask = 0x4Bu;
  extmem_list_config[1].PsramObject.psram_public.config[2].WriteValue = 0x4Bu;
  extmem_list_config[1].PsramObject.psram_public.config[2].REGAddress = 0x08u;

  // Memory command configuration
  extmem_list_config[1].PsramObject.psram_public.ReadREG           = 0x40u;
  extmem_list_config[1].PsramObject.psram_public.WriteREG          = 0xC0u;
  extmem_list_config[1].PsramObject.psram_public.ReadREGSize       = 2u;
  extmem_list_config[1].PsramObject.psram_public.REG_DummyCycle    = 6u;
  extmem_list_config[1].PsramObject.psram_public.Write_command     = 0x80u;
  extmem_list_config[1].PsramObject.psram_public.Write_DummyCycle  = 7u;
  extmem_list_config[1].PsramObject.psram_public.Read_command      = 0x20u;
  extmem_list_config[1].PsramObject.psram_public.Read_command      = 0x00u;
  extmem_list_config[1].PsramObject.psram_public.WrapRead_command  = 0x00u;
  extmem_list_config[1].PsramObject.psram_public.Read_DummyCycle   = 7u;

  // *****************************************************************************
  // original code from firmware package: STM32Cube_FW_H7RS_V1.1.0
  // example code: STM32H7S78-DK/Template_XIP
  // *****************************************************************************

  //  EXTMEM_Init(EXTMEMORY_1, HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2));
  //  EXTMEM_Init(EXTMEMORY_2, HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1));

  // *****************************************************************************

  // get frequency for PSRAM
  uint32_t PERIPHCLK_XSPI1 = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1);
  // get frequency for FLASH
  uint32_t PERIPHCLK_XSPI2 = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2);

  // initialize FLASH
  if (EXTMEM_Init(EXTMEMORY_1, PERIPHCLK_XSPI2) != EXTMEM_OK)
  {
	  Error_Handler();
  }
  // firmware fix for clock Pre-scaler, activate next line if you want to use your Pre-scaler factor
  // MODIFY_REG(hxspi2.Instance->DCR2, XSPI_DCR2_PRESCALER, hxspi2.Init.ClockPrescaler << XSPI_DCR2_PRESCALER_Pos);


  // initialize PSRAM
  if (EXTMEM_Init(EXTMEMORY_2, PERIPHCLK_XSPI1) != EXTMEM_OK)
  {
	  Error_Handler();
  }
  // firmware fix for clock Pre-scaler, activate next line if you want to use your Pre-scaler factor
  // MODIFY_REG(hxspi1.Instance->DCR2, XSPI_DCR2_PRESCALER, hxspi1.Init.ClockPrescaler << XSPI_DCR2_PRESCALER_Pos);


  // *****************************************************************************
*/

  /* USER CODE END MX_EXTMEM_Init_PostTreatment */
}
