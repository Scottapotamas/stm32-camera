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
LIBS:appli_logic_devices
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
LIBS:stm32-camera-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 9100 4450 0    118  ~ 24
Mounting Holes
Text Notes 9300 3475 0    118  ~ 24
Fiducials
Text Notes 8925 5475 0    118  ~ 24
Logos and Markings
$Comp
L FIDUCIAL FID?
U 1 1 5891D98F
P 9600 3825
F 0 "FID?" H 9753 3869 47  0000 L CNN
F 1 "FIDUCIAL" H 9753 3782 47  0000 L CNN
F 2 "Applidyne_Fiducial:FID100X300" H 9600 4000 47  0001 C CNN
F 3 "" H 9600 3825 60  0000 C CNN
	1    9600 3825
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID?
U 1 1 5891D9E3
P 10275 3825
F 0 "FID?" H 10428 3869 47  0000 L CNN
F 1 "FIDUCIAL" H 10428 3782 47  0000 L CNN
F 2 "Applidyne_Fiducial:FID100X300" H 10275 4000 47  0001 C CNN
F 3 "" H 10275 3825 60  0000 C CNN
	1    10275 3825
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID?
U 1 1 5891DA17
P 8850 3825
F 0 "FID?" H 9003 3869 47  0000 L CNN
F 1 "FIDUCIAL" H 9003 3782 47  0000 L CNN
F 2 "Applidyne_Fiducial:FID100X300" H 8850 4000 47  0001 C CNN
F 3 "" H 8850 3825 60  0000 C CNN
	1    8850 3825
	1    0    0    -1  
$EndComp
Text Notes 5500 4100 0    118  ~ 24
MicroSD Card
$Comp
L MOLEX_104031-0811 CON?
U 1 1 58BB720F
P 5325 5400
F 0 "CON?" H 6155 5316 50  0000 L CNN
F 1 "MOLEX_104031-0811" H 6155 5225 50  0000 L CNN
F 2 "Applidyne_Connector_Molex:MOLEX_104031-0811" V 6325 5400 50  0001 C CNN
F 3 "http://au.rs-online.com/web/p/memory-sim-card-connectors/8967560/" V 6975 5200 50  0001 C CNN
F 4 "104031-0811" V 6425 5400 60  0001 C CNN "manf#"
F 5 "RS" V 6625 5400 60  0001 C CNN "Supplier"
F 6 "http://au.rs-online.com/web/p/memory-sim-card-connectors/8967560/" V 6525 5400 60  0001 C CNN "Supplier URL"
F 7 "896-7560" V 6725 5400 60  0001 C CNN "Supplier Part No"
F 8 "1.95" V 6825 5400 60  0001 C CNN "Supplier Price"
F 9 "2" V 6925 5400 60  0001 C CNN "Supplier Price Break"
F 10 "MOLEX" V 6225 5400 60  0001 C CNN "manf"
	1    5325 5400
	1    0    0    -1  
$EndComp
Text GLabel 2825 6100 0    60   Input ~ 0
MICROSD_D1
Text GLabel 2825 5800 0    60   Input ~ 0
MICROSD_D0
Text GLabel 2825 4575 0    60   Input ~ 0
MICROSD_D2
Text GLabel 2825 6425 0    60   Input ~ 0
MICROSD_DETECT
Text GLabel 2825 4875 0    60   Input ~ 0
MICROSD_D3
Text GLabel 2825 5500 0    60   Input ~ 0
MICROSD_CK
Text GLabel 2825 5175 0    60   Input ~ 0
MICROSD_CMD
Text Notes 4475 4425 0    60   ~ 0
MicroSD card is used for bulk storage of sound files, config and logs.\nAlso allows firmware update and other assets as required.
Wire Wire Line
	4925 6200 4925 6475
Wire Wire Line
	4825 6200 4825 6425
Wire Wire Line
	7200 5075 7200 5400
Wire Wire Line
	7200 5925 7200 5600
