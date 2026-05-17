/**
  ******************************************************************************
  * @file           : crc.h
  * @brief          : Header for crc.c file.
 s * @details		: Driver for the CRC (cyclic redundancy check)
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_INC_CRC_H_
#define BSP_INC_CRC_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @defgroup crc_Drive CRC Drive
   * @brief    Public API for crc driver.
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


  /*******************************************************************************/
  /* Exported Constants ---------------------------------------------------------*/
  /*******************************************************************************/
  /*--None*/

  /*******************************************************************************/
  /* Exported Macros ------------------------------------------------------------*/
  /*******************************************************************************/
  /*--None*/

  /*******************************************************************************/
  /* Exported Variables ---------------------------------------------------------*/
  /*******************************************************************************/
  /*--None*/

  /*******************************************************************************/
  /* Exported Functions ---------------------------------------------------------*/
  /*******************************************************************************/
  /*--None*/
  extern void xDriverCrc_OPEN();
  extern void xDriverCrc_CLOSE();
  extern BspReturn_t xCrc_CALC(uint32_t *, uint8_t, uint32_t *);
  /**
   * @}
   */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* BSP_INC_CRC_H_ */
/* End of File */
