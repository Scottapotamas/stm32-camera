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
Sheet 3 5
Title ""
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 4725 1200 0    118  ~ 24
Input Protection and Regulation
Text Notes 7175 1825 0    63   ~ 13
3.3V Regulator
Text Notes 6575 2200 0    60   ~ 0
Regulator provides for microcontroller, other IC's \nand is used predominantly on all pullups etc.
$Comp
L +3.3V #PWR?
U 1 1 5898ACD8
P 9500 2600
F 0 "#PWR?" H 9500 2560 30  0001 C CNN
F 1 "+3.3V" H 9509 2738 30  0000 C CNN
F 2 "" H 9500 2600 60  0000 C CNN
F 3 "" H 9500 2600 60  0000 C CNN
	1    9500 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5898DF8B
P 8025 3050
F 0 "#PWR?" H 8025 2800 50  0001 C CNN
F 1 "GND" H 8030 2877 50  0000 C CNN
F 2 "" H 8025 3050 60  0000 C CNN
F 3 "" H 8025 3050 60  0000 C CNN
	1    8025 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5898E012
P 7450 3050
F 0 "#PWR?" H 7450 2800 50  0001 C CNN
F 1 "GND" H 7455 2877 50  0000 C CNN
F 2 "" H 7450 3050 60  0000 C CNN
F 3 "" H 7450 3050 60  0000 C CNN
	1    7450 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5898E2B4
P 6300 3050
F 0 "#PWR?" H 6300 2800 50  0001 C CNN
F 1 "GND" H 6305 2877 50  0000 C CNN
F 2 "" H 6300 3050 60  0000 C CNN
F 3 "" H 6300 3050 60  0000 C CNN
	1    6300 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5898F1EE
P 8700 3050
F 0 "#PWR?" H 8700 2800 50  0001 C CNN
F 1 "GND" H 8705 2877 50  0000 C CNN
F 2 "" H 8700 3050 60  0000 C CNN
F 3 "" H 8700 3050 60  0000 C CNN
	1    8700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2525 6300 2675
Wire Wire Line
	6300 2600 7000 2600
Connection ~ 6300 2600
Wire Wire Line
	7000 2750 6900 2750
Wire Wire Line
	6900 2750 6900 2600
Connection ~ 6900 2600
Wire Wire Line
	6300 2875 6300 3050
Wire Wire Line
	7450 3050 7450 2950
Wire Wire Line
	7900 2600 9500 2600
Wire Wire Line
	7900 2750 8025 2750
Wire Wire Line
	8025 2750 8025 2800
Wire Wire Line
	8025 3000 8025 3050
Wire Wire Line
	8700 2875 8700 3050
$Comp
L +12V #PWR?
U 1 1 58CBCCE7
P 6300 2525
F 0 "#PWR?" H 6300 2375 50  0001 C CNN
F 1 "+12V" H 6315 2698 50  0000 C CNN
F 2 "" H 6300 2525 60  0000 C CNN
F 3 "" H 6300 2525 60  0000 C CNN
	1    6300 2525
	1    0    0    -1  
$EndComp
$Comp
L AP2210K U?
U 1 1 58CE8C55
P 7450 2650
F 0 "U?" H 7450 2944 40  0000 C CNN
F 1 "AP2210K" H 7450 2868 40  0000 C CNN
F 2 "Applidyne_SOT:SOT95P280X145-5L30N" H 7150 2850 35  0001 L CIN
F 3 "http://docs-asia.electrocomponents.com/webdocs/1332/0900766b8133217a.pdf" H 7450 1500 60  0001 C CNN
F 4 "DIODES ZETEX" H 7450 2000 60  0001 C CNN "manf"
F 5 "AP2210K-3.3TRG1" H 7450 1900 60  0001 C CNN "manf#"
F 6 "RS Online" H 7450 1800 60  0001 C CNN "Supplier"
F 7 "828-7429" H 7450 1700 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/low-dropout-voltage-regulators/8287429/" H 7450 1600 60  0001 C CNN "Supplier URL"
F 9 "0.176" H 7450 1400 60  0001 C CNN "Supplier Price"
F 10 "100" H 7450 1300 60  0001 C CNN "Supplier Price Break"
	1    7450 2650
	1    0    0    -1  
