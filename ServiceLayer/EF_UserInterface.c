/***************************************************************
 *  Source File: EF_UserInterface.c
 *
 *  Description: User Interface Module For Avon Project
 *               Using LCD, KeyPad and EEPROM
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
#include "EF_UserInterface.h"
#include "../HAL/EF_LCD.h"
#include "EF_UserInterface_cfg.h"
#include "EF_LcdMenus.h"
#include "EF_RFID.h"
#include "EF_RFID_cfg.h"
#include "../UtilitiesLayer/EF_SpechialTIMER.h"
#include "../UtilitiesLayer/std_types.h"
#include "../HAL/EF_KeyPad.h"
#include "../MCAL/EF_TIVA_EEPROM.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
/*************************************************************
 * Definitions
 **************************************************************/
#define PASSWORD_SIZE       4
#define MAX_BALANCE_SIZE    5
#define FIRST_RELEASE_FLAG_EEPROM_ADD    228        /* EEPROM ADD to save FirstRelease flag to init Some Varablies when First Realease only */
#define FIRST_RELEASE_FLAG_VALUE         55         /* Value in EEPROM to checked if it not saved --> init Some Varablies when First Realease only and save it */

/* Variables used in Switch Cases in EF_BOOLEAN_UI_ConfigureTolerance Function */
volatile static U8_t gEnumSystemStatus = WELCOME_STATE;
U32_t   u32HistoryCharge = 0;
U8_t u8pPasswordArray[PASSWORD_SIZE] = {1,2,3,4};
 U8_t u8pHistoryPassword[4] = {1,1,1,1};
/*************************************************************
 * Local Functions/Tasks/ System States
 **************************************************************/
static void void_InitConsole(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlDelay(5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlDelay(5);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 9600, 16000000);

}
/* -------------------------------- Calibration Tasks ------------------------------------- */



/*********************************************************************************/
/* ---------------------------API Functions--------------------------------------*/
/*********************************************************************************/

/*********************************************************************
 * Function    : void EF_void_UI_Init ();
 *
 * DESCRIPTION : This function used to Initialize Lcd,KeyPad and EEPROM
 *
 * PARAMETERS  : Void.
 *
 * Return Value: Void.
 ***********************************************************************/
void EF_void_UserInterface_Init ()
{
    U32_t FirstRelease_EEPROM = 0;

    /* Enable LCD */
    EF_void_LcdMenus_Init ();

    /* Enable UART Dubegger if need it (it was with UART power)*/
    void_InitConsole();

    /* Enable Timer Module */
    EF_void_TimerInit();

    /* Enable KeyPad Module */
    EF_void_KeyPad_Init ();

    EF_BOOLEAN_RFID_Init(SLM025M_MODULE);

    EF_BOOLEAN_EEPROM_Init();

    EF_BOOLEAN_EEPROM_ReadNBytes (&FirstRelease_EEPROM  , FIRST_RELEASE_FLAG_EEPROM_ADD , 4);
     if (FirstRelease_EEPROM != FIRST_RELEASE_FLAG_VALUE)
     {
         /* Save 100 in it noto enter here again */
         FirstRelease_EEPROM = FIRST_RELEASE_FLAG_VALUE;
         EF_BOOLEAN_EEPROM_WriteNBytes ( &FirstRelease_EEPROM  , FIRST_RELEASE_FLAG_EEPROM_ADD , 4);
         u32HistoryCharge = 0;
         EF_BOOLEAN_EEPROM_WriteNBytes (&u32HistoryCharge, 400 , 4);
     }
}


