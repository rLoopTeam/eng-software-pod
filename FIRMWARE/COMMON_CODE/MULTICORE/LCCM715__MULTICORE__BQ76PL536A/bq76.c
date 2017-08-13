/**
 * @file		BQ76.C
 * @brief		Core File
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.000
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
 * @addtogroup BQ76__CORE
 * @ingroup BQ76
 * @{
*/
#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>
#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

TS_BQ76__MAIN sBQ76;

/***************************************************************************//**
 * @brief
 * Init the BQ76 device.
 * 
 * @st_funcMD5		F10254CAECA5B757C2E5CBB41CB26500
 * @st_funcID		LCCM715R0.FILE.000.FUNC.001
 */
void vBQ76__Init(void)
{

	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Counter++)
	{
		vSIL3_FAULTTREE__Init(&sBQ76.sDevice[u8Counter].sFaultFlags);
	}


	//init the SPI subsystem
	vBQ76_SPI__Init();

	//init the cell system
	vBQ76_CELLS__Init();

	//init the battery pack calcs
	vBQ76_BATTERY__Init();

	//Init the balancer
	vBQ76_BALANCE__Init();

	//resistor control
	vBQ76_RES__Init();

}

/***************************************************************************//**
 * @brief
 * Process any BQ76 tasks.
 * 
 * @st_funcMD5		D23D95EBB63C64E05A886A25E83702E6
 * @st_funcID		LCCM715R0.FILE.000.FUNC.002
 */
void vBQ76__Process(void)
{

	//process any SPI tasks
	vBQ76_SPI__Process();

	//process the cell level tasks
	vBQ76_CELLS__Process();

	//process our battery
	vBQ76_BATTERY__Process();

	//process any balancing
	vBQ76_BALANCE__Process();

	//resistor control
	vBQ76_RES__Process();

}

/***************************************************************************//**
 * @brief
 * Get a cell voltage
 *
 * @note
 * Returns the filtered voltage if filtering is enabled
 * 
 * @param[in]		u8CellIndex				The cell index in the pack
 * @return			Cell voltage
 * @st_funcMD5		F9449053D59F927DE2C805568AAE0908
 * @st_funcID		LCCM715R0.FILE.000.FUNC.005
 */
Lfloat32 f32BQ76__Get_CellVoltage(Luint8 u8CellIndex)
{

	#if C_LOCALDEF__LCCM715__AVERAGE_WINDOW > 0U
		return sBQ76.sCell[u8CellIndex].f32FiltVoltage;
	#else
		return sBQ76.sCell[u8CellIndex].f32CellVoltage;
	#endif
}


/***************************************************************************//**
 * @brief
 * Return the number of times the cells were read
 * 
 * @st_funcMD5		E866054152E6FBED501DED5B601B916D
 * @st_funcID		LCCM715R0.FILE.000.FUNC.003
 */
Luint32 u32BQ76__Get_VoltsUpdateCount(void)
{
	return sBQ76.sCells.u32UpdateCount;
}

/***************************************************************************//**
 * @brief
 * 10ms interrupt
 * 
 * @st_funcMD5		E1AB47E5E68DD020598F75EEF0D0774B
 * @st_funcID		LCCM715R0.FILE.000.FUNC.004
 */
void vBQ76__10MS_ISR(void)
{
	vBQ76_CELLS__10MS_ISR();
}

/***************************************************************************//**
 * @brief
 * Get any BQ76 fault flags
 * 
 * @param[in]		u8DeviceIndex			BQ76 index
 * @return			32bit fault flags.
 * @st_funcMD5		5964CEBB233BCB7C4E9DAB5E3D38AFEE
 * @st_funcID		LCCM715R0.FILE.000.FUNC.006
 */
Luint32 u32BQ76__Get_FaultFlags(Luint8 u8DeviceIndex)
{
	return sBQ76.sDevice[u8DeviceIndex].sFaultFlags.u32Flags[0];
}

#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

