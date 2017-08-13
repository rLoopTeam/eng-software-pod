/**
 * @file		BQ76__REG_DEFS.H
 * @brief		Register definitions.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.004
 */

#ifndef MULTICORE_LCCM715__MULTICORE__BQ76PL536A_BQ76__REG_DEFS_H_
#define MULTICORE_LCCM715__MULTICORE__BQ76PL536A_BQ76__REG_DEFS_H_


	typedef enum
	{

		/** The STATUS register provides information about the current state of the bq76PL536A. */
		BQ76_REG__DEVICE_STATUS = 0x00U,

		BQ76_REG__VCELL1 = 0x03U,
		
		/* The ALERT_STATUS register provides information about the source of the ALERT signal. The host must clear
		 * each alert flag by writing a 1 to the bit that is set. The exception is bit 4, which may be written 1 or 0 as needed
		 * to implement self-test of the IC stack and wiring */
		BQ76_REG__ALERT_STATUS = 0x20U,

		/* The FAULT_STATUS register provides information about the source of the FAULT signal. The host must clear
		 * each fault flag by writing a 1 to the bit that is set. The exception is bit 4, which may be written 1 or 0 as needed
		 * to implement self-test of the IC stack and wiring. */
		BQ76_REG__FAULT_STATUS = 0x21U,

		BQ76_REG__ADC_CONTROL = 0x30U,
		
		BQ76_REG__CB_CTRL = 0x32U,

		BQ76_REG__CB_TIME = 0x33U,

		BQ76_REG__ADC_CONVERT = 0x34U,
		
		/* The ADDRESS_CONTROL register allows the host to assign an address to the bq76PL536A for communication.
		 * The default for this register is 0x00 at RESET. */
		BQ76_REG__ADDX_CONTROL = 0x3BU,

		
		BQ76_REG__RESET = 0x3CU,

	}TE_BQ76__REG_DEFS;


#endif /* MULTICORE_LCCM715__MULTICORE__BQ76PL536A_BQ76__REG_DEFS_H_ */
