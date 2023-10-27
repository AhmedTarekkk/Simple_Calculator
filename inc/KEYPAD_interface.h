/******************************************************************************
*  File name:		KEYPAD_interface.h
*  Date:			Oct 26, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "STD_TYPES.h"

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/
/*******************************************************************************
* Function Name:		KEYPAD_init
* Description:			Function to initialize keypad pins
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void KEYPAD_init(void);

/*******************************************************************************
* Function Name:		KEYPAD_getPressedKey
* Description:			Get the Keypad pressed button
* Parameters (in):    	None
* Parameters (out):   	The pressed key on the keypad
* Return value:      	uint8
********************************************************************************/
u8 KEYPAD_getPressedKey(void);

#endif
