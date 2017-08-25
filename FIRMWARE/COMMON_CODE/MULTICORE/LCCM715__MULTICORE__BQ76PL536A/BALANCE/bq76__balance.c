/**
 * @file		BQ76__BALANCE.C
 * @brief		Battery balancing functoins
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.012
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
 * @addtogroup BQ76__BALANCE
 * @ingroup BQ76
 * @{
*/
#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>
#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

extern TS_BQ76__MAIN sBQ76;

/***************************************************************************//**
 * @brief
 * Init the balancer
 * 
 * @st_funcMD5		DCBDDD902B64D985F0B09D4BB187B122
 * @st_funcID		LCCM715R0.FILE.012.FUNC.001
 */
void vBQ76_BALANCE__Init(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
	{
		sBQ76.sBalance.u8Resistor[u8Counter] = 0U;
	}

	sBQ76.sBalance.u3210MS_Counter = 0U;
}

/***************************************************************************//**
 * @brief
 * Process any balancing tasks
 * 
 * @st_funcMD5		600233110464B6BAD3B047B64966DA0D
 * @st_funcID		LCCM715R0.FILE.012.FUNC.002
 */
void vBQ76_BALANCE__Process(void)
{

    //Update cell balance discharge resistor at 2 Hz
	if(sBQ76.sBalance.u3210MS_Counter >= 50U){
	    sBQ76.sBalance.u3210MS_Counter = 0U;
	    vBQ76_BALANCE__Update_Discharge_Resistors();
	}
}

/***************************************************************************//**
 * @brief
 * Start the balancing process
 * 
 * @st_funcMD5		C75001693893BA9946A832499E1350EF
 * @st_funcID		LCCM715R0.FILE.012.FUNC.003
 */
void vBQ76_BALANCE__Start(void)
{
	//nothing here yet
}

/***************************************************************************//**
 * @brief
 * Check if the balancer is busy
 * 
 * @return 			1 = busy
 * @st_funcMD5		EAC635F7A4A802DB33BC96DDB37EF9F6
 * @st_funcID		LCCM715R0.FILE.012.FUNC.004
 */
Luint8 u8BQ76_BALANCE__Is_Busy(void)
{
	return 0;
}

/***************************************************************************//**
 * @brief
 * Stop the balancing
 * 
 * @st_funcMD5		FB05686967B46A17D238B4B6740C4B4F
 * @st_funcID		LCCM715R0.FILE.012.FUNC.005
 */
void vBQ76_BALANCE__Stop(void)
{
	//nothign here yet
}

/***************************************************************************//**
 * @brief
 * Manual balancing
 * 
 * @param[in]		u8Enable				1 = resistor on
 * @param[in]		u8CellIndex				Cell index in system
 * @st_funcMD5		0827BCA902FBB2EC4E1DB5C8F0184EFA
 * @st_funcID		LCCM715R0.FILE.012.FUNC.006
 */
void vBQ76_BALANCE__Manual(Luint8 u8CellIndex, Luint8 u8Enable)
{
	Luint8 u8Counter;
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
				if(u8Enable == 1U)
				{

					//make sure not already on
					if(sBQ76.sBalance.u8Resistor[u8CellIndex] == 0U)
					{
						vBQ76_RES__Resistor_On(u8CellIndex);
					}
					else
					{
						//already on
					}

				}
				else
				{
					//disable
					//make sure not already ff
					if(sBQ76.sBalance.u8Resistor[u8CellIndex] == 1U)
					{
						vBQ76_RES__Resistor_Off(u8CellIndex);
					}
					else
					{
						//already off
					}

				}

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
 * Read discharge resistor status from BMS
 *
 */
//TODO: maybe move to RESISTOR
void vBQ76_BALANCE__Update_Discharge_Resistors(void)
{
    Luint8 u8DeviceCounter;
    Luint8 u8Temp;
    Luint8 u8Counter;


    for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8DeviceCounter++)
    {
        u8Temp = u8BQ76_SPI__Read_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL);
        for(u8Counter = 0U; u8Counter < 8; u8Counter++){
            sBQ76.sBalance.u8Resistor[u8Counter+8*u8DeviceCounter] = (u8Temp >> u8Counter) & 0x01;
        }

        //set the balance time. 5 min = 0x85U
        vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_TIME, 0x0AU);

        //refresh the resistor value
        vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL, 0);
        vBQ76_SPI__Write_U8(u8DeviceCounter + 1U, BQ76_REG__CB_CTRL, u8Temp);
    }
}

/***************************************************************************//**
 * @brief
 * 10MS interrupt
 *
 * @st_funcMD5      1CEDE1D02EFC86149E3C00E8A5AB3EA1
 * @st_funcID       LCCM715R0.FILE.010.FUNC.007
 */
void vBQ76_BALANCE__10MS_ISR(void)
{

    sBQ76.sBalance.u3210MS_Counter++;
}

#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

