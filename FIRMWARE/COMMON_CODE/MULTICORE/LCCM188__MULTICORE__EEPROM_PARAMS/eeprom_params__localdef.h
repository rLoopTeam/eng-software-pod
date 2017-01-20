/**
 * @file		eeprom_params__localdef.h
 * @brief		eeprom parameters local defs
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM188R0.FILE.003
 */
#if 0

/*******************************************************************************
EEPROM BASIC PARAMETERS
*******************************************************************************/
	#define C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U
	
		//select your architecture
		#define C_LOCALDEF__LCCM188__USE_ON_PIC18							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_PIC32							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_DSPIC							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_RM4 							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_MSP430 							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_WIN32 							(0U)
	
		/** Use the EEPRARAMS module with an external FLASH */
		#define C_LOCALDEF__LCCM188__USE_WITH_LCCM013						(0U)
	
		/** Define the number of parameters in the system */
		#define C_LOCALDEF__LCCM188__NUM_PARAMETERS							(32U)
		
		/** set to 1 if you want to enable CRC's across the entire paramter
		range.  If so you will loose one paramter at the end to store theCRC
		*/
		#define C_LOCALDEF__LCCM188__ENABLE_CRC								(0U)
	
		/** Offset to start in memory */
		#define C_LOCALDEF__LCCM188__EEPROM_START_OFFSET					(0U)
	
		/** DISABLES */
		#define C_LOCALDEF__LCCM188__DISABLE__U16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__U32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__F32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__MAC							(0U)
	
		/** Specialised enabled */
		#define C_LOCALDEF__LCCM188__ENABLE_VECTORS							(0U)

		/** Testing options */
		#define C_LOCALDEF__LCCM188__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM188__MULTICORE__EEPROM_PARAMS/eeprom_params.h>
		
	#endif //C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE

#endif //0
