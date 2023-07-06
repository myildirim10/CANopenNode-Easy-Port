/**
 * @file EEPROM.h
 * @author SU
 * @date 03.11.2014 00:27:37
 * @brief EEPROM API
 *
 * @see http://ww1.microchip.com/downloads/en/devicedoc/atmel-8698-seeprom-at25128b-256b-datasheet.pdf
 */

/**
 * @file MainTask.h
 * @date 2016-06-30
 * @author Oguz Atsiz
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


#ifndef EEPROM_H_
#define EEPROM_H_

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include "stdint.h"

/*******************************************************************************
* EXPORTED DEFINES
********************************************************************************/
//opcodes for AT25256B
#define WREN 6
#define WRDI 4
#define RDSR 5
#define WRSR 1
#define READ 3
#define WRITE 2

//EEPROM definitions____________________________________
#define E2PROM_PAGE_SIZE 64
#define EEPROM_TEST_ADDRESS 0x3FFF
#define EEPROM_PRM_ADDRESS 0x0000
#define EEPROM_TEST_DATA 0xE0

/*******************************************************************************
* EXPORTED TYPES
********************************************************************************/
/**
 *
 */
typedef enum EEPROM_ERROR {
    EEPROM_OK,
    EEPROM_CRC_ERROR,
    EEPROM_WRITE_ERROR,
    EEPROM_MISMATCH,
    EEPROM_READ_ERROR
} eEEPROMERR;

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
typedef union _E2PageBuf {
    uint32_t I[32]; /**< Integer access. */
    uint16_t W[64]; /**< Word access. */
    uint8_t B[128]; /**< Byte access. */
    float F[32]; /**< float access. */
} E2PageBuf_t;

/**
 *
 */
typedef struct _E2StatusBits {
    uint8_t WPEN : 1;
    uint8_t Bits : 3;
    uint8_t BP1 : 1;
    uint8_t BP0 : 1;
    uint8_t WEN : 1;
    uint8_t RDY : 1;
} E2StatusBits;

/**
 *
 */
typedef union _E2Status {
    uint8_t all;
    E2StatusBits bit;
} E2Status_t;

/**
 *
 */
typedef struct _E2FlagBits {
    uint8_t OK : 1;
    uint8_t Initiated : 1;
    uint8_t EmptyParams : 1;
    uint8_t Update : 1;
    uint8_t rsvd : 4;
} E2FlagBits_t;

/**
 *
 */
typedef union _E2Flags {
    uint8_t all;
    E2FlagBits_t bit;
} E2Flags_t;

/**
 *
 */
typedef struct _EEPROM {
    E2Status_t StatusRegister;
    E2Flags_t Flags;
    uint8_t ByteTx;
    uint8_t ByteRx;
    E2PageBuf_t BufferTx;
    E2PageBuf_t BufferRx;
} EEPROM_t;

/*******************************************************************************
* EXPORTED MACROS
********************************************************************************/

/*******************************************************************************
* EXPORTED CONSTANTS
********************************************************************************/

/*******************************************************************************
* EXPORTED VARIABLES
********************************************************************************/

/*******************************************************************************
* API FUNCTIONS
********************************************************************************/

/**
 * @brief check-compare eeprom page
 *
 * @param page page
 * @param page_size page_size
 * @param buffer buffer address
 * @return flag result
 */
char CheckEEPROMReadWrite(uint16_t page, uint8_t* buffer);

/**
 * @brief read eeprom page
 *
 * @param page page
 * @param page_size page_size
 * @param buffer buffer address
 * @return None
 */
void read_eeprom(uint16_t page, uint16_t page_size, uint8_t* buffer);

/**
 * @brief write eeprom page
 *
 * @param page page
 * @param page_size page_size
 * @param buffer buffer address
 * @return None
 */
extern void write_eeprom(uint16_t page, uint16_t page_size, uint8_t* buffer);
extern void WriteEEPROMByte(uint8_t Data, uint16_t DestAddress);
extern void read_eeprom(uint16_t page, uint16_t page_size, uint8_t* buffer);
extern void WriteEEPROMBlock(uint16_t pageNo, E2PageBuf_t bufTx);

/**
 * @brief writeEEPROM16bitDataset To write 16bit data sets like arrays
 *
 * @param startAddress beginning point of eeprom
 * @param size data size which will be written to eeprom
 * @param data address of data
 * @return None
 */
extern void writeEEPROM16bitDataset(uint16_t startAddress, uint16_t size, uint16_t *data);

/**
 * @brief writeEEPROM16bitDataset To read 16bit data sets like arrays from eeprom
 *
 * @param v beginning point of eeprom
 * @param size data size which will be written to eeprom
 * @param data address of data
 * @return None
 */
extern void readEEPROM16bitDataset(uint16_t SrcAddress, uint16_t size, uint16_t* buffer);

void InitEEPROM(void);

#endif /* EEPROM_H_ */
