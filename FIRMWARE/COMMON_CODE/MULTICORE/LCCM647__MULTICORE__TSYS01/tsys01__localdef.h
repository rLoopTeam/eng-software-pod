/**
 * @file		TSYS01__LOCALDEF.H
 * @brief		Localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM647R0.FILE.002
 */

#if 0

/*******************************************************************************
TSYS01 - DIGITAL TEMP SENSOR
*******************************************************************************/
	#define C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

		/** The number of main program loops to wait for conversion */
		#define C_LOCALDEF__LCCM647__NUM_CONVERSION_LOOPS					(10000U)

		/** the I2C address on the bus */
		#define C_LOCALDEF__LCCM647__BUS_ADDX								(0x77U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM647__ENABLE_TEST_SPEC						(0U)

		/** Enable datasheet values to test math
		 * DO NOT put this in production */
		#define C_LOCALDEF__LCCM647__ENABLE_DS_VALUES						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>

	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

#endif //#if 0

