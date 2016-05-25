/*
 * EF_SLM025.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Kareem
 */

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
#include "../ServiceLayer/std_types.h"
#include "../MCAL/EF_TIVA_DIO.h"
#include "../MCAL/EF_TIVA_uart.h"

#include "EF_RFID.h"
#include "EF_RFID_cfg.h"


UART_cfg_str  uart_cfg = {UART5, 9600, NUMBER_OF_BITS_8, ONE_STOP_BIT,NO_PARITY,FALSE,FALSE,TRUE,TRUE};

static U8_t Calc_CheckSum(U8_t * Data_ptr, U8_t DataLength)
{
    U8_t DataCheckSum   = 0;
    U8_t CheckSumIndex  = 0;
    U8_t CheckSumLength = 0;


    CheckSumLength = DataLength + 3;
    for(CheckSumIndex= 0; CheckSumIndex < CheckSumLength; CheckSumIndex++)
    {
        DataCheckSum ^= Data_ptr[CheckSumIndex];
    }

    return DataCheckSum;
}


static U8_t UpdateCmdLenght(U8_t CMD)
{
    U8_t CMD_LENGTH = 0;

    switch(CMD)
    {
    case READ_DATA_BLOCK_CMD:
    case READ_DATA_VALUE_CMD:
    case MANAGE_RED_LED_CMD:
        CMD_LENGTH = 0x03;
        break;
    case SELECT_MIFARE_CARD_CMD:
    case GET_FIRMWARE_VERSION:
        CMD_LENGTH = 0x02;
        break;
    case DECREMENT_VALUE_CMD:
    case INCREMENT_VALUE_CMD:
    case WRITE_DATA_VALUE_CMD:
        CMD_LENGTH = 0x07;
        break;
    case LOGIN_SECTOR_CMD:
    case DOWNLOAD_KEY_CMD:
        CMD_LENGTH = 0x0A;
        break;
    case LOGIN_SECTOR_STORED_KEY_CMD:
    case COPY_VALUE_CMD:
        CMD_LENGTH = 0x04;
        break;
    case WRITE_MASTER_KEY_CMD:
        CMD_LENGTH = 0x09;
        break;
    case WRITE_DATA_BLOCK_CMD:
        CMD_LENGTH = 19;
        break;
    default:
        CMD_LENGTH = WRONG_CMD;
        break;
    }
    return CMD_LENGTH;
}


/****************************************************************************
* Function    : EF_BOOLEAN_RFID_SendFrame (U8_t CMD, U8_t * Data_ptr, U8_t DataLength)
*
* DESCRIPTION : Send Frame to RFID card via Uart. Frame structure: [Preamble|Len|Command|Data(if found)|Checksum]
*
* PARAMETERS  : CMD         : Command Number.
*               Data_ptr    : Pointer to wanted data to be Send
*               DataLength  : Length of Sent Data
*
* Return Value: 0x01: TRUE
*               0x00: FALSE if Command is wrong.
******************************************************************************/
static BOOLEAN EF_BOOLEAN_RFID_SendFrame (U8_t CMD, U8_t * Data_ptr, U8_t DataLength)
{
    U8_t Index         = 0;
    U8_t CMDLength     = 0;
    U8_t FrameCheckSum = 0;
    U8_t command_array[MAX_SEND_CMD_LENGTH];

    command_array[PREAMBLE_INDEX]   = HOST_SL025_PREAMBLE;
    /* get Command Length*/
    CMDLength       = UpdateCmdLenght(CMD);
    if (CMDLength == WRONG_CMD)
    {
        return FALSE;
    }
    command_array[CMD_LENGTH_INDEX] = CMDLength;
    /* add The Command */
    command_array[CMD_INDEX]        = CMD;
    /* add Data if found */
    if((FALSE !=DataLength) && (NULL != Data_ptr))
    {
        for (Index = 0; Index < DataLength; Index++)
        {
            command_array[DATA_INDEX + Index] =  *Data_ptr;
            Data_ptr++;
        }
    }
    /* add The checkSum */
    FrameCheckSum = Calc_CheckSum(&command_array[PREAMBLE_INDEX], DataLength);
    command_array[CMDLength + 1]     = FrameCheckSum;
    /* Send the Frame */
    //todo or not ?
    EF_void_UART_Init(&uart_cfg);

    EF_void_UART_SendArray( UART5 , command_array, (CMDLength + 2));
    UARTprintf("\n");
    UARTprintf("TX :  \"");
    for (Index = 0; Index < (command_array[CMD_LENGTH_INDEX] + 2) ; Index++ )
    {
        UARTprintf("%X " , *(command_array + Index) );
    }
    UARTprintf("\n");
    return TRUE;
}



