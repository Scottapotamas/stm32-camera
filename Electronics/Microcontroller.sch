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
Text Notes 3275 8575 0    79   ~ 16
Programming Header
Wire Wire Line
	4150 8975 4225 8975
Wire Wire Line
	4150 9075 4225 9075
Wire Wire Line
	4150 9375 4225 9375
Wire Wire Line
	3250 9175 3550 9175
Wire Wire Line
	3250 9075 3550 9075
Wire Wire Line
	3250 8975 3550 8975
Text GLabel 4225 8975 2    60   Output ~ 0
SWDIO
Text GLabel 4225 9075 2    60   Output ~ 0
SWDCLK
Text GLabel 4225 9375 2    60   Output ~ 0
NRST
$Comp
L +3.3V #PWR?
U 1 1 5891D7C5
P 3250 8975
F 0 "#PWR?" H 3250 8935 30  0001 C CNN
F 1 "+3.3V" H 3259 9113 30  0000 C CNN
F 2 "" H 3250 8975 60  0000 C CNN
F 3 "" H 3250 8975 60  0000 C CNN
	1    3250 8975
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5891D817
P 3150 9125
F 0 "#PWR?" H 3150 8875 50  0001 C CNN
F 1 "GND" V 3155 8997 50  0000 R CNN
F 2 "" H 3150 9125 60  0000 C CNN
F 3 "" H 3150 9125 60  0000 C CNN
	1    3150 9125
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 9075 3250 9175
Wire Wire Line
	3250 9125 3150 9125
Connection ~ 3250 9125
NoConn ~ 4150 9275
Text Notes 1575 1650 0    60   ~ 0
BOOT0 Jumper
$Comp
L STM32F407VGT6 U?
U 1 1 58C74B6D
P 8250 5050
F 0 "U?" H 8250 5200 60  0000 C CNN
F 1 "STM32F407VGT6" H 8250 5075 60  0000 C CNN
F 2 "Applidyne_QFP:QFP50P1600X1600X160-100L25N" H 8250 4900 20  0001 C CNN
F 3 "http://docs-asia.electrocomponents.com/webdocs/13e2/0900766b813e2847.pdf" H 8250 4875 20  0001 C CNN
F 4 "ST MICROELECTRONICS" H 8250 4825 20  0001 C CNN "manf"
F 5 "STM32F407VGT6" H 8250 4800 20  0001 C CNN "manf#"
F 6 "RS Online" H 8250 4775 20  0001 C CNN "Supplier"
F 7 "746-8226" H 8250 4750 20  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/microcontrollers/7468226/" H 8250 4725 20  0001 C CNN "Supplier URL"
F 9 "19.2" H 8250 4700 20  0001 C CNN "Supplier Price"
F 10 "1" H 8250 4675 20  0001 C CNN "Supplier Price Break"
	1    8250 5050
	1    0    0    -1  
$EndComp
$Comp
L CSTCE8M00G55Z X?
U 1 1 58C74CCA
P 2700 3200
F 0 "X?" V 2654 3327 50  0000 L CNN
F 1 "CSTCE8M00G55Z" V 2745 3327 50  0000 L CNN
F 2 "Applidyne_Crystal:OSCSC-CSCTE-CERALOCK" H 2700 3200 60  0001 C CNN
F 3 "http://docs-asia.electrocomponents.com/webdocs/0655/0900766b80655dc4.pdf" H 2700 2780 60  0001 C CNN
F 4 "Murata" H 2700 2530 60  0001 C CNN "manf"
F 5 "CSTCE8M00G55Z-R0" H 2700 2410 60  0001 C CNN "manf#"
F 6 "RS Online" H 2700 2300 60  0001 C CNN "Supplier"
F 7 "792-6533" H 2700 2190 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/ceramic-resonators/7926533/" H 2700 2090 60  0001 C CNN "Supplier URL"
F 9 "0.43" H 2700 1980 60  0001 C CNN "Supplier Price"
F 10 "5" H 2700 1860 60  0001 C CNN "Supplier Price Break"
	1    2700 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 2900 2700 2900
Wire Wire Line
	2700 2900 2700 2950
Wire Wire Line
	3250 3500 2700 3500
Wire Wire Line
	2700 3500 2700 3450
Wire Wire Line
	2400 3200 2200 3200
Wire Wire Line
	2200 3200 2200 3500
$Comp
L GND #PWR?
U 1 1 58C74E02
P 2200 3500
F 0 "#PWR?" H 2200 3250 50  0001 C CNN
F 1 "GND" H 2205 3327 50  0000 C CNN
F 2 "" H 2200 3500 60  0000 C CNN
F 3 "" H 2200 3500 60  0000 C CNN
	1    2200 3500
	1    0    0    -1  
$EndComp
Text GLabel 2900 5200 0    60   Input ~ 0
USB_VBUS
Text GLabel 2900 5500 0    60   BiDi ~ 0
USB_D+
Text GLabel 2900 5400 0    60   BiDi ~ 0
USB_D-
Text GLabel 2900 5300 0    60   UnSpc ~ 0
USB_OTG
Text GLabel 2900 5600 0    60   Input ~ 0
SWDIO
Text GLabel 2900 5700 0    60   Input ~ 0
SWDCLK
Text GLabel 1825 2700 0    60   Input ~ 0
NRST
Wire Wire Line
	3250 5700 2900 5700