void EF_void_UserInterface_SystemStates ()
{
    volatile U8_t u8CardExistence = 0;
    volatile U8_t u8KeyPressed_Status = 0;
    static   U8_t u8UserSelection     = 0;
    static   U16_t u16UpdatedBalance  = 0;
    static   U8_t u8SelectionMenuState = 0;
    static   U8_t TempArray[PASSWORD_SIZE] = {0};
    static   U8_t ConfirmState    = CONFIRM_PRINT_STATE;
    static   U8_t u8HistorySwitch = 0;
    volatile U8_t u8ReturnStatus      = 0;
    static   U8_t u8ReadBalanceState   = 0;
    static   U8_t u8Iterator          = 0;
    static   U8_t u8EnterBalanceState = 0;
             U8_t u8CardNumber_ptr[7] = {0};
             U8_t u8CardNumber_NoOfDigits = 0;


    switch (gEnumSystemStatus)
    {
    case WELCOME_STATE :
        EF_void_LcdMenus_Welcome();
        gEnumSystemStatus = ENTER_CARD_STATE;
        break;

    case ENTER_CARD_STATE:
        EF_void_LcdMenus_EnterCard();
        gEnumSystemStatus = CHECK_CARD_STATE;
        break;

    case CHECK_CARD_STATE :
        u8CardExistence = EF_u8_RFID_IsCardExist(SLM025M_MODULE);
        if(u8CardExistence == CARD_IS_DETECTED)
        {
            u8ReturnStatus = EF_u8_RFID_GetCardNumber(SLM025M_MODULE, u8CardNumber_ptr, &u8CardNumber_NoOfDigits);
            if (u8ReturnStatus == SL025_STATUS_SUCCEED)
            {
                EF_void_LcdMenus_CardDeteced ();
                gEnumSystemStatus = SELECTION_STATE;
                u8SelectionMenuState = PRINT_SELECTION_MENU;
            }
        }
        break;

    case SELECTION_STATE :
        switch (u8SelectionMenuState)
        {
        case PRINT_SELECTION_MENU:
            EF_void_LcdMenus_Selection();
            u8SelectionMenuState = GET_KEYPAD_MENU;
            break;

        case GET_KEYPAD_MENU:
            u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();
              if (u8KeyPressed_Status != NOT_PRESSED)
              {
                  if ( (u8KeyPressed_Status == 1) || (u8KeyPressed_Status == 2) || (u8KeyPressed_Status == 3) )
                  {
                      u8UserSelection = u8KeyPressed_Status;
                      gEnumSystemStatus = ENTER_PASSWORD_STATE;
                      u8SelectionMenuState = PRINT_SELECTION_MENU;
                  }
                  else if (u8KeyPressed_Status == EXIT_KEY)
                  {
                      gEnumSystemStatus = ENTER_CARD_STATE;
                      u8SelectionMenuState = PRINT_SELECTION_MENU;
                  }
              }
            break;

        default:
            break;
        }
        break;

   case ENTER_PASSWORD_STATE:
       EF_void_LcdMenus_EnterPassword();
       gEnumSystemStatus = CHECK_PASSWORD;
       u8Iterator = 0;

       break;

   case CHECK_PASSWORD:
         u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();

         if (u8KeyPressed_Status != NOT_PRESSED)
         {
             /* return */
             if (u8KeyPressed_Status == EXIT_KEY)
             {
                 gEnumSystemStatus = ENTER_CARD_STATE;
             }
             /* enter */
             else if ( (u8KeyPressed_Status == ENTER_KEY) && (u8Iterator == PASSWORD_SIZE) )
             {
                 /* Check Password */
//                 EF_BOOLEAN_EEPROM_ReadNBytes((U32_t *)&u8pTempArray, 400 , PASSWORD_SIZE);
                 /* compare */
                 for (u8Iterator = 0; u8Iterator < PASSWORD_SIZE; u8Iterator++)
                 {
                     if ((u8UserSelection == 3) &&  ( u8pHistoryPassword[u8Iterator] != TempArray [u8Iterator]) )
                     {
                         EF_void_LcdMenus_WrongPassword();
                         gEnumSystemStatus = ENTER_PASSWORD_STATE;
                         return;
                     }
                     else if ( ((u8UserSelection == 2)||(u8UserSelection == 1) )&& ( u8pPasswordArray[u8Iterator] != TempArray [u8Iterator]) )
                     {
                         EF_void_LcdMenus_WrongPassword();
                         gEnumSystemStatus = ENTER_PASSWORD_STATE;
                         return;
                     }
                 }

                 EF_void_LcdMenus_RightPassword();

                 if ( u8UserSelection == 1)
                 {
                     gEnumSystemStatus = CHANGE_BALANCE_STATE;
                     u8EnterBalanceState = PRINT_ENTER_BALANCE;
                 }
                 else if (u8UserSelection == 2)
                 {
                     gEnumSystemStatus = READ_BALANCE_STATE;
                     u8ReadBalanceState = PRINT_READ_BALANCE;
                 }
                 else if (u8UserSelection == 3)
                 {
                     gEnumSystemStatus = CHARGE_HISTORY_STATE;
                     u8HistorySwitch = PRINT_HISTORY_STATE;
                 }
                 /* zeroing the Array */
                 for (u8Iterator = 0; u8Iterator < PASSWORD_SIZE; u8Iterator++)
                 {
                     TempArray[u8Iterator] = 0;
                 }
             }
             else
             {
                 if (u8Iterator != PASSWORD_SIZE)
                 {
//                     EF_void_LCD_send_data (u8KeyPressed_Status + '0');
                     EF_void_LCD_send_data ('*');
                     TempArray[u8Iterator] = u8KeyPressed_Status;
                     u8Iterator++;
                 }
             }
         }


        break;

   case CHANGE_BALANCE_STATE :
       switch (u8EnterBalanceState )
       {
       case PRINT_ENTER_BALANCE:
           EF_void_LcdMenus_EnterBalance();
           u8EnterBalanceState = ADD_BALANCE_KEYPAD;
           u8Iterator        = 0;
           u16UpdatedBalance = 0;
           break;

       case ADD_BALANCE_KEYPAD:
           u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();

            if (u8KeyPressed_Status != NOT_PRESSED)
            {
                /* return */
                if (u8KeyPressed_Status == EXIT_KEY)
                {
                    gEnumSystemStatus = SELECTION_STATE;
                    u8EnterBalanceState = PRINT_ENTER_BALANCE;
                }
                /* enter */
                else if ( (u8KeyPressed_Status == ENTER_KEY) && (u16UpdatedBalance > 0))
                {
                    gEnumSystemStatus = CONFIRM_BALANCE_STATE;
                    u8EnterBalanceState = PRINT_ENTER_BALANCE;
                    ConfirmState    = CONFIRM_PRINT_STATE;
                }
                else
                {
                    if (u8Iterator != MAX_BALANCE_SIZE)
                    {
                        EF_void_LCD_send_data (u8KeyPressed_Status + '0');
                        u16UpdatedBalance = u8KeyPressed_Status + (u16UpdatedBalance * 10);
                        u8Iterator++;
                    }
                }
            }
           break;
       }
         break;

   case CONFIRM_BALANCE_STATE:
       switch (ConfirmState)
       {
       case CONFIRM_PRINT_STATE:
           EF_void_LcdMenus_ConfirmBalance();
           ConfirmState = CONFIRM_GET_KEYPAD_STATE;
           break;

       case CONFIRM_GET_KEYPAD_STATE :
           u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();

            if (u8KeyPressed_Status != NOT_PRESSED)
            {
                if ( (u8KeyPressed_Status == ENTER_KEY) )
                {
                    u8ReturnStatus = EF_u8_RFID_AddUserBalance (SLM025M_MODULE,u16UpdatedBalance);
                    EF_BOOLEAN_EEPROM_ReadNBytes  ( &u32HistoryCharge, 400 , 4);
                    u32HistoryCharge += u16UpdatedBalance;
                    EF_BOOLEAN_EEPROM_WriteNBytes ( &u32HistoryCharge, 400 , 4);
                    if ( u8ReturnStatus == SL025_STATUS_SUCCEED )
                    {
                        gEnumSystemStatus = UPDATED_BALANCE_STATE;
                    }
                    else
                    {
                        EF_void_LcdMenus_CardRemoved();
                        ConfirmState = CONFIRM_PRINT_STATE;
                    }
                }
                else if ((u8KeyPressed_Status == EXIT_KEY))
                {
                    gEnumSystemStatus = CHANGE_BALANCE_STATE;
                }
            }
           break;

       default:
           break;
       }
        break;

   case READ_BALANCE_STATE:
       u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();

        if (u8KeyPressed_Status == EXIT_KEY)
        {
            gEnumSystemStatus = SELECTION_STATE;
        }
       switch (u8ReadBalanceState)
       {
       case PRINT_READ_BALANCE:
           EF_void_LcdMenus_GetBalance();
           u8ReadBalanceState = READ_RFID_STATE;
           break;

       case READ_RFID_STATE:
           u8ReturnStatus = EF_u8_RFID_GetUserBalance ( SLM025M_MODULE, (U8_t*) &u16UpdatedBalance);
           if(u8ReturnStatus == SL025_STATUS_SUCCEED)
           {
               EF_void_LCD_print_NUM (u16UpdatedBalance, 2 ,1);
               u8ReadBalanceState = WAIT_KEYPAD_STATE;
           }
           else
           {
               _delay_ms(500);
               EF_void_LcdMenus_CardRemoved();
               u8ReadBalanceState = PRINT_READ_BALANCE;
           }
           break;

       case WAIT_KEYPAD_STATE:
           u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();

            if (u8KeyPressed_Status != NOT_PRESSED)
            {
                gEnumSystemStatus = ENTER_CARD_STATE;
                u8ReadBalanceState = PRINT_READ_BALANCE;
            }
           break;

       default:
           break;
       }

        break;

   case UPDATED_BALANCE_STATE:
       EF_void_LcdMenus_BalanceUpdated();
       gEnumSystemStatus = ENTER_CARD_STATE;
       break;

   case CHARGE_HISTORY_STATE:
       switch ( u8HistorySwitch )
       {
       case PRINT_HISTORY_STATE:
           EF_void_LcdMenus_ChargeHistory();
           EF_BOOLEAN_EEPROM_ReadNBytes  ( &u32HistoryCharge, 400 , 4);
           u32HistoryCharge += u16UpdatedBalance;
           EF_BOOLEAN_EEPROM_WriteNBytes ( &u32HistoryCharge, 400 , 4);
           EF_void_LCD_print_NUM (u32HistoryCharge , 2, 1);
           u8HistorySwitch = WAIT_PRESSED_STATE;
           break;

       case WAIT_PRESSED_STATE:
           u8KeyPressed_Status = EF_u8_KeyPad_GetKeyAfterReleasing ();

            if (u8KeyPressed_Status != NOT_PRESSED)
            {
                gEnumSystemStatus = ENTER_CARD_STATE;
                u8HistorySwitch = PRINT_HISTORY_STATE;
            }
           break;

       default:
           break;
       }

       break;

   default :
        break;
    }
}
