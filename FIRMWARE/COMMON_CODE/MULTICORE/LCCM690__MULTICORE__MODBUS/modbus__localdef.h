/**
 * @file		MODBUS__LOCALDEF.H
 * @brief		Localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM690R0.FILE.003
 */

#if 0

/*******************************************************************************
SIL3 - MODBUS MASTER / SLAVE INTERFACE
*******************************************************************************/
	#define C_LOCALDEF__LCCM690__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM690__ENABLE_THIS_MODULE == 1U

		/** Personality Master / nSlave */
		#define C_LOCALDEF__LCCM690__PERSONALITY_MASTER						(0U)

		/** If we are a slave, set the maximum number of registers supported
		 * This will go into the register pool and we can configure each register
		 * individually after this in software
		 */
		#define C_LOCALDEF__LCCM690__NUM_SLAVE_REGISTERS					(1U)

		/** Serial port function */
		#define M_LOCALDEF__LCCM690__SERIAL_TX_ARRAY_U8(x, len)				{vRM4_SCI_TX__Tx_U8Array(SCI_CHANNEL__3, len, x);}

		/** TX Enable Pin (Active High) */
		#define M_LOCALDEF__LCCM690__DRIVER_TX_LATCH(x)						{vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 7U, x);}

		/** Testing Options */
		#define C_LOCALDEF__LCCM690__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <MULTICORE/LCCM690__MULTICORE__MODBUS/modbus.h>
		
	#endif //#if C_LOCALDEF__LCCM690__ENABLE_THIS_MODULE == 1U

#endif //#if 0