/****************************************************************************
* Function    : EF_u8_RFID_ReceiveFrame (U8_t * RxData_ptr )
*
* DESCRIPTION : Receive Frame from RFID card via Uart. Frame structure: [Preamble|Len|Command|Status|Data(if found)|Checksum]
*
* PARAMETERS  : Data_ptr : Pointer to Receiving Data
*
* Return Value: 0x01: TRUE
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : you should Send Frame first then Get the Response
******************************************************************************/
static U8_t EF_u8_RFID_ReceiveFrame (U8_t * RxData_ptr )
{
    BOOLEAN b_ReturnStatus = 0,index;
    U8_t command_array[MAX_SEND_CMD_LENGTH];

    /* Get the Preample */
    EF_BOOLEAN_UART_GetChar( UART5, &command_array[PREAMBLE_INDEX] );
    /* if Preample was rigth, get the Frame ,else Return NOT_FOUND_FRAME*/
    if(SL025_HOST_PREAMBLE == command_array[PREAMBLE_INDEX])
    {
        b_ReturnStatus = EF_BOOLEAN_UART_GetChar( UART5, &command_array[CMD_LENGTH_INDEX] );

        if( (command_array[CMD_LENGTH_INDEX] >= MIN_RECEIVED_LENGTH) && (b_ReturnStatus == TRUE) )
        {
            b_ReturnStatus = EF_BOOLEAN_UART_GetArrayByLength(UART5 , command_array, command_array[CMD_LENGTH_INDEX]);

            EF_ArrayCopy (RxData_ptr, command_array, (command_array[CMD_LENGTH_INDEX] + 2)  );

            UARTprintf("\n");
            UARTprintf("RX Array is :  \"");
            for (index = 0; index < (RxData_ptr[CMD_LENGTH_INDEX] + 2) ; index++ )
            {
                UARTprintf("%X " , (int)*(RxData_ptr + index) );
//                _delay_ms(1);
            }
            UARTprintf("\n");
//            _delay_ms(1);

        }

    }
    else
    {
        b_ReturnStatus = NOT_FOUND_FRAME;
    }
    return b_ReturnStatus;
}

