/**
 * @file		ATA6870__LOCALDEF.H
 * @brief		Local definitions template for the ATA6870 device driver
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.003
 */

#if 0

/*******************************************************************************
ATA6870N - BATTERY MANAGEMENT DEVICE
*******************************************************************************/
	#define C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

		//architecture
		#define C_LOCALDEF__LCCM650__USE_ON_RM4								(0U)
	
		/** number of devices in series */
		#define C_LOCALDEF__LCCM650__NUM_DEVICES							(1U)

		/** Use checksum support on the ATA comms or not? */
		#define C_LOCALDEF__LCCM650__ENABLE_CRC								(0U)

		/** Average window, set to 0 for averaging off */
		#define C_LOCALDEF__LCCM650__AVERAGE_WINDOW							(16U)

		//setup for functions
		#define M_LOCALDEF__LCCM650__NCS_TRIS(dir)							{}
		#define M_LOCALDEF__LCCM650__NCS_LATCH(val)							{}
		#define M_LOCALDEF__LCCM650__SPI_TX_U8								{}

		#define M_LOCALDEF__LCCM650__POWER_ENABLE_TRIS(x)					{if(x == 0){ vRM4_GIO__Set_BitDirection(gioPORTB, 2U, GIO_DIRECTION__OUTPUT); }else{ vRM4_GIO__Set_BitDirection(gioPORTB, 2U, GIO_DIRECTION__INPUT); }}
		#define M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(x)					{vRM4_GIO__Set_Bit(gioPORTB, 2U, x); }

		#define M_LOCALDEF__LCCM650__POWER_AVAIL_TRIS(x)					{if(x == 0){ vRM4_GIO__Set_BitDirection(gioPORTB, 5U, GIO_DIRECTION__OUTPUT); }else{ vRM4_GIO__Set_BitDirection(gioPORTB, 5U, GIO_DIRECTION__INPUT); }}
		#define M_LOCALDEF__LCCM650__POWER_AVAIL_PORT()						u32RM4_GIO__Get_Bit(gioPORTB, 5U)

		
		/** Testing Options */
		#define C_LOCALDEF__LCCM650__ENABLE_TEST_SPEC						(0U)
		
		
		/** Main include file */
		#include <MULTICORE/LCCM650__MULTICORE__ATA6870/ata6870.h>
	#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

#endif //#if 0

