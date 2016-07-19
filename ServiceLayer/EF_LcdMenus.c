/***************************************************************
 *  Source File: EF_PrintMenus.c
 *
 *  Description: Using LCD driver to Print User Interface Menus.
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
#include "../HAL/EF_LCD.h"
#include <string.h>
#include "EF_LcdMenus.h"

/**************************API FuncTions ****************************************/

void EF_void_LcdMenus_Init ()
{
    /* Enable LCD */
    EF_void_LCD_init();
    EF_void_LCD_Clear_Screen();
    EF_void_LCD_goto(1, 1);
}

void EF_void_LcdMenus_Welcome()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"***Welcome***");
    _delay_ms(500);
}

void EF_void_LcdMenus_EnterCard ()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Please");
    EF_void_LCD_goto(2, 1);
    EF_void_LCD_print( (char *)"Enter Your Card");
    _delay_ms(500);
}


void EF_void_LcdMenus_CardDeteced ()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"your Card");
    EF_void_LCD_goto(2, 1);
    EF_void_LCD_print( (char *)"is deteced");
    _delay_ms(500);

}

void EF_void_LcdMenus_Selection()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"1-Add   ");
    EF_void_LCD_print( (char *)"2-Read");
    EF_void_LCD_goto(2, 1);
    EF_void_LCD_print( (char *)"3-History");
}


void EF_void_LcdMenus_EnterPassword()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Enter Password:");
    EF_void_LCD_goto(2, 1);
}


void EF_void_LcdMenus_RightPassword()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Right Password");
    _delay_ms(500);

}

void EF_void_LcdMenus_WrongPassword()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Wrong Password");
    _delay_ms(500);

}

void EF_void_LcdMenus_EnterBalance()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Enter Balance:");
    EF_void_LCD_goto(2, 1);
}

void EF_void_LcdMenus_GetBalance()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Your Balance:");
    EF_void_LCD_goto(2, 1);
}

void EF_void_LcdMenus_ConfirmBalance()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"(*)-Confirm");
    EF_void_LCD_goto(2, 1);
    EF_void_LCD_print( (char *)"(#)-Return");
}

void EF_void_LcdMenus_CardRemoved()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Card is removed");
    _delay_ms(500);

}

void EF_void_LcdMenus_BalanceUpdated()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Balance  is");
    EF_void_LCD_goto(2, 1);
    EF_void_LCD_print( (char *)"Updated");
    _delay_ms(500);
}

void EF_void_LcdMenus_ChargeHistory()
{
    EF_void_LCD_Clear_Screen();
    _delay_ms(20);

    EF_void_LCD_goto(1, 1);
    EF_void_LCD_print( (char *)"Charge History");
    EF_void_LCD_goto(2, 1);
}

