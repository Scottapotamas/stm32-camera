# stm32-camera

Existing products are either cameras which lack resolution and image quality (640x480 security cams that happen to have UART outputs), or are higher end expensive options geared towards computer vision for embedded hardware (openMV, PixyCam, etc).

This seeks to provide higher quality photos or short videos in an integrated device, whilst minimising power consumption and allowing higher quality imaging.

# Required features

- Sample a CMOS camera sensor using a microcontroller.
- Condition the data as appropriate, and hold images in memory.
- Allow upload of image data to the host over a serial, USB, SPI or other connection.
- Must have low continuous current draw, and ability to 'sleep' for maximum power savings.
- Must support a range of lens options which can be focused and swapped based on application requirements.
- Allow the host to control basic functionality such as exposure, capture modes and resolution, and power saving functionality.
- Cost less than $65

# Bonus Features

- Control either an onboard or off-board LED flash. Use a DAC output to drive it for variable brightness.
- Control a IR filter switch mechanism to add or subtract IR filtering automatically.
- Include a photoresistor so the board can detect ambient lighting conditions without use of the camera (for IR filter switch, or flash brightness control).
- Ability to overlay arbitary data (text or otherwise) onto the images as a footer or datestamp.

# Considered Approach

- PCB with camera sensor, lens mount, light sensor etc on front
- STM32F4 or F7 chip on the rear of the PCB or on the side.
- IO pinout is through hole, bonus points if compatible with VC076 style camera
- Mounting hole pattern is compatible with current cameras if possible
- Support 5V input, TTL level signalling

# Other notes

