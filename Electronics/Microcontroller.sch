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
$Descr A3 16535 11693
encoding utf-8
Sheet 2 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 2600 8050 0    79   ~ 16
Programming Header
Text GLabel 3800 8450 2    60   Output ~ 0
SWDIO
Text GLabel 3800 8550 2    60   Output ~ 0
SWDCLK
Text GLabel 3800 8850 2    60   Output ~ 0
NRST
$Comp
L +3.3V #PWR01
U 1 1 5891D7C5
P 2750 8450
F 0 "#PWR01" H 2750 8410 30  0001 C CNN
F 1 "+3.3V" H 2759 8588 30  0000 C CNN
F 2 "" H 2750 8450 60  0000 C CNN
F 3 "" H 2750 8450 60  0000 C CNN
	1    2750 8450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5891D817
P 2750 8600
F 0 "#PWR02" H 2750 8350 50  0001 C CNN
F 1 "GND" V 2755 8472 50  0000 R CNN
F 2 "" H 2750 8600 60  0000 C CNN
F 3 "" H 2750 8600 60  0000 C CNN
	1    2750 8600
	0    1    1    0   
$EndComp
NoConn ~ 3600 8750
Text Notes 13850 975  0    60   ~ 12
Bootloader Boot-strap Circuit
Text GLabel 1500 4600 0    60   Input ~ 0
SWDIO
Text GLabel 1500 4700 0    60   Input ~ 0
SWDCLK
Text GLabel 975  1000 0    60   Input ~ 0
NRST
Wire Wire Line
	1900 3800 1500 3800
Wire Wire Line
	1900 3700 1500 3700
Text GLabel 9500 4200 0    60   BiDi ~ 0
MICROSD_D1
Text GLabel 9500 4300 0    60   BiDi ~ 0
MICROSD_D2
Text GLabel 9500 4400 0    60   BiDi ~ 0
MICROSD_D3
Text GLabel 9500 4500 0    60   Output ~ 0
MICROSD_CK
Text GLabel 9500 4100 0    60   BiDi ~ 0
MICROSD_D0
Text GLabel 9500 5700 0    60   Output ~ 0
MICROSD_CMD
Text GLabel 9500 9300 0    60   Input ~ 0
MICROSD_DETECT
Wire Wire Line
	1075 1050 1075 1000
Connection ~ 1075 1000
$Comp
L GND #PWR03
U 1 1 58C7F2EE
P 1075 1275
F 0 "#PWR03" H 1075 1025 50  0001 C CNN
F 1 "GND" H 1080 1102 50  0000 C CNN
F 2 "" H 1075 1275 60  0000 C CNN
F 3 "" H 1075 1275 60  0000 C CNN
	1    1075 1275
	1    0    0    -1  
$EndComp
Wire Wire Line
	1075 1275 1075 1250
$Comp
L +3.3V #PWR04
U 1 1 58C829C9
P 9250 1200
F 0 "#PWR04" H 9250 1160 30  0001 C CNN
F 1 "+3.3V" H 9259 1338 30  0000 C CNN
F 2 "" H 9250 1200 60  0000 C CNN
F 3 "" H 9250 1200 60  0000 C CNN
	1    9250 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1700 9250 1950
Wire Wire Line
	9250 1950 10750 1950
Wire Wire Line
	9850 1950 9850 1700
Wire Wire Line
	10750 1700 10750 2025
Connection ~ 9850 1950
Wire Wire Line
	10150 1700 10150 1950
Connection ~ 10150 1950
Wire Wire Line
	10450 1700 10450 1950
Connection ~ 10450 1950
Wire Wire Line
	9550 1700 9550 1950
Connection ~ 9550 1950
Connection ~ 10750 1950
Wire Wire Line
	9250 1200 9250 1500
Wire Wire Line
	10750 1250 10750 1500
Connection ~ 9250 1250
Wire Wire Line
	9550 1500 9550 1250
Connection ~ 9550 1250
Wire Wire Line
	9850 1250 9850 1500
Connection ~ 9850 1250
Wire Wire Line
	10150 1250 10150 1500
Connection ~ 10150 1250
Wire Wire Line
	10450 1250 10450 1500
Connection ~ 10450 1250
Text Notes 13650 2850 0    60   ~ 0
BOOT1    BOOT0\n   x         0     Main Mem\n   0         1     System Mem
NoConn ~ 3000 8850
$Comp
L SWD X2
U 1 1 58CD8186
P 3300 8650
F 0 "X2" H 3300 9094 60  0000 C CNN
F 1 "SWD" H 3300 8988 60  0000 C CNB
F 2 "Applidyne_Connector:HARWIN_M50-3600542" H 3350 8250 39  0001 L BNN
F 3 "https://cdn.harwin.com/pdfs/M50-360.pdf" H 3100 8150 39  0001 L BNN
F 4 "HARWIN" H 3100 8250 39  0001 L BNN "manf"
F 5 "M50-3600542" H 3100 8200 39  0001 L BNN "manf#"
F 6 "Digi-Key" H 3100 8100 39  0001 L BNN "Supplier"
F 7 "952-1389-ND" H 3100 8050 39  0001 L BNN "Supplier Part No"
F 8 "http://www.digikey.com.au/product-detail/en/M50-3600542/952-1389-ND/2264370" H 3100 8000 39  0001 L BNN "Supplier URL"
F 9 "1.71" H 3100 7950 39  0001 L BNN "Supplier Price"
F 10 "1" H 3100 7900 39  0001 L BNN "Supplier Price Break "
	1    3300 8650
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C2
U 1 1 59430B8C
P 1075 1050
F 0 "C2" H 1152 985 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 1152 905 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 1190 950 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 1215 950 20  0001 C CNN
F 4 "TDK" V 1265 950 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 1290 950 20  0001 C CNN "manf#"
F 6 "Element14" V 1315 950 20  0001 C CNN "Supplier"
F 7 "2210822" V 1340 950 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 1365 950 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 1390 950 20  0001 C CNN "Supplier Price"
F 10 "100" V 1415 950 20  0001 C CNN "Supplier Price Break"
	1    1075 1050
	-1   0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C6
