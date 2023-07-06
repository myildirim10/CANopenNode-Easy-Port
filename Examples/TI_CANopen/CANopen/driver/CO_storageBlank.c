/*
 * CANopen Object Dictionary storage object (blank example).
 *
 * @file        CO_storageBlank.c
 * @author      Janez Paternoster
 * @copyright   2021 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/* Includes ------------------------------------------------------------------*/
#include "CO_storageBlank.h"


#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
#include "CANopenHardware.h"
#include "301/crc16-ccitt.h"

#include "spiDriver.h"

/* Defines -------------------------------------------------------------------*/
#ifndef CO_STORAGE_EEPROM_TOTAL_SIZE
 #define CO_STORAGE_EEPROM_TOTAL_SIZE            ( 0x4000 )  //EEPROM_SIZE       //      // 0x4000 for 128kbits or 0x8000 for 25LC256
#endif
#ifndef CO_STORAGE_EEPROM_PAGE_SIZE
 #define CO_STORAGE_EEPROM_PAGE_SIZE             ( 64 )  //EEPROM_PAGE_SIZE  //
#endif

#define EE_CMD_READ                              ( (unsigned)0b00000011 )
#define EE_CMD_WRITE                             ( (unsigned)0b00000010 )
#define EE_CMD_WRDI                              ( (unsigned)0b00000100 )
#define EE_CMD_WREN                              ( (unsigned)0b00000110 )
#define EE_CMD_RDSR                              ( (unsigned)0b00000101 )
#define EE_CMD_WRSR                              ( (unsigned)0b00000001 )
#define SPI_FIFO_SIZE                            16                           // SPI_FIFO_SIZE  // Dependent MCU, PIC32 uses 16 bytes long FIFO buffer with SPI.

#define CO_STORAGE_SS_LOW()                      vEEPROMCSPin ( 0 )
#define CO_STORAGE_SS_HIGH()                     vEEPROMCSPin ( 1 )

/**
 * Return true if write is in process.
 */
#define EE_isWriteInProcess()                    ( (EE_readStatus() & 0x01) != 0 )
/**
 * Return true if upper half of the eeprom is protected
 */
#define EE_isWriteProtected()                    ( (EE_readStatus() & 0x8C) == 0x88 )

/**
 * Enable write protection for upper half of the eeprom
 */
#define EE_writeProtect()                        EE_writeStatus ( 0x88 )
/*
 * Disable write protection for upper half of the eeprom
 */
#define EE_writeUnprotect()                      EE_writeStatus ( 0 )


/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/*
 * Eeprom is configured so, that first half of memory locations is not write
 * protected, so it is suitable for auto storage variables. Second half of
 * memory locations is write protected. It is used for storage on command, which
 * disables the protection for the short time when writing. Below are two
 * internal variables, used for indicating next free address in eeprom, one for
 * autonomous storage and one for protected storage
 */
static size_t eepromAddrNextAuto = 0;
static size_t eepromAddrNextProt = CO_STORAGE_EEPROM_TOTAL_SIZE / 2;
static volatile uint32_t dummy;


/* Private function prototypes -----------------------------------------------*/
static inline void EE_writeStatus ( uint8_t ucData );
static inline uint8_t EE_readStatus ( void );
static inline void EE_writeEnable (void);


/* Functions -----------------------------------------------------------------*/
/*
 * Function for writing data on "Store parameters" command - OD object 1010
 *
 * For more information see file CO_storage.h, CO_storage_entry_t.
 */
static ODR_t storeBlank(CO_storage_entry_t *entry, CO_CANmodule_t *CANmodule) {

    /* Open a file and write data to it */
    /* file = open(entry->pathToFileOrPointerToMemory); */
    CO_LOCK_OD(CANmodule);
    /* write(entry->addr, entry->len, file); */
    CO_UNLOCK_OD(CANmodule);

    return ODR_OK;
}


/*
 * Function for restoring data on "Restore default parameters" command - OD 1011
 *
 * For more information see file CO_storage.h, CO_storage_entry_t.
 */
static ODR_t restoreBlank(CO_storage_entry_t *entry, CO_CANmodule_t *CANmodule){

    /* disable (delete) the file, so default values will stay after startup */

    return ODR_OK;
}


