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
Sheet 5 5
Title "STM32 Camera Board"
Date "2017-07-18"
Rev "1.0.0"
Comp "Scott Rapson"
Comment1 "https://github.com/Scottapotamas/stm32-camera"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 5275 950  0    118  ~ 24
2MP CMOS Camera
$Comp
L OV02640-VL9A U5
U 1 1 59481BFB
P 4600 3500
F 0 "U5" H 4650 3625 60  0000 R CNN
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
L 100NF_X7R_1005M C21
U 1 1 594832D1
P 4400 5425
F 0 "C21" H 4477 5360 50  0000 L CNN
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
L GND #PWR57
U 1 1 594833B8
P 4400 5700
F 0 "#PWR57" H 4400 5450 50  0001 C CNN
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
RESET Active Low (internal pullup?)\nPWDN Active High (internal pulldown?)\nSTROBE indicates flash LED (no pull R)\n\nPull Up/Down specified in main pinout.\nSpecified as not included in hardware appnote.\nMicrocontroller pins can be configured \nas pullup or pulldown if required.
Text GLabel 7600 3750 2    60   BiDi ~ 0
SIO_D
Text GLabel 7600 3650 2    60   Input ~ 0
SIO_C
$Comp
L 4K7_1005M R12
U 1 1 5948382E
P 7500 3150
F 0 "R12" H 7573 3035 50  0000 L CNN
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
L 4K7_1005M R11
U 1 1 594838D9
P 7025 3175
F 0 "R11" H 7098 3060 50  0000 L CNN
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
Text Notes 5800 2500 0    60   ~ 0
PIXCK - Pixel clock from sensor\n6Mhz = 2.5fps\n36Mhz = 15fps\n\nVSYNC - Active FRAME\nHREF - Active Pixels/Line\nSee page 7 of overview appnote
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
L 100NF_X7R_1005M C22
U 1 1 59484912
P 4600 5425
F 0 "C22" H 4678 5360 50  0000 L CNN
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
L GND #PWR58
U 1 1 59484919
P 4600 5700
F 0 "#PWR58" H 4600 5450 50  0001 C CNN
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
Text Notes 1025 1625 0    60   ~ 0
1600x1200px resolution.\n140mW for 15fps 2MP.\n1/4" sensor. 2.2um pitch.\n0.6V/Lux-sec sensitivity.\n40dB S/N with 50dB dynamic range.\nADC run at 20Mhz at 10-bit.
Text Label 10150 1250 2    60   ~ 0
AVDD
Text Label 8275 1250 2    60   ~ 0
DVDD
Text Label 9300 2775 2    60   ~ 0
DOVDD
$Comp
L 1UF_X5R_1005M C24
U 1 1 594872C0
P 9300 1350
F 0 "C24" H 9378 1285 50  0000 L CNN
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
L GND #PWR64
U 1 1 59487366
P 9300 1750
F 0 "#PWR64" H 9300 1500 50  0001 C CNN
F 1 "GND" H 9305 1577 50  0000 C CNN
F 2 "" H 9300 1750 60  0000 C CNN
F 3 "" H 9300 1750 60  0000 C CNN
	1    9300 1750
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C27
U 1 1 5948770F
P 10400 2825
F 0 "C27" H 10478 2760 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 10478 2680 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10515 2725 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10540 2725 20  0001 C CNN
F 4 "TDK" V 10590 2725 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10615 2725 20  0001 C CNN "manf#"
F 6 "Element14" V 10640 2725 20  0001 C CNN "Supplier"
F 7 "2210822" V 10665 2725 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10690 2725 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10715 2725 20  0001 C CNN "Supplier Price"
F 10 "100" V 10740 2725 20  0001 C CNN "Supplier Price Break"
	1    10400 2825
	1    0    0    -1  
$EndComp
Text Label 10300 2775 2    60   ~ 0
EVDD
$Comp
L GND #PWR70
U 1 1 594877FB
P 10400 3125
F 0 "#PWR70" H 10400 2875 50  0001 C CNN
F 1 "GND" H 10405 2952 50  0000 C CNN
F 2 "" H 10400 3125 60  0000 C CNN
F 3 "" H 10400 3125 60  0000 C CNN
	1    10400 3125
	1    0    0    -1  
