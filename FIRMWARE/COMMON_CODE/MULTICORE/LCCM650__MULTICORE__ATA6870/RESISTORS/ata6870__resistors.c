/**
 * @file		ATA6870__RESISTORS.C
 * @brief		Discharge resistor control
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.008
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__RESISTORS
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Turn on an individual discharge resistor.
 * 
 * @param[in]		u8CellIndex				The specific cell index from 0 to 6
 * @param[in]		u8DeviceIndex			The BMS device index
 * @st_funcMD5		DB12A9B1E58AB28C4E786FAAF9689A77
 * @st_funcID		LCCM650R0.FILE.008.FUNC.001
 */
void vATA6870_RES__TurnOn(Luint8 u8DeviceIndex, Luint8 u8CellIndex)
{
	//Taking address of near auto variable, reviewed
	/*lint -e934*/
	Luint8 u8Temp;
	Luint8 u8Mask;

	//read our old discharge selector
	vATA6870_LOWLEVEL__Reg_ReadU8(u8DeviceIndex, ATA6870_REG__CH_DISCHARGE, &u8Temp, 1U);

	//generate our cell index mask
	u8Mask = 0x01U;
	u8Mask <<= u8CellIndex;

	//mask out
	u8Temp |= u8Mask;

	//update
	vATA6870_LOWLEVEL__Reg_WriteU8(u8DeviceIndex, ATA6870_REG__CH_DISCHARGE, &u8Temp, 1U);
	
	/*lint +e934*/
}


/***************************************************************************//**
 * @brief
 * Turn off an individual discharge resistor.
 * 
 * @param[in]		u8CellIndex				The specific cell index from 0 to 6
 * @param[in]		u8DeviceIndex			The BMS device index
 * @st_funcMD5		5E59534CAF73A6A9FC09D0B164DCDA4A
 * @st_funcID		LCCM650R0.FILE.008.FUNC.002
 */
void vATA6870_RES__TurnOff(Luint8 u8DeviceIndex, Luint8 u8CellIndex)
{
	//Taking address of near auto variable, reviewed
	/*lint -e934*/
	Luint8 u8Temp;
	Luint8 u8Mask;

	//read our old discharge selector
	vATA6870_LOWLEVEL__Reg_ReadU8(u8DeviceIndex, ATA6870_REG__CH_DISCHARGE, &u8Temp, 1U);

	//generate our cell index mask
	u8Mask = 0x01U;
	u8Mask <<= u8CellIndex;

	//mask out to switch off
	u8Mask ^= 0xFFU;
	u8Temp &= u8Mask;

	//update
	vATA6870_LOWLEVEL__Reg_WriteU8(u8DeviceIndex, ATA6870_REG__CH_DISCHARGE, &u8Temp, 1U);
	
	/*lint +e934*/

}

/***************************************************************************//**
 * @brief
 * Turn off all resistors
 * 
 * @param[in]		u8DeviceIndex			The BMS device index
 * @st_funcMD5		E0486D18237104702DD1E0CF589B1632
 * @st_funcID		LCCM650R0.FILE.008.FUNC.003
 */
void vATA6870_RES__TurnAllOff(Luint8 u8DeviceIndex)
{
	//Taking address of near auto variable, reviewed
	/*lint -e934*/
	Luint8 u8Temp;
	
	//all off
	u8Temp = 0U;
	
	//update
	vATA6870_LOWLEVEL__Reg_WriteU8(u8DeviceIndex, ATA6870_REG__CH_DISCHARGE, &u8Temp, 1U);

	/*lint +e934*/
}


#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif

