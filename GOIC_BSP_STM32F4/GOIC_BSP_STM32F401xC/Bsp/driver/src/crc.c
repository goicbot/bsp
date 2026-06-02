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
static void vDriverCrc_RESET(void);
static void vDriverCrc_DR_WRITE(uint32_t *);
static void xDriverCrc_DR_READ(uint32_t *);
/*static void vDriverCrc_IDR_WRITE(uint8_t);*/
/*static void xDriverCrc_IDR_READ(uint8_t *);*/
BspReturn_t xCrc_OPEN();
BspReturn_t xCrc_CLOSE();
static BspReturn_t xCrc_ISOPEN();
BspReturn_t xCrc_CALC(uint32_t *, uint8_t, uint32_t *);

/**
 * @brief CRC driver CLOSE
 */
BspReturn_t xCrc_CLOSE()
{
	if ( xCrc_ISOPEN() == BSP_RETURN_OK)
	{
		/* RCC AHB1 peripheral clock enable register */
		RCC->AHB1ENR &= ~RCC_AHB1ENR_CRCEN;
		return BSP_RETURN_OK;
	}
	return BSP_RETURN_ERROR_CRC;
}

/**
 * @brief CRC driver OPEN
 */
BspReturn_t xCrc_OPEN()
{
	if ( xCrc_ISOPEN() == BSP_RETURN_ERROR_CRC)
	{
		/* RCC AHB1 peripheral clock enable register */
		RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;
		return BSP_RETURN_OK;
	}
	return BSP_RETURN_ERROR_CRC;
}

/**
 * @brief Verifies whether the clock control for the CRC module is enabled
 * @return BSP return result
 */

BspReturn_t xCrc_ISOPEN()
{
	uint8_t bit;

	bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_CRCEN_Msk) >> RCC_AHB1ENR_CRCEN_Pos);

	if(bit)
		return BSP_RETURN_OK;
	else
		return BSP_RETURN_ERROR_CRC;
}

/**
 * @brief Calculates the CCR
 * @detail Uses CRC-32 (Ethernet) polynomial
 * @param[in] p_buf Buffer data to calculate CRC
 * @param[in] size Buffer size
 * @param[in] p_crc Holds the CRC result
 * @return BSP return result
 */
BspReturn_t xCrc_CALC(uint32_t *p_buf, uint8_t size, uint32_t *p_crc)
{

  if ( xCrc_ISOPEN() == BSP_RETURN_ERROR_CRC || p_buf == NULL ||  size == 0x00UL || p_crc == NULL)
  {
    *p_crc = CRC_CR_RESET;
    return BSP_RETURN_ERROR_CRC;
  }

  /* Reset CRC */
  vDriverCrc_RESET();

  for (uint8_t idx = 0; idx < size; idx++)
  {
    vDriverCrc_DR_WRITE(&p_buf[idx]);
  }

  xDriverCrc_DR_READ(p_crc);

  return BSP_RETURN_OK;
}

/**
 * @brief Reset the CCR module through the Control Register
 */
static void vDriverCrc_RESET()
{

  CRC->CR |= CRC_CR_RESET;
}

/**
 * @brief Write data into DR register to calculate the CRC
 */
static void vDriverCrc_DR_WRITE(uint32_t *data2Write)
{

  CRC->DR = *data2Write;
}

/**
 * @brief Read data from DR register with the calculated CRC
 */
static void xDriverCrc_DR_READ(uint32_t *p_data2Read)
{

  *p_data2Read = CRC->DR;
}

/**
 * @brief Write data into IDR General Purpose register
 */
/*static void vDriverCrc_IDR_WRITE( uint8_t data2Write){

  CRC->IDR = data2Write;

}*/

/**
 * @brief Read data from IDR register general purpose
 */
/*static	void xDriverCrc_IDR_READ(uint8_t *p_data2Read){

  *p_data2Read = CRC->IDR;

}*/

/* End of File */
