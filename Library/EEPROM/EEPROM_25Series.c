/**
  ******************************************************************************
  * @file           : EEPROM_25Series.c
  * @brief          : EEPROM XX25 Series EEPROM (AT25256B, CAV25256...) Library
  *                   This library based on SPI Communication
  ******************************************************************************
  * This program is made for Wat Motor Company
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "EEPROM_25Series.h"
#include "EEPROM_25Series_Hardware.h"
#include <stdint.h>


/* Defines -------------------------------------------------------------------*/
/**
 *  EEPROM INSTRUCTION SET
 */
#define EEPROM_WRSR		                    ( 0b00000001 )      // 0x01
#define EEPROM_WRITE	                    ( 0b00000010 )      // 0x02
#define EEPROM_READ		                    ( 0b00000011 )      // 0x03
#define EEPROM_WRDI		                    ( 0b00000100 )      // 0x04
#define EEPROM_RDSR		                    ( 0b00000101 )      // 0x05
#define EEPROM_WREN		                    ( 0b00000110 ) 	    // 0x06

#define MAX_BUSY_WAIT						( 100 )
#define EEPROM_CHIP_SELECT_DELAY			( ) 				// Min 30 ns delay time
#define EEPROM_WRITE_TIMEOUT				( 400 )


/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static uint8_t ucEEPROM_ReadStatus ( void );
static EEPROM_Status_t xEEPROM_WritePage ( const uint16_t usStartAddress, const uint8_t *pucWriteData, const uint8_t ucDataSize );


/* Functions ----------------------------------------------------------------*/
/**
  * @brief  Initialize EEPROM
  * @retval Status
  */
EEPROM_Status_t xEEPROM_Init ( void )
{
	return xEEPROM_IsReady();
}


/**
  * @brief  EEPROM is ready or not
  * @retval Status
  */
EEPROM_Status_t xEEPROM_IsReady ( void )
{
	uint16_t usIndex;

	for ( usIndex = 0; usIndex < MAX_BUSY_WAIT; usIndex++ )
	{
	    if ( ucEEPROM_ReadStatus() )
		{
			return EEPROM_STATUS_SUCCESS;
		}
	}

	return EEPROM_STATUS_ERROR;
}


/**
  * @brief  Read Status EEPROM
  * @retval 1: if EEPROM is ready
  * 		0: if EEPROM is not ready
  */
static uint8_t ucEEPROM_ReadStatus ( void )
{
	volatile uint8_t ucTempData;

	vSPI_ChipSelect(EEPROM_CS_STATE_LOW);
	ucSPI_TransmitReceive(EEPROM_RDSR);
	ucTempData = ucSPI_TransmitReceive(0x00);
	vSPI_ChipSelect(EEPROM_CS_STATE_HIGH);

	return !(ucTempData & 0x01);
}


/**
  * @brief  Read byte given EEPROM address
  * @param  usAddress: Address
  */
uint8_t ucEEPROM_ReadByte ( const uint16_t usAddress )
{
	volatile uint8_t ucTempData;

	vSPI_ChipSelect(EEPROM_CS_STATE_LOW);
	ucSPI_TransmitReceive(EEPROM_READ);
	ucSPI_TransmitReceive((usAddress >> 8) & 0xFF);
	ucSPI_TransmitReceive(usAddress & 0xFF);
	ucTempData = ucSPI_TransmitReceive(0x00);
	vSPI_ChipSelect(EEPROM_CS_STATE_HIGH);

	return ucTempData;
}


/**
  * @brief  Read one 16-bit word (little endian) from EEPROM address
  * @param  usAddress: Address
  */
uint16_t usEEPROM_ReadWord ( const uint16_t usAddress )
{
	volatile uint16_t usTempData;

	usTempData = ucEEPROM_ReadByte(usAddress);
	usTempData |= (uint16_t)ucEEPROM_ReadByte((usAddress + 1)) << 8;

	return usTempData;
}


/**
  * @brief  Write a byte to EEPROM address
  * @param  usAddress: Address
  * @param  ucValue: Value
  */
void vEEPROM_WriteByte ( const uint16_t usAddress, const uint8_t ucValue )
{
	vSPI_ChipSelect(EEPROM_CS_STATE_LOW);
	ucSPI_TransmitReceive(EEPROM_WREN);		/* Write Enable */
	vSPI_ChipSelect(EEPROM_CS_STATE_HIGH);

	vSPI_ChipSelect(EEPROM_CS_STATE_LOW);
	ucSPI_TransmitReceive(EEPROM_WRITE);
	ucSPI_TransmitReceive((usAddress >> 8) & 0xFF);
	ucSPI_TransmitReceive(usAddress & 0xFF);
	ucSPI_TransmitReceive(ucValue);
	vSPI_ChipSelect(EEPROM_CS_STATE_HIGH);

}


