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
Text Notes 8825 3125 0    118  ~ 24
Mounting Holes
Text Notes 9175 1875 0    118  ~ 24
Fiducials
Text Notes 8700 4400 0    118  ~ 24
Logos and Markings
$Comp
L FIDUCIAL FID2
U 1 1 5891D98F
P 9475 2425
F 0 "FID2" H 9628 2469 47  0000 L CNN
F 1 "FIDUCIAL" H 9628 2382 47  0000 L CNN
F 2 "Applidyne_Fiducial:FID100X300" H 9475 2600 47  0001 C CNN
F 3 "" H 9475 2425 60  0000 C CNN
	1    9475 2425
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID3
U 1 1 5891D9E3
P 10150 2425
F 0 "FID3" H 10303 2469 47  0000 L CNN
F 1 "FIDUCIAL" H 10303 2382 47  0000 L CNN
F 2 "Applidyne_Fiducial:FID100X300" H 10150 2600 47  0001 C CNN
F 3 "" H 10150 2425 60  0000 C CNN
	1    10150 2425
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID1
U 1 1 5891DA17
P 8725 2425
F 0 "FID1" H 8878 2469 47  0000 L CNN
F 1 "FIDUCIAL" H 8878 2382 47  0000 L CNN
F 2 "Applidyne_Fiducial:FID100X300" H 8725 2600 47  0001 C CNN
F 3 "" H 8725 2425 60  0000 C CNN
	1    8725 2425
	1    0    0    -1  
$EndComp
Text Notes 5500 4100 0    118  ~ 24
MicroSD Card
$Comp
L MOLEX_104031-0811 CON1
U 1 1 58BB720F
P 5325 5400
F 0 "CON1" H 6155 5316 50  0000 L CNN
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
Text GLabel 2175 6100 0    60   Input ~ 0
MICROSD_D1
Text GLabel 2175 5800 0    60   Input ~ 0
MICROSD_D0
Text GLabel 2175 4575 0    60   Input ~ 0
MICROSD_D2
Text GLabel 2175 6425 0    60   Input ~ 0
MICROSD_DETECT
Text GLabel 2175 4875 0    60   Input ~ 0
MICROSD_D3
Text GLabel 2175 5500 0    60   Input ~ 0
MICROSD_CK
Text GLabel 2175 5175 0    60   Input ~ 0
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
L GND #PWR99
U 1 1 58BD4B91
P 4925 6475
F 0 "#PWR99" H 4925 6225 50  0001 C CNN
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
L GND #PWR100
U 1 1 58BD4CFB
P 5675 6475
F 0 "#PWR100" H 5675 6225 50  0001 C CNN
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
L GND #PWR98
U 1 1 58CA2FF4
P 4325 6475
F 0 "#PWR98" H 4325 6225 50  0001 C CNN
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
L +3.3V #PWR97
U 1 1 58CA30F9
P 4325 4800
F 0 "#PWR97" H 4325 4760 30  0001 C CNN
F 1 "+3.3V" H 4334 4938 30  0000 C CNN
F 2 "" H 4325 4800 60  0000 C CNN
F 3 "" H 4325 4800 60  0000 C CNN
	1    4325 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR101
U 1 1 58CECAEE
P 7200 5075
F 0 "#PWR101" H 7200 5035 30  0001 C CNN
F 1 "+3.3V" H 7209 5213 30  0000 C CNN
F 2 "" H 7200 5075 60  0000 C CNN
F 3 "" H 7200 5075 60  0000 C CNN
	1    7200 5075
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR102
U 1 1 58CECB3C
P 7200 5925
F 0 "#PWR102" H 7200 5675 50  0001 C CNN
F 1 "GND" H 7205 5752 50  0000 C CNN
F 2 "" H 7200 5925 60  0000 C CNN
F 3 "" H 7200 5925 60  0000 C CNN
	1    7200 5925
	1    0    0    -1  
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R25
U 4 1 58EEEF72
P 2825 4575
F 0 "R25" V 2725 4425 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 4425 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 4425 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 4425 20  0001 C CNN
F 4 "BOURNS" V 3115 4425 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 4425 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 4425 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 4425 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 4425 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 4425 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 4425 20  0001 C CNN "Supplier Price Break"
	4    2825 4575
	0    1    1    0   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R30
U 1 1 58EEF041
P 2825 4875
F 0 "R30" V 2725 4725 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 4725 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 4725 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 4725 20  0001 C CNN
F 4 "BOURNS" V 3115 4725 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 4725 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 4725 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 4725 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 4725 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 4725 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 4725 20  0001 C CNN "Supplier Price Break"
	1    2825 4875
	0    1    1    0   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R31
