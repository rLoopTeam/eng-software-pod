/**
 * @file		BQ76__LOCALDEF.H
 * @brief		Loocaldef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.003
 */

#if 0

/*******************************************************************************
BQ76PL536A - BMS DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

		/** number of devices in series */
		#define C_LOCALDEF__LCCM715__NUM_DEVICES							(1U)

		/** Average window, set to 0 for averaging off */
		#define C_LOCALDEF__LCCM715__AVERAGE_WINDOW							(16U)


		/** SPI TX / RX */
		#define M_LOCALDEF__LCCM715__SPI_TX_U8(value)

		/** Chip Select */
		#define M_LOCALDEF__LCCM715__LATCH__CS(x)							{}

		/** Convert Control */
		#define M_LOCALDEF__LCCM715__LATCH__CONV(x)							{}

		/** Data Ready Input (if not using interrupts) */
		#define M_LOCALDEF__LCCM715__PORT__DRDY()							{}

		/** Fault Input (if not using interrupts) */
		#define M_LOCALDEF__LCCM715__PORT__FAULT()							{}

		/** Alert Input (if not using interrupts) */
		#define M_LOCALDEF__LCCM715__PORT__ALERT()							{}


		/** Testing Options */
		#define C_LOCALDEF__LCCM715__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>

	#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

#endif //#if 0

