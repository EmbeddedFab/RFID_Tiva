/***************************************************************
 *  Source File: EF_RFID_cfg.h
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
#ifndef EF_SLM025M_CFG_H_
#define EF_SLM025M_CFG_H_


#define VIRTUAL_UART_DEBUGG             0       /* Disable Virtual Uart Terminal when equals 0 */

#define HOST_SL025_PREAMBLE             0xBA    /* Preamble When Send Frame to RFID */
#define SL025_HOST_PREAMBLE             0xBD    /* Preamble When Receive Frame from RFID */

/* Detected Pin : detect if RFID Module See Card inside it or not  */
#define DETECT_CARD_GPIO_BASE           GPIO_PORTC_BASE
#define DETECT_CARD_GPIO_PIN            GPIO_PIN_7
#define DETECT_CARD_PORT                'c'
#define DETECT_CARD_PIN                 7
#define CARD_IS_DETECTED                0x00
#define CARD_IS_NOT_DETECTED            0x01


#define MAX_SEND_CMD_LENGTH             21
#define MAX_RECEIVED_LENGTH             21
#define MAX_CARD_FRAME_LENGTH           13
#define MIN_RECEIVED_LENGTH             3

/* Addresses in the Frame */
#define DATA_INDEX                      3U
#define PREAMBLE_INDEX                  0
#define CMD_LENGTH_INDEX                1
#define CMD_INDEX                       2
#define STATUS_INDEX                    3
#define READ_DATA_INDEX                 4
#define RX_CARD_DATA_INDEX              4

/* Length of Command Data which are inserted in the frame */
#define MAX_SELECT_CARD_LENGTH          13
#define LOGIN_SECTOR_DATA_LENGTH        8
#define WRITE_MASTER_KEY_DATA_LENGTH    7
#define WRITE_BLOCK_DATA_LENGTH         17
#define BLOCK_DATA_LENGTH               16
#define VALUE_LENGTH                    4
#define READ_DATA_LENGTH                1
#define UPDATE_KEYS_DATA_LENGTH         16
#define KEY_LENGTH                      6
#define WRITE_VALUE_DATA_LENGTH         5
#define LED_DATA_LENGTH                 1
#define CARD_LENGTH_OLD_VERSION         4
#define CARD_LENGTH_NEW_VERSION         7

/* RFID Mifare 1k has 16 Sector(0 to 15), Every Sector has 4 Blocks(0 to 3) , Every Block has 16 bytes */
#define MAX_SECTOR_NUMBER               15
#define MAX_BLOCK_NUMBER                3

/* Data to Led For Turn on or Off , inserted in the Frame */
#define RED_LED_ON_DATA                 1
#define RED_LED_OFF_DATA                0


/*********************************************************
 ***************** Command Codes ***********************
 *********************************************************/
#define SELECT_MIFARE_CARD_CMD          0x01
#define LOGIN_SECTOR_CMD                0x02
#define READ_DATA_BLOCK_CMD             0x03
#define WRITE_DATA_BLOCK_CMD            0x04
#define READ_DATA_VALUE_CMD             0x05
#define WRITE_DATA_VALUE_CMD            0x06
#define WRITE_MASTER_KEY_CMD            0x07
#define INCREMENT_VALUE_CMD             0x08
#define DECREMENT_VALUE_CMD             0x09
#define COPY_VALUE_CMD                  0x0A
#define READ_DATA_PAGE_CMD              0x10
#define WRITE_DATA_PAGE_CMD             0x11
#define DOWNLOAD_KEY_CMD                0x12
#define LOGIN_SECTOR_STORED_KEY_CMD     0x13
#define MANAGE_RED_LED_CMD              0x40
#define GET_FIRMWARE_VERSION            0xF0

/*********************************************************
 ***************** Status Code  **************************
 *********************************************************/
// Read status
#define OPERATION_SUCCEED               0x00
/* convert the return status of OPERATION_SUCCEED to STATUS_SUCCEED not to conflict with FALSE */
#define STATUS_SUCCEED                  0xFF
#define NO_TAG                          0x01
#define LOGIN_SUCCEED                   0x02
#define LOGIN_FAIL                      0x03
#define READ_FAIL                       0x04
#define WRITE_FAIL                      0x05
#define UNABLE_READ_AFTER_WRITE         0x06
#define READ_AFTER_WRITE_FAIL           0x07
#define ADD_OVERFLOW                    0x08
#define NOT_AUTHENTICATE                0x0D
#define LOAD_KEY_FAIL                   0x0C
#define CHECKSUM_ERROR                  0xF0
#define COMMAND_CODE_ERROR              0xF1
#define NOT_FOUND_FRAME                 0xEF
#define WRONG_CMD                       0xEE


/*********************************************************
 ***************** Command Code Length ******************
 *********************************************************/
#define SELECT_MIFARE_CARD_LENGTH       0x02
#define LOGIN_SECTOR_LENGTH             0x0A
#define DOWNLOAD_KEY_LENGTH             LOGIN_SECTOR_LENGTH
#define LOGIN_SECTOR_STORED_KEY_LENGTH  0x04
#define READ_DATA_BLOCK_LENGTH          0x03
#define READ_BLOCK_VALUE_LENGTH         READ_DATA_BLOCK_LENGTH
#define INIT_BLOCK_VALUE_LENGTH         0x07
#define WRITE_MASTER_KEY_LENGTH         0x09
#define INCREMENT_VALUE_LENGTH          0x07
#define DECREMENT_VALUE_LENGTH          INCREMENT_VALUE_LENGTH
#define COPY_VALUE_LENGTH               0x04
#define MANAGE_RED_LED_LENGTH           0x03
#define GET_FIRMWARE_VERSION_LENGTH     0x02


#endif /* EF_SLM025M_CFG_H_ */