/****************************************************************************
* Function    : EF_void_RFID_Init ();
*
* DESCRIPTION : init the Uart For RFID Module SLM025M and init Card detected Pin
*
* PARAMETERS  : None.
*
* Return Value: None.
******************************************************************************/
void EF_void_RFID_Init ()
{

    EF_void_UART_Init(&uart_cfg);

    EF_S8_t_DIO_InitPin (DETECT_CARD_PORT , DETECT_CARD_PIN , INPUT);
    GPIOPadConfigSet (DETECT_CARD_GPIO_BASE, DETECT_CARD_GPIO_PIN, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
}





/****************************************************************************
* Function    : EF_u8_RFID_GetCardNumber (U8_t* CardNumber_ptr ,U8_t* CardNumber_NoOFDigits);
*
* DESCRIPTION : Get Card Number with it's length.
*
* PARAMETERS  : CardNumber_ptr        : Pointer to the Return CardNumber.
*               CardNumber_NoOFDigits : Pointer to Card Length, the old standard is 4 bytes and the new is 7bytes.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*******************************************************************************/
U8_t EF_u8_RFID_GetCardNumber (U8_t* CardNumber_ptr ,U8_t* CardNumber_NoOFDigits)
{
    volatile U8_t ReturnStatus = 0;
    U8_t SendData_ptr[MAX_RECEIVED_LENGTH] ;

    /* Send Frame: [0xBA Len 0x01 Checksum] */
    ReturnStatus = EF_BOOLEAN_RFID_SendFrame (SELECT_MIFARE_CARD_CMD, SendData_ptr, 0);

    if (ReturnStatus == TRUE)
    {
//        _delay_ms(10);
        ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
        if (ReturnStatus == TRUE)
        {
            ReturnStatus = SendData_ptr[STATUS_INDEX];
            /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
            if (ReturnStatus == OPERATION_SUCCEED)
            {
                ReturnStatus = STATUS_SUCCEED;
                /* Extract CardId , RxFrame [0xBD|Len|0x01|Status|UID(7 or 4bytes)|Type|Checksum] */
                if (SendData_ptr[CMD_LENGTH_INDEX] == 8)
                {
                    EF_ArrayCopy (CardNumber_ptr, &SendData_ptr[RX_CARD_DATA_INDEX], 4 );
                }
                else if  (SendData_ptr[CMD_LENGTH_INDEX] == 11)
                {
                    EF_ArrayCopy (CardNumber_ptr, &SendData_ptr[RX_CARD_DATA_INDEX], 7 );
                }
                else
                {
                    ReturnStatus = FALSE;
                }
                *CardNumber_NoOFDigits = SendData_ptr[CMD_LENGTH_INDEX];
            }
        }
    }

    return ReturnStatus;
}



/****************************************************************************
* Function    : EF_u8_RFID_LoginSector (U8_t SectorNumber, KeyTypeEnum KeyType, U8_t* Key_6HexBytes_ptr  );
*
* DESCRIPTION : Get Card Number with it's length.
*
* PARAMETERS  : SectorNumber     : Number of Sector from 0 to 15.
*               KeyType          : define it was KeyA or KeyB take one of the KeyTypeEnum
*               Key_6HexBytes_ptr: Pointer to Key (6 Bytes) to login via it.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x03: LOGIN_FAIL
*               0x08: ADD_OVERFLOW
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - RFID has 16 sector(0 to 15), every Sector has 4 block and has it's Special and Seperate KeyA and KeyB.
*               - Every Block has 16 bytes.
*               - KeyA and KeyB are saved in the last block ( Block 3) .
*               - Key A(Master Key :More Secured) and B (not Secured), the Default of them: "FF FF FF FF FF FF"
******************************************************************************/
U8_t EF_u8_RFID_LoginSector (U8_t SectorNumber, KeyTypeEnum KeyType, U8_t* Key_6HexBytes_ptr )
{
    volatile U8_t ReturnStatus = 0;

    /* Send Frame: [0xBA|Len|0x02|Sector|Type|Key|Checksum] */
    U8_t SendData_ptr[LOGIN_SECTOR_DATA_LENGTH];
    SendData_ptr[0] = SectorNumber;
    SendData_ptr[1] = KeyType;
    /* Check for KeyType and SectorNumber */
    if ( (SectorNumber > MAX_SECTOR_NUMBER) || ( (KeyType !=KEY_TYPE_A) && (KeyType != KEY_TYPE_B) ))
    {
        return FALSE;
    }
    EF_ArrayCopy(&SendData_ptr[2], Key_6HexBytes_ptr, LOGIN_SECTOR_DATA_LENGTH-2);

    ReturnStatus = EF_BOOLEAN_RFID_SendFrame (LOGIN_SECTOR_CMD, SendData_ptr, LOGIN_SECTOR_DATA_LENGTH);

    if (ReturnStatus == TRUE)
    {
        ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
        if (ReturnStatus == TRUE)
        {
            ReturnStatus = SendData_ptr[STATUS_INDEX];
        }
    }

    return ReturnStatus;
}



/****************************************************************************
* Function    : EF_u8_RFID_UpdateMasterKey (U8_t SectorNumber , U8_t* KeyA_6HexBytes  );
*
* DESCRIPTION : Update Master Key (A).
*
* PARAMETERS  : SectorNumber     : Number of Sector from 0 to 15.
*               Key_6HexBytes_ptr: Pointer to Key A (6 Bytes) to login via it.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x05: WRITE_FAIL
*               0x08: ADD_OVERFLOW
*               0x0D: NOT_AUTHENTICATE
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - you should Login to the Wanted Sector Before this Function.
*               - After Changing KeyA:
*                   . Key B will be Zeros.
*                   . Key A will be used to read block or Value and Can't be used for write Block or value or Update Master Key
*                   . if you want to write block/value/MasterKey , use KeyB.
******************************************************************************/
U8_t EF_u8_RFID_UpdateMasterKey (U8_t SectorNumber , U8_t* KeyA_6HexBytes_ptr  )
{
    volatile U8_t ReturnStatus = 0;

    /* Send Frame: [0xBA Len 0x07 Sector Key Checksum]*/

    U8_t SendData_ptr[WRITE_MASTER_KEY_DATA_LENGTH] ;
    SendData_ptr[0] = SectorNumber;
    /* Check for KeyType and SectorNumber */
    if ( SectorNumber > MAX_SECTOR_NUMBER )
    {
        return FALSE;
    }
//
//    for (iterator = 1; iterator < WRITE_MASTER_KEY_DATA_LENGTH ; iterator++ )
//    {
//        SendData_ptr[iterator] = (U8_t) (Key_6HexBytes_ptr >>(WRITE_MASTER_KEY_DATA_LENGTH -1         - iterator)*8 );
//    }
    EF_ArrayCopy(&SendData_ptr[1], KeyA_6HexBytes_ptr, WRITE_MASTER_KEY_DATA_LENGTH-1);

    ReturnStatus = EF_BOOLEAN_RFID_SendFrame (WRITE_MASTER_KEY_CMD, SendData_ptr, WRITE_MASTER_KEY_DATA_LENGTH);

    if (ReturnStatus == TRUE)
    {
        ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
        if (ReturnStatus == TRUE)
        {
            ReturnStatus = SendData_ptr[STATUS_INDEX];
            /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
            if (ReturnStatus == OPERATION_SUCCEED)
            {
                ReturnStatus = STATUS_SUCCEED;
            }
        }
    }

    return ReturnStatus;
}


/****************************************************************************
* Function    : EF_u8_RFID_UpdateAllKeys ( U8_t SectorNumber , U8_t* Key_A_6HexBytes , U8_t* Key_B_6HexBytes );
*
* DESCRIPTION : Update All Keys (A) and (B) for Defined Sector as every Sector has it's Own Keys.
*
* PARAMETERS  : SectorNumber     : Number of Sector from 0 to 15.
*               Key_A_6HexBytes: Pointer to New Key A (6 Bytes).
*               Key_B_6HexBytes: Pointer to New Key B (6 Bytes).
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x05: WRITE_FAIL
*               0x06: UNABLE_READ_AFTER_WRITE
*               0x0D: NOT_AUTHENTICATE
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - you should Login to the Wanted Sector Before this Function.
*               - KeyA and KeyB are saved in the last block (Block 3) in every Sector.
*               - if this Operation Ok, Key A and KeyB changed and needed to login again with new Keys
*               - if you read block 3 again KeyA and KeyB will return 0
******************************************************************************/
U8_t EF_u8_RFID_UpdateAllKeys ( U8_t SectorNumber , U8_t* Key_A_6HexBytes_ptr , U8_t* Key_B_6HexBytes_ptr )
{

    volatile U8_t ReturnStatus = 0;

     U8_t SendData_ptr[UPDATE_KEYS_DATA_LENGTH];
     /* write in Block 3 this data:  [keyA(6Bytes)|08 77 8F 00|keyb(6Bytes)] */
     /* Insert KeyA in SendData_ptr  */
//     for (iterator = 0; iterator < 6 ; iterator++ )
//     {
//         SendData_ptr[iterator] = (U8_t) (Key_A_6HexBytes_ptr >>(6 -1         - iterator)*8 );
//     }
     EF_ArrayCopy(&SendData_ptr[0], Key_A_6HexBytes_ptr, KEY_LENGTH);

     /* ( 4 bits: Access Bits) , if writning to the Block 3 without this Access bits you may be unable to access this Sector again */
     SendData_ptr[6] = 0x08;
     SendData_ptr[7] = 0x77;
     SendData_ptr[8] = 0x8F;
     SendData_ptr[9] = 0x00;
     /* Insert KeyB in SendData_ptr */
//     for (iterator = 10; iterator < UPDATE_KEYS_DATA_LENGTH ; iterator++ )
//     {
//         SendData_ptr[iterator] = (U8_t) (Key_B_6HexBytes_ptr >>(UPDATE_KEYS_DATA_LENGTH -1         - iterator)*8 );
//     }
     EF_ArrayCopy(&SendData_ptr[10], Key_B_6HexBytes_ptr, KEY_LENGTH);

     ReturnStatus = EF_u8_RFID_WriteDataBlock (SectorNumber, 3 , SendData_ptr);
     return ReturnStatus;
}


/****************************************************************************
* Function    : EF_u8_RFID_WriteDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_16HexBytes  );
*
* DESCRIPTION : Write Data Block (16 bytes) in Defined Sector in defined Block.
*
* PARAMETERS  : SectorNumber      : Number of Sector from 0 to 15.
*               BlockNumber       : Block Number from 0 to 4.
*               DataPtr_16HexBytes: Pointer to Wanted data to be Written  (16 bytes).
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x05: WRITE_FAIL
*               0x06: UNABLE_READ_AFTER_WRITE
*               0x0D: NOT_AUTHENTICATE
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - you should Login to the Wanted Sector Before this Function.
*               - Every Block has 16 bytes.
******************************************************************************/
U8_t EF_u8_RFID_WriteDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_16HexBytes  )
{
    volatile U8_t ReturnStatus = 0;

     U8_t SendData_ptr[WRITE_BLOCK_DATA_LENGTH];

     /* Check for BlockNumber and SectorNumber */
     if ( (SectorNumber > MAX_SECTOR_NUMBER) || (BlockNumber > MAX_BLOCK_NUMBER ) )
     {
         return FALSE;
     }

     BlockNumber = ( SectorNumber * 4 ) + BlockNumber;
     /* Send Frame: [0xBA Len 0x04 Block Data Checksum]*/
     SendData_ptr[0] = BlockNumber;
     EF_ArrayCopy(&SendData_ptr[1], DataPtr_16HexBytes, WRITE_BLOCK_DATA_LENGTH-1);


     ReturnStatus = EF_BOOLEAN_RFID_SendFrame (WRITE_DATA_BLOCK_CMD, SendData_ptr, WRITE_BLOCK_DATA_LENGTH);

     if (ReturnStatus == TRUE)
     {
         ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
         if (ReturnStatus == TRUE)
         {
             ReturnStatus = SendData_ptr[STATUS_INDEX];
             /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
             if (ReturnStatus == OPERATION_SUCCEED)
             {
                 ReturnStatus = STATUS_SUCCEED;
             }
         }
     }

     return ReturnStatus;
}


