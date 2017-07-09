/**
 * @file		CELL_MODEL__BATTERY.C
 * @brief		Model of a complete battery pack
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM723R0.FILE.006
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
 * @addtogroup LIPO_CELL_MODEL__BATTERY
 * @ingroup LIPO_CELL_MODEL
 * @{
*/
#include <MULTICORE/LCCM723__MULTICORE__LIPO_CELL_MODEL/cell_model.h>
#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

extern TS_LIPO_CELL_MODEL sLiPo;


/***************************************************************************//**
 * @brief
 * Init the battery pack
 * 
 * @param[in]		u16PackIndex			The pack index
 * @st_funcMD5		1C6F2B505DC041FA9497D7C3750D9A28
 * @st_funcID		LCCM723R0.FILE.006.FUNC.001
 */
void vLIPOMODEL_BATTERY__Init(Luint16 u16PackIndex)
{
	Luint32 u32Counter;

	
	if(u16PackIndex < C_LOCALDEF__LCCM723__NUM_PACKS)
	{
		//clear the vars
		sLiPo.sPack[u16PackIndex].f32PackVoltage_V = 0.0F;

		//configure the cells
		for (u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK; u32Counter++)
		{
			vLIPOMODEL_CELL__Init(u16PackIndex, u32Counter);
		}
	}
	else
	{
		//error
	}

}

/***************************************************************************//**
 * @brief
 * Process the battery pack
 * 
 * @param[in]		u16PackIndex			The pack index
 * @st_funcMD5		888CC156FCFD5FBE78DEC4C060C1FEF7
 * @st_funcID		LCCM723R0.FILE.006.FUNC.002
 */
void vLIPOMODEL_BATTERY__Process(Luint16 u16PackIndex)
{
	Luint32 u32Counter;
	Lfloat32 f32Temp;
	
	if(u16PackIndex < C_LOCALDEF__LCCM723__NUM_PACKS)
	{
		//clear the pack vo
		f32Temp = 0.0F;

		//configure the cells
		for (u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK; u32Counter++)
		{
			//process the cell model
			vLIPOMODEL_CELL__Process(u16PackIndex, u32Counter);

			//get the new voltabe
			f32Temp += sLiPo.sPack[u16PackIndex].sCell[u32Counter].f32CellVoltage_V[sLiPo.sPack[u16PackIndex].sCell[u32Counter].u32CellTimer_Counter - 1U];
		}

		//Update pack voltage
		sLiPo.sPack[u16PackIndex].f32PackVoltage_V = f32Temp;

	}
	else
	{
		//error
	}
}


#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

