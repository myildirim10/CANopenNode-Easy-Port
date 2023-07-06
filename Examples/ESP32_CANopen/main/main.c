/**
  ******************************************************************************
  * @file           : main.c
  * @author 		    : Muhammed YILDIRIM
  * @brief          : Main program body
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
// TEST FILE
//  . /home/muhammed/workspace/sdk/esp/esp-idf/export.sh
/* Includes ------------------------------------------------------------------*/
#include "CANopenNode.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

/* Defines -------------------------------------------------------------------*/

/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void TimerConfig (void);
static void CANReceiveInterruptHandler(void* args);
static void CANTimerInterruptHandler(void* args);


/* Functions ----------------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval Status 
  */
void app_main(void)
{
    
    xCANopenNodeInit();
    TimerConfig();


    while (1)
    {
      vCANopenNodeProcess();
    }

}


static void TimerConfig (void)
{
    const esp_timer_create_args_t CANTimerInterruptArgs = {
            .callback = &CANTimerInterruptHandler,
            /* name is optional, but may help identify the timer when debugging */
            .name = "CANopenTimerInterrupt"
    };

    const esp_timer_create_args_t CANReceiveInterruptArgs = {
    .callback = &CANReceiveInterruptHandler, /*Timer Interrupt Callback */
    .name = "CANopenReceiveInterrupt"};   /* Optional Task Name for debugging */

    esp_timer_handle_t receiveTimer;
    ESP_ERROR_CHECK(esp_timer_create(&CANTimerInterruptArgs, &receiveTimer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(receiveTimer, 1000));

    esp_timer_handle_t periodicTimer;
    ESP_ERROR_CHECK(esp_timer_create(&CANReceiveInterruptArgs, &periodicTimer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodicTimer, 1000));
}


static void CANReceiveInterruptHandler(void* args)
{
   vCANopenNodeReceiveInterrupt();
   vTaskDelay(10 / portTICK_PERIOD_MS);
}


static void CANTimerInterruptHandler(void* args)
{
    vCANopenNodeTimerInterrupt();
}