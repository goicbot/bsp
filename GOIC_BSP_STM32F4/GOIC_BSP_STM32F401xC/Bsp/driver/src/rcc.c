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
void vRcc_INIT(){

	/* Enable HSE and wait for it to be ready*/
	RCC_SET_CR(RCC_CR_HSEON);
	while(RCC_READ_CR(RCC_CR_HSERDY) == 0x0UL){/*Do nothing*/}
	// Enable Prefetch, Instruction Cache, Data Cache and set 2 Latency wait states
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_2WS);
	// 3. Configure AHB and APB Bus Prescaler
	// HCLK = 84MHz (Div 1), PCLK1 = 42MHz (Div 2 max), PCLK2 = 84MHz (Div 1)
	RCC_MODIFY_CFRG(RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
	RCC_MODIFY_CFRG(RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2);
	RCC_MODIFY_CFRG(RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1);
	/* PLL configuration register*/
	RCC_WRITE_PLLCFGR(	(25 << RCC_PLLCFGR_PLLM_Pos) 	|
						(336 << RCC_PLLCFGR_PLLN_Pos)	|
						(1 << RCC_PLLCFGR_PLLP_Pos)	 	|
						(7 << RCC_PLLCFGR_PLLQ_Pos)		|
						RCC_PLLCFGR_PLLSRC_HSE
						);

	/* Enable PLL and wait for it to be ready*/
	RCC_SET_CR(RCC_CR_PLLON);
	while(RCC_READ_CR(RCC_CR_PLLRDY) == 0x0UL){/*Do nothing*/}
	//Switch System Clock to PLL
	RCC_MODIFY_CFRG(RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    while (RCC_READ_CFGR(RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {/*Do nothing*/}
}

/* End of File */
