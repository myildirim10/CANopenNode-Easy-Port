/**
  ******************************************************************************
  * @file           : EEPROM_25Series_Hardware.h
  *                   This library is made for SPI Communication with EEPROM
  * @author         : Muhammed YILDIRIM
  * @version        : 1.0
  * @date           : June 2022
  ******************************************************************************
  *
  ******************************************************************************
  */

#ifndef __EEPROM_25_SERIES_HARDWARE__H_
#define __EEPROM_25_SERIES_HARDWARE__H_

//#define INFINEON

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#ifdef INFINEON
#include <DAVE.h>
#endif

/* Defines -------------------------------------------------------------------*/


/* Enum definitions ----------------------------------------------------------*/
typedef enum
{
	EEPROM_CS_STATE_LOW,
	EEPROM_CS_STATE_HIGH

} Hardware_SPI_CS_State_t;


/* Structure definitions -----------------------------------------------------*/


/* Function prototypes -------------------------------------------------------*/


/**
  * @brief  Example static function
  * @param  ucTxData: SPI transmit data
  * @retval Receive value from SPI
  */
static inline uint8_t ucSPI_TransmitReceive ( const uint8_t ucTxData )
{
	volatile uint8_t ucRxData;

	// SPI Hardware Transmit Receive Function
#ifdef INFINEON
	SPI_MASTER_Transfer(&SPI_MASTER_0, &ucTxData, &ucRxData, 1);
#endif
	return ucRxData;
}


static inline void vSPI_ChipSelect ( const Hardware_SPI_CS_State_t xState )
{
	// Chip Select IO Low or High State Function
#ifdef INFINEON
	if (xState == EEPROM_CS_STATE_LOW)
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);

	else
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
#endif

}


#endif /* __EEPROM_25_SERIES_HARDWARE__H_ */
