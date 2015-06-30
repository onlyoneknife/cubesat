FreeRTOS V7.5.2 with modified portable part for M0 MCU

Changes with comparison to standard version:
- \Source\portable\GCC\ARM_CM0\port.c
- \Source\portable\GCC\ARM_CM0\portmacro.h
- \Source\portable\IAR\ARM_CM0\port.c
- \Source\portable\IAR\ARM_CM0\portmacro.h
Added support for tickless idle and own idle function.



Each real time kernel port consists of three files that contain the core kernel
components and are common to every port, and one or more files that are 
specific to a particular microcontroller and or compiler.

+ The FreeRTOS/Source directory contains the three files that are common to 
every port - list.c, queue.c and tasks.c.  The kernel is contained within these 
three files.  croutine.c implements the optional co-routine functionality - which
is normally only used on very memory limited systems.

+ The FreeRTOS/Source/Portable directory contains the files that are specific to 
a particular microcontroller and or compiler.

+ The FreeRTOS/Source/include directory contains the real time kernel header 
files.

See the readme file in the FreeRTOS/Source/Portable directory for more 
information.

FreeRTOS - Tickless example

This example project uses the FreeRTOS, and gives a basic demonstration of using two tasks,
one sender generating number and one receiver that displays the number on LCD. The FreeRTOS is 
configured in tick-less mode, going into EM2 when no tasks are active (  is possible to use 
EM1 or EM2 in this example, EM3 mode can't work, because LCD driver doesn't work in that mode- configured 
in FreeRTOSConfig.h file ). 
This example is intended as a skeleton for new projects using FreeRTOS for energy aware applications. 

Board:  Silicon Labs EFM32GG_STK3700 Starter Kit
Device: EFM32GG990F1024