$Comp
L GND #PWR?
U 1 1 58BD4B91
P 4925 6475
F 0 "#PWR?" H 4925 6225 50  0001 C CNN
F 1 "GND" H 4930 6302 50  0000 C CNN
F 2 "" H 4925 6475 60  0000 C CNN
F 3 "" H 4925 6475 60  0000 C CNN
	1    4925 6475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5525 6200 5525 6350
Wire Wire Line
	5525 6350 5825 6350
Wire Wire Line
	5825 6350 5825 6200
Wire Wire Line
	5725 6200 5725 6350
Connection ~ 5725 6350
$Comp
L GND #PWR?
U 1 1 58BD4CFB
P 5675 6475
F 0 "#PWR?" H 5675 6225 50  0001 C CNN
F 1 "GND" H 5680 6302 50  0000 C CNN
F 2 "" H 5675 6475 60  0000 C CNN
F 3 "" H 5675 6475 60  0000 C CNN
	1    5675 6475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5625 6200 5625 6350
Connection ~ 5625 6350
Wire Wire Line
	5675 6350 5675 6475
Connection ~ 5675 6350
Wire Wire Line
	4425 5600 4325 5600
Wire Wire Line
	4325 5600 4325 6475
$Comp
L GND #PWR?
U 1 1 58CA2FF4
P 4325 6475
F 0 "#PWR?" H 4325 6225 50  0001 C CNN
F 1 "GND" H 4330 6302 50  0000 C CNN
F 2 "" H 4325 6475 60  0000 C CNN
F 3 "" H 4325 6475 60  0000 C CNN
	1    4325 6475
	1    0    0    -1  
$EndComp
Wire Wire Line
	4425 5400 4325 5400
Wire Wire Line
	4325 5400 4325 4800
$Comp
L +3.3V #PWR?
U 1 1 58CA30F9
P 4325 4800
F 0 "#PWR?" H 4325 4760 30  0001 C CNN
F 1 "+3.3V" H 4334 4938 30  0000 C CNN
F 2 "" H 4325 4800 60  0000 C CNN
F 3 "" H 4325 4800 60  0000 C CNN
	1    4325 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 58CECAEE
P 7200 5075
F 0 "#PWR?" H 7200 5035 30  0001 C CNN
F 1 "+3.3V" H 7209 5213 30  0000 C CNN
F 2 "" H 7200 5075 60  0000 C CNN
F 3 "" H 7200 5075 60  0000 C CNN
	1    7200 5075
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 58CECB3C
P 7200 5925
F 0 "#PWR?" H 7200 5675 50  0001 C CNN
F 1 "GND" H 7205 5752 50  0000 C CNN
F 2 "" H 7200 5925 60  0000 C CNN
F 3 "" H 7200 5925 60  0000 C CNN
	1    7200 5925
	1    0    0    -1  
$EndComp
Wire Wire Line
	4425 5500 2825 5500
Wire Wire Line
	4425 5100 4175 5100
Wire Wire Line
	4175 5100 4175 4575
Wire Wire Line
	4175 4575 2825 4575
Wire Wire Line
	2825 4875 4075 4875
Wire Wire Line
	4075 4875 4075 5200
Wire Wire Line
	4075 5200 4425 5200
Wire Wire Line
	4425 5300 3975 5300
Wire Wire Line
	3975 5300 3975 5175
Wire Wire Line
	3975 5175 2825 5175
Wire Wire Line
	2825 5800 4075 5800
Wire Wire Line
	4075 5800 4075 5700
Wire Wire Line
	4075 5700 4425 5700
Wire Wire Line
	4425 5800 4175 5800
Wire Wire Line
	4175 5800 4175 6100
Wire Wire Line
	4175 6100 2825 6100
Wire Wire Line
	4825 6425 2825 6425
Wire Wire Line
	4075 4175 4075 4575
Connection ~ 4075 4575
Wire Wire Line
	3725 4175 3725 4875
