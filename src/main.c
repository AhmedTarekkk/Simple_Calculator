#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
typedef enum
{
    Entering_number_one,
    Entering_number_two,
    Calculate_the_result,
    reset_calculator
}state;
state current_state = Entering_number_one;
s32 num1 = 0,num2 = 0,result = 0;
void TOG(void)
{
	GPIO_u8TogPinValue(GPIO_u8_GPIOA,GPIO_u8_PIN0);
}
int main(void)
{
	RCC_u8InitSysClk();
	STK_u8Init(STK_u8_AHB_8);
	LCD_init();
    KEYPAD_init();
    LCD_clearScreen();
    u8 negative_num_1 = FALSE,key = STD_TYPES_NOK,op;
	while(1)
	{
        if(Calculate_the_result != current_state && key != 'C')
        {
            key = KEYPAD_getPressedKey();
        }
        switch(current_state)
        {
            case Entering_number_one:
                if(key >= '0' && key <= '9')
                {
                    LCD_displayCharacter(key);
                    num1 = num1*10 + key - '0';
                }
                else if(('*' == key) || ('+' == key) || ('/' == key) || ('-' == key))
                {
                    if((num1 == 0) && ('-' == key))
                    {
                        LCD_displayCharacter(key);
                        negative_num_1 = TRUE;
                    }
                    else
                    {
                        if(num1 == 0)
                        {
                            LCD_displayCharacter('0');
                        }
                        LCD_displayCharacter(key);
                        op = key;
                        if(negative_num_1)
                        {
                            num1 *= -1;
                        }
                        LCD_moveCursor(1,0);
                        current_state = Entering_number_two;
                    }
                }
                else
                {
                    current_state = reset_calculator;
                }
                break;
            case Entering_number_two:
                if(key >= '0' && key <= '9')
                {
                    LCD_displayCharacter(key);
                    num2 = num2*10 + key - '0';
                }
                else if('=' == key)
                {
                    current_state = Calculate_the_result;
                }
                else if('C' == key)
                {
                    current_state = reset_calculator;
                }
                else
                {
                    /* Do nothing */
                }
                break;
            case Calculate_the_result:
                LCD_clearScreen();
                LCD_displayString("Result = ");
                LCD_moveCursor(1,0);
                switch(op)
                {
                    case '+':
                        result = num1 + num2;
                        break;
                    case '-':
                        result = num1 - num2;
                        break;
                    case '*':
                        result = num1 * num2;
                        break;
                    case '/':
                        if(num2 == 0)
                        {
                            LCD_displayString("ERROR !!!");
                        }
                        else
                        {
                            result = num1 / num2;
                        }
                        break;
                    default:
                        /* This case shouldn't happen */
                        break;
                }
                if(result >= 0)
                {
                    LCD_intgerToString(result);
                }
                else
                {
                    LCD_displayCharacter('-');
                    result *= -1;
                    LCD_intgerToString(result);
                }
                current_state = reset_calculator;
                break;
            case reset_calculator:
                if('C' == key)
                {
                    LCD_clearScreen();
                    LCD_moveCursor(0,0);
                    num1 = 0;
                    num2 = 0;
                    result = 0;
                    negative_num_1 = FALSE;
                    current_state = Entering_number_one;
                    key = STD_TYPES_NOK;
                }
                break;
        }
        STK_u8SetmSBusyWait(1000);
	}
	
}
