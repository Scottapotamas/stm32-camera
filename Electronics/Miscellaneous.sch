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
Text Notes 9450 3475 0    118  ~ 24
Fiducials
Text Notes 8950 5900 0    118  ~ 24
Logos and Markings
Text Notes 5500 4100 0    118  ~ 24
MicroSD Card
Text GLabel 2825 6100 0    60   Input ~ 0
MICROSD_D1
Text GLabel 2825 5800 0    60   Input ~ 0
MICROSD_D0
Text GLabel 2825 4600 0    60   Input ~ 0
MICROSD_D2
Text GLabel 2825 6400 0    60   Input ~ 0
MICROSD_DETECT
Text GLabel 2825 4900 0    60   Input ~ 0
MICROSD_D3
Text GLabel 2825 5500 0    60   Input ~ 0
MICROSD_CK
Text GLabel 2825 5200 0    60   Input ~ 0
MICROSD_CMD
Text Notes 4475 4425 0    60   ~ 0
MicroSD card is used for bulk storage of image files, config setting and logs.
Wire Wire Line
	4900 6200 4900 6450
Wire Wire Line
	4800 6200 4800 6400
Wire Wire Line
	7200 5075 7200 5400
Wire Wire Line
	7200 5925 7200 5600
$Comp
L GND #PWR041
U 1 1 58BD4B91
P 4900 6450
F 0 "#PWR041" H 4900 6200 50  0001 C CNN
F 1 "GND" H 4905 6277 50  0000 C CNN
F 2 "" H 4900 6450 60  0000 C CNN
F 3 "" H 4900 6450 60  0000 C CNN
	1    4900 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 6200 5500 6400
Wire Wire Line
	5600 6200 5600 6450
Wire Wire Line
	4400 5600 4300 5600
Wire Wire Line
	4300 5600 4300 6475
$Comp
L GND #PWR042
U 1 1 58CA2FF4
P 4300 6475
F 0 "#PWR042" H 4300 6225 50  0001 C CNN
F 1 "GND" H 4305 6302 50  0000 C CNN
F 2 "" H 4300 6475 60  0000 C CNN
F 3 "" H 4300 6475 60  0000 C CNN
	1    4300 6475
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5400 4300 5400
Wire Wire Line
	4300 5400 4300 4750
$Comp
L +3.3V #PWR043
U 1 1 58CA30F9
P 4300 4750
F 0 "#PWR043" H 4300 4710 30  0001 C CNN
F 1 "+3.3V" H 4309 4888 30  0000 C CNN
F 2 "" H 4300 4750 60  0000 C CNN
F 3 "" H 4300 4750 60  0000 C CNN
	1    4300 4750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR044
U 1 1 58CECAEE
P 7200 5075
F 0 "#PWR044" H 7200 5035 30  0001 C CNN
F 1 "+3.3V" H 7209 5213 30  0000 C CNN
F 2 "" H 7200 5075 60  0000 C CNN
F 3 "" H 7200 5075 60  0000 C CNN
	1    7200 5075
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR045
U 1 1 58CECB3C
P 7200 5925
F 0 "#PWR045" H 7200 5675 50  0001 C CNN
F 1 "GND" H 7205 5752 50  0000 C CNN
F 2 "" H 7200 5925 60  0000 C CNN
F 3 "" H 7200 5925 60  0000 C CNN
	1    7200 5925
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5500 2825 5500
Wire Wire Line
	4400 5100 4150 5100
Wire Wire Line
	4150 5100 4150 4600
Wire Wire Line
	4150 4600 2825 4600
Wire Wire Line
	2825 4900 4075 4900
Wire Wire Line
	4075 4900 4075 5200
Wire Wire Line
	4075 5200 4400 5200
Wire Wire Line
	4400 5300 4000 5300
Wire Wire Line
	4000 5300 4000 5200
Wire Wire Line
	4000 5200 2825 5200
Wire Wire Line
	2825 5800 4075 5800
Wire Wire Line
	4075 5800 4075 5700
Wire Wire Line
	4075 5700 4400 5700
Wire Wire Line
	4400 5800 4150 5800
Wire Wire Line
	4150 5800 4150 6100
Wire Wire Line
	4150 6100 2825 6100
Wire Wire Line
	4800 6400 2825 6400
Wire Wire Line
	4075 4175 4075 4600
Connection ~ 4075 4600
Wire Wire Line
	3725 4175 3725 4900
Connection ~ 3725 4900
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
L +3.3V #PWR046
U 1 1 58EFD597
P 4075 3675
F 0 "#PWR046" H 4075 3635 30  0001 C CNN
F 1 "+3.3V" H 4084 3813 30  0000 C CNN
F 2 "" H 4075 3675 60  0000 C CNN
F 3 "" H 4075 3675 60  0000 C CNN
	1    4075 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR047