Wire Wire Line
	3250 5600 2900 5600
Wire Wire Line
	3250 5500 2900 5500
Wire Wire Line
	3250 5400 2900 5400
Wire Wire Line
	3250 5300 2900 5300
Wire Wire Line
	3250 5200 2900 5200
Wire Wire Line
	3250 5100 2900 5100
Wire Wire Line
	3250 5000 2900 5000
Wire Wire Line
	3250 4900 2900 4900
Wire Wire Line
	3250 4800 2900 4800
Wire Wire Line
	3250 4700 2900 4700
Wire Wire Line
	3250 4600 2900 4600
Wire Wire Line
	3250 4500 2900 4500
Wire Wire Line
	3250 4400 2900 4400
Wire Wire Line
	3250 4300 2900 4300
Wire Wire Line
	3250 7500 2900 7500
Wire Wire Line
	3250 7400 2900 7400
Wire Wire Line
	3250 7300 2900 7300
Wire Wire Line
	3250 7200 2900 7200
Wire Wire Line
	3250 7100 2900 7100
Wire Wire Line
	3250 7000 2900 7000
Wire Wire Line
	3250 6900 2900 6900
Wire Wire Line
	3250 6800 2900 6800
Wire Wire Line
	3250 6700 2900 6700
Wire Wire Line
	3250 6600 2900 6600
Wire Wire Line
	3250 6500 2900 6500
Wire Wire Line
	3250 6400 2900 6400
Wire Wire Line
	3250 6300 2900 6300
Wire Wire Line
	3250 6200 2900 6200
Wire Wire Line
	3250 6100 2900 6100
Wire Wire Line
	3250 7600 2900 7600
Wire Wire Line
	13600 5700 13250 5700
Wire Wire Line
	13600 5600 13250 5600
Wire Wire Line
	13600 5500 13250 5500
Wire Wire Line
	13600 5400 13250 5400
Wire Wire Line
	13600 5300 13250 5300
Wire Wire Line
	13600 5000 13250 5000
Wire Wire Line
	13600 4900 13250 4900
Wire Wire Line
	13600 4800 13250 4800
Wire Wire Line
	13600 4700 13250 4700
Wire Wire Line
	13600 4600 13250 4600
Wire Wire Line
	13600 4500 13250 4500
Wire Wire Line
	13600 4400 13250 4400
Wire Wire Line
	13600 4300 13250 4300
Wire Wire Line
	13600 5800 13250 5800
Wire Wire Line
	13600 7400 13250 7400
Wire Wire Line
	13600 7300 13250 7300
Wire Wire Line
	13600 7200 13250 7200
Wire Wire Line
	13600 7100 13250 7100
Wire Wire Line
	13600 7000 13250 7000
Wire Wire Line
	13600 6900 13250 6900
Wire Wire Line
	13600 6800 13250 6800
Wire Wire Line
	13600 6700 13250 6700
Wire Wire Line
	13600 6600 13250 6600
Wire Wire Line
	13600 6500 13250 6500
Wire Wire Line
	13600 6400 13250 6400
Wire Wire Line
	13600 6300 13250 6300
Wire Wire Line
	13600 6200 13250 6200
Wire Wire Line
	13600 6100 13250 6100
Wire Wire Line
	13600 3900 13250 3900
Wire Wire Line
	13600 3800 13250 3800
Wire Wire Line
	13600 3700 13250 3700
Wire Wire Line
	13600 3600 13250 3600
Wire Wire Line
	13600 3500 13250 3500
Wire Wire Line
	13600 3400 13250 3400
Wire Wire Line
	13600 3300 13250 3300
Wire Wire Line
	13600 3200 13250 3200
Wire Wire Line
	13600 3100 13250 3100
Wire Wire Line
	13600 3000 13250 3000
Wire Wire Line
	13600 2900 13250 2900
Wire Wire Line
	13600 2800 13250 2800
Wire Wire Line
	13600 2700 13250 2700
Wire Wire Line
	13600 2600 13250 2600
Wire Wire Line
	13600 2500 13250 2500
Wire Wire Line
	13600 4000 13250 4000
Text GLabel 13600 7000 2    60   BiDi ~ 0
MICROSD_D1
Text GLabel 13600 7100 2    60   BiDi ~ 0
MICROSD_D2
Text GLabel 13600 7200 2    60   BiDi ~ 0
MICROSD_D3
Text GLabel 13600 7300 2    60   Output ~ 0
MICROSD_CK
Text GLabel 13600 6900 2    60   BiDi ~ 0
MICROSD_D0
Text GLabel 13600 4500 2    60   Output ~ 0
MICROSD_CMD
Text GLabel 13600 4300 2    60   Input ~ 0
MICROSD_DETECT
Wire Wire Line
	1825 2700 3250 2700
Wire Wire Line
	1925 2775 1925 2700
Connection ~ 1925 2700
$Comp
L GND #PWR?
U 1 1 58C7F2EE
P 1925 3050
F 0 "#PWR?" H 1925 2800 50  0001 C CNN
F 1 "GND" H 1930 2877 50  0000 C CNN
F 2 "" H 1925 3050 60  0000 C CNN
F 3 "" H 1925 3050 60  0000 C CNN
	1    1925 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1925 3050 1925 2975
