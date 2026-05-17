/**
  ******************************************************************************
  * @file           : rcc.c
  * @brief          : Source file for rcc.h module.
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

/*******************************************************************************/
/* Includes -------------------------------------------------------------------*/
/*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "rcc.h"

/*******************************************************************************/
/* Private Define -------------------------------------------------------------*/
/*******************************************************************************/
/*--None*/

/*******************************************************************************/
/* Private Typedef ------------------------------------------------------------*/
/*******************************************************************************/
/*--None*/

/*******************************************************************************/
/* Private Variables ----------------------------------------------------------*/
/*******************************************************************************/
/*--None*/

/*******************************************************************************/
/* Private Function Prototypes ------------------------------------------------*/
/*******************************************************************************/
/*--None*/

/*******************************************************************************/
/* Private Function Implementations -------------------------------------------*/
/*******************************************************************************/
/*--None*/


/*******************************************************************************/
/* Public Function Implementations --------------------------------------------*/
/*******************************************************************************/

/**
 * @brief RCC module initialization
 * @details The goal frequency PLL is of 84MHz
 */
void vDriverRcc_INIT(){

	RCC->CR &= ~(RCC_CR_HSION_Msk | RCC_CR_HSITRIM_Msk |RCC_CR_HSEON_Msk |
			 RCC_CR_HSEBYP_Msk | RCC_CR_CSSON_Msk | RCC_CR_PLLON_Msk | RCC_CR_PLLI2SON_Msk);

	/* PLL configuration register*/
	RCC->PLLCFGR &= ~( RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLP_Msk |
			RCC_PLLCFGR_PLLQ_Msk);

	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLM_4 | RCC_PLLCFGR_PLLM_3 | RCC_PLLCFGR_PLLM_0);// 1.0 MHz = VCO_INPUT = BSP_RCC_HSE_OSC/BSP_RCC_PLLM
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_2 | RCC_PLLCFGR_PLLN_0);// 336MHz = VCO_OUTPUT = VCO_INPUT * BSP_RCC_PLLN
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLP_1); // 84MHz = VCO_OUTPUT / BSP_RCC_PLLP
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_0); // 48MHz = VCO_OUTPUT / BSP_RCC_PLLQ
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

	/* RCC clock configuration register*/
	RCC->CFGR |= (RCC_CFGR_RTCPRE_4 | RCC_CFGR_RTCPRE_3 | RCC_CFGR_RTCPRE_0);
	RCC->CFGR |= RCC_CFGR_SW_HSE;


	/* Control Register */
	RCC->CR |= RCC_CR_HSION;
	RCC->CR |= RCC_CR_HSEON;
	RCC->CR |= RCC_CR_CSSON;
	RCC->CR |= RCC_CR_PLLON;
	RCC->CR |= RCC_CR_PLLI2SON;

}

/* End of File */
