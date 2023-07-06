/**
 * @file EEPROM.c
 * @date 03.11.2014
 * @author SU
 *
 * @cond
 *********************************************************************************************************************
 * v1.0.0 - Rakun Project
 *
 * Copyright (c) 2017-2020, ARCELIK AS
 * All rights reserved.
 *
 *********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2020-06-01:
 *     - Initial Version
 *
 * @endcond
 *
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/

#include "EEPROM.h"
#include "spiDriver.h"


/*******************************************************************************
 * GLOBAL[EXTERNAL] FUNCTIONS
 *******************************************************************************/

/*******************************************************************************
 * GLOBAL[EXTERNAL] VARIABLES
 *******************************************************************************/

/*******************************************************************************
* LOCAL TYPEDEFS
********************************************************************************/

/*******************************************************************************
* LOCAL DEFINES
********************************************************************************/

/*******************************************************************************
* LOCAL VARIABLES
********************************************************************************/
static EEPROM_t E2PROM;

/*******************************************************************************
* LOCAL FUNCTION PROTOTYPES
********************************************************************************/

/*******************************************************************************
* LOCAL CONSTANTS
********************************************************************************/

/*******************************************************************************
* INTERFACE FUNCTIONS
********************************************************************************/

void InitEEPROM(void)
{
    uint8_t temp;
    uint8_t tempBuf[1];
    tempBuf[0] = 0xAA;

    temp = CheckEEPROMReadWrite(21, tempBuf);

}


void WriteEEPROMEnable()
{

    uint32_t dataFrame = 0x00FF0000; // with dummy data
    uint32_t opt_code;

    EEPROM_SPI_CHIP_SELECT;

    opt_code = WREN;
    dataFrame = (opt_code << 24);
    spiXmit(dataFrame, 2);

    EEPROM_SPI_CHIP_UNSELECT;
}

uint8_t ReadEEPROMStatus()
{

    uint32_t E2PROM_Data = 0;

    EEPROM_SPI_CHIP_SELECT;

    E2PROM_Data = spiReceive(0x05FF0000, 2);

    EEPROM_SPI_CHIP_UNSELECT;

    return (E2PROM_Data & 0xFF);
}

void WriteEEPROMByte(uint8_t Data, uint16_t DestAddress)
{
    uint32_t dataFrame = 0xFF; // with dummy data
    uint32_t opt_code;

    WriteEEPROMEnable();

    DELAY_US(2000);

    EEPROM_SPI_CHIP_SELECT;

    opt_code = WRITE;
    dataFrame = (uint32_t)(opt_code << 24);
    dataFrame |= (uint32_t)DestAddress << 8;
    dataFrame |= (uint32_t)Data;

    spiXmit(dataFrame, 4);

    EEPROM_SPI_CHIP_UNSELECT;
}

void WriteEEPROMBlock(uint16_t pageNo, E2PageBuf_t bufTx)
{

    uint16_t i = 0;
    uint32_t dataFrame = 0xFF; // with dummy data
    uint32_t opt_code;
    uint16_t SrcAddress = pageNo * E2PROM_PAGE_SIZE;

    WriteEEPROMEnable();

    DELAY_US(5000);

    EEPROM_SPI_CHIP_SELECT;

    opt_code = WRITE;
    dataFrame = (uint32_t)opt_code << 24;
    dataFrame |= (uint32_t)SrcAddress << 8;

    spiXmit(dataFrame, 3); //send Opcode and start address

    for (i = 0; i < E2PROM_PAGE_SIZE; i++) {
        spiXmit((uint32_t)bufTx.B[i] << 24, 1); //send data
    }

    EEPROM_SPI_CHIP_UNSELECT;
}

void WriteEEPROM16BitData(uint16_t SrcAddress, uint16_t data1)
{

//    uint16_t i = 0;
    uint32_t dataFrame = 0xFF; // with dummy data
    uint32_t opt_code;
//    uint16_t SrcAddress = 0;
//    uint8_t data1 = 14;

    WriteEEPROMEnable();

    DELAY_US(2000);

    EEPROM_SPI_CHIP_SELECT;

    opt_code = WRITE;
    dataFrame = (uint32_t)opt_code << 24;
    dataFrame |= (uint32_t)SrcAddress << 8;

    spiXmit(dataFrame, 3); //send Opcode and start address

//    for (i = 0; i < E2PROM_PAGE_SIZE; i++) {
//        spiXmit(data1, 1); //send data
        spiXmit((uint32_t)data1 << 16, 2); //send data
//    }

    EEPROM_SPI_CHIP_UNSELECT;
}

