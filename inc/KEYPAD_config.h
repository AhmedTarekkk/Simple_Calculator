/******************************************************************************
*  File name:		KEYPAD_config.h
*  Date:			Oct 26, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*******************************************************************************
*                        		Configuration                                  *
*******************************************************************************/
#include "STD_TYPES.h"

#define STANDARD_KEYPAD				FALSE
#define KEYPAD_CALCULATOR
#define NOTPRESSED 					0xFF

#define KEYPAD_NUM_COLS				4
#define	KEYPAD_NUM_ROWS				4

#define	KEYPAD_COL_PORT_ID			GPIO_u8_GPIOA
#define	KEYPAD_FIRST_COL_PIN_ID		GPIO_u8_PIN0
#define KEYPAD_COL_RCC              RCC_u8_GPIOA

#define KEYPAD_ROW_PORT_ID			GPIO_u8_GPIOB
#define KEYPAD_FIRST_ROW_PIN_ID		GPIO_u8_PIN0
#define KEYPAD_ROW_RCC              RCC_u8_GPIOB

#define KEYPAD_BUTTON_PRESSED       GPIO_u8_LOW
#define KEYPAD_BUTTON_RELEASED      GPIO_u8_HIGH

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

#endif
