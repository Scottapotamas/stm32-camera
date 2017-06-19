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
Text Notes 5250 2500 0    118  ~ 24
3.3V Regulator
Text Notes 4650 2875 0    60   ~ 0
Regulator provides for microcontroller, other IC's \nand is used predominantly on all pullups etc.
$Comp
L +3.3V #PWR59
U 1 1 5898ACD8
P 7625 3800
F 0 "#PWR59" H 7625 3760 30  0001 C CNN
F 1 "+3.3V" H 7634 3938 30  0000 C CNN
F 2 "" H 7625 3800 60  0000 C CNN
F 3 "" H 7625 3800 60  0000 C CNN
	1    7625 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR57
U 1 1 5898DF8B
P 6150 4250
F 0 "#PWR57" H 6150 4000 50  0001 C CNN
F 1 "GND" H 6155 4077 50  0000 C CNN
F 2 "" H 6150 4250 60  0000 C CNN
F 3 "" H 6150 4250 60  0000 C CNN
	1    6150 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR56
U 1 1 5898E012
P 5575 4250
F 0 "#PWR56" H 5575 4000 50  0001 C CNN
F 1 "GND" H 5580 4077 50  0000 C CNN
F 2 "" H 5575 4250 60  0000 C CNN
F 3 "" H 5575 4250 60  0000 C CNN
	1    5575 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR54
U 1 1 5898E2B4
P 4425 4250
F 0 "#PWR54" H 4425 4000 50  0001 C CNN
F 1 "GND" H 4430 4077 50  0000 C CNN
F 2 "" H 4425 4250 60  0000 C CNN
F 3 "" H 4425 4250 60  0000 C CNN
	1    4425 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR58
U 1 1 5898F1EE
P 6825 4250
F 0 "#PWR58" H 6825 4000 50  0001 C CNN
F 1 "GND" H 6830 4077 50  0000 C CNN
F 2 "" H 6825 4250 60  0000 C CNN
F 3 "" H 6825 4250 60  0000 C CNN
	1    6825 4250
	1    0    0    -1  
$EndComp
Text Notes 4525 4925 0    60   Italic 12
CONSIDER CHANGING ONCE ACTUAL LOAD IS KNOWN
Wire Wire Line
	4425 3725 4425 3875
Wire Wire Line
	4425 3800 5125 3800
Connection ~ 4425 3800
Wire Wire Line
	5125 3950 5025 3950
Wire Wire Line
	5025 3950 5025 3800
Connection ~ 5025 3800
Wire Wire Line
	4425 4075 4425 4250
Wire Wire Line
	5575 4250 5575 4150
Wire Wire Line
	6025 3800 7625 3800
Wire Wire Line
	6025 3950 6150 3950
Wire Wire Line
	6150 3950 6150 4000
Wire Wire Line
	6150 4200 6150 4250
Wire Wire Line
	6825 4075 6825 4250
$Comp
L +12V #PWR53
U 1 1 58CBCCE7
P 4425 3725
F 0 "#PWR53" H 4425 3575 50  0001 C CNN
F 1 "+12V" H 4440 3898 50  0000 C CNN
F 2 "" H 4425 3725 60  0000 C CNN
F 3 "" H 4425 3725 60  0000 C CNN
	1    4425 3725
	1    0    0    -1  
