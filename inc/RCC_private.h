/******************************************************************************
*  File name:		RCC_private.h
*  Date:			Oct 21, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/
/*******************************************************************************
*                        		PLL Clock Source	                           *
*******************************************************************************/
#define RCC_u8_PLL_HSI_DIVIDED_BY_2			1
#define RCC_u8_PLL_HSE						2
#define RCC_u8_PLL_HSE_DIVIDED_BY_2			3

/*******************************************************************************
*                        		PLL Clock Multiplier	                       *
*******************************************************************************/
#define RCC_u8_PLL_MULTIPLY_BY_2       		0x00 /* 0b0000 */
#define RCC_u8_PLL_MULTIPLY_BY_3       		0x01 /* 0b0001 */
#define RCC_u8_PLL_MULTIPLY_BY_4       		0x02 /* 0b0010 */
#define RCC_u8_PLL_MULTIPLY_BY_5       		0x03 /* 0b0011 */
#define RCC_u8_PLL_MULTIPLY_BY_6       		0x04 /* 0b0100 */
#define RCC_u8_PLL_MULTIPLY_BY_7       		0x05 /* 0b0101 */
#define RCC_u8_PLL_MULTIPLY_BY_8       		0x06 /* 0b0110 */
#define RCC_u8_PLL_MULTIPLY_BY_9       		0x07 /* 0b0111 */
#define RCC_u8_PLL_MULTIPLY_BY_10      		0x08 /* 0b1000 */
#define RCC_u8_PLL_MULTIPLY_BY_11      		0x09 /* 0b1001 */
#define RCC_u8_PLL_MULTIPLY_BY_12      		0x0A /* 0b1010 */
#define RCC_u8_PLL_MULTIPLY_BY_13      		0x0B /* 0b1011 */
#define RCC_u8_PLL_MULTIPLY_BY_14      		0x0C /* 0b1100 */
#define RCC_u8_PLL_MULTIPLY_BY_15      		0x0D /* 0b1101 */
#define RCC_u8_PLL_MULTIPLY_BY_16      		0x0E /* 0b1110 */


/*******************************************************************************
*                        		HSE Clock Source	                           *
*******************************************************************************/
#define RCC_u8_HSE_NOT_BYPASS          		1
#define RCC_u8_HSE_BYPASS              		2

/*******************************************************************************
*                        		APBx Prescaler		                           *
*******************************************************************************/
#define RCC_u8_APBx_DIVIDED_BY_1       		0x00 /* 0b000 */
#define RCC_u8_APBx_DIVIDED_BY_2       		0x04 /* 0b100 */
#define RCC_u8_APBx_DIVIDED_BY_4       		0x05 /* 0b101 */
#define RCC_u8_APBx_DIVIDED_BY_8       		0x06 /* 0b110 */
#define RCC_u8_APBx_DIVIDED_BY_16      		0x07 /* 0b111 */

/*******************************************************************************
*                        		AHB Prescaler		                           *
*******************************************************************************/
#define RCC_u8_AHB_DIVIDED_BY_1       		0x00 /* 0b0000 */
#define RCC_u8_AHB_DIVIDED_BY_2       		0x08 /* 0b1000 */
#define RCC_u8_AHB_DIVIDED_BY_4       		0x09 /* 0b1001 */
#define RCC_u8_AHB_DIVIDED_BY_8       		0x0A /* 0b1010 */
#define RCC_u8_AHB_DIVIDED_BY_16      		0x0B /* 0b1011 */
#define RCC_u8_AHB_DIVIDED_BY_64      		0x0C /* 0b1100 */
#define RCC_u8_AHB_DIVIDED_BY_128     		0x0D /* 0b1101 */
#define RCC_u8_AHB_DIVIDED_BY_256     		0x0E /* 0b1110 */
#define RCC_u8_AHB_DIVIDED_BY_512     		0x0F /* 0b1111 */


#endif
