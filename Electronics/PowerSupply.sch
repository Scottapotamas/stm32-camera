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
Text Notes 7175 1775 0    63   ~ 13
3.3V Regulator
Text Notes 6575 2050 0    60   ~ 0
Regulator provides for microcontroller, other IC's \nand is used predominantly on all pullups etc.
$Comp
L +3.3V #PWR022
U 1 1 5898ACD8
P 9500 2425
F 0 "#PWR022" H 9500 2385 30  0001 C CNN
F 1 "+3.3V" H 9509 2563 30  0000 C CNN
F 2 "" H 9500 2425 60  0000 C CNN
F 3 "" H 9500 2425 60  0000 C CNN
	1    9500 2425
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5898E012
P 7450 2875
F 0 "#PWR023" H 7450 2625 50  0001 C CNN
F 1 "GND" H 7455 2702 50  0000 C CNN
F 2 "" H 7450 2875 60  0000 C CNN
F 3 "" H 7450 2875 60  0000 C CNN
	1    7450 2875
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 5898E2B4
P 6300 2875
F 0 "#PWR024" H 6300 2625 50  0001 C CNN
F 1 "GND" H 6305 2702 50  0000 C CNN
F 2 "" H 6300 2875 60  0000 C CNN
F 3 "" H 6300 2875 60  0000 C CNN
	1    6300 2875
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5898F1EE
P 8700 2875
F 0 "#PWR025" H 8700 2625 50  0001 C CNN
F 1 "GND" H 8705 2702 50  0000 C CNN
F 2 "" H 8700 2875 60  0000 C CNN
F 3 "" H 8700 2875 60  0000 C CNN
	1    8700 2875
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2350 6300 2500
Wire Wire Line
	6300 2425 7000 2425
Connection ~ 6300 2425
Wire Wire Line
	7000 2575 6900 2575
Wire Wire Line
	6900 2575 6900 2425
Connection ~ 6900 2425
Wire Wire Line
	6300 2700 6300 2875
Wire Wire Line
	7450 2875 7450 2775
Wire Wire Line
	7900 2425 9500 2425
Wire Wire Line
	8700 2700 8700 2875
Wire Wire Line
	8700 2500 8700 2425
Connection ~ 8700 2425
$Comp
L +1.3V #PWR026
U 1 1 5948D3E9
P 9550 5350
F 0 "#PWR026" H 9550 5310 30  0001 C CNN
F 1 "+1.3V" H 9559 5488 30  0000 C CNN
F 2 "" H 9550 5350 60  0000 C CNN
F 3 "" H 9550 5350 60  0000 C CNN
	1    9550 5350
	1    0    0    -1  
$EndComp
$Comp
L +2.8V #PWR027
U 1 1 5948D459
P 9525 3950
F 0 "#PWR027" H 9525 3910 30  0001 C CNN
F 1 "+2.8V" H 9534 4088 30  0000 C CNN
F 2 "" H 9525 3950 60  0000 C CNN
F 3 "" H 9525 3950 60  0000 C CNN
	1    9525 3950
	1    0    0    -1  
$EndComp
Text Notes 7125 3575 0    63   ~ 13
2.8V Regulator
Text Notes 1825 4475 0    79   ~ 16
Input Filter and polarity/esd protection???\nCurrently incredibly plain. Assume user is intelligent.
Text Notes 2375 1900 0    63   ~ 13
Main Connector
$Comp
L AP2210K-ADJ U2
U 1 1 5948E321
P 7450 2475
F 0 "U2" H 7450 2769 40  0000 C CNN
F 1 "AP2210K-ADJ" H 7450 2693 40  0000 C CNN
F 2 "Applidyne_SOT:SOT95P280X145-5L30N" H 7150 2675 35  0001 L CIN
F 3 "http://docs-asia.electrocomponents.com/webdocs/1332/0900766b8133217a.pdf" H 7450 1325 60  0001 C CNN
F 4 "DIODES ZETEX" H 7450 1825 60  0001 C CNN "manf"
F 5 "AP2210K-ADJTRG1" H 7450 1725 60  0001 C CNN "manf#"
F 6 "RS Online" H 7450 1625 60  0001 C CNN "Supplier"
F 7 "828-7422" H 7450 1525 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/low-dropout-voltage-regulators/8287422/" H 7450 1425 60  0001 C CNN "Supplier URL"
F 9 "0.272" H 7450 1225 60  0001 C CNN "Supplier Price"
F 10 "100" H 7450 1125 60  0001 C CNN "Supplier Price Break"
	1    7450 2475
	1    0    0    -1  