CO_ReturnError_t CO_storageBlank_init(CO_storage_t *storage,
                                      CO_CANmodule_t *CANmodule,
                                      OD_entry_t *OD_1010_StoreParameters,
                                      OD_entry_t *OD_1011_RestoreDefaultParam,
                                      CO_storage_entry_t *entries,
                                      uint8_t entriesCount,
                                      uint32_t *storageInitError)
{
    CO_ReturnError_t ret;

    /* verify arguments */
    if (storage == NULL || entries == NULL || entriesCount == 0
        || storageInitError == NULL
    ) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    /* initialize storage and OD extensions */
    ret = CO_storage_init(storage,
                          CANmodule,
                          OD_1010_StoreParameters,
                          OD_1011_RestoreDefaultParam,
                          storeBlank,
                          restoreBlank,
                          entries,
                          entriesCount);
    if (ret != CO_ERROR_NO) {
        return ret;
    }

    /* initialize entries */
    *storageInitError = 0;
    for (uint8_t i = 0; i < entriesCount; i++) {
        CO_storage_entry_t *entry = &entries[i];

        /* verify arguments */
        if (entry->addr == NULL || entry->len == 0 || entry->subIndexOD < 2) {
            *storageInitError = i;
            return CO_ERROR_ILLEGAL_ARGUMENT;
        }

        /* Open a file and read data from file to entry->addr */
        /* file = open(entry->pathToFileOrPointerToMemory); */
        /* read(entry->addr, entry->len, file); */

    }

    return ret;
}


/*******************************************************************************************/

/**
 * Initialize eeprom device, target system specific function.
 *
 * @param storageModule Pointer to storage module.
 *
 * @return True on success
 */
bool_t CO_eeprom_init(void *storageModule)
{
    if (xEEPROMInit() == CAN_OPEN_HARDWARE_OK)
        return true;

    return false;
}


/**
 * Write to SPI and at the same time read from SPI.
 *
 * @param tx Ponter to transmitting data. If NULL, zeroes will be transmitted.
 * @param rx Ponter to data buffer, where received data wile be stored.
 * If null, Received data will be disregarded.
 * @param len Length of data buffers. Max SPI_FIFO_SIZE.
 */

static void EE_SPIWriteRead (uint8_t *tx, uint8_t *rx, uint8_t len)
{
    vEEPROMSPIWriteRead(tx, rx, len);
}


/**
 * Get free address inside eeprom, target system specific function.
 *
 * Function is called several times for each storage block in the initialization
 * phase after CO_eeprom_init().
 *
 * @param storageModule Pointer to storage module.
 * @param isAuto True, if variable is auto stored or false if protected
 * @param len Length of data, which will be stored to that location
 * @param [out] overflow set to true, if not enough eeprom memory
 *
 * @return Asigned eeprom address
 */
size_t CO_eeprom_getAddr(void *storageModule, bool_t isAuto, size_t len, bool_t *overflow)
{
    size_t addr;

    if (isAuto) {
        /* auto storage is processed byte by byte, no alignment necessary */
        addr = eepromAddrNextAuto;
        eepromAddrNextAuto += len;
        if (eepromAddrNextAuto > (CO_STORAGE_EEPROM_TOTAL_SIZE / 2)) {
            *overflow = true;
        }
    }
    else {
        /* addresses for storage on command must be page aligned */
        addr = eepromAddrNextProt;
        size_t lenAligned = len & (~(CO_STORAGE_EEPROM_TOTAL_SIZE - 1));
        if (lenAligned < len) {
            lenAligned += CO_STORAGE_EEPROM_PAGE_SIZE;
        }
        eepromAddrNextProt += lenAligned;
        if (eepromAddrNextProt > CO_STORAGE_EEPROM_TOTAL_SIZE) {
            *overflow = true;
        }
    }

    return addr;
}


/**
 * Read block of data from the eeprom, target system specific function.
 *
 * @param storageModule Pointer to storage module.
 * @param data Pointer to data buffer, where data will be stored.
 * @param eepromAddr Address in eeprom, from where data will be read.
 * @param len Length of the data block to be read.
 */
