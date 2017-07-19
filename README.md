# stm32-camera

Existing products are either cameras which lack resolution and image quality (640x480 security cams that happen to have UART outputs), or are higher end expensive options geared towards computer vision for embedded hardware (openMV, PixyCam, etc).

This project seeks to provide higher quality still photos or short low-fps videos in an integrated device, allowing for greater integration flexibility whilst minimising power consumption.

![Business at the front](Electronics/Renders%201.0.0/1-0-0_FRONT.png)
![Party in the back](Electronics/Renders%201.0.0/1-0-0_BACK.png)

# Project Goals

- Sample a CMOS camera sensor using a microcontroller. Condition the data as appropriate, and hold images in memory.
- Allow upload of image data to the host over a serial, USB, or other connection.
- Aim to minimise current draw wherever possible, and design around the ability to 'deep-sleep' for maximum power savings.
- Support a wide range of lenses for different application requirements.
- Allow the host to control functionality such as exposure, capture modes, resolution, and power saving functionality.
- Cost less than $65
- Provide source for interfacing a host device like an Arduino/STM32.
- Provide software sources for the camera board to allow modified behaviour.

# Bonus Features

- Control either an onboard or off-board LED flash. Use a DAC output to drive it for variable brightness.
- Control a IR filter switch mechanism to add or subtract IR filtering automatically at night.
- Include hardware light sensing to detect ambient light without use of the camera (for IR filter switch, dynamic flash brightness, etc).
- Ability to store images or image sequences on disk, and/or copy them off later when the action dies down.

# Approach

- Small 32x32mm PCB with camera sensor, lens mount (uses 20mm spaced M2 screws), microcontroller.
- STM32F4 microcontroller interfaces to the sensor and provides power management, filter swaps, storage etc.
- The IO pinout is 2.54mm 8-way through hole. Accepts 4-14V DC input power. Has UART, and 3 high feature set expansion IO.
- Mounting hole pattern is somewhat backwards compatible with 28mm spaced M3 holes.

# Hardware Overview

- Its a 4 layer board due to the density of the fanout and smaller board package. 
- Min track width/clearance is 0.22mm and min via is 0.35mm. No blind or buried vias.
- While a bit tight, it should be fine with better 'budget' Chinese fabs. OSHPark would have absolutely no issues with it.
- Specific notes are in [the electronics folder](Electronics)
