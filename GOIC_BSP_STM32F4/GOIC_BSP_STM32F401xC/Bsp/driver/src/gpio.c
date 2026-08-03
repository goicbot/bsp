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

/* None---*/

/*******************************************************************************/
/* Private Function Implementations -------------------------------------------*/
/*******************************************************************************/

/**
  * @brief   Checks the pointer address .
  * @param[in] GPIOx pointer address (@see GPIO_TypeDef)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xPortAddssCtrl(GPIO_TypeDef *gpio)
{
	uintptr_t addrs = (uintptr_t) gpio;
	if(gpio == NULL)
	{
		return BSP_ERROR_GPIO;
	}
	else if(addrs <= GPIOH_BASE && addrs >= GPIOA_BASE)
	{
		return BSP_ERROR_OK;
	}
	return BSP_ERROR_GPIO;
}

/**
  * @brief   Retrieves the pointer address corresponding to the GPIOx register.
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  GPIOx pointer address (@see GPIO_TypeDef)
  * @note    Private function
  */
static GPIO_TypeDef *xGetPortAddrss(GpioPortLabel_t port)
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
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioMode(GpioPinLabel_t pin, GpioPortLabel_t port ,GpioPortMode_t mode)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioModeOutRange(mode))
	{
		return BSP_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->MODER,( 0x3UL << 2UL*pin),((uint32_t) mode << 2UL*pin));

	return BSP_ERROR_OK;
}

/**
  * @brief   Sets the MODER register
  * @details Possible modes are: Input, Output, Alternate function, or Analog mode.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] mode  Mode label (@see GpioPortMode_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioOTyper(GpioPinLabel_t pin,GpioPortLabel_t port , GpioOutputType_t type)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioOutTypeOutRange(type))
	{
		return BSP_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->OTYPER,(0x1UL << pin),((uint32_t) type << pin));

	return BSP_ERROR_OK;
}

/**
  * @brief   Sets the OSPEEDR register
  * @details Possible speeds are: Low, Medium, High, or Very high.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] speed  speed type (@see GpioOutputSpeed_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioOSpeedR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioOutputSpeed_t speed)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioSpeedOutRange(speed))
	{
		return BSP_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->OSPEEDR,(0x3UL << 2U*pin),((uint32_t) speed << 2U*pin));

	return BSP_ERROR_OK;
}

/**
  * @brief   Sets the PUPDR register
  * @details Possible configurations are: Pull Up, or Pull Down.
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] pupdr  Type (@see GpioPupdr_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioPuPdr(GpioPinLabel_t pin,GpioPortLabel_t port , GpioPupdr_t pupdr)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioPuPdrOutRange(pupdr))
	{
		return BSP_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	MODIFY_REG(p_GPIOx->PUPDR,(0x3UL << 2U*pin),((uint32_t) pupdr << 2U*pin));

	return BSP_ERROR_OK;
}

/**
  * @brief   Reads the IDR register
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] *p_getState  Pointer to variable holding the current (pin,port) state value (@see GpioState_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioIdr(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t *p_getState)
{
	if(xIsGpioPinOutRange(pin))
	{
		return BSP_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	/*Read port pin value*/
	*p_getState = (GpioState_t) (READ_BIT(p_GPIOx->IDR, 0x1UL << pin) >> pin);

	return BSP_ERROR_OK;
}

#ifdef GPIO_ODR_FUNC
/**
  * @brief   Sets the ODR register
  * @details This function is hidden since is not used. For atomic set/reset (pin,port) GPIO state @ref xGpioBsRr
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] setState  Current (pin,port) value to be written (@see GpioState_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioOdr(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t setState)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioStateOutRange(setState))
	{
		return BSP_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}


	MODIFY_REG(p_GPIOx->ODR,(0x1UL << pin),((uint32_t)setState << pin));

	return BSP_ERROR_OK;
}
#endif

/**
  * @brief   Sets the BSRR register
  * @details Possible configurations are: Set ( bits [0:15]), or reset (bits [16:31])
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] setState  Current (pin,port) value to be written (@see GpioState_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioBsRr(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t setState)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioStateOutRange(setState))
	{
		return BSP_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	if(setState == GPIO_HIGH)
	{
		WRITE_REG(p_GPIOx->BSRR, (0x1UL << pin));
	}
	else
	{
		WRITE_REG(p_GPIOx->BSRR, (0x1UL << (pin + 16)));
	}

	return BSP_ERROR_OK;
}

/**
  * @brief   Sets the AFR register
  * @details Possible alternate functions configurations are: AF1, ... , AF15
  * @param[in] pin   Pin label (@see GpioPinLabel_t)
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @param[in] altFunc  Alternate functions (@see GpioAltFunc_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Private function
  */
static bspError_t xGpioAfr(GpioPinLabel_t pin, GpioPortLabel_t port, GpioAltFunc_t altFunc)
{
	if(xIsGpioPinOutRange(pin) || xIsGpioAltFunOutRange(altFunc))
	{
		return BSP_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
	}

	if(pin < PIN_8)
	{
		MODIFY_REG(p_GPIOx->AFR[0],(0xFUL << 4UL*pin),((uint32_t) altFunc << 4UL*pin));
	}
	else
	{
		MODIFY_REG(p_GPIOx->AFR[1],(0xFUL << 4UL*pin),((uint32_t) altFunc << 4UL*pin));
	}

	return BSP_ERROR_OK;
}


/**
  * @brief   Evaluates whether the RCC (@see RCC_TypeDef) for the GPIOx peripheral is enabled or disabled.
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Boolean False or True (@see bool_t)
  * @note    Private function
  */
