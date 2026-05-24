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

/**
  * @brief   Main function.
  */
int main()
{
	/* RCC module initialization */				vDriverRcc_INIT();
	/* GPIO module initialization*/				xGpio_INIT();
	/* CRC driver Open*/						assert(xDriverCrc_OPEN() == BSP_RETURN_OK);


	GpioConfig_t gpioP13C_t = {
			.pin = 13,
			.port = GPIO_C,
			.mode = GPIO_OUTPUT_MODE,
			.type = GPIO_PUSH_PULL,
			.speed = GPIO_HIGH_SPEED,
			.pupdr = GPIO_PULL_UP,
			.altFunc = GPIO_AF0,
	};

	/*GPIO CONFIG*/								assert(xGpio_CONFIG(&gpioP13C_t) == BSP_RETURN_OK);
	xGpio_WRITE(&gpioP13C_t, GPIO_HIGH);
	xGpio_WRITE(&gpioP13C_t, GPIO_LOW);
	uint32_t buf[3] = {0x01, 0xD0, 0x31};
	uint8_t size = 3;
	uint32_t crc = 0x00;
	crc = 0x00UL;
	xCrc_CALC(buf, size ,&crc);
	/* CRC driver Close */						assert(xDriverCrc_CLOSE() == BSP_RETURN_OK);
	while(1) /* Infinite Loop*/
	{

	}
}
/* End of File */