$Comp
L GND #PWR?
U 1 1 58C7F383
P 2275 2500
F 0 "#PWR?" H 2275 2250 50  0001 C CNN
F 1 "GND" H 2280 2327 50  0000 C CNN
F 2 "" H 2275 2500 60  0000 C CNN
F 3 "" H 2275 2500 60  0000 C CNN
	1    2275 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	2850 2500 3250 2500
Wire Wire Line
	2275 2500 2550 2500
Wire Wire Line
	3075 2500 3075 2225
Wire Wire Line
	3075 2225 3250 2225
Connection ~ 3075 2500
Wire Wire Line
	3250 1925 3075 1925
Wire Wire Line
	3075 1925 3075 1900
$Comp
L +3.3V #PWR?
U 1 1 58C7F67B
P 3075 1900
F 0 "#PWR?" H 3075 1860 30  0001 C CNN
F 1 "+3.3V" H 3084 2038 30  0000 C CNN
F 2 "" H 3075 1900 60  0000 C CNN
F 3 "" H 3075 1900 60  0000 C CNN
	1    3075 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 8050 7850 9175
$Comp
L GND #PWR?
U 1 1 58C7FFF1
P 7850 9175
F 0 "#PWR?" H 7850 8925 50  0001 C CNN
F 1 "GND" H 7855 9002 50  0000 C CNN
F 2 "" H 7850 9175 60  0000 C CNN
F 3 "" H 7850 9175 60  0000 C CNN
	1    7850 9175
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 8050 8050 8325
Wire Wire Line
	8050 8325 8650 8325
Wire Wire Line
	8650 8325 8650 8050
Wire Wire Line
	8450 8050 8450 8325
Connection ~ 8450 8325
Wire Wire Line
	8250 8050 8250 8325
Connection ~ 8250 8325
Wire Wire Line
	8350 8325 8350 9175
Connection ~ 8350 8325
$Comp
L GND #PWR?
U 1 1 58C80253
P 8350 9175
F 0 "#PWR?" H 8350 8925 50  0001 C CNN
F 1 "GND" H 8355 9002 50  0000 C CNN
F 2 "" H 8350 9175 60  0000 C CNN
F 3 "" H 8350 9175 60  0000 C CNN
	1    8350 9175
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 8525 9350 8700
Wire Wire Line
	8700 8525 9350 8525
Wire Wire Line
	8700 8525 8700 8700
Wire Wire Line
	9150 8050 9150 8525
Connection ~ 9150 8525
Wire Wire Line
	9350 9075 9350 8900
Wire Wire Line
	8700 9075 9350 9075
Wire Wire Line
	8700 9075 8700 8900
Wire Wire Line
	9150 9075 9150 9175
Connection ~ 9150 9075
Wire Wire Line
	10100 8250 10100 8700
Wire Wire Line
	10750 8525 10750 8700
Wire Wire Line
	10750 9075 10750 8900
Wire Wire Line
	10100 9075 10750 9075
Wire Wire Line
	10100 9075 10100 8900
Connection ~ 10100 8525
Wire Wire Line
	10450 9075 10450 9175
Connection ~ 10450 9075
$Comp
L GND #PWR?
U 1 1 58C8087A
P 10450 9175
F 0 "#PWR?" H 10450 8925 50  0001 C CNN
F 1 "GND" H 10455 9002 50  0000 C CNN
F 2 "" H 10450 9175 60  0000 C CNN
F 3 "" H 10450 9175 60  0000 C CNN
	1    10450 9175
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 58C808C0
P 9150 9175
F 0 "#PWR?" H 9150 8925 50  0001 C CNN
F 1 "GND" H 9155 9002 50  0000 C CNN
F 2 "" H 9150 9175 60  0000 C CNN
F 3 "" H 9150 9175 60  0000 C CNN
	1    9150 9175
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 8050 9650 8250
Wire Wire Line
	9650 8250 10100 8250
Wire Wire Line
	10100 8525 10750 8525
$Comp
L 10UF_X7R_2012M C?
U 1 1 58C80C38
P 5075 1125
F 0 "C?" V 4950 975 50  0000 L CNN
F 1 "10UF_X7R_2012M" V 5175 725 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC2012X110L" V 5190 1025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1870456.pdf" V 5215 1025 20  0001 C CNN
F 4 "MULTICOMP" V 5265 1025 20  0001 C CNN "manf"
F 5 "MC0805B106K6R3CT" V 5290 1025 20  0001 C CNN "manf#"
F 6 "Element14" V 5315 1025 20  0001 C CNN "Supplier"
F 7 "2320851" V 5340 1025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/multicomp/mc0805b106k6r3ct/cap-mlcc-x7r-10uf-6-3v-0805/dp/2320851" V 5365 1025 20  0001 C CNN "Supplier URL"
F 9 "0.241" V 5390 1025 20  0001 C CNN "Supplier Price"
F 10 "10" V 5415 1025 20  0001 C CNN "Supplier Price Break"
	1    5075 1125
	1    0    0    -1  
