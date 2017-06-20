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
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 5275 950  0    118  ~ 24
2MP CMOS Camera
$Comp
L OV02640-VL9A U?
U 1 1 59481BFB
P 4600 3500
F 0 "U?" H 4650 3625 60  0000 R CNN
F 1 "OV02640-VL9A" H 4925 3475 60  0000 R CNN
F 2 "Applidyne_Special:OV2640_CSP_38" H 4600 1875 60  0001 C CNN
F 3 "http://www.uctronics.com/download/cam_module/OV2640DS.pdf" H 4575 2000 60  0001 C CNN
F 4 "OmniVision" H 4575 1760 60  0001 C CNN "manf"
F 5 "OV02640-VL9A" H 4585 1650 60  0001 C CNN "manf#"
F 6 "OmniVision" H 4575 1540 60  0001 C CNN "Supplier"
F 7 "N/A" H 4575 1430 60  0001 C CNN "Supplier Part No"
F 8 "N/A" H 4575 1330 60  0001 C CNN "Supplier URL"
F 9 "3.40" H 4575 1210 60  0001 C CNN "Supplier Price"
F 10 "10" H 4585 1100 60  0001 C CNN "Supplier Price Break"
	1    4600 3500
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 594832D1
P 4400 5425
F 0 "C?" H 4477 5360 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 4477 5280 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 4515 5325 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 4540 5325 20  0001 C CNN
F 4 "TDK" V 4590 5325 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 4615 5325 20  0001 C CNN "manf#"
F 6 "Element14" V 4640 5325 20  0001 C CNN "Supplier"
F 7 "2210822" V 4665 5325 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 4690 5325 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 4715 5325 20  0001 C CNN "Supplier Price"
F 10 "100" V 4740 5325 20  0001 C CNN "Supplier Price Break"
	1    4400 5425
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 594833B8
P 4400 5700
F 0 "#PWR?" H 4400 5450 50  0001 C CNN
F 1 "GND" H 4405 5527 50  0000 C CNN
F 2 "" H 4400 5700 60  0000 C CNN
F 3 "" H 4400 5700 60  0000 C CNN
	1    4400 5700
	1    0    0    -1  
$EndComp
Text GLabel 4150 5000 3    60   Input ~ 0
PWDN
Text GLabel 4050 5000 3    60   Input ~ 0
RESET
Text Notes 1725 5175 0    60   ~ 0
RESET Active Low (internal pullup?)\nPWDN Active High (internal pulldown?)\nSTROBE indicates flash LED (no pull R)\n\nPull Up/Down specified in main pinout.\nSpecified as not included in hardware appnote.
Text GLabel 7600 3750 2    60   BiDi ~ 0
SIO_D
Text GLabel 7600 3650 2    60   Input ~ 0
SIO_C
$Comp
L 4K7_1005M R?
U 1 1 5948382E
P 7500 3150
F 0 "R?" H 7573 3035 50  0000 L CNN
F 1 "4K7_1005M" H 7573 2955 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 7610 3000 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2049157.pdf" V 7635 3000 20  0001 C CNN
F 4 "VISHAY" V 7685 3000 20  0001 C CNN "manf"
F 5 "CRCW08054K70FKTA" V 7710 3000 20  0001 C CNN "manf#"
F 6 "Element14" V 7735 3000 20  0001 C CNN "Supplier"
F 7 "1653013" V 7760 3000 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw08054k70fkta/res-thick-film-4k7-1-0-125w-0805/dp/1653013" V 7785 3000 20  0001 C CNN "Supplier URL"
F 9 "0.109" V 7810 3000 20  0001 C CNN "Supplier Price"
F 10 "100" V 7835 3000 20  0001 C CNN "Supplier Price Break"
	1    7500 3150
	1    0    0    -1  