$EndComp
Text Notes 9575 1875 0    60   ~ 0
VOUT=1.25V*(1+R2/R1) 
$Comp
L GND #PWR028
U 1 1 5948E8F8
P 7475 4400
F 0 "#PWR028" H 7475 4150 50  0001 C CNN
F 1 "GND" H 7480 4227 50  0000 C CNN
F 2 "" H 7475 4400 60  0000 C CNN
F 3 "" H 7475 4400 60  0000 C CNN
	1    7475 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5948E8FE
P 6325 4400
F 0 "#PWR029" H 6325 4150 50  0001 C CNN
F 1 "GND" H 6330 4227 50  0000 C CNN
F 2 "" H 6325 4400 60  0000 C CNN
F 3 "" H 6325 4400 60  0000 C CNN
	1    6325 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 5948E904
P 8725 4400
F 0 "#PWR030" H 8725 4150 50  0001 C CNN
F 1 "GND" H 8730 4227 50  0000 C CNN
F 2 "" H 8725 4400 60  0000 C CNN
F 3 "" H 8725 4400 60  0000 C CNN
	1    8725 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6325 3875 6325 4150
Wire Wire Line
	6325 3950 7025 3950
Connection ~ 6325 3950
Wire Wire Line
	7025 4100 6925 4100
Wire Wire Line
	6325 4350 6325 4400
Wire Wire Line
	7475 4400 7475 4300
Wire Wire Line
	7925 3950 9525 3950
Wire Wire Line
	8725 4225 8725 4400
Wire Wire Line
	8725 4025 8725 3950
Connection ~ 8725 3950
$Comp
L AP2210K-ADJ U3
U 1 1 5948E91D
P 7475 4000
F 0 "U3" H 7475 4294 40  0000 C CNN
F 1 "AP2210K-ADJ" H 7475 4218 40  0000 C CNN
F 2 "Applidyne_SOT:SOT95P280X145-5L30N" H 7175 4200 35  0001 L CIN
F 3 "http://docs-asia.electrocomponents.com/webdocs/1332/0900766b8133217a.pdf" H 7475 2850 60  0001 C CNN
F 4 "DIODES ZETEX" H 7475 3350 60  0001 C CNN "manf"
F 5 "AP2210K-ADJTRG1" H 7475 3250 60  0001 C CNN "manf#"
F 6 "RS Online" H 7475 3150 60  0001 C CNN "Supplier"
F 7 "828-7422" H 7475 3050 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/low-dropout-voltage-regulators/8287422/" H 7475 2950 60  0001 C CNN "Supplier URL"
F 9 "0.272" H 7475 2750 60  0001 C CNN "Supplier Price"
F 10 "100" H 7475 2650 60  0001 C CNN "Supplier Price Break"
	1    7475 4000
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR031
U 1 1 5948E93A
P 6300 2350
F 0 "#PWR031" H 6300 2300 20  0001 C CNN
F 1 "+BATT" H 6303 2488 30  0000 C CNN
F 2 "" H 6300 2350 60  0000 C CNN
F 3 "" H 6300 2350 60  0000 C CNN
	1    6300 2350
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR032
U 1 1 5948E952
P 6325 3875
F 0 "#PWR032" H 6325 3825 20  0001 C CNN
F 1 "+BATT" H 6328 4013 30  0000 C CNN
F 2 "" H 6325 3875 60  0000 C CNN
F 3 "" H 6325 3875 60  0000 C CNN
	1    6325 3875
	1    0    0    -1  
$EndComp
Text Notes 7150 4975 0    63   ~ 13
1.3V Regulator
$Comp
L GND #PWR033
U 1 1 5948EA7B
P 7500 5800
F 0 "#PWR033" H 7500 5550 50  0001 C CNN
F 1 "GND" H 7505 5627 50  0000 C CNN
F 2 "" H 7500 5800 60  0000 C CNN
F 3 "" H 7500 5800 60  0000 C CNN
	1    7500 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 5948EA81
P 6350 5800
F 0 "#PWR034" H 6350 5550 50  0001 C CNN
F 1 "GND" H 6355 5627 50  0000 C CNN
F 2 "" H 6350 5800 60  0000 C CNN
F 3 "" H 6350 5800 60  0000 C CNN
	1    6350 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 5948EA87
P 8750 5800
F 0 "#PWR035" H 8750 5550 50  0001 C CNN
F 1 "GND" H 8755 5627 50  0000 C CNN
F 2 "" H 8750 5800 60  0000 C CNN
F 3 "" H 8750 5800 60  0000 C CNN
	1    8750 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 5275 6350 5550
Wire Wire Line
	6350 5350 7050 5350
Connection ~ 6350 5350
Wire Wire Line
	7050 5500 6950 5500
Wire Wire Line
	6350 5750 6350 5800
Wire Wire Line
	7500 5800 7500 5700
Wire Wire Line
	7950 5350 9550 5350
Wire Wire Line
	8750 5625 8750 5800
Wire Wire Line
	8750 5425 8750 5350
Connection ~ 8750 5350
$Comp
L AP2210K-ADJ U4
U 1 1 5948EAA0
P 7500 5400
F 0 "U4" H 7500 5694 40  0000 C CNN
F 1 "AP2210K-ADJ" H 7500 5618 40  0000 C CNN
F 2 "Applidyne_SOT:SOT95P280X145-5L30N" H 7200 5600 35  0001 L CIN
F 3 "http://docs-asia.electrocomponents.com/webdocs/1332/0900766b8133217a.pdf" H 7500 4250 60  0001 C CNN
F 4 "DIODES ZETEX" H 7500 4750 60  0001 C CNN "manf"
F 5 "AP2210K-ADJTRG1" H 7500 4650 60  0001 C CNN "manf#"
F 6 "RS Online" H 7500 4550 60  0001 C CNN "Supplier"
F 7 "828-7422" H 7500 4450 60  0001 C CNN "Supplier Part No"
F 8 "http://au.rs-online.com/web/p/low-dropout-voltage-regulators/8287422/" H 7500 4350 60  0001 C CNN "Supplier URL"
F 9 "0.272" H 7500 4150 60  0001 C CNN "Supplier Price"
F 10 "100" H 7500 4050 60  0001 C CNN "Supplier Price Break"
	1    7500 5400
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR036
U 1 1 5948EAA6
P 6350 5275
F 0 "#PWR036" H 6350 5225 20  0001 C CNN
F 1 "+BATT" H 6353 5413 30  0000 C CNN
F 2 "" H 6350 5275 60  0000 C CNN
F 3 "" H 6350 5275 60  0000 C CNN
	1    6350 5275
	1    0    0    -1  
