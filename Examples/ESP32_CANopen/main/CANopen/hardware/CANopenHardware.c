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

#include "stdio.h"                                     
#include "driver/twai.h"


/* Defines -------------------------------------------------------------------*/
#define TX_GPIO_NUM                     (GPIO_NUM_21)
#define RX_GPIO_NUM                     (GPIO_NUM_22)
#define TX_TASK_PRIO                    8               //Sending task priority
#define RX_TASK_PRIO                    9               //Receiving task priority

/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, TWAI_MODE_NORMAL);
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

/* Private function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
 * @brief CAN Hardware Initialize
 * 
 * @return CANopenHardwareStatusTypeDef_t 
 */
CANopenHardwareStatusTypeDef_t xCANopenHardwareInit (void)
{
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
        return CAN_OPEN_HARDWARE_ERROR;

    if (twai_start() != ESP_OK)
        return CAN_OPEN_HARDWARE_ERROR;

    return CAN_OPEN_HARDWARE_OK;
}


/**
 * @brief Transmit function for LOG
 * 
 */
void vLogTransmit (int32_t lCharacter)
{
    printf("%c", (char)lCharacter);
}


/**
 * @brief Reset MCU
 * 
 */
void vResetModule (void)
{
    esp_restart();
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
    twai_status_info_t esp_twai_hw_status;
    twai_message_t receive_can_message;

    twai_get_status_info(&esp_twai_hw_status);

    if(esp_twai_hw_status.msgs_to_rx != 0)
    {
        twai_receive(&receive_can_message, pdMS_TO_TICKS(1000));
        xMessage->ident = receive_can_message.identifier;
        xMessage->DLC = receive_can_message.data_length_code;

        for (uint8_t i = 0; i < 8; i++)
        {
            xMessage->data[i] = receive_can_message.data[i];                     
        }
        return CAN_OPEN_NODE_OK;
    }

    else
        return CAN_OPEN_NODE_ERROR;  
        
}