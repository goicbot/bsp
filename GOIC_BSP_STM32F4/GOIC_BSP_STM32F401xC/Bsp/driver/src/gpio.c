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
#include "gpio.h"


/*******************************************************************************/
/* Private Define -------------------------------------------------------------*/
/*******************************************************************************/
/*#define GPIO_ODR_FUNC*/

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

static BspReturn_t xDriverGpio_AFR(GpioPinLabel_t , GpioPortLabel_t, GpioAltFunc_t);
static BspReturn_t xDriverGpio_BSRR(GpioPinLabel_t ,GpioPortLabel_t , GpioState_t);
#ifdef GPIO_ODR_FUNC
static BspReturn_t xDriverGpio_ODR(GpioPinLabel_t ,GpioPortLabel_t  , GpioState_t );
#endif
static BspReturn_t xDriverGpio_IDR(GpioPinLabel_t ,GpioPortLabel_t  , GpioState_t *);
static BspReturn_t xDriverGpio_PUPDR(GpioPinLabel_t ,GpioPortLabel_t , GpioPupdr_t);
static BspReturn_t xDriverGpio_OSPEEDR(GpioPinLabel_t ,GpioPortLabel_t , GpioOutputSpeed_t);
static BspReturn_t xDriverGpio_OTYPER(GpioPinLabel_t ,GpioPortLabel_t , GpioOutputType_t);
static BspReturn_t xDriverGpio_MODE(GpioPinLabel_t, GpioPortLabel_t ,GpioPortMode_t);
static GPIO_TypeDef *xDriverGpio_PORTADDRESS(GpioPortLabel_t );
static BspReturn_t xGpio_ISOPEN(GpioPortLabel_t );
BspReturn_t xGpio_LCKR(uint32_t,GpioPortLabel_t);
BspReturn_t xGpio_CONFIG(GpioConfig_t *);
BspReturn_t xGpio_WRITE(GpioConfig_t *, GpioState_t);
BspReturn_t xGpio_READ(GpioConfig_t *, GpioState_t *);
static BspReturn_t xGpio_OPEN(GpioPortLabel_t);
static BspReturn_t xGpio_CLOSE(GpioPortLabel_t);
BspReturn_t xGpio_RESET(GpioPortLabel_t );
void xGpio_INIT();
void xGpio_END();

/*******************************************************************************/
/* Private Function Implementations -------------------------------------------*/
/*******************************************************************************/


static GPIO_TypeDef *xDriverGpio_PORTADDRESS(GpioPortLabel_t port)
{
	switch (port)
		{
			case GPIO_A: return GPIOA;
			case GPIO_B: return GPIOB;
			case GPIO_C: return GPIOC;
			case GPIO_D: return GPIOD;
			case GPIO_E: return GPIOE;
			case GPIO_H: return GPIOH;
			default: return NULL;
		}

}


static BspReturn_t xDriverGpio_MODE(GpioPinLabel_t pin, GpioPortLabel_t port ,GpioPortMode_t mode)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_MODE_ENUM_CTRL(mode))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Clear masked register*/
	p_GPIOx->MODER &=  ~( 0x3UL << 2UL*pin) ;
	/*Set masked register */
	p_GPIOx->MODER |= ((uint32_t) mode << 2UL*pin) ;

	return BSP_RETURN_OK;
}


static BspReturn_t xDriverGpio_OTYPER(GpioPinLabel_t pin,GpioPortLabel_t port , GpioOutputType_t type)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_OUTTYPE_ENUM_CTRL(type))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Clear masked register*/
	p_GPIOx->OTYPER &=  ~( 0x1UL << pin) ;
	/*Set masked register */
	p_GPIOx->OTYPER |=  ((uint32_t) type << pin) ;

	return BSP_RETURN_OK;
}


static BspReturn_t xDriverGpio_OSPEEDR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioOutputSpeed_t speed)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_SPEED_ENUM_CTRL(speed))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Clear masked register*/
	p_GPIOx->OSPEEDR &= ~( 0x3UL << 2U*pin) ;
	/*Set masked register */
	p_GPIOx->OSPEEDR |= ((uint32_t) speed << 2U*pin) ;

	return BSP_RETURN_OK;
}


static BspReturn_t xDriverGpio_PUPDR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioPupdr_t pupdr)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_PUPDR_ENUM_CTRL(pupdr))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Clear masked register*/
	p_GPIOx->PUPDR &= ~( 0x3UL << 2U*pin) ;
	/*Set masked register */
	p_GPIOx->PUPDR |= ((uint32_t) pupdr << 2U*pin);

	return BSP_RETURN_OK;
}


static BspReturn_t xDriverGpio_IDR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t *getState)
{
	if(GPIO_PIN_ENUM_CTRL(pin))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Read port pin value*/
	*getState = (GpioState_t) ((p_GPIOx->IDR >> pin) & 0x1UL);

	return BSP_RETURN_OK;
}

#ifdef GPIO_ODR_FUNC
static BspReturn_t xDriverGpio_ODR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t setState)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_STATE_ENUM_CTRL(setState))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Clear masked register*/
	p_GPIOx->ODR &= (uint32_t) ~( 0x1UL << pin) ;
	/*Write port pin value*/
	p_GPIOx->ODR |= (uint32_t) (setState << pin);

	return BSP_RETURN_OK;
}
#endif

static BspReturn_t xDriverGpio_BSRR(GpioPinLabel_t pin,GpioPortLabel_t port , GpioState_t setState)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_STATE_ENUM_CTRL(setState))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(setState == GPIO_HIGH)
	{
		p_GPIOx->BSRR =  (0x1UL << pin);
	}
	else
	{
		p_GPIOx->BSRR =  (0x1UL << (pin + 16));
	}

	return BSP_RETURN_OK;
}


static BspReturn_t xDriverGpio_AFR(GpioPinLabel_t pin, GpioPortLabel_t port, GpioAltFunc_t altFunc)
{
	if(GPIO_PIN_ENUM_CTRL(pin) || GPIO_AF_ENUM_CTRL(altFunc))
	{
		return BSP_RETURN_ERROR_GPIO;
	}
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(pin < GPIO_PIN_8)
	{
		p_GPIOx->AFR[0] &= ~(0xF << 4UL*pin);
		p_GPIOx->AFR[0] |= ((uint32_t) altFunc << 4UL*pin);
	}
	else
	{
		p_GPIOx->AFR[1] &= ~(0xFUL << 4UL*pin);
		p_GPIOx->AFR[1] |= ((uint32_t) altFunc << 4UL*pin);
	}

	return BSP_RETURN_OK;
}

/**
 * @brief Verifies whether the clock control for the CRC module is enabled
 * @return BSP return result
 */

static BspReturn_t xGpio_ISOPEN(GpioPortLabel_t port)
{
	uint8_t bit;
	switch(port)
	{
		case GPIO_A:
		{
			bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN) >> RCC_AHB1ENR_GPIOAEN_Pos);
		}
		break;
		case GPIO_B:
		{
			bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN) >> RCC_AHB1ENR_GPIOBEN_Pos);
		}
		break;
		case GPIO_C:
		{
			bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN) >> RCC_AHB1ENR_GPIOCEN_Pos);
		}
		break;
		case GPIO_D:
		{
			bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_GPIODEN) >> RCC_AHB1ENR_GPIODEN_Pos);
		}
		break;
		case GPIO_E:
		{
			bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_GPIOEEN) >> RCC_AHB1ENR_GPIOEEN_Pos);
		}
		break;
		case GPIO_H:
		{
			bit = (uint8_t)((RCC->AHB1ENR & RCC_AHB1ENR_GPIOHEN) >> RCC_AHB1ENR_GPIOHEN_Pos);
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

/*******************************************************************************/
/* Public Function Implementations --------------------------------------------*/
/*******************************************************************************/

BspReturn_t xGpio_LCKR(uint32_t lck,GpioPortLabel_t port)
{
	GPIO_TypeDef *p_GPIOx = xDriverGpio_PORTADDRESS(port);

	if(p_GPIOx == NULL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	/*Clear masked register*/
	p_GPIOx->LCKR &= ~(0x1FFFF);
	/*LOCK sequence*/
	p_GPIOx->LCKR |= (0x1UL << 16) | (lck & 0xFFFFUL);
	p_GPIOx->LCKR &= ~(0x1UL << 16) | (lck & 0xFFFFUL);
	p_GPIOx->LCKR |= ~(0x1UL << 16) | (lck & 0xFFFFUL);

	/*Read the LCKR[16] bit to confirm that the lock is active */
	uint32_t rControl = (p_GPIOx->LCKR >> 16) & 0x1UL;

	if(rControl != 0x1UL)
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}


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
			case GPIO_A:
			{
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			}
			break;
			case GPIO_B:
			{
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
			}
			break;
			case GPIO_C:
			{
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			}
			break;
			case GPIO_D:
			{
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
			}
			break;
			case GPIO_E:
			{
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
			}
			break;
			case GPIO_H:
			{
				RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
			}
			break;
			default:
				return BSP_RETURN_ERROR_CRC;
		}
	}
	return BSP_RETURN_OK;
}

