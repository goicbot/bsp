/**
  ******************************************************************************
  * @file           : gpio.c
  * @brief          : Source file for gpio.h module.
  * @details		: Driver for the GPIO (General Purpose Inputs and Outputs)
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

/*******************************************************************************/
/* Includes -------------------------------------------------------------------*/
/*******************************************************************************/

#include <stdio.h>
#include "stm32f4xx.h"
#include "rcc.h"
#include "gpio.h"


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
/* Public Variables ----------------------------------------------------------*/
/*******************************************************************************/
GpioConfig_t gpio[GPIO_PORT_MAX][GPIO_PIN_MAX];

/*******************************************************************************/
/* Private Function Prototypes ------------------------------------------------*/
/*******************************************************************************/
static BspReturn_t xPORT_CHECK_ADDRS_IN_RANGE(GPIO_TypeDef *);
static BspReturn_t xPORT_AFR(GpioPinLabel_t , GpioPortLabel_t, GpioAltFunc_t);
static BspReturn_t xPORT_BSRR(GpioPinLabel_t ,GpioPortLabel_t , GpioState_t);
#ifdef GPIO_ODR_FUNC
static BspReturn_t xGpio_ODR(GpioPinLabel_t ,GpioPortLabel_t  , GpioState_t );
#endif
static BspReturn_t xGpio_IDR(GpioPinLabel_t ,GpioPortLabel_t  , GpioState_t *);
static BspReturn_t xGpio_PUPDR(GpioPinLabel_t ,GpioPortLabel_t , GpioPupdr_t);
static BspReturn_t xGpio_OSPEEDR(GpioPinLabel_t ,GpioPortLabel_t , GpioOutputSpeed_t);
static BspReturn_t xGpio_OTYPER(GpioPinLabel_t ,GpioPortLabel_t , GpioOutputType_t);
static BspReturn_t xGpio_MODE(GpioPinLabel_t, GpioPortLabel_t ,GpioPortMode_t);
static GPIO_TypeDef *xGpio_PORTADDRESS(GpioPortLabel_t );
static BspReturn_t xGpio_ISOPEN(GpioPortLabel_t );
static void vGpio_INIT_CONFIG();
BspReturn_t xGpio_LCKR(GpioPortLabel_t);
BspReturn_t xPORT_CONFIG(GpioConfig_t *);
BspReturn_t xGpio_WRITE(GpioConfig_t *, GpioState_t);
BspReturn_t xGpio_READ(GpioConfig_t *, GpioState_t *);
BspReturn_t xGpio_TOGGLE(GpioConfig_t *);
static BspReturn_t xGpio_OPEN(GpioPortLabel_t);
static BspReturn_t xPORT_CLOSE(GpioPortLabel_t);
BspReturn_t xGpio_RESET(GpioPortLabel_t );
BspReturn_t xGpio_INIT();
BspReturn_t xPORT_END();

/*******************************************************************************/
/* Private Function Implementations -------------------------------------------*/
/*******************************************************************************/

/**
  * @brief   Checks the pointer address .
  * @param[in] GPIOx pointer address (@see GPIO_TypeDef)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xPORT_CHECK_ADDRS_IN_RANGE(GPIO_TypeDef *gpio)
{
	uintptr_t addrs = (uintptr_t) gpio;
	if(gpio == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	else if(addrs <= GPIOH_BASE && addrs >= GPIOA_BASE)
	{
		return BSP_RETURN_OK;
	}
	return BSP_RETURN_ERROR_GPIO;
}

/**
  * @brief   Retrieves the pointer address corresponding to the GPIOx register.
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  GPIOx pointer address (@see GPIO_TypeDef)
  * @note    Private function
  */
static GPIO_TypeDef *xGpio_PORTADDRESS(GpioPortLabel_t port)
{
	switch (port)
		{
			case PORT_A: return GPIOA;
			case PORT_B: return GPIOB;
			case PORT_C: return GPIOC;
			case PORT_D: return GPIOD;
			case PORT_E: return GPIOE;
			case PORT_H: return GPIOH;
			default: return NULL;
		}

}