$EndComp
$Comp
L 10UF_X7R_2012M C?
U 1 1 58C80CA9
P 6200 1150
F 0 "C?" V 6075 1000 50  0000 L CNN
F 1 "10UF_X7R_2012M" V 6325 750 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC2012X110L" V 6315 1050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1870456.pdf" V 6340 1050 20  0001 C CNN
F 4 "MULTICOMP" V 6390 1050 20  0001 C CNN "manf"
F 5 "MC0805B106K6R3CT" V 6415 1050 20  0001 C CNN "manf#"
F 6 "Element14" V 6440 1050 20  0001 C CNN "Supplier"
F 7 "2320851" V 6465 1050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/multicomp/mc0805b106k6r3ct/cap-mlcc-x7r-10uf-6-3v-0805/dp/2320851" V 6490 1050 20  0001 C CNN "Supplier URL"
F 9 "0.241" V 6515 1050 20  0001 C CNN "Supplier Price"
F 10 "10" V 6540 1050 20  0001 C CNN "Supplier Price Break"
	1    6200 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1050 6500 1050
Wire Wire Line
	6200 1050 6200 1150
Wire Wire Line
	5075 1125 5075 1050
Wire Wire Line
	4900 1050 5350 1050
Wire Wire Line
	6500 1050 6500 2050
Connection ~ 6200 1050
Wire Wire Line
	5750 1050 5625 1050
Wire Wire Line
	5625 1050 5625 875 
Wire Wire Line
	6200 1350 6200 1475
$Comp
L GND #PWR?
U 1 1 58C81316
P 6200 1475
F 0 "#PWR?" H 6200 1225 50  0001 C CNN
F 1 "GND" H 6205 1302 50  0000 C CNN
F 2 "" H 6200 1475 60  0000 C CNN
F 3 "" H 6200 1475 60  0000 C CNN
	1    6200 1475
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 58C8136C
P 5075 1475
F 0 "#PWR?" H 5075 1225 50  0001 C CNN
F 1 "GND" H 5080 1302 50  0000 C CNN
F 2 "" H 5075 1475 60  0000 C CNN
F 3 "" H 5075 1475 60  0000 C CNN
	1    5075 1475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5075 1475 5075 1325
Wire Wire Line
	5350 1050 5350 1900
Wire Wire Line
	5350 1900 6000 1900
Wire Wire Line
	6000 1900 6000 2050
Connection ~ 5075 1050
Wire Wire Line
	4600 1050 4375 1050
Wire Wire Line
	4375 1050 4375 875 
$Comp
L +3.3V #PWR?
U 1 1 58C816C1
P 4375 875
F 0 "#PWR?" H 4375 835 30  0001 C CNN
F 1 "+3.3V" H 4384 1013 30  0000 C CNN
F 2 "" H 4375 875 60  0000 C CNN
F 3 "" H 4375 875 60  0000 C CNN
	1    4375 875 
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 58C81706
P 5625 875
F 0 "#PWR?" H 5625 835 30  0001 C CNN
F 1 "+3.3V" H 5634 1013 30  0000 C CNN
F 2 "" H 5625 875 60  0000 C CNN
F 3 "" H 5625 875 60  0000 C CNN
	1    5625 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 1850 9000 1850
Wire Wire Line
	9000 1850 9000 2050
Wire Wire Line
	8700 2050 8700 1850
Connection ~ 8700 1850
Wire Wire Line
	8400 2050 8400 1850
Connection ~ 8400 1850
Wire Wire Line
	8100 2050 8100 1850
Connection ~ 8100 1850
Wire Wire Line
	7800 2050 7800 1850
Connection ~ 7800 1850
Connection ~ 7500 1850
$Comp
L +3.3V #PWR?
U 1 1 58C829C9
P 7350 900
F 0 "#PWR?" H 7350 860 30  0001 C CNN
F 1 "+3.3V" H 7359 1038 30  0000 C CNN
F 2 "" H 7350 900 60  0000 C CNN
F 3 "" H 7350 900 60  0000 C CNN
	1    7350 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2050 7500 1850
Wire Wire Line
	7500 1350 7500 1600
Wire Wire Line
	7500 1600 9200 1600
Wire Wire Line
	8100 1600 8100 1350
Wire Wire Line
	9000 1600 9000 1325
Connection ~ 8100 1600
Wire Wire Line
	8400 1350 8400 1600
Connection ~ 8400 1600
Wire Wire Line
	8700 1325 8700 1600
Connection ~ 8700 1600
Wire Wire Line
	7800 1350 7800 1600
Connection ~ 7800 1600
$Comp
L GND #PWR?
U 1 1 58C83532
P 9200 1600
F 0 "#PWR?" H 9200 1350 50  0001 C CNN
F 1 "GND" H 9205 1427 50  0000 C CNN
F 2 "" H 9200 1600 60  0000 C CNN
F 3 "" H 9200 1600 60  0000 C CNN
	1    9200 1600
	1    0    0    -1  
$EndComp
Connection ~ 9000 1600
Wire Wire Line
	7500 1150 7500 900 
Wire Wire Line
	7350 900  9000 900 
Wire Wire Line
	9000 900  9000 1125
Connection ~ 7500 900 
$Comp
L +3.3V #PWR?
U 1 1 58C838D4
P 7350 1850
F 0 "#PWR?" H 7350 1810 30  0001 C CNN
F 1 "+3.3V" H 7359 1988 30  0000 C CNN
F 2 "" H 7350 1850 60  0000 C CNN
F 3 "" H 7350 1850 60  0000 C CNN
	1    7350 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1150 7800 900 