$EndComp
Text Label 10300 3075 2    60   ~ 0
EGND
Text Label 9225 1675 2    60   ~ 0
SGND
$Comp
L 100NF_X7R_1005M C25
U 1 1 59487AE8
P 9425 2825
F 0 "C25" H 9503 2760 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 9503 2680 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9540 2725 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9565 2725 20  0001 C CNN
F 4 "TDK" V 9615 2725 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9640 2725 20  0001 C CNN "manf#"
F 6 "Element14" V 9665 2725 20  0001 C CNN "Supplier"
F 7 "2210822" V 9690 2725 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9715 2725 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9740 2725 20  0001 C CNN "Supplier Price"
F 10 "100" V 9765 2725 20  0001 C CNN "Supplier Price Break"
	1    9425 2825
	1    0    0    -1  
$EndComp
Text Label 9300 3075 2    60   ~ 0
DOGND
$Comp
L GND #PWR66
U 1 1 59487BCE
P 9425 3125
F 0 "#PWR66" H 9425 2875 50  0001 C CNN
F 1 "GND" H 9430 2952 50  0000 C CNN
F 2 "" H 9425 3125 60  0000 C CNN
F 3 "" H 9425 3125 60  0000 C CNN
	1    9425 3125
	1    0    0    -1  
$EndComp
Text Label 8275 1675 2    60   ~ 0
DGND
Text Label 10150 1675 2    60   ~ 0
AGND
$Comp
L 100NF_X7R_1005M C26
U 1 1 59488533
P 10225 1350
F 0 "C26" H 10303 1285 50  0000 L CNN
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
Text Notes 7825 2125 0    60   ~ 0
AGND and DGND should be connected outside sensor area grounding
Text Notes 7700 750  0    60   ~ 0
If DOVDD is same as AVDD, share reg and use hardware RC to separate.\nOtherwise use 3 regs...
$Comp
L +2.8V #PWR63
U 1 1 5948B73C
P 9300 1150
F 0 "#PWR63" H 9300 1110 30  0001 C CNN
F 1 "+2.8V" H 9309 1288 30  0000 C CNN
F 2 "" H 9300 1150 60  0000 C CNN
F 3 "" H 9300 1150 60  0000 C CNN
	1    9300 1150
	1    0    0    -1  
$EndComp
$Comp
L +1.3V #PWR61
U 1 1 5948B79A
P 8350 1150
F 0 "#PWR61" H 8350 1110 30  0001 C CNN
F 1 "+1.3V" H 8359 1288 30  0000 C CNN
F 2 "" H 8350 1150 60  0000 C CNN
F 3 "" H 8350 1150 60  0000 C CNN
	1    8350 1150
	1    0    0    -1  
$EndComp
$Comp
L +2.8V #PWR67
U 1 1 5948B7E3
P 10225 1150
F 0 "#PWR67" H 10225 1110 30  0001 C CNN
F 1 "+2.8V" H 10234 1288 30  0000 C CNN
F 2 "" H 10225 1150 60  0000 C CNN
F 3 "" H 10225 1150 60  0000 C CNN
	1    10225 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR68
U 1 1 5948B86F
P 10225 1750
F 0 "#PWR68" H 10225 1500 50  0001 C CNN
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
L GND #PWR62
U 1 1 5948BD7C
P 8350 1750
F 0 "#PWR62" H 8350 1500 50  0001 C CNN
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
Text Notes 7475 5850 0    60   ~ 0
If micro is disabling/enabling regs sequentially, ensure turn on order is:\n3.3V -> 1.3V -> 2.8V or the camera gets angry.\n\nAfter last supply is on for 3ms, the reset line on the OV2460 can go high.\n
$Comp
L +3.3V #PWR65
U 1 1 594A76B0
P 9425 2700
F 0 "#PWR65" H 9425 2660 30  0001 C CNN
F 1 "+3.3V" H 9434 2838 30  0000 C CNN
F 2 "" H 9425 2700 60  0000 C CNN
F 3 "" H 9425 2700 60  0000 C CNN
	1    9425 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9425 2700 9425 2825
Wire Wire Line
	9425 3025 9425 3125
