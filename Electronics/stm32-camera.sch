EESchema Schematic File Version 2
LIBS:appli_analog_devices
LIBS:appli_atmel
LIBS:appli_battery
LIBS:appli_capacitor
LIBS:appli_connector
LIBS:appli_connector_molex
LIBS:appli_connector_jst
LIBS:appli_crystal
LIBS:appli_device
LIBS:appli_fiducial
LIBS:appli_ftdi
LIBS:appli_fuse
LIBS:appli_inductor
LIBS:appli_linear
LIBS:appli_link
LIBS:appli_logo
LIBS:appli_memory
LIBS:appli_mount
LIBS:appli_opto
LIBS:appli_power
LIBS:appli_regulator
LIBS:appli_relay
LIBS:appli_resistor
LIBS:appli_special
LIBS:appli_spice
LIBS:appli_stm32
LIBS:appli_switch
LIBS:appli_tag_connect
LIBS:appli_template
LIBS:appli_test_points
LIBS:appli_transformer
LIBS:appli_transistor
LIBS:appli_ublox
LIBS:appli_uC
LIBS:appli_usb
LIBS:appli_wireless
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date "2017-03-04"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 7000 1625 1950 2125
U 58721303
F0 "Microcontroller" 60
F1 "Microcontroller.sch" 60
$EndSheet
$Sheet
S 3200 1625 1950 2125
U 58721310
F0 "Regulation" 60
F1 "PowerSupply.sch" 60
$EndSheet
$Sheet
S 6975 4400 1925 1900
U 587213A7
F0 "Interface Electronics, Mechanicals" 60
F1 "Miscellaneous.sch" 60
$EndSheet
Text Notes 4575 825  0    118  ~ 24
STM32-Camera Board Overview
Text Notes 6850 1325 0    79   ~ 0
STM32F4 based processor handles the show.\nClocks, debug and related hardware.\nUses standard ARM CORTEX SWD 10-pin to program
Text Notes 2600 1325 0    79   ~ 0
Regulator to power microcontroller and sensor.\nInput protection and filtering as required.
Text Notes 6850 4250 0    79   ~ 0
Miscelaneous periphery. MicroSD card.\nMounting holes, fiducials, branding, etc
$Sheet
S 3175 4400 1975 1900
U 58B99D94
F0 "Camera Sensor and Mount" 60
F1 "Camera.sch" 60
$EndSheet
Text Notes 2850 4150 0    79   ~ 0
Sensor, mounts and supporting electronics
$EndSCHEMATC
