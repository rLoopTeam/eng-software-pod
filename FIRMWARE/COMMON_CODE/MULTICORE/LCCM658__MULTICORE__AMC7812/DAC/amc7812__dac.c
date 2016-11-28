/**
 * @file		AMC7812__DAC.C
 * @brief		DAC Portion of the device
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.007
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__DAC
 * @ingroup AMC7812
 * @{ */

#include "../amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

extern struct _strAMC7812_DAC strAMC7812_DAC;


/***************************************************************************//**
 * @brief
 * Init the DAC portion.
 * 
 * @st_funcMD5		C180710CF0A27FA75265B2D3FA81C0E7
 * @st_funcID		LCCM658R0.FILE.007.FUNC.001
 */
void vAMC7812_DAC__Init(void)
{

	//structure init
	strAMC7812_DAC.eState = AMC7812_DAC_STATE__INIT_DEVICE;
	strAMC7812_DAC.u32LoopCounter = 0U;

}




#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

