/**
 * @file		ATA6870__SCAN.C
 * @brief		Helpers for scanning the bus for any devices, up to the max of 16 devices.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.007
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__SCAN
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Scans the bus for devices
 * 
 * @st_funcMD5		96343991C433CB27E0A245629F759BD5
 * @st_funcID		LCCM650R0.FILE.007.FUNC.001
 */
void vATA6870_SCAN__Start(void)
{
	Luint8 u8Counter;
	Luint8 u8Temp;
	Luint8 u8RevID;
	Luint8 u8MFirst;
	Luint8 u8PowerEn;

	//Search the max devices possible on the bus
	//we want to scan more than the number of devices we have because not only should any devices we
	//have listed be available, but we should not have any additional devices that are maybe even configured incorrectly.
	for(u8Counter = 0U; u8Counter < 16U; u8Counter++)
	{

		//read the device
		vATA6870_LOWLEVEL__Reg_ReadU8(u8Counter, ATA6870_REG__REV_ID, &u8Temp, 1U);

		//get the revision ID
		u8RevID = u8Temp;
		u8RevID &= 0x07U;

		//see if we are marked as the first device (hardware pin connected)
		u8MFirst = u8Temp;
		u8MFirst >>= 3U;
		u8MFirst &= 0x01U;

		//check the power enable input
		u8PowerEn = u8Temp;
		u8PowerEn >>= 4U;
		u8PowerEn &= 0x01U;

		//todo:
		//Update the system level structures
		
	}//for(u8Counter = 0U; u8Counter < 16U; u8Counter++)


}



//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_CRC
	#error
#endif

#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif



