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
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 5400 975  0    118  ~ 24
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
Text Notes 1500 5325 0    60   ~ 0
RESET Active Low (internal pullup?)\nPWDN Active High (internal pulldown?)\nSTROBE indicates flash LED (no pull R)\n\nPull Up/Down specified in main pinout.\nSpecified as not included in hardware appnote.
Text GLabel 7825 3750 2    60   BiDi ~ 0
SIO_D
Text GLabel 7825 3650 2    60   Input ~ 0
SIO_C
$Comp
L 4K7_1005M R?
U 1 1 5948382E
P 7750 3150
F 0 "R?" H 7823 3035 50  0000 L CNN
F 1 "4K7_1005M" H 7823 2955 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 7860 3000 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2049157.pdf" V 7885 3000 20  0001 C CNN
F 4 "VISHAY" V 7935 3000 20  0001 C CNN "manf"
F 5 "CRCW08054K70FKTA" V 7960 3000 20  0001 C CNN "manf#"
F 6 "Element14" V 7985 3000 20  0001 C CNN "Supplier"
F 7 "1653013" V 8010 3000 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw08054k70fkta/res-thick-film-4k7-1-0-125w-0805/dp/1653013" V 8035 3000 20  0001 C CNN "Supplier URL"
F 9 "0.109" V 8060 3000 20  0001 C CNN "Supplier Price"
F 10 "100" V 8085 3000 20  0001 C CNN "Supplier Price Break"
	1    7750 3150
	1    0    0    -1  
$EndComp
$Comp
L 4K7_1005M R?
U 1 1 594838D9
P 7275 3150
F 0 "R?" H 7348 3035 50  0000 L CNN
F 1 "4K7_1005M" H 7348 2955 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 7385 3000 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2049157.pdf" V 7410 3000 20  0001 C CNN
F 4 "VISHAY" V 7460 3000 20  0001 C CNN "manf"
F 5 "CRCW08054K70FKTA" V 7485 3000 20  0001 C CNN "manf#"
F 6 "Element14" V 7510 3000 20  0001 C CNN "Supplier"
F 7 "1653013" V 7535 3000 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw08054k70fkta/res-thick-film-4k7-1-0-125w-0805/dp/1653013" V 7560 3000 20  0001 C CNN "Supplier URL"
F 9 "0.109" V 7585 3000 20  0001 C CNN "Supplier Price"
F 10 "100" V 7610 3000 20  0001 C CNN "Supplier Price Break"
	1    7275 3150
	1    0    0    -1  
$EndComp
Text Notes 8225 3825 0    60   ~ 0
I2C Config Interface.\nRecommended 100k during bringup.\n400kHz capable.
Text GLabel 6225 3550 2    60   Output ~ 0
HREF
Text GLabel 6200 3850 2    60   Input ~ 0
XCLK
Text GLabel 6225 3350 2    60   Input ~ 0
PIXCK
Text GLabel 6225 3450 2    60   Output ~ 0
VSYNC
Text Notes 6850 2825 0    60   ~ 0
PIXCK - Pixel clock from sensor\nVSYNC - Active FRAME\nHREF - Active Pixels/Line
Text Notes 8550 4500 0    60   ~ 12
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
Text Notes 5425 2250 0    60   ~ 0
DVDD is Sensor core power.\nEVDD is internal regulator.\n
Text Notes 5750 4450 0    60   ~ 0
DOVDD is digital IO power\nDOGND is digital IO ground
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
Text Notes 5450 4925 0    60   ~ 0
AVDD is the analog power.\nSVDD is sensor array power.\n
Text Notes 6525 3975 0    60   ~ 0
XCLK is master clock.\nMust be >6Mhz. 24MHz typ.
Text GLabel 5150 5000 3    60   Input ~ 0
FREX
Text GLabel 5050 5000 3    60   Input ~ 0
EXPSTB
Text Notes 5450 5350 0    60   ~ 0
FREX activates a snapshot sequence.\nEXPSTB 0 - sensor starts exposure (only works with snapshot)\nEXPSTB 1 - sensor stays in reset
Wire Wire Line
	4400 5625 4400 5700
Wire Wire Line
	4150 5000 4150 4600
Wire Wire Line
	4050 4600 4050 5000
Wire Wire Line
	5700 3650 7825 3650
Wire Wire Line
	5700 3750 7825 3750
Wire Wire Line
	7275 3450 7275 3650
Connection ~ 7275 3650
Wire Wire Line
	7750 3450 7750 3750
Connection ~ 7750 3750
Wire Wire Line
	7750 3150 7750 3100
