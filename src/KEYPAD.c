/******************************************************************************
*  File name:		KEYPAD.c
*  Date:			Oct 26, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "BIT_MATH.h"
#include "stm32f401xx.h"

#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
/*******************************************************************************
* Function Name:		KEYPAD_init
********************************************************************************/
void KEYPAD_init(void)
{
    RCC_u8EnableDisablPeripheralClk(KEYPAD_COL_RCC,RCC_u8_Enable);
    RCC_u8EnableDisablPeripheralClk(KEYPAD_ROW_RCC,RCC_u8_Enable);
    for(u8 i = 0 ; i < KEYPAD_NUM_ROWS ; i++)
    {
        GPIO_u8SetPinMode(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+i,GPIO_u8_INPUT_PULL_UP);
    }
    for(u8 i = 0 ; i < KEYPAD_NUM_ROWS ; i++)
    {
        GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+i,GPIO_u8_OUTPUT_GP_PP);
    }
}

/*******************************************************************************
* Function Name:		KEYPAD_getPressedKey
********************************************************************************/
u8 KEYPAD_getPressedKey(void)
{
#ifndef KEYPAD_CALCULATOR
    char arr[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
#else
    char arr[4][4]={{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','C'},{'*','0','/','='}};
#endif
    u8 row,coloumn,pinval = NOTPRESSED;
    u8  returnval = NOTPRESSED;
    while(returnval == NOTPRESSED)
    {
        for(row=0;row<4;row++)
        {
            GPIO_u8WritePinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID,     GPIO_u8_HIGH);
            GPIO_u8WritePinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1,   GPIO_u8_HIGH);
            GPIO_u8WritePinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2,   GPIO_u8_HIGH);
            GPIO_u8WritePinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3,   GPIO_u8_HIGH);
            GPIO_u8WritePinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, GPIO_u8_LOW);
            for(coloumn=0;coloumn<4;coloumn++)
            {
                pinval = 1 ;
                GPIO_u8GetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+coloumn, &pinval);
                if(KEYPAD_BUTTON_PRESSED == pinval)
                {
                     returnval = arr[row][coloumn];
                     break;
                }
            }
            if(KEYPAD_BUTTON_PRESSED == pinval)
            {
                break;
            }
        }
        if(returnval != NOTPRESSED)
        {
            return returnval ;
        }
    }
    return returnval ;
}