$EndComp
$Comp
L 100K_1005M R7
U 1 1 5948EAFE
P 8200 5425
F 0 "R7" H 8273 5310 50  0000 L CNN
F 1 "100K_1005M" H 8273 5230 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 8310 5275 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1911175.pdf" V 8335 5275 20  0001 C CNN
F 4 "PANASONIC" V 8385 5275 20  0001 C CNN "manf"
F 5 "ERJ2RKF1003X" V 8410 5275 20  0001 C CNN "manf#"
F 6 "Element14" V 8435 5275 20  0001 C CNN "Supplier"
F 7 "2302839" V 8460 5275 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/erj2rkf1003x/res-thick-film-100k-1-0-1w-0402/dp/2302839" V 8485 5275 20  0001 C CNN "Supplier URL"
F 9 "0.016" V 8510 5275 20  0001 C CNN "Supplier Price"
F 10 "5" V 8535 5275 20  0001 C CNN "Supplier Price Break"
	1    8200 5425
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 5425 8200 5350
Connection ~ 8200 5350
Wire Wire Line
	8200 5725 8200 5825
Wire Wire Line
	8200 5775 8050 5775
Wire Wire Line
	8050 5775 8050 5500
Wire Wire Line
	8050 5500 7950 5500
Connection ~ 8200 5775
$Comp
L GND #PWR037
U 1 1 5948EC54
P 8200 6150
F 0 "#PWR037" H 8200 5900 50  0001 C CNN
F 1 "GND" H 8205 5977 50  0000 C CNN
F 2 "" H 8200 6150 60  0000 C CNN
F 3 "" H 8200 6150 60  0000 C CNN
	1    8200 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 6150 8200 6125
Wire Wire Line
	8175 4325 8175 4425
Wire Wire Line
	8175 4375 8025 4375
Wire Wire Line
	8025 4375 8025 4100
Wire Wire Line
	8025 4100 7925 4100
Connection ~ 8175 4375
$Comp
L GND #PWR038
U 1 1 5948ED24
P 8175 4750
F 0 "#PWR038" H 8175 4500 50  0001 C CNN
F 1 "GND" H 8180 4577 50  0000 C CNN
F 2 "" H 8175 4750 60  0000 C CNN
F 3 "" H 8175 4750 60  0000 C CNN
	1    8175 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8175 4750 8175 4725
Wire Wire Line
	8175 4025 8175 3950
Connection ~ 8175 3950
Wire Wire Line
	8150 2800 8150 2900
Wire Wire Line
	8150 2850 8000 2850
Wire Wire Line
	8000 2850 8000 2575
Wire Wire Line
	8000 2575 7900 2575
Connection ~ 8150 2850
$Comp
L GND #PWR039
U 1 1 5948EE42
P 8150 3225
F 0 "#PWR039" H 8150 2975 50  0001 C CNN
F 1 "GND" H 8155 3052 50  0000 C CNN
F 2 "" H 8150 3225 60  0000 C CNN
F 3 "" H 8150 3225 60  0000 C CNN
	1    8150 3225
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3225 8150 3200
Wire Wire Line
	8150 2500 8150 2425
Connection ~ 8150 2425
$Comp
L 2.2UF_X7R_1608M C19
U 1 1 5948F7B8
P 8750 5425
F 0 "C19" H 8828 5360 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 8828 5280 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 8865 5325 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 8890 5325 20  0001 C CNN
F 4 "MURATA" V 8940 5325 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 8965 5325 20  0001 C CNN "manf#"
F 6 "Element14" V 8990 5325 20  0001 C CNN "Supplier"
F 7 "2611925" V 9015 5325 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 9040 5325 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 9065 5325 20  0001 C CNN "Supplier Price"
F 10 "10" V 9090 5325 20  0001 C CNN "Supplier Price Break"
	1    8750 5425
	1    0    0    -1  
$EndComp
$Comp
L 2.2UF_X7R_1608M C18
U 1 1 5948F8D4
P 8725 4025
F 0 "C18" H 8803 3960 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 8803 3880 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 8840 3925 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 8865 3925 20  0001 C CNN
F 4 "MURATA" V 8915 3925 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 8940 3925 20  0001 C CNN "manf#"
F 6 "Element14" V 8965 3925 20  0001 C CNN "Supplier"
F 7 "2611925" V 8990 3925 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 9015 3925 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 9040 3925 20  0001 C CNN "Supplier Price"
F 10 "10" V 9065 3925 20  0001 C CNN "Supplier Price Break"
	1    8725 4025
	1    0    0    -1  
