/**
 * @file		BQ76__BATTERY.C
 * @brief		Batteyr pack top level
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.011
 */

/**
 * @addtogroup MULTICORE
 * @{
*/
/**
 * @addtogroup BQ76
 * @ingroup MULTICORE
 * @{
*/
/**
 * @addtogroup BQ76__BATTERY
 * @ingroup BQ76
 * @{
*/
#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>
#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

extern TS_BQ76__MAIN sBQ76;

/***************************************************************************//**
 * @brief
 * Init the battery
 * 
 * @st_funcMD5		8972212B91CA3DA6760475F2EB84EC01
 * @st_funcID		LCCM715R0.FILE.011.FUNC.001
 */
void vBQ76_BATTERY__Init(void)
{
	//init
	sBQ76.sBattery.f32PackVoltage = 0.0F;
}

/***************************************************************************//**
 * @brief
 * Process any battery tasks
 * 
 * @st_funcMD5		7EAEC9E911EA69F8D9997E533A179039
 * @st_funcID		LCCM715R0.FILE.011.FUNC.002
 */
void vBQ76_BATTERY__Process(void)
{
	//nothing here
}


/***************************************************************************//**
 * @brief
 * Compute the pack voltage
 * 
 * @st_funcMD5		6C6BDAAC96F01266E2AC867276327B77
 * @st_funcID		LCCM715R0.FILE.011.FUNC.003
 */
void vBQ76_BATTERY__Compute_PackVoltage(void)
{
	Luint8 u8Counter;
	Lfloat32 f32Temp;

	//clear initially:
	f32Temp = 0.0F;

	//go through each device
	for(u8Counter = 0U; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
	{
		#if C_LOCALDEF__LCCM715__AVERAGE_WINDOW == 0U
			f32Temp += sBQ76.sCell[u8Counter].f32CellVoltage;
		#else
			f32Temp += sBQ76.sCell[u8Counter].f32FiltVoltage;
		#endif
	}

	//update
	sBQ76.sBattery.f32PackVoltage = f32Temp;
}

/***************************************************************************//**
 * @brief
 * return the pack voltage
 * 
 * @st_funcMD5		9B133686076E3583A90F0C223A77EFDB
 * @st_funcID		LCCM715R0.FILE.011.FUNC.004
 */
Lfloat32 f32BQ76_BATTERY__Get_PackVoltage(void)
{
	return sBQ76.sBattery.f32PackVoltage;
}

#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

