/**
  ******************************************************************************
  * @file           : CANopenHardware.c
  * @author 		: Muhammed YILDIRIM
  * @brief          : CANopen Hardware driver file
  ******************************************************************************
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "CANopenHardware.h"
#include "CANopenNode.h"

#define TEST_TI_TMS320F28335
#define ENABLE_EEPROM

#ifdef TEST_ESP32
#include "stdio.h"                                     
#include "driver/twai.h"
#endif
#ifdef TEST_STM32
#include "can.h"
#include "usart.h"
#endif
#ifdef TEST_TI_TMS320F28335
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdint.h>
#endif
#ifdef ENABLE_EEPROM
#include "301/crc16-ccitt.h"
#include "spiDriver.h"
#endif

/* Defines -------------------------------------------------------------------*/
#ifdef TEST_ESP32
#define TX_GPIO_NUM                     (GPIO_NUM_21)
#define RX_GPIO_NUM                     (GPIO_NUM_22)
#define TX_TASK_PRIO                    8               //Sending task priority
#define RX_TASK_PRIO                    9               //Receiving task priority
#endif

/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#ifdef TEST_ESP32
static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, TWAI_MODE_NORMAL);
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
#endif


/* Private function prototypes -----------------------------------------------*/
#ifdef TEST_TI_TMS320F28335
static void InitCanMailbox ( void );
static void InitTimer ( void );
#endif

/* External function prototypes -----------------------------------------------*/
#ifdef TEST_TI_TMS320F28335
extern interrupt void Ecan0ISR ( void );
extern interrupt void CPUTimerISR ( void );
#endif

#ifdef ENABLE_EEPROM

#endif

/* Functions -----------------------------------------------------------------*/
/**
 * @brief CAN Hardware Initialize
 * 
 * @return CANopenHardwareStatusTypeDef_t 
 */
CANopenHardwareStatusTypeDef_t xCANopenHardwareInit ( void )
{
#ifdef TEST_ESP32
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
        return CAN_OPEN_HARDWARE_ERROR;

    if (twai_start() != ESP_OK)
        return CAN_OPEN_HARDWARE_ERROR;
#endif
#ifdef TEST_STM32
    /* Configure the CAN Filter */
    CAN_FilterTypeDef  sFilterConfig;

    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
      /* Filter configuration Error */
      Error_Handler();
      return CAN_OPEN_HARDWARE_ERROR;
    }

    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //enable interrupts

    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
        return CAN_OPEN_HARDWARE_ERROR;
    }
#endif

#ifdef TEST_TI_TMS320F28335
    /* In this case just initialize eCAN-A and eCAN-B */
    InitECan();

    /* Timer initialize */
    InitTimer();

    /* Mailbox initialize */
    InitCanMailbox();
#endif

    return CAN_OPEN_HARDWARE_OK;
}


/**
 * @brief Transmit function for LOG
 * 
 */
void vLogTransmit ( int32_t lCharacter )
{
#ifdef TEST_ESP32
    printf("%c", (char)lCharacter);
#endif
#ifdef TEST_STM32
    HAL_UART_Transmit(&huart2, (uint8_t *)&lCharacter, 1, 1000);
#endif
}


/**
 * @brief Reset MCU
 * 
 */
void vResetModule ( void )
{
#ifdef TEST_ESP32
    esp_restart();
#endif

}


/**
 * @brief CAN Transmit message
 * @param message 
 * @return CANopenNodeStatusTypeDef_t
 *         CAN_OPEN_NODE_OK: Transmit message successfully
 *         CAN_OPEN_NODE_ERROR: Error transmit message
 */
