/**
 * @file spiDriver.c
 * @date 2019-04-13
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

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/
#include "spiDriver.h"


/*******************************************************************************
 * GLOBAL[EXTERNAL] FUNCTIONS
 *******************************************************************************/

/*******************************************************************************
 * GLOBAL[EXTERNAL] VARIABLES
 *******************************************************************************/

/*******************************************************************************
 * ENUMS
 *******************************************************************************/

/*******************************************************************************
 * DATA STRUCTURES
 *******************************************************************************/

/*******************************************************************************
 * MACROS
 *******************************************************************************/
/* PUSH data to SPI buffer - left adjusted */
#define SPIA_PUSH(TX) SpiaRegs.SPITXBUF = (TX << 8)

/* POP data from SPI buffer - right adjusted */
#define SPIA_POP SpiaRegs.SPIRXBUF

/*******************************************************************************
 * LOCAL VARIABLES
 *******************************************************************************/
_SPIConfiguration   SPIConfiguration;
int                 assert = 0;
/*******************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *******************************************************************************/

/*******************************************************************************
 * LOCAL CONSTANTS
 *******************************************************************************/

/*******************************************************************************
 * INTERFACE FUNCTIONS
 *******************************************************************************/
#if 1
void InitSpiaGpio()
{

   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   // GPIO16: MOSI
   // GPIO17: MISO
   // GPIO18: CLK
   // GPIO19: STE
#if 0
   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO54 (SPISIMOA)
   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO55 (SPISOMIA)
   GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO56 (SPICLKA)


/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.


    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input  (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input  (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input  (SPICLKA)



/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO56 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO55 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO54 as SPISIMOA

/* Configure EEPROM Select Pin*/
    GpioDataRegs.GPASET.bit.GPIO19 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;

    GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;
#endif
#if 1
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   //Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   //Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   //Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   //Enable pull-up on GPIO19 (SPISTEA)

    //GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0; //Enable pull-up on GPIO54 (SPISIMOA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0; //Enable pull-up on GPIO55 (SPISOMIA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0; //Enable pull-up on GPIO56 (SPICLKA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0; //Enable pull-up on GPIO57 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    //GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input GPIO16 (SPISIMOA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO17 (SPISOMIA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO18 (SPICLKA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO19 (SPISTEA)

    //
    // Configure SPI-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SPI
    // functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    //GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; // Configure GPIO54 as SPISIMOA
    //GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
    //GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
    //GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

    GpioDataRegs.GPASET.bit.GPIO23 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;

#endif
    EDIS;
}
#endif

/* SPI init */
void EEPROM_InitSPI(void)
{

    InitSpiaGpio();
    asm(" EALLOW"); /* Enable EALLOW protected register access */
    /* enable peripheral clock */
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1; /* SPI-A */

    /* Initialize SPI periphery */
    SpiaRegs.SPICCR.bit.SPISWRESET = 0; /* Reset SPI and hold */
    SpiaRegs.SPICCR.all = 0x0047;       /* Loopback off  8-bit character, Clock Polarity 0 */
    SpiaRegs.SPICTL.all = 0x0006;       /* master, xmit enable */
    SpiaRegs.SPIBRR = 24;               /* SYSCLK = 90Mhz = LSPCLK, baud rate = LSPCLK/(SPIBRR+1) = 6 MHz */
    SpiaRegs.SPISTS.all = 0x0000;       /* reset all status information */
    SpiaRegs.SPIPRI.bit.FREE = 1;       /* priority control settings - free run */
    SpiaRegs.SPICCR.bit.SPISWRESET = 1; /* Release from SPI reset */
    /* reset both fifos */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 0;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0; /*and keep them in reset during configuration */
    /* configure fifos  */
    SpiaRegs.SPIFFTX.all = 0xC000; /* Enable FIFO's, do not use interrupts */
    SpiaRegs.SPIFFRX.all = 0x0000; /* Set RX FIFO, do not use interrupts  */
    SpiaRegs.SPIFFCT.all = 0x0000; /* no delay between FIFO and TXBUF */
    /* releasing fifos from reset */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1; /* OK */

    /* error checking, fifo pointers should be zero */
    if ((SpiaRegs.SPIFFTX.bit.TXFFST != 0) || (SpiaRegs.SPIFFRX.bit.RXFFST != 0)) { assert++; }

    asm(" EDIS"); /* Disable EALLOW protected register access */

   // GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;

}

#if 0
void InitSPI2(void)
{

    InitSpiaGpio();
    asm(" EALLOW"); /* Enable EALLOW protected register access */
    /* enable peripheral clock */
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1; /* SPI-A */

    /* Initialize SPI periphery */
    SpiaRegs.SPICCR.bit.SPISWRESET = 0; /* Reset SPI and hold */
    SpiaRegs.SPICCR.all = 0x0047;       /* Loopback off  8-bit character, Clock Polarity 0 */
    SpiaRegs.SPICTL.all = 0x0006;       /* master, xmit enable */
    SpiaRegs.SPIBRR = 24;               /* SYSCLK = 90Mhz = LSPCLK, baud rate = LSPCLK/(SPIBRR+1) = 6 MHz */
    SpiaRegs.SPISTS.all = 0x0000;       /* reset all status information */
    SpiaRegs.SPIPRI.bit.FREE = 1;       /* priority control settings - free run */
    SpiaRegs.SPICCR.bit.SPISWRESET = 1; /* Release from SPI reset */
    /* reset both fifos */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 0;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0; /*and keep them in reset during configuration */
    /* configure fifos  */
    SpiaRegs.SPIFFTX.all = 0xC000; /* Enable FIFO's, do not use interrupts */
    SpiaRegs.SPIFFRX.all = 0x0000; /* Set RX FIFO, do not use interrupts  */
    SpiaRegs.SPIFFCT.all = 0x0000; /* no delay between FIFO and TXBUF */
    /* releasing fifos from reset */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1; /* OK */

    /* error checking, fifo pointers should be zero */
    if ((SpiaRegs.SPIFFTX.bit.TXFFST != 0) || (SpiaRegs.SPIFFRX.bit.RXFFST != 0)) { assert++; }

    asm(" EDIS"); /* Disable EALLOW protected register access */

    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 1;

}
#endif

/* Exchanges 4 Bytes via SPI, blocks until finished, 32b architecture = no pointer */
void spiXmit(uint32_t data, uint8_t size)
{

    int byteCounter=0;
    /* empty RX and TX 4B FIFOs */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 0; /* reset FIFOs */
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;

    SpiaRegs.SPIFFTX.bit.TXFFIL = size; /* Enable FIFO's, do not use interrupts */
    SpiaRegs.SPIFFRX.all = size;
    asm(" NOP"); /* probably not needed */
    asm(" NOP"); /* probably not needed */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1; /* release from reset */

 //   for(byteCounter=0; byteCounter <size ; byteCounter++)
 //   {
        SpiaRegs.SPITXBUF =  (uint16_t)data; // (data >> 8*(3-byteCounter) ) <<8 ;
 //   }

    /* wait until the transmission is finished */
    while (SpiaRegs.SPIFFRX.bit.RXFFST < size) ;

}

/* spi receive */
uint32_t spiReceive(uint32_t data, uint8_t size)
{
    int byteCounter=0;
    uint32_t rxval=0;
    /* empty RX and TX @size FIFOs */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 0; /* reset FIFOs */
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;

    SpiaRegs.SPIFFTX.bit.TXFFIL = size; /* Enable FIFO's, do not use interrupts */
    SpiaRegs.SPIFFRX.all = size;
    asm(" NOP"); /* probably not needed */
    asm(" NOP"); /* probably not needed */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1; /* release from reset */

    for(byteCounter=0; byteCounter <size ; byteCounter++)
      {
          SpiaRegs.SPITXBUF =  (data >> 8*(3-byteCounter) ) <<8 ;
      }

    /* wait until the transmission is finished */
    while (SpiaRegs.SPIFFRX.bit.RXFFST < size) ;

    /* get data from RX FIFO */
    rxval = ((rxval << 8) | SPIA_POP);
    for(byteCounter=0; byteCounter<size-1 ; byteCounter++)
          {
        rxval = ((rxval << 8) | SPIA_POP);
     //  rxval |= (SPIA_POP & 0xFF ) << (8*byteCounter);
          }

    return (rxval);
}

#if 0
/*spi test*/
uint32_t spiTest(uint32_t data, uint8_t size)
{
    int byteCounter=0;
    uint32_t rxval=0;
    /* empty RX and TX @size FIFOs */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 0; /* reset FIFOs */
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;

    SpiaRegs.SPIFFTX.bit.TXFFIL = 6; /* Enable FIFO's, do not use interrupts */
    SpiaRegs.SPIFFRX.all = 6;
    asm(" NOP"); /* probably not needed */
    asm(" NOP"); /* probably not needed */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1; /* release from reset */

    for(byteCounter=0; byteCounter <size ; byteCounter++)
      {
          SpiaRegs.SPITXBUF =  (data >> 8*(3-byteCounter) ) <<8 ;
      }

    /* wait until the transmission is finished */
    while (SpiaRegs.SPIFFRX.bit.RXFFST < size) ;

    /* get data from RX FIFO */
    rxval = ((rxval << 8) | SPIA_POP);
    for(byteCounter=0; byteCounter<size-1 ; byteCounter++)
          {
        rxval = ((rxval << 8) | SPIA_POP);
     //  rxval |= (SPIA_POP & 0xFF ) << (8*byteCounter);
          }

    return (rxval);
}
#endif

/* configure spi */
void ConfigureSPI(_SPIConfiguration request)
{
    switch (request) {
        case PGA_IC:
//            pga411_InitSPI();
            break;
        case EEPROM_IC:
            EEPROM_InitSPI();
            break;
        default:
            break;
    }
}