U 1 1 594317AB
P 9250 1500
F 0 "C6" V 9125 1350 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 9350 1150 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9365 1400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9390 1400 20  0001 C CNN
F 4 "TDK" V 9440 1400 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9465 1400 20  0001 C CNN "manf#"
F 6 "Element14" V 9490 1400 20  0001 C CNN "Supplier"
F 7 "2210822" V 9515 1400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9540 1400 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9565 1400 20  0001 C CNN "Supplier Price"
F 10 "100" V 9590 1400 20  0001 C CNN "Supplier Price Break"
	1    9250 1500
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C7
U 1 1 59431B86
P 9550 1500
F 0 "C7" V 9425 1350 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 9650 1150 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9665 1400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9690 1400 20  0001 C CNN
F 4 "TDK" V 9740 1400 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9765 1400 20  0001 C CNN "manf#"
F 6 "Element14" V 9790 1400 20  0001 C CNN "Supplier"
F 7 "2210822" V 9815 1400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9840 1400 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9865 1400 20  0001 C CNN "Supplier Price"
F 10 "100" V 9890 1400 20  0001 C CNN "Supplier Price Break"
	1    9550 1500
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C8
U 1 1 59431BD4
P 9850 1500
F 0 "C8" V 9725 1350 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 9950 1150 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9965 1400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9990 1400 20  0001 C CNN
F 4 "TDK" V 10040 1400 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10065 1400 20  0001 C CNN "manf#"
F 6 "Element14" V 10090 1400 20  0001 C CNN "Supplier"
F 7 "2210822" V 10115 1400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10140 1400 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10165 1400 20  0001 C CNN "Supplier Price"
F 10 "100" V 10190 1400 20  0001 C CNN "Supplier Price Break"
	1    9850 1500
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C9
U 1 1 59431C26
P 10150 1500
F 0 "C9" V 10025 1350 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 10250 1150 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10265 1400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10290 1400 20  0001 C CNN
F 4 "TDK" V 10340 1400 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10365 1400 20  0001 C CNN "manf#"
F 6 "Element14" V 10390 1400 20  0001 C CNN "Supplier"
F 7 "2210822" V 10415 1400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10440 1400 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10465 1400 20  0001 C CNN "Supplier Price"
F 10 "100" V 10490 1400 20  0001 C CNN "Supplier Price Break"
	1    10150 1500
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C10
U 1 1 59431C72
P 10450 1500
F 0 "C10" V 10325 1350 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 10550 1150 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10565 1400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10590 1400 20  0001 C CNN
F 4 "TDK" V 10640 1400 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10665 1400 20  0001 C CNN "manf#"
F 6 "Element14" V 10690 1400 20  0001 C CNN "Supplier"
F 7 "2210822" V 10715 1400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 10740 1400 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 10765 1400 20  0001 C CNN "Supplier Price"
F 10 "100" V 10790 1400 20  0001 C CNN "Supplier Price Break"
	1    10450 1500
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C11
U 1 1 59431CC4
P 10750 1500
F 0 "C11" V 10625 1350 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 10850 1150 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10865 1400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10890 1400 20  0001 C CNN
F 4 "TDK" V 10940 1400 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10965 1400 20  0001 C CNN "manf#"
F 6 "Element14" V 10990 1400 20  0001 C CNN "Supplier"
F 7 "2210822" V 11015 1400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 11040 1400 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 11065 1400 20  0001 C CNN "Supplier Price"
F 10 "100" V 11090 1400 20  0001 C CNN "Supplier Price Break"
	1    10750 1500
	1    0    0    -1  
$EndComp
Text GLabel 1500 4500 0    60   Output ~ 0
PWDN
Text GLabel 1500 4400 0    60   Output ~ 0
RESET
Text GLabel 1500 4100 0    60   Output ~ 0
XCLK
Text GLabel 1500 3700 0    60   Input ~ 0
HREF
Text GLabel 1500 6200 0    60   Input ~ 0
VSYNC
Text GLabel 1500 3900 0    60   Input ~ 0
PIXCK
Text GLabel 1600 6900 0    60   Input ~ 0
STROBE
Text GLabel 9500 6300 0    60   Output ~ 0
FREX
Text GLabel 1600 7000 0    60   Output ~ 0
EXPSTB
Text GLabel 9500 3900 0    60   Input ~ 0
D0
Text GLabel 9500 4000 0    60   Input ~ 0
D1
Text GLabel 9500 7800 0    60   Input ~ 0
D2
Text GLabel 9500 7900 0    60   Input ~ 0
D3
Text GLabel 9500 8200 0    60   Input ~ 0
D4
Text GLabel 1500 6100 0    60   Input ~ 0
D5
Text GLabel 9500 8300 0    60   Input ~ 0
D6
Text GLabel 1500 6400 0    60   Input ~ 0
D7
Text GLabel 1600 6500 0    60   Input ~ 0
SIO_C
Text GLabel 1600 6600 0    60   BiDi ~ 0
SIO_D
Text Notes 550  6600 0    60   ~ 0
SSCB Interface
$Comp
L LED_GREEN_1608M D1
U 1 1 5948E009
P 4650 9100
F 0 "D1" V 4696 8992 50  0000 R CNN
F 1 "LED_GREEN_1608M" V 4605 8992 50  0000 R CNN
F 2 "Applidyne_LED:LEDC1608X80L40L" H 4550 9100 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1720200.pdf" H 4650 8890 50  0001 C CNN
F 4 "DIALIGHT" H 4650 8680 60  0001 C CNN "manf"
F 5 "5988070107F" H 4650 8590 60  0001 C CNN "manf#"
F 6 "Element 14" H 4650 8490 60  0001 C CNN "Supplier"
F 7 "1465991" H 4650 8390 60  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/dialight/5988070107f/led-0603-green-20mcd-566nm/dp/1465991" H 4660 8310 60  0001 C CNN "Supplier URL"
F 9 "0.4" H 4650 8210 60  0001 C CNN "Supplier Price"
F 10 "10" H 4650 8110 60  0001 C CNN "Supplier Price Break"
	1    4650 9100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 5948E41A