U 1 1 58EFD61A
P 3725 3675
F 0 "#PWR047" H 3725 3635 30  0001 C CNN
F 1 "+3.3V" H 3734 3813 30  0000 C CNN
F 2 "" H 3725 3675 60  0000 C CNN
F 3 "" H 3725 3675 60  0000 C CNN
	1    3725 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR048
U 1 1 58EFD69D
P 3375 3675
F 0 "#PWR048" H 3375 3635 30  0001 C CNN
F 1 "+3.3V" H 3384 3813 30  0000 C CNN
F 2 "" H 3375 3675 60  0000 C CNN
F 3 "" H 3375 3675 60  0000 C CNN
	1    3375 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR049
U 1 1 58EFD720
P 3025 3675
F 0 "#PWR049" H 3025 3635 30  0001 C CNN
F 1 "+3.3V" H 3034 3813 30  0000 C CNN
F 2 "" H 3025 3675 60  0000 C CNN
F 3 "" H 3025 3675 60  0000 C CNN
	1    3025 3675
	1    0    0    -1  
$EndComp
Text Notes 1650 1150 0    118  ~ 24
IR Cut Filter Driver
Text Notes 1300 1600 0    60   ~ 0
Hardware switching IR-Cut is bistable solenoid.\nUse a H-Bridge style drive for control. Approx 100mA rating.\nSee the electronics readme for test info.\n
Text Notes 5950 1150 0    118  ~ 24
IR Flash Driver
Text Notes 5050 1550 0    60   ~ 0
Allow the board to drive a IR flash.\nOnboard driver is potentially limiting, so provide header\nso the end-user can connect their own driver or expansion board
Text GLabel 5600 1900 0    60   Input ~ 0
FLASH_DAC
Text GLabel 2150 1900 0    60   Input ~ 0
IRCUT_A
Text GLabel 2150 2200 0    60   Input ~ 0
IRCUT_B
Text Notes 8675 1150 0    118  ~ 24
Ambient Light Sensor
Text Notes 8600 1400 0    60   ~ 0
Read ambient light to select IR-cut filter etc.
Text GLabel 10250 2200 2    60   Output ~ 0
AMBIENT_LIGHT
$Comp
L 47K_QUAD_ARRAY_1608M R9
U 4 1 594A8889
P 3025 3875
F 0 "R9" V 2900 3650 50  0000 L CNN
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
	4    3025 3875
	1    0    0    -1  
$EndComp
$Comp
L 47K_QUAD_ARRAY_1608M R9
U 3 1 594A8B4E
P 3375 3875
F 0 "R9" V 3250 3650 50  0000 L CNN
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
	3    3375 3875
	1    0    0    -1  
$EndComp
$Comp
L 47K_QUAD_ARRAY_1608M R9
U 2 1 594A8B8B
P 3725 3875
F 0 "R9" V 3600 3650 50  0000 L CNN
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
	2    3725 3875
	1    0    0    -1  
$EndComp
$Comp
L 47K_QUAD_ARRAY_1608M R9
U 1 1 594A8BD3
P 4075 3875
F 0 "R9" V 3950 3650 50  0000 L CNN
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
	1    4075 3875
	1    0    0    -1  
$EndComp
$Comp
L MOLEX_PICO_PTH_VERT_2_WAY P2
U 1 1 594D4823
P 2675 2050
F 0 "P2" H 2752 2080 50  0000 L CNN
F 1 "MOLEX_PICO_PTH_VERT_2_WAY" H 2752 2000 35  0000 L CNN
F 2 "Applidyne_Connector_Molex:MOLEX_PICOBLADE_53047-0210" V 2790 2050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1861728.pdf" V 2815 2050 20  0001 C CNN
F 4 "MOLEX" V 2865 2050 20  0001 C CNN "manf"
F 5 "53047-0210" V 2890 2050 20  0001 C CNN "manf#"
F 6 "Element14" V 2915 2050 20  0001 C CNN "Supplier"
F 7 "9733051" V 2940 2050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/molex/53047-0210/header-tht-vertical-1-25mm-2way/dp/9733051" V 2965 2050 20  0001 C CNN "Supplier URL"
F 9 "0.414" V 2990 2050 20  0001 C CNN "Supplier Price"
F 10 "5" V 3015 2050 20  0001 C CNN "Supplier Price Break"
	1    2675 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2475 2000 2350 2000
Wire Wire Line
	2350 2000 2350 1900
Wire Wire Line
	2350 1900 2150 1900
Wire Wire Line
	2475 2100 2350 2100
Wire Wire Line
	2350 2100 2350 2200
Wire Wire Line
	2350 2200 2150 2200