void CO_eeprom_readBlock(void *storageModule, uint8_t *data, size_t eepromAddr, size_t len)
{
    uint8_t buf[3] = {
        EE_CMD_READ,
        (uint8_t) (eepromAddr >> 8),
        (uint8_t) eepromAddr
    };

    CO_STORAGE_SS_LOW();

#ifdef C2000_PORT
    uint16_t i = 0;
    uint32_t dataFrame;
    dataFrame = (uint32_t)buf[0] << 24;
    dataFrame |= (uint32_t)buf[1] << 8;
    dataFrame |= (uint32_t)buf[2];
    spiXmit(dataFrame, 3);

    for (i = 0; i < 64; i++) {
        data[i] = spiReceive(0xFF, 1); //get datas
    }
#else
    EE_SPIWriteRead(buf, NULL, 3);


    while (len > 0) {
        uint8_t subLen = len <= SPI_FIFO_SIZE ? (uint8_t)len : SPI_FIFO_SIZE;

        EE_SPIWriteRead(NULL, data, subLen);
        len -= subLen;
        data += subLen;
    }
#endif
    CO_STORAGE_SS_HIGH();
}


/**
 * Write block of data to the eeprom, target system specific function.
 *
 * It is blocking function, so it waits, until all data is written.
 *
 * @param storageModule Pointer to storage module.
 * @param data Pointer to data buffer which will be written.
 * @param eepromAddr Address in eeprom, where data will be written. If data is
 * stored accross multiple pages, address must be aligned with page.
 * @param len Length of the data block.
 *
 * @return true on success
 */
bool_t CO_eeprom_writeBlock(void *storageModule, uint8_t *data, size_t eepromAddr, size_t len)
 {
#if 0
    while(EE_isWriteInProcess());
    EE_writeUnprotect();
    while(EE_isWriteInProcess());
#endif
   // while (len > 0) {
        uint8_t buf[3] = {
            EE_CMD_WRITE,
            (uint8_t) (eepromAddr >> 8),
            (uint8_t) eepromAddr,
        };

        EE_writeEnable();
        DELAY_US(5000);

        CO_STORAGE_SS_LOW();

#ifdef C2000_PORT
    uint32_t dataFrame = 0xFF;

//    dataFrame = (uint32_t)buf[0] << 24;
//    dataFrame |= (uint32_t)buf[1] << 8;
//    dataFrame |= (uint32_t)buf[2];
    uint32_t opt_code = EE_CMD_WRITE;
    dataFrame = (uint32_t)opt_code << 24;
    //dataFrame |= (uint32_t)0 << 8;
    spiXmit(dataFrame, 3); //send Opcode and start address
    for (int i = 0; i < CO_STORAGE_EEPROM_PAGE_SIZE; i++) {
        spiXmit((uint32_t)data[i], 1); //send data
    }
#else
    EE_SPIWriteRead(buf, NULL, 3);


        for (uint8_t i = 0; i < (CO_STORAGE_EEPROM_PAGE_SIZE / SPI_FIFO_SIZE); i++) {
            if (len > SPI_FIFO_SIZE) {
                uint8_t *ptr = data;
                *ptr <<= 24;
                EE_SPIWriteRead(&data, NULL, SPI_FIFO_SIZE);
                len -= SPI_FIFO_SIZE;
                data += SPI_FIFO_SIZE;
            }
            else {
                uint8_t *ptr = data;
                *ptr <<= 24;
                EE_SPIWriteRead((data), NULL, (uint8_t)len);
                len = 0;
                break;
            }
        }
#endif
        CO_STORAGE_SS_HIGH();

        eepromAddr += CO_STORAGE_EEPROM_PAGE_SIZE;

        /*  wait for completion of the write operation */
#if 0
        while(EE_isWriteInProcess());
#endif
   // }

#if 0
    EE_writeProtect();
    while(EE_isWriteInProcess());

    return EE_isWriteProtected();
#endif
    return 1;
}

uint8_t txData[10] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x11, 0x22, 0x33, 0x44, 0x55};
uint8_t rxData[10];


void TEST_FUNC ()
{
    uint32_t i;
//    memset(txData, 0x24, 10);

    DELAY_US(5000);
    CO_eeprom_writeBlock(NULL, txData, 0, 0);
    DELAY_US(5000);
    CO_eeprom_readBlock(NULL, rxData, 0, 0);
    DELAY_US(5000);
}

/**
 * Get CRC checksum of the block of data stored in the eeprom, target system
 * specific function.
 *
 * @param storageModule Pointer to storage module.
 * @param eepromAddr Address of data in eeprom.
 * @param len Length of the data.
 *
 * @return CRC checksum
 */
