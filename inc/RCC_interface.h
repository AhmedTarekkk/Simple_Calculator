/******************************************************************************
*  File name:		RCC.h
*  Date:			Oct 21, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef RCC_H
#define RCC_H

/*******************************************************************************
*                        		Includes		                               *
*******************************************************************************/
#include "STD_TYPES.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/
/*******************************************************************************
*                        		Clock Source	                               *
*******************************************************************************/
#define RCC_u8_HSI					1
#define RCC_u8_HSE					2
#define RCC_u8_PLL					3

/*******************************************************************************
*                        		Peripherals State                              *
*******************************************************************************/
#define RCC_u8_Disable				(0)
#define RCC_u8_Enable				(1)

/*******************************************************************************
*                        		AHB1 Peripherals                                *
*******************************************************************************/
#define	RCC_u8_GPIOA				(0 )
#define	RCC_u8_GPIOB				(1 )
#define	RCC_u8_GPIOC				(2 )
#define	RCC_u8_GPIOD				(3 )
#define	RCC_u8_GPIOE				(4 )
#define	RCC_u8_GPIOH				(7 )
#define	RCC_u8_CRC					(12)
#define	RCC_u8_DMA1					(21)
#define	RCC_u8_DMA2					(22)
#define RCC_u8_AHB1_END				(1 +RCC_u8_DMA2)

/*******************************************************************************
*                        		AHB2 Peripherals                               *
*******************************************************************************/
#define	RCC_u8_OTGFSE				(0 +RCC_u8_AHB1_END)
#define RCC_u8_AHB2_END				(1 +RCC_u8_OTGFSE)

/*******************************************************************************
*                        		APB1 Peripherals                               *
*******************************************************************************/
#define	RCC_u8_TIM2					(0  +RCC_u8_AHB2_END)
#define	RCC_u8_TIM3					(1  +RCC_u8_AHB2_END)
#define	RCC_u8_TIM4					(2  +RCC_u8_AHB2_END)
#define	RCC_u8_TIM5					(3  +RCC_u8_AHB2_END)
#define	RCC_u8_WWDG					(11 +RCC_u8_AHB2_END)
#define	RCC_u8_SPI2					(14 +RCC_u8_AHB2_END)
#define	RCC_u8_SPI3					(15 +RCC_u8_AHB2_END)
#define	RCC_u8_USART2				(17 +RCC_u8_AHB2_END)
#define	RCC_u8_I2C1					(21 +RCC_u8_AHB2_END)
#define	RCC_u8_I2C2					(22 +RCC_u8_AHB2_END)
#define	RCC_u8_I2C3					(23 +RCC_u8_AHB2_END)
#define	RCC_u8_PWR					(28 +RCC_u8_AHB2_END)
#define RCC_u8_APB1_END				(1  +RCC_u8_PWR)

/*******************************************************************************
*                        		APB2 Peripherals                               *
*******************************************************************************/
#define	RCC_u8_TIM1						(0  +RCC_u8_APB1_END)
#define	RCC_u8_USART1					(4  +RCC_u8_APB1_END)
#define	RCC_u8_USART6					(5  +RCC_u8_APB1_END)
#define	RCC_u8_ADC1						(8  +RCC_u8_APB1_END)
#define	RCC_u8_SDIO						(11 +RCC_u8_APB1_END)
#define	RCC_u8_SPI1						(12 +RCC_u8_APB1_END)
#define	RCC_u8_SPI4						(13 +RCC_u8_APB1_END)
#define	RCC_u8_SYSCFGEN					(14 +RCC_u8_APB1_END)
#define	RCC_u8_TIM9						(16 +RCC_u8_APB1_END)
#define	RCC_u8_TIM10					(17 +RCC_u8_APB1_END)
#define	RCC_u8_TIM11					(18 +RCC_u8_APB1_END)
#define RCC_u8_APB2_END					(1  +RCC_u8_TIM11)

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		RCC_u8InitSysClk
* Description:			Function to init the system clock source
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 RCC_u8InitSysClk	(void);

/*******************************************************************************
* Function Name:		RCC_u8GetClkSource
* Description:			Function to get the system clock source
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 RCC_u8GetClkSource	(u8 *Copy_pu8ClkSource);

/*******************************************************************************
* Function Name:		RCC_u8EnablePeripheralClk
* Description:			Function to enable or disable clock for specific periphral
* Parameters (in):    	The required peripheral and its bus
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 RCC_u8EnableDisablPeripheralClk	(u8 Copy_u8PeripheralId ,u8 Copy_u8State);

/*******************************************************************************
* Function Name:		RCC_u8ResetPeripheralClk
* Description:			Function to reset clock for specific periphral
* Parameters (in):    	The required peripheral and its bus
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 RCC_u8ResetPeripheralClk	(u8 Copy_u8PeripheralId);

#endif
