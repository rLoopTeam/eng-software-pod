/**
 * @file		DP83640__LOCALDEF.H
 * @brief		Localdef Template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM515R0.FILE.003
 */

#if 0

/*******************************************************************************
DP83640 - Ethernet PHY with IEE1588
*******************************************************************************/
	#define C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U

		/** CPU Architecture */
		#define C_LOCALDEF__LCCM515__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM515__USE_ON_XILINX							(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM515__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM515__MULTICORE__DP83640/dp83640.h>

	#endif //#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U


#endif //#if 0

