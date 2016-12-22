/**
 * @file		ATA6870__STATUS.C
 * @brief		Handles the status control
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.010
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__STATUS
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Returns the Op Status register details
 * 
 * @param[in]		u8DeviceIndex			The BMS device idnex
 * @return			0 = all good\n
 * 					1 = In Progress\n
 *					2 = Finished\n
 * 					3 = Some Error
 * @st_funcMD5		5EA1B4E990C07EB39B0D8105C534CF31
 * @st_funcID		LCCM650R0.FILE.010.FUNC.001
 */
Luint8 u8ATA6870_STATUS__Get_Op_Status(Luint8 u8DeviceIndex)
{
	Luint8 u8StatusOP;
	
	//Clear
	u8StatusOP = 0xFFU;
	
	//Get
	vATA6870_LOWLEVEL__Reg_ReadU8(u8DeviceIndex, ATA6870_REG__OP_STATUS, &u8StatusOP, 1U);
	
	//return it
	return u8StatusOP;

}

/***************************************************************************//**
 * @brief
 * Gets the status of the IRQ system
 * 
 * @param[in]		u8DeviceIndex			The BMS device index
 * @return			Bit Mask:\n
 *					0x01 = Data Ready - Conversion has completed\n
 *					0x02 = LF Timer elapsed\n
 *					0x04 = Comms Error / Bad SPI command\n
 *					0x08 = Undervoltage Detected\n
 *					0x10 = Checksum Error\n
 *					0x20 = Power On Reset Detected\n
 *					0x40 = Test Mode On.
 * @st_funcMD5		45D369BA4CD5A839AF91394683510ACD
 * @st_funcID		LCCM650R0.FILE.010.FUNC.002
 */
Luint8 u8ATA6870_STATUS__Get_IRQ_Status(Luint8 u8DeviceIndex)
{
	Luint8 u8StatusIRQ;
	
	//Init
	u8StatusIRQ = 0xFFU;
	
	//Get
	vATA6870_LOWLEVEL__Reg_ReadU8(u8DeviceIndex, ATA6870_REG__IRQ_STATUS, &u8StatusIRQ, 1U);
	
	//return it
	return u8StatusIRQ;

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