$EndComp
$Comp
L 4K7_1005M R?
U 1 1 594838D9
P 7025 3175
F 0 "R?" H 7098 3060 50  0000 L CNN
F 1 "4K7_1005M" H 7098 2980 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 7135 3025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2049157.pdf" V 7160 3025 20  0001 C CNN
F 4 "VISHAY" V 7210 3025 20  0001 C CNN "manf"
F 5 "CRCW08054K70FKTA" V 7235 3025 20  0001 C CNN "manf#"
F 6 "Element14" V 7260 3025 20  0001 C CNN "Supplier"
F 7 "1653013" V 7285 3025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw08054k70fkta/res-thick-film-4k7-1-0-125w-0805/dp/1653013" V 7310 3025 20  0001 C CNN "Supplier URL"
F 9 "0.109" V 7335 3025 20  0001 C CNN "Supplier Price"
F 10 "100" V 7360 3025 20  0001 C CNN "Supplier Price Break"
	1    7025 3175
	1    0    0    -1  
$EndComp
Text Notes 8000 3825 0    60   ~ 0
I2C Config Interface.\nRecommended 100k during bringup.\n400kHz capable.
Text GLabel 6225 3550 2    60   Output ~ 0
HREF
Text GLabel 6200 3850 2    60   Input ~ 0
XCLK
Text GLabel 6225 3350 2    60   Input ~ 0
PIXCK
Text GLabel 6225 3450 2    60   Output ~ 0
VSYNC
Text Notes 6325 2650 0    60   ~ 0
PIXCK - Pixel clock from sensor\nVSYNC - Active FRAME\nHREF - Active Pixels/Line
Text Notes 6425 2975 0    39   ~ 8
investigate if stm32 internal pullups (30-50k) \nwould be even close to driving this... reduce parts
Text GLabel 4150 1950 1    60   Output ~ 0
D7
Text GLabel 4250 1950 1    60   Output ~ 0
D6
Text GLabel 4350 1950 1    60   Output ~ 0
D5
Text GLabel 4450 1950 1    60   Output ~ 0
D4
Text GLabel 4550 1950 1    60   Output ~ 0
D3
Text GLabel 4650 1950 1    60   Output ~ 0
D2
Text GLabel 4750 1950 1    60   Output ~ 0
D1
Text GLabel 4850 1950 1    60   Output ~ 0
D0
Text Notes 4075 1625 0    60   ~ 0
In 8-bit mode, Y0 and Y1 aren't used.\nThus LSB is D2.\nNo pull resistors on these pins.
NoConn ~ 5700 3250
NoConn ~ 5700 3150
Text Label 4350 4900 1    60   ~ 0
SVDD
Text Label 4750 4900 1    60   ~ 0
SVDD
Text Label 4650 4900 1    60   ~ 0
SGND
Text Label 4050 2275 1    60   ~ 0
DVDD
Text Label 5050 2275 1    60   ~ 0
DVDD
Text Label 4950 2275 1    60   ~ 0
DGND
Text Label 5150 2275 1    60   ~ 0
EVDD
Text Label 3350 3350 2    60   ~ 0
DGND
Text Label 6075 2950 2    60   ~ 0
EVDD
Text Label 6075 3050 2    60   ~ 0
EGND
Text Label 6075 3950 2    60   ~ 0
DOVDD
Text Label 6075 4050 2    60   ~ 0
DOGND
$Comp
L 100NF_X7R_1005M C?
U 1 1 59484912
P 4600 5425
F 0 "C?" H 4678 5360 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 4678 5280 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 4715 5325 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 4740 5325 20  0001 C CNN
F 4 "TDK" V 4790 5325 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 4815 5325 20  0001 C CNN "manf#"
F 6 "Element14" V 4840 5325 20  0001 C CNN "Supplier"
F 7 "2210822" V 4865 5325 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 4890 5325 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 4915 5325 20  0001 C CNN "Supplier Price"
F 10 "100" V 4940 5325 20  0001 C CNN "Supplier Price Break"
	1    4600 5425
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59484919
P 4600 5700
F 0 "#PWR?" H 4600 5450 50  0001 C CNN
F 1 "GND" H 4605 5527 50  0000 C CNN
F 2 "" H 4600 5700 60  0000 C CNN
F 3 "" H 4600 5700 60  0000 C CNN
	1    4600 5700
	1    0    0    -1  
