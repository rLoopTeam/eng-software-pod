/**
 * @file		BQ76__CELLS.C
 * @brief		Cell level interface
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.010
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
 * @addtogroup BQ76__CELLS
 * @ingroup BQ76
 * @{
*/
#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>
#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

extern TS_BQ76__MAIN sBQ76;

//locals
void vBQ76_CELLS__Read_All(void);
void vBQ76_CELLS__Compute_AllVoltages(void);

/***************************************************************************//**
 * @brief
 * Init the cells subsystem
 * 
 * @st_funcMD5		B734200087845452AE87CF6ACC59141D
 * @st_funcID		LCCM715R0.FILE.010.FUNC.001
 */
void vBQ76_CELLS__Init(void)
{
	Luint8 u8Counter;
	Luint8 u8Filt;
	
	sBQ76.sCells.u3210MS_Counter = 0U;
	sBQ76.sCells.sState = CELLS_STATE__IDLE;
	
	//clear the cell voltages
	for(u8Counter = 0U; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
	{
		sBQ76.sCell[u8Counter].f32CellVoltage = 0.0F;

		#if C_LOCALDEF__LCCM715__AVERAGE_WINDOW > 0U
			for(u8Filt = 0U; u8Filt < C_LOCALDEF__LCCM715__AVERAGE_WINDOW; u8Filt++)
			{
				sBQ76.sCell[u8Counter].f32VoltagesBuffer[u8Filt] = 0.0F;
			}
		#endif
		sBQ76.sCell[u8Counter].u16AverageCounter = 0;
		sBQ76.sCell[u8Counter].f32FiltVoltage = 0.0F;
	}

	sBQ76.sCells.u32UpdateCount = 0U;

}


/***************************************************************************//**
 * @brief
 * Process the cell level state machine.
 * 
 * @st_funcMD5		DB9A8F4A04A3B0439C6548DAFDEDA803
 * @st_funcID		LCCM715R0.FILE.010.FUNC.002
 */
void vBQ76_CELLS__Process(void)
{
	
	Luint8 u8Device;
	Lfloat32 f32Max;
	Lfloat32 f32Min;
	Luint8 u8CellCounter;
	Luint8 u8CellIndex;


	switch(sBQ76.sCells.sState)
	{
		/** Idle state */
		case CELLS_STATE__IDLE:
		
			//move to start conversion.
			sBQ76.sCells.sState = CELLS_STATE__START_CONVERT;
			break;
			
		/** Start the conversion */
		case CELLS_STATE__START_CONVERT:
		
			//issue the conversion request to all devices
			for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Device++)
			{
				//start
				vBQ76_SPI__Write_U8(u8Device + 1U, BQ76_REG__ADC_CONVERT, 0x01U);
				
			}
			
			//Clear the counter
			sBQ76.sCells.u3210MS_Counter = 0U;
			
			//move state
			sBQ76.sCells.sState = CELLS_STATE__WAIT_CONVERT;
		
			break;
		
		/** Wait for the conversion to complete */
		case CELLS_STATE__WAIT_CONVERT:
		
			//needs >42us
			if(sBQ76.sCells.u3210MS_Counter > 5U)
			{
				//conversion complete, process it
				sBQ76.sCells.sState = CELLS_STATE__READ_VOLTS;
			}
			else
			{
				//not ready yet
			}
		
			break;
		
		/** Read the cell voltages */
		case CELLS_STATE__READ_VOLTS:
		
			//get the cell volts from each chip
			vBQ76_CELLS__Read_All();
			
			sBQ76.sCells.sState = CELLS_STATE__CONVERT_VOLTS;
			break;
		
		/** Convert raw to voltages */
		case CELLS_STATE__CONVERT_VOLTS:
			
			//turn the raw data into voltages
			vBQ76_CELLS__Compute_AllVoltages();
			
			//filter if needed
			sBQ76.sCells.sState = CELLS_STATE__RUN_AVERAGER;
			break;
			
		/** Do any filtering as needed */
		case CELLS_STATE__RUN_AVERAGER:

			#if C_LOCALDEF__LCCM715__AVERAGE_WINDOW > 0U
			for(u8CellCounter = 0U; u8CellCounter < C_BQ76__TOTAL_CELLS; u8CellCounter++)
			{
				//do the filtering
				sBQ76.sCell[u8CellCounter].f32FiltVoltage = f32SIL3_NUM_FILTERING__Add_F32(sBQ76.sCell[u8CellCounter].f32CellVoltage,
																						   &sBQ76.sCell[u8CellCounter].u16AverageCounter,
																						   C_LOCALDEF__LCCM715__AVERAGE_WINDOW,
																						   &sBQ76.sCell[u8CellCounter].f32VoltagesBuffer[0]);
			}
			#else
				//do nothing
			#endif

		
			sBQ76.sCells.sState = CELLS_STATE__COMPUTE_MIN_MAX;
			break;
		
		/** Compute the min/max volts */
		case CELLS_STATE__COMPUTE_MIN_MAX:

			//set the max voltage very low
			f32Max = 0.0F;

			//loop through each cell
			for(u8CellCounter = 0U; u8CellCounter < C_BQ76__TOTAL_CELLS; u8CellCounter++)
			{

				//simply choose the highest cell.
				if(sBQ76.sCell[u8CellCounter].f32CellVoltage > f32Max)
				{
					//record it.
					f32Max = sBQ76.sCell[u8CellCounter].f32CellVoltage;
				}
				else
				{
					//keep sorting
				}

			}//for(u8CellCounter = 0U; u8CellCounter < C_BQ76__TOTAL_CELLS; u8CellCounter++)

			sBQ76.sCells.f32Highest = f32Max;


			//set the min way out of the scale
			f32Min = 100.0F;

			//go through each cell.
			for(u8CellCounter = 0U; u8CellCounter < C_BQ76__TOTAL_CELLS; u8CellCounter++)
			{

				//simply choose the lowest cell.
				if(sBQ76.sCell[u8CellCounter].f32CellVoltage < f32Min)
				{
					//set the minimum cell voltage
					f32Min = sBQ76.sCell[u8CellCounter].f32CellVoltage;
				}
				else
				{
					//keep sorting
				}

			}//for(u8CellCounter = 0U; u8CellCounter < C_BQ76__TOTAL_CELLS; u8CellCounter++)

			sBQ76.sCells.f32Lowest = f32Min;

			sBQ76.sCells.sState = CELLS_STATE__COMPUTE_BATTERY;
			break;

		/** Compute the battery */
		case CELLS_STATE__COMPUTE_BATTERY:

			//compute the pack voltage
			vBQ76_BATTERY__Compute_PackVoltage();

			sBQ76.sCells.sState = CELLS_STATE__IDLE;
			break;

	}//switch(sBQ76.sCells.sState)

}



