#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <string.h>
#include "UtilitiesLayer/std_types.h"
#include "UtilitiesLayer/EF_SpechialTIMER.h"
#include "MCAL/EF_TIVA_uart.h"
#include "MCAL/EF_TIVA_DIO.h"
#include "HAL/EF_SLM025M.h"
#include "HAL/EF_SLM025M_cfg.h"
#include "ServiceLayer/EF_RFID.h"
#include "ServiceLayer/EF_LcdMenus.h"
#include "ServiceLayer/EF_UserInterface.h"

#define SECTOR_MAX_COUNT                16
#define BLOCK_MAX_COUNT                  3 /* To avoid writing on keys */
#define BALANCE_SIZE                     4

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


int main(void)
{
    volatile U8_t u8ReturnStatus = 0;
    U8_t        u8CardNumber_ptr [7];
    U8_t        u8CardNumber_NoOfDigits;
    //    U8_t        u8Key_6HexBytes_ptr[6]   = {0xFF, 0xFF,0xFF ,0xFF,0xFF,0xFF} ;
    //    U8_t        u8DataPtr_16HexBytes[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //    U8_t        u8DataRead[16];
    //    U8_t        u8DataPtr_4HexBytes[4]   = {1, 2, 3 ,4} ;
    //    U8_t        u8Key_A_6HexBytes_ptr[6] = {1,2,3,4,5,6};
    //    U8_t        u8Key_Default[6]         = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    //    U8_t        u8Key_B_6HexBytes_ptr[6] = {6, 5, 4, 3, 2, 1};
    //    U8_t        u8Key_B_6HexBytes[6]     = {0,0,0,0,0,0};
    U8_t        u8index                  = 0;
    U8_t        u8CardExistence        = CARD_IS_NOT_DETECTED;
    //    U8_t        u8SectorCount          = 0;
    //    U8_t        u8BlockNumber          = 0;
    //    U8_t        u8UserBalance[4];
    //    U8_t        u8BalanceElement       = 0;
    U16_t       u16InsertedBalance     = 1000;
    U16_t       u16GetUserBalance      = 0;
    //    KeyTypeEnum eCardKey               = KEY_TYPE_A;


    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    void_InitConsole();

    EF_void_UserInterface_Init ();


    while (1)
    {
        EF_void_UserInterface_SystemStates ();

    }


    UARTprintf(" Testing SLM025 \n");

    //    u8CardExistence = EF_u8_RFID_IsCardExist(SLM025M_MODULE);
    //    if(u8CardExistence == CARD_IS_DETECTED)
    //    {
    //        UARTprintf("Card detected \n");
    //        EF_u8_RFID_PrepairCard(SLM025M_MODULE);
    //    }

    //    EF_u8_RFID_PrepareCard (SLM025M_MODULE);

    u8CardExistence = EF_u8_RFID_IsCardExist(SLM025M_MODULE);
    if(u8CardExistence == CARD_IS_DETECTED)
    {
        UARTprintf("Card detected \n");
        UARTprintf("Updating balance \n");
        u8ReturnStatus = EF_u8_RFID_UpdateUserBalance (SLM025M_MODULE, u16InsertedBalance);
        if(u8ReturnStatus == SL025_STATUS_SUCCEED)
        {
            UARTprintf("Reading Balance \n");
            u8ReturnStatus = EF_u8_RFID_GetUserBalance(SLM025M_MODULE, (U8_t*) &u16GetUserBalance);
            UARTprintf("Balance retrieved = \n");

            UARTprintf("%d, ", u16GetUserBalance);
        }
    }
    else
    {
        UARTprintf("Card not detected \n");
    }

    u8CardExistence = EF_u8_RFID_IsCardExist(SLM025M_MODULE);
    if(u8CardExistence == CARD_IS_DETECTED)
    {
        UARTprintf("Card detected \n");
        UARTprintf("Incrementing Balance \n");
        u8ReturnStatus = EF_u8_RFID_AddUserBalance(SLM025M_MODULE, 500);
        if(u8ReturnStatus == SL025_STATUS_SUCCEED)
        {
            UARTprintf("Getting balance \n");
            u8ReturnStatus = EF_u8_RFID_GetUserBalance(SLM025M_MODULE,  (U8_t*) &u16GetUserBalance);
            if(u8ReturnStatus == SL025_STATUS_SUCCEED)
            {
                UARTprintf("Balance retrieved = \n");
                UARTprintf("%d, ", u16GetUserBalance);
            }
        }
    }
    else
    {
        UARTprintf("Card not detected \n");
    }

    u8CardExistence = EF_u8_RFID_IsCardExist(SLM025M_MODULE);
    if(u8CardExistence == CARD_IS_DETECTED)
    {
        UARTprintf("Card detected \n");
        UARTprintf("decrementing Balance \n");
        u8ReturnStatus = EF_u8_RFID_SubtractUserBalance(SLM025M_MODULE, 1000);
        if(u8ReturnStatus == SL025_STATUS_SUCCEED)
        {
            UARTprintf("Getting balance \n");
            u8ReturnStatus = EF_u8_RFID_GetUserBalance(SLM025M_MODULE,  (U8_t*) &u16GetUserBalance);
            if(u8ReturnStatus == SL025_STATUS_SUCCEED)
            {
                UARTprintf("Balance retrieved = \n");
                UARTprintf("%d, ", u16GetUserBalance);

            }
        }
    }
    else
    {
        UARTprintf("Card not detected \n");
    }


    u8CardExistence = EF_u8_RFID_IsCardExist(SLM025M_MODULE);
    if(u8CardExistence == CARD_IS_DETECTED)
    {
        UARTprintf("Card detected \n");
        u8ReturnStatus = EF_u8_RFID_GetCardNumber(SLM025M_MODULE, u8CardNumber_ptr, &u8CardNumber_NoOfDigits);
        if (u8ReturnStatus == SL025_STATUS_SUCCEED)
        {
            for (u8index = 0; u8index < (u8CardNumber_NoOfDigits ) ; u8index++ )
            {
                UARTprintf("%X " , (int)*(u8CardNumber_ptr + u8index) );
            }
            UARTprintf("\n\n");
        }
        else if (u8ReturnStatus == FALSE)
        {
            UARTprintf("ERROR\n");
        }
        else if (u8ReturnStatus == SL025_NOT_FOUND_FRAME )
        {
            UARTprintf("Not Found\n");

        }
    }
    else
    {
        UARTprintf("Card not detected \n");
    }
    _delay_ms(200);


    while(1)
    {

    }

}