Connection ~ 7800 900 
Wire Wire Line
	8100 1150 8100 900 
Connection ~ 8100 900 
Wire Wire Line
	8400 1150 8400 900 
Connection ~ 8400 900 
Wire Wire Line
	8700 1125 8700 900 
Connection ~ 8700 900 
Wire Wire Line
	9500 1850 9500 2050
NoConn ~ 4150 9175
Text Notes 1450 2100 0    60   ~ 0
Boot 0    Boot 1\n   x         0     Main Mem\n   0         1     System Mem
Wire Wire Line
	3250 5800 2900 5800
NoConn ~ 3550 9375
$Comp
L SWD X?
U 1 1 58CD8186
P 3850 9175
F 0 "X?" H 3850 9619 60  0000 C CNN
F 1 "SWD" H 3850 9513 60  0000 C CNB
F 2 "Applidyne_Connector:HARWIN_M50-3600542" H 3900 8775 39  0001 L BNN
F 3 "https://cdn.harwin.com/pdfs/M50-360.pdf" H 3650 8675 39  0001 L BNN
F 4 "HARWIN" H 3650 8775 39  0001 L BNN "manf"
F 5 "M50-3600542" H 3650 8725 39  0001 L BNN "manf#"
F 6 "Digi-Key" H 3650 8625 39  0001 L BNN "Supplier"
F 7 "952-1389-ND" H 3650 8575 39  0001 L BNN "Supplier Part No"
F 8 "http://www.digikey.com.au/product-detail/en/M50-3600542/952-1389-ND/2264370" H 3650 8525 39  0001 L BNN "Supplier URL"
F 9 "1.71" H 3650 8475 39  0001 L BNN "Supplier Price"
F 10 "1" H 3650 8425 39  0001 L BNN "Supplier Price Break "
	1    3850 9175
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 5942E47D
P 9350 8700
F 0 "C?" H 9428 8635 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 9428 8555 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9465 8600 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9490 8600 20  0001 C CNN
F 4 "TDK" V 9540 8600 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9565 8600 20  0001 C CNN "manf#"
F 6 "Element14" V 9590 8600 20  0001 C CNN "Supplier"
F 7 "2210822" V 9615 8600 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9640 8600 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9665 8600 20  0001 C CNN "Supplier Price"
F 10 "100" V 9690 8600 20  0001 C CNN "Supplier Price Break"
	1    9350 8700
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 5942E501
P 10750 8700
F 0 "C?" H 10828 8635 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 10828 8555 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10865 8600 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 10890 8600 20  0001 C CNN
F 4 "TDK" V 10940 8600 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 10965 8600 20  0001 C CNN "manf#"
F 6 "Element14" V 10990 8600 20  0001 C CNN "Supplier"
F 7 "2210822" V 11015 8600 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 11040 8600 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 11065 8600 20  0001 C CNN "Supplier Price"
F 10 "100" V 11090 8600 20  0001 C CNN "Supplier Price Break"
	1    10750 8700
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 59430B8C
P 1925 2775
F 0 "C?" H 2002 2710 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 2002 2630 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 2040 2675 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 2065 2675 20  0001 C CNN
F 4 "TDK" V 2115 2675 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 2140 2675 20  0001 C CNN "manf#"
F 6 "Element14" V 2165 2675 20  0001 C CNN "Supplier"
F 7 "2210822" V 2190 2675 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 2215 2675 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 2240 2675 20  0001 C CNN "Supplier Price"
F 10 "100" V 2265 2675 20  0001 C CNN "Supplier Price Break"
	1    1925 2775
	-1   0    0    -1  
$EndComp
$Comp
L 10K_1005M R?
U 1 1 59430CAB
P 2850 2500
F 0 "R?" V 2662 2350 50  0000 C CNN
F 1 "10K_1005M" V 2742 2350 35  0000 C CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 2960 2350 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 2985 2350 20  0001 C CNN
F 4 "VISHAY" V 3035 2350 20  0001 C CNN "manf"
F 5 "CRCW040210K0FKED" V 3060 2350 20  0001 C CNN "manf#"
F 6 "Element14" V 3085 2350 20  0001 C CNN "Supplier"
F 7 "1469669" V 3110 2350 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210k0fked/res-thick-film-10k-1-0-063w-0402/dp/1469669" V 3135 2350 20  0001 C CNN "Supplier URL"
F 9 "0.009" V 3160 2350 20  0001 C CNN "Supplier Price"
F 10 "10" V 3185 2350 20  0001 C CNN "Supplier Price Break"
	1    2850 2500
	0    1    1    0   
$EndComp
$Comp
L 2.2NF_X7R_1005M C?
U 1 1 59430EF3
P 8700 8700
F 0 "C?" H 8778 8635 50  0000 L CNN
F 1 "2.2NF_X7R_1005M" H 8778 8555 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8815 8600 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2305821.pdf" V 8840 8600 20  0001 C CNN
F 4 "KEMET" V 8890 8600 20  0001 C CNN "manf"
F 5 "C0402C222J3RACAUTO" V 8915 8600 20  0001 C CNN "manf#"
F 6 "Element14" V 8940 8600 20  0001 C CNN "Supplier"
F 7 "2478233" V 8965 8600 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/kemet/c0402c222j3racauto/cap-mlcc-x7r-2200pf-25v-0402/dp/2478233" V 8990 8600 20  0001 C CNN "Supplier URL"
F 9 "0.3" V 9015 8600 20  0001 C CNN "Supplier Price"
F 10 "100" V 9040 8600 20  0001 C CNN "Supplier Price Break"
	1    8700 8700
	1    0    0    -1  