$EndComp
$Comp
L AP2210K U4
U 1 1 58CE8C55
P 5575 3850
F 0 "U4" H 5575 4144 40  0000 C CNN
F 1 "AP2210K" H 5575 4068 40  0000 C CNN
F 2 "Applidyne_SOT:SOT95P280X145-5L30N" H 5275 4050 35  0001 L CIN
F 3 "http://docs-asia.electrocomponents.com/webdocs/1332/0900766b8133217a.pdf" H 5575 2700 60  0001 C CNN
F 4 "DIODES ZETEX" H 5575 3200 60  0001 C CNN "manf"
F 5 "AP2210K-3.3TRG1" H 5575 3100 60  0001 C CNN "manf#"
F 6 "RS Online" H 5575 3000 60  0001 C CNN "Supplier"
F 7 "828-7429" H 5575 2900 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/low-dropout-voltage-regulators/8287429/" H 5575 2800 60  0001 C CNN "Supplier URL"
F 9 "0.176" H 5575 2600 60  0001 C CNN "Supplier Price"
F 10 "100" H 5575 2500 60  0001 C CNN "Supplier Price Break"
	1    5575 3850
	1    0    0    -1  
$EndComp
$Comp
L 10UF_X7R_3225M C31
U 1 1 58CE57BE
P 4425 3875
F 0 "C31" H 4503 3810 50  0000 L CNN
F 1 "10UF_X7R_3225M" H 4503 3730 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC3225X170L" V 4540 3775 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1880583.pdf" V 4565 3775 20  0001 C CNN
F 4 "WURTH ELEKTRONIK" V 4615 3775 20  0001 C CNN "manf"
F 5 "885012209028" V 4640 3775 20  0001 C CNN "manf#"
F 6 "Element14" V 4665 3775 20  0001 C CNN "Supplier"
F 7 "2466740" V 4690 3775 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/wurth-elektronik/885012209028/cap-mlcc-x7r-10uf-25v-1210/dp/2466740" V 4715 3775 20  0001 C CNN "Supplier URL"
F 9 "0.569" V 4740 3775 20  0001 C CNN "Supplier Price"
F 10 "1" V 4765 3775 20  0001 C CNN "Supplier Price Break"
	1    4425 3875
	1    0    0    -1  
$EndComp
$Comp
L 10UF_X7R_3225M C34
U 1 1 58CE58B0
P 6825 3875
F 0 "C34" H 6903 3810 50  0000 L CNN
F 1 "10UF_X7R_3225M" H 6903 3730 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC3225X170L" V 6940 3775 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1880583.pdf" V 6965 3775 20  0001 C CNN
F 4 "WURTH ELEKTRONIK" V 7015 3775 20  0001 C CNN "manf"
F 5 "885012209028" V 7040 3775 20  0001 C CNN "manf#"
F 6 "Element14" V 7065 3775 20  0001 C CNN "Supplier"
F 7 "2466740" V 7090 3775 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/wurth-elektronik/885012209028/cap-mlcc-x7r-10uf-25v-1210/dp/2466740" V 7115 3775 20  0001 C CNN "Supplier URL"
F 9 "0.569" V 7140 3775 20  0001 C CNN "Supplier Price"
F 10 "1" V 7165 3775 20  0001 C CNN "Supplier Price Break"
	1    6825 3875
	1    0    0    -1  
$EndComp
$Comp
L 100PF_C0G_1005M C33
U 1 1 5942E50F
P 6150 4000
F 0 "C33" H 6228 3935 50  0000 L CNN
F 1 "100PF_C0G_1005M" H 6228 3855 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 6265 3900 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1955634.pdf" V 6290 3900 20  0001 C CNN
F 4 "MURATA" V 6340 3900 20  0001 C CNN "manf"
F 5 "GCM1555C1H101JA16D" V 6365 3900 20  0001 C CNN "manf#"
F 6 "Element14" V 6390 3900 20  0001 C CNN "Supplier"
F 7 "2494184" V 6415 3900 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/gcm1555c1h101ja16d/cap-mlcc-c0g-np0-100pf-50v-0402/dp/2494184" V 6440 3900 20  0001 C CNN "Supplier URL"
F 9 "0.025" V 6465 3900 20  0001 C CNN "Supplier Price"
F 10 "10" V 6490 3900 20  0001 C CNN "Supplier Price Break"
	1    6150 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6825 3875 6825 3800
Connection ~ 6825 3800
$EndSCHEMATC
