/**
 * @file		RM4_CPULOAD.H
 * @brief		Main header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM663R0.FILE.001
 */

#ifndef _RM4_CPULOAD_H_
#define _RM4_CPULOAD_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		//the ratio used to compute CPU load (percentage) from system clock freq and counts.
		//200,000,000 / 200 * 10,000 = 100%
		#define C_RM4CPULOAD__CLK_DIVIDER							((Luint32)C_LOCALDEF__SYSTEM__HCLK_FREQ_MHZ * (Luint32)10000U);

		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strCPULoad
		{

			/** first cycle measurement*/
			Luint32 u32FirstCycleCount;

			/** The last CPU cycle counter */
			Luint32 u32LastCycleCount;

			/** The last computed percentage of load, in 10x */
			Luint32 u32LastPercent_X10;

			/** buffer to hold the samples */
			Luint16 u16Buffer[C_LOCALDEF__LCCM663__FILTER_WINDOW];

			/** The last filtering result */
			Luint16 u16FilterResult;

			/** our current filtering position */
			Luint16 u16FilterPos;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vRM4_CPULOAD__Init(void);
		void vRM4_CPULOAD__Process(void);
		void vRM4_CPULOAD__While_Entry(void);
		void vRM4_CPULOAD__While_Exit(void);
		Luint8 u8RM4_CPULOAD__Get_LoadPercent(void);

	//safetys
	#ifndef C_LOCALDEF__LCCM663__FILTER_WINDOW
		#error
	#endif

	#endif //#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_RM4_CPULOAD_H_