$EndComp
$Comp
L 2.2NF_X7R_1005M C?
U 1 1 5943118A
P 10100 8700
F 0 "C?" H 10178 8635 50  0000 L CNN
F 1 "2.2NF_X7R_1005M" H 10178 8555 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 10215 8600 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2305821.pdf" V 10240 8600 20  0001 C CNN
F 4 "KEMET" V 10290 8600 20  0001 C CNN "manf"
F 5 "C0402C222J3RACAUTO" V 10315 8600 20  0001 C CNN "manf#"
F 6 "Element14" V 10340 8600 20  0001 C CNN "Supplier"
F 7 "2478233" V 10365 8600 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/kemet/c0402c222j3racauto/cap-mlcc-x7r-2200pf-25v-0402/dp/2478233" V 10390 8600 20  0001 C CNN "Supplier URL"
F 9 "0.3" V 10415 8600 20  0001 C CNN "Supplier Price"
F 10 "100" V 10440 8600 20  0001 C CNN "Supplier Price Break"
	1    10100 8700
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 594317AB
P 7500 1150
F 0 "C?" V 7375 1000 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 7600 800 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 7615 1050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 7640 1050 20  0001 C CNN
F 4 "TDK" V 7690 1050 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 7715 1050 20  0001 C CNN "manf#"
F 6 "Element14" V 7740 1050 20  0001 C CNN "Supplier"
F 7 "2210822" V 7765 1050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 7790 1050 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 7815 1050 20  0001 C CNN "Supplier Price"
F 10 "100" V 7840 1050 20  0001 C CNN "Supplier Price Break"
	1    7500 1150
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 59431B86
P 7800 1150
F 0 "C?" V 7675 1000 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 7900 800 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 7915 1050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 7940 1050 20  0001 C CNN
F 4 "TDK" V 7990 1050 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 8015 1050 20  0001 C CNN "manf#"
F 6 "Element14" V 8040 1050 20  0001 C CNN "Supplier"
F 7 "2210822" V 8065 1050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 8090 1050 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 8115 1050 20  0001 C CNN "Supplier Price"
F 10 "100" V 8140 1050 20  0001 C CNN "Supplier Price Break"
	1    7800 1150
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 59431BD4
P 8100 1150
F 0 "C?" V 7975 1000 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 8200 800 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8215 1050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 8240 1050 20  0001 C CNN
F 4 "TDK" V 8290 1050 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 8315 1050 20  0001 C CNN "manf#"
F 6 "Element14" V 8340 1050 20  0001 C CNN "Supplier"
F 7 "2210822" V 8365 1050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 8390 1050 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 8415 1050 20  0001 C CNN "Supplier Price"
F 10 "100" V 8440 1050 20  0001 C CNN "Supplier Price Break"
	1    8100 1150
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 59431C26
P 8400 1150
F 0 "C?" V 8275 1000 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 8500 800 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8515 1050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 8540 1050 20  0001 C CNN
F 4 "TDK" V 8590 1050 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 8615 1050 20  0001 C CNN "manf#"
F 6 "Element14" V 8640 1050 20  0001 C CNN "Supplier"
F 7 "2210822" V 8665 1050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 8690 1050 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 8715 1050 20  0001 C CNN "Supplier Price"
F 10 "100" V 8740 1050 20  0001 C CNN "Supplier Price Break"
	1    8400 1150
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 59431C72
P 8700 1125
F 0 "C?" V 8575 975 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 8800 775 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8815 1025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 8840 1025 20  0001 C CNN
F 4 "TDK" V 8890 1025 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 8915 1025 20  0001 C CNN "manf#"
F 6 "Element14" V 8940 1025 20  0001 C CNN "Supplier"
F 7 "2210822" V 8965 1025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 8990 1025 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9015 1025 20  0001 C CNN "Supplier Price"
F 10 "100" V 9040 1025 20  0001 C CNN "Supplier Price Break"
	1    8700 1125
	1    0    0    -1  
$EndComp
$Comp
L 100NF_X7R_1005M C?
U 1 1 59431CC4
P 9000 1125
F 0 "C?" V 8875 975 50  0000 L CNN
F 1 "100NF_X7R_1005M" V 9100 775 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 9115 1025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 9140 1025 20  0001 C CNN
F 4 "TDK" V 9190 1025 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 9215 1025 20  0001 C CNN "manf#"
F 6 "Element14" V 9240 1025 20  0001 C CNN "Supplier"
F 7 "2210822" V 9265 1025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 9290 1025 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 9315 1025 20  0001 C CNN "Supplier Price"
F 10 "100" V 9340 1025 20  0001 C CNN "Supplier Price Break"
	1    9000 1125
	1    0    0    -1  
