/**
 * @file		rm4_n2het1__localdef.h
 * @brief		Localdefs template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @st_fileID	LCCM240R0.FILE.003
 */
#if 0

/*******************************************************************************
RM4 High End Timers (HET)
General Configuration
HR Clock = 100MHZ
VCLK2 = 100Mhz, Actual HR Clock = 100MHZ
Loop Time = 100ns
LR Time = 160ns
*******************************************************************************/
	#define C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE							(1U)
 	 #if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U

		//Module Enables
		#define C_LOCALDEF__LCCM240__ENABLE_N2HET1							(1U)
		#define C_LOCALDEF__LCCM240__ENABLE_N2HET2							(0U)

		//enable interrupts or not
		#define C_LOCALDEF__LCCM240__ENABLE_INTERRUPTS						(0U)


		//HET Options
		#define C_LOCALDEF__LCCM240__ENABLE_INPUT_CAPTURE					(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_EDGE_CAPTURE					(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_PWM								(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_TIMESTAMPING					(0U)

		//testing
		#define C_LOCALDEF__LCCM240__ENABLE_TEST_SPEC						(0U)

 	 	//main include
 	 	#include <RM4/LCCM240__RM4__N2HET/rm4_n2het.h>

 	 #endif //C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE

#endif //0
