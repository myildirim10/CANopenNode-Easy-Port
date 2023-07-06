/**
  ******************************************************************************
  * @file           : CANopenNode.h
  * @author         : Muhammed YILDIRIM
  * @version        : 1.0
  * @date           : April 2022
  * @brief          : Header for CANopenNode.c file.
  *                   This file contains the common defines of the application.
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


/**
 * @brief NMT Status
 *
 */
typedef enum
{
    NMT_UNKNOWN = -1,
    /** 0, Device is initializing */
    NMT_INITIALIZING = 0,
    /** 127, Device is in pre-operational state */
    NMT_PRE_OPERATIONAL = 127,
    /** 5, Device is in operational state */
    NMT_OPERATIONAL = 5,
    /** 4, Device is stopped */
    NMT_STOPPED = 4

} CANopenNodeNMTStatusTypeDef_t;


/* Structure definitions -----------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
CANopenNodeStatusTypeDef_t xCANopenNodeInit ( void );
void vCANopenNodeProcess ( void );
void vCANopenNodeReceiveInterrupt ( void );
void vCANopenNodeTimerInterrupt ( void );
CANopenNodeNMTStatusTypeDef_t xCANopenNodeGetNMTState ( void );
void vCANopenNodeSetNMTState ( CANopenNodeNMTStatusTypeDef_t xState );


#ifdef __cplusplus
}
#endif

#endif /* __CAN_OPEN_NODE_H */