$EndComp
Text GLabel 4250 5000 3    60   Output ~ 0
STROBE
Text Label 4950 4900 1    60   ~ 0
AVDD
Text Label 4850 4900 1    60   ~ 0
AGND
Text Notes 6525 3975 0    60   ~ 0
XCLK is master clock.\nMust be >6Mhz. 24MHz typ.
Text GLabel 5150 5000 3    60   Input ~ 0
FREX
Text GLabel 5050 5000 3    60   Input ~ 0
EXPSTB
Text Notes 5400 4875 0    60   ~ 0
FREX activates a snapshot sequence.\nEXPSTB 0 - sensor starts exposure (only works with snapshot)\nEXPSTB 1 - sensor stays in reset
Wire Wire Line
	4400 5625 4400 5700
Wire Wire Line
	4150 5000 4150 4600
Wire Wire Line
	4050 4600 4050 5000
Wire Wire Line
	5700 3650 7600 3650
Wire Wire Line
	5700 3750 7600 3750
Wire Wire Line
	7025 3475 7025 3650
Connection ~ 7025 3650
Wire Wire Line
	7500 3450 7500 3750
Connection ~ 7500 3750
Wire Wire Line
	7500 3150 7500 3100
Wire Wire Line
	7025 3175 7025 3100
Wire Wire Line
	6200 3850 5700 3850
Wire Wire Line
	5700 3550 6225 3550
Wire Wire Line
	6225 3350 5700 3350
Wire Wire Line
	6225 3450 5700 3450
Wire Wire Line
	4150 1950 4150 2400
Wire Wire Line
	4850 1950 4850 2400
Wire Wire Line
	4750 1950 4750 2400
Wire Wire Line
	4650 2400 4650 1950
Wire Wire Line
	4550 1950 4550 2400
Wire Wire Line
	4450 2400 4450 1950
Wire Wire Line
	4350 1950 4350 2400
Wire Wire Line
	4250 2400 4250 1950
Wire Wire Line
	4350 4600 4350 4900
Wire Wire Line
	4650 4600 4650 4900
Wire Wire Line
	4750 4600 4750 4900
Wire Wire Line
	3500 3350 3350 3350
Wire Wire Line
	6075 2950 5700 2950
Wire Wire Line
	5700 3050 6075 3050
Wire Wire Line
	5700 3950 6075 3950
Wire Wire Line
	5700 4050 6075 4050
Wire Wire Line
	4950 2275 4950 2400
Wire Wire Line
	5050 2275 5050 2400
Wire Wire Line
	5150 2275 5150 2400
Wire Wire Line
	4050 2275 4050 2400
Wire Wire Line
	4250 4600 4250 5000
Wire Wire Line
	4600 5625 4600 5700
Wire Wire Line
	4450 4600 4450 5200
Wire Wire Line
	4550 4600 4550 5200
Wire Wire Line
	4400 5425 4400 5200
Wire Wire Line
	4400 5200 4450 5200
Wire Wire Line
	4550 5200 4600 5200
Wire Wire Line
	4600 5200 4600 5425
Wire Wire Line
	4850 4600 4850 4900
Wire Wire Line
	4950 4600 4950 4900
Wire Wire Line
	5050 5000 5050 4600
Wire Wire Line
	5150 5000 5150 4600