$Comp
L MNT_M3_PLATED MNT1
U 1 1 59512A53
P 9100 4700
F 0 "MNT1" H 9253 4700 47  0000 L CNN
F 1 "MNT_M3_PLATED" H 9253 4613 47  0000 L CNN
F 2 "Applidyne_Mount:MTGP650H330" H 9100 4875 47  0001 C CNN
F 3 "" H 9100 4700 60  0000 C CNN
	1    9100 4700
	1    0    0    -1  
$EndComp
$Comp
L MNT_M3_PLATED MNT3
U 1 1 59512AC9
P 9950 4700
F 0 "MNT3" H 10103 4700 47  0000 L CNN
F 1 "MNT_M3_PLATED" H 10103 4613 47  0000 L CNN
F 2 "Applidyne_Mount:MTGP650H330" H 9950 4875 47  0001 C CNN
F 3 "" H 9950 4700 60  0000 C CNN
	1    9950 4700
	1    0    0    -1  
$EndComp
$Comp
L MNT_M3_PLATED MNT4
U 1 1 59512BAB
P 9950 5200
F 0 "MNT4" H 10103 5200 47  0000 L CNN
F 1 "MNT_M3_PLATED" H 10103 5113 47  0000 L CNN
F 2 "Applidyne_Mount:MTGP650H330" H 9950 5375 47  0001 C CNN
F 3 "" H 9950 5200 60  0000 C CNN
	1    9950 5200
	1    0    0    -1  
$EndComp
$Comp
L MNT_M3_PLATED MNT2
U 1 1 59512C63
P 9100 5200
F 0 "MNT2" H 9253 5200 47  0000 L CNN
F 1 "MNT_M3_PLATED" H 9253 5113 47  0000 L CNN
F 2 "Applidyne_Mount:MTGP650H330" H 9100 5375 47  0001 C CNN
F 3 "" H 9100 5200 60  0000 C CNN
	1    9100 5200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR050
U 1 1 59512CD5
P 10550 4950
F 0 "#PWR050" H 10550 4700 50  0001 C CNN
F 1 "GND" V 10555 4822 50  0000 R CNN
F 2 "" H 10550 4950 60  0000 C CNN
F 3 "" H 10550 4950 60  0000 C CNN
	1    10550 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 4950 10550 4950
Wire Wire Line
	9100 4950 9100 4900
Wire Wire Line
	9950 4900 9950 4950
Connection ~ 9950 4950
Wire Wire Line
	9100 5400 9100 5450
Wire Wire Line
	9100 5450 10550 5450
Wire Wire Line
	9950 5400 9950 5450
Connection ~ 9950 5450
$Comp
L GND #PWR051
U 1 1 59512E83
P 10550 5450
F 0 "#PWR051" H 10550 5200 50  0001 C CNN
F 1 "GND" V 10555 5322 50  0000 R CNN
F 2 "" H 10550 5450 60  0000 C CNN
F 3 "" H 10550 5450 60  0000 C CNN
	1    10550 5450
	0    -1   -1   0   
$EndComp
$Comp
L MOLEX_47309-2651 CON1
U 1 1 594E6989
P 5300 5400
F 0 "CON1" H 6130 5316 50  0000 L CNN
F 1 "MOLEX_47309-2651" H 6130 5225 50  0000 L CNN
F 2 "Applidyne_Connector_Molex:MOLEX_47309-2651" V 6300 5400 50  0001 C CNN
F 3 "http://www.molex.com/molex/products/datasheet.jsp?part=active/0473092651_MEMORY_CARD_SOCKET.xml&channel=Products&Lang=en-US" V 6950 5200 50  0001 C CNN
F 4 "MOLEX" V 6200 5400 60  0001 C CNN "manf"
F 5 "47309-2651" V 6400 5400 60  0001 C CNN "manf#"
F 6 "Element14" V 6600 5400 60  0001 C CNN "Supplier"
F 7 "http://au.element14.com/molex/47309-2651/connector-micro-sd-header-smt/dp/1568092" V 6500 5400 60  0001 C CNN "Supplier URL"
F 8 "1568092" V 6700 5400 60  0001 C CNN "Supplier Part No"
F 9 "1.42" V 6800 5400 60  0001 C CNN "Supplier Price"
F 10 "25" V 6900 5400 60  0001 C CNN "Supplier Price Break"
	1    5300 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 6400 5600 6400
Connection ~ 5600 6400
$Comp
L GND #PWR052
U 1 1 594E6D09
P 5600 6450
F 0 "#PWR052" H 5600 6200 50  0001 C CNN
F 1 "GND" H 5605 6277 50  0000 C CNN
F 2 "" H 5600 6450 60  0000 C CNN
F 3 "" H 5600 6450 60  0000 C CNN
	1    5600 6450
	1    0    0    -1  