/****************************************************************************
* Function    : EF_u8_RFID_WriteDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_4HexBytes  );
*
* DESCRIPTION : Write Data Value in Defined Sector in defined Block.
*
* PARAMETERS  : SectorNumber      : Number of Sector from 0 to 15.
*               BlockNumber       : Block Number from 0 to 4.
*               DataPtr_4HexBytes : Pointer to Wanted data to be Written (4 bytes).
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x05: WRITE_FAIL
*               0x06: UNABLE_READ_AFTER_WRITE
*               0x0D: NOT_AUTHENTICATE
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - you should Login to the Wanted Sector Before this Function.
*               - Data was written in the First 4 Addressess in the Wanted Block
*               - if Written are Ok, All the Block data will changed!
*               - Take Care: Block 3 has Key A in the First 6 bytes, you Will OverWrite on it if block3 is used.
*               - if read a block then Write in this block after reading, it may return UNABLE_READ_AFTER_WRITE
******************************************************************************/
U8_t EF_u8_RFID_WriteDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_4HexBytes  )
{
    volatile U8_t ReturnStatus = 0;
     U8_t SendData_ptr[WRITE_VALUE_DATA_LENGTH];


     /* Check for BlockNumber and SectorNumber */
     if ( (SectorNumber > MAX_SECTOR_NUMBER) || (BlockNumber > MAX_BLOCK_NUMBER ) )
     {
         return FALSE;
     }
     BlockNumber = ( SectorNumber * 4 ) + BlockNumber;
     SendData_ptr[0] = BlockNumber;

     EF_ArrayCopy(&SendData_ptr[1], DataPtr_4HexBytes, WRITE_VALUE_DATA_LENGTH-1);

     /* Send Frame: [0xBA Len 0x04 Block Data Checksum]*/
     ReturnStatus = EF_BOOLEAN_RFID_SendFrame (WRITE_DATA_VALUE_CMD, SendData_ptr, WRITE_VALUE_DATA_LENGTH);

     if (ReturnStatus == TRUE)
     {
         ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
         if (ReturnStatus == TRUE)
         {
             ReturnStatus = SendData_ptr[STATUS_INDEX];
             /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
             if (ReturnStatus == OPERATION_SUCCEED)
             {
                 ReturnStatus = STATUS_SUCCEED;
             }
         }
     }

     return ReturnStatus;
}




