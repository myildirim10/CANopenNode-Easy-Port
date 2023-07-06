/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main file
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
#include "main.h"
#include <stdint.h>
#include "DSP28x_Project.h"     /* Device Headerfile and Examples Include File */
#include "CANopenNode.h"

/* Defines -------------------------------------------------------------------*/


/* Enum definitions ----------------------------------------------------------*/


/* Structure definitions -----------------------------------------------------*/


/* External variables --------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
static void vDelayMs ( int32_t lMilisecond );
interrupt void Ecan0ISR ( void );
interrupt void CPUTimerISR ( void );

extern void TEST_FUNC ();
uint8_t ret = 0;

/* Functions ----------------------------------------------------------------*/
/**
 * @brief   main function
 */
int main ( void )
{
    //
    // Create a shadow register structure for the CAN control registers.
    // This is needed, since only 32-bit access is allowed to these registers.
    // 16-bit access to these registers could potentially corrupt the register
    // contents or return false data.
    //


    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Copy time critical code and Flash setup code to RAM
    // This includes the following ISR functions: epwm1_timer_isr(),
    // epwm2_timer_isr(), epwm3_timer_isr and and InitFlash();
    // The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the F28335.cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //
    InitFlash();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Just initialize eCAN pins for this example
    // This function is in DSP2833x_ECan.c
    //
    InitECanGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();


    /* CANopen Node initialize */
    xCANopenNodeInit();

    /* Interrupt Enable */
    EnableInterrupts();

    TEST_FUNC ();
    //uint8_t testData[10] = { 0x01, 0x02, 0x03 };

   // ret = CheckEEPROMReadWrite(0, testData);


     while (1)
     {
        vCANopenNodeProcess();
     }

}


/**
 * @brief Delay milisecond
 * @param milisecond
 * @return StatusTypeDef_t
 */
static void vDelayMs ( int32_t lMilisecond )
{
    static int32_t lCounter;

    for (lCounter = 0; lCounter < lMilisecond; lCounter++)
    {
        DELAY_US(1000);
    }
}


/**
 * @brief Ecan Interrupt
 */
interrupt void Ecan0ISR ( void )
{

    if(ECanaRegs.CANRMP.all == 0x00010000)
    {
        vCANopenNodeReceiveInterrupt();
        ECanaRegs.CANRMP.all = 0x00010000;
    }

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //

}


/**
 * @brief CPU Timer0 ISR
 */
interrupt void CPUTimerISR ( void )
{
    CpuTimer0.InterruptCount++;

    vCANopenNodeTimerInterrupt();

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

