/**
 ******************************************************************************
 * @file           : bsp_commons.h
 * @brief          : Header for bsp_commons.c file.
 * @author         : GOIC Embedded Systems
 * @date           : May 7, 2026
 * @version        : 1.0.0
 * @copyright      : Copyright (c) 2026 GOIC Embedded Systems
 ******************************************************************************
 * @attention
 *
 * MIT License
 *
 * Copyright (c) May 7, 2026 GOIC Embedded Systems
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
#ifndef BSP_INC_BSP_CORE_H_
#define BSP_INC_BSP_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @defgroup bsp_commons_Module bsp_commons Module
   * @brief    Public API for bsp_commons driver.
   * @{
   */

  /*******************************************************************************/
  /* Includes -------------------------------------------------------------------*/
  /*******************************************************************************/

  /*None ---*/

  /*******************************************************************************/
  /* Exported Types -------------------------------------------------------------*/
  /*******************************************************************************/

  typedef enum
  {
    BSP_RETURN_OK = 0,
    BSP_RETURN_ERROR_CRC,
  } BspReturn_t;

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
  /*--None*/
  /**
   * @brief   Initializes the example module.
   * @param[in] config  Pointer to configuration structure.
   * @return  Status code, see @ref ExampleStatus_t.
   * @note    Must be called before any other function.
   * @par Example:
   * @code
   * ExampleConfig_t cfg = {1000U, 3300U};
   * Example_Init(&cfg);
   * @endcode
   */
  /* ExampleStatus_t Example_Init(const ExampleConfig_t *config); */

  /**
   * @brief   Performs a periodic update.
   * @param[in] delta_time_ms  Elapsed time in milliseconds.
   * @return  None.
   * @note    Should be called in main loop or RTOS task.
   */
  /* void Example_Update(uint32_t delta_time_ms); */

  /**
   * @}
   */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* BSP_BSP_CORE_H_ */
/* End of File */
