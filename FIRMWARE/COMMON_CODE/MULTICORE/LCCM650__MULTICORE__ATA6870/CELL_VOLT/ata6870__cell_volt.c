/**
 * @file		ATA6870__CELL_VOLT.C
 * @brief		Cell voltage read
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.011
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__CELL_VOLT
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U



//main structure
extern struct _str6870 sATA6870;

/***************************************************************************//**
 * @brief
 * bulk read voltages: 6 voltages, 1 temperature
 *
 */
Lint16 s16ATA6870_CELL__BulkRead_All(void)
{
	// volt mode = calibration or regular acquisition. 0 for calibration, 1 for regular.
	// tempBit = temperature sensor to select. 1 for internal, 0 for external.

	Lint16 s16Return;
	// loop counter
	Luint8 u8Counter;
	// number of cell voltage readings
	Luint8 u8VolCounter = 0U;


	s16Return = 0U;

	// read data
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		vATA6870_CELL__Get_Voltages(u8Counter, &sATA6870.f32Voltage[u8VolCounter], &sATA6870.f32NTCTemperatureReading[u8Counter]);

		// move to next module
		u8VolCounter += C_ATA6870__MAX_CELLS;
	}

	// check if any cells are dead or out of threshold
	s16Return = s16ATA6870_CELL__Check_CellVoltageError(&sATA6870.f32Voltage[0]);

	return s16Return;
}

//compute the sum of all voltages (= our pack voltage)
void vATA6870_CELL__Sum_CellVoltages(void)
{
	Luint8 u8Counter;
	Luint8 u8Cell;
	Lfloat32 f32Temp;

	//clear initially:
	f32Temp = 0.0F;

	//go through each device
	for(u8Counter = 0U; u8Counter < C_ATA6870__TOTAL_CELLS; u8Counter++)
	{
		f32Temp += sATA6870.f32Voltage[u8Counter];

	}

	//update
	sATA6870.f32PackVoltage = f32Temp;

	//todo: we may need to average this.
}

//take the average cell voltages
void vATA6870_CELL__Average_CellVoltages(void)
{
	Lfloat32 f32Temp;

	//set initially:
	f32Temp = sATA6870.f32PackVoltage;

	f32Temp /= (Lfloat32)C_ATA6870__TOTAL_CELLS;

	//update
	sATA6870.f32AverageCellVoltage = f32Temp;

	//needed for balancing
	sATA6870.u8AverageUpdated = 1U;

}


//*** check if a cell is above or below safe threshold ***//
//TODO: if we use UNDER_VOLT function instead, be sure to implement
//      an upper bound check as well for over voltage
// Lfloat32 *f32Voltages					voltages array of size C_ATA6870__MAX_CELLS
Lint16 s16ATA6870_CELL__Check_CellVoltageError(Lfloat32 *pf32Voltages)
{
	Lint16 s16Return;
	Luint8 u8Counter;

	s16Return = 0;

	// check each voltage is within threshold
	for(u8Counter = 0U; u8Counter < C_ATA6870__MAX_CELLS; u8Counter++)
	{
		if (pf32Voltages[u8Counter] > C_ATA6870__MAX_VOLTS)
		{
			// log voltage error
			// TODO: standardize error codes
			s16Return = -1;
		}
		else if (pf32Voltages[u8Counter] < C_ATA6870__MIN_VOLTS)
		{
			// log voltage error
			// TODO: standardize error codes
			s16Return = -2;
		}
		else
		{
			// fall through
		}
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Gets the voltages for each cell from a specific BMS device
 * 
 * @note
 * Need to ensure that a conversion has actually completed before this can
 * be issued
 *
 * @param[out]		*pF32Temperature		The returned temperature reading from the NTC
 * @param[out]		*pf32Voltages			An array of 6 Cell voltages
 * @param[in]		u8DeviceIndex			The device index on the bus
 * @st_funcMD5		9BC1EB66852FF80D8FF3D84707D5C92E
 * @st_funcID		LCCM650R0.FILE.011.FUNC.002
 */
void vATA6870_CELL__Get_Voltages(Luint8 u8DeviceIndex, Lfloat32 *pf32Voltages, Lfloat32 *pF32Temperature)
{
	Luint8 u8Counter;
	Lfloat32 f32Temp;
	union
	{
		Luint16 u16;
		Luint8 u8[2];
	}unT;
	
	//14 bytes of local memory, reviewed.
	//We also have to return the temperature value in this
	Luint8 u8Buffer[C_ATA6870__BUSRT_LENGTH];
	
	//do the burst read
	//reviewed magic numbers.
	vATA6870_LOWLEVEL__Reg_ReadU8(u8DeviceIndex, ATA6870_REG__DATA_RD16_BURST, &u8Buffer[0], C_ATA6870__BUSRT_LENGTH);

	//todo
	//review the status and make sure we did not get a tiemout or data corruption
	
	//do the conversions
	for(u8Counter = 0U; u8Counter < C_ATA6870__MAX_CELLS; u8Counter++)
	{
		//convert
		unT.u8[0] = u8Buffer[1 + (u8Counter * 2U)];
		unT.u8[1] = u8Buffer[0 + (u8Counter * 2U)];
	
		//unpack
		f32Temp = (Lfloat32)unT.u16;
		f32Temp -= C_ATA6870__OFFSET_VOLTAGE; //pg.18, 5.5 Offset Voltage
		f32Temp *= C_ATA6870__ADC_RES_V;
		
		//assign
		pf32Voltages[u8Counter] = f32Temp;
		
	}

	//last two are the temp reading, we can save this off elsewhere
	unT.u8[0] = u8Buffer[C_ATA6870__BUSRT_LENGTH - 2U];
	unT.u8[1] = u8Buffer[C_ATA6870__BUSRT_LENGTH - 1U];

	//unpack
	//todo, check temp value
	f32Temp = (Lfloat32)unT.u16;
	f32Temp *= C_ATA6870__ADC_RES_V;
	
	//assign
	*pF32Temperature = f32Temp;
	
}



//safetys
#ifndef C_LOCALDEF__LCCM650__NUM_DEVICES
	#error
#endif
#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif

