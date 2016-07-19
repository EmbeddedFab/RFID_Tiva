/***************************************************************
 *  Source File: EF_KeyPad.c
 *
 *  Description: This simple driver for keypad 3X3
 *
 *  History:     Version 1.0  - INIT Version
 *  Date   :     25/08/2014
 *  -------------------------------------------------------
 *  Author :     EmbeddedFab.
 *
 *  Copyright (C) <2014>  <EmbeddedFab>
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 
 **************************************************************/
#include "EF_KeyPad.h"
#include "../MCAL/EF_TIVA_DIO.h"

/*************************************************************
 * Global Definitions
**************************************************************/
/* ROWS */
#define FIRST_ROW_PORT      'e'
#define FIRST_ROW_PIN        4

#define SECOND_ROW_PORT     'b'
#define SECOND_ROW_PIN       1

#define THIRD_ROW_PORT      'b'
#define THIRD_ROW_PIN        0

/* Cloums */
#define FIRST_COLUMN_PORT   'a'
#define FIRST_COLUMN_PIN     5

#define SECOND_COLUMN_PORT  'b'
#define SECOND_COLUMN_PIN    4

#define THIRD_COLUMN_PORT   'e'
#define THIRD_COLUMN_PIN     5

/*************************************************************
 * API Functions
**************************************************************/
/*********************************************************************
* Function    : void EF_void_KeyPad_Init (void);
*
* DESCRIPTION : This function used to Initialize keypad
*
* PARAMETERS  : Void.
*            
*
* Return Value: Void.
***********************************************************************/
void EF_void_KeyPad_Init (void)
{
    /* make 3 pins output (COLOUMNS) and anther 3 inputs (ROWS) with pull-up
     * normally, input is high. */
    EF_S8_t_DIO_InitPin (FIRST_ROW_PORT  , FIRST_ROW_PIN  , INPUT);
    EF_S8_t_DIO_InitPin (SECOND_ROW_PORT , SECOND_ROW_PIN , INPUT);
    EF_S8_t_DIO_InitPin (THIRD_ROW_PORT  , THIRD_ROW_PIN  , INPUT);

    EF_S8_t_DIO_InitPin (FIRST_COLUMN_PORT  , FIRST_COLUMN_PIN  , OUTPUT);
    EF_S8_t_DIO_InitPin (SECOND_COLUMN_PORT , SECOND_COLUMN_PIN , OUTPUT);
    EF_S8_t_DIO_InitPin (THIRD_COLUMN_PORT  , THIRD_COLUMN_PIN  , OUTPUT);

    /* Enable Internal PullUp Resistor */
    GPIOPadConfigSet (GPIO_PORTE_BASE, 1<<FIRST_ROW_PIN , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

    GPIOPadConfigSet (GPIO_PORTB_BASE, 1<<SECOND_ROW_PIN , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

    GPIOPadConfigSet (GPIO_PORTB_BASE, 1<<THIRD_ROW_PIN , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
/*
	EF_S8_DIO_SetPin   (FIRST_ROW_PORT , FIRST_ROW_PIN);
	EF_S8_DIO_SetPin   (SECOND_ROW_PORT, SECOND_ROW_PIN);
	EF_S8_DIO_SetPin   (THIRD_ROW_PORT ,  THIRD_ROW_PIN);
*/
}
/*********************************************************************
* Function    : U8_t EF_u8_KeyPad_Scan (void);
*
* DESCRIPTION : This function used to scan the input if it existed
*
* PARAMETERS  : void
*            
*
* Return Value: U8_t : Return number from (1 to 9) if user press any
                       key or 0 if user not press.
***********************************************************************/
U8_t EF_u8_KeyPad_Scan (void)
{
    U8_t KeyPressed = NOT_PRESSED;
    /* when SW is pressed , it will be a short circuit between input and output,
     * so input will be low. So Scanning with making output low , will tell
     * the Scan function which SW is pressed. keypad mapping :
     * 	[1|2|3]
     * 	[4|5|6]
     * 	[7|8|9]
     * */
    /* Scan First Column */
    EF_S8_DIO_ClearPin(FIRST_COLUMN_PORT , FIRST_COLUMN_PIN);
	EF_S8_DIO_SetPin  (SECOND_COLUMN_PORT, SECOND_COLUMN_PIN);
	EF_S8_DIO_SetPin  (THIRD_COLUMN_PORT , THIRD_COLUMN_PIN);

    if(!(EF_S8_DIO_CheckPin(FIRST_ROW_PORT, FIRST_ROW_PIN)))
    {
        KeyPressed = 1;
    }
    else if(!(EF_S8_DIO_CheckPin(SECOND_ROW_PORT, SECOND_ROW_PIN)))
    {
        KeyPressed = 4;
    }
    else if(!(EF_S8_DIO_CheckPin(THIRD_ROW_PORT, THIRD_ROW_PIN)))
    {
        KeyPressed = 7;	
    }
/* Scan Second Column */

    EF_S8_DIO_SetPin (FIRST_COLUMN_PORT , FIRST_COLUMN_PIN);
    EF_S8_DIO_ClearPin (SECOND_COLUMN_PORT, SECOND_COLUMN_PIN);
	EF_S8_DIO_SetPin  (THIRD_COLUMN_PORT , THIRD_COLUMN_PIN);

    if(!(EF_S8_DIO_CheckPin(FIRST_ROW_PORT, FIRST_ROW_PIN)))
    {
        KeyPressed = 2;
    }
    else if(!(EF_S8_DIO_CheckPin(SECOND_ROW_PORT, SECOND_ROW_PIN)))
    {
        KeyPressed = 5;
    }
    else if(!(EF_S8_DIO_CheckPin(THIRD_ROW_PORT, THIRD_ROW_PIN)))
    {
        KeyPressed = 8;	
    }

/* Scan Third Column */

    EF_S8_DIO_SetPin(FIRST_COLUMN_PORT , FIRST_COLUMN_PIN);
    EF_S8_DIO_SetPin  (SECOND_COLUMN_PORT, SECOND_COLUMN_PIN);
    EF_S8_DIO_ClearPin (THIRD_COLUMN_PORT , THIRD_COLUMN_PIN);

    if(!(EF_S8_DIO_CheckPin(FIRST_ROW_PORT, FIRST_ROW_PIN)))
    {
        KeyPressed = 3;
    }
    else if(!(EF_S8_DIO_CheckPin(SECOND_ROW_PORT, SECOND_ROW_PIN)))
    {
        KeyPressed = 6;
    }
    else if(!(EF_S8_DIO_CheckPin(THIRD_ROW_PORT, THIRD_ROW_PIN)))
    {
        KeyPressed = 9;
    }
	return (KeyPressed);
}



U8_t EF_u8_KeyPad_GetKeyAfterReleasing ()
{
    volatile U8_t KeyPressed_Status = 0;

    KeyPressed_Status = EF_u8_KeyPad_Scan();
    if( KeyPressed_Status != NOT_PRESSED)
    {
        while (EF_u8_KeyPad_Scan() != NOT_PRESSED );
                _delay_ms(50);
    }

    return KeyPressed_Status;
}

