# Electronics Notes

General implementation notes during assignment and schematic capture. These are notes which don't make it onto the schematic due to length or relevance. Hopefully they might be useful during software dev.

# Microcontroller Pin Assignment

- I2C2 peripheral is used for SSCB interface (configuration registers).
- MCO (PA8) is used for the camera XCLK clock. Should clock at 24Mhz typical, 6Mhz minimum. This can be the HSI, HSE, a timer, etc.
- DCMI interface is used for main camera connection (includes HSYNC/VSYNC/PIXCK pins etc)
- PCLK is the camera strobe for 8-bit data on rising edge.
- PWDN is the camera power down signal (active high). Connected to PE3.
- RES is camera reset signal (active low). Connected to PE2
- SDIO interface is used in 4-bit mode for SD card. In theory, we should be able to write images to the SD card at highish speed, then allow the host to pull them off later if needed.
- SWD with SWO is enabled explicitly. Plan on using CORTEX 10-pin header.
- HSE clock included. Probably use a 16MHz CERALOCK instead of usual 8MHz?
- DAC2 is proposed for use with a flash driver. Ideally don't use PWM as switching noise is potentially visible, but that same pin can also be an analog input, PWM output or general GPIO.

# Sensor Specifics

## Power Down Options

| Hardware Control  | Software Control |
| ----------------- | ---------------- |
| PWDN is pulled high to stop the clock  | i2c commands available but doesn't stop everything (clocks) |
| Power draw is apparently 15uA.  | Registers are retained but draws 1mA.  |

Later on in the datasheet, this is conflicted by:

> For OV2640, there have big power down current, so power down mode is not supported by OV2640 for power saving.

The lower voltage LDO's have their EN line connected to the micro for more granular/forceful control.
I'll likely just use hardware control as long as it configures fast enough.

## Reset

A full hardware reset is performed when RESETB goes low.

There is also reset via the i2c interface.

## Other lines

- The datasheet states that strobe mode allows it to operate with an external flash and(/or?) LED. 
- The pinmap guide states this defaults as an input, but is the flash control output.
- A STM32 GPIO is connected instead of flash driver (at least to know if the camera wants a flash, probably redundant info by the time we see it)

# SD Card

# IR Cut Filter Switcher

As far as I can tell, its a bistable solenoid which moves the IR cut filter infront or away from the sensor.

## Theory

The [aliexpress page I got my samples from](https://www.aliexpress.com/item/HD-3MP-IR-CUT-filter-M12-lens-Metal-mount-double-filter-switcher-for-cctv-camera-IRCUT/32785570950.html?spm=2114.13010608.0.0.Kv2NdH ) has no real information other than images (but hey, $2.50AUD).

This [ebay page](http://www.ebay.com/itm/400938137287) seems to have more info (copied below)

- Working Voltage: 5V-18V
- Rated Current: 0.2A
- Screw thread interface: M12 Mount (MTV / C)
- Switcher Type: Pendulum Switcher
- Filter: Phosphate Filter
- Glass Size: 11*9.3mm
- Hole Spacing: 20mm
- Total length: 30mm. Inner Diameter: 15mm

I found another page with similar looking units which states the following:

- Start voltage: 1.8V±10%
- Applied voltage: 3.0V±10%
- Driver pulse width: 50ms
- Trigger current: 100mA or less
- Working current: 200mA or less

~~If the filter needs to be held in place during aquisition then some interesting software might need to manage the power consumption cleverly.~~ Pendulum switching means a short pulse high or low to set and forget. Drive with inverted polarity to change back.
This seems to vary between modules. Some of the other samples I received later *are* spring loaded.

It appears the units I recieved use a 1.25mm pitch molex(?) 2-pin connector. 
I'm pretty sure its molex because locking tab instead of slot. 
Seems like a Picoblade connector.

## Testing

Tests with bench supply show switching latches setting after power is removed.

With the supply set to 3.000V, the minimum current which triggers a full switch is 60mA. At 40mA and above, it appears to half-hold and reset on removal of power. Below 40mA nothing happens.

Switching would not occur at 2.0V. At 2.5V 50mA was able to activate the shutter, but 60-70mA was more reliable.

At 3.250V (rough design target for regulator and hence micro VDD) 45mA was enough to trigger a switch but sounded 'slower'. It seems the solenoid will draw 54mA, or 0.175W.

As some of these cameras will be in potentially extreme outdoor environments, a switching unit was cooled to -10°C and tested. 
At the same 3.250V, it requires 60mA to switch (0.195W). 

## Decision

It is unclear how the power requirements might change with manufacturing tolerances, temp cycling etc. Effects such as stiction etc haven't been tested for.

A 100mA spec'ed H-Bridge driver or equiv is probably the route to go.

As this eats a lot of room on the board using even small H-bridge drivers, and cost is a luxury, I'm strongly considering using multiple parallel GPIO pins (shared port for bitwise simultaneous control) to allow for push pull drive. As we only need short impulses this seems reasonable.

Unclear if the body diodes in the micro will be happy with this arrangement.

