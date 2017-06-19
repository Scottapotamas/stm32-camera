# Electronics Notes

General implementation notes during assignment and schematic capture. Might be useful during software dev.

# Microcontroller Pin Assignment

I2C2 peripheral is used for SSCB interface (configuration registers).

MCO (PA8) is used for the camera XCLK clock. Should clock at 24Mhz typical, 6Mhz minimum.

DCMI interface is used for main camera connection (includes HSYNC/VSYNC/PIXCK pins etc)

PCLK is the camera strobe for 8-bit data on rising edge.

PWDN is the camera power down signal (active high). Connected to PE3.

RES is camera reset signal (active low). Connected to PE2

SDIO interface is used in 4-bit mode for SD card. In theory, we should be able to write images to the SD card at highish speed, then allow the host to pull them off later if needed.

SYS_WKUP (PA0) is enabled to allow external wakeup commands at a hardware level.

SWD with SWO is enabled explicitly. Plan on using CORTEX 10-pin header.

HSE clock included. Probably use a 16MHz CERALOCK instead of usual 8MHz?

DAC2 is proposed for use with a flash driver. Ideally don't use PWM as switching noise is potentially visible.

# Sensor Specifics

There are two power down methods available (hardware and software power down).

PWDN is pulled high and the camera clock/timers will stop and reset.
Power draw is apparently 15uA.

Software power down through i2c doesn't stop the clock. Registers are retained but draws 1mA.

Later on in the datasheet...
"For OV2640, there have big power down current, so power down mode is not supported by OV2640 for power saving."

So I think I should include a off-camera switch for the 3v3 rail to the camera, just incase.


A full hardware reset is performed when RESETB goes low

The datasheet states that the strobe mode allows it to operate with an external flash and(/or?) LED. The pinmap guide states this defaults as an input, but is the flash control output.
Should connect to a GPIO (at least to know if the camera wants a flash, probably redundant info)


# IR Switcher

As far as I can tell, its basically a solenoid which moves the IR cut filter infront or away from the sensor. Unclear if spring loaded or not.

The aliexpress page I got my samples from (below link) has no real information other than images (but hey, $2.50AUD).

https://www.aliexpress.com/item/HD-3MP-IR-CUT-filter-M12-lens-Metal-mount-double-filter-switcher-for-cctv-camera-IRCUT/32785570950.html?spm=2114.13010608.0.0.Kv2NdH 

This ebay page http://www.ebay.com/itm/400938137287 seems to have more info (copied below)

- Working Voltage:5V-18V
- Rated Current:0.2A
- Screw thread interface:M12 Mount (MTV / C)
- Switcher Type:Pendulum Switcher
- Filter:Phosphate Filter
- The Glass Size:11*9.3mm
- The distance for two holes:20mm
- Total length:30mm
- The inner Diameter:15mm
- Inductor cores:HP V5
- Shake length：625+-10nm

Unsure if it can be switched with 3v3 supply. I found another page with similar looking units which states the following:

- Start voltage: 1.8V±10%
- Applied voltage: 3.0V±10%
- Driver pulse width: 50ms
- Trigger current: 100mA or less
- Working current: 200mA or less

If the filter needs to be held in place during aquisition then some interesting software might need to manage the power consumption cleverly. I'm hopeful pendulum switching means a short pulse high or low to set and forget.

A 100mA spec'ed H-Bridge driver is probably the route to go.