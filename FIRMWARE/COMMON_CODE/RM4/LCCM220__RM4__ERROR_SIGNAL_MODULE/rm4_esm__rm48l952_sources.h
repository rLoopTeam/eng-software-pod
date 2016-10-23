/**
 * @file		RM4_ESM__RM48L952_SOURCES.H
 * @brief		Error Sources
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @st_fileID	LCCM220R0.FILE.022
 */

#ifndef _RM4_ESM__RM48L952_SROUCES_H_
#define _RM4_ESM__RM48L952_SROUCES_H_
	/*
	Table 4-34. ESM Groups
	ERROR GROUP 		INTERRUPT CHARACTERISTICS 			INFLUENCE ON ERROR PIN
	Group1 				maskable, low or high priority 		configurable
	Group2 				non-maskable, high priority 		fixed
	Group3 				no interrupt generated 				fixed
	*/

	/*
	Table 4-35. ESM Channel Assignments
	ERROR SOURCES 					GROUP 				CHANNELS
	Reserved 						Group1 				0
	MibADC2 - parity 				Group1 				1
	DMA - MPU 						Group1 				2
	DMA - parity 					Group1 				3
	Reserved 						Group1 				4
	DMA/DMM - imprecise read error 	Group1 				5
	FMC - correctable error: 
	bus1 and bus2 interfaces 
	(does not include accesses to EEPROM bank) Group1 	6
	N2HET1/N2HET2 - parity 			Group1 				7
	HET TU1/HET TU2 - parity 		Group1 				8
	HET TU1/HET TU2 - MPU 			Group1 				9
	PLL - Slip 						Group1 				10
	Clock Monitor - interrupt 		Group1 				11
	Reserved 						Group1 				12
	DMA/DMM - imprecise write error Group1 				13
	Reserved 						Group1 14
	VIM RAM - parity 				Group1 15
	Reserved 						Group1 16
	MibSPI1 - parity 				Group1 17
	MibSPI3 - parity 				Group1 18
	MibADC1 - parity 				Group1 19
	Reserved 						Group1 20
	DCAN1 - parity 					Group1 21
	DCAN3 - parity 					Group1 22
	DCAN2 - parity 					Group1 23
	MibSPI5 - parity 				Group1 24
	Reserved 						Group1 25
	RAM even bank (B0TCM) - correctable error Group1 26
	CPU - selftest 					Group1 27
	RAM odd bank (B1TCM) - correctable error Group1 28
	Reserved 						Group1 29
	DCC1 - error 					Group1 30
	CCM-R4 - selftest 				Group1 31
	Reserved Group1 32
	Reserved Group1 33
	Reserved Group1 34
	FMC - correctable error (EEPROM bank access) Group1 35
	FMC - uncorrectable error (EEPROM bank access) Group1 36
	IOMM - Mux configuration error Group1 37
	Power domain controller compare error Group1 38
	Power domain controller self-test error Group1 39
	eFuse Controller Error � this error signal is generated when any bit in the eFuse
	controller error status register is set. The application can choose to generate an Group1 40
	interrupt whenever this bit is set to service any eFuse controller error conditions.
	eFuse Controller - Self Test Error. This error signal is generated only when a self
	test on the eFuse controller generates an error condition. When this error signal is Group1 41
	set, group 1 channel 40 error signal will also be set.
	PLL2 - Slip Group1 42
	Ethernet Controller master interface Group1 43
	USB Host Controller master interface Group1 44	
	DCC2 - error Group1 62
	Reserved Group1 63


	Reserved Group2 0
	Reserved Group2 1
	CCMR4 - compare Group2 2
	Reserved Group2 3
	FMC - uncorrectable error (address parity on bus1 accesses) Group2 4
	Reserved Group2 5
	RAM even bank (B0TCM) - uncorrectable error Group2 6
	Reserved Group2 7
	RAM odd bank (B1TCM) - uncorrectable error Group2 8
	Reserved Group2 9
	RAM even bank (B0TCM) - address bus parity error Group2 10
	Reserved Group2 11
	RAM odd bank (B1TCM) - address bus parity error Group2 12
	Reserved Group2 13
	Reserved Group2 14
	Reserved Group2 15
	Flash (ATCM) - ECC live lock detect Group2 16
	Reserved Group2 17
	Reserved Group2 18
	Reserved Group2 19
	Reserved Group2 20
	Reserved Group2 21
	Reserved Group2 22
	Reserved Group2 23
	RTI_WWD_NMI Group2 24
	Reserved Group2 25
	Reserved Group2 26
	Reserved Group2 27
	Reserved Group2 28
	Reserved Group2 29
	Reserved Group2 30
	Reserved Group2 31

	Reserved Group3 0
	eFuse Controller - autoload error Group3 1
	Reserved Group3 2
	RAM even bank (B0TCM) - ECC uncorrectable error Group3 3
	Reserved Group3 4
	RAM odd bank (B1TCM) - ECC uncorrectable error Group3 5
	Reserved Group3 6
	FMC - uncorrectable error: bus1 and bus2 interfaces (does not include address parity error and errors on accesses to EEPROM bank) Group3 7
	Reserved Group3 8
	Reserved Group3 9
	Reserved Group3 10
	Reserved Group3 11
	*/
	
	

#endif //_RM4_ESM__RM48L852_SROUCES_H_
