/**
 * @file		HE_THERM__TIMERS.C
 * @brief		
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM721R0.FILE.005
 */
/**
 * @addtogroup PROJECT_NAME
 * @{
 */
/**
 * @addtogroup PROJECT_NAME
 * @ingroup MODULE_NAME
 * @{
 */
/**
 * @addtogroup MODULE_NAME__CORE
 * @ingroup MODULE_NAME
 * @{
 */
/** @} */
/** @} */
/** @} */


/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM__TIMERS
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_HET__MAIN sHET;

/***************************************************************************//**
 * @brief
 * 10ms Interrupt
 * 
 */
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		5C389003D05A56345E3DF628AF71CF2C
 * @st_funcID		LCCM721R0.FILE.005.FUNC.001
 */
void vHETHERM_TIMERS__10MS_ISR(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
		#if C_LOCALDEF__LCCM644__USE_10MS_ISR == 1U
			vDS18B20__10MS_ISR();
		#endif
	#endif
	
}

/***************************************************************************//**
 * @brief
 * 100ms Interrupt
 */
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		F5C37117A8C7616CA55CB884860D0E7D
 * @st_funcID		LCCM721R0.FILE.005.FUNC.002
 */
void vHETHERM_TIMERS__100MS_ISR(void)
{
	
	
}





#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