$EndComp
Text Notes 5000 2450 0    60   ~ 0
DAC output pin is also capable of PWM, and normal GPIO push pull.
$Comp
L VEMT3700 Q1
U 1 1 594F0B89
P 9900 1900
F 0 "Q1" H 10096 1938 40  0000 L CNN
F 1 "VEMT3700" H 10096 1862 40  0000 L CNN
F 2 "Applidyne_Device:VISHAY_VEMT3700N" H 9825 2000 29  0001 R CNN
F 3 "http://www.vishay.com/docs/81478/vemt3700.pdf" V 10125 1900 20  0001 C CNN
F 4 "VISHAY" V 10175 1900 20  0001 C CNN "manf"
F 5 "Vishay Phototransistor, NPN, 120degrees, 2-Pin PLCC package" V 10150 1900 20  0001 C CNN "desc"
F 6 "VEMT3700-GS08" V 10200 1900 20  0001 C CNN "manf#"
F 7 "RS Online" V 10225 1900 20  0001 C CNN "Supplier"
F 8 "710-3948" V 10250 1900 20  0001 C CNN "Supplier Part No"
F 9 "http://au.rs-online.com/web/p/phototransistors/7103948" V 10275 1900 20  0001 C CNN "Supplier URL"
F 10 "0.347" V 10300 1900 20  0001 C CNN "Supplier Price"
F 11 "10" V 10325 1900 20  0001 C CNN "Supplier Price Break"
	1    9900 1900
	1    0    0    -1  
$EndComp
Text Notes 8400 2600 0    60   ~ 0
TODO: Switch to a 0603/0805 \npackage transistor
$Comp
L 10K_1005M R10
U 1 1 594F0F97
P 10000 2300
F 0 "R10" H 10073 2185 50  0000 L CNN
F 1 "10K_1005M" H 10073 2105 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 10110 2150 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 10135 2150 20  0001 C CNN
F 4 "VISHAY" V 10185 2150 20  0001 C CNN "manf"
F 5 "CRCW040210K0FKED" V 10210 2150 20  0001 C CNN "manf#"
F 6 "Element14" V 10235 2150 20  0001 C CNN "Supplier"
F 7 "1469669" V 10260 2150 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210k0fked/res-thick-film-10k-1-0-063w-0402/dp/1469669" V 10285 2150 20  0001 C CNN "Supplier URL"
F 9 "0.009" V 10310 2150 20  0001 C CNN "Supplier Price"
F 10 "10" V 10335 2150 20  0001 C CNN "Supplier Price Break"
	1    10000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 2300 10000 2100
Wire Wire Line
	10000 2200 10250 2200
Connection ~ 10000 2200
Wire Wire Line
	10000 2600 10000 2700
$Comp
L GND #PWR053
U 1 1 594F128A
P 10000 2700
F 0 "#PWR053" H 10000 2450 50  0001 C CNN
F 1 "GND" H 10005 2527 50  0000 C CNN
F 2 "" H 10000 2700 60  0000 C CNN
F 3 "" H 10000 2700 60  0000 C CNN
	1    10000 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR054
U 1 1 594F12E8
P 10000 1600
F 0 "#PWR054" H 10000 1560 30  0001 C CNN
F 1 "+3.3V" H 10009 1738 30  0000 C CNN
F 2 "" H 10000 1600 60  0000 C CNN
F 3 "" H 10000 1600 60  0000 C CNN
	1    10000 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1600 10000 1700
$Comp
L GND #PWR055
U 1 1 594F2D3A
P 6050 2000
F 0 "#PWR055" H 6050 1750 50  0001 C CNN
F 1 "GND" H 6055 1827 50  0000 C CNN
F 2 "" H 6050 2000 60  0000 C CNN
F 3 "" H 6050 2000 60  0000 C CNN
	1    6050 2000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR056
U 1 1 594F2D65
P 6050 1800
F 0 "#PWR056" H 6050 1760 30  0001 C CNN
F 1 "+3.3V" H 6059 1938 30  0000 C CNN
F 2 "" H 6050 1800 60  0000 C CNN
F 3 "" H 6050 1800 60  0000 C CNN
	1    6050 1800
	1    0    0    -1  
$EndComp
$Comp
L 2.2UF_X7R_1608M C20
U 1 1 595188C0
P 7200 5400
F 0 "C20" H 7278 5335 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 7278 5255 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 7315 5300 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 7340 5300 20  0001 C CNN
F 4 "MURATA" V 7390 5300 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 7415 5300 20  0001 C CNN "manf#"
F 6 "Element14" V 7440 5300 20  0001 C CNN "Supplier"
F 7 "2611925" V 7465 5300 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 7490 5300 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 7515 5300 20  0001 C CNN "Supplier Price"
F 10 "10" V 7540 5300 20  0001 C CNN "Supplier Price Break"
	1    7200 5400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
