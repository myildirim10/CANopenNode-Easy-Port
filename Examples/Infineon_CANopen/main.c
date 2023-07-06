/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Example file for XMC4800 CANopen communication
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "DAVE.h"    //Declarations from DAVE Code Generation (includes SFR declaration)
#include "CANopenNode.h"

#include "301/CO_ODinterface.h"
#include "OD.h"
/* Defines -------------------------------------------------------------------*/

/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/* Functions ----------------------------------------------------------------*/
/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");
    while(1);
  }

  xCANopenNodeInit();


  while(1)
  {
	  vCANopenNodeProcess();
  }
}


/**
 *  @brief Timer Handler (1 ms)
 */
void TimerHandler ( void )
{
    vCANopenNodeTimerInterrupt();

	/* Acknowledge the period match interrupt*/
    TIMER_ClearEvent(&TIMER_0);
}


/**
 *  @brief CAN Receive Handler
 */
void CANReceiveHandler ( void )
{
   vCANopenNodeReceiveInterrupt();
}