/****************************************************************************
* Function    : EF_u8_RFID_ReadDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_16HexBytes  );
*
* DESCRIPTION : Read Data Block in Defined Sector in defined Block.
*
* PARAMETERS  : SectorNumber       : Number of Sector from 0 to 15.
*               BlockNumber        : Block Number from 0 to 4.
*               DataPtr_16HexBytes : Pointer to Wanted data to be Written (4 bytes).
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x04: READ_FAIL
*               0x0D: NOT_AUTHENTICATE
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - you should Login to the Wanted Sector Before this Function.
*               - Block 3 has Key A in the First 6 bytes then Access Bits then Key B,
*                it will return zeros in Key A and return Default Values of Key B if it wasn't changed, if
*                Key B was changed then it will return zeros in Key B.
******************************************************************************/
U8_t EF_u8_RFID_ReadDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_16HexBytes)
{
    volatile U8_t ReturnStatus = 0;
             U8_t SendData_ptr[MAX_SEND_CMD_LENGTH];

     /* Check for BlockNumber and SectorNumber */
     if ( (SectorNumber > MAX_SECTOR_NUMBER) || (BlockNumber > MAX_BLOCK_NUMBER ) || (DataPtr_16HexBytes == (U8_t *)NULL) )
     {
         return FALSE;
     }

     BlockNumber = ( SectorNumber * 4 ) + BlockNumber;

     /* Send Frame: [0xBA Len 0x03 Block Checksum]*/
     ReturnStatus = EF_BOOLEAN_RFID_SendFrame (READ_DATA_BLOCK_CMD, &BlockNumber, READ_DATA_LENGTH);

     if (ReturnStatus == TRUE)
     {
         ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
         if (ReturnStatus == TRUE)
         {
             /* RxFrame : [0xBD Len 0x04 Status Data Checksum]*/
             EF_ArrayCopy(DataPtr_16HexBytes, (SendData_ptr + READ_DATA_INDEX), BLOCK_DATA_LENGTH);

             ReturnStatus = SendData_ptr[STATUS_INDEX];
             /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
             if (ReturnStatus == OPERATION_SUCCEED)
             {
                 ReturnStatus = STATUS_SUCCEED;
             }
         }
     }

     return ReturnStatus;
}



