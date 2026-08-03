/**
 ******************************************************************************
 * @file           : crc.c
 * @brief          : Source file for crc.h module.
 * @details		: Driver for the CRC (cyclic redundancy check)
 * @author         : GOIC Embedded Systems
 * @date           : May 6, 2026
 * @version        : 1.0.0
 * @copyright      : Copyright (c) 2026 GOIC Embedded Systems
 ******************************************************************************
 * @attention
 *
 * MIT License
 *
 * Copyright (c) May 6, 2026 GOIC Embedded Systems
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
#include "stm32f4xx.h"
#include "rcc.h"
#include "crc.h"

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
 * @brief Verifies whether the clock control for the CRC module is enabled
 * @return BSP return result
 */

bool_t xIsCrcOpen()
{
	bool_t  rtnVal = TRUE;

	uint32_t regVal;

	regVal = RCC_READ_AHB1ENR(RCC_AHB1ENR_CRCEN);

	if(regVal)
	{
		rtnVal =  FALSE;
	}

	return rtnVal;
}

/**
 * @brief CRC driver CLOSE
 */
bspError_t xCrcClose()
{
	bspError_t rtnVal = BSP_ERROR_CRC;

	if (!xIsCrcOpen())
	{
		/* RCC AHB1 peripheral clock enable register */
		RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_CRCEN);

		rtnVal =  BSP_ERROR_OK;
	}

	return rtnVal;
}

/**
 * @brief CRC driver OPEN
 */
bspError_t xCrcOpen()
{
	bspError_t rtnVal = BSP_ERROR_CRC;
	if (xIsCrcOpen())
	{
		/* RCC AHB1 peripheral clock enable register */
		RCC_SET_AHB1ENR(RCC_AHB1ENR_CRCEN);
		rtnVal = BSP_ERROR_OK;
	}
	return rtnVal;
}

/**
 * @brief Reset the CCR module through the Control Register
 */
static void vCrcReset()
{
	SET_BIT(CRC->CR,CRC_CR_RESET);
}

/**
 * @brief Write data into DR register to calculate the CRC
 */
static void vCrcDrWrite(uint32_t data2Write)
{
	WRITE_REG(CRC->DR,data2Write);
}

/**
 * @brief Read data from DR register with the calculated CRC
 */
static void vCrcDrRead(uint32_t *p_data2Read)
{

  *p_data2Read = READ_REG(CRC->DR);
}


/**
 * @brief Calculates the CCR
 * @detail Uses CRC-32 (Ethernet) polynomial
 * @param[in] p_buf Buffer data to calculate CRC
 * @param[in] size Buffer size
 * @param[in] p_crc Holds the CRC result
 * @return BSP return result
 */
bspError_t xCrcCalc(uint32_t *p_buf, uint8_t size, uint32_t *p_crc)
{
	bspError_t rtnVal = BSP_ERROR_OK;

	if (!(xIsCrcOpen() || p_buf == NULL ||  size == 0U || p_crc == NULL))
	{
		/* Reset CRC */
		vCrcReset();

		for (uint8_t idx = 0; idx < size; idx++)
		{
			vCrcDrWrite(p_buf[idx]);
		}

		vCrcDrRead(p_crc);
	}
	else
	{
		*p_crc = CRC_CR_RESET;

		rtnVal = BSP_ERROR_CRC;
	}

	return rtnVal;
}


#if 0
/**
 * @brief Write data into IDR General Purpose register
 */
static void vCrcIdrWrite( uint8_t data2Write){

  WRITE_REG(CRC->IDR,data2Write);

}

/**
 * @brief Read data from IDR register general purpose
 */
static	void vCrcIdrRead(uint8_t *p_data2Read){

  *p_data2Read = READ_REG(CRC->IDR);

}
#endif
/* End of File */