/**
  * @brief   Sets the MODER register
  * @details possible modes are: Input, Output, Alternate function, or Analog mode.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] mode  Mode label (@see GpioPortMode_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_MODE(GpioPinLabel_t pin, GpioPortLabel_t port ,GpioPortMode_t mode)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_MODE_ENUM_CTRL(mode))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->MODER,( 0x3UL << 2UL*pin),((uint32_t) mode << 2UL*pin));

	return BSP_RETURN_OK;
}

/**
  * @brief   Sets the MODER register
  * @details Possible modes are: Input, Output, Alternate function, or Analog mode.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] mode  Mode label (@see GpioPortMode_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_OTYPER(GpioPinLabel_t pin,GpioPortLabel_t port , GpioOutputType_t type)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_OUTTYPE_ENUM_CTRL(type))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->OTYPER,(0x1UL << pin),((uint32_t) type << pin));

	return BSP_RETURN_OK;
}

/**
  * @brief   Sets the OSPEEDR register
  * @details Possible speeds are: Low, Medium, High, or Very high.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] speed  speed type (@see GpioOutputSpeed_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_OSPEEDR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioOutputSpeed_t speed)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_SPEED_ENUM_CTRL(speed))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->OSPEEDR,(0x3UL << 2U*pin),((uint32_t) speed << 2U*pin));

	return BSP_RETURN_OK;
}

/**
  * @brief   Sets the PUPDR register
  * @details Possible configurations are: Pull Up, or Pull Down.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] pupdr  Type (@see GpioPupdr_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_PUPDR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioPupdr_t pupdr)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_PUPDR_ENUM_CTRL(pupdr))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->PUPDR,(0x3UL << 2U*pin),((uint32_t) pupdr << 2U*pin));

	return BSP_RETURN_OK;
}

/**
  * @brief   Reads the IDR register
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] *p_getState  Pointer to variable holding the current (pin,port) state value (@see GpioState_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_IDR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t *p_getState)
{
	if(GPIO_PIN_ENUM_CTRL(pin))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Read port pin value*/
	*p_getState = (GpioState_t) (READ_BIT(p_GPIOx->IDR, 0x1UL << pin) >> pin);

	return BSP_RETURN_OK;
}

#ifdef GPIO_ODR_FUNC
/**
  * @brief   Sets the ODR register
  * @details This function is hidden since is not used. For atomic set/reset (pin,port) GPIO state @ref xPORT_BSRR
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] setState  Current (pin,port) value to be written (@see GpioState_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_ODR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t setState)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_STATE_ENUM_CTRL(setState))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}


	MODIFY_REG(p_GPIOx->ODR,(0x1UL << pin),((uint32_t)setState << pin));

	return BSP_RETURN_OK;
}
#endif

/**
  * @brief   Sets the BSRR register
  * @details Possible configurations are: Set ( bits [0:15]), or reset (bits [16:31])
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] setState  Current (pin,port) value to be written (@see GpioState_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xPORT_BSRR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t setState)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_STATE_ENUM_CTRL(setState))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(setState == PORT_HIGH)
	{
		WRITE_REG(p_GPIOx->BSRR, (0x1UL << pin));
	}
	else
	{
		WRITE_REG(p_GPIOx->BSRR, (0x1UL << (pin + 16)));
	}

	return BSP_RETURN_OK;
}

/**
  * @brief   Sets the AFR register
  * @details Possible alternate functions configurations are: AF1, ... , AF15
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] altFunc  Alternate functions (@see GpioAltFunc_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xPORT_AFR(GpioPinLabel_t pin, GpioPortLabel_t port, GpioAltFunc_t altFunc)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || PORT_AF_ENUM_CTRL(altFunc))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(pin < PIN_8)
	{
		MODIFY_REG(p_GPIOx->AFR[0],(0xFUL << 4UL*pin),((uint32_t) altFunc << 4UL*pin));
	}
	else
	{
		MODIFY_REG(p_GPIOx->AFR[1],(0xFUL << 4UL*pin),((uint32_t) altFunc << 4UL*pin));
	}

	return BSP_RETURN_OK;
}


/**
  * @brief   Evaluates whether the RCC (@see RCC_TypeDef) for the GPIOx peripheral is enabled or disabled.
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Private function
  */
static BspReturn_t xGpio_ISOPEN(GpioPortLabel_t port)
{
	uint32_t bit;
	switch(port)
	{
		case PORT_A:
		{
			bit = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN);
		}
		break;
		case PORT_B:
		{
			bit = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN);
		}
		break;
		case PORT_C:
		{
			bit = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN);
		}
		break;
		case PORT_D:
		{
			bit = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN);
		}
		break;
		case PORT_E:
		{
			bit = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOEEN);
		}
		break;
		case PORT_H:
		{
			bit = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOHEN);
		}
		break;
		default:
			return BSP_RETURN_ERROR_GPIO;

	}

	if(bit)
		return BSP_RETURN_OK;
	else
		return BSP_RETURN_NOK;
}

/**
  * @brief   Initialization GPIO global variable.
  * @note    Private function
  */