$EndComp
$Comp
L 10UF_X7R_3225M C?
U 1 1 58CE57BE
P 6300 2675
F 0 "C?" H 6378 2610 50  0000 L CNN
F 1 "10UF_X7R_3225M" H 6378 2530 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC3225X170L" V 6415 2575 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1880583.pdf" V 6440 2575 20  0001 C CNN
F 4 "WURTH ELEKTRONIK" V 6490 2575 20  0001 C CNN "manf"
F 5 "885012209028" V 6515 2575 20  0001 C CNN "manf#"
F 6 "Element14" V 6540 2575 20  0001 C CNN "Supplier"
F 7 "2466740" V 6565 2575 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/wurth-elektronik/885012209028/cap-mlcc-x7r-10uf-25v-1210/dp/2466740" V 6590 2575 20  0001 C CNN "Supplier URL"
F 9 "0.569" V 6615 2575 20  0001 C CNN "Supplier Price"
F 10 "1" V 6640 2575 20  0001 C CNN "Supplier Price Break"
	1    6300 2675
	1    0    0    -1  
$EndComp
$Comp
L 10UF_X7R_3225M C?
U 1 1 58CE58B0
P 8700 2675
F 0 "C?" H 8778 2610 50  0000 L CNN
F 1 "10UF_X7R_3225M" H 8778 2530 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC3225X170L" V 8815 2575 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1880583.pdf" V 8840 2575 20  0001 C CNN
F 4 "WURTH ELEKTRONIK" V 8890 2575 20  0001 C CNN "manf"
F 5 "885012209028" V 8915 2575 20  0001 C CNN "manf#"
F 6 "Element14" V 8940 2575 20  0001 C CNN "Supplier"
F 7 "2466740" V 8965 2575 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/wurth-elektronik/885012209028/cap-mlcc-x7r-10uf-25v-1210/dp/2466740" V 8990 2575 20  0001 C CNN "Supplier URL"
F 9 "0.569" V 9015 2575 20  0001 C CNN "Supplier Price"
F 10 "1" V 9040 2575 20  0001 C CNN "Supplier Price Break"
	1    8700 2675
	1    0    0    -1  
$EndComp
$Comp
L 100PF_C0G_1005M C?
U 1 1 5942E50F
P 8025 2800
F 0 "C?" H 8103 2735 50  0000 L CNN
F 1 "100PF_C0G_1005M" H 8103 2655 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 8140 2700 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1955634.pdf" V 8165 2700 20  0001 C CNN
F 4 "MURATA" V 8215 2700 20  0001 C CNN "manf"
F 5 "GCM1555C1H101JA16D" V 8240 2700 20  0001 C CNN "manf#"
F 6 "Element14" V 8265 2700 20  0001 C CNN "Supplier"
F 7 "2494184" V 8290 2700 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/gcm1555c1h101ja16d/cap-mlcc-c0g-np0-100pf-50v-0402/dp/2494184" V 8315 2700 20  0001 C CNN "Supplier URL"
F 9 "0.025" V 8340 2700 20  0001 C CNN "Supplier Price"
F 10 "10" V 8365 2700 20  0001 C CNN "Supplier Price Break"
	1    8025 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 2675 8700 2600
Connection ~ 8700 2600
$Comp
L +1.3V #PWR?
U 1 1 5948D3E9
P 9600 5625
F 0 "#PWR?" H 9600 5585 30  0001 C CNN
F 1 "+1.3V" H 9609 5763 30  0000 C CNN
F 2 "" H 9600 5625 60  0000 C CNN
F 3 "" H 9600 5625 60  0000 C CNN
	1    9600 5625
	1    0    0    -1  
$EndComp
$Comp
L +2.8V #PWR?
U 1 1 5948D459
P 9475 4225
F 0 "#PWR?" H 9475 4185 30  0001 C CNN
F 1 "+2.8V" H 9484 4363 30  0000 C CNN
F 2 "" H 9475 4225 60  0000 C CNN
F 3 "" H 9475 4225 60  0000 C CNN
	1    9475 4225
	1    0    0    -1  
$EndComp
Text Notes 7125 4050 0    63   ~ 13
2.8V Regulator
Text Notes 7125 5600 0    63   ~ 13
1.3V Regulator
Text Notes 2425 5000 0    60   ~ 0
Input Filter?
Text Notes 2375 1900 0    63   ~ 13
Main Connector
$EndSCHEMATC