Connection ~ 3725 4875
Wire Wire Line
	3375 4175 3375 5800
Connection ~ 3375 5800
Wire Wire Line
	3025 4175 3025 6100
Connection ~ 3025 6100
Wire Wire Line
	4075 3875 4075 3675
Wire Wire Line
	3725 3875 3725 3675
Wire Wire Line
	3375 3675 3375 3875
Wire Wire Line
	3025 3875 3025 3675
$Comp
L +3.3V #PWR?
U 1 1 58EFD597
P 4075 3675
F 0 "#PWR?" H 4075 3635 30  0001 C CNN
F 1 "+3.3V" H 4084 3813 30  0000 C CNN
F 2 "" H 4075 3675 60  0000 C CNN
F 3 "" H 4075 3675 60  0000 C CNN
	1    4075 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 58EFD61A
P 3725 3675
F 0 "#PWR?" H 3725 3635 30  0001 C CNN
F 1 "+3.3V" H 3734 3813 30  0000 C CNN
F 2 "" H 3725 3675 60  0000 C CNN
F 3 "" H 3725 3675 60  0000 C CNN
	1    3725 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 58EFD69D
P 3375 3675
F 0 "#PWR?" H 3375 3635 30  0001 C CNN
F 1 "+3.3V" H 3384 3813 30  0000 C CNN
F 2 "" H 3375 3675 60  0000 C CNN
F 3 "" H 3375 3675 60  0000 C CNN
	1    3375 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 58EFD720
P 3025 3675
F 0 "#PWR?" H 3025 3635 30  0001 C CNN
F 1 "+3.3V" H 3034 3813 30  0000 C CNN
F 2 "" H 3025 3675 60  0000 C CNN
F 3 "" H 3025 3675 60  0000 C CNN
	1    3025 3675
	1    0    0    -1  
$EndComp
Text Notes 1650 1150 0    118  ~ 24
IR Cut Filter Driver
Text Notes 1300 1475 0    60   ~ 0
Hardware switching IR-Cut is like a latching solenoid.\nUse a H-Bridge style driver to control.
Text Notes 5950 1150 0    118  ~ 24
IR Flash Driver
Text Notes 5725 1400 0    60   ~ 0
Allow the board to drive a IR flash.
$Comp
L 1UF_X5R_1005M C?
U 1 1 5948A11C
P 7200 5400
F 0 "C?" H 7278 5335 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 7278 5255 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 7315 5300 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 7340 5300 20  0001 C CNN
F 4 "TDK" V 7390 5300 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 7415 5300 20  0001 C CNN "manf#"
F 6 "Element14" V 7440 5300 20  0001 C CNN "Supplier"
F 7 "2346885" V 7465 5300 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 7490 5300 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 7515 5300 20  0001 C CNN "Supplier Price"
F 10 "100" V 7540 5300 20  0001 C CNN "Supplier Price Break"
	1    7200 5400
	1    0    0    -1  
$EndComp
Text GLabel 5825 1975 0    60   Input ~ 0
FLASH_DAC
Text GLabel 1475 2050 0    60   Input ~ 0
IRCUT_A
Text GLabel 1475 2325 0    60   Input ~ 0
IRCUT_B
Text Notes 8675 1150 0    118  ~ 24
Ambient Light Sensor
Text Notes 8850 1500 0    60   ~ 0
Read the ambient light directly to\nallow auto-cut filter selection etc.
Text GLabel 9650 1950 0    60   Output ~ 0
AMBIENT_LIGHT
Text Notes 8625 2225 0    60   ~ 0
Light sensor should have an IR cut filter.
Text Notes 6050 2050 0    60   ~ 0
Constant current drive?
Text Notes 2075 2175 0    60   ~ 0
Approx 100mA rating.
$Comp
L 47K_QUAD_ARRAY_1608M R?
U 1 1 594A8889
P 3025 3875
F 0 "R?" V 2900 3650 50  0000 L CNN
F 1 "47K_QUAD_ARRAY_1608M" V 3125 3425 35  0000 L CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3225 3740 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2085571.pdf" V 3250 3740 20  0001 C CNN
F 4 "PANASONIC" V 3300 3740 20  0001 C CNN "manf"
F 5 "EXB38V473JV" V 3325 3740 20  0001 C CNN "manf#"
F 6 "Element14" V 3350 3740 20  0001 C CNN "Supplier"
F 7 "2060111" V 3375 3740 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/exb38v473jv/resistance-47kohm/dp/2060111" V 3400 3740 20  0001 C CNN "Supplier URL"
F 9 "0.081" V 3425 3740 20  0001 C CNN "Supplier Price"
F 10 "1" V 3450 3740 20  0001 C CNN "Supplier Price Break"
	1    3025 3875
	1    0    0    -1  
