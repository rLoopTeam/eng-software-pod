/**
 * @file		RM4_VIM__LOCALDEF.H
 * @brief		Localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM225R0.FILE.008
 */


#if 0

/*******************************************************************************
VECTORED INTERRUPT MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM225__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM225__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM225__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM225__RM4__VECTORED_ISR_MGR/rm4_vim.h>

	#endif //C_LOCALDEF__LCCM225__ENABLE_THIS_MODULE

#endif //0
