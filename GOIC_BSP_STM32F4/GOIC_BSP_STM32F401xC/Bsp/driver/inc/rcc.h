/**
  ******************************************************************************
  * @file           : rcc.h
  * @brief          : Header for rcc.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_DRIVER_INC_RCC_H_
#define BSP_DRIVER_INC_RCC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  * @defgroup rcc_Module rcc Module
  * @brief    Public API for rcc driver.
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
/* #define EXAMPLE_DEFAULT_FREQUENCY   (1000U) */ /**< Default frequency in Hz */

/*******************************************************************************/
/* Exported Macros ------------------------------------------------------------*/
/*******************************************************************************/

/* ***************** RCC clock control register ************************/
#define RCC_CLEAR_CR(BIT) 						CLEAR_BIT(RCC->CR,BIT)
#define RCC_SET_CR(BIT) 						SET_BIT(RCC->CR,BIT)
#define RCC_READ_CR(BIT) 						READ_BIT(RCC->CR,BIT)
#define RCC_WRITE_CR(VAL) 						WRITE_REG(RCC->CR,VAL)
#define RCC_MODIFY_CR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->CR,SETMASK,SETMASK)
/* ***************** RCC PLL configuration register ************************/
#define RCC_CLEAR_PLLCFGR(BIT) 					CLEAR_BIT(RCC->PLLCFGR,BIT)
#define RCC_SET_PLLCFGR(BIT) 					SET_BIT(RCC->PLLCFGR,BIT)
#define RCC_READ_PLLCFGR(BIT) 					READ_BIT(RCC->PLLCFGR,BIT)
#define RCC_WRITE_PLLCFGR(VAL) 					WRITE_REG(RCC->PLLCFGR,VAL)
#define RCC_MODIFY_PLLCFGR(CLEARMASK, SETMASK)	MODIFY_REG(RCC->PLLCFGR,SETMASK,SETMASK)
/* ***************** RCC clock configuration register ************************/
#define RCC_CLEAR_CFGR(BIT) 					CLEAR_BIT(RCC->CFGR,BIT)
#define RCC_SET_CFGR(BIT) 						SET_BIT(RCC->CFGR,BIT)
#define RCC_READ_CFGR(BIT) 						READ_BIT(RCC->CFGR,BIT)
#define RCC_WRITE_CFGR(VAL) 					WRITE_REG(RCC->CFGR,VAL)
#define RCC_MODIFY_CFRG(CLEARMASK, SETMASK)		MODIFY_REG(RCC->CFGR,SETMASK,SETMASK)
/* ***************** RCC clock interrupt register ************************/
#define RCC_CLEAR_CIR(BIT) 						CLEAR_BIT(RCC->CIR,BIT)
#define RCC_SET_CIR(BIT) 						SET_BIT(RCC->CIR,BIT)
#define RCC_READ_CIR(BIT) 						READ_BIT(RCC->CIR,BIT)
#define RCC_WRITE_CIR(VAL) 						WRITE_REG(RCC->CIR,VAL)
#define RCC_MODIFY_CIR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->CIR,SETMASK,SETMASK)
/* ***************** RCC AHB1 peripheral reset register ************************/
#define RCC_CLEAR_AHB1RSTR(BIT) 					CLEAR_BIT(RCC->AHB1RSTR,BIT)
#define RCC_SET_AHB1RSTR(BIT) 						SET_BIT(RCC->AHB1RSTR,BIT)
#define RCC_READ_AHB1RSTR(BIT) 						READ_BIT(RCC->AHB1RSTR,BIT)
#define RCC_WRITE_AHB1RSTR(VAL) 					WRITE_REG(RCC->AHB1RSTR,VAL)
#define RCC_MODIFY_AHB1RSTR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->AHB1RSTR,SETMASK,SETMASK)
/* ***************** RCC AHB2 peripheral reset register ************************/
#define RCC_CLEAR_AHB2RSTR(BIT) 					CLEAR_BIT(RCC->AHB2RSTR,BIT)
#define RCC_SET_AHB2RSTR(BIT) 						SET_BIT(RCC->AHB2RSTR,BIT)
#define RCC_READ_AHB2RSTR(BIT) 						READ_BIT(RCC->AHB2RSTR,BIT)
#define RCC_WRITE_AHB2RSTR(VAL) 					WRITE_REG(RCC->AHB2RSTR,VAL)
#define RCC_MODIFY_AHB2RSTR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->AHB2RSTR,SETMASK,SETMASK)
/* ***************** RCC APB1 peripheral reset register ************************/
#define RCC_CLEAR_APB1RSTR(BIT) 					CLEAR_BIT(RCC->APB1RSTR,BIT)
#define RCC_SET_APB1RSTR(BIT) 						SET_BIT(RCC->APB1RSTR,BIT)
#define RCC_READ_APB1RSTR(BIT) 						READ_BIT(RCC->APB1RSTR,BIT)
#define RCC_WRITE_APB1RSTR(VAL) 					WRITE_REG(RCC->APB1RSTR,VAL)
#define RCC_MODIFY_APB1RSTR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->APB1RSTR,SETMASK,SETMASK)
/* ***************** RCC APB2 peripheral reset register ************************/
#define RCC_CLEAR_APB2RSTR(BIT) 					CLEAR_BIT(RCC->APB2RSTR,BIT)
#define RCC_SET_APB2RSTR(BIT) 						SET_BIT(RCC->APB2RSTR,BIT)
#define RCC_READ_APB2RSTR(BIT) 						READ_BIT(RCC->APB2RSTR,BIT)
#define RCC_WRITE_APB2RSTR(VAL) 					WRITE_REG(RCC->APB2RSTR,VAL)
#define RCC_MODIFY_APB2RSTR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->APB2RSTR,SETMASK,SETMASK)
/* ***************** RCC AHB1 peripheral clock register ************************/
#define RCC_CLEAR_AHB1ENR(BIT) 						CLEAR_BIT(RCC->AHB1ENR,BIT)
#define RCC_SET_AHB1ENR(BIT) 						SET_BIT(RCC->AHB1ENR,BIT)
#define RCC_READ_AHB1ENR(BIT) 						READ_BIT(RCC->AHB1ENR,BIT)
#define RCC_WRITE_AHB1ENR(VAL) 						WRITE_REG(RCC->AHB1ENR,VAL)
#define RCC_MODIFY_AHB1ENR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->AHB1ENR,SETMASK,SETMASK)
/* ***************** RCC AHB2 peripheral clock register ************************/
#define RCC_CLEAR_AHB2ENR(BIT) 						CLEAR_BIT(RCC->AHB2ENR,BIT)
#define RCC_SET_AHB2ENR(BIT) 						SET_BIT(RCC->AHB2ENR,BIT)
#define RCC_READ_AHB2ENR(BIT) 						READ_BIT(RCC->AHB2ENR,BIT)
#define RCC_WRITE_AHB2ENR(VAL) 						WRITE_REG(RCC->AHB2ENR,VAL)
#define RCC_MODIFY_AHB2ENR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->AHB2ENR,SETMASK,SETMASK)
/* ***************** RCC APB1 peripheral clock enable register ************************/
#define RCC_CLEAR_APB1ENR(BIT) 						CLEAR_BIT(RCC->APB1ENR,BIT)
#define RCC_SET_APB1ENR(BIT) 						SET_BIT(RCC->APB1ENR,BIT)
#define RCC_READ_APB1ENR(BIT) 						READ_BIT(RCC->APB1ENR,BIT)
#define RCC_WRITE_APB1ENR(VAL) 						WRITE_REG(RCC->APB1ENR,VAL)
#define RCC_MODIFY_APB1ENR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->APB1ENR,SETMASK,SETMASK)
/* ***************** RCC APB2 peripheral clock enable register ************************/
#define RCC_CLEAR_APB2ENR(BIT) 						CLEAR_BIT(RCC->APB2ENR,BIT)
#define RCC_SET_APB2ENR(BIT) 						SET_BIT(RCC->APB2ENR,BIT)
#define RCC_READ_APB2ENR(BIT) 						READ_BIT(RCC->APB2ENR,BIT)
#define RCC_WRITE_APB2ENR(VAL) 						WRITE_REG(RCC->APB2ENR,VAL)
#define RCC_MODIFY_APB2ENR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->APB2ENR,SETMASK,SETMASK)
/* ***************** RCC AHB1 peripheral clock enable in low power mode register ************************/
#define RCC_CLEAR_AHB1LPENR(BIT) 					CLEAR_BIT(RCC->AHB1LPENR,BIT)
#define RCC_SET_AHB1LPENR(BIT) 						SET_BIT(RCC->AHB1LPENR,BIT)
#define RCC_READ_AHB1LPENR(BIT) 					READ_BIT(RCC->AHB1LPENR,BIT)
#define RCC_WRITE_AHB1LPENR(VAL) 					WRITE_REG(RCC->AHB1LPENR,VAL)
#define RCC_MODIFY_AHB1LPENR(CLEARMASK, SETMASK)	MODIFY_REG(RCC->AHB1LPENR,SETMASK,SETMASK)
/* ***************** RCC AHB2 peripheral clock enable in low power mode register ************************/
#define RCC_CLEAR_AHB2LPENR(BIT) 					CLEAR_BIT(RCC->AHB2LPENR,BIT)
#define RCC_SET_AHB2LPENR(BIT) 						SET_BIT(RCC->AHB2LPENR,BIT)
#define RCC_READ_AHB2LPENR(BIT) 					READ_BIT(RCC->AHB2LPENR,BIT)
#define RCC_WRITE_AHB2LPENR(VAL) 					WRITE_REG(RCC->AHB2LPENR,VAL)
#define RCC_MODIFY_AHB2LPENR(CLEARMASK, SETMASK)	MODIFY_REG(RCC->AHB2LPENR,SETMASK,SETMASK)
/* ***************** RCC APB1 peripheral clock enable in low power mode register ************************/
#define RCC_CLEAR_APB1LPENR(BIT) 					CLEAR_BIT(RCC->APB1LPENR,BIT)
#define RCC_SET_APB1LPENR(BIT) 						SET_BIT(RCC->APB1LPENR,BIT)
#define RCC_READ_APB1LPENR(BIT) 					READ_BIT(RCC->APB1LPENR,BIT)
#define RCC_WRITE_APB1LPENR(VAL) 					WRITE_REG(RCC->APB1LPENR,VAL)
#define RCC_MODIFY_APB1LPENR(CLEARMASK, SETMASK)	MODIFY_REG(RCC->APB1LPENR,SETMASK,SETMASK)
/* ***************** RCC APB2 peripheral clock enable in low power mode register ************************/
#define RCC_CLEAR_APB2LPENR(BIT) 					CLEAR_BIT(RCC->APB2LPENR,BIT)
#define RCC_SET_APB2LPENR(BIT) 						SET_BIT(RCC->APB2LPENR,BIT)
#define RCC_READ_APB2LPENR(BIT) 					READ_BIT(RCC->APB2LPENR,BIT)
#define RCC_WRITE_APB2LPENR(VAL) 					WRITE_REG(RCC->APB2LPENR,VAL)
#define RCC_MODIFY_APB2LPENR(CLEARMASK, SETMASK)	MODIFY_REG(RCC->APB2LPENR,SETMASK,SETMASK)
/* ***************** RCC Backup domain control register ************************/
#define RCC_CLEAR_BDCR(BIT) 						CLEAR_BIT(RCC->BDCR,BIT)
#define RCC_SET_BDCR(BIT) 							SET_BIT(RCC->BDCR,BIT)
#define RCC_READ_BDCR(BIT) 							READ_BIT(RCC->BDCR,BIT)
#define RCC_WRITE_BDCR(VAL) 						WRITE_REG(RCC->BDCR,VAL)
#define RCC_MODIFY_BDCR(CLEARMASK, SETMASK)			MODIFY_REG(RCC->BDCR,SETMASK,SETMASK)
/* ***************** RCC clock control & status register ************************/
#define RCC_CLEAR_CSR(BIT) 							CLEAR_BIT(RCC->CSR,BIT)
#define RCC_SET_CSR(BIT) 							SET_BIT(RCC->CSR,BIT)
#define RCC_READ_CSR(BIT) 							READ_BIT(RCC->CSR,BIT)
#define RCC_WRITE_CSR(VAL) 							WRITE_REG(RCC->CSR,VAL)
#define RCC_MODIFY_CSR(CLEARMASK, SETMASK)			MODIFY_REG(RCC->CSR,SETMASK,SETMASK)
/* ***************** RCC spread spectrum clock generation register ************************/
#define RCC_CLEAR_SSCGR(BIT) 						CLEAR_BIT(RCC->SSCGR,BIT)
#define RCC_SET_SSCGR(BIT) 							SET_BIT(RCC->SSCGR,BIT)
#define RCC_READ_SSCGR(BIT) 						READ_BIT(RCC->SSCGR,BIT)
#define RCC_WRITE_SSCGR(VAL) 						WRITE_REG(RCC->SSCGR,VAL)
#define RCC_MODIFY_SSCGR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->SSCGR,SETMASK,SETMASK)
/* ***************** RCC PLLI2S configuration register ************************/
#define RCC_CLEAR_PLLI2SCFGR(BIT) 					CLEAR_BIT(RCC->PLLI2SCFGR,BIT)
#define RCC_SET_PLLI2SCFGR(BIT) 					SET_BIT(RCC->PLLI2SCFGR,BIT)
#define RCC_READ_PLLI2SCFGR(BIT) 					READ_BIT(RCC->PLLI2SCFGR,BIT)
#define RCC_WRITE_PLLI2SCFGR(VAL) 					WRITE_REG(RCC->PLLI2SCFGR,VAL)
#define RCC_MODIFY_PLLI2SCFGR(CLEARMASK, SETMASK)	MODIFY_REG(RCC->PLLI2SCFGR,SETMASK,SETMASK)
/* ***************** RCC Dedicated Clocks configuration register ************************/
#define RCC_CLEAR_DCKCFGR(BIT) 						CLEAR_BIT(RCC->DCKCFGR,BIT)
#define RCC_SET_DCKCFGR(BIT) 						SET_BIT(RCC->DCKCFGR,BIT)
#define RCC_READ_DCKCFGR(BIT) 						READ_BIT(RCC->DCKCFGR,BIT)
#define RCC_WRITE_DCKCFGR(VAL) 						WRITE_REG(RCC->DCKCFGR,VAL)
#define RCC_MODIFY_DCKCFGR(CLEARMASK, SETMASK)		MODIFY_REG(RCC->DCKCFGR,SETMASK,SETMASK)


/*******************************************************************************/
/* Exported Variables ---------------------------------------------------------*/
/*******************************************************************************/
/*--None*/

/*******************************************************************************/
/* Exported Functions ---------------------------------------------------------*/
/*******************************************************************************/

extern void vRcc_INIT();

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* BSP_DRIVER_INC_RCC_H_ */
/* End of File */