P 5650 9450
F 0 "#PWR05" H 5650 9200 50  0001 C CNN
F 1 "GND" H 5655 9277 50  0000 C CNN
F 2 "" H 5650 9450 60  0000 C CNN
F 3 "" H 5650 9450 60  0000 C CNN
	1    5650 9450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5948E458
P 4650 9450
F 0 "#PWR06" H 4650 9200 50  0001 C CNN
F 1 "GND" H 4655 9277 50  0000 C CNN
F 2 "" H 4650 9450 60  0000 C CNN
F 3 "" H 4650 9450 60  0000 C CNN
	1    4650 9450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 9450 4650 9300
Wire Wire Line
	5650 9300 5650 9450
$Comp
L 1K_1005M R1
U 1 1 5948E833
P 4650 8525
F 0 "R1" H 4723 8410 50  0000 L CNN
F 1 "1K_1005M" H 4723 8330 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 4760 8375 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 4785 8375 20  0001 C CNN
F 4 "VISHAY" V 4835 8375 20  0001 C CNN "manf"
F 5 "CRCW04021K00FKED" V 4860 8375 20  0001 C CNN "manf#"
F 6 "Element14" V 4885 8375 20  0001 C CNN "Supplier"
F 7 "1469669" V 4910 8375 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210k0fked/res-thick-film-10k-1-0-063w-0402/dp/1469669" V 4935 8375 20  0001 C CNN "Supplier URL"
F 9 "0.09" V 4960 8375 20  0001 C CNN "Supplier Price"
F 10 "10" V 4985 8375 20  0001 C CNN "Supplier Price Break"
	1    4650 8525
	1    0    0    -1  
$EndComp
$Comp
L 1K_1005M R2
U 1 1 5948E8C5
P 5650 8525
F 0 "R2" H 5723 8410 50  0000 L CNN
F 1 "1K_1005M" H 5723 8330 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 5760 8375 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 5785 8375 20  0001 C CNN
F 4 "VISHAY" V 5835 8375 20  0001 C CNN "manf"
F 5 "CRCW04021K00FKED" V 5860 8375 20  0001 C CNN "manf#"
F 6 "Element14" V 5885 8375 20  0001 C CNN "Supplier"
F 7 "1469669" V 5910 8375 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210k0fked/res-thick-film-10k-1-0-063w-0402/dp/1469669" V 5935 8375 20  0001 C CNN "Supplier URL"
F 9 "0.09" V 5960 8375 20  0001 C CNN "Supplier Price"
F 10 "10" V 5985 8375 20  0001 C CNN "Supplier Price Break"
	1    5650 8525
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 8825 5650 8900
Wire Wire Line
	4650 8825 4650 8900
Wire Wire Line
	4650 8525 4650 8400
Wire Wire Line
	5650 8525 5650 8400
Text GLabel 4650 8400 1    60   Input ~ 0
STATUS0
Text GLabel 5650 8400 1    60   Input ~ 0
STATUS1
Text GLabel 1500 5500 0    60   Output ~ 0
STATUS0
Text GLabel 1500 5600 0    60   Output ~ 0
STATUS1
Text Notes 4900 7800 0    79   ~ 16
Status Leds
Text GLabel 9500 8500 0    60   Output ~ 0
IRCUT_A
Text GLabel 9500 8900 0    60   Output ~ 0
IRCUT_B
Text GLabel 1500 3800 0    60   Output ~ 0
FLASH_DAC
Text GLabel 9500 3300 0    60   Input ~ 0
AMBIENT_LIGHT
Text GLabel 1500 4800 0    60   Input ~ 0
PWR_EN
$Comp
L STM32F429VET6 U1
U 2 1 594F36A3
P 4550 4000
F 0 "U1" H 4675 5075 60  0000 L CNN
F 1 "STM32F429VET6" H 4375 4975 60  0000 L CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25L" H 4550 2975 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2283387.pdf" H 4550 2950 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 4550 2900 20  0001 C CNN "manf"
F 5 "STM32F429VET6" H 4550 2875 20  0001 C CNN "manf#"
F 6 "Element14" H 4550 2850 20  0001 C CNN "Supplier"
F 7 "2469586" H 4550 2825 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 4550 2800 20  0001 C CNN "Supplier URL"
F 9 "14.22" H 4550 2775 20  0001 C CNN "Supplier Price"
F 10 "10" H 4550 2750 20  0001 C CNN "Supplier Price Break"
	2    4550 4000
	1    0    0    -1  