U 3 1 58EEF320
P 2825 6975
F 0 "R31" V 2725 6825 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 6825 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 6825 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 6825 20  0001 C CNN
F 4 "BOURNS" V 3115 6825 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 6825 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 6825 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 6825 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 6825 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 6825 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 6825 20  0001 C CNN "Supplier Price Break"
	3    2825 6975
	0    1    1    0   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R31
U 1 1 58EEF3A2
P 2825 6100
F 0 "R31" V 2725 5950 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 5950 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 5950 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 5950 20  0001 C CNN
F 4 "BOURNS" V 3115 5950 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 5950 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 5950 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 5950 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 5950 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 5950 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 5950 20  0001 C CNN "Supplier Price Break"
	1    2825 6100
	0    1    1    0   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R30
U 4 1 58EEF429
P 2825 5800
F 0 "R30" V 2725 5650 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 5650 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 5650 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 5650 20  0001 C CNN
F 4 "BOURNS" V 3115 5650 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 5650 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 5650 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 5650 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 5650 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 5650 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 5650 20  0001 C CNN "Supplier Price Break"
	4    2825 5800
	0    1    1    0   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R30
U 2 1 58EEF493
P 2825 5175
F 0 "R30" V 2725 5025 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 5025 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 5025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 5025 20  0001 C CNN
F 4 "BOURNS" V 3115 5025 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 5025 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 5025 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 5025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 5025 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 5025 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 5025 20  0001 C CNN "Supplier Price Break"
	2    2825 5175
	0    1    1    0   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R31
U 2 1 58EEF53F
P 2825 6425
F 0 "R31" V 2725 6275 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 6275 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 6275 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 6275 20  0001 C CNN
F 4 "BOURNS" V 3115 6275 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 6275 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 6275 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 6275 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 6275 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 6275 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 6275 20  0001 C CNN "Supplier Price Break"
	2    2825 6425
	0    1    1    0   
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
	2525 6425 2175 6425
Wire Wire Line
	2525 6100 2175 6100
Wire Wire Line
	2525 5800 2175 5800
Wire Wire Line
	2525 5500 2175 5500
Wire Wire Line
	2525 5175 2175 5175
Wire Wire Line
	2525 4875 2175 4875
Wire Wire Line
	2525 4575 2175 4575
$Comp
L 1K_QUAD_ARRAY_1608M R34
U 1 1 58EF33D1
P 3375 4175
F 0 "R34" V 3275 4025 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 3475 4025 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3590 4025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3615 4025 20  0001 C CNN
F 4 "BOURNS" V 3665 4025 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3690 4025 20  0001 C CNN "manf#"
F 6 "Element14" V 3715 4025 20  0001 C CNN "Supplier"
F 7 "1770133" V 3740 4025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3765 4025 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3790 4025 20  0001 C CNN "Supplier Price"
F 10 "50" V 3815 4025 20  0001 C CNN "Supplier Price Break"
	1    3375 4175
	-1   0    0    1   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R34
U 2 1 58EF343D
P 3725 4175
F 0 "R34" V 3625 4025 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 3825 4025 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3940 4025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3965 4025 20  0001 C CNN
F 4 "BOURNS" V 4015 4025 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 4040 4025 20  0001 C CNN "manf#"
F 6 "Element14" V 4065 4025 20  0001 C CNN "Supplier"
F 7 "1770133" V 4090 4025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 4115 4025 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 4140 4025 20  0001 C CNN "Supplier Price"
F 10 "50" V 4165 4025 20  0001 C CNN "Supplier Price Break"
	2    3725 4175
	-1   0    0    1   
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R34
U 3 1 58EF34D0
P 4075 4175
F 0 "R34" V 3975 4025 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 4175 4025 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 4290 4025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 4315 4025 20  0001 C CNN
F 4 "BOURNS" V 4365 4025 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 4390 4025 20  0001 C CNN "manf#"
F 6 "Element14" V 4415 4025 20  0001 C CNN "Supplier"
F 7 "1770133" V 4440 4025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 4465 4025 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 4490 4025 20  0001 C CNN "Supplier Price"
F 10 "50" V 4515 4025 20  0001 C CNN "Supplier Price Break"
	3    4075 4175
	-1   0    0    1   
