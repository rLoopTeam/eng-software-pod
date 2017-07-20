/**
 * @file		RM4_CPULOAD__LOCALDEF.H
 * @brief		Localdef template for RM4 CPU Load Module
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM663R0.FILE.002
 */

#if 0

/*******************************************************************************
SIl3 - RM48 - CPU LOAD MEASUREMENT
*******************************************************************************/
	#define C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

		/** The filtering size for the percentage trend */
		#define C_LOCALDEF__LCCM663__FILTER_WINDOW							(8U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM663__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <RM4/LCCM663__RM4__CPU_LOAD/rm4_cpuload.h>
	#endif //#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

#endif //#if 0