static void vGpio_INIT_CONFIG()
{

	GpioPortLabel_t portIdx;
	GpioPinLabel_t  pinIdx;

	for(portIdx = PORT_A;portIdx < GPIO_PORT_MAX; portIdx++)
	{
		for(pinIdx = PIN_0;pinIdx < GPIO_PIN_MAX;pinIdx++)
		{
			gpio[portIdx][pinIdx].pin = pinIdx;
			gpio[portIdx][pinIdx].port = portIdx;
			gpio[portIdx][pinIdx].mode = GPIO_OUTPUT_MODE;
			gpio[portIdx][pinIdx].type = GPIO_PUSH_PULL;
			gpio[portIdx][pinIdx].speed = PORT_HIGH_SPEED;
			gpio[portIdx][pinIdx].pupdr = GPIO_PULL_UP;
			gpio[portIdx][pinIdx].altFunc = PORT_AF0;
		}
	}
}

/*******************************************************************************/
/* Public Function Implementations --------------------------------------------*/
/*******************************************************************************/

/**
  * @brief   Performs the Lock sequence for the GPIOx port under consideration
  * @details The Lock register must be word accessed (i.e. 32 bit),
  * and the sequence should contain the LCKR[0:15] bits unmodified with:
  * LCKR[16] = "1"	+ LCKR[0:15]
  * LCKR[16] = "0"	+ LCKR[0:15]
  * LCKR[16] = "1"	+ LCKR[0:15]
  * This function must only be used after proper GPIOx configuration.
  * Only after reset, the GPIOx configuration can be modified once is performed the LOCK sequence.
  * Double read instructions should be done to assess the correct LOCK write sequence
  *
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  * @warning This function performs a Lock sequence for the entire set of pins of a port "x"
  */
BspReturn_t xGpio_LCKR(GpioPortLabel_t port)
{
	GPIO_TypeDef *p_GPIOx = xGpio_PORTADDRESS(port);

	if(xPORT_CHECK_ADDRS_IN_RANGE(p_GPIOx ))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*LOCK sequence*/
	WRITE_REG(p_GPIOx->LCKR,0x01FFFFUL);
	WRITE_REG(p_GPIOx->LCKR,0xFFFFUL);
	WRITE_REG(p_GPIOx->LCKR,0x01FFFFUL);

	/*Read the LCKR[16] bit to confirm that the lock is active (Two Times obligatory under ST terms)*/
	volatile uint32_t rControl;
	rControl = READ_BIT(p_GPIOx->LCKR,GPIO_LCKR_LCKK);
	rControl = READ_BIT(p_GPIOx->LCKR,GPIO_LCKR_LCKK);

	if(!rControl)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}

