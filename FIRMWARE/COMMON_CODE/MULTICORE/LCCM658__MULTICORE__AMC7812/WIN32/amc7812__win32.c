/**
 * @file		AMC7812__WIN32.C
 * @brief		WIN32 Emulation Layer
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.003
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__WIN32
 * @ingroup AMC7812
 * @{ */

#include "../amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

pAMC7812_WIN32__DACVoltsCallback_FuncType m_pAMC7812_WIN32__DACVolts;

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		pFunc		## Desc ##
 * @st_funcMD5		8217A957A52EF51B2A5A1FC0C7003C09
 * @st_funcID		LCCM658R0.FILE.003.FUNC.001
 */
void vAMC7812_WIN32__Set_DACVoltsCallback(pAMC7812_WIN32__DACVoltsCallback_FuncType pFunc)
{
	 m_pAMC7812_WIN32__DACVolts = pFunc;
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		Lfloat32		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		EFA6DB1225AA0C17436AD45FA6380A35
 * @st_funcID		LCCM658R0.FILE.003.FUNC.002
 */
void vAMC7182_WIN32__DAC_SetVolage(Luint8 u8Channel, Lfloat32 f32Volts)
{
	m_pAMC7812_WIN32__DACVolts(u8Channel, f32Volts);
}

#endif //win32

#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

