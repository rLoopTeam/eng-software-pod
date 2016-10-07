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
		unT.u8[0] = u8Buffer[0 + (u8Counter * 2U)];
		unT.u8[1] = u8Buffer[1 + (u8Counter * 2U)];
	
		//unpack
		f32Temp = (Lfloat32)unT.u16;
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