/**
  * @brief   Enabling of the RCC corresponding to the GPIOx peripheral
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
static BspReturn_t xGpio_OPEN(GpioPortLabel_t port)
{
	if(GPIO_PORT_ENUM_CTRL(port))
	{
		return BSP_RETURN_ERROR_GPIO;
	}


	if (xGpio_ISOPEN(port) == BSP_RETURN_NOK)
	{
		switch(port)
		{
			case PORT_A:
			{
				RCC_SET_AHB1ENR(RCC_AHB1ENR_GPIOAEN);
			}
			break;
			case PORT_B:
			{
				RCC_SET_AHB1ENR(RCC_AHB1ENR_GPIOBEN);
			}
			break;
			case PORT_C:
			{
				RCC_SET_AHB1ENR(RCC_AHB1ENR_GPIOCEN);
			}
			break;
			case PORT_D:
			{
				RCC_SET_AHB1ENR(RCC_AHB1ENR_GPIODEN);
			}
			break;
			case PORT_E:
			{
				RCC_SET_AHB1ENR(RCC_AHB1ENR_GPIOEEN);
			}
			break;
			case PORT_H:
			{
				RCC_SET_AHB1ENR(RCC_AHB1ENR_GPIOHEN);
			}
			break;
			default:
				return BSP_RETURN_ERROR_CRC;
		}
	}
	return BSP_RETURN_OK;
}

/**
  * @brief   Disabling of the RCC corresponding to the GPIOx peripheral
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
static BspReturn_t xPORT_CLOSE(GpioPortLabel_t port)
{
	if(GPIO_PORT_ENUM_CTRL(port))
	{
		return BSP_RETURN_ERROR_GPIO;
	}


	if (xGpio_ISOPEN(port) == BSP_RETURN_OK)
	{
		switch(port)
		{
			case PORT_A:
			{
				RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_GPIOAEN);
			}
			break;
			case PORT_B:
			{
				RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_GPIOBEN);
			}
			break;
			case PORT_C:
			{
				RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_GPIOCEN);
			}
			break;
			case PORT_D:
			{
				RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_GPIODEN);
			}
			break;
			case PORT_E:
			{
				RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_GPIOEEN);
			}
			break;
			case PORT_H:
			{
				RCC_CLEAR_AHB1ENR(RCC_AHB1ENR_GPIOHEN);
			}
			break;
			default:
				return BSP_RETURN_ERROR_CRC;
		}
	}
	return BSP_RETURN_OK;
}

/**
  * @brief   Reset of the RCC corresponding to the GPIOx peripheral
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xGpio_RESET(GpioPortLabel_t port)
{
	if(GPIO_PORT_ENUM_CTRL(port))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	switch(port)
	{
		case PORT_A:
		{
			RCC_SET_AHB1ENR(RCC_AHB1RSTR_GPIOARST);
		}
		break;
		case PORT_B:
		{
			RCC_SET_AHB1ENR(RCC_AHB1RSTR_GPIOBRST);
		}
		break;
		case PORT_C:
		{
			RCC_SET_AHB1ENR(RCC_AHB1RSTR_GPIOCRST);
		}
		break;
		case PORT_D:
		{
			RCC_SET_AHB1ENR(RCC_AHB1RSTR_GPIODRST);
		}
		break;
		case PORT_E:
		{
			RCC_SET_AHB1ENR(RCC_AHB1RSTR_GPIOERST);
		}
		break;
		case PORT_H:
		{
			RCC_SET_AHB1ENR(RCC_AHB1RSTR_GPIOHRST);
		}
		break;
		default:
			return BSP_RETURN_ERROR_CRC;
	}

	return BSP_RETURN_OK;
}

/**
  * @brief   Configures the GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xPORT_CONFIG(GpioConfig_t *p_config)
{
	if(xGpio_MODE(p_config->pin,p_config->port, p_config->mode))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xGpio_OTYPER(p_config->pin,p_config->port, p_config->type))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xGpio_OSPEEDR(p_config->pin,p_config->port, p_config->speed))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xGpio_PUPDR(p_config->pin,p_config->port, p_config->pupdr))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xPORT_AFR(p_config->pin,p_config->port, p_config->altFunc))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}

/**
  * @brief   Writes the state of a GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @param[in] state  Current (pin,port) value to be written (@see GpioState_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xGpio_WRITE(GpioConfig_t *p_config, GpioState_t state)
{
	if(xPORT_BSRR(p_config->pin,p_config->port, state))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}

/**
  * @brief   Reads the state of a GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @param[in] p_state  Holds the read value (@see GpioState_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xGpio_READ(GpioConfig_t *p_config, GpioState_t *p_state)
{
	if(xGpio_IDR(p_config->pin,p_config->port, p_state))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}

/**
  * @brief   Toggles the state of a GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xGpio_TOGGLE(GpioConfig_t *p_config)
{
	GpioState_t state;
	if(xGpio_IDR(p_config->pin,p_config->port, &state))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(state == PORT_HIGH)
		return xGpio_WRITE(p_config,GPIO_LOW);
	else
		return xGpio_WRITE(p_config,PORT_HIGH);
}


/**
  * @brief   Initializes all the GPIO ports work
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xGpio_INIT()
{
	BspReturn_t retnVal = BSP_RETURN_OK;
	/* GPIO A driver Open*/
	if(xGpio_OPEN(PORT_A))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO B driver Open*/
	else if(xGpio_OPEN(PORT_B))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO C driver Open*/
	else if(xGpio_OPEN(PORT_C))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO D driver Open*/
	else if(xGpio_OPEN(PORT_D))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO E driver Open*/
	else if(xGpio_OPEN(PORT_E))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO H driver Open*/
	else if(xGpio_OPEN(PORT_H))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	else
	{
		vGpio_INIT_CONFIG();
	}

	return retnVal;
}

/**
  * @brief   Stops all the GPIO ports work
  * @return  Board Support Package error handling (@see BspReturn_t)
  * @note    Public function
  */
BspReturn_t xPORT_END()
{
	BspReturn_t retnVal = BSP_RETURN_OK;
	/* GPIO A driver Close*/
	if(xPORT_CLOSE(PORT_A))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO B driver Close*/
	else if(xPORT_CLOSE(PORT_B))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO C driver Close*/
	else if(xPORT_CLOSE(PORT_C))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO D driver Close*/
	else if(xPORT_CLOSE(PORT_D))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO E driver Close*/
	else if(xPORT_CLOSE(PORT_E))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}
	/* GPIO H driver Close*/
	else if(xPORT_CLOSE(PORT_H))
	{
		retnVal = BSP_RETURN_ERROR_GPIO;
	}

	return retnVal;
}
/* End of File */
