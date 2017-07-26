# Software Notes

General implementation notes during development. Some hardware related notes are built in here for people unfamiliar with STM32 or the programming ecosystem for ARM micros.

# Software Development and Debugging

## Toolchain and Install

I use the [SW4 System Workbench for STM32](http://www.openstm32.org/System+Workbench+for+STM32) for development and debugging. Follow the install instructions from openstm and everything should be reasonably easy to get working. The Eclipse project includes the config file for the debugging setup.

## Importing and navigating source

Import the project file in the stm32-camera folder. Code in [Src](stm32-camera\Src) is applicable to the project, everything else is either Eclipse or CubeMX generated. 

The software is based heavily on the framework I use at work, and uses a (custom) simple task scheduler and series of (HSM) state machines. The app_state_machines folder contains the highest level tasks and handles events.

app_drivers contains the mid-level functional code to handle individual software level tasks like or manage a series of hardware interfaces (controlling the camera requires use of the DCMI, GPIO and timer/mco functions for example).

app_hal is the 'low-level' hardware interface code. This mostly wraps the STM32 HAL library calls in human friendly functions for convenience. This layer can/should be split away form the rest of the code to provide unit tests, or reduce the effort for porting to other platforms etc.

## Flashing/Debugging Hardware

The board has a CORTEX 1.25mm pitch 2x5 connector for flashing and debugging over SWD. Pinout is below. Pin 7 is designed as the locating pin/key, and some connectors or headers don't have the pin/socket.

| Row 1 Pins    | Row 2 Pins    |
| ------------- | ------------- |
| 1 - VTref     | 2 - SWDIO		|
| 3 - GND      	| 4 - SWDCLK	|
| 5 - GND 		| 6 - SWO		|
| 7 - Key/NC	| 8 - NC		|
| 9 - GNDDetect | 10 - NRST		|

I use a J-Link programmer, but the ST-Link/VS ISOL is also another choice I like which uses the same 20-pin jtag header.

Adafruit sell a [suitable cable](https://www.adafruit.com/product/1675), and [adaptor board](https://www.adafruit.com/product/2094) for standard 2.54mm 20-pin. I got an [adapter from OLIMEX](https://www.olimex.com/Products/ARM/JTAG/ARM-JTAG-20-10/) which is a bit nicer for direct connection to the programmer.

Using a STM32 discovery as a programmer, or the cheap chinese STLink clones will also work, but you will need to make a suitable cable.

## STM32 CubeMX

CubeMX is designed to take the effort out of setting up and configuring the peripherals and pins on STM32 micros. This is pretty standard in many STM based projects and should be easy enough to follow.

If pinouts are being changed or settings modified, make sure the changes are actually reflected in the app_hal source as I don't use the CubeMX generated wrappers for init etc. By rolling (mostly) the same code in my own hal layer, there are fewer issues with regenerating cubemx and allows for dynamic init/deinit of peripherals to reduce power when they are unused.

___

# SD Card

We use the SDIO interface in 4-bit mode.

This thread discusses using DMA for high performance non-blocking use.
https://community.st.com/thread/39133-high-performance-sdiosdmmc-driver-using-dma-for-freertos-anyone

Also this tutorial: http://thehackerworkshop.com/?p=1103

Detection relies on the internal pullup on that GPIO pin.

# Other notes

https://github.com/nothings/stb

Seems like a possible option for direct jpeg manipulation.