uint16_t CO_eeprom_getCrcBlock(void *storageModule, size_t eepromAddr, size_t len)
{
    uint16_t crc = 0;
    uint8_t buf[SPI_FIFO_SIZE] = {
        EE_CMD_READ,
        (uint8_t) (eepromAddr >> 8),
        (uint8_t) eepromAddr
    };

    CO_STORAGE_SS_LOW();
    EE_SPIWriteRead(buf, NULL, 3);

    while (len > 0) {
        uint8_t subLen = len <= SPI_FIFO_SIZE ? (uint8_t)len : SPI_FIFO_SIZE;

        /* update crc from data part */
        EE_SPIWriteRead(NULL, buf, subLen);
        crc = crc16_ccitt(buf, subLen, crc);
        len -= subLen;
    }

    CO_STORAGE_SS_HIGH();

    return crc;
}


/**
 * Update one byte of data in the eeprom, target system specific function.
 *
 * Function is used by automatic storage. It updates byte in eeprom only if
 * differs from data.
 *
 * @param storageModule Pointer to storage module.
 * @param data Data byte to be written
 * @param eepromAddr Address in eeprom, from where data will be updated.
 *
 * @return true if write was successful or false, if still waiting previous
 * data to finish writing.
 */
bool_t CO_eeprom_updateByte(void *storageModule, uint8_t data, size_t eepromAddr)
{

    if (EE_isWriteInProcess()) {
        return false;
    }

    /* read data byte from eeprom */
    uint8_t bufTx[4] = {
        EE_CMD_READ,
        (uint8_t) (eepromAddr >> 8),
        (uint8_t) eepromAddr,
        0
    };

    uint8_t bufRx[4];
    CO_STORAGE_SS_LOW();
    EE_SPIWriteRead(bufTx, bufRx, 4);
    CO_STORAGE_SS_HIGH();

    /* If data in EEPROM differs, then write it to EEPROM.
     * Don't wait write to complete */
    if(bufRx[3] != data) {
        uint8_t buf[4] = {
            EE_CMD_WRITE,
            (uint8_t) (eepromAddr >> 8),
            (uint8_t) eepromAddr,
            data
        };

        EE_writeEnable();
        CO_STORAGE_SS_LOW();
        EE_SPIWriteRead(buf, NULL, 4);
        CO_STORAGE_SS_HIGH();
    }

    return true;
}


/**
 * Enable write operation in EEPROM. It is called before every writing to it.
 */
static inline void EE_writeEnable (void)
{
    uint32_t cmd = EE_CMD_WREN;

    CO_STORAGE_SS_LOW();

#ifdef 0 //C2000_PORT
    uint32_t dataFrame = 0x00FF0000; // with dummy data

    dataFrame = ((uint32_t)cmd << 24);
    spiXmit(dataFrame, 2);
#else
    /* write byte */
    EE_SPIWriteRead(&cmd, NULL, 1);
#endif
    CO_STORAGE_SS_HIGH();
}


/**
 * Write eeprom status register.
 *
 * Make sure EE_isWriteInProcess() is false before and after function call
 *
 * @param data Data byte to be written to status register.
 */
static inline void EE_writeStatus ( uint8_t ucData )
{
    uint8_t cmd[] = { EE_CMD_WRSR, ucData };
    uint8_t readDummy[2];

    EE_writeEnable();

    CO_STORAGE_SS_LOW();

    /* write two bytes */
    EE_SPIWriteRead (cmd, readDummy, 2);

    CO_STORAGE_SS_HIGH();
}


/**
 * Read eeprom status register.
 *
 * @return Data read from the status register.
 */
static inline uint8_t EE_readStatus ( void )
{
    uint8_t cmd[] = { EE_CMD_RDSR, 0 };
    /* volatile */ uint8_t read[2];

    CO_STORAGE_SS_LOW();
#ifdef C2000_PORT
    uint32_t E2PROM_Data = 0;


    E2PROM_Data = spiReceive(0x05FF0000, 2);

    CO_STORAGE_SS_HIGH();

    return (E2PROM_Data & 0xFF);

#else
    /* write two bytes */
    EE_SPIWriteRead (cmd, read, 2);
#endif

    CO_STORAGE_SS_HIGH();

    return read[1];
}
/******************************************************************************/


#endif /* (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE */
