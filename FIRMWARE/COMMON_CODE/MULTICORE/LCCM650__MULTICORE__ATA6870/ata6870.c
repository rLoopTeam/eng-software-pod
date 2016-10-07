/**
 * @file		ATA6870.C
 * @brief		Top level file for the ATA6870N device
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__CORE
 * @ingroup ATA6870
 * @{ */

#include "ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
struct _str6870 sATA6870;

/***************************************************************************//**
 * @brief
 * Init any ATA6870 systems
 * 
 * @st_funcMD5		99D6BF2EA733AE85B32BE7F078646C43
 * @st_funcID		LCCM650R0.FILE.000.FUNC.001
 */
void vATA6870__Init(void)
{
	//Taking address of near auto variable, reviewed
	/*lint -e934*/ 
	Luint8 u8Counter;
	Luint8 u8Temp;

	//setup the lowlevel
	vATA6870_LOWLEVEL__Init();
	
	//setup the interrupts
	vATA6870_INT__Init();

	//init the blancer subsystem
	vATA6870_BALANCE__Init();
	
	//switch on
	vATA6870_LOWLEVEL__PowerOn();

	//delay a bit for things to settle
	vRM4_DELAYS__Delay_mS(100U);

	//setup and get the basic BMS pods operational
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{

		//setup the control register with CRC or not
		#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
			u8Temp = 0x10U;
		#else
			u8Temp = 0x00U;
		#endif
		vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__CONTROL, &u8Temp, 1U);

		//setup the interupts
		//Only do the important onces for now
		u8Temp = 0x16U;
		vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__IRQ_MASK, &u8Temp, 1U);

		//Other house keeping issues:
		//Todo
		//1. Check under voltage issues
		//2. Check comms actually works.

	}


	//make sure we have our devices
	vATA6870_SCAN__Start();

	/*lint +e934*/ 

}

/***************************************************************************//**
 * @brief
 * Process any ATA6870 tasks
 * 
 * @st_funcMD5		B36C2CF202BFF0A45AD77EE21E6F3822
 * @st_funcID		LCCM650R0.FILE.000.FUNC.002
 */
void vATA6870__Process(void)
{

	//process any balancer tasks.
	vATA6870_BALANCE__Process();

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