CANopenNodeStatusTypeDef_t xCANTransmitMessage ( CO_CANtx_t *xMessage )
{
#ifdef TEST_ESP32
    twai_message_t msg;
    msg.identifier = xMessage->ident;
    msg.data_length_code = xMessage->DLC;
    msg.flags = TWAI_MSG_FLAG_NONE;

    for (uint8_t i = 0; i < 8; i++)
      msg.data[i] = xMessage->data[i];

    esp_err_t ret = twai_transmit(&msg, pdMS_TO_TICKS(1000));

    if (ret == ESP_OK)
        return CAN_OPEN_NODE_OK;

#endif
#ifdef TEST_STM32
    CAN_TxHeaderTypeDef header;
    uint8_t data[8];
    uint32_t mailbox;

    header.DLC = xMessage->DLC;
    header.StdId = xMessage->ident;
    header.IDE = CAN_ID_STD;
    header.RTR = CAN_RTR_DATA;
    header.ExtId = 0x00;
    header.TransmitGlobalTime = DISABLE;

    for (uint8_t i = 0; i < 8; i++)
    {
    	data[i] = xMessage->data[i];
    }

	HAL_CAN_AddTxMessage(&hcan, &header, data, &mailbox);

	while(HAL_CAN_IsTxMessagePending(&hcan, mailbox));

	return CAN_OPEN_NODE_OK;

#endif
#ifdef TEST_TI_TMS320F28335
	volatile static struct ECAN_REGS ECanaShadow;

    uint16_t usNumberMailbox = 0;
    usNumberMailbox |= (1 << 5);

    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME5 = 0;
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    ECanaMboxes.MBOX5.MSGID.bit.IDE = 0;
    ECanaMboxes.MBOX5.MSGID.bit.STDMSGID = xMessage->ident;
    ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = xMessage->DLC;
    ECanaMboxes.MBOX5.MDL.byte.BYTE0 = xMessage->data[0];
    ECanaMboxes.MBOX5.MDL.byte.BYTE1 = xMessage->data[1];
    ECanaMboxes.MBOX5.MDL.byte.BYTE2 = xMessage->data[2];
    ECanaMboxes.MBOX5.MDL.byte.BYTE3 = xMessage->data[3];
    ECanaMboxes.MBOX5.MDH.byte.BYTE4 = xMessage->data[4];
    ECanaMboxes.MBOX5.MDH.byte.BYTE5 = xMessage->data[5];
    ECanaMboxes.MBOX5.MDH.byte.BYTE6 = xMessage->data[6];
    ECanaMboxes.MBOX5.MDH.byte.BYTE7 = xMessage->data[7];

    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME5 = 1;
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    ECanaRegs.CANTRS.all |= usNumberMailbox;

    do
    {
        ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    } while((ECanaShadow.CANTA.all & usNumberMailbox) == 0 );

#endif
    return CAN_OPEN_NODE_OK;
}


/**
 * @brief CAN Receive message
 * @param message 
 * @return CANopenNodeStatusTypeDef_t 
 *         CAN_OPEN_NODE_OK: Message received successfully
 *         CAN_OPEN_NODE_ERROR: No received message
 */
CANopenNodeStatusTypeDef_t xCANReceiveMessage ( CO_CANrxMsg_t *xMessage )
{
#ifdef TEST_ESP32
    twai_status_info_t esp_twai_hw_status;
    twai_message_t receive_can_message;

    twai_get_status_info(&esp_twai_hw_status);

    if(esp_twai_hw_status.msgs_to_rx != 0)
    {
        twai_receive(&receive_can_message, pdMS_TO_TICKS(1000));
        xMessage->ident = receive_can_message.identifier;
        xMessage->DLC = receive_can_message.data_length_code;

        for (uint8_t i = 0; i < 8; i++)
            xMessage->data[i] = receive_can_message.data[i];                     

        return CAN_OPEN_NODE_OK;
    }

    return CAN_OPEN_NODE_ERROR;
#endif
#ifdef TEST_STM32
   CAN_RxHeaderTypeDef header;
   uint8_t data[8];

   /* Get RX message */
   if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &header, data) != HAL_OK)
   {
     /* Reception Error */
     Error_Handler();
     return CAN_OPEN_NODE_ERROR;
   }

   xMessage->ident = header.StdId;
   xMessage->DLC = header.DLC;

   for (uint8_t i = 0; i < 8; i++)
   {
       xMessage->data[i] = data[i];
   }

   return CAN_OPEN_NODE_OK;
#endif

#ifdef TEST_TI_TMS320F28335
   volatile static struct MBOX *Mailbox;

   Mailbox = &ECanaMboxes.MBOX16;

   xMessage->ident = Mailbox->MSGID.bit.STDMSGID;
   xMessage->DLC = Mailbox->MSGCTRL.bit.DLC;
   xMessage->data[0] = Mailbox->MDL.byte.BYTE0;
   xMessage->data[1] = Mailbox->MDL.byte.BYTE1;
   xMessage->data[2] = Mailbox->MDL.byte.BYTE2;
   xMessage->data[3] = Mailbox->MDL.byte.BYTE3;
   xMessage->data[4] = Mailbox->MDH.byte.BYTE4;
   xMessage->data[5] = Mailbox->MDH.byte.BYTE5;
   xMessage->data[6] = Mailbox->MDH.byte.BYTE6;
   xMessage->data[7] = Mailbox->MDH.byte.BYTE7;

   return CAN_OPEN_NODE_OK;
