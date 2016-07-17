/***************************************************************
 *  Source File: EF_RFID.h
 *
 *  Description:  RFID  driver for service layer for more RFID Module types
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
#ifndef EF_RFID_H_
#define EF_RFID_H_

#include "../UtilitiesLayer/std_types.h"

typedef enum
{
    SLM025M_MODULE,
}RFID_ModulesEnum;

/****************************************************************************
* Function    : EF_BOOLEAN_RFID_Init(RFID_ModulesEnum ModuleType)
*
* DESCRIPTION : Initializes the RFID module
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*
* Return Value: Initialization status
******************************************************************************/
BOOLEAN EF_BOOLEAN_RFID_Init (RFID_ModulesEnum ModuleType);

/****************************************************************************
* Function    : EF_u8_RFID_IsCardExist(RFID_ModulesEnum ModuleType)
*
* DESCRIPTION : Check if card pin is connected and the card itself is near by to
*               RFID module
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*
* Return Value: Card existance status
******************************************************************************/
U8_t EF_u8_RFID_IsCardExist (RFID_ModulesEnum ModuleType);

/****************************************************************************
* Function    : EF_u8_RFID_GetCardNumber (RFID_ModulesEnum ModuleType , U8_t* u8CardNumber_ptr ,U8_t* u8CardLength_ptr)
*
* DESCRIPTION : Get RFID card number
*
* PARAMETERS  : ModuleType:       enum type for RFID module type
*               u8CardNumber_ptr: Pointer to the returned CardNumber.
*               u8CardLength_ptr: Pointer to returned Card Length, the old
*                                 standard is 4 bytes and the new is 7bytes.
*
* Return Value: Getting Card number status
******************************************************************************/
U8_t EF_u8_RFID_GetCardNumber (RFID_ModulesEnum ModuleType , U8_t* u8CardNumber_ptr ,U8_t* u8CardLength_ptr  );

/****************************************************************************
* Function    : EF_u8_RFID_PrepareCard (RFID_ModulesEnum ModuleType)
*
* DESCRIPTION : locking all sectors with a locking key except for the working
*               sector
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*
* Return Value: Working sector login status
******************************************************************************/
U8_t EF_u8_RFID_PrepareCard (RFID_ModulesEnum ModuleType );

/****************************************************************************
* Function    : EF_u8_RFID_GetUserBalance (RFID_ModulesEnum ModuleType , U8_t * u8Balance_ptr )
*
* DESCRIPTION : Get the current user balance
*
* PARAMETERS  : ModuleType:    enum type for RFID module type
*               u8Balance_ptr: A pointer to the returned balance
*
* Return Value: Working sector login status
******************************************************************************/
U8_t EF_u8_RFID_GetUserBalance (RFID_ModulesEnum ModuleType , U8_t * u8Balance_ptr );

/****************************************************************************
* Function    : EF_u8_RFID_UpdateUserBalance  (RFID_ModulesEnum ModuleType , U16_t u16Balance )
*
* DESCRIPTION : Update the user balance to a certain value
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*               u16Balance: The value of the new balance
*
* Return Value: Login or Writing status
******************************************************************************/
U8_t EF_u8_RFID_UpdateUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance );

/****************************************************************************
* Function    : EF_u8_RFID_AddUserBalance  (RFID_ModulesEnum ModuleType , U16_t u16Balance )
*
* DESCRIPTION : Increment the user balance by a certain value
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*               u16Balance: The value of the balance increment
*
* Return Value: Login, Reading or Writing status
******************************************************************************/
U8_t EF_u8_RFID_AddUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance );

/****************************************************************************
* Function    : EF_u8_RFID_SubtractUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance )
*
* DESCRIPTION : Decrement the user balance by a certain value
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*               u16Balance: The value of the balance decrement
*
* Return Value: Login, Reading or Writing status
******************************************************************************/
U8_t EF_u8_RFID_SubtractUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance );

#endif /* EF_RFID_H_ */