Wire Wire Line
	9425 3075 9300 3075
Connection ~ 9425 3075
Wire Wire Line
	9300 2775 9425 2775
Connection ~ 9425 2775
Wire Wire Line
	10400 2825 10400 2700
Wire Wire Line
	10400 2775 10300 2775
Connection ~ 10400 2775
Wire Wire Line
	10400 3125 10400 3025
Wire Wire Line
	10400 3075 10300 3075
Connection ~ 10400 3075
$Comp
L +3.3V #PWR69
U 1 1 594A7A32
P 10400 2700
F 0 "#PWR69" H 10400 2660 30  0001 C CNN
F 1 "+3.3V" H 10409 2838 30  0000 C CNN
F 2 "" H 10400 2700 60  0000 C CNN
F 3 "" H 10400 2700 60  0000 C CNN
	1    10400 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR60
U 1 1 594A7B15
P 7500 3100
F 0 "#PWR60" H 7500 3060 30  0001 C CNN
F 1 "+3.3V" H 7509 3238 30  0000 C CNN
F 2 "" H 7500 3100 60  0000 C CNN
F 3 "" H 7500 3100 60  0000 C CNN
	1    7500 3100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR59
U 1 1 594A7B32
P 7025 3100
F 0 "#PWR59" H 7025 3060 30  0001 C CNN
F 1 "+3.3V" H 7034 3238 30  0000 C CNN
F 2 "" H 7025 3100 60  0000 C CNN
F 3 "" H 7025 3100 60  0000 C CNN
	1    7025 3100
	1    0    0    -1  
$EndComp
Text Notes 1150 2400 0    59   ~ 12
IR-Cut Switchable Filter\nLens Mount
Text Notes 800  2600 0    60   ~ 0
Bisable Solenoid drive and connector on misc page
$Comp
L M12_LENS_MOUNT_IR_SWITCHNG MP1
U 1 1 594F9921
P 1650 3150
F 0 "MP1" H 1650 3562 60  0000 C CNN
F 1 "M12_LENS_MOUNT_IR_SWITCHNG" H 1650 3456 60  0000 C CNN
F 2 "Applidyne_Special:M12x0.5_LENS_MOUNT_IR_SWITCHNG" H 1650 2700 60  0001 C CNN
F 3 "" H 1670 2800 60  0001 C CNN
F 4 "NOVOXY" H 1650 2560 60  0001 C CNN "manf"
F 5 "UNKNOWN" H 1650 2460 60  0001 C CNN "manf#"
F 6 "Aliexpress" H 1660 2350 60  0001 C CNN "Supplier"
F 7 "IR CUT" H 1650 2250 60  0001 C CNN "Supplier Part No"
F 8 "https://www.aliexpress.com/item/Full-Metal-High-Quality-CCTV-Camera-IP-camera-Module-Accessories-M12-0-5-MTV-Mount-Lense/32709601083.html" H 1650 2160 60  0001 C CNN "Supplier URL"
F 9 "3.07" H 1650 2050 60  0001 C CNN "Supplier Price"
F 10 "2" H 1650 1950 60  0001 C CNN "Supplier Price Break"
	1    1650 3150
	1    0    0    -1  
$EndComp
$Comp
L 4.7UF_X5R_1005M C23
U 1 1 59526835
P 8350 1350
F 0 "C23" H 8428 1285 50  0000 L CNN
F 1 "4.7UF_X5R_1005M" H 8428 1205 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8465 1250 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2047949.pdf" V 8490 1250 20  0001 C CNN
F 4 "MURATA" V 8540 1250 20  0001 C CNN "manf"
F 5 "GRM155R60J475ME47D" V 8565 1250 20  0001 C CNN "manf#"
F 6 "Element14" V 8590 1250 20  0001 C CNN "Supplier"
F 7 "2426952" V 8615 1250 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm155r60j475me47d/cap-mlcc-x5r-4-7uf-6-3v-0402/dp/2426952" V 8640 1250 20  0001 C CNN "Supplier URL"
F 9 "0.083" V 8665 1250 20  0001 C CNN "Supplier Price"
F 10 "100" V 8690 1250 20  0001 C CNN "Supplier Price Break"
	1    8350 1350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