$EndComp
$Comp
L 10R_1005M R?
U 1 1 59432145
P 6050 1050
F 0 "R?" V 5862 900 50  0000 C CNN
F 1 "10R_1005M" V 5942 900 35  0000 C CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 6160 900 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 6185 900 20  0001 C CNN
F 4 "VISHAY" V 6235 900 20  0001 C CNN "manf"
F 5 "CRCW040210R0FKED" V 6260 900 20  0001 C CNN "manf#"
F 6 "Element14" V 6285 900 20  0001 C CNN "Supplier"
F 7 "1652742" V 6310 900 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210r0fked/res-thick-film-10r-1-0-063w-0402/dp/1652742" V 6335 900 20  0001 C CNN "Supplier URL"
F 9 "0.009" V 6360 900 20  0001 C CNN "Supplier Price"
F 10 "10" V 6385 900 20  0001 C CNN "Supplier Price Break"
	1    6050 1050
	0    1    1    0   
$EndComp
$Comp
L 10R_1005M R?
U 1 1 59432275
P 4900 1050
F 0 "R?" V 4712 900 50  0000 C CNN
F 1 "10R_1005M" V 4792 900 35  0000 C CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 5010 900 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 5035 900 20  0001 C CNN
F 4 "VISHAY" V 5085 900 20  0001 C CNN "manf"
F 5 "CRCW040210R0FKED" V 5110 900 20  0001 C CNN "manf#"
F 6 "Element14" V 5135 900 20  0001 C CNN "Supplier"
F 7 "1652742" V 5160 900 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210r0fked/res-thick-film-10r-1-0-063w-0402/dp/1652742" V 5185 900 20  0001 C CNN "Supplier URL"
F 9 "0.009" V 5210 900 20  0001 C CNN "Supplier Price"
F 10 "10" V 5235 900 20  0001 C CNN "Supplier Price Break"
	1    4900 1050
	0    1    1    0   
$EndComp
$Comp
L SOLDER-LINK-2 SL?
U 1 1 5947CB5D
P 3250 2075
F 0 "SL?" V 3212 2133 40  0000 L CNN
F 1 "SOLDER-LINK-2" V 3288 2133 40  0000 L CNN
F 2 "Applidyne_Link:SJ1608-2N" V 3365 1975 20  0001 C CNN
F 3 "DatasheetURL" V 3390 1975 20  0001 C CNN
F 4 "Manufacturer" V 3440 1975 20  0001 C CNN "manf"
F 5 "ManufacturerPartNo" V 3465 1975 20  0001 C CNN "manf#"
F 6 "Supplier" V 3490 1975 20  0001 C CNN "Supplier"
F 7 "SupplierPartNo" V 3515 1975 20  0001 C CNN "Supplier Part No"
F 8 "SupplierURL" V 3540 1975 20  0001 C CNN "Supplier URL"
F 9 "0" V 3565 1975 20  0001 C CNN "Supplier Price"
F 10 "1" V 3590 1975 20  0001 C CNN "Supplier Price Break"
	1    3250 2075
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59480FA5
P 9500 1850
F 0 "#PWR?" H 9500 1810 30  0001 C CNN
F 1 "+3.3V" H 9509 1988 30  0000 C CNN
F 2 "" H 9500 1850 60  0000 C CNN
F 3 "" H 9500 1850 60  0000 C CNN
	1    9500 1850
	1    0    0    -1  
$EndComp
Text GLabel 2400 10275 0    60   Output ~ 0
PWDN
Text GLabel 2400 10400 0    60   Output ~ 0
RESET
Text GLabel 2650 10600 2    60   Output ~ 0
XCLK
Text GLabel 2650 10475 2    60   Input ~ 0
HREF
Text GLabel 2650 10350 2    60   Input ~ 0
VSYNC
Text GLabel 2650 10225 2    60   Input ~ 0
PIXCK
Text GLabel 2400 10525 0    60   Input ~ 0
STROBE
Text GLabel 2400 10150 0    60   Output ~ 0
FREX
Text GLabel 2400 10025 0    60   Output ~ 0
EXPSTB
Text GLabel 3200 10000 2    60   Input ~ 0
D0
Text GLabel 3200 10125 2    60   Input ~ 0
D1
Text GLabel 3200 10250 2    60   Input ~ 0
D2
Text GLabel 3200 10375 2    60   Input ~ 0
D3
Text GLabel 3200 10500 2    60   Input ~ 0
D4
Text GLabel 3200 10625 2    60   Input ~ 0
D5
Text GLabel 3200 10750 2    60   Input ~ 0
D6
Text GLabel 3200 10875 2    60   Input ~ 0
D7
Text Notes 2500 9925 0    60   ~ 0
Camera lines
Text GLabel 3700 10325 2    60   Input ~ 0
SIO_C
Text GLabel 3725 10500 2    60   BiDi ~ 0
SIO_D
Text Notes 3800 10225 0    60   ~ 0
i2c
$Comp
L LED_GREEN_1608M D?
U 1 1 5948E009
P 5175 9300
F 0 "D?" V 5221 9192 50  0000 R CNN
F 1 "LED_GREEN_1608M" V 5130 9192 50  0000 R CNN
F 2 "" H 5075 9300 50  0000 C CNN
F 3 "http://www.farnell.com/datasheets/1720200.pdf" H 5175 9090 50  0001 C CNN
F 4 "DIALIGHT" H 5175 8880 60  0001 C CNN "manf"
F 5 "5988070107F" H 5175 8790 60  0001 C CNN "manf#"
F 6 "Element 14" H 5175 8690 60  0001 C CNN "Supplier"
F 7 "1465991" H 5175 8590 60  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/dialight/5988070107f/led-0603-green-20mcd-566nm/dp/1465991" H 5185 8510 60  0001 C CNN "Supplier URL"
F 9 "0.4" H 5175 8410 60  0001 C CNN "Supplier Price"
F 10 "10" H 5175 8310 60  0001 C CNN "Supplier Price Break"
	1    5175 9300
	0    -1   -1   0   
