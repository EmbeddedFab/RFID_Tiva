/***************************************************************
 *  Source File: EF_RFID.c
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

#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "utils/uartstdio.h"
#include <string.h>
#include "../UtilitiesLayer/std_types.h"
#include "../MCAL/EF_TIVA_DIO.h"
#include "../MCAL/EF_TIVA_uart.h"
#include "../HAL/EF_SLM025M.h"
#include "../HAL/EF_SLM025M_cfg.h"
#include "EF_RFID.h"
#include "EF_RFID_cfg.h"

#define SL025_KEY_A_WORKED     0x010203040506UL
#define SL025_KEY_B_WORKED     0x060504030201UL
#define SL025_KEY_A_LOCKED     0x090807060504UL
#define SL025_KEY_B_LOCKED     0x040506070809UL
#define SL025_KEY_DEFAULT      0xFFFFFFFFFFFFUL

U8_t SL025_WorkedKeyA [6] = {1 , 2 , 3 , 4, 5  ,6};
U8_t SL025_WorkedKeyB [6] = {1 , 2 , 3 , 4, 5  ,6};
U8_t SL025_LockedKeyA [6] = {9 , 8 , 7 , 6, 5  ,4};
U8_t SL025_LockedKeyB [6] = {4 , 5 , 6 , 7, 8  ,9};
U8_t SL025_DefaultKey [6] = {0xFF, 0xFF,0xFF ,0xFF,0xFF,0xFF} ;

/****************************************************************************
* Function    : EF_BOOLEAN_RFID_Init(RFID_ModulesEnum ModuleType)
*
* DESCRIPTION : Initializes the RFID module
*
* PARAMETERS  : ModuleType: enum type for RFID module type
*
* Return Value: Initialization status
******************************************************************************/
BOOLEAN EF_BOOLEAN_RFID_Init (RFID_ModulesEnum ModuleType)
{
    U8_t ReturnStatus = TRUE;   /* Get the Return Status of function in it */

    switch (ModuleType)
    {
    case SLM025M_MODULE:
        EF_void_SLM025M_Init ();
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }
    return ReturnStatus;
}

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
U8_t EF_u8_RFID_IsCardExist (RFID_ModulesEnum ModuleType )
{
    U8_t ReturnStatus = 0;   /* Get the Return Status of function in it */

    switch (ModuleType)
    {
    case SLM025M_MODULE:
        ReturnStatus = EF_u8_SLM025M_IsCardExist ();
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }

    return ReturnStatus;
}

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
U8_t EF_u8_RFID_GetCardNumber (RFID_ModulesEnum ModuleType , U8_t* u8CardNumber_ptr ,U8_t* u8CardLength_ptr  )
{
    U8_t ReturnStatus = 0;   /* Get the Return Status of function in it */

    switch (ModuleType)
    {
    case SLM025M_MODULE:
        ReturnStatus = EF_u8_SLM025M_GetCardNumber (u8CardNumber_ptr, u8CardLength_ptr);
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }

    return ReturnStatus;
}

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
U8_t EF_u8_RFID_PrepareCard (RFID_ModulesEnum ModuleType )
{
    volatile U8_t ReturnStatus = 0;   /* Get the Return Status of function in it */
    volatile U8_t LoginStatus = 0;   /* Get the Return Status of function in it */

    U8_t Iterator     = 0;
    switch (ModuleType)
    {
    case SLM025M_MODULE:
        /* Locking All not worked blocked by defined locked key */
        while ((Iterator <= SL025_MAX_SECTOR_NUMBER)  )
        {
            LoginStatus = EF_u8_SLM025M_LoginSector (Iterator , KEY_TYPE_B,  SL025_DefaultKey);
            if (LoginStatus == SL025_LOGIN_SUCCEED)
            {
                ReturnStatus = EF_u8_SLM025M_UpdateAllKeys ( Iterator , SL025_LockedKeyA , SL025_LockedKeyB );
            }
            else
            {
                //todo break or check or indicator...
                //                return FALSE;
            }

            Iterator++;
            /* not to change in the Worked Sector */
            if (Iterator == SL025_WORKED_SECTOR)
            {
                Iterator++;
            }
        }
        LoginStatus = EF_u8_SLM025M_LoginSector (SL025_WORKED_SECTOR , KEY_TYPE_B,  SL025_DefaultKey);
        if (LoginStatus == SL025_LOGIN_SUCCEED)
        {
            ReturnStatus = EF_u8_SLM025M_UpdateAllKeys ( SL025_WORKED_SECTOR , SL025_WorkedKeyA , SL025_WorkedKeyB );
        }
        else
        {
            ReturnStatus = LoginStatus;
        }


        break;

    default:
        ReturnStatus = FALSE;
        break;
    }

    return ReturnStatus;
}

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
U8_t EF_u8_RFID_GetUserBalance (RFID_ModulesEnum ModuleType , U8_t * u8Balance_ptr )
{
    U8_t ReturnStatus = 0;   /* Get the Return Status of function in it */

    switch (ModuleType)
    {
    case SLM025M_MODULE:
        ReturnStatus = EF_u8_SLM025M_LoginSector (SL025_WORKED_SECTOR , KEY_TYPE_B,  SL025_WorkedKeyB);
        if (ReturnStatus == SL025_LOGIN_SUCCEED)
        {
            ReturnStatus = EF_u8_SLM025M_ReadDataValue (SL025_WORKED_SECTOR , SL025_WORKED_BLOCK, u8Balance_ptr);
        }
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }

    return ReturnStatus;


}

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
U8_t EF_u8_RFID_UpdateUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance )
{

    U8_t ReturnStatus = TRUE;   /* Get the Return Status of function in it */

    switch (ModuleType)
    {
    case SLM025M_MODULE:
        ReturnStatus = EF_u8_SLM025M_LoginSector (SL025_WORKED_SECTOR , KEY_TYPE_B,  SL025_WorkedKeyB);
        if (ReturnStatus == SL025_LOGIN_SUCCEED)
        {
            ReturnStatus = EF_u8_SLM025M_WriteDataValue (SL025_WORKED_SECTOR , SL025_WORKED_BLOCK, (U8_t*)&u16Balance);
        }
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }
    return ReturnStatus;

}

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
U8_t EF_u8_RFID_AddUserBalance (RFID_ModulesEnum ModuleType , U16_t u16Balance )
{
    U8_t ReturnStatus = TRUE;   /* Get the Return Status of function in it */
    U16_t u16GetBalance = 0;
    switch (ModuleType)
    {
    case SLM025M_MODULE:
        ReturnStatus = EF_u8_SLM025M_LoginSector (SL025_WORKED_SECTOR , KEY_TYPE_B,  SL025_WorkedKeyB);
        if (ReturnStatus == SL025_LOGIN_SUCCEED)
        {
            ReturnStatus = EF_u8_SLM025M_ReadDataValue (SL025_WORKED_SECTOR , SL025_WORKED_BLOCK, (U8_t*)&u16GetBalance);
            if (ReturnStatus == SL025_STATUS_SUCCEED)
            {
                u16Balance = u16Balance + u16GetBalance;
                ReturnStatus = EF_u8_SLM025M_WriteDataValue (SL025_WORKED_SECTOR , SL025_WORKED_BLOCK, (U8_t*)&u16Balance);
            }
        }
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }
    return ReturnStatus;
}

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
U8_t EF_u8_RFID_SubtractUserBalance (RFID_ModulesEnum ModuleType , U16_t u16SubtractedValue )
{
    U8_t ReturnStatus = TRUE;   /* Get the Return Status of function in it */
    U16_t u16GetBalance = 0;
    switch (ModuleType)
    {
    case SLM025M_MODULE:
        ReturnStatus = EF_u8_SLM025M_LoginSector (SL025_WORKED_SECTOR , KEY_TYPE_B,  SL025_WorkedKeyB);
        if (ReturnStatus == SL025_LOGIN_SUCCEED)
        {
            ReturnStatus = EF_u8_SLM025M_ReadDataValue (SL025_WORKED_SECTOR , SL025_WORKED_BLOCK, (U8_t*)&u16GetBalance);
            if (ReturnStatus == SL025_STATUS_SUCCEED)
            {
                if (u16SubtractedValue > u16GetBalance)
                {
                    //todo zeroing ??
                    return BALANCE_LOW_CANNOT_SUB;
                }
                u16SubtractedValue = u16GetBalance - u16SubtractedValue;
                ReturnStatus = EF_u8_SLM025M_WriteDataValue (SL025_WORKED_SECTOR , SL025_WORKED_BLOCK, (U8_t*)&u16SubtractedValue);
            }
        }
        break;

    default:
        ReturnStatus = FALSE;
        break;
    }
    return ReturnStatus;
}

