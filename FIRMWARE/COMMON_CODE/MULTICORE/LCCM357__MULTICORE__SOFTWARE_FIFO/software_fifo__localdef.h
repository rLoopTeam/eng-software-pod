/**
 * @file		software_fifo__localdef.h
 * @brief		Soft FIFO localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM357R0.FILE.003
 */


#if 0

/*******************************************************************************
GENERAL PURPOSE
SOFTWARE FIFO
*******************************************************************************/
	#define C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U
	
		/** Software FIFO depth size, U8 = 255 or U16 = 65K, not both */
		#define C_LOCALDEF__LCCM357__FIFO_DEPTH_U8							(1U)
		#define C_LOCALDEF__LCCM357__FIFO_DEPTH_U16							(0U)

		//testing options
		#define C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC						(0U)
	
		//main include file
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo.h>
	
	#endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE



#endif //0
