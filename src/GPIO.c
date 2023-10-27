/******************************************************************************
*  File name:		GPIO_program.c
*  Date:			Oct 22, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#include "BIT_MATH.h"
#include "stm32f401xx.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/*******************************************************************************
*                      Private Variables	                                   *
*******************************************************************************/
static GPIO_RegDef_t * GPIO_Astr[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOH};

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
********************************************************************************/
u8 GPIO_u8SetPinMode	(u8 Copy_PortId, u8 Copy_PinId, u8 Copy_PinMode)
{
	u8 u8_error_state = STD_TYPES_OK;

	if((Copy_PortId <= GPIO_u8_GPIOH) && (Copy_PinId <= GPIO_u8_PIN15))
	{
		/* Clear the 2 bits for the mode */
		GPIO_Astr[Copy_PortId]->MODER &= ~(unsigned)(0b11<<(Copy_PinId*2));
		/* Configure the required pin with the specified mode */
		GPIO_Astr[Copy_PortId]->MODER |= (unsigned)((Copy_PinMode & 0b11)<<(Copy_PinId*2));
		switch(Copy_PinMode & 0b11)
		{
			case GPIO_INPUT_BITS:
				/* Configure the input pull up / down / floating */
				GPIO_Astr[Copy_PortId]->PUPDR &= ~(unsigned)(0b11<<(Copy_PinId*2));
				GPIO_Astr[Copy_PortId]->PUPDR |= (unsigned)(((Copy_PinMode>>2) & 0b11)<<(Copy_PinId*2));
				break;
			case GPIO_ANALOG_BITS:
				/* Do Nothing */
				break;
			case GPIO_OUTPUT_BITS:
			case GPIO_ALTERNATE_BITS:
				/* Make the pin high speed */
				GPIO_Astr[Copy_PortId]->OSPEEDR |= (unsigned)(0b10<<(Copy_PinId*2));
				/* Configure the pin to be push pull or open drain */
				GPIO_Astr[Copy_PortId]->OTYPER &= ~(unsigned)(0b01<<Copy_PinId);
				GPIO_Astr[Copy_PortId]->OTYPER |=  (unsigned)(GET_BIT(Copy_PinMode,2)<<Copy_PinId);
				break;
			default:
				u8_error_state = STD_TYPES_NOK;
		}	
		
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
********************************************************************************/
u8 GPIO_u8WritePinValue	(u8 Copy_PortId, u8 Copy_PinId, u8 Copy_u8PinValue)
{
	u8 u8_error_state = STD_TYPES_OK;

	if(Copy_PortId <= GPIO_u8_GPIOH && Copy_PinId <= GPIO_u8_PIN15)
	{
		switch(Copy_u8PinValue)
		{
		case GPIO_u8_HIGH:
			GPIO_Astr[Copy_PortId]->BSRR = (1<<Copy_PinId);
			break;
		case GPIO_u8_LOW:
			GPIO_Astr[Copy_PortId]->BSRR = (1<<(Copy_PinId+16));
			break;
		default:
			u8_error_state = STD_TYPES_NOK;
		}
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
********************************************************************************/
u8 GPIO_u8GetPinValue	(u8 Copy_PortId, u8 Copy_PinId , u8 * Copy_Pu8RetunredPinValue)
{
	u8 u8_error_state = STD_TYPES_OK;

	if(Copy_PortId <= GPIO_u8_GPIOH && Copy_PinId <= GPIO_u8_PIN15)
	{
		*Copy_Pu8RetunredPinValue = GET_BIT(GPIO_Astr[Copy_PortId]->IDR,Copy_PinId);
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		GPIO_u8TogPinValue
********************************************************************************/
u8 GPIO_u8TogPinValue	(u8 Copy_PortId, u8 Copy_PinId)
{
	u8 u8_error_state = STD_TYPES_OK;

	if(Copy_PortId <= GPIO_u8_GPIOE && Copy_PinId <= GPIO_u8_PIN15)
	{
		TOG_BIT(GPIO_Astr[Copy_PortId]->ODR,Copy_PinId);
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

