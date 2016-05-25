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
#include "ServiceLayer/std_types.h"
#include "MCAL/EF_SpechialTIMER.h"
#include "MCAL/EF_TIVA_uart.h"
#include "MCAL/EF_TIVA_DIO.h"
#include "HAL/EF_RFID.h"
#include "HAL/EF_RFID_cfg.h"

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
    U8_t CardNumber_ptr [7] ;
    U8_t CardNumber_NoOfDigits ;
    U8_t Key_6HexBytes_ptr[6] = {0xFF, 0xFF,0xFF ,0xFF,0xFF,0xFF} ;
    U8_t DataPtr_16HexBytes[16];
    U8_t DataPtr_4HexBytes[4]= {1, 2, 3 ,4} ;
    U8_t Key_A_6HexBytes_ptr[6] = {1,2,3,4,5,6};
    U8_t Key_B_6HexBytes_ptr[6] = {6, 5, 4, 3, 2, 1};

    U8_t Key_B_6HexBytes[6] = {0,0,0,0,0,0};

    volatile U8_t ReturnStatus = 0;
    U8_t index = 0;
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    void_InitConsole();

    EF_void_TimerInit();
    EF_void_RFID_Init ();

    ReturnStatus = EF_u8_RFID_RedLedOn ();
    UARTprintf(" %d \n" , ReturnStatus );
    _delay_ms(500);

    ReturnStatus = EF_u8_RFID_RedLedOff ();
    UARTprintf(" %d \n" , ReturnStatus );
    _delay_ms(500);


    if (EF_S8_DIO_CheckPin (DETECT_CARD_PORT , DETECT_CARD_PIN) == CARD_IS_DETECTED)
    {
        ReturnStatus = EF_u8_RFID_LoginSector (10 , KEY_TYPE_B,  Key_B_6HexBytes);
        UARTprintf("login: %d \n" , ReturnStatus );
        if (ReturnStatus == LOGIN_SUCCEED)
        {
            ReturnStatus =EF_u8_RFID_UpdateMasterKey (10 , Key_A_6HexBytes_ptr  );
//            ReturnStatus = EF_u8_RFID_UpdateAllKeys ( 10 , Key_A_6HexBytes_ptr , Key_B_6HexBytes_ptr );

            UARTprintf("key status: %d \n" , ReturnStatus );
        }
    }
//
while (1)
{

}

    while (1)
    {
        if (EF_S8_DIO_CheckPin (DETECT_CARD_PORT , DETECT_CARD_PIN) == CARD_IS_DETECTED)
        {
            ReturnStatus = EF_u8_RFID_LoginSector (10 , KEY_TYPE_B,  Key_B_6HexBytes);
            UARTprintf("login: %d \n" , ReturnStatus );

            if (ReturnStatus == LOGIN_SUCCEED)
            {
                ReturnStatus =EF_u8_RFID_ReadDataBlock (10, 1,  DataPtr_16HexBytes  );
                UARTprintf("BLock 1 , Read: %d \n" , ReturnStatus );

                ReturnStatus = EF_u8_RFID_UpdateAllKeys ( 10 , Key_A_6HexBytes_ptr , Key_B_6HexBytes_ptr );
                UARTprintf("  %d \n" , ReturnStatus );

                ReturnStatus =EF_u8_RFID_WriteDataValue (10 , 1, DataPtr_4HexBytes  );
                UARTprintf("write value in block 1, status: %d \n" , ReturnStatus );

                ReturnStatus =EF_u8_RFID_ReadDataValue (10 , 2, DataPtr_4HexBytes  );
                UARTprintf("read data value, status: %d \n" , ReturnStatus );

                ReturnStatus =EF_u8_RFID_ReadDataValue (10 , 0, DataPtr_4HexBytes  );
                UARTprintf("read data value, status: %d \n" , ReturnStatus );

                ReturnStatus =EF_u8_RFID_ReadDataBlock (10, 1,  DataPtr_16HexBytes  );
                UARTprintf("BLock 0 , Read: %d \n" , ReturnStatus );
//
                ReturnStatus =EF_u8_RFID_ReadDataBlock (10, 0,  DataPtr_16HexBytes  );
                UARTprintf("BLock 0 , Read: %d \n" , ReturnStatus );
//
                ReturnStatus =EF_u8_RFID_WriteDataBlock (10 , 1, DataPtr_16HexBytes  );
                UARTprintf("write in block 1 from 0 , status: %d \n" , ReturnStatus );

            }
        }
        _delay_ms(1000);
    }

    while (1)
    {
        if (EF_S8_DIO_CheckPin (DETECT_CARD_PORT , DETECT_CARD_PIN) == CARD_IS_DETECTED)
        {
            ReturnStatus = EF_u8_RFID_GetCardNumber(CardNumber_ptr , &CardNumber_NoOfDigits);



            if (ReturnStatus == STATUS_SUCCEED)
            {
                for (index = 0; index < (CardNumber_NoOfDigits - 4) ; index++ )
                {
                    UARTprintf("%X " , (int)*(CardNumber_ptr + index) );
                }
                UARTprintf("\n\n");
            }
            else if (ReturnStatus == FALSE)
            {
                UARTprintf("ERROR\n");
            }
            else if (ReturnStatus == NOT_FOUND_FRAME )
            {
                UARTprintf("Not Found\n");

            }
        }
        _delay_ms(500);
    }

    ///////////////////

//    while (1)
//    {
//        if (EF_S8_DIO_CheckPin (DETECT_CARD_PORT , DETECT_CARD_PIN) == _FALSE)
//        {
//            EF_BOOLEAN_RFID_SendFrame (SELECT_MIFARE_CARD_CMD, Data_ptr, 0);
//
//            ReturnStatus = EF_u8_RFID_ReceiveFrame (Data_ptr);
//            if (ReturnStatus == TRUE)
//            {
//
//                //                UARTprintf("Rx: %s \n" , Data_ptr);
//            }
//            else if (ReturnStatus == _FALSE)
//            {
//                UARTprintf("ERROR\n");
//            }
//            else if (ReturnStatus == NOT_FOUND_FRAME )
//            {
//                UARTprintf("Not Found\n");
//
//            }
//        }
//        _delay_ms(500);
//    }
}