$EndComp
$Comp
L STM32F429VET6 U1
U 3 1 594F3871
P 4550 6200
F 0 "U1" H 4775 7300 60  0000 C CNN
F 1 "STM32F429VET6" H 4750 7175 60  0000 C CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25L" H 4550 5175 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2283387.pdf" H 4550 5150 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 4550 5100 20  0001 C CNN "manf"
F 5 "STM32F429VET6" H 4550 5075 20  0001 C CNN "manf#"
F 6 "Element14" H 4550 5050 20  0001 C CNN "Supplier"
F 7 "2469586" H 4550 5025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 4550 5000 20  0001 C CNN "Supplier URL"
F 9 "14.22" H 4550 4975 20  0001 C CNN "Supplier Price"
F 10 "10" H 4550 4950 20  0001 C CNN "Supplier Price Break"
	3    4550 6200
	1    0    0    -1  
$EndComp
$Comp
L STM32F429VET6 U1
U 4 1 594F38D1
P 12650 4000
F 0 "U1" H 12750 5075 60  0000 L CNN
F 1 "STM32F429VET6" H 12500 4975 60  0000 L CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25L" H 12650 2975 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2283387.pdf" H 12650 2950 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 12650 2900 20  0001 C CNN "manf"
F 5 "STM32F429VET6" H 12650 2875 20  0001 C CNN "manf#"
F 6 "Element14" H 12650 2850 20  0001 C CNN "Supplier"
F 7 "2469586" H 12650 2825 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 12650 2800 20  0001 C CNN "Supplier URL"
F 9 "14.22" H 12650 2775 20  0001 C CNN "Supplier Price"
F 10 "10" H 12650 2750 20  0001 C CNN "Supplier Price Break"
	4    12650 4000
	1    0    0    -1  
$EndComp
$Comp
L STM32F429VET6 U1
U 5 1 594F3927
P 12650 6200
F 0 "U1" H 12775 7300 60  0000 L CNN
F 1 "STM32F429VET6" H 12500 7175 60  0000 L CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25L" H 12650 5175 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2283387.pdf" H 12650 5150 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 12650 5100 20  0001 C CNN "manf"
F 5 "STM32F429VET6" H 12650 5075 20  0001 C CNN "manf#"
F 6 "Element14" H 12650 5050 20  0001 C CNN "Supplier"
F 7 "2469586" H 12650 5025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 12650 5000 20  0001 C CNN "Supplier URL"
F 9 "14.22" H 12650 4975 20  0001 C CNN "Supplier Price"
F 10 "10" H 12650 4950 20  0001 C CNN "Supplier Price Break"
	5    12650 6200
	1    0    0    -1  
$EndComp
$Comp
L STM32F429VET6 U1
U 6 1 594F3B43
P 12650 8500
F 0 "U1" H 12775 9625 60  0000 L CNN
F 1 "STM32F429VET6" H 12500 9500 60  0000 L CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25L" H 12650 7475 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2283387.pdf" H 12650 7450 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 12650 7400 20  0001 C CNN "manf"
F 5 "STM32F429VET6" H 12650 7375 20  0001 C CNN "manf#"
F 6 "Element14" H 12650 7350 20  0001 C CNN "Supplier"
F 7 "2469586" H 12650 7325 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 12650 7300 20  0001 C CNN "Supplier URL"
F 9 "14.22" H 12650 7275 20  0001 C CNN "Supplier Price"
F 10 "10" H 12650 7250 20  0001 C CNN "Supplier Price Break"
	6    12650 8500
	1    0    0    -1  
$EndComp
$Comp
L STM32F429VET6 U1
U 1 1 594F34EA
P 4500 1650
F 0 "U1" H 4700 2737 60  0000 C CNN
F 1 "STM32F429VET6" H 4700 2631 60  0000 C CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25L" H 4500 625 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2283387.pdf" H 4500 600 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 4500 550 20  0001 C CNN "manf"
F 5 "STM32F429VET6" H 4500 525 20  0001 C CNN "manf#"
F 6 "Element14" H 4500 500 20  0001 C CNN "Supplier"
F 7 "2469586" H 4500 475 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 4500 450 20  0001 C CNN "Supplier URL"
F 9 "14.22" H 4500 425 20  0001 C CNN "Supplier Price"
F 10 "10" H 4500 400 20  0001 C CNN "Supplier Price Break"
	1    4500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 2050 1800 2050
Wire Wire Line
	1800 2050 1800 1750
Wire Wire Line
	1000 1550 1800 1550
Wire Wire Line
	1800 1550 1800 1650
Wire Wire Line
	1800 1650 1850 1650
Wire Wire Line
	1800 1750 1850 1750
Wire Wire Line
	700  1800 600  1800
Wire Wire Line
	600  1800 600  2000
$Comp
L GND #PWR07
U 1 1 594F6A2C
P 600 2000
F 0 "#PWR07" H 600 1750 50  0001 C CNN
F 1 "GND" H 605 1827 50  0000 C CNN
F 2 "" H 600 2000 60  0000 C CNN
F 3 "" H 600 2000 60  0000 C CNN
	1    600  2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1450 1250 1450
Wire Wire Line
	1250 1450 1250 1000
Wire Wire Line
	1250 1000 975  1000
Wire Wire Line
	7800 1450 7550 1450
Wire Wire Line
	7800 850  7800 1450
Wire Wire Line
	7800 950  7550 950 
