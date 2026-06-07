/**
  ******************************************************************************
  * @file           : gpio.h
  * @brief          : Header for gpio.c file.
  * @author         : GOIC Embedded Systems
  * @date           : May 18, 2026
  * @version        : 1.0.0
  * @copyright      : Copyright (c) 2026 GOIC Embedded Systems
  ******************************************************************************
  * @attention
  *
  * MIT License
  *
  * Copyright (c) May 18, 2026 GOIC Embedded Systems
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
#ifndef BSP_DRIVER_INC_PORT_H_
#define BSP_DRIVER_INC_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  * @defgroup gpio_Module gpio Module
  * @brief    Public API for gpio driver.
  * @{
  */

/*******************************************************************************/
/* Includes -------------------------------------------------------------------*/
/*******************************************************************************/

#include "bsp_core.h"

/*******************************************************************************/
/* Exported Types -------------------------------------------------------------*/
/*******************************************************************************/

/**
  * @brief Public enumeration representing the port mode
  */
typedef enum{
	GPIO_INPUT_MODE = 0,
	GPIO_OUTPUT_MODE,
	PORT_ALTERNATE_FUNCTION_MODE,
	PORT_ANALOG_MODE,
	GPIO_MAX_MODE,
}GpioPortMode_t;

/*
 * @brief Control of GpioPortMode_t type input into range
 */
static inline uint32_t GPIO_MODE_ENUM_CTRL(GpioPortMode_t mode)
{
	if(mode >= GPIO_MAX_MODE)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
  * @brief Public enumeration representing the port label group
  */
typedef enum{
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_H,
	GPIO_PORT_MAX,
}GpioPortLabel_t;

/*
 * @brief Control of GpioPortLabel_t type input into range
 */
static inline uint32_t GPIO_PORT_ENUM_CTRL(GpioPortLabel_t port)
{
	if(port >= GPIO_PORT_MAX)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
  * @brief Public enumeration representing the pin label
  */
typedef enum{
	PIN_0 = 0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15,
	GPIO_PIN_MAX,
}GpioPinLabel_t;


/*
 * @brief Control of GpioPinLabel_t type input into range
 */
static inline uint32_t GPIO_PIN_ENUM_CTRL(GpioPinLabel_t pin)
{
	if(pin >= GPIO_PIN_MAX)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
  * @brief Public enumeration representing the output type label
  */
typedef enum{
	GPIO_PUSH_PULL = 0,
	GPIO_OPEN_DRAIN,
	GPIO_MAX_OUTPUT_TYPE,
}GpioOutputType_t;


/*
 * @brief Control of GpioOutputType_t type input into range
 */
static inline uint32_t GPIO_OUTTYPE_ENUM_CTRL(GpioOutputType_t outtype)
{
	if(outtype >= GPIO_MAX_OUTPUT_TYPE)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
 * @brief Public enumeration representing the I/O output speed
 */
typedef enum{
	GPIO_LOW_SPEED = 0,
	GPIO_MEDIUM_SPEED,
	PORT_HIGH_SPEED,
	GPIO_VERY_HIGH_SPEED,
	GPIO_OUTPUT_SPEED_MAX,
}GpioOutputSpeed_t;


/*
 * @brief Control of GpioOutputSpeed_t type input into range
 */
static inline uint32_t GPIO_SPEED_ENUM_CTRL(GpioOutputSpeed_t speed)
{
	if(speed >= GPIO_OUTPUT_SPEED_MAX)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
 * @brief Public enumeration representing the Pull-Up/Pull-Down
 */
typedef enum{
	GPIO_NO_PUPDR = 0,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
	GPIO_PUPDR_MAX,
}GpioPupdr_t;


/*
 * @brief Control of GpioPupdr_t type input into range
 */
static inline uint32_t GPIO_PUPDR_ENUM_CTRL(GpioPupdr_t pudpr)
{
	if(pudpr >= GPIO_PUPDR_MAX )
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
 * @brief Public enumeration representing the GPIO state
 */
typedef enum{
	GPIO_LOW = 0,
	PORT_HIGH,
	GPIO_STATE_MAX,
}GpioState_t;


/*
 * @brief Control of GpioState_t type input into range
 */
static inline uint32_t GPIO_STATE_ENUM_CTRL(GpioState_t state)
{
	if(state >= GPIO_STATE_MAX)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/**
 * @brief Public enumeration representing the GPIO alternate functions
 */
typedef enum{
	PORT_AF0 = 0,
	PORT_AF1,
	PORT_AF2,
	PORT_AF3,
	PORT_AF4,
	PORT_AF5,
	PORT_AF6,
	PORT_AF7,
	PORT_AF8,
	PORT_AF9,
	PORT_AF10,
	PORT_AF11,
	PORT_AF12,
	PORT_AF13,
	PORT_AF14,
	PORT_AF15,
	PORT_AF_MAX,
}GpioAltFunc_t;


/*
 * @brief Control of GpioAltFunc_t type input into range
 */
static inline uint32_t PORT_AF_ENUM_CTRL(GpioAltFunc_t af)
{
	if(af >= PORT_AF_MAX)
	{
		return 0x01UL;
	}
	return 0x00UL;
}

/*
 * @brief This structure contains the basic GPIOx configuration for a certain pin
 */
typedef struct{
	GpioPinLabel_t		pin;
	GpioPortLabel_t		port;
	GpioPortMode_t		mode;
	GpioOutputType_t 	type;
	GpioOutputSpeed_t 	speed;
	GpioPupdr_t			pupdr;
	GpioAltFunc_t		altFunc;

}GpioConfig_t;


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
extern GpioConfig_t gpio[GPIO_PORT_MAX][GPIO_PIN_MAX];

/*******************************************************************************/
/* Exported Functions ---------------------------------------------------------*/
/*******************************************************************************/

extern BspReturn_t xGpio_LCKR(GpioPortLabel_t);
extern BspReturn_t xPORT_CONFIG(GpioConfig_t *);
extern BspReturn_t xGpio_WRITE(GpioConfig_t *, GpioState_t);
extern BspReturn_t xGpio_READ(GpioConfig_t *, GpioState_t *);
extern BspReturn_t xGpio_RESET(GpioPortLabel_t);
extern BspReturn_t xGpio_TOGGLE(GpioConfig_t *);
extern BspReturn_t xGpio_INIT();
extern BspReturn_t xPORT_END();
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* BSP_DRIVER_INC_PORT_H_ */
/* End of File */
