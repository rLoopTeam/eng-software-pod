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

void vAMC7812_WIN32__Set_DACVoltsCallback(pAMC7812_WIN32__DACVoltsCallback_FuncType pFunc)
{
	 m_pAMC7812_WIN32__DACVolts = pFunc;
}

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

