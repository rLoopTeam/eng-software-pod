/**
 * @file		rm4_delays__localdef.h
 * @brief		Localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM228R0.FILE.003
 */
#if 0

/*******************************************************************************
RM4 DELAY ROUTINES
*******************************************************************************/
	#define C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE == 1U

		//Testing options
		#define C_LOCALDEF__LCCM228__ENABLE_TEST_SPEC						(0U)

		//enable the PMU if needed
		#define C_LOCALDEF__LCCM288__ENABLE_PMU_FOR_DEBUG					(0U)

		//main include file
		#include <RM4/LCCM228__RM4__DELAYS/rm4_delays.h>

	#endif //C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE


#endif
