/***************************************************************
 *  Source File: EF_SLM025M.h
 *
 *  Description:  RFID Module SLM025M  driver
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
#ifndef EF_SLM025M_H_
#define EF_SLM025M_H_

#include "../UtilitiesLayer/std_types.h"

/*********************************************************
 ***************** Status Code  Defines ******************
 *********************************************************/
// Read status
#define SL025_OPERATION_SUCCEED               0x00
/* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
#define SL025_STATUS_SUCCEED                  0xFF
#define SL025_NO_TAG                          0x01
#define SL025_LOGIN_SUCCEED                   0x02
#define SL025_LOGIN_FAIL                      0x03
#define SL025_READ_FAIL                       0x04
#define SL025_WRITE_FAIL                      0x05
#define SL025_UNABLE_READ_AFTER_WRITE         0x06
#define SL025_READ_AFTER_WRITE_FAIL           0x07
#define SL025_ADD_OVERFLOW                    0x08
#define SL025_NOT_AUTHENTICATE                0x0D
#define SL025_LOAD_KEY_FAIL                   0x0C
#define SL025_CHECKSUM_ERROR                  0xF0
#define SL025_COMMAND_CODE_ERROR              0xF1
#define SL025_NOT_FOUND_FRAME                 0xEF
#define SL025_WRONG_CMD                       0xEE

/* RFID Mifare 1k has 16 Sector(0 to 15), Every Sector has 4 Blocks(0 to 3) , Every Block has 16 bytes */
#define SL025_MAX_SECTOR_NUMBER               15

/* Enum to define which Key is used, EF_u8_SLM025M_LoginSector Function use it as argument */
typedef enum {
    KEY_TYPE_A=0xAA,
    KEY_TYPE_B=0xBB
}KeyTypeEnum;

/****************************************************************************
* Function    : EF_void_SLM025M_Init ();
*
* DESCRIPTION : init the Uart For SLM025M Module SLM025M and init Card detected Pin
*
* PARAMETERS  : None.
*
* Return Value: None.
******************************************************************************/
void EF_void_SLM025M_Init ();

/****************************************************************************
* Function    : EF_u8_SLM025M_GetCardNumber (U8_t* CardNumber_ptr ,U8_t* u8CardLength_ptr);
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
U8_t EF_u8_SLM025M_GetCardNumber (U8_t* CardNumber_ptr ,U8_t* u8CardLength_ptr);

//todo change all SLM025M to SL025M
/****************************************************************************
* Function    : EF_u8_SLM025M_IsCardExist ();
*
* DESCRIPTION : check if RFID see a card inside it.
*
* PARAMETERS  : None.
*
* Return Value: 0x00: CARD_IS_DETECTED
*               0x01: CARD_IS_NOT_DETECTED
*******************************************************************************/
U8_t EF_u8_SLM025M_IsCardExist ();

/****************************************************************************
* Function    : EF_u8_SLM025M_LoginSector (U8_t SectorNumber, KeyTypeEnum KeyType, U8_t* u8Key_ptr  );
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
* NOTE        : - SLM025M has 16 sector(0 to 15), every Sector has 4 block and has it's Special and Seperate KeyA and KeyB.
*               - Every Block has 16 bytes.
*               - KeyA and KeyB are saved in the last block ( Block 3) .
*               - Key A(Master Key :More Secured) and B (not Secured), the Default of them: "FF FF FF FF FF FF"
******************************************************************************/
U8_t EF_u8_SLM025M_LoginSector (U8_t SectorNumber, KeyTypeEnum KeyType, U8_t* u8Key_ptr );


/****************************************************************************
* Function    : EF_u8_SLM025M_UpdateMasterKey (U8_t SectorNumber , U8_t* u8KeyA_ptr  );
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
U8_t EF_u8_SLM025M_UpdateMasterKey (U8_t SectorNumber , U8_t* u8KeyA_ptr  );

/****************************************************************************
* Function    : EF_u8_SLM025M_UpdateAllKeys ( U8_t SectorNumber , U8_t* u8KeyA_ptr , U8_t* u8KeyB_ptr );
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
U8_t EF_u8_SLM025M_UpdateAllKeys ( U8_t SectorNumber , U8_t* u8KeyA_ptr , U8_t* u8KeyB_ptr );

/****************************************************************************
* Function    : EF_u8_SLM025M_WriteDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );
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
U8_t EF_u8_SLM025M_WriteDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );

/****************************************************************************
* Function    : EF_u8_SLM025M_WriteDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );
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
U8_t EF_u8_SLM025M_WriteDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );

/****************************************************************************
* Function    : EF_u8_SLM025M_ReadDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );
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
U8_t EF_u8_SLM025M_ReadDataBlock (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr);

/****************************************************************************
* Function    : EF_u8_SLM025M_ReadDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );
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
U8_t EF_u8_SLM025M_ReadDataValue (U8_t SectorNumber , U8_t BlockNumber, U8_t* u8DataPtr  );

/****************************************************************************
* Function    : EF_u8_SLM025M_RedLedOn ();
*
* DESCRIPTION : Turn on the Red LEd on the SLM025M Card.
*
* PARAMETERS  : None.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*******************************************************************************/
U8_t EF_u8_SLM025M_RedLedOn ();

/****************************************************************************
* Function    : EF_u8_SLM025M_RedLedOff ();
*
* DESCRIPTION : Turn off the Red LEd on the SLM025M Card.
*
* PARAMETERS  : None.
*
* Return Value: 0xFF: STATUS_SUCCEED
*               0xF0: CHECKSUM_ERROR
*               0x00: FALSE
*               0xEF: NOT_FOUND_FRAME
*******************************************************************************/
U8_t EF_u8_SLM025M_RedLedOff ();

#endif /* EF_SLM025M_H_ */
