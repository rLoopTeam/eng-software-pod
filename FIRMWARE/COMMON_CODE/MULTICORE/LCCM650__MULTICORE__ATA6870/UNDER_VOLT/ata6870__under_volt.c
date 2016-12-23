v /**
 * @file		ATA6870__UNDER_VOLT.C
 * @brief		Handles the undervoltage threshold functions
 *
 * @note
 * 				A programmable undervoltage detection function is embedded in the ATA6870N.
 * 				After being digitalized, each of the 6 voltages is compared to a programmable threshold 
 * 				defined in the UdvThresh register. If one of the six channels is out of the
 * 				range defined by the threshold, an interrupt is requested to the host MCU if the 
 * 				corresponding udv mask bit is not set in the IrqMask register.
 * 				The default threshold is 1.5V.
 * 				As soon as MCU has acknowledged, undervoltage information is no more available to MCU,
 * 				because status register is cleared when MCU reads it out. As a consequence, the next 
 * 				undervoltage interrupt cannot occur until the Atmel ATA6870N leaves its current undervoltage state.
 *
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.009
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__UNDERVOLT
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
extern struct _str6870 sATA6870;

/***************************************************************************//**
 * @brief
 * Set the under voltage threshold value
 * 
 * @param[in]		f32Value				The value in volts
 * @param[in]		u8DeviceIndex			The BMS device index
 * @st_funcMD5		65E4082BE59A5BDC1CE5DA84740EE690
 * @st_funcID		LCCM650R0.FILE.009.FUNC.001
 */
void vATA6870_UV__Set_UVTrip(Luint8 u8DeviceIndex, Lfloat32 f32Value)
{
	Lfloat32 f32Temp;
	Luint8 u8Counter;
	union
	{
		Luint16 u16;
		Luint8 u8[2];
	
	}unT, unT2;

	//equation is:
	//UV = Vref * (Value - 410) / (1502 - 410)
	//Example:
	//Value = 1392
	//1.5 = 1.667 * (1392 - 410) / (1502 - 410)
	//1.5 = 1.667 * (1392 - 410) / 1092
	
	//Transpose
	//(1.5 / 1.667) * 1092 = 1932 - 410
	//[(1.5 / 1.667) * 1092] + 410 = 1932
	
	//todo range and negative checks.
	
	f32Temp = f32Value;
	f32Temp /= C_ATA6870__VREF_V;
	f32Temp *= 1092.0F;
	f32Temp += 410.0F;
	
	//convert
	unT.u16 = (Luint16)f32Temp;
	
	//do some endianness
	unT2.u8[0] = unT.u8[1];
	unT2.u8[1] = unT.u8[0];
	
	//send
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		//send the UL thresh
		vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__UNDERVOLT_THRESH, &unT2.u8[0], 2U);
	}

	//todo:
	//do a read-back comparison
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

