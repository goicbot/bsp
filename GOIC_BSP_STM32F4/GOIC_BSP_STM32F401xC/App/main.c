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

void TIM2_IRQHandler()
{
	if(READ_BIT(TIM2->SR, TIM_SR_UIF))
	{
		CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
		xGpioToggle(&gpio[PORT_C][PIN_13]);
	}
}

/**
  * @brief   Main function.
  */
int main()
{
	/* RCC module initialization */				vRcc_INIT();
	/* GPIO module initialization*/				xGpioInit();
	/* CRC driver Open*/						assert(xCrcOpen() == BSP_ERROR_OK);


	/*GPIO CONFIG*/								assert(xGpioSetConfig(&gpio[PORT_C][PIN_13]) == BSP_ERROR_OK);

	xGpioToggle(&gpio[PORT_C][PIN_13]);


	vTim2BasicTimer(8399,4999,TRUE);
	uint32_t buf[3] = {0x01, 0xD0, 0x31};
	uint8_t size = 3;
	uint32_t crc = 0x00;
	crc = 0x00UL;
	xCrcCalc(buf, size ,&crc);
	/* CRC driver Close */						assert(xCrcClose() == BSP_ERROR_OK);

	while(1) /* Infinite Loop*/
	{

	}
}
/* End of File */
