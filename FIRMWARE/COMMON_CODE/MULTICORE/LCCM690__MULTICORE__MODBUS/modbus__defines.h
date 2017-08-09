/**
 * @file		MODBUS__DEFINES.H
 * @brief		Standard defines
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM690R0.FILE.002
 */

#ifndef _MODBUS_DEFINES_H_
#define _MODBUS_DEFINES_H_


	/** Maximum size of a ModBus frame */
	#define C_MODBUS__MAX_FRAME_SIZE_BYTES				(256U)


	// modbus timers in 10 ms units
	#define C_MODBUS__MAX_TURNAROUND_DELAY_MS			(150U)
	#define C_MODBUS__MAX_REPLYWAIT_MS					(1000)
	
#endif //_MODBUS_DEFINES_H_
