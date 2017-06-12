/**
 * @file		rm4_system__localdef.h
 * @brief		Localdef template for the core of the system
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM219R0.FILE.003
 */

#if 0

/*******************************************************************************
RM4 MAIN SYSTEM SETUP
Place this at the top of your Localdef file
Change the build settings:
1. Enable GCC extensions under advanced options -> language options
2. Enable unaligned loads and stores to on
3. Make sure designate enum type is packed.

*******************************************************************************/
	/*lint -e950 */
	/*lint -e621 */
	#include "sil3_generic__cpu.h"

	//data types
	#include <RM4/LCCM105__RM4__BASIC_TYPES/basic_types.h>

	//set this to 1 to disable all common startups as would be used by a bootloader
	#define C_LOCALDEF__SYSTEM__DISABLE_ALL_FOR_BOOTLOADER					(0U)

	//change osc freq to match the osc on your board
	//valid values are 10 and 16MHZ
	#define C_LOCALDEF__SYSTEM__OSCILLATOR_FREQ     						(16000000U)

	//This is the HCLK frequency, it is not defined here, but is a result of the
	//PLL1 setup.  Standard range is 200MHZ to 220MHZ (952 part)
	//Valid Is:
	//300 (RM57 ONLY)
	//220
	//200 (Standard)
	//150 (Low Power) OR RM57
	//100 (Low Power)
	#define C_LOCALDEF__SYSTEM__HCLK_FREQ_MHZ								(200U)

	//normal bus division is either 1 or 2
	//In 1x mode, VCLK1 is 100MHZ, in 2x mode VCLK is 50MHZ
	//you may only need 2x mode if you need ultra lo SPI comms, etc.
	//Needs to be 2 on RM57
	#define C_LOCALDEF__SYSTEM__VCLK1_DIVISOR								(1U)


	//just here because of no EMIF
	//if ou are using EMIF, then remove this line
	#define C_LOCALDEF__LCCM107__EMIF_CLOCK_DIVISOR							(1U)


	//we have the ability to use the ECLK pin to generate a high frequency divided
	//clock signal, possibly faster than we can do with PWM
	#define C_LOCALDEF__SYSTEM__ENABLE_ECLK									(0U)

	//The divisor is VCLK1 /x so a value of 40x = 2.5MHZ ECLK
	#define C_LOCALDEF__SYSTEM__ECLK_DIVISOR								(40U)

	//other includes
	#include <RM4/LCCM219__RM4__SYSTEM/rm4_system.h>

	#if C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U
		#include <RM57/LCCM704__RM57__COMMON/HL_system.h>
	#endif


	#include <RM4/LCCM364__RM4__FIRMWARE_VERSION/rm4_firmware_version.h>


#endif //0