$EndComp
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
$Comp
L 1K_QUAD_ARRAY_1608M R31
U 4 1 58EFCF80
P 3025 4175
F 0 "R31" V 2925 4025 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 3125 4025 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3240 4025 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3265 4025 20  0001 C CNN
F 4 "BOURNS" V 3315 4025 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3340 4025 20  0001 C CNN "manf#"
F 6 "Element14" V 3365 4025 20  0001 C CNN "Supplier"
F 7 "1770133" V 3390 4025 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3415 4025 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3440 4025 20  0001 C CNN "Supplier Price"
F 10 "50" V 3465 4025 20  0001 C CNN "Supplier Price Break"
	4    3025 4175
	-1   0    0    1   
$EndComp
Wire Wire Line
	4075 3875 4075 3675
Wire Wire Line
	3725 3875 3725 3675
Wire Wire Line
	3375 3675 3375 3875
Wire Wire Line
	3025 3875 3025 3675
$Comp
L +3.3V #PWR96
U 1 1 58EFD597
P 4075 3675
F 0 "#PWR96" H 4075 3635 30  0001 C CNN
F 1 "+3.3V" H 4084 3813 30  0000 C CNN
F 2 "" H 4075 3675 60  0000 C CNN
F 3 "" H 4075 3675 60  0000 C CNN
	1    4075 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR95
U 1 1 58EFD61A
P 3725 3675
F 0 "#PWR95" H 3725 3635 30  0001 C CNN
F 1 "+3.3V" H 3734 3813 30  0000 C CNN
F 2 "" H 3725 3675 60  0000 C CNN
F 3 "" H 3725 3675 60  0000 C CNN
	1    3725 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR92
U 1 1 58EFD69D
P 3375 3675
F 0 "#PWR92" H 3375 3635 30  0001 C CNN
F 1 "+3.3V" H 3384 3813 30  0000 C CNN
F 2 "" H 3375 3675 60  0000 C CNN
F 3 "" H 3375 3675 60  0000 C CNN
	1    3375 3675
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR91
U 1 1 58EFD720
P 3025 3675
F 0 "#PWR91" H 3025 3635 30  0001 C CNN
F 1 "+3.3V" H 3034 3813 30  0000 C CNN
F 2 "" H 3025 3675 60  0000 C CNN
F 3 "" H 3025 3675 60  0000 C CNN
	1    3025 3675
	1    0    0    -1  
$EndComp
$Comp
L 1K_QUAD_ARRAY_1608M R30
U 3 1 58F0153F
P 2825 5500
F 0 "R30" V 2725 5350 50  0000 C CNN
F 1 "1K_QUAD_ARRAY_1608M" V 2925 5350 35  0000 C CNN
F 2 "Applidyne_Resistor:R_Array_Concave_4x1608M" V 3040 5350 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1885635.pdf" V 3065 5350 20  0001 C CNN
F 4 "BOURNS" V 3115 5350 20  0001 C CNN "manf"
F 5 "CAY16-102J4LF" V 3140 5350 20  0001 C CNN "manf#"
F 6 "Element14" V 3165 5350 20  0001 C CNN "Supplier"
F 7 "1770133" V 3190 5350 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/bourns/cay16-102j4lf/resistor-array-4-1k-1206-5-smd/dp/1770133?CMP=GRHB-OCTOPART" V 3215 5350 20  0001 C CNN "Supplier URL"
F 9 "0.073" V 3240 5350 20  0001 C CNN "Supplier Price"
F 10 "50" V 3265 5350 20  0001 C CNN "Supplier Price Break"
	3    2825 5500
	0    1    1    0   
$EndComp
NoConn ~ 2825 6975
NoConn ~ 2525 6975
$Comp
L 100NF_X7R_1005M C45
U 1 1 594348C8
P 7200 5400
F 0 "C45" H 7278 5335 50  0000 L CNN
F 1 "100NF_X7R_1005M" H 7278 5255 35  0000 L CNN
F 2 "Applidyne_Capacitor:CAPC1005X60N" V 7315 5300 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1936565.pdf" V 7340 5300 20  0001 C CNN
F 4 "TDK" V 7390 5300 20  0001 C CNN "manf"
F 5 "CGA2B3X7R1H104K050BB" V 7415 5300 20  0001 C CNN "manf#"
F 6 "Element14" V 7440 5300 20  0001 C CNN "Supplier"
F 7 "2210822" V 7465 5300 20  0001 C CNN "Supplier Part No"
F 8 "http://au.element14.com/tdk/cga2b3x7r1h104k050bb/cap-mlcc-x7r-100nf-50v-0402/dp/2210822" V 7490 5300 20  0001 C CNN "Supplier URL"
F 9 "0.087" V 7515 5300 20  0001 C CNN "Supplier Price"
F 10 "100" V 7540 5300 20  0001 C CNN "Supplier Price Break"
	1    7200 5400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
