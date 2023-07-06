/**
 * @file spiDriver.h
 * @date 2019-13-02
 * @author OguzEmre & OguzAtsiz
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

#ifndef SPIA_SPIDRIVER_H_
#define SPIA_SPIDRIVER_H_

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include "stdint.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP28x_Project.h"
#include "stdbool.h"

/*******************************************************************************
* EXPORTED DEFINES
********************************************************************************/

#define PGA_SPI_CHIP_SELECT

#define EEPROM_SPI_CHIP_SELECT      GpioDataRegs.GPACLEAR.bit.GPIO23    = 1
#define EEPROM_SPI_CHIP_UNSELECT    GpioDataRegs.GPASET.bit.GPIO23      = 1

//Chip selection definitions
#define PGA                     1
#define EEPROM                  2

/*******************************************************************************
* EXPORTED TYPES
********************************************************************************/
typedef enum {
    PGA_IC,
    EEPROM_IC
} _SPIConfiguration;

/*******************************************************************************
* EXPORTED MACROS
********************************************************************************/

/*******************************************************************************
* EXPORTED CONSTANTS
********************************************************************************/

/*******************************************************************************
* EXPORTED VARIABLES
********************************************************************************/
extern _SPIConfiguration SPIConfiguration;

/*******************************************************************************
* API FUNCTIONS
********************************************************************************/

#if 0
/**
 * @brief init spi
 *
 */
void InitSPI2(void);

/**
 * @brief init spi
 *
 */
void EEPROM_InitSPIA(void);
#endif

/**
 * @brief transmit data
 *
 */
void spiXmit(uint32_t, uint8_t size);

/**
 * @brief receive data
 *
 */
uint32_t spiReceive(uint32_t, uint8_t size);

/**
 * @brief configure spi
 *
 */
void ConfigureSPI(_SPIConfiguration request);

#endif /* SPIA_SPIDRIVER_H_ */
