/******************************************************************************
*  File name:		RCC_program.c
*  Date:			Mar 5, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "BIT_MATH.h"
#include "stm32f401xx.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
/*******************************************************************************
* Function Name:		RCC_u8InitSysClk
********************************************************************************/
u8 RCC_u8InitSysClk	(void)
{
	u8 u8_error_state = STD_TYPES_NOK;
	u32 u32_timeout = 0;
	do
	{
	#if (RCC_u8_HSI == RCC_u8_CLK_SYS)
		SET_BIT(RCC->CR,0); /* Internal high-speed clock enable */
		/* wait until HSI RDY flag = 1  or timeout occurs */
		while((GET_BIT(RCC->CR,1) == 0) && (u32_timeout <= MAX_U16))
		{
			u32_timeout++;
		}
		if(u32_timeout < MAX_U16)
		{
			u8_error_state = STD_TYPES_OK;
		}
		else
		{
			u8_error_state = STD_TYPES_NOK;
			break;
		}
		CLR_BIT(RCC->CFGR,0); /* Select HSI as the clock source */
		CLR_BIT(RCC->CFGR,1);
	#elif (RCC_u8_HSE == RCC_u8_CLK_SYS)
		#if(RCC_u8_HSE_NOT_BYPASS == RCC_u8_HSE_TYPE)
		CLR_BIT(RCC->CR,18);
		#elif(RCC_u8_HSE_BYPASS == RCC_u8_HSE_TYPE)
		SET_BIT(RCC->CR,18);
		#else
		#error "Wrong System Clock Configuration"
		#endif
		SET_BIT(RCC->CR,16);
		/* wait until HSI RDY flag = 1  or timeout occurs */
		while((GET_BIT(RCC->CR,17) == 0) && (u32_timeout <= MAX_U16))
		{
			u32_timeout++;
		}
		if(u32_timeout < MAX_U16)
		{
			u8_error_state = STD_TYPES_OK;
		}
		else
		{
			u8_error_state = STD_TYPES_NOK;
			break;
		}
		SET_BIT(RCC->CFGR,0); /* Select HSE as the clock source */
		CLR_BIT(RCC->CFGR,1);
	#elif (RCC_u8_PLL == RCC_u8_CLK_SYS)
		/* Todo Later */
	#else
		#error "Wrong System Clock Configuration"
	#endif
		RCC->CFGR |= ((RCC->CFGR &~ (unsigned)(0b1111<<4))  | (RCC_u8_AHB_PRESCALER << 4  )) ;
		RCC->CFGR |= ((RCC->CFGR &~ (unsigned)(0b111<<10)) | (RCC_u8_APB1_PRESCALER << 10)) ;
		RCC->CFGR |= ((RCC->CFGR &~ (unsigned)(0b111<<13)) | (RCC_u8_APB2_PRESCALER << 13)) ;
	}while(0);
	return u8_error_state;
}

/*******************************************************************************
* Function Name:		RCC_u8GetClkSource
********************************************************************************/
u8 RCC_u8GetClkSource	(u8 *Copy_pu8ClkSource)
{
	u8 u8_error_state = STD_TYPES_OK;
	/* Get the value of the two bits that represent the system clock */
	u8 u8_sys_clk = ((RCC->CFGR & (0b1100))>>2);
	switch(u8_sys_clk)
	{
		case 0:
			*Copy_pu8ClkSource = RCC_u8_HSI;
			break;
		case 1:
			*Copy_pu8ClkSource = RCC_u8_HSE;
			break;
		case 2:
			*Copy_pu8ClkSource = RCC_u8_PLL;
			break;
		default:
			u8_error_state = STD_TYPES_NOK;
			break;
	}
	
	return u8_error_state;
}

/*******************************************************************************
* Function Name:		RCC_u8EnablePeripheralClk
********************************************************************************/
u8 RCC_u8EnableDisablPeripheralClk	(u8 Copy_u8PeripheralId ,u8 Copy_u8State)
{
	u8 u8_error_state = STD_TYPES_OK;
	if((Copy_u8PeripheralId < RCC_u8_APB2_END) && Copy_u8State < 2)
	{
		switch(Copy_u8State)
		{
			case RCC_u8_Enable:
				if(Copy_u8PeripheralId < RCC_u8_AHB1_END)
				{
					SET_BIT(RCC->AHB1ENR,Copy_u8PeripheralId);
				}
				else if(Copy_u8PeripheralId < RCC_u8_AHB2_END)
				{
					Copy_u8PeripheralId -= RCC_u8_AHB1_END;
					SET_BIT(RCC->AHB2ENR,Copy_u8PeripheralId);
				}
				else if(Copy_u8PeripheralId < RCC_u8_APB1_END)
				{
					Copy_u8PeripheralId -= RCC_u8_AHB2_END;
					SET_BIT(RCC->APB1ENR,Copy_u8PeripheralId);
				}
				else
				{
					Copy_u8PeripheralId -= RCC_u8_APB1_END;
					SET_BIT(RCC->APB2ENR,Copy_u8PeripheralId);
				}
				break;
				
			case RCC_u8_Disable:
				if(Copy_u8PeripheralId < RCC_u8_AHB1_END)
				{
					CLR_BIT(RCC->AHB1ENR,Copy_u8PeripheralId);
				}
				else if(Copy_u8PeripheralId < RCC_u8_AHB2_END)
				{
					Copy_u8PeripheralId -= RCC_u8_AHB1_END;
					CLR_BIT(RCC->AHB2ENR,Copy_u8PeripheralId);
				}
				else if(Copy_u8PeripheralId < RCC_u8_APB1_END)
				{
					Copy_u8PeripheralId -= RCC_u8_AHB2_END;
					CLR_BIT(RCC->APB1ENR,Copy_u8PeripheralId);
				}
				else
				{
					Copy_u8PeripheralId -= RCC_u8_APB1_END;
					CLR_BIT(RCC->APB2ENR,Copy_u8PeripheralId);
				}
				break;
				
			default:
				/* This case shouldn't happen */
				break;
		}
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}
	return u8_error_state;
}

/*******************************************************************************
* Function Name:		RCC_u8ResetPeripheralClk
********************************************************************************/
u8 RCC_u8ResetPeripheralClk	(u8 Copy_u8PeripheralId)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8PeripheralId < RCC_u8_APB2_END)
	{
		if(Copy_u8PeripheralId < RCC_u8_AHB1_END)
		{
			CLR_BIT(RCC->AHB1RSTR,Copy_u8PeripheralId);
		}
		else if(Copy_u8PeripheralId < RCC_u8_AHB2_END)
		{
			Copy_u8PeripheralId -= RCC_u8_AHB1_END;
			CLR_BIT(RCC->AHB2RSTR,Copy_u8PeripheralId);
		}
		else if(Copy_u8PeripheralId < RCC_u8_APB1_END)
		{
			Copy_u8PeripheralId -= RCC_u8_AHB2_END;
			CLR_BIT(RCC->APB1RSTR,Copy_u8PeripheralId);
		}
		else
		{
			Copy_u8PeripheralId -= RCC_u8_APB1_END;
			CLR_BIT(RCC->APB2RSTR,Copy_u8PeripheralId);
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
