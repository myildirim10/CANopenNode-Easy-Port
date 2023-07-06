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

#define TEST_STM32

#ifdef TEST_ESP32
#include "stdio.h"                                     
#include "driver/twai.h"
#endif
#ifdef TEST_STM32
#include "can.h"
#include "usart.h"
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

/* Functions -----------------------------------------------------------------*/
/**
 * @brief CAN Hardware Initialize
 * 
 * @return CANopenHardwareStatusTypeDef_t 
 */
CANopenHardwareStatusTypeDef_t xCANopenHardwareInit (void)
{
#ifdef TEST_ESP32
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
        return CAN_OPEN_HARDWARE_ERROR;

    if (twai_start() != ESP_OK)
        return CAN_OPEN_HARDWARE_ERROR;
#endif
#ifdef TEST_STM32
    /*##-2- Configure the CAN Filter ###########################################*/
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
    return CAN_OPEN_HARDWARE_OK;
}


/**
 * @brief Transmit function for LOG
 * 
 */
void vLogTransmit (int32_t lCharacter)
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
void vResetModule (void)
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
CANopenNodeStatusTypeDef_t xCANTransmitMessage (CO_CANtx_t *xMessage)
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

    else
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
    return CAN_OPEN_NODE_ERROR;
}


/**
 * @brief CAN Receive message
 * @param message 
 * @return CANopenNodeStatusTypeDef_t 
 *         CAN_OPEN_NODE_OK: Message received successfully
 *         CAN_OPEN_NODE_ERROR: No received message
 */
CANopenNodeStatusTypeDef_t xCANReceiveMessage (CO_CANrxMsg_t *xMessage)
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
        
}