static BspReturn_t xGpio_CLOSE(GpioPortLabel_t port)
{
	if(GPIO_PORT_ENUM_CTRL(port))
	{
		return BSP_RETURN_ERROR_GPIO;
	}


	if (xGpio_ISOPEN(port) == BSP_RETURN_OK)
	{
		switch(port)
		{
			case GPIO_A:
			{
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
			}
			break;
			case GPIO_B:
			{
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
			}
			break;
			case GPIO_C:
			{
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
			}
			break;
			case GPIO_D:
			{
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
			}
			break;
			case GPIO_E:
			{
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
			}
			break;
			case GPIO_H:
			{
				RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
			}
			break;
			default:
				return BSP_RETURN_ERROR_CRC;
		}
	}
	return BSP_RETURN_OK;
}

BspReturn_t xGpio_RESET(GpioPortLabel_t port)
{
	if(GPIO_PORT_ENUM_CTRL(port))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	switch(port)
	{
		case GPIO_A:
		{
			RCC->AHB1ENR |= ~RCC_AHB1RSTR_GPIOARST;
		}
		break;
		case GPIO_B:
		{
			RCC->AHB1ENR |= ~RCC_AHB1RSTR_GPIOBRST;
		}
		break;
		case GPIO_C:
		{
			RCC->AHB1ENR |= ~RCC_AHB1RSTR_GPIOCRST;
		}
		break;
		case GPIO_D:
		{
			RCC->AHB1ENR |= ~RCC_AHB1RSTR_GPIODRST;
		}
		break;
		case GPIO_E:
		{
			RCC->AHB1ENR |= ~RCC_AHB1RSTR_GPIOERST;
		}
		break;
		case GPIO_H:
		{
			RCC->AHB1ENR |= ~RCC_AHB1RSTR_GPIOHRST;
		}
		break;
		default:
			return BSP_RETURN_ERROR_CRC;
	}

	return BSP_RETURN_OK;
}

BspReturn_t xGpio_CONFIG(GpioConfig_t *config)
{
	if(xDriverGpio_MODE(config->pin,config->port, config->mode))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xDriverGpio_OTYPER(config->pin,config->port, config->type))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xDriverGpio_OSPEEDR(config->pin,config->port, config->speed))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xDriverGpio_PUPDR(config->pin,config->port, config->pupdr))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	if(xDriverGpio_AFR(config->pin,config->port, config->altFunc))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}

BspReturn_t xGpio_WRITE(GpioConfig_t *config, GpioState_t state)
{
	if(xDriverGpio_BSRR(config->pin,config->port, state))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}


BspReturn_t xGpio_READ(GpioConfig_t *config, GpioState_t *state)
{
	if(xDriverGpio_IDR(config->pin,config->port, state))
	{
		return BSP_RETURN_ERROR_GPIO;
	}

	return BSP_RETURN_OK;
}

void xGpio_INIT()
{
	/* GPIO A driver Open*/						xGpio_OPEN(GPIO_A);
	/* GPIO B driver Open*/						xGpio_OPEN(GPIO_B);
	/* GPIO C driver Open*/						xGpio_OPEN(GPIO_C);
	/* GPIO D driver Open*/						xGpio_OPEN(GPIO_D);
	/* GPIO E driver Open*/						xGpio_OPEN(GPIO_E);
	/* GPIO H driver Open*/						xGpio_OPEN(GPIO_H);
}

void xGpio_END()
{
	/* GPIO A driver Close*/					xGpio_CLOSE(GPIO_A);
	/* GPIO B driver Close*/					xGpio_CLOSE(GPIO_B);
	/* GPIO C driver Close*/					xGpio_CLOSE(GPIO_C);
	/* GPIO D driver Close*/					xGpio_CLOSE(GPIO_D);
	/* GPIO E driver Close*/					xGpio_CLOSE(GPIO_E);
	/* GPIO H driver Close*/					xGpio_CLOSE(GPIO_H);
}
/**
  * @brief   Initializes the module.
  * @details Configures internal state and prepares the driver.
  * @param[in] config  Pointer to configuration structure.
  * @return  Operation status.
  * @pre     Must be called before Example_Update().
  * @note    Thread-safe if called only during initialization phase.
  */
/*
ExampleStatus_t Example_Init(const ExampleConfig_t *config)
{
    Example_ResetContext();
    (void)config; // suppress unused warning
    return EXAMPLE_OK;
}
*/

/**
  * @brief   Periodic update handler.
  * @details Called periodically to refresh internal state.
  * @param[in] delta_time_ms  Elapsed time since last call.
  * @return  None.
  * @note    Should be called in main loop or from scheduler.
  */
/*
void Example_Update(uint32_t delta_time_ms)
{
    (void)delta_time_ms;
    if (example_state == STATE_IDLE)
    {
        example_state = STATE_BUSY;
    }
}
*/

/* End of File */
