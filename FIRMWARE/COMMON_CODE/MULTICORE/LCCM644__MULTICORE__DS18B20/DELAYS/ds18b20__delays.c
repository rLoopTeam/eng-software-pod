/**
 * @file		DS18B20__DELAYS.C
 * @brief		Interface for delays
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.008
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20__DELAYS
 * @ingroup DS18B20
 * @{ */

#include "../ds18b20.h"
#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

/***************************************************************************//**
 * @brief
 * microsecond delay.
 * 
 * @param[in]		u32Value				Delay Value
 * @st_funcMD5		49782D0D32EAE7FA4DE6100C744D6566
 * @st_funcID		LCCM644R0.FILE.008.FUNC.001
 */
void vDS18B20_DELAYS__Delay_uS(Luint32 u32Value)
{
	#if C_LOCALDEF__LCCM644__USE_ON_RM4 == 1U
		vRM4_DELAYS__Delay_uS(u32Value);
	#elif C_LOCALDEF__LCCM644__USE_ON_XILINX == 1U
		vXILINX_DELAYS__Delay_uS(u32Value);
	#elif C_LOCALDEF__LCCM644__USE_ON_MSP430 == 1U
		vMSP430_DELAYS__Delay_uS(u32Value);
	#else
		#error
	#endif
}

/***************************************************************************//**
 * @brief
 * millisecond delay
 * 
 * @param[in]		u32Value				Delay value
 * @st_funcMD5		7C43316DD186DFA88546E51F8F144552
 * @st_funcID		LCCM644R0.FILE.008.FUNC.002
 */
void vDS18B20_DELAYS__Delay_mS(Luint32 u32Value)
{
	#if C_LOCALDEF__LCCM644__USE_ON_RM4 == 1U
		vRM4_DELAYS__Delay_mS(u32Value);
	#elif C_LOCALDEF__LCCM644__USE_ON_XILINX == 1U
		vXILINX_DELAYS__Delay_mS(u32Value);
	#elif C_LOCALDEF__LCCM644__USE_ON_MSP430 == 1U
		vMSP430_DELAYS__Delay_mS(u32Value);
	#else
		#error
	#endif
}

//safetys
#ifndef C_LOCALDEF__LCCM644__USE_ON_RM4
	#error
#endif
#ifndef C_LOCALDEF__LCCM644__USE_ON_XILINX
	#error
#endif

#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

