/**
  ******************************************************************************
  * @file           : tim.c
  * @brief          : Source file for tim.h module.
  * @author         : GOIC Embedded Systems
  * @date           : Jun 14, 2026
  * @version        : 1.0.0
  * @copyright      : Copyright (c) 2026 GOIC Embedded Systems
  ******************************************************************************
  * @attention
  *
  * MIT License
  *
  * Copyright (c) Jun 14, 2026 GOIC Embedded Systems
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

#include "stm32f4xx.h"
#include "tim.h"
#include "rcc.h"

/*******************************************************************************/
/* Private Define -------------------------------------------------------------*/
/*******************************************************************************/
/*--None*/
/* #define EXAMPLE_TIMEOUT_MS   (100U) */ /**< Internal timeout constant */

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


void vTim1BasicTimer(uint16_t psc, uint16_t arr, uint8_t rcr)
{
	RCC_SET_APB2ENR(RCC_APB2ENR_TIM1EN);

	CLEAR_BIT(TIM1->CNT,TIM_CNT_CNT);

	MODIFY_REG(TIM1->PSC,TIM_PSC_PSC, psc);

	MODIFY_REG(TIM1->ARR,TIM_ARR_ARR,arr);

	MODIFY_REG(TIM1->RCR,TIM_RCR_REP, rcr);

	SET_BIT(TIM1->CR1,TIM_CR1_URS);

	CLEAR_BIT(TIM1->CR1,TIM_CR1_UDIS);

	SET_BIT(TIM1->CR1,TIM_CR1_CEN);
}

void vTim2BasicTimer(uint16_t psc, uint16_t arr, bool_t intpt)
{
	RCC_SET_APB1ENR(RCC_APB1ENR_TIM2EN);

	CLEAR_BIT(TIM2->CNT,TIM_CNT_CNT);

	MODIFY_REG(TIM2->PSC,TIM_PSC_PSC, psc);

	MODIFY_REG(TIM2->ARR,TIM_ARR_ARR,arr);

	SET_BIT(TIM2->CR1,TIM_CR1_URS);

	CLEAR_BIT(TIM2->CR1,TIM_CR1_UDIS);

	if(intpt == TRUE)
	{
		SET_BIT(TIM2->DIER,TIM_DIER_UIE);

		NVIC_EnableIRQ(TIM2_IRQn);
	}

	SET_BIT(TIM2->CR1,TIM_CR1_CEN);
}

/* End of File */