Wire Wire Line
	7550 2050 7800 2050
Wire Wire Line
	7800 2050 7800 2450
Wire Wire Line
	7800 2350 7550 2350
Wire Wire Line
	7550 2250 7800 2250
Connection ~ 7800 2250
Wire Wire Line
	7550 2150 7800 2150
Connection ~ 7800 2150
Wire Wire Line
	7550 1350 7800 1350
Connection ~ 7800 1350
Wire Wire Line
	7550 1250 7800 1250
Connection ~ 7800 1250
Wire Wire Line
	7550 1150 7800 1150
Connection ~ 7800 1150
Wire Wire Line
	7550 1050 7800 1050
Connection ~ 7800 1050
$Comp
L +3.3V #PWR08
U 1 1 594FE0A0
P 1700 1150
F 0 "#PWR08" H 1700 1110 30  0001 C CNN
F 1 "+3.3V" H 1709 1288 30  0000 C CNN
F 2 "" H 1700 1150 60  0000 C CNN
F 3 "" H 1700 1150 60  0000 C CNN
	1    1700 1150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1700 1150 1850 1150
Wire Wire Line
	1850 1350 1550 1350
$Comp
L 100NF_X7R_1005M C13
U 1 1 594FEA0C
P 12325 1650
F 0 "C13" H 12402 1585 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 12402 1505 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 12440 1550 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 12465 1550 20  0001 C CNN
F 4 "TDK" V 12515 1550 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 12540 1550 20  0001 C CNN "manf#"
F 6 "Element14" V 12565 1550 20  0001 C CNN "Supplier"
F 7 "2210822" V 12590 1550 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 12615 1550 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 12640 1550 20  0001 C CNN "Supplier Price"
F 10 "100" V 12665 1550 20  0001 C CNN "Supplier Price Break"
	1    12325 1650
	1    0    0    -1  
$EndComp
$Comp
L 1UF_X5R_1005M C3
U 1 1 594FF1C2
P 1550 2350
F 0 "C3" H 1628 2285 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 1628 2205 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 1665 2250 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 1690 2250 20  0001 C CNN
F 4 "TDK" V 1740 2250 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 1765 2250 20  0001 C CNN "manf#"
F 6 "Element14" V 1790 2250 20  0001 C CNN "Supplier"
F 7 "2346885" V 1815 2250 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 1840 2250 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 1865 2250 20  0001 C CNN "Supplier Price"
F 10 "100" V 1890 2250 20  0001 C CNN "Supplier Price Break"
	1    1550 2350
	1    0    0    -1  
$EndComp
$Comp
L 1UF_X5R_1005M C1
U 1 1 594FF27C
P 950 2350
F 0 "C1" H 1028 2285 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 1028 2205 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 1065 2250 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 1090 2250 20  0001 C CNN
F 4 "TDK" V 1140 2250 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 1165 2250 20  0001 C CNN "manf#"
F 6 "Element14" V 1190 2250 20  0001 C CNN "Supplier"
F 7 "2346885" V 1215 2250 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 1240 2250 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 1265 2250 20  0001 C CNN "Supplier Price"
F 10 "100" V 1290 2250 20  0001 C CNN "Supplier Price Break"
	1    950  2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2350 950  2150
Wire Wire Line
	950  2150 1850 2150
Wire Wire Line
	1850 2250 1550 2250
Wire Wire Line
	1550 2250 1550 2350
Wire Wire Line
	1550 2550 1550 2650
Wire Wire Line
	950  2550 950  2650
$Comp
L GND #PWR09
U 1 1 594FF524
P 950 2650
F 0 "#PWR09" H 950 2400 50  0001 C CNN
F 1 "GND" H 955 2477 50  0000 C CNN
F 2 "" H 950 2650 60  0000 C CNN
F 3 "" H 950 2650 60  0000 C CNN
	1    950  2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 594FF56E
P 1550 2650
F 0 "#PWR010" H 1550 2400 50  0001 C CNN
F 1 "GND" H 1555 2477 50  0000 C CNN
F 2 "" H 1550 2650 60  0000 C CNN
F 3 "" H 1550 2650 60  0000 C CNN
	1    1550 2650
	1    0    0    -1  
$EndComp
$Comp
L 1UF_X5R_1005M C4
U 1 1 594FFF9E
P 7800 1650
F 0 "C4" H 7878 1585 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 7878 1505 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 7915 1550 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 7940 1550 20  0001 C CNN
F 4 "TDK" V 7990 1550 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 8015 1550 20  0001 C CNN "manf#"
F 6 "Element14" V 8040 1550 20  0001 C CNN "Supplier"
F 7 "2346885" V 8065 1550 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 8090 1550 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 8115 1550 20  0001 C CNN "Supplier Price"
F 10 "100" V 8140 1550 20  0001 C CNN "Supplier Price Break"
	1    7800 1650
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C5
U 1 1 59500284
P 8400 1650
F 0 "C5" H 8477 1585 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 8477 1505 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8515 1550 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 8540 1550 20  0001 C CNN
F 4 "TDK" V 8590 1550 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 8615 1550 20  0001 C CNN "manf#"
F 6 "Element14" V 8640 1550 20  0001 C CNN "Supplier"
F 7 "2210822" V 8665 1550 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 8690 1550 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 8715 1550 20  0001 C CNN "Supplier Price"
F 10 "100" V 8740 1550 20  0001 C CNN "Supplier Price Break"
	1    8400 1650
	1    0    0    -1  