Wire Wire Line
	7275 3150 7275 3100
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
Text Notes 825  1150 0    60   ~ 0
TODO\n\nWRITE STATS FOR CAMERA HERE
Text Label 10125 1175 2    60   ~ 0
AVDD
Text Notes 9700 1000 0    60   ~ 0
2.8V
Text Label 8350 1675 2    60   ~ 0
DVDD
Text Notes 8225 1450 0    60   ~ 0
1.3V
Text Label 9275 2400 2    60   ~ 0
DOVDD
Text Notes 9575 2125 0    60   ~ 0
1.8V to 3.0V
$Comp
L 1UF_X5R_1005M C?
U 1 1 594872C0
P 9525 1300
F 0 "C?" H 9603 1235 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 9603 1155 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9640 1200 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 9665 1200 20  0001 C CNN
F 4 "TDK" V 9715 1200 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 9740 1200 20  0001 C CNN "manf#"
F 6 "Element14" V 9765 1200 20  0001 C CNN "Supplier"
F 7 "2346885" V 9790 1200 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 9815 1200 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 9840 1200 20  0001 C CNN "Supplier Price"
F 10 "100" V 9865 1200 20  0001 C CNN "Supplier Price Break"
	1    9525 1300
	1    0    0    -1  
$EndComp
Text Label 9450 1200 2    60   ~ 0
SVDD
$Comp
L GND #PWR?
U 1 1 59487366
P 9525 1625
F 0 "#PWR?" H 9525 1375 50  0001 C CNN
F 1 "GND" H 9530 1452 50  0000 C CNN
F 2 "" H 9525 1625 60  0000 C CNN
F 3 "" H 9525 1625 60  0000 C CNN
	1    9525 1625
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 5948770F
P 10350 2425
F 0 "C?" H 10428 2360 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 10428 2280 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10465 2325 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10490 2325 20  0001 C CNN
F 4 "TDK" V 10540 2325 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10565 2325 20  0001 C CNN "manf#"
F 6 "Element14" V 10590 2325 20  0001 C CNN "Supplier"
F 7 "2210822" V 10615 2325 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10640 2325 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10665 2325 20  0001 C CNN "Supplier Price"
F 10 "100" V 10690 2325 20  0001 C CNN "Supplier Price Break"
	1    10350 2425
	1    0    0    -1  
$EndComp
Text Label 10325 2375 2    60   ~ 0
EVDD
$Comp
L GND #PWR?
U 1 1 594877FB
P 10350 2750
F 0 "#PWR?" H 10350 2500 50  0001 C CNN
F 1 "GND" H 10355 2577 50  0000 C CNN
F 2 "" H 10350 2750 60  0000 C CNN
F 3 "" H 10350 2750 60  0000 C CNN
	1    10350 2750
	1    0    0    -1  
$EndComp
Text Label 10275 2725 2    60   ~ 0
EGND
Text Label 9450 1600 2    60   ~ 0
SGND
$Comp
L 100NF_X7R_1005M C?
U 1 1 59487AE8
P 9375 2425
F 0 "C?" H 9453 2360 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 9453 2280 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9490 2325 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9515 2325 20  0001 C CNN
F 4 "TDK" V 9565 2325 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9590 2325 20  0001 C CNN "manf#"
F 6 "Element14" V 9615 2325 20  0001 C CNN "Supplier"
F 7 "2210822" V 9640 2325 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9665 2325 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9690 2325 20  0001 C CNN "Supplier Price"
F 10 "100" V 9715 2325 20  0001 C CNN "Supplier Price Break"
	1    9375 2425
	1    0    0    -1  
$EndComp
Text Label 9300 2650 2    60   ~ 0
DOGND
$Comp
L GND #PWR?
U 1 1 59487BCE
P 9375 2725
F 0 "#PWR?" H 9375 2475 50  0001 C CNN
F 1 "GND" H 9380 2552 50  0000 C CNN
F 2 "" H 9375 2725 60  0000 C CNN
F 3 "" H 9375 2725 60  0000 C CNN
	1    9375 2725
	1    0    0    -1  
$EndComp
Text Label 8375 1975 2    60   ~ 0
DGND
Text Label 10150 1650 2    60   ~ 0
AGND
$Comp
L 100NF_X7R_1005M C?
U 1 1 59488533
P 10125 1300
F 0 "C?" H 10203 1235 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 10203 1155 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10240 1200 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10265 1200 20  0001 C CNN
F 4 "TDK" V 10315 1200 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10340 1200 20  0001 C CNN "manf#"
F 6 "Element14" V 10365 1200 20  0001 C CNN "Supplier"
F 7 "2210822" V 10390 1200 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10415 1200 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10440 1200 20  0001 C CNN "Supplier Price"
F 10 "100" V 10465 1200 20  0001 C CNN "Supplier Price Break"
	1    10125 1300
	1    0    0    -1  
$EndComp
Text Notes 8150 1825 0    60   ~ 0
4.7uF 0603
Text Notes 7775 700  0    60   ~ 0
AGND and DGND should be connected outside sensor area grounding
Text Notes 7775 925  0    60   ~ 0
If DOVDD is same as AVDD, share reg and use hardware RC to separate.\nOtherwise use 3 regs...
$EndSCHEMATC