$EndComp
$Comp
L 2.2UF_X7R_1608M C17
U 1 1 5948F90C
P 8700 2500
F 0 "C17" H 8778 2435 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 8778 2355 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 8815 2400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 8840 2400 20  0001 C CNN
F 4 "MURATA" V 8890 2400 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 8915 2400 20  0001 C CNN "manf#"
F 6 "Element14" V 8940 2400 20  0001 C CNN "Supplier"
F 7 "2611925" V 8965 2400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 8990 2400 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 9015 2400 20  0001 C CNN "Supplier Price"
F 10 "10" V 9040 2400 20  0001 C CNN "Supplier Price Break"
	1    8700 2500
	1    0    0    -1  
$EndComp
$Comp
L 2.2UF_X7R_1608M C15
U 1 1 5948F9E4
P 6325 4150
F 0 "C15" H 6403 4085 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 6403 4005 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 6440 4050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 6465 4050 20  0001 C CNN
F 4 "MURATA" V 6515 4050 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 6540 4050 20  0001 C CNN "manf#"
F 6 "Element14" V 6565 4050 20  0001 C CNN "Supplier"
F 7 "2611925" V 6590 4050 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 6615 4050 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 6640 4050 20  0001 C CNN "Supplier Price"
F 10 "10" V 6665 4050 20  0001 C CNN "Supplier Price Break"
	1    6325 4150
	1    0    0    -1  
$EndComp
$Comp
L 2.2UF_X7R_1608M C16
U 1 1 5948FA28
P 6350 5550
F 0 "C16" H 6428 5485 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 6428 5405 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 6465 5450 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 6490 5450 20  0001 C CNN
F 4 "MURATA" V 6540 5450 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 6565 5450 20  0001 C CNN "manf#"
F 6 "Element14" V 6590 5450 20  0001 C CNN "Supplier"
F 7 "2611925" V 6615 5450 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 6640 5450 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 6665 5450 20  0001 C CNN "Supplier Price"
F 10 "10" V 6690 5450 20  0001 C CNN "Supplier Price Break"
	1    6350 5550
	1    0    0    -1  
$EndComp
$Comp
L 2.2UF_X7R_1608M C14
U 1 1 5948FA6B
P 6300 2500
F 0 "C14" H 6378 2435 50  0000 L CNN
F 1 "2.2UF_X7R_1608M" H 6378 2355 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1608X90L" V 6415 2400 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2079169.pdf?_ga=1.116328000.774814437.1442284889" V 6440 2400 20  0001 C CNN
F 4 "MURATA" V 6490 2400 20  0001 C CNN "manf"
F 5 "GRM188R61H225KE11D" V 6515 2400 20  0001 C CNN "manf#"
F 6 "Element14" V 6540 2400 20  0001 C CNN "Supplier"
F 7 "2611925" V 6565 2400 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/murata/grm188r61h225ke11d/cap-mlcc-x5r-2-2uf-50v-0603/dp/2611925" V 6590 2400 20  0001 C CNN "Supplier URL"
F 9 "0.0256" V 6615 2400 20  0001 C CNN "Supplier Price"
F 10 "10" V 6640 2400 20  0001 C CNN "Supplier Price Break"
	1    6300 2500
	1    0    0    -1  