Text Notes 950  1250 0    60   ~ 0
WRITE STATS FOR CAMERA HERE
Text Label 10150 1250 2    60   ~ 0
AVDD
Text Label 8275 1250 2    60   ~ 0
DVDD
Text Label 9325 2775 2    60   ~ 0
DOVDD
Text Notes 9450 2400 0    60   ~ 0
1.8V to 3.0V
$Comp
L 1UF_X5R_1005M C?
U 1 1 594872C0
P 9300 1350
F 0 "C?" H 9378 1285 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 9378 1205 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9415 1250 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 9440 1250 20  0001 C CNN
F 4 "TDK" V 9490 1250 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 9515 1250 20  0001 C CNN "manf#"
F 6 "Element14" V 9540 1250 20  0001 C CNN "Supplier"
F 7 "2346885" V 9565 1250 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 9590 1250 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 9615 1250 20  0001 C CNN "Supplier Price"
F 10 "100" V 9640 1250 20  0001 C CNN "Supplier Price Break"
	1    9300 1350
	1    0    0    -1  
$EndComp
Text Label 9225 1250 2    60   ~ 0
SVDD
$Comp
L GND #PWR?
U 1 1 59487366
P 9300 1750
F 0 "#PWR?" H 9300 1500 50  0001 C CNN
F 1 "GND" H 9305 1577 50  0000 C CNN
F 2 "" H 9300 1750 60  0000 C CNN
F 3 "" H 9300 1750 60  0000 C CNN
	1    9300 1750
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 5948770F
P 10400 2800
F 0 "C?" H 10478 2735 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 10478 2655 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10515 2700 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10540 2700 20  0001 C CNN
F 4 "TDK" V 10590 2700 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10615 2700 20  0001 C CNN "manf#"
F 6 "Element14" V 10640 2700 20  0001 C CNN "Supplier"
F 7 "2210822" V 10665 2700 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10690 2700 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10715 2700 20  0001 C CNN "Supplier Price"
F 10 "100" V 10740 2700 20  0001 C CNN "Supplier Price Break"
	1    10400 2800
	1    0    0    -1  
$EndComp
Text Label 10375 2750 2    60   ~ 0
EVDD
$Comp
L GND #PWR?
U 1 1 594877FB
P 10400 3125
F 0 "#PWR?" H 10400 2875 50  0001 C CNN
F 1 "GND" H 10405 2952 50  0000 C CNN
F 2 "" H 10400 3125 60  0000 C CNN
F 3 "" H 10400 3125 60  0000 C CNN
	1    10400 3125
	1    0    0    -1  
$EndComp
Text Label 10325 3100 2    60   ~ 0
EGND
Text Label 9225 1675 2    60   ~ 0
SGND
$Comp
L 100NF_X7R_1005M C?
U 1 1 59487AE8
P 9425 2800
F 0 "C?" H 9503 2735 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 9503 2655 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9540 2700 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9565 2700 20  0001 C CNN
F 4 "TDK" V 9615 2700 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9640 2700 20  0001 C CNN "manf#"
F 6 "Element14" V 9665 2700 20  0001 C CNN "Supplier"
F 7 "2210822" V 9690 2700 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9715 2700 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9740 2700 20  0001 C CNN "Supplier Price"
F 10 "100" V 9765 2700 20  0001 C CNN "Supplier Price Break"
	1    9425 2800
	1    0    0    -1  
$EndComp
Text Label 9350 3025 2    60   ~ 0
DOGND
$Comp
L GND #PWR?
U 1 1 59487BCE
P 9425 3100
F 0 "#PWR?" H 9425 2850 50  0001 C CNN
F 1 "GND" H 9430 2927 50  0000 C CNN
F 2 "" H 9425 3100 60  0000 C CNN
F 3 "" H 9425 3100 60  0000 C CNN
	1    9425 3100
	1    0    0    -1  
$EndComp
Text Label 8275 1675 2    60   ~ 0
DGND
Text Label 10150 1675 2    60   ~ 0
AGND
$Comp
L 100NF_X7R_1005M C?
U 1 1 59488533
P 10225 1350
F 0 "C?" H 10303 1285 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 10303 1205 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10340 1250 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10365 1250 20  0001 C CNN
F 4 "TDK" V 10415 1250 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10440 1250 20  0001 C CNN "manf#"
F 6 "Element14" V 10465 1250 20  0001 C CNN "Supplier"
F 7 "2210822" V 10490 1250 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10515 1250 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10540 1250 20  0001 C CNN "Supplier Price"
F 10 "100" V 10565 1250 20  0001 C CNN "Supplier Price Break"
	1    10225 1350
	1    0    0    -1  