/****************************************************************************
* Function    : EF_u8_RFID_ReadDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_4HexBytes  );
*
* DESCRIPTION : Read Data Value in Defined Sector in defined Block.
*
* PARAMETERS  : SectorNumber      : Number of Sector from 0 to 15.
*               BlockNumber       : Block Number from 0 to 4.
*               DataPtr_4HexBytes : Pointer to Wanted data to be Written (4 bytes).
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0x01: NO_TAG
*               0x04: READ_FAIL
*               0x0D: NOT_AUTHENTICATE
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*
* NOTE        : - you should Login to the Wanted Sector Before this Function.
*               - Block 3 has Key A in the First 6 bytes, it will return zeros if read it.
******************************************************************************/
U8_t EF_u8_RFID_ReadDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* DataPtr_4HexBytes  )
{
    volatile U8_t ReturnStatus = 0;
     U8_t SendData_ptr[MAX_SEND_CMD_LENGTH];

     /* Check for BlockNumber and SectorNumber */
     if ( (SectorNumber > MAX_SECTOR_NUMBER) || (BlockNumber > MAX_BLOCK_NUMBER ) || (DataPtr_4HexBytes == (U8_t *)NULL) )
     {
         return FALSE;
     }
     BlockNumber = ( SectorNumber * 4 ) + BlockNumber;

     /* Send Frame: [0xBA Len 0x03 Block Checksum]*/
     ReturnStatus = EF_BOOLEAN_RFID_SendFrame (READ_DATA_VALUE_CMD, &BlockNumber, READ_DATA_LENGTH);

     if (ReturnStatus == TRUE)
     {
         ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
         if (ReturnStatus == TRUE)
         {
             /* RxFrame : [0xBD Len 0x04 Status Data Checksum]*/
             //todo test it
             EF_ArrayCopy(DataPtr_4HexBytes, (SendData_ptr + READ_DATA_INDEX), VALUE_LENGTH);

             ReturnStatus = SendData_ptr[STATUS_INDEX];
             /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
             if (ReturnStatus == OPERATION_SUCCEED)
             {
                 ReturnStatus = STATUS_SUCCEED;
             }
         }
     }

     return ReturnStatus;
}

