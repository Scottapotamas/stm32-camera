# Omnivision documentation

- Found the 'confidential' OV hardware and software appnotes, along with the SSCB (i2c like) settings interface.
- Found some unattributed c code which has the best register maps I've found so far.
- Won't run on hardware, but great reference for control over camera functions.

# OV2640 Camera Module under ChibiOS on the STM32F4-Discovery Board

http://www.elektricks.net/ov2640-camera-module-under-chibios-on-the-stm32f4-discovery-board/

- Provided source
- Uses chibiOS
- Uses DCMI, shows pinout and wiring to F4 disco
- Blog post archived in .zip.

# OV2640 Camera module on STM32 (without DCMI interface)

http://qyx.krtko.org/projects/ov2640_stm32/
https://github.com/iqyx/ov2640-stm32

- Main.c code in ref folder.
- Blog archived in zip.
- Uses chibiOS
- Doesn't use DCMI (because chibiOS had poor support for it back then)
- Uses DMA, discusses i2c config.

# OV2640 Linux driver

- Has additional notes for register settings etc.
- Source .c in folder.