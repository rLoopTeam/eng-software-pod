/**
 * @file		AMC7812__LOWLEVEL.C
 * @brief		Lowlevel Interface
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.004
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__LOWLEVEL
 * @ingroup AMC7812
 * @{ */

#include "../amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

extern struct _strAMC7812 sAMC;

/***************************************************************************//**
 * @brief
 * Configure any low level items.
 * 
 * @st_funcMD5		8B4F90FD3EECFCB210D4EB16E704CDB1
 * @st_funcID		LCCM658R0.FILE.004.FUNC.001
 */
void vAMC7812_LOWLEVEL__Init(void)
{

#ifndef WIN32
	//reset line to output
	C_LOCALDEF__LCCM658__NRESET__TRIS(0U);
	C_LOCALDEF__LCCM658__NRESET__LATCH(0U);

	//reset the device
	//vAMC7812_LOWLEVEL__Reset();
#endif //WIN32
}


//generate the reset pulse
void vAMC7812_LOWLEVEL__Reset(void)
{
#ifndef WIN32
	//reset high
	C_LOCALDEF__LCCM658__NRESET__LATCH(1U);

	//delay
	vRM4_DELAYS__Delay_uS(100U);

	//reset
	C_LOCALDEF__LCCM658__NRESET__LATCH(0U);

	//reset low for a bit
	vRM4_DELAYS__Delay_uS(100U);

	//reset off.
	C_LOCALDEF__LCCM658__NRESET__LATCH(1U);

	//wait until ready
	vRM4_DELAYS__Delay_uS(100U);

#endif //win32
}


#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
