/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Source file for main.h module.
  * @author         : GOIC Embedded Systems
  * @date           : Nov 11, 2025
  * @version        : 1.0.0
  * @copyright      : Copyright (c) 2025 GOIC Embedded Systems
  ******************************************************************************
  * @attention
  *
  * MIT License
  *
  * Copyright (c) Nov 11, 2025 GOIC Embedded Systems
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

#include "main.h"

#include "stddef.h"
#include "stdio.h"


/*******************************************************************************/
/* Private Define -------------------------------------------------------------*/
/*******************************************************************************/

/* None */

/*******************************************************************************/
/* Private Typedef ------------------------------------------------------------*/
/*******************************************************************************/

/* None */

/*******************************************************************************/
/* Private Variables ----------------------------------------------------------*/
/*******************************************************************************/

/* None */

/*******************************************************************************/
/* Private Function Prototypes ------------------------------------------------*/
/*******************************************************************************/

/* None */

/*******************************************************************************/
/* Private Function Implementations -------------------------------------------*/
/*******************************************************************************/

/* None */

/*******************************************************************************/
/* Public Function Implementations --------------------------------------------*/
/*******************************************************************************/

volatile uint32_t sr_debug;
void TIM2_IRQHandler()
{
	sr_debug = TIM2->SR;
	if(TIM2->SR & TIM_SR_UIF)
	{
	    TIM2->SR &= ~TIM_SR_UIF;
		xGpio_TOGGLE(&gpio[PORT_C][PIN_13]);
	}
}


static void xTim2_INIT()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CNT = 0x0UL;
	TIM2->PSC = 8399;
	TIM2->ARR = 4999;
	//TIM2->CCMR1 |= TIM_CCMR1_OC1M_0;
	//TIM2->CCR1 = 0xF4240UL;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->SR = 0;

	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CR1 |= TIM_CR1_CEN;

}
/**
  * @brief   Main function.
  */
int main()
{
	/* RCC module initialization */				vRcc_INIT();
	/* GPIO module initialization*/				xGpio_INIT();
	/* CRC driver Open*/						assert(xCrc_OPEN() == BSP_RETURN_OK);


	/*GPIO CONFIG*/								assert(xPORT_CONFIG(&gpio[PORT_C][PIN_13]) == BSP_RETURN_OK);

	xGpio_TOGGLE(&gpio[PORT_C][PIN_13]);

	//assert(xGpio_LCKR(0x01<<13,PORT_C) == BSP_RETURN_OK );

	/*GPIO CONFIG*/								assert(xPORT_CONFIG(&gpio[PORT_C][PIN_13]) == BSP_RETURN_OK);

	xGpio_TOGGLE(&gpio[PORT_C][PIN_13]);

	xTim2_INIT();
	uint32_t buf[3] = {0x01, 0xD0, 0x31};
	uint8_t size = 3;
	uint32_t crc = 0x00;
	crc = 0x00UL;
	xCrc_CALC(buf, size ,&crc);
	/* CRC driver Close */						assert(xCrc_CLOSE() == BSP_RETURN_OK);
	while(1) /* Infinite Loop*/
	{

	}
}
/* End of File */