#endif
}


#ifdef ENABLE_EEPROM
/**
 * Initialize eeprom device
 *
 * @return CANopenNodeStatusTypeDef_t
 */
CANopenNodeStatusTypeDef_t xEEPROMInit ( void )
{
    ConfigureSPI(EEPROM_IC);

    return CAN_OPEN_NODE_OK;
}


/**
 * Write to SPI and at the same time read from SPI.
 *
 * @param tx Ponter to transmitting data. If NULL, zeroes will be transmitted.
 * @param rx Ponter to data buffer, where received data wile be stored.
 * If null, Received data will be disregarded.
 * @param len Length of data buffers. Max SPI_FIFO_SIZE.
 */
void vEEPROMSPIWriteRead ( uint8_t *ucTX, uint8_t *ucRX, uint8_t ucLen )
{
    if (ucTX != NULL)
    {
        spiXmit(ucTX, ucLen);
    }

    if (ucRX != NULL)
    {
        spiReceive(ucRX, ucLen);
    }
}

/**
 * CS Pin Control EEPROM (for SPI device)
 *
 * @param bState High or Low.
 */
void vEEPROMCSPin ( bool_t bState )
{
    if(bState)
        GpioDataRegs.GPASET.bit.GPIO23      = 1;
    else
        GpioDataRegs.GPACLEAR.bit.GPIO23    = 1;

}


#endif


#ifdef TEST_TI_TMS320F28335
/**
 * @brief CAN Mailbox Init
 */
static void InitCanMailbox ( void )
{
    struct ECAN_REGS ECanaShadow;

    /* Configure Mailbox under test as a Re/Transmit mailbox */
    EALLOW;
    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD16 = 1;             // RX Mailbox
    ECanaShadow.CANMD.bit.MD5 = 0;              // TX Mailbox
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

    /* without considering id and the data can be received */
    ECanaMboxes.MBOX16.MSGID.bit.AME = 1;
    ECanaLAMRegs.LAM16.all = 0xFFFFFFFF;

    /* Enable Mailbox under test */
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME16 = 1;
    ECanaShadow.CANME.bit.ME5 = 1;
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    ECanaRegs.CANRMP.all = 0xFFFFFC00;
    EDIS;


    EALLOW;
    ECanaShadow.CANMIM.all=ECanaRegs.CANMIM.all;
    ECanaShadow.CANMIM.bit.MIM16=1;
    ECanaRegs.CANMIM.all=ECanaShadow.CANMIM.all;

    ECanaShadow.CANMIL.all = ECanaRegs.CANMIL.all;
    ECanaShadow.CANMIL.all = 0;              // 1-32 Mailbox No. is disconnected in the middle 0 produce
    ECanaRegs.CANMIL.all = ECanaShadow.CANMIL.all;

    ECanaShadow.CANGIM.all = ECanaRegs.CANGIM.all;
    ECanaShadow.CANGIM.bit.I0EN = 1 ;              //  trunk 0 Can make
    ECanaRegs.CANGIM.all = ECanaShadow.CANGIM.all;

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.STM = 0;    // 0-Normal
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
    EDIS;

    EALLOW;
    PieVectTable.ECAN0INTA = &Ecan0ISR;
    EDIS;

    IER |= M_INT9;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx5=1;     // R-CAN0  Receive email

    EINT;
    ERTM;
}

/**
 * @brief Initialize 1 milisecond timer interrupt
 */
static void InitTimer ( void )
{
    EALLOW;         // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &CPUTimerISR;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    InitCpuTimers();   // For this example, only initialize the Cpu Timers
#if (CPU_FRQ_150MHZ)
    //
    // Configure CPU-Timer 0 to interrupt every 1 milliseconds:
    // 150MHz CPU Freq, 50 millisecond Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 150, 1000);

    //
    // Use write-only instruction to set TSS bit = 0
    //
    CpuTimer0Regs.TCR.all = 0x4000;

    //
    // Enable CPU INT1 which is connected to CPU-Timer 0:
    //
    IER |= M_INT1;

    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    //EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM
#endif
}
#endif
