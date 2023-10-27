/******************************************************************************
*  File name:		stm32f103xx.h
*  Date:			Oct 21, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef STM32F103xx_H
#define STM32F103xx_H

/*******************************************************************************
*                      				INCLUDE                    		           *
*******************************************************************************/

#include "STD_TYPES.h"

/*******************************************************************************
*                      				RCC                     		           *
*******************************************************************************/

#define RCC_u32_BASE_ADDRESS						0x40023800U

typedef struct
{	
	volatile u32 CR;
	volatile u32 PLLCFGR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 AHB1RSTR;
	volatile u32 AHB2RSTR;
	volatile u32 RESERVED[2];
	volatile u32 APB1RSTR;
	volatile u32 APB2RSTR;
	volatile u32 RESERVED2[2];
	volatile u32 AHB1ENR;
	volatile u32 AHB2ENR;
	volatile u32 RESERVED3[2];
	volatile u32 APB1ENR;
	volatile u32 APB2ENR;
	volatile u32 RESERVED4[2];
	volatile u32 AHB1LPENR;
	volatile u32 AHB2LPENR;
	volatile u32 RESERVED5[2];
	volatile u32 APB1LPENR;
	volatile u32 APB2LPENR;
	volatile u32 RESERVED6[2];
	volatile u32 BDCR;		
	volatile u32 CSR;
	volatile u32 RESERVED7[2];
	volatile u32 SSCGR;		
	volatile u32 PLLI2SCFGR;
	volatile u32 DCKCFGR;
}RCC_RegDef_t;

#define RCC						((RCC_RegDef_t *)RCC_u32_BASE_ADDRESS)

/*******************************************************************************
*                      				GPIO                     		           *
*******************************************************************************/

#define GPIOA_u32_BASE_ADDRESS						0x40020000U
#define GPIOB_u32_BASE_ADDRESS						0x40020400U
#define GPIOC_u32_BASE_ADDRESS						0x40020800U
#define GPIOD_u32_BASE_ADDRESS						0x40020C00U
#define GPIOE_u32_BASE_ADDRESS						0x40021000U
#define GPIOH_u32_BASE_ADDRESS						0x40021C00U

typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
}GPIO_RegDef_t;

#define GPIOA					((GPIO_RegDef_t *)GPIOA_u32_BASE_ADDRESS)
#define GPIOB					((GPIO_RegDef_t *)GPIOB_u32_BASE_ADDRESS)
#define GPIOC					((GPIO_RegDef_t *)GPIOC_u32_BASE_ADDRESS)
#define GPIOD					((GPIO_RegDef_t *)GPIOD_u32_BASE_ADDRESS)
#define GPIOE					((GPIO_RegDef_t *)GPIOE_u32_BASE_ADDRESS)
#define GPIOH					((GPIO_RegDef_t *)GPIOH_u32_BASE_ADDRESS)

/*******************************************************************************
*                      				SYSTICK                    		           *
*******************************************************************************/

#define STK_u32_BASE_ADDRESS						0xE000E010U

typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}STK_RegDef_t;

#define STK						((STK_RegDef_t *)STK_u32_BASE_ADDRESS)

#endif