$EndComp
Text GLabel 6950 5500 0    60   Input ~ 0
PWR_EN
Text GLabel 6925 4100 0    60   Input ~ 0
PWR_EN
Text Notes 9775 5425 0    60   ~ 0
Aims for 1.295V
Text Notes 9800 4175 0    60   ~ 0
Aims for 2.744V
Text Notes 9775 2675 0    60   ~ 0
Aims for 3.259V
$Comp
L 47K_1005M R5
U 1 1 59495399
P 8175 4025
F 0 "R5" H 8248 3910 50  0000 L CNN
F 1 "47K_1005M" H 8248 3830 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 8285 3875 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2167052.pdf" V 8310 3875 20  0001 C CNN
F 4 "YAGEO" V 8360 3875 20  0001 C CNN "manf"
F 5 "RC0402FR-0747KL" V 8385 3875 20  0001 C CNN "manf#"
F 6 "Element14" V 8410 3875 20  0001 C CNN "Supplier"
F 7 "9239430" V 8435 3875 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/yageo-phycomp/rc0402fr-0747kl/res-thick-film-47k-1-0-063w-0402/dp/9239430" V 8460 3875 20  0001 C CNN "Supplier URL"
F 9 "0.003" V 8485 3875 20  0001 C CNN "Supplier Price"
F 10 "10" V 8510 3875 20  0001 C CNN "Supplier Price Break"
	1    8175 4025
	1    0    0    -1  
$EndComp
$Comp
L 56K2_1005M R6
U 1 1 59495584
P 8175 4425
F 0 "R6" H 8248 4310 50  0000 L CNN
F 1 "56K2_1005M" H 8248 4230 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 8285 4275 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2052875.pdf" V 8310 4275 20  0001 C CNN
F 4 "PANASONIC" V 8360 4275 20  0001 C CNN "manf"
F 5 "ERA2AEB5622X" V 8385 4275 20  0001 C CNN "manf#"
F 6 "Element14" V 8410 4275 20  0001 C CNN "Supplier"
F 7 "2563631" V 8435 4275 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/era2aeb5622x/res-aec-q200-thin-film-56k2-0402/dp/2563631" V 8460 4275 20  0001 C CNN "Supplier URL"
F 9 "0.318" V 8485 4275 20  0001 C CNN "Supplier Price"
F 10 "100" V 8510 4275 20  0001 C CNN "Supplier Price Break"
	1    8175 4425
	1    0    0    -1  
$EndComp
$Comp
L 51K_1005M R3
U 1 1 5949707D
P 8150 2500
F 0 "R3" H 8223 2385 50  0000 L CNN
F 1 "51K_1005M" H 8223 2305 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 8260 2350 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2052875.pdf" V 8285 2350 20  0001 C CNN
F 4 "PANASONIC" V 8335 2350 20  0001 C CNN "manf"
F 5 "ERA2AEB513X" V 8360 2350 20  0001 C CNN "manf#"
F 6 "Element14" V 8385 2350 20  0001 C CNN "Supplier"
F 7 "2324790" V 8410 2350 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/era2aeb513x/res-metal-film-51k-0-1-0-063w/dp/2324790" V 8435 2350 20  0001 C CNN "Supplier URL"
F 9 "0.3" V 8460 2350 20  0001 C CNN "Supplier Price"
F 10 "100" V 8485 2350 20  0001 C CNN "Supplier Price Break"
	1    8150 2500
	1    0    0    -1  
$EndComp
$Comp
L 82K_1005M R4
U 1 1 59497EAB
P 8150 2900
F 0 "R4" H 8223 2785 50  0000 L CNN
F 1 "82K_1005M" H 8223 2705 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 8260 2750 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2059623.pdf" V 8285 2750 20  0001 C CNN
F 4 "PANASONIC" V 8335 2750 20  0001 C CNN "manf"
F 5 "ERJ2GEJ823X" V 8360 2750 20  0001 C CNN "manf#"
F 6 "Element14" V 8385 2750 20  0001 C CNN "Supplier"
F 7 "2324353" V 8410 2750 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/erj2gej823x/res-thick-film-82k-5-0-1w-0402/dp/2324353" V 8435 2750 20  0001 C CNN "Supplier URL"
F 9 "0.012" V 8460 2750 20  0001 C CNN "Supplier Price"
F 10 "100" V 8485 2750 20  0001 C CNN "Supplier Price Break"
	1    8150 2900
	1    0    0    -1  
