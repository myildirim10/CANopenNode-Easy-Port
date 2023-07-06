/**
  ******************************************************************************
  * @file           : CANopenNode.h
  * @author         : Muhammed YILDIRIM
  * @version        : 1.0
  * @date           : April 2022
  * @brief          : Header for CANopenNode.c file.
  *                   This file contains the common defines of the application.
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
  ******************************************************************************
  * @HowToUse

  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_OPEN_NODE_H
#define __CAN_OPEN_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#define CAN_OPEN_NODE_ID                              1
#define CAN_OPEN_NODE_BAUDRATE                        1000

/* Enum definitions ----------------------------------------------------------*/
/**
 * @brief CANopenNode Status
 * 
 */
typedef enum
{
    CAN_OPEN_NODE_OK,
	CAN_OPEN_NODE_ERROR
	
} CANopenNodeStatusTypeDef_t;


/* Structure definitions -----------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
CANopenNodeStatusTypeDef_t xCANopenNodeInit (void);
void vCANopenNodeProcess (void);
void vCANopenNodeReceiveInterrupt (void);
void vCANopenNodeTimerInterrupt (void);


#ifdef __cplusplus
}
#endif

#endif /* __CAN_OPEN_NODE_H */
