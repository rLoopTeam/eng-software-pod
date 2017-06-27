/**
 * @file		rm4_eeprom__localdef.h
 * @brief		Localdefs for RM4 eeprom emulation
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM230R0.FILE.004
 */
#if 0

/*******************************************************************************
SIL3 - RM4 EEPROM EMULATION
You'll need the flash access module for this
*******************************************************************************/
	#define C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE							(1U)
 	 #if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM230__ENABLE_TEST_SPEC						(0U)

 	 	//main include
 	 	#include <RM4/LCCM230__RM4__EEPROM/rm4_eeprom.h>

 	 #endif //C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE


#endif //0