$EndComp
$Comp
L 3K6_1005M R8
U 1 1 59498FB3
P 8200 5825
F 0 "R8" H 8273 5710 50  0000 L CNN
F 1 "3K6_1005M" H 8273 5630 35  0000 L CNN
F 2 "Applidyne_Resistor:RESC1005X40N" V 8310 5675 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2059623.pdf" V 8335 5675 20  0001 C CNN
F 4 "PANASONIC" V 8385 5675 20  0001 C CNN "manf"
F 5 "ERJ2GEJ362X" V 8410 5675 20  0001 C CNN "manf#"
F 6 "Element14" V 8435 5675 20  0001 C CNN "Supplier"
F 7 "2324307" V 8460 5675 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/panasonic-electronic-components/erj2gej362x/res-thick-film-3k6-5-0-1w-0402/dp/2324307" V 8485 5675 20  0001 C CNN "Supplier URL"
F 9 "0.01" V 8510 5675 20  0001 C CNN "Supplier Price"
F 10 "100" V 8535 5675 20  0001 C CNN "Supplier Price Break"
	1    8200 5825
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR040
U 1 1 594EBD75
P 3125 2650
F 0 "#PWR040" H 3125 2400 50  0001 C CNN
F 1 "GND" V 3130 2522 50  0000 R CNN
F 2 "" H 3125 2650 60  0000 C CNN
F 3 "" H 3125 2650 60  0000 C CNN
	1    3125 2650
	0    -1   -1   0   
$EndComp
$Comp
L +BATT #PWR041
U 1 1 594EBEB7
P 2850 2450
F 0 "#PWR041" H 2850 2400 20  0001 C CNN
F 1 "+BATT" H 2853 2588 30  0000 C CNN
F 2 "" H 2850 2450 60  0000 C CNN
F 3 "" H 2850 2450 60  0000 C CNN
	1    2850 2450
	1    0    0    -1  
$EndComp
Text GLabel 2600 2850 2    60   Input ~ 0
UART_TX
Text GLabel 2600 2750 2    60   Output ~ 0
UART_RX
Wire Wire Line
	2450 2550 2850 2550
Wire Wire Line
	2850 2550 2850 2450
Wire Wire Line
	3125 2650 2450 2650
Wire Wire Line
	2600 2750 2450 2750
Wire Wire Line
	2450 2850 2600 2850
Text Notes 1500 2150 0    60   ~ 0
This mimics the 2mm pitch of the adafruit VC0706\nmodule. Unsure if this should attempt to be pin-compatible or not...
$Comp
L CONN_01X08 P1
U 1 1 5961CC25
P 2250 2900
F 0 "P1" H 2328 2986 50  0000 L CNN
F 1 "CONN_01X08" H 2328 2895 50  0000 L CNN
F 2 "Applidyne_Header:Socket_Strip_Straight_1x08" H 2328 2804 50  0001 L CNN
F 3 "" H 2250 2900 50  0000 C CNN
	1    2250 2900
	-1   0    0    -1  
$EndComp
Text GLabel 2600 3050 2    60   Input ~ 0
FLASH_DAC
Text GLabel 2600 3250 2    60   BiDi ~ 0
EXP_1
Text GLabel 2600 3150 2    60   BiDi ~ 0
EXP_0
Text Notes 3250 3100 0    60   ~ 0
DAC output pin is also timer and ADC capable.
Text Notes 3250 3250 0    60   ~ 0
EXP pins are generic I/O (and also CAN pins)
Wire Wire Line
	2600 3050 2450 3050
Wire Wire Line
	2600 3150 2450 3150
Wire Wire Line
	2600 3250 2450 3250
Wire Wire Line
	2450 2950 3125 2950
$Comp
L GND #PWR042
U 1 1 59686534
P 3125 2950
F 0 "#PWR042" H 3125 2700 50  0001 C CNN
F 1 "GND" V 3130 2822 50  0000 R CNN
F 2 "" H 3125 2950 60  0000 C CNN
F 3 "" H 3125 2950 60  0000 C CNN
	1    3125 2950
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