$EndComp
Text Notes 8100 1500 0    60   ~ 0
4.7uF 0603
Text Notes 7825 2125 0    60   ~ 0
AGND and DGND should be connected outside sensor area grounding
Text Notes 7700 750  0    60   ~ 0
If DOVDD is same as AVDD, share reg and use hardware RC to separate.\nOtherwise use 3 regs...
$Comp
L +2.8V #PWR?
U 1 1 5948B73C
P 9300 1150
F 0 "#PWR?" H 9300 1110 30  0001 C CNN
F 1 "+2.8V" H 9309 1288 30  0000 C CNN
F 2 "" H 9300 1150 60  0000 C CNN
F 3 "" H 9300 1150 60  0000 C CNN
	1    9300 1150
	1    0    0    -1  
$EndComp
$Comp
L +1.3V #PWR?
U 1 1 5948B79A
P 8350 1150
F 0 "#PWR?" H 8350 1110 30  0001 C CNN
F 1 "+1.3V" H 8359 1288 30  0000 C CNN
F 2 "" H 8350 1150 60  0000 C CNN
F 3 "" H 8350 1150 60  0000 C CNN
	1    8350 1150
	1    0    0    -1  
$EndComp
$Comp
L +2.8V #PWR?
U 1 1 5948B7E3
P 10225 1150
F 0 "#PWR?" H 10225 1110 30  0001 C CNN
F 1 "+2.8V" H 10234 1288 30  0000 C CNN
F 2 "" H 10225 1150 60  0000 C CNN
F 3 "" H 10225 1150 60  0000 C CNN
	1    10225 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5948B86F
P 10225 1750
F 0 "#PWR?" H 10225 1500 50  0001 C CNN
F 1 "GND" H 10230 1577 50  0000 C CNN
F 2 "" H 10225 1750 60  0000 C CNN
F 3 "" H 10225 1750 60  0000 C CNN
	1    10225 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10225 1550 10225 1750
Wire Wire Line
	10225 1150 10225 1350
Wire Wire Line
	10150 1250 10225 1250
Connection ~ 10225 1250
Wire Wire Line
	10150 1675 10225 1675
Connection ~ 10225 1675
Wire Wire Line
	9300 1550 9300 1750
Wire Wire Line
	9300 1150 9300 1350
Wire Wire Line
	9225 1675 9300 1675
Connection ~ 9300 1675
Wire Wire Line
	9225 1250 9300 1250
Connection ~ 9300 1250
Wire Wire Line
	8350 1150 8350 1350
Wire Wire Line
	8275 1250 8350 1250
Connection ~ 8350 1250
Wire Wire Line
	8350 1550 8350 1750
Wire Wire Line
	8275 1675 8350 1675
Connection ~ 8350 1675
$Comp
L GND #PWR?
U 1 1 5948BD7C
P 8350 1750
F 0 "#PWR?" H 8350 1500 50  0001 C CNN
F 1 "GND" H 8355 1577 50  0000 C CNN
F 2 "" H 8350 1750 60  0000 C CNN
F 3 "" H 8350 1750 60  0000 C CNN
	1    8350 1750
	1    0    0    -1  
$EndComp
Text Notes 8075 925  0    60   ~ 0
Sensor Core
Text Notes 9950 2525 0    60   ~ 0
Internal Regulator
Text Notes 9125 2500 0    60   ~ 0
Digital IO
Text Notes 8975 925  0    60   ~ 0
Sensor Array
Text Notes 9875 925  0    60   ~ 0
Analog Frontend
Text Notes 1150 950  0    59   ~ 12
Camera Specifications
$EndSCHEMATC