$EndComp
$Comp
L 1UF_X5R_1005M C12
U 1 1 59500942
P 11675 1650
F 0 "C12" H 11753 1585 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 11753 1505 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 11790 1550 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 11815 1550 20  0001 C CNN
F 4 "TDK" V 11865 1550 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 11890 1550 20  0001 C CNN "manf#"
F 6 "Element14" V 11915 1550 20  0001 C CNN "Supplier"
F 7 "2346885" V 11940 1550 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 11965 1550 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 11990 1550 20  0001 C CNN "Supplier Price"
F 10 "100" V 12015 1550 20  0001 C CNN "Supplier Price Break"
	1    11675 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 950  1550 950 
Text Label 1550 950  0    60   ~ 0
VREF
Text Label 12125 1550 0    60   ~ 0
VREF
$Comp
L +3.3V #PWR011
U 1 1 59501137
P 8400 1450
F 0 "#PWR011" H 8400 1410 30  0001 C CNN
F 1 "+3.3V" H 8409 1588 30  0000 C CNN
F 2 "" H 8400 1450 60  0000 C CNN
F 3 "" H 8400 1450 60  0000 C CNN
	1    8400 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5950118F
P 8400 2050
F 0 "#PWR012" H 8400 1800 50  0001 C CNN
F 1 "GND" H 8405 1877 50  0000 C CNN
F 2 "" H 8400 2050 60  0000 C CNN
F 3 "" H 8400 2050 60  0000 C CNN
	1    8400 2050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR013
U 1 1 595011D7
P 7800 850
F 0 "#PWR013" H 7800 810 30  0001 C CNN
F 1 "+3.3V" H 7809 988 30  0000 C CNN
F 2 "" H 7800 850 60  0000 C CNN
F 3 "" H 7800 850 60  0000 C CNN
	1    7800 850 
	1    0    0    -1  
$EndComp
Connection ~ 7800 950 
Connection ~ 7800 2350
$Comp
L GND #PWR014
U 1 1 595014B5
P 7800 2450
F 0 "#PWR014" H 7800 2200 50  0001 C CNN
F 1 "GND" H 7805 2277 50  0000 C CNN
F 2 "" H 7800 2450 60  0000 C CNN
F 3 "" H 7800 2450 60  0000 C CNN
	1    7800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1650 7650 1650
Wire Wire Line
	7650 1650 7650 1550
Wire Wire Line
	7650 1550 8400 1550
Wire Wire Line
	8400 1450 8400 1650
Wire Wire Line
	7550 1850 7650 1850
Wire Wire Line
	7650 1850 7650 1950
Wire Wire Line
	7650 1950 8400 1950
Wire Wire Line
	8400 1850 8400 2050
Connection ~ 8400 1550
Connection ~ 8400 1950
Wire Wire Line
	7800 1650 7800 1550
Connection ~ 7800 1550
Wire Wire Line
	7800 1850 7800 1950
Connection ~ 7800 1950
Text Notes 9525 950  0    60   ~ 12
VDD Bypass Capacitors
Text Notes 11675 975  0    60   ~ 12
VREF Bypass Capacitors
$Comp
L +3.3V #PWR015
U 1 1 5950200B
P 11675 1450
F 0 "#PWR015" H 11675 1410 30  0001 C CNN
F 1 "+3.3V" H 11684 1588 30  0000 C CNN
F 2 "" H 11675 1450 60  0000 C CNN
F 3 "" H 11675 1450 60  0000 C CNN
	1    11675 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	11675 1450 11675 1650
Wire Wire Line
	11675 1850 11675 2050
$Comp
L GND #PWR016
U 1 1 59502320
P 11675 2050
F 0 "#PWR016" H 11675 1800 50  0001 C CNN
F 1 "GND" H 11680 1877 50  0000 C CNN
F 2 "" H 11675 2050 60  0000 C CNN
F 3 "" H 11675 2050 60  0000 C CNN
	1    11675 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12325 1650 12325 1550
Wire Wire Line
	12325 1550 11675 1550
Connection ~ 11675 1550
Wire Wire Line
	12325 1850 12325 1950
Wire Wire Line
	12325 1950 11675 1950
Connection ~ 11675 1950
Text Label 1550 1350 0    60   ~ 0
BOOT0
Text Label 13200 1850 0    60   ~ 0
BOOT0
Wire Wire Line
	13200 1850 14650 1850
Wire Wire Line
	1900 5700 1550 5700
Text Label 1550 5700 0    60   ~ 0
BOOT1
Text Label 13200 2050 0    60   ~ 0
BOOT1
Wire Wire Line
	13200 2050 13650 2050
$Comp
L GND #PWR017
U 1 1 5950530F
P 13650 2250
F 0 "#PWR017" H 13650 2000 50  0001 C CNN
F 1 "GND" H 13655 2077 50  0000 C CNN
F 2 "" H 13650 2250 60  0000 C CNN
F 3 "" H 13650 2250 60  0000 C CNN
	1    13650 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	13650 2050 13650 2250
Text Notes 13325 1425 0    60   ~ 0
To update firmware, send request to micro.\nMicro will latch BOOT0 high, and then nvReset.\nWill boot into ST Bootloader and accept update \nover USART1. Once complete, power cycle the camera.
$Comp
L GND #PWR018
U 1 1 59505CC0
P 10750 2025
F 0 "#PWR018" H 10750 1775 50  0001 C CNN
F 1 "GND" H 10755 1852 50  0000 C CNN
F 2 "" H 10750 2025 60  0000 C CNN
F 3 "" H 10750 2025 60  0000 C CNN
	1    10750 2025
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1250 10750 1250
Wire Wire Line
	9700 9200 10000 9200
