/**
  ******************************************************************************
  * @file           : EEPROM_25Series.h
  * @brief          : EEPROM XX25 Series EEPROM (AT25256B, CAV25256...) Library
  *                   This library based on SPI Communication
  * @author         : Muhammed YILDIRIM
  * @version        : 1.0
  * @date           : June 2022
  ******************************************************************************
  *
  ******************************************************************************
  * @HowToUse
  * 1. EEPROM kütüphanesi SPI ile çalıştığı için SPI transmit ve receive
  *    fonksiyonları eklenmesi gerekir. SPI çevresel birimi ayarlandıktan
  *    sonra, "Hardware_EEPROM_25Series.h" dosyasında ucSPI_TransmitReceive
  *    fonksiyonu içerisine SPI Transmit ve Receive fonksiyonu eklenir.
  *    (Örneğin SPI ayarları CAV25256 entegresi için; SPI Mode 0-0,
  *    Word Length:8, Frame Length:8, Transmit Mode: Direct,
  *    Receive Mode: Direct, Operation Mode: Full Duplex,
  *    Bus Speed: 1MHz seçilmiştir)
  *
  * 2. SPI Chip Select için Digital I/O ayarlanıp vSPI_ChipSelect fonksiyonu
  *    içinde yazılmalıdır.
  */

#ifndef __EEPROM_25Series_H_
#define __EEPROM_25Series_H_


/* Includes ------------------------------------------------------------------*/
#include "stdint.h"


/* Defines -------------------------------------------------------------------*/
#define EEPROM_PAGE_SIZE					( 64 )
#define EEPROM_TOTAL_SIZE					( 0x8000 )			// for 256-Kb (32 Kbyte) EEPROMs


/* Enum definitions ----------------------------------------------------------*/
typedef enum
{
	EEPROM_STATUS_SUCCESS,
	EEPROM_STATUS_ERROR

} EEPROM_Status_t;


/* Structure definitions -----------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
EEPROM_Status_t xEEPROM_Init ( void );
EEPROM_Status_t xEEPROM_IsReady ( void );
uint8_t ucEEPROM_ReadByte ( const uint16_t usAddress );
uint16_t usEEPROM_ReadWord ( const uint16_t usAddress );
void vEEPROM_WriteByte ( const uint16_t usAddress, const uint8_t ucValue );
void vEEPROM_WriteWord ( const uint16_t usAddress, const uint16_t usValue );
void vEEPROM_UpdateByte ( const uint16_t usAddress, const uint8_t ucValue );
void vEEPROM_UpdateWord ( const uint16_t usAddress, const uint16_t usValue );
EEPROM_Status_t vEEPROM_Write ( const uint16_t usStartAddress, const uint8_t *pucWriteData, const uint16_t usDataSize );
EEPROM_Status_t vEEPROM_Read ( const uint16_t usStartAddress, uint8_t *pucReadData, const uint16_t usDataSize );


#endif /* __EEPROM_25Series_H_ */
