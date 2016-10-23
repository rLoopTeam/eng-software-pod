/**
 * @file		rm4_flash__localdef.h
 * @brief		FLASH Local def template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @st_fileID	LCCM135R0.FILE.003
 */
#if 0

/*******************************************************************************
FLASH MODULE
Even if you don't want in system programming or firmware update features
include this to get access to the flash registers and setup features
*******************************************************************************/
	#define C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U

		//enable F021
		#define C_LOCALDEF__LCCM135__ENABLE_F021							(1U)

		//testing options
		#define C_LOCALDEF__LCCM135__ENABLE_TEST_SPEC						(0U)

		#include <RM4/LCCM135__RM4__FLASH/rm4_flash.h>

	#endif //#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U



#endif //0


