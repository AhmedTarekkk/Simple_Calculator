/******************************************************************************
*  File name:		STK_program.c
*  Date:			Oct 22, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "BIT_MATH.h"
#include "stm32f401xx.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

/* to store the address of the function to be the ISR */
static void (*STK_Pf)(void) = NULL;
static u8 STK_u8ModeOfInterval; /* Variable to save the current mode of the STK */
void SysTick_Handler(void);
/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		STK_voidInit
********************************************************************************/
u8 STK_u8Init(u8 Copy_u8ClockSource)
{
	u8 u8_error_state = STD_TYPES_OK;

	/* Choose the Clock Source */
	switch(Copy_u8ClockSource)
	{
		case STK_u8_AHB:
			
			break;
		case STK_u8_AHB_8:
			
			break;
		default:
			u8_error_state = STD_TYPES_NOK;
			break;
	}
	/* Disable the timer */
	CLR_BIT(STK->CTRL,0);

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8SetBusyWait
********************************************************************************/
u8 STK_u8SetuSBusyWait(u32 Copy_u32Time_us)
{
	u8 u8_error_state = STD_TYPES_OK;
	u32 u32_load_value;

	if(GET_BIT(STK->CTRL,2)) /* The clock source is AHB/1 */
	{
		u32_load_value = (F_CPU/1000000)*Copy_u32Time_us ;
	}
	else /* The clock source is AHB/8 */
	{
		u32_load_value = (F_CPU/8000000)*Copy_u32Time_us ;
	}

	if(u32_load_value <= 0x00FFFFFF)
	{
		/* Close the exception request */
		CLR_BIT(STK->CTRL,1);
		/* Load the required delay */
		STK->LOAD = u32_load_value ;
		/* Enable the timer */
		SET_BIT(STK->CTRL,0);
		/* Start the change immediately by writing any value to VAL register */
		STK->VAL = 0;
		/* Wait until timer reach zero */
		while(0 == GET_BIT(STK->CTRL,16));
		/* Disable Timer */
		CLR_BIT(STK->CTRL,0);
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8SetmSBusyWait
********************************************************************************/
u8 STK_u8SetmSBusyWait(u32 Copy_u32Time_ms)
{
	u8 u8_error_state = STD_TYPES_OK;

	for(u32 i = 0 ; i < Copy_u32Time_ms ; i++)
	{
		STK_u8SetuSBusyWait(1000);
	}

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8SetIntervalSingle
********************************************************************************/
u8 STK_u8SetIntervalSingle(u32 Copy_u32Time_us, void(*Copy_pf)(void))
{
	u8 u8_error_state = STD_TYPES_OK;
	u32 u32_load_value;

	if(GET_BIT(STK->CTRL,2)) /* The clock source is AHB/1 */
	{
		u32_load_value = (F_CPU/1000000)*Copy_u32Time_us ;
	}
	else /* The clock source is AHB/8 */
	{
		u32_load_value = (F_CPU/8000000)*Copy_u32Time_us ;
	}
	if((u32_load_value <= 0x00FFFFFF) && (Copy_pf != NULL))
	{
		/* Set Callback Function */
		STK_Pf = Copy_pf;
		/* Load the required delay */
		STK->LOAD = u32_load_value ;
		/* Set the mode = interval */
		STK_u8ModeOfInterval = STK_u8_SINGLE_INTERVAL;
		/* Enable the exception request */
		SET_BIT(STK->CTRL,1);
		/* Enable the timer */
		SET_BIT(STK->CTRL,0);
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}
	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8SetIntervalPeriodic
********************************************************************************/
u8 STK_u8SetIntervalPeriodic(u32 Copy_u32Time_us, void(*Copy_pf)(void))
{
	u8 u8_error_state = STD_TYPES_NOK;
	u32 u32_load_value;

	if(GET_BIT(STK->CTRL,2)) /* The clock source is AHB/1 */
	{
		u32_load_value = (F_CPU/1000000)*Copy_u32Time_us ;
	}
	else /* The clock source is AHB/8 */
	{
		u32_load_value = (F_CPU/8000000)*Copy_u32Time_us ;
	}
	if((u32_load_value <= 0x00FFFFFF) && (Copy_pf != NULL))
	{
		/* Set Callback Function */
		STK_Pf = Copy_pf;
		/* Load the required delay */
		STK->LOAD = u32_load_value-1 ;
		/* Enable the timer */
		SET_BIT(STK->CTRL,0);
		/* Set the mode = interval */
		STK_u8ModeOfInterval = STK_u8_PERIODIC_INTERVAL;
		/* Enable the exception request */
		SET_BIT(STK->CTRL,1);
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}
	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8Stop
********************************************************************************/
u8 STK_u8Stop(void)
{
	u8 u8_error_state = STD_TYPES_OK;

	CLR_BIT(STK->CTRL,0);
	STK->LOAD = 0;
	STK->VAL  = 0;

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8GetElapsedTime
********************************************************************************/
u8 STK_u8GetElapsedTime      (u32 * Copy_pu32ElapsedTime)
{
	u8 u8_error_state = STD_TYPES_OK;

	if(Copy_pu32ElapsedTime != NULL)
	{
		*Copy_pu32ElapsedTime = (STK->LOAD - STK->VAL) ;
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

/*******************************************************************************
* Function Name:		STK_u8GetRemainingTime
********************************************************************************/
u8 STK_u8GetRemainingTime    (u32 * Copy_pu32RemainingTime)
{
	u8 u8_error_state = STD_TYPES_OK;

	if(Copy_pu32RemainingTime != NULL)
	{
		*Copy_pu32RemainingTime = STK->VAL ;
	}
	else
	{
		u8_error_state = STD_TYPES_NOK;
	}

	return u8_error_state;
}

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void SysTick_Handler(void)
{
	/* Clear The Interrupt Flag */
	CLR_BIT(STK->CTRL,16);
	
	if(STK_u8ModeOfInterval == STK_u8_SINGLE_INTERVAL)
	{
		/* Disable and Stop The Timer */
		CLR_BIT(STK->CTRL,0);
		CLR_BIT(STK->CTRL,1);
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
	if(STK_Pf != NULL)
	{
		STK_Pf();
	}
}