void EreaseEEPROM(uint16_t DestAddress, uint16_t size)
{

    uint16_t i = 0;

    for (i = 0; i <= size; i++) {
        WriteEEPROMByte(0xFF, DestAddress);
        E2PROM.StatusRegister.bit.RDY = 1;
        while (E2PROM.StatusRegister.bit.RDY) {
            E2PROM.StatusRegister.all = ReadEEPROMStatus();
        }
        DestAddress++;
    }

    E2PROM.Flags.bit.EmptyParams = 1;
}

#if 0
char TestEEPROM(void)
{
    int i =0;
    for(i=0; i<64;i++)
       E2PROM.BufferTx.B[i] =i;

    WriteEEPROMBlock(1,E2PROM.BufferTx);
    DELAY_US(2000);
    ReadEEPROMBlock(1);

    if(1)//E2PROM.BufferRx[0] == E2PROM.BufferTx[0])
    {
        return 1;
    }

    return 0;
}
#endif

char CheckEEPROMReadWrite(uint16_t page, uint8_t* buffer )
{
    uint8_t buffer_rx[64];
    write_eeprom(page,1, buffer);
    DELAY_US(3000);
    read_eeprom(page,1, buffer_rx);

    if(buffer_rx[0] == buffer[0])
    {
        return 1;
    }

    return 0;
}

void read_eeprom(uint16_t page, uint16_t page_size, uint8_t* buffer)
{

    uint16_t i = 0;
    uint32_t opt_code;
    uint32_t dataFrame;

//    ConfigureSPI(EEPROM_IC);

    uint16_t SrcAddress = page * 64;
    dataFrame = (uint32_t)0xFF << 24;

    EEPROM_SPI_CHIP_SELECT;

    opt_code = READ;

    dataFrame = (uint32_t)opt_code << 24;
    dataFrame |= (uint32_t)SrcAddress << 8;

    spiXmit(dataFrame, 3); //send opcode and start address

    for (i = 0; i < E2PROM_PAGE_SIZE * page_size; i++) {
        buffer[i] = spiReceive(0xFF, 1); //get datas
    }

    EEPROM_SPI_CHIP_UNSELECT;
}


/**
 * @brief writeEEPROM16bitDataset To read 16bit data sets like arrays from eeprom
 *
 * @param v beginning point of eeprom
 * @param size data size which will be written to eeprom
 * @param data address of data
 * @return None
 */
void readEEPROM16bitDataset(uint16_t SrcAddress, uint16_t size, uint16_t* buffer)
{

    uint16_t i = 0;
    uint32_t opt_code;
    uint32_t dataFrame;

    dataFrame = (uint32_t)0xFF << 24;

    EEPROM_SPI_CHIP_SELECT;

    opt_code = READ;

    dataFrame = (uint32_t)opt_code << 24;
    dataFrame |= (uint32_t)SrcAddress << 8;

    spiXmit(dataFrame, 3); //send opcode and start address

    for (i = 0; i < size; i++) {
        buffer[i] = spiReceive(0xFFFF, 2); //get datas
//        DELAY_US(10000);
    }

    EEPROM_SPI_CHIP_UNSELECT;
}

/**
 * @brief writeEEPROM16bitDataset To write 16bit data sets like arrays
 *
 * @param startAddress beginning point of eeprom
 * @param size data size which will be written to eeprom
 * @param data address of data
 * @return None
 */
void writeEEPROM16bitDataset(uint16_t startAddress, uint16_t size, uint16_t *data)
{
    uint16_t var;
    uint16_t address;
    uint16_t val;

    for (var = 0; var < size; ++var) {
        address = startAddress + var*2;
        val =  *(data + var);

        WriteEEPROM16BitData(address,val);
        DELAY_US(10000);
    }

}

/**/
void write_eeprom(uint16_t page, uint16_t page_size, uint8_t* buffer)
{

    int i = 0, k = 0;
    E2PageBuf_t buf;

//    ConfigureSPI(EEPROM_IC);

    for (i = page; i < (page_size + page); i++) {
        memcpy(buf.B, buffer + (k * 64), E2PROM_PAGE_SIZE);
        WriteEEPROMBlock(i, buf);
        k++;
        DELAY_US(5000);
    }
}

/*
uint8_t LoadParameters(uint16_t *SrcAddress, uint16_t *DestAddress,  uint16_t size){

    uint16_t i = 0;

    if(ReadEEPROMBlock(SrcAddress, size)){
        return 1;
    }

    for(i = 0; i < (size / 2); i++){
        *DestAddress = E2PROM.BufferRx.W[i];
        DestAddress++;
    }

    return 0;
}

*/
