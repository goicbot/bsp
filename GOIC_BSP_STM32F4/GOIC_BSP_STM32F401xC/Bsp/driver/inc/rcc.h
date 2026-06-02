/**
  ******************************************************************************
  * @file           : rcc.h
  * @brief          : Header for rcc.c file.
  * @details        : Reset and Clock Control module.
  * @author         : GOIC Embedded Systems
  * @date           : May 9, 2026
  * @version        : 1.0.0
  * @copyright      : Copyright (c) 2026 GOIC Embedded Systems
  ******************************************************************************
  * @attention
  *
  * MIT License
  *
  * Copyright (c) May 9, 2026 GOIC Embedded Systems
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all
  * copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_DRIVER_INC_RCC_H_
#define BSP_DRIVER_INC_RCC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  * @defgroup rcc_Module rcc Module
  * @brief    Public API for rcc driver.
  * @{
  */

/*******************************************************************************/
/* Includes -------------------------------------------------------------------*/
/*******************************************************************************/

#include "bsp_core.h"

/*******************************************************************************/
/* Exported Types -------------------------------------------------------------*/
/*******************************************************************************/
/*--None*/
/**
  * @brief Example of public enumeration type.
  */
/*
typedef enum
{
    EXAMPLE_OK = 0U,   ///< Operation successful
    EXAMPLE_ERROR      ///< Operation failed
} ExampleStatus_t;
*/

/**
  * @brief Example of configuration structure.
  */
/*
typedef struct
{
    uint32_t frequency;   ///< Operating frequency in Hz
    uint16_t voltage;     ///< Operating voltage in mV
} ExampleConfig_t;
*/

/*******************************************************************************/
/* Exported Constants ---------------------------------------------------------*/
/*******************************************************************************/
/*--None*/
/* #define EXAMPLE_DEFAULT_FREQUENCY   (1000U) */ /**< Default frequency in Hz */

/*******************************************************************************/
/* Exported Macros ------------------------------------------------------------*/
/*******************************************************************************/
/*--None*/
/* #define EXAMPLE_IS_VALID(x)  ((x) <= 5000U) */ /**< Checks valid input range */

/*******************************************************************************/
/* Exported Variables ---------------------------------------------------------*/
/*******************************************************************************/
/*--None*/
/* extern ExampleConfig_t g_example_config; */ /**< Global configuration instance */

/*******************************************************************************/
/* Exported Functions ---------------------------------------------------------*/
/*******************************************************************************/

extern void vRcc_INIT();

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* BSP_DRIVER_INC_RCC_H_ */
/* End of File */
