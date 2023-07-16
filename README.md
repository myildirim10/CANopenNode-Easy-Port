# CANopenNode

This project was made to more easily "port" the CANopenNode open source library. (https://github.com/CANopenNode/CANopenNode)

The project also contains the library in the EEPROM XX25 Series (AT25256B, CAV25256...). In this way, the changes you make via CANopen can be kept in permanent memory.

This library has been tested with MCU models STM32 (NUCLEO-F303RE), ESP32 (WROOM-32), TI (TMS320F28335), Infineon (XMC4800). The sample projects are in the "Examples" folder.



*The folders in the project were grouped for the following purposes:*

**stack directory:** The directory that contains the files from the CANopenNode library that we will probably never change.

**driver directory:** It is the directory that contains the files that can be changed according to the project. For example, OD.c and OD.h files are files that you need to create with the CANopen Editor program (https://github.com/CANopenNode/CANopenEditor) according to the needs of your project. In my project, I created a comprehensive OD file that supports DS301 and DS402 standards.

CO_storageBlank file, if a different EEPROM model is to be used, you can port it through this file.

The CO_driver_target file is the one modified by me. Receive and Transmit functions are done on a different file for easy porting to other projects.

**hardware directory:** Contains files that need to be modified according to hardware. You must write your CAN transmit and receive functions over the CANopenHardware.c file in this directory. For the transmit function, you must write your CAN transmit functions in the xCANTransmitMessage content. For the receive function, you must write CAN receive functions in the context of xCANReceiveMessage.





## How to port the project

#### Usage of the library:

1. The CANopenNode Library needs CAN peripheral unit, 1ms Timer and CAN Receive Interrupt function to work.
2. After the above hardware settings are made, the xCANopenNodeInit function should be called in main.
3. After setting the 1ms Timer Interrupt, the vCANopenNodeTimerInterrupt function must be called within the Interrupt function.
4. The vCANopenNodeReceiveInterrupt must be called within the CAN Receive Interrupt function.
5. The vCANopenNodeProcess function must be called in the main loop or a task.
6. In the CANopenHardware.c file, the CAN Transmit function required by the hardware must be written into the xCANTransmitMessage function and the CAN Receive function into the xCANReceiveMessage function.



#### Directories to add to the project:

     1. CANopen
     2. CANopen/driver
     3. CANopen/hardware
     4. CANopen/stack
     5. (EEPROM) - If EEPROM is to be used



> Note: If you are going to use a TI C2000 series MCU, you should change it to #define C2000_PORT (1) in the stack/301/CO_config.h file. In TMS320C28x series processors, such a change is needed because *bytes* and *word* are *16 bits* long in C2000. Note that the linker file has been changed in the sample project for C2000.



##### EEPROM Library

   1. When using the CANopenNode library, the EEPROM library must be added in order for the parameter changes made with SDO to be valid at the next startup. There is also the EEPROM folder in this library file. Added library for EEPROM XX25 Series.

   2. After the changes are made via SDO, "save" is written to index 0x1010 with ASCII code and saved to EEPROM. 

      ```bash
      CAN-ID: 601, DATA: 23 10 10 01 73 61 76 65
      ```





## Sample code

```c
// main.c
#include "CANopenNode.h"

int main ( void )
{
     xCANopenNodeInit();

     while(1)
     {
         vCANopenNodeProcess();
     }

}

void CAN_Receive_Interrupt ( void )
{
     vCANopenNodeReceiveInterrupt();
}

void Timer_1MS_Handler ( void )
{
     vCANopenNodeTimerInterrupt();
}
```





## How will you test

After making CAN Rx-Tx connections and connecting to your computer with a CAN-USB converter, you can query CANopen SDO. For example, I used the PCAN-View program while testing.

After selecting the CAN Baud rate setting and connecting, you can try the sample commands below.



#### Some example commands

> To query the Software Version SDO
>
> ```bash
> 601h | 8 | 40 00 1A 00 00 00 00 00



> If PDO transmission is desired to be set via SDO
>
> *For PDO with index 181h;*
>
> ```bash
> 601h | 8 | 2B 00 18 05 E8 03 00 00
> ```
>
> *For PDO with index 201h;*
>
> ```bash
> 601h | 8 | 2B 01 18 05 E8 03 00 00
> ```



> To set up a sample Heartbeat message delivery
>
> ```bash
> 601 | 8 | 2B 17 10 00 DE F0 00 00



> NMT messages
>
> To initialize the device with *01 Node ID* (operational mode);
>
> ```bash
> 000| 2 | 01 01
> ```
>
> 
>
> To stop the device with *01 Node ID*;
>
> ```bash
> 000| 2 | 02 01
> ```
>
> 
>
> To put the device with *01 Node ID* into pre-operational mode;
>
> ```bash
> 000| 2 | 80 01
> ```
>
> 
>
> To reset the device with *01 Node ID* (Reset node);
>
> ```bash
> 000 | 2 | 81 01
> ```
>
> 
>
> To reset the communication device with *01 Node ID*;
>
> ```bash
> 000 | 2 | 82 01
> ```



> Save All Data (Save to EEPROM)
>
> ```bash
> 601 | 8 | 23 10 10 01 73 61 76 65
> ```



> Restore All Data
>
> ```bash
> 601 | 8 | 23 11 10 01 6C 6F 61 64
> ```

