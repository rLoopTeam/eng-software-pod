/**
 * @file		CELL_MODEL__WIN32.C
 * @brief		Win32 simulation helpers
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM723R0.FILE.004
 */

/**
 * @addtogroup MULTICORE
 * @{
*/
/**
 * @addtogroup LIPO_CELL_MODEL
 * @ingroup MULTICORE
 * @{
*/
/**
 * @addtogroup LIPO_CELL_MODEL__WIN32
 * @ingroup LIPO_CELL_MODEL
 * @{
*/
#include <MULTICORE/LCCM723__MULTICORE__LIPO_CELL_MODEL/cell_model.h>
#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

extern TS_LIPO_CELL_MODEL sLiPo;

/***************************************************************************//**
 * @brief
 * Get the entire pack voltage sum
 * 
 * @param[in]		u16PackIndex			The pack index
 * @st_funcMD5		F56427632D4E1792930CD4AB4B76AB98
 * @st_funcID		LCCM723R0.FILE.004.FUNC.001
 */
Lfloat32 f32LIPOMODEL_WIN32__Get_PackVoltage(Luint16 u16PackIndex)
{
	return sLiPo.sPack[u16PackIndex].f32PackVoltage_V;
}

/***************************************************************************//**
 * @brief
 * Update the load power value in Watts
 * 
 * @param[in]		f32Value			New load power
 * @st_funcMD5		81F60BDC1AD218E73F671FDA4B7A9147
 * @st_funcID		LCCM723R0.FILE.004.FUNC.002
 */
void vLIPOMODEL_WIN32__Update_LoadPower(Lfloat32 f32Value)
{
	//configure the loads
	sLiPo.sLoads.u8Current = 0U;
	sLiPo.sLoads.u8Power = 1U;
	sLiPo.sLoads.u8Resistance = 0U;
	sLiPo.sLoads.f32Current_A = 0.0F;
	sLiPo.sLoads.f32Power_W = f32Value;
	sLiPo.sLoads.f32Resistance_R = 0.0F;
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		f32Value		## Desc ##
 * @st_funcMD5		CE4FFAB14A92927CC5955D2A1E624907
 * @st_funcID		LCCM723R0.FILE.004.FUNC.003
 */
void vLIPOMODEL_WIN32__Update_LoadCurrent(Lfloat32 f32Value)
{
	//configure the loads
	sLiPo.sLoads.u8Current = 1U;
	sLiPo.sLoads.u8Power = 0U;
	sLiPo.sLoads.u8Resistance = 0U;
	sLiPo.sLoads.f32Current_A = f32Value;
	sLiPo.sLoads.f32Power_W = 0.0F;
	sLiPo.sLoads.f32Resistance_R = 0.0F;
}

#endif //WIN32

#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