$EndComp
$Comp
L LED_RED_1608M D?
U 1 1 5948E26E
P 6175 9300
F 0 "D?" V 6221 9192 50  0000 R CNN
F 1 "LED_RED_1608M" V 6130 9192 50  0000 R CNN
F 2 "" H 6075 9300 50  0000 C CNN
F 3 "http://www.farnell.com/datasheets/87215.pdf?_ga=1.108371586.1676120999.1492995984" H 6175 9090 50  0001 C CNN
F 4 "DIALIGHT" H 6175 8880 60  0001 C CNN "manf"
F 5 "597-5004-407F" H 6175 8790 60  0001 C CNN "manf#"
F 6 "Element 14" H 6175 8690 60  0001 C CNN "Supplier"
F 7 "1867024" H 6175 8590 60  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/dialight/597-5004-407f/led-red-0-8mm-x-1-2mm-50mcd-630nm/dp/1867024" H 6185 8510 60  0001 C CNN "Supplier URL"
F 9 "1.71" H 6175 8410 60  0001 C CNN "Supplier Price"
F 10 "10" H 6175 8310 60  0001 C CNN "Supplier Price Break"
	1    6175 9300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5948E41A
P 6175 9625
F 0 "#PWR?" H 6175 9375 50  0001 C CNN
F 1 "GND" H 6180 9452 50  0000 C CNN
F 2 "" H 6175 9625 60  0000 C CNN
F 3 "" H 6175 9625 60  0000 C CNN
	1    6175 9625
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5948E458
P 5175 9625
F 0 "#PWR?" H 5175 9375 50  0001 C CNN
F 1 "GND" H 5180 9452 50  0000 C CNN
F 2 "" H 5175 9625 60  0000 C CNN
F 3 "" H 5175 9625 60  0000 C CNN
	1    5175 9625
	1    0    0    -1  
$EndComp
Wire Wire Line
	5175 9625 5175 9500
Wire Wire Line
	6175 9500 6175 9625
$Comp
L 1K_1005M R?
U 1 1 5948E833
P 5175 8700
F 0 "R?" H 5248 8585 50  0000 L CNN
F 1 "1K_1005M" H 5248 8505 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 5285 8550 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 5310 8550 20  0001 C CNN
F 4 "VISHAY" V 5360 8550 20  0001 C CNN "manf"
F 5 "CRCW04021K00FKED" V 5385 8550 20  0001 C CNN "manf#"
F 6 "Element14" V 5410 8550 20  0001 C CNN "Supplier"
F 7 "1469669" V 5435 8550 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210k0fked/res-thick-film-10k-1-0-063w-0402/dp/1469669" V 5460 8550 20  0001 C CNN "Supplier URL"
F 9 "0.09" V 5485 8550 20  0001 C CNN "Supplier Price"
F 10 "10" V 5510 8550 20  0001 C CNN "Supplier Price Break"
	1    5175 8700
	1    0    0    -1  
$EndComp
$Comp
L 1K_1005M R?
U 1 1 5948E8C5
P 6175 8700
F 0 "R?" H 6248 8585 50  0000 L CNN
F 1 "1K_1005M" H 6248 8505 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 6285 8550 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2111203.pdf" V 6310 8550 20  0001 C CNN
F 4 "VISHAY" V 6360 8550 20  0001 C CNN "manf"
F 5 "CRCW04021K00FKED" V 6385 8550 20  0001 C CNN "manf#"
F 6 "Element14" V 6410 8550 20  0001 C CNN "Supplier"
F 7 "1469669" V 6435 8550 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/vishay/crcw040210k0fked/res-thick-film-10k-1-0-063w-0402/dp/1469669" V 6460 8550 20  0001 C CNN "Supplier URL"
F 9 "0.09" V 6485 8550 20  0001 C CNN "Supplier Price"
F 10 "10" V 6510 8550 20  0001 C CNN "Supplier Price Break"
	1    6175 8700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6175 9000 6175 9100
Wire Wire Line
	5175 9000 5175 9100
Wire Wire Line
	5175 8700 5175 8575
Wire Wire Line
	6175 8700 6175 8575
Text GLabel 5175 8575 1    60   Input ~ 0
STATUS0
Text GLabel 6175 8575 1    60   Input ~ 0
STATUS1
Text GLabel 1050 10375 1    60   Output ~ 0
STATUS0
Text GLabel 1200 10425 1    60   Output ~ 0
STATUS1
Text Notes 925  9750 0    60   ~ 0
Status Leds
Text GLabel 4975 10750 0    60   Output ~ 0
IRCUT_A
Text GLabel 5025 10950 0    60   Output ~ 0
IRCUT_B
Text GLabel 6225 10650 0    60   Output ~ 0
FLASH_DAC
Text GLabel 6250 10925 0    60   Input ~ 0
AMBIENT_LIGHT
Text GLabel 4575 10100 2    60   Input ~ 0
PWR_EN
$EndSCHEMATC
