 /***************************************************************
 *  Source File: EF_SPI.c
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
#include "EF_TIVA_SPI.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "../UtilitiesLayer/EF_SpechialTIMER.h"
#include "EF_TIVA_DIO.h"

/*********************************************************************
* Function    : void EF_void_SPI_Init(U8_t DeviceType);
*
* DESCRIPTION : This function used to Initialize SPI Module.
*
* PARAMETERS  : U8_t DeviceType : 0 ----> Master
*                                 1 ----> Slave
* Return Value: void
**********************************************************************/
void EF_SpiInit(MasterOrSlaveType DeviceType , SPIModuleTypeEnum  SPI_Module)
{
    switch (SPI_Module)
    {
    case SPI_MODULE_0 :
        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        GPIOPinConfigure(GPIO_PA2_SSI0CLK);
        GPIOPinConfigure(GPIO_PA5_SSI0TX);
        GPIOPinConfigure(GPIO_PA4_SSI0RX);
        EF_S8_t_DIO_InitPin ('a', 3, OUTPUT);

        GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_2);
         SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, DeviceType, 7000, 8);
         SSIEnable(SSI0_BASE);

        break;

    case SPI_MODULE_2 :
        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

        GPIOPinConfigure(GPIO_PB4_SSI2CLK);
        GPIOPinConfigure(GPIO_PB7_SSI2TX);   //MOSI   if master
        GPIOPinConfigure(GPIO_PB6_SSI2RX);   //MISO
        EF_S8_t_DIO_InitPin ('b', 5, OUTPUT);

        GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_6);
        SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, DeviceType, 7000, 8);
        SSIEnable(SSI2_BASE);

        break;

    default:
        break;
    }

    /* using Special Timer to able some UART Function to be unstuck */
    EF_void_TimerCreate(SPI_TIMER_ID, SPI_TIMEOUT);
}


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
void EF_SpiTransfer(U8_t data , SPIModuleTypeEnum  SPI_Module)
{
    switch (SPI_Module)
    {
    case SPI_MODULE_0 :
        SSIDataPut( SSI0_BASE, data );
        while( SSIBusy(SSI0_BASE) )
        {

        }
        break;

    case SPI_MODULE_2 :
        SSIDataPut( SSI2_BASE, data );
        while( SSIBusy(SSI2_BASE) )
        {

        }
        break;

    default:
        break;
    }



}

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
void EF_void_SpiReceive(U16_t *DataPtr , SPIModuleTypeEnum  SPI_Module)
{
    switch (SPI_Module)
    {
    case SPI_MODULE_0 :
        SSIDataGet( SSI0_BASE, (U32_t*)DataPtr );

        break;

    case SPI_MODULE_2 :
        SSIDataGet( SSI2_BASE, (U32_t*)DataPtr );

        break;

    default:
        break;
    }

}

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
BOOLEAN EF_BOOLEAN_SpiTransmit(U8_t data   , SPIModuleTypeEnum  SPI_Module)
{
    BOOLEAN TransferFlag   = FALSE;
    /* using Special Timer */
    EF_void_TimerStart(SPI_TIMER_ID);

    switch (SPI_Module)
    {
    case SPI_MODULE_0 :
        SSIDataPutNonBlocking( SSI0_BASE, data );

        /* make SPI unstuck  + Wait for empty transmit buffer */
        while( (SSIBusy(SSI0_BASE)) && (!EF_BOOLEAN_TimerCheck(SPI_TIMER_ID)) );

        /* extracting from the previous loop because of receiving byte or Time out*/
        EF_void_TimerStop(SPI_TIMER_ID);
        EF_void_TimerReset(SPI_TIMER_ID);


        if (SSIBusy(SSI0_BASE))
        {
            TransferFlag = FALSE;
        }
        else
        {
            TransferFlag = TRUE;
        }
        break;

    case SPI_MODULE_2 :

        SSIDataPutNonBlocking( SSI2_BASE, data );

        /* make SPI unstuck  + Wait for empty transmit buffer */
        while( (SSIBusy(SSI2_BASE)) && (!EF_BOOLEAN_TimerCheck(SPI_TIMER_ID)) );

        /* extracting from the previous loop because of receiving byte or Time out*/
        EF_void_TimerStop(SPI_TIMER_ID);
        EF_void_TimerReset(SPI_TIMER_ID);


        if (SSIBusy(SSI2_BASE))
        {
            TransferFlag = FALSE;
        }
        else
        {
            TransferFlag = TRUE;
        }
        break;

    default:
        break;
    }



    return TransferFlag;

}


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
BOOLEAN EF_BOOLEAN_SpiReceive(U16_t * returnedValue  , SPIModuleTypeEnum  SPI_Module)
{
    /* TODO : test this function */
    BOOLEAN TransferFlag   = FALSE;
    /* using Special Timer */
    EF_void_TimerStart(SPI_TIMER_ID);

    switch (SPI_Module)
    {
    case SPI_MODULE_0 :

        /* make SPI unstuck  + Wait for empty transmit buffer */
        while( ( !(HWREG(SSI0_BASE + SSI_O_SR) & SSI_SR_RNE) ) &&  (!EF_BOOLEAN_TimerCheck(SPI_TIMER_ID)) );

        /* extracting from the previous loop because of receiving byte or Time out*/
        EF_void_TimerStop(SPI_TIMER_ID);
        EF_void_TimerReset(SPI_TIMER_ID);

        if (HWREG(SSI0_BASE + SSI_O_SR) & SSI_SR_RNE)
        {
            TransferFlag = TRUE;
        }
        else
        {
            TransferFlag = FALSE;
        }

        SSIDataGetNonBlocking( SSI0_BASE, (U32_t*)returnedValue );
        break;

    case SPI_MODULE_2 :

        /* make SPI unstuck  + Wait for empty transmit buffer */
        while( ( !(HWREG(SSI2_BASE + SSI_O_SR) & SSI_SR_RNE) ) &&  (!EF_BOOLEAN_TimerCheck(SPI_TIMER_ID)) );

    //    while( /*( SSIDataGetNonBlocking( SSI2_BASE, (U32_t*)returnedValue ) == 0 ) && */ (!EF_BOOLEAN_TimerCheck(SPI_TIMER_ID)) );

        /* extracting from the previous loop because of receiving byte or Time out*/
        EF_void_TimerStop(SPI_TIMER_ID);
        EF_void_TimerReset(SPI_TIMER_ID);



        if (HWREG(SSI2_BASE + SSI_O_SR) & SSI_SR_RNE)
        {
            TransferFlag = TRUE;
        }
        else
        {
            TransferFlag = FALSE;
        }
        SSIDataGetNonBlocking( SSI2_BASE, (U32_t*)returnedValue );

        break;

    default:
        break;
    }



    return TransferFlag;

}