/***************************************************************************//**
 * @brief
 * Read all the cell voltages off the device
 * 
 * @st_funcMD5		78564D765DDF8EFC0F439B5F489E4572
 * @st_funcID		LCCM715R0.FILE.010.FUNC.006
 */
void vBQ76_CELLS__Read_All(void)
{
	Luint8 u8Device;

	//loop through each device
	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Device++)
	{
		//read out the array
		vBQ76_SPI__Read_U8_Array(u8Device + 1U, BQ76_REG__VCELL1, &sBQ76.sDevice[u8Device].u8RawVoltArray[0], 12U);
		
	}
	
	//inc the update count
	sBQ76.sCells.u32UpdateCount++;

}

/***************************************************************************//**
 * @brief
 * Return the highest cell voltage.
 * 
 * @st_funcMD5		8F2B032B9D5EA69046F232D3AC3845CD
 * @st_funcID		LCCM715R0.FILE.010.FUNC.003
 */
Lfloat32 f32BQ76_CELLS__Get_HighestVoltage(void)
{
	return sBQ76.sCells.f32Highest;
}

/***************************************************************************//**
 * @brief
 * Return the lowest cell voltage in the system
 * 
 * @return			The lowest computed voltage
 * @st_funcMD5		C4773F27824190CA34294ECB61E26A90
 * @st_funcID		LCCM715R0.FILE.010.FUNC.004
 */
Lfloat32 f32BQ76_CELLS__Get_LowestVoltage(void)
{
	return sBQ76.sCells.f32Lowest;
}


/***************************************************************************//**
 * @brief
 * Compute the floating point cell voltages from the data arrays
 * 
 * @st_funcMD5		0DB7F59511A12A5002E1DC0474DE066F
 * @st_funcID		LCCM715R0.FILE.010.FUNC.008
 */
void vBQ76_CELLS__Compute_AllVoltages(void)
{
	Luint8 u8Device;
	Luint8 u8Cell;
	Luint8 u8CellIndex;
	Luint8 u8ArrayPos;
	
	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Device++)
	{
		//go through each cell in the device
		u8ArrayPos = 0U;
		for(u8Cell = 0U; u8Cell < C_BQ76__MAX_CELLS_PER_DEVICE; u8Cell++)
		{
			
			//compute the system wide cell index
			u8CellIndex = (u8Device * C_BQ76__MAX_CELLS_PER_DEVICE) + u8Cell;
			
			//compute
			sBQ76.sCell[u8CellIndex].f32CellVoltage = f32BQ76_CELLS__Compute_CellVoltage(sBQ76.sDevice[u8Device].u8RawVoltArray[u8ArrayPos], sBQ76.sDevice[u8Device].u8RawVoltArray[u8ArrayPos + 1U]);
			
			//inc array pos
			u8ArrayPos += 2U;
			
		}//for(u8Cell = 0U; u8Cell < C_BQ76__MAX_CELLS_PER_DEVICE; u8Cell++)
		
	}//for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Device++)
}


/***************************************************************************//**
 * @brief
 * Compute a cells voltage based on the datasheet equations.
 * 
 * @param[in]		u8LowByte			Low byte from read
 * @param[in]		u8HighByte			High byte from read
 * @st_funcMD5		F6051FF8EEF476D7CAFA5DBACD2A6ABF
 * @st_funcID		LCCM715R0.FILE.010.FUNC.005
 */
Lfloat32 f32BQ76_CELLS__Compute_CellVoltage(Luint8 u8HighByte, Luint8 u8LowByte)
{
	Lfloat32 f32H;
	Lfloat32 f32L;
	Lfloat32 f32F;
	
	//high byte
	f32H = (Lfloat32)u8HighByte;
	f32H *= 256.0F;
	
	//low byte
	f32L = (Lfloat32)u8LowByte;
	
	//sum
	f32H += f32L;
	
	//conversion factor
	f32F = 6250.0F / 16383.0F;

	//mult by conversion factor	
	f32H *= f32F;
	
	//convert to volts
	f32H /= 1000.0F;

	return f32H;

}

/***************************************************************************//**
 * @brief
 * 10MS interrupt
 * 
 * @st_funcMD5		1CEDE1D02EFC86149E3C00E8A5AB3EA1
 * @st_funcID		LCCM715R0.FILE.010.FUNC.007
 */
void vBQ76_CELLS__10MS_ISR(void)
{
	
	sBQ76.sCells.u3210MS_Counter++;
}

#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