/**
  * @brief  Write a word value to EEPROM address
  * @param  usAddress: Address
  * @param  usValue: Value
  */
void vEEPROM_WriteWord ( const uint16_t usAddress, const uint16_t usValue )
{
	vEEPROM_WriteByte(usAddress, usValue);
	vEEPROM_WriteByte(usAddress+1, ((usValue>>8) & 0xFF));
}


/**
  * @brief  Update byte to EEPROM address
  * @param  usAddress: Address
  * @param  usValue: Value
  */
void vEEPROM_UpdateByte ( const uint16_t usAddress, const uint8_t ucValue )
{
	if ( ucEEPROM_ReadByte(usAddress) != ucValue )
	{
		vEEPROM_WriteByte(usAddress, ucValue);
	}
}


/**
  * @brief  Update word to EEPROM address
  * @param  usAddress: Address
  * @param  usValue: Value
  */
void vEEPROM_UpdateWord ( const uint16_t usAddress, const uint16_t usValue )
{
	volatile uint16_t usWordData = usEEPROM_ReadWord(usAddress);

	if ( usWordData != usValue )
	{
		vEEPROM_WriteWord (usAddress, usValue);
	}
}


/**
  * @brief  Write data to EEPROM given address and data size
  * @param  usStartAddress: Start address EPPROM
  * @param  pucWriteData: Address of data to write
  * @param  usDataSize: Size of data to write
  * @retval Status
  */
static EEPROM_Status_t xEEPROM_WritePage ( const uint16_t usStartAddress, const uint8_t *pucWriteData, const uint8_t ucDataSize )
{
	EEPROM_Status_t status;
	uint16_t usIndex;
	uint16_t usWaitIndex;

	status = xEEPROM_IsReady();

	for ( usIndex = 0; usIndex < ucDataSize; usIndex++ )
	{
		vEEPROM_WriteByte((usStartAddress+usIndex), pucWriteData[usIndex]);

		for ( usWaitIndex = 0; usWaitIndex <= EEPROM_WRITE_TIMEOUT; usWaitIndex++ )
		{
			if ( usWaitIndex == EEPROM_WRITE_TIMEOUT )
			{
				status = xEEPROM_IsReady();

				if ( status != EEPROM_STATUS_SUCCESS )
					return status;
			}
		}

	}

	return status;
}


/**
  * @brief  Write data to EEPROM given address and data size
  * @param  usStartAddress: Start address EPPROM
  * @param  pucWriteData: Address of data to write
  * @param  usDataSize: Size of data to write
  * @retval Status
  */
EEPROM_Status_t vEEPROM_Write ( const uint16_t usStartAddress, const uint8_t *pucWriteData, const uint16_t usDataSize )
{
	EEPROM_Status_t status;
	uint16_t usIndex;
	uint16_t usPacketIndex;
	uint16_t usNumberBytesPacket;
	uint16_t usNumberBytesWastePacket;

	usPacketIndex = 0;
	usNumberBytesPacket = usDataSize / EEPROM_PAGE_SIZE;
	usNumberBytesWastePacket = usDataSize % EEPROM_PAGE_SIZE;

	for ( usIndex = 0; usIndex < usNumberBytesPacket; usIndex++)
	{
		status = xEEPROM_WritePage((usStartAddress + usPacketIndex), (pucWriteData + usPacketIndex), EEPROM_PAGE_SIZE);
		usPacketIndex += EEPROM_PAGE_SIZE;

		if (status != EEPROM_STATUS_SUCCESS)
		{
			return status;
		}
	}

	if (usNumberBytesWastePacket)
	{
		status = xEEPROM_WritePage((usStartAddress + usPacketIndex), (pucWriteData + usPacketIndex), usNumberBytesWastePacket);
	}

	return status;
}


/**
  * @brief  Read data to EEPROM given address and data size
  * @param  usStartAddress: Start address EPPROM
  * @param  pucWriteData: Address of data to write
  * @param  usDataSize: Size of data to write
  * @retval Status
  */
EEPROM_Status_t vEEPROM_Read ( const uint16_t usStartAddress, uint8_t *pucReadData, const uint16_t usDataSize )
{
	uint16_t usIndex;

	for ( usIndex = 0; usIndex < usDataSize; usIndex++ )
	{
		pucReadData[usIndex] = ucEEPROM_ReadByte((usStartAddress+usIndex));
	}

	return xEEPROM_IsReady();
}
