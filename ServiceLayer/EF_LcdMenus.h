/***************************************************************
 *  Source File: EF_LcdMenus.h
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

#ifndef _EF_LCD_MENUS_H_
#define _EF_LCD_MENUS_H_

#include "../UtilitiesLayer/std_types.h"

/*********************************************************************
* Function    : void EF_void_PrintError (U8_t ERRORType)
*
* DESCRIPTION : This function used to Print Special Error On LCD
*
* PARAMETERS  : ERRORType: define which Error will be printed
*
* Return Value: Void.
***********************************************************************/
void EF_void_LcdMenus_Init ();

void EF_void_LcdMenus_EnterCard ();

void EF_void_LcdMenus_Welcome();

void EF_void_LcdMenus_CardDeteced ();

void EF_void_LcdMenus_Selection();

void EF_void_LcdMenus_EnterPassword();

void EF_void_LcdMenus_RightPassword();

void EF_void_LcdMenus_WrongPassword();

void EF_void_LcdMenus_EnterBalance();

void EF_void_LcdMenus_GetBalance();

void EF_void_LcdMenus_ConfirmBalance();

void EF_void_LcdMenus_BalanceUpdated();

void EF_void_LcdMenus_CardRemoved();

void EF_void_LcdMenus_ChargeHistory();

#endif