/****************************************************************************
* Function    : EF_u8_RFID_RedLedOn ();
*
* DESCRIPTION : Turn on the Red LEd on the RFID Card.
*
* PARAMETERS  : None.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*******************************************************************************/
U8_t EF_u8_RFID_RedLedOn ()
{
    volatile U8_t ReturnStatus = 0;
    U8_t SendByte = RED_LED_ON_DATA;
    U8_t SendData_ptr[MAX_SEND_CMD_LENGTH];

    /* Send Frame: [0xBA Len 0x40 Code Checksum] */
    ReturnStatus = EF_BOOLEAN_RFID_SendFrame (MANAGE_RED_LED_CMD, &SendByte, LED_DATA_LENGTH);

    if (ReturnStatus == TRUE)
    {
        ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
        if (ReturnStatus == TRUE)
        {
            /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
            if (ReturnStatus == OPERATION_SUCCEED)
            {
                ReturnStatus = STATUS_SUCCEED;
            }
        }
    }
    return ReturnStatus;

}

/****************************************************************************
* Function    : EF_u8_RFID_RedLedOff ();
*
* DESCRIPTION : Turn off the Red LEd on the RFID Card.
*
* PARAMETERS  : None.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*******************************************************************************/
U8_t EF_u8_RFID_RedLedOff ()
{
    volatile U8_t ReturnStatus = 0;
    U8_t SendData_ptr[MAX_SEND_CMD_LENGTH];

    U8_t SendByte = RED_LED_OFF_DATA;
    /* Send Frame: [0xBA Len 0x40 Code Checksum] */
    ReturnStatus = EF_BOOLEAN_RFID_SendFrame (MANAGE_RED_LED_CMD, &SendByte, LED_DATA_LENGTH);

    if (ReturnStatus == TRUE)
    {
        ReturnStatus = EF_u8_RFID_ReceiveFrame (SendData_ptr);
        if (ReturnStatus == TRUE)
        {
            /* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
            if (ReturnStatus == OPERATION_SUCCEED)
            {
                ReturnStatus = STATUS_SUCCEED;
            }
        }
    }
    return ReturnStatus;

}