$EndComp
$Comp
L 47K_QUAD_ARRAY_1608M R?
U 2 1 594A8B4E
P 3375 3875
F 0 "R?" V 3250 3650 50  0000 L CNN
F 1 "47K_QUAD_ARRAY_1608M" V 3475 3425 35  0000 L CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3575 3740 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2085571.pdf" V 3600 3740 20  0001 C CNN
F 4 "PANASONIC" V 3650 3740 20  0001 C CNN "manf"
F 5 "EXB38V473JV" V 3675 3740 20  0001 C CNN "manf#"
F 6 "Element14" V 3700 3740 20  0001 C CNN "Supplier"
F 7 "2060111" V 3725 3740 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/exb38v473jv/resistance-47kohm/dp/2060111" V 3750 3740 20  0001 C CNN "Supplier URL"
F 9 "0.081" V 3775 3740 20  0001 C CNN "Supplier Price"
F 10 "1" V 3800 3740 20  0001 C CNN "Supplier Price Break"
	2    3375 3875
	1    0    0    -1  
$EndComp
$Comp
L 47K_QUAD_ARRAY_1608M R?
U 3 1 594A8B8B
P 3725 3875
F 0 "R?" V 3600 3650 50  0000 L CNN
F 1 "47K_QUAD_ARRAY_1608M" V 3825 3425 35  0000 L CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3925 3740 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2085571.pdf" V 3950 3740 20  0001 C CNN
F 4 "PANASONIC" V 4000 3740 20  0001 C CNN "manf"
F 5 "EXB38V473JV" V 4025 3740 20  0001 C CNN "manf#"
F 6 "Element14" V 4050 3740 20  0001 C CNN "Supplier"
F 7 "2060111" V 4075 3740 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/exb38v473jv/resistance-47kohm/dp/2060111" V 4100 3740 20  0001 C CNN "Supplier URL"
F 9 "0.081" V 4125 3740 20  0001 C CNN "Supplier Price"
F 10 "1" V 4150 3740 20  0001 C CNN "Supplier Price Break"
	3    3725 3875
	1    0    0    -1  
$EndComp
$Comp
L 47K_QUAD_ARRAY_1608M R?
U 4 1 594A8BD3
P 4075 3875
F 0 "R?" V 3950 3650 50  0000 L CNN
F 1 "47K_QUAD_ARRAY_1608M" V 4175 3425 35  0000 L CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 4275 3740 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2085571.pdf" V 4300 3740 20  0001 C CNN
F 4 "PANASONIC" V 4350 3740 20  0001 C CNN "manf"
F 5 "EXB38V473JV" V 4375 3740 20  0001 C CNN "manf#"
F 6 "Element14" V 4400 3740 20  0001 C CNN "Supplier"
F 7 "2060111" V 4425 3740 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/exb38v473jv/resistance-47kohm/dp/2060111" V 4450 3740 20  0001 C CNN "Supplier URL"
F 9 "0.081" V 4475 3740 20  0001 C CNN "Supplier Price"
F 10 "1" V 4500 3740 20  0001 C CNN "Supplier Price Break"
	4    4075 3875
	1    0    0    -1  
$EndComp
$EndSCHEMATC