Wire Wire Line
	9700 8900 9700 9200
Wire Wire Line
	9500 8900 10000 8900
Wire Wire Line
	10000 9000 9700 9000
Connection ~ 9700 9000
Wire Wire Line
	10000 9100 9700 9100
Connection ~ 9700 9100
Connection ~ 9700 8900
Wire Wire Line
	9700 8800 10000 8800
Wire Wire Line
	9700 8500 9700 8800
Wire Wire Line
	9500 8500 10000 8500
Wire Wire Line
	10000 8600 9700 8600
Connection ~ 9700 8600
Wire Wire Line
	10000 8700 9700 8700
Connection ~ 9700 8700
Connection ~ 9700 8500
Text GLabel 3800 8650 2    60   Input ~ 0
SWO
Wire Wire Line
	3800 8850 3600 8850
Wire Wire Line
	3600 8650 3800 8650
Wire Wire Line
	3800 8550 3600 8550
Wire Wire Line
	3600 8450 3800 8450
Wire Wire Line
	3000 8550 2850 8550
Wire Wire Line
	2850 8550 2850 8650
Wire Wire Line
	2850 8650 3000 8650
Wire Wire Line
	2850 8600 2750 8600
Connection ~ 2850 8600
Wire Wire Line
	2750 8450 3000 8450
Wire Wire Line
	1500 4700 1900 4700
Wire Wire Line
	1900 4600 1500 4600
Text GLabel 1500 5800 0    60   Output ~ 0
SWO
Wire Wire Line
	1500 5800 1900 5800
Wire Wire Line
	1600 6600 1900 6600
Wire Wire Line
	1900 6500 1600 6500
Text GLabel 1500 4200 0    60   Output ~ 0
UART_TX
Text GLabel 1500 4300 0    60   Input ~ 0
UART_RX
Wire Wire Line
	1500 4300 1900 4300
Wire Wire Line
	1900 4200 1500 4200
Wire Wire Line
	1500 4400 1900 4400
Wire Wire Line
	1500 3900 1900 3900
Wire Wire Line
	1500 6400 1900 6400
Wire Wire Line
	1900 6300 1500 6300
Wire Wire Line
	1500 6200 1900 6200
Wire Wire Line
	1900 6100 1500 6100
Wire Wire Line
	9500 7800 10000 7800
Wire Wire Line
	10000 7900 9500 7900
Wire Wire Line
	9500 8200 10000 8200
Wire Wire Line
	9500 4000 10000 4000
Wire Wire Line
	10000 3900 9500 3900
Wire Wire Line
	9500 4100 10000 4100
Wire Wire Line
	10000 4200 9500 4200
Wire Wire Line
	9500 4300 10000 4300
Wire Wire Line
	10000 4400 9500 4400
Wire Wire Line
	9500 4500 10000 4500
Wire Wire Line
	9500 5700 10000 5700
Text Notes 7800 9850 0    60   ~ 0
Manual pg136 discusses pin current.\nWe can get +-8mA per pin at VDD level.\nCan get +-20mA with relaxed output voltage (VDD-1.3).
Text Notes 7800 8900 0    60   ~ 0
Use parallel IO to make\nH-Bridge for IR-Filter.\nUse direct port operations to ensure\nsafe switching.
Wire Wire Line
	9500 6300 10000 6300
Wire Wire Line
	9500 3300 10000 3300
Wire Wire Line
	1500 4100 1900 4100
$Comp
L LED_RED_1608M D2
U 1 1 594E9581
P 5650 9100
F 0 "D2" V 5696 8992 50  0000 R CNN
F 1 "LED_RED_1608M" V 5605 8992 50  0000 R CNN
F 2 "Applidyne_LED:LEDC1608X80L40L" H 5650 9300 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1720200.pdf" H 5650 8890 50  0001 C CNN
F 4 "DIALIGHT" H 5650 8680 60  0001 C CNN "manf"
F 5 "5988010107F" H 5650 8590 60  0001 C CNN "manf#"
F 6 "Element 14" H 5650 8490 60  0001 C CNN "Supplier"
F 7 "1465988" H 5650 8390 60  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/dialight/5988010107f/led-0603-red-40mcd-635nm/dp/1465988" H 5660 8310 60  0001 C CNN "Supplier URL"
F 9 "0.18" H 5650 8210 60  0001 C CNN "Supplier Price"
F 10 "10" H 5650 8110 60  0001 C CNN "Supplier Price Break"
	1    5650 9100
	0    -1   -1   0   
$EndComp
Text Notes 3200 10700 0    60   ~ 0
Use internal temp sensor for logging environmental factors.
Text Notes 4500 10400 0    79   ~ 16
Notes
Wire Wire Line
	9500 8300 10000 8300
Text GLabel 1500 6300 0    60   Output ~ 0
REBOOT_LATCH
Text GLabel 13900 1650 0    60   Input ~ 0
REBOOT_LATCH
Wire Wire Line
	13900 1650 14100 1650
Wire Wire Line
	14100 1650 14100 1850
Connection ~ 14100 1850
Wire Wire Line
	14300 1850 14300 1950
Connection ~ 14300 1850
Wire Wire Line
	14300 2150 14300 2250
$Comp
L GND #PWR019
U 1 1 5950F7A9
P 14300 2250
F 0 "#PWR019" H 14300 2000 50  0001 C CNN
F 1 "GND" H 14305 2077 50  0000 C CNN
F 2 "" H 14300 2250 60  0000 C CNN
F 3 "" H 14300 2250 60  0000 C CNN
	1    14300 2250
	1    0    0    -1  
