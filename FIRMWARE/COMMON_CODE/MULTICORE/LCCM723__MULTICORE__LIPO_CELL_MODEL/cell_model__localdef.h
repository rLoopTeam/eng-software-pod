/**
 * @file		CELL_MODEL__LOCALDEF.H
 * @brief		Localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM723R0.FILE.002
 */

#if 0

/*******************************************************************************
LIPO CELL MODEL
*******************************************************************************/
	#define C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

		/** Define the maximum time size in seconds */
		#define C_LOCALDEF__LCCM723__MAX_TIME_SIZE							(600U)
	
	
		/** If you want to make a battery out of many cells, specify the
		number of cells, min is 1
		Number of cells * num Packs = total cells */
		#define C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK						(1U)
	
		/** If you want to make a parallel pack, set this to the number
		of cells in parallel, else 1*/
		#define C_LOCALDEF__LCCM723__NUM_PARALLEL							(1U)

		
		/** Number of individual battery packs */
		#define C_LOCALDEF__LCCM723__NUM_PACKS								(1U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM723__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <MULTICORE/LCCM723__MULTICORE__LIPO_CELL_MODEL/cell_model.h>
	#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

#endif //#if 0

