/**
 * @file		CELL_MODEL.C
 * @brief		Main model file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM723R0.FILE.000
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
 * @addtogroup LIPO_CELL_MODEL__CORE
 * @ingroup LIPO_CELL_MODEL
 * @{
*/
#include <MULTICORE/LCCM723__MULTICORE__LIPO_CELL_MODEL/cell_model.h>
#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

TS_LIPO_CELL_MODEL sLiPo;


/***************************************************************************//**
 * @brief
 * Init the LiPo model
 * 
 * @st_funcMD5		E634A9BF7A4B2017AB69FA0CFED34C73
 * @st_funcID		LCCM723R0.FILE.000.FUNC.001
 */
void vLIPOMODEL__Init(void)
{
	Luint32 u32Counter;
	
	//configure simulator
	sLiPo.sSim.f32SimTimeStep = 0.5F;
	sLiPo.sSim.f32TempAmbient_degC = 20.0F;
	
	
	//configure the loads
	sLiPo.sLoads.u8Current = 0U;
	sLiPo.sLoads.u8Power = 1U;
	sLiPo.sLoads.u8Resistance = 0U;
	sLiPo.sLoads.f32Current_A = 0.0F;
	sLiPo.sLoads.f32Power_W = 260.0F;
	sLiPo.sLoads.f32Resistance_R = 0.0F;
	
	//conifg each battery
	for (u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM723__NUM_PACKS; u32Counter++)
	{
		vLIPOMODEL_BATTERY__Init(u32Counter);
	}
	
}

/***************************************************************************//**
 * @brief
 * Process the model, call this as fast as possible from main loop.
 * 
 * @st_funcMD5		FC697BF7DC0C010FEAAB03DB9D5BCE2F
 * @st_funcID		LCCM723R0.FILE.000.FUNC.002
 */
void vLIPOMODEL__Process(void)
{
	Luint32 u32Counter;
	
	//process each battery
	for (u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM723__NUM_PACKS; u32Counter++)
	{
		vLIPOMODEL_BATTERY__Process(u32Counter);
	}
	
}

/***************************************************************************//**
 * @brief
 * 1 Second interrupt. Provide this for the timing rate.
 * 
 * @st_funcMD5		77D429A0F9283934A773B2047582D0CB
 * @st_funcID		LCCM723R0.FILE.000.FUNC.003
 */
void vLIPOMODEL__1S_ISR(void)
{
	vLIPOMODEL_CELL__1S_ISR();
}

/***************************************************************************//**
 * @brief
 * Test case
 * 
 * @st_funcMD5		0101B930DA854FB86508E450D7A25AA4
 * @st_funcID		LCCM723R0.FILE.000.FUNC.004
 */
DLL_DECLARATION void vLCCM723R0_TS_000(void)
{

	Luint32 u32Counter;
	Luint32 u32Length;

	u32Length = 600-2;

	vLIPOMODEL__Init();

	for (u32Counter = 0U; u32Counter < u32Length; u32Counter++)
	{
		vLIPOMODEL_CELL__1S_ISR();
		vLIPOMODEL__Process();
	}

	//save off the data
	vWIN32_DEBUG_CSV__Write_CSV_F32("D:\\RLOOP_LOG\\BATTERY_MODEL\\cell_voltage.csv", u32Length, &sLiPo.sPack[0].sCell[0].f32CellVoltage_V[0]);
	vWIN32_DEBUG_CSV__Write_CSV_F32("D:\\RLOOP_LOG\\BATTERY_MODEL\\cell_current.csv", u32Length, &sLiPo.sPack[0].sCell[0].f32CellCurrent_A[0]);
	vWIN32_DEBUG_CSV__Write_CSV_F32("D:\\RLOOP_LOG\\BATTERY_MODEL\\cell_power.csv", u32Length, &sLiPo.sPack[0].sCell[0].f32CellPower_W[0]);
	vWIN32_DEBUG_CSV__Write_CSV_F32("D:\\RLOOP_LOG\\BATTERY_MODEL\\cell_oc_voltage.csv", u32Length, &sLiPo.sPack[0].sCell[0].f32OpenCircuitVoltage_V[0]);

}




#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