$EndComp
$Comp
L 510K_1005M R13
U 1 1 5950FF05
P 14650 1900
F 0 "R13" H 14723 1785 50  0000 L CNN
F 1 "510K_1005M" H 14723 1705 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 14760 1750 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1911175.pdf" V 14785 1750 20  0001 C CNN
F 4 "PANASONIC" V 14835 1750 20  0001 C CNN "manf"
F 5 "ERJ2RKF5103X" V 14860 1750 20  0001 C CNN "manf#"
F 6 "Element14" V 14885 1750 20  0001 C CNN "Supplier"
F 7 "2302919" V 14910 1750 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/erj2rkf5103x/res-thick-film-510k-1-0-1w-0402/dp/2302919" V 14935 1750 20  0001 C CNN "Supplier URL"
F 9 "0.011" V 14960 1750 20  0001 C CNN "Supplier Price"
F 10 "50" V 14985 1750 20  0001 C CNN "Supplier Price Break"
	1    14650 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	14650 2200 14650 2250
$Comp
L GND #PWR020
U 1 1 595100F1
P 14650 2250
F 0 "#PWR020" H 14650 2000 50  0001 C CNN
F 1 "GND" H 14655 2077 50  0000 C CNN
F 2 "" H 14650 2250 60  0000 C CNN
F 3 "" H 14650 2250 60  0000 C CNN
	1    14650 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	14650 1850 14650 1900
$Comp
L 1UF_X5R_1005M C28
U 1 1 595105DA
P 14300 1950
F 0 "C28" H 14378 1885 50  0000 L CNN
F 1 "1UF_X5R_1005M" H 14378 1805 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 14415 1850 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2291921.pdf" V 14440 1850 20  0001 C CNN
F 4 "TDK" V 14490 1850 20  0001 C CNN "manf"
F 5 "C1005X5R1V105K050BC" V 14515 1850 20  0001 C CNN "manf#"
F 6 "Element14" V 14540 1850 20  0001 C CNN "Supplier"
F 7 "2346885" V 14565 1850 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/c1005x5r1v105k050bc/cap-mlcc-x5r-1uf-35v-0402/dp/2346885" V 14590 1850 20  0001 C CNN "Supplier URL"
F 9 "0.101" V 14615 1850 20  0001 C CNN "Supplier Price"
F 10 "100" V 14640 1850 20  0001 C CNN "Supplier Price Break"
	1    14300 1950
	-1   0    0    -1  
$EndComp
Text Notes 14150 1750 0    60   ~ 0
510k and 1uF = 0.510 sec RC time
Wire Wire Line
	1500 4500 1900 4500
Wire Wire Line
	1900 4800 1500 4800
Wire Wire Line
	9500 9300 10000 9300
Wire Wire Line
	1600 6700 1900 6700
Wire Wire Line
	1900 6800 1600 6800
Wire Wire Line
	1600 6900 1900 6900
Wire Wire Line
	1900 7000 1600 7000
$Comp
L CSTCE16M0V53A X1
U 1 1 5951CCB6
P 1000 1800
F 0 "X1" V 954 1927 50  0000 L CNN
F 1 "CSTCE16M0V53A" V 1045 1927 50  0000 L CNN
F 2 "Applidyne_Crystal:OSCSC-CSCTE-CERALOCK" H 1000 1250 60  0001 C CNN
F 3 "http://au.rs-online.com/webdocs/0ef2/0900766b80ef2ca9.pdf" H 1000 1380 60  0001 C CNN
F 4 "Murata" H 1000 1130 60  0001 C CNN "manf"
F 5 "CSTCE16M0V53A-R0" H 1000 1010 60  0001 C CNN "manf#"
F 6 "RS Online" H 1000 900 60  0001 C CNN "Supplier"
F 7 "721-4818" H 1000 790 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/ceramic-resonators/7214818/" H 1000 690 60  0001 C CNN "Supplier URL"
F 9 "0.696" H 1000 580 60  0001 C CNN "Supplier Price"
F 10 "5" H 1000 460 60  0001 C CNN "Supplier Price Break"
	1    1000 1800
	0    1    1    0   
$EndComp
$Comp
L B3U-1000P_SPST-NO_SMD SW1
U 1 1 5961F9F2
P 3300 9850
F 0 "SW1" H 3325 10092 50  0000 C CNN
F 1 "B3U-1000P_SPST-NO_SMD" H 3325 10001 50  0000 C CNN
F 2 "Applidyne_Switch:B3U-1000P" H 3300 9610 20  0001 C CNN
F 3 "http://www.farnell.com/cad/1520836.pdf" H 3300 9585 20  0001 C CNN
F 4 "OMRON" H 3300 9535 20  0001 C CNN "manf"
F 5 "B3U-1000P" H 3300 9510 20  0001 C CNN "manf#"
F 6 "Element 14" H 3300 9485 20  0001 C CNN "Supplier"
F 7 "1333652" H 3300 9460 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/omron-electronic-components/b3u-1000p/switch-spst-no-0-05a-12v-smd/dp/1333652" H 3300 9435 20  0001 C CNN "Supplier URL"
F 9 "0.546" H 3300 9410 20  0001 C CNN "Supplier Price"
F 10 "5" H 3300 9385 20  0001 C CNN "Supplier Price Break"
	1    3300 9850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 5600 1500 5600
Wire Wire Line
	1500 5500 1900 5500
$EndSCHEMATC