static bool_t xIsGpioOpen(GpioPortLabel_t port)
{
	bool_t rtn = FALSE;

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
		break;

	}

	if(!bit)	rtn = TRUE;

	return rtn;
}

/**
  * @brief   Default initialization of the GPIO global variable (@see gpio).
  * @note    Private function
  */
static void vGpioDefaultConfig()
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
			gpio[portIdx][pinIdx].speed = GPIO_HIGH_SPEED;
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
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  * @warning This function performs a Lock sequence for the entire set of pins of a port "x"
  */
bspError_t xGpioLCKR(GpioPortLabel_t port)
{
	GPIO_TypeDef *p_GPIOx = xGetPortAddrss(port);

	if(xPortAddssCtrl(p_GPIOx ))
	{
		return BSP_ERROR_GPIO;
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
		return BSP_ERROR_GPIO;
	}

	return BSP_ERROR_OK;
}

/**
  * @brief   Enabling of the RCC corresponding to the GPIOx peripheral
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
static bspError_t xGpioOpen(GpioPortLabel_t port)
{
	bspError_t err = BSP_ERROR_OK;

	if(!xIsGpioPortOutRange(port))
	{
		if (xIsGpioOpen(port))
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
					err = BSP_ERROR_GPIO;
			}
		}
	}
	else
	{
		err =  BSP_ERROR_GPIO;
	}
	return err;
}

/**
  * @brief   Disabling of the RCC corresponding to the GPIOx peripheral
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
static bspError_t xGpioClose(GpioPortLabel_t port)
{
	if(!xIsGpioPortOutRange(port))
	{
		return BSP_ERROR_GPIO;
	}


	if (xIsGpioOpen(port))
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
				return BSP_ERROR_CRC;
		}
	}
	return BSP_ERROR_OK;
}

/**
  * @brief   Reset of the RCC corresponding to the GPIOx peripheral
  * @param[in] port  Port label (@see GpioPortLabel_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioReset(GpioPortLabel_t port)
{
	if(!xIsGpioPortOutRange(port))
	{
		return BSP_ERROR_GPIO;
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
			return BSP_ERROR_CRC;
	}

	return BSP_ERROR_OK;
}

/**
  * @brief   Configures the GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioSetConfig(GpioConfig_t *p_config)
{
	if(xGpioMode(p_config->pin,p_config->port, p_config->mode))
	{
		return BSP_ERROR_GPIO;
	}

	if(xGpioOTyper(p_config->pin,p_config->port, p_config->type))
	{
		return BSP_ERROR_GPIO;
	}

	if(xGpioOSpeedR(p_config->pin,p_config->port, p_config->speed))
	{
		return BSP_ERROR_GPIO;
	}

	if(xGpioPuPdr(p_config->pin,p_config->port, p_config->pupdr))
	{
		return BSP_ERROR_GPIO;
	}

	if(xGpioAfr(p_config->pin,p_config->port, p_config->altFunc))
	{
		return BSP_ERROR_GPIO;
	}

	return BSP_ERROR_OK;
}

/**
  * @brief   Writes the state of a GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @param[in] state  Current (pin,port) value to be written (@see GpioState_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioWrite(GpioConfig_t *p_config, GpioState_t state)
{
	if(xGpioBsRr(p_config->pin,p_config->port, state))
	{
		return BSP_ERROR_GPIO;
	}

	return BSP_ERROR_OK;
}

/**
  * @brief   Reads the state of a GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @param[in] p_state  Holds the read value (@see GpioState_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioRead(GpioConfig_t *p_config, GpioState_t *p_state)
{
	if(xGpioIdr(p_config->pin,p_config->port, p_state))
	{
		return BSP_ERROR_GPIO;
	}

	return BSP_ERROR_OK;
}

/**
  * @brief   Toggles the state of a GPIOx pin
  * @param[in] p_config  GPIOx pin configuration (@see GpioConfig_t)
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioToggle(GpioConfig_t *p_config)
{
	GpioState_t state;
	if(xGpioIdr(p_config->pin,p_config->port, &state))
	{
		return BSP_ERROR_GPIO;
	}

	if(state == GPIO_HIGH)
		return xGpioWrite(p_config,GPIO_LOW);
	else
		return xGpioWrite(p_config,GPIO_HIGH);
}


/**
  * @brief   Initializes all the GPIO ports work
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioInit()
{
	bspError_t err = BSP_ERROR_OK;

	/* GPIO A driver Open*/
	if(xGpioOpen(PORT_A))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO B driver Open*/
	else if(xGpioOpen(PORT_B))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO C driver Open*/
	else if(xGpioOpen(PORT_C))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO D driver Open*/
	else if(xGpioOpen(PORT_D))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO E driver Open*/
	else if(xGpioOpen(PORT_E))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO H driver Open*/
	else if(xGpioOpen(PORT_H))
	{
		err = BSP_ERROR_GPIO;
	}

	vGpioDefaultConfig();

	return err;
}

/**
  * @brief   Stops all the GPIO ports work
  * @return  Board Support Package error handling (@see bspError_t)
  * @note    Public function
  */
bspError_t xGpioEnd()
{
	bspError_t err = BSP_ERROR_OK;
	/* GPIO A driver Close*/
	if(xGpioClose(PORT_A))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO B driver Close*/
	else if(xGpioClose(PORT_B))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO C driver Close*/
	else if(xGpioClose(PORT_C))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO D driver Close*/
	else if(xGpioClose(PORT_D))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO E driver Close*/
	else if(xGpioClose(PORT_E))
	{
		err = BSP_ERROR_GPIO;
	}
	/* GPIO H driver Close*/
	else if(xGpioClose(PORT_H))
	{
		err = BSP_ERROR_GPIO;
	}

	return err;
}
/* End of File */
