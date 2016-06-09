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

BOOLEAN EF_BOOLEAN_RFID_Init (RFID_ModulesEnum ModuleType);

U8_t EF_u8_RFID_IsCardExist (RFID_ModulesEnum ModuleType);

U8_t EF_u8_RFID_GetCardNumber (RFID_ModulesEnum ModuleType , U8_t* u8CardNumber_ptr ,U8_t* u8CardLength_ptr  );

U8_t EF_u8_RFID_PrepareCard (RFID_ModulesEnum ModuleType );

U8_t EF_u8_RFID_GetUserBalance (RFID_ModulesEnum ModuleType , U8_t * u8Balance_ptr );

U8_t EF_u8_RFID_UpdateUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance );

U8_t EF_u8_RFID_AddUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance );

U8_t EF_u8_RFID_SubtractUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance );

#endif /* EF_RFID_H_ */
