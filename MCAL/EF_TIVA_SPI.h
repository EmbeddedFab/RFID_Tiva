 /***************************************************************
 *  Source File: EF_SPI.h
 *
 *  Description: SPI driver for ATMEGA32
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
#ifndef _EF_TIVA_SPI_H_
#define _EF_TIVA_SPI_H_
#include "../ServiceLayer/std_types.h"

typedef enum{
    MASTER_TYPE=0,
    SLAVE_TYPE
}MasterOrSlaveType;

typedef enum{
    SPI_MODULE_0,
    SPI_MODULE_2
}SPIModuleTypeEnum;

/*********************************************************************
* Function    : void EF_void_SPI_Init(U8_t DeviceType);
*
* DESCRIPTION : This function used to Initialize SPI Module.
*
* PARAMETERS  : U8_t DeviceType : 0 ----> Master
*                                 1 ----> Slave
* Return Value: void
**********************************************************************/
void EF_SpiInit(MasterOrSlaveType DeviceType , SPIModuleTypeEnum  SPI_Module);

/*********************************************************************
* Function    : U8_t EF_SpiTransfer(U8_t data);
*
* DESCRIPTION : This function used to Transfer Data through SPI bus
*
* PARAMETERS  : U8_t data  Data user need to transmit.
*
*
* Return Value: Data User received
**********************************************************************/
void EF_SpiTransfer(U8_t data , SPIModuleTypeEnum  SPI_Module);

/*********************************************************************
* Function    : U8_t EF_BOOLEAN_SpiReceive(U8_t data);
*
* DESCRIPTION : This function used to receive Data through SPI bus
*
* PARAMETERS  : U8_t data  Data user need to transmit.
*
*
* Return Value: Data User received
**********************************************************************/
void EF_void_SpiReceive(U16_t *DataPtr , SPIModuleTypeEnum  SPI_Module);

/*********************************************************************
* Function    : U8_t EF_BOOLEAN_SpiTransfer(U8_t * returnedValue);
*
* DESCRIPTION : This function used to Transfer Data through SPI bus without Stuck .
*
* PARAMETERS  : U8_t data  transfered data .
*
*
* Return Value: return True if Byte is received or false
**********************************************************************/
BOOLEAN EF_BOOLEAN_SpiTransmit(U8_t data   , SPIModuleTypeEnum  SPI_Module);

/*********************************************************************
* Function    : U8_t EF_BOOLEAN_SpiReceive(U8_t * returnedValue);
*
* DESCRIPTION : This function used to Transfer Data through SPI bus without Stuck .
*
* PARAMETERS  : U8_t data  transfered data .
*
*
* Return Value: return True if Byte is received or false
**********************************************************************/
BOOLEAN EF_BOOLEAN_SpiReceive(U16_t * returnedValue  , SPIModuleTypeEnum  SPI_Module);


#endif
