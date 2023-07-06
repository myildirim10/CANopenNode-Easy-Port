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
#include <stdlib.h>
#include "EEPROM_25Series.h"


/* Defines -------------------------------------------------------------------*/
#ifndef CO_STORAGE_EEPROM_TOTAL_SIZE
 #define CO_STORAGE_EEPROM_TOTAL_SIZE            EEPROM_TOTAL_SIZE
#endif
#ifndef CO_STORAGE_EEPROM_PAGE_SIZE
 #define CO_STORAGE_EEPROM_PAGE_SIZE             EEPROM_PAGE_SIZE
#endif


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
static size_t eepromAddrNextProt = 0x1000;			//  Default: CO_STORAGE_EEPROM_TOTAL_SIZE / 2;
static volatile uint32_t dummy;


/* Private function prototypes -----------------------------------------------*/


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
    if (xEEPROM_Init() == EEPROM_STATUS_SUCCESS)
        return true;

    return false;
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
	vEEPROM_Read(eepromAddr, data, len);
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
	if ( vEEPROM_Write(eepromAddr, data, (uint16_t)len) == EEPROM_STATUS_SUCCESS )
		return true;

	return false;
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
    uint8_t *buf = malloc(len*sizeof(uint8_t));

    vEEPROM_Read(eepromAddr, buf, len);

    crc = crc16_ccitt(buf, len, crc);

    free(buf);

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

	vEEPROM_UpdateByte(eepromAddr, data);

    return true;
}


/******************************************************************************/


#endif /* (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE */
