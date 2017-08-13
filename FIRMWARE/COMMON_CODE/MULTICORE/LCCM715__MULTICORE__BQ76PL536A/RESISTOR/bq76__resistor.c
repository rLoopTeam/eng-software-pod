/**
 * @file		BQ76__RESISTOR.C
 * @brief		Discharge Resistor Control
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.007
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
 * @addtogroup BQ76__RESISTOR
 * @ingroup BQ76
 * @{
*/
#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>
#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

extern TS_BQ76__MAIN sBQ76;

/***************************************************************************//**
 * @brief
 * Init any resistor items
 * 
 * @st_funcMD5		02E263E709AE6776A1D965F823088B04
 * @st_funcID		LCCM715R0.FILE.007.FUNC.001
 */
void vBQ76_RES__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Process any resistor control items
 * 
 * @st_funcMD5		868D0314B99E1423B048A825A1D9135A
 * @st_funcID		LCCM715R0.FILE.007.FUNC.002
 */
void vBQ76_RES__Process(void)
{
	//do nothing
}

/***************************************************************************//**
 * @brief
 * Turn off all resistors
 * 
 * @st_funcMD5		97971BB9CA087C63B21E64D56CA11F78
 * @st_funcID		LCCM715R0.FILE.007.FUNC.003
 */
void vBQ76_RES__All_Off(void)
{
	Luint8 u8DeviceCounter;

	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8DeviceCounter++)
	{
		vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL, 0x00U);
	}

	for(u8DeviceCounter = 0U; u8DeviceCounter < C_BQ76__TOTAL_CELLS; u8DeviceCounter++)
	{
		sBQ76.sBalance.u8Resistor[u8DeviceCounter] = 0U;
	}
}

/***************************************************************************//**
 * @brief
 * Turn an individual resistor on
 * 
 * @param[in]		u8CellIndex				Associated cell resistor
 * @st_funcMD5		1A954DF979AB61EFBF44011583AAF477
 * @st_funcID		LCCM715R0.FILE.007.FUNC.004
 */
void vBQ76_RES__Resistor_On(Luint8 u8CellIndex)
{

	Luint8 u8DeviceCounter;
	Luint8 u8CellCounter;
	Luint8 u8Temp;
	Luint8 u8Mask;
	Luint8 u8Test;


	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8DeviceCounter++)
	{
		for(u8CellCounter = 0U; u8CellCounter < C_BQ76__MAX_CELLS_PER_DEVICE; u8CellCounter++)
		{
			//compute the index
			u8Test = (u8DeviceCounter * C_BQ76__MAX_CELLS_PER_DEVICE) + u8CellCounter;
			if(u8Test == u8CellIndex)
			{
				//match
				//set the state
				sBQ76.sBalance.u8Resistor[u8CellIndex] = 1U;

				//set the balance time of 5 min
				vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_TIME, 0x85U);

				//read the current resistors
				u8Temp = u8BQ76_SPI__Read_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL);

				//modify
				u8Mask = 0x01U;
				u8Mask <<= u8CellCounter;

				//set the cell bit
				u8Temp |= u8Mask;

				//switch on the resistor
				vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL, u8Temp);

				//done
				break;
			}
			else
			{
				//no match yet
			}

		}//for(u8CellCounter = 0U; u8CellCounter < C_BQ76__MAX_CELLS_PER_DEVICE; u8CellCounter++)

	}//for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8DeviceCounter++)
}

/***************************************************************************//**
 * @brief
 * Turn an individual resistor off
 * 
 * @param[in]		u8CellIndex			The resistor index.
 * @st_funcMD5		443202F442F97669254DFC6511ADC43A
 * @st_funcID		LCCM715R0.FILE.007.FUNC.005
 */
void vBQ76_RES__Resistor_Off(Luint8 u8CellIndex)
{

	Luint8 u8Test;
	Luint8 u8DeviceCounter;
	Luint8 u8CellCounter;
	Luint8 u8Temp;
	Luint8 u8Mask;

	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8DeviceCounter++)
	{
		for(u8CellCounter = 0U; u8CellCounter < C_BQ76__MAX_CELLS_PER_DEVICE; u8CellCounter++)
		{
			//compute the index
			u8Test = (u8DeviceCounter * C_BQ76__MAX_CELLS_PER_DEVICE) + u8CellCounter;
			if(u8Test == u8CellIndex)
			{
				//match
				//set the state
				sBQ76.sBalance.u8Resistor[u8CellIndex] = 0U;

				//read the current resistors
				u8Temp = u8BQ76_SPI__Read_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL);

				//modify
				u8Mask = 0x01U;
				u8Mask <<= u8CellCounter;
				u8Mask ^= 0xFF;

				//clear the cell bit
				u8Temp &= u8Mask;

				//switch on the resistor
				vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL, u8Temp);

				//done
				break;
			}
			else
			{
				//no match yet
			}

		}//for(u8CellCounter = 0U; u8CellCounter < C_BQ76__MAX_CELLS_PER_DEVICE; u8CellCounter++)

	}//for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8DeviceCounter++)

}


#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

