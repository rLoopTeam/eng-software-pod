/**
 * @file		software_fifo.h
 * @brief		Soft fifo main header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM357R0.FILE.002
 */

#ifndef _SOFTWARE_FIFO_H_
#define _SOFTWARE_FIFO_H_

	#include <localdef.h>
	
	#if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo__public.h>
	
		//function prots
		void vSOFTFIFO__Init(SOFTWARE_FIFO__USER_T * pUserT, Luint8 u8Depth);
		Lint16 s16SOFTFIFO__Push(SOFTWARE_FIFO__USER_T * pUserT);
		Lint16 s16SOFTFIFO__Pop(SOFTWARE_FIFO__USER_T * pUserT);
		Luint8 u8SOFTFIFO__Is_Empty(const SOFTWARE_FIFO__USER_T * pUserT);
		Luint8 u8SOFTFIFO__Is_Full(const SOFTWARE_FIFO__USER_T * pUserT);
		Luint8 u8SOFTFIFO__Get__WritePosition(const SOFTWARE_FIFO__USER_T * pUserT);
		Luint8 u8SOFTFIFO__Get_IsWriteBusy(const SOFTWARE_FIFO__USER_T *pUserT);
		Luint8 u8SOFTFIFO__Get_IsReadBusy(const SOFTWARE_FIFO__USER_T *pUserT);
	
		#if C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC == 1U
			DLL_DECLARATION void vLCCM357_TS_001(void);
			DLL_DECLARATION void vLCCM357_TS_004(void);
			DLL_DECLARATION void vLCCM357_TS_005(void);
			DLL_DECLARATION void vLCCM357_TS_006(void);
			DLL_DECLARATION void vLCCM357R0_TS_011(void);
			DLL_DECLARATION void vLCCM357R0_TS_012(void);
		#endif

	#endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE
	#ifndef C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE
		#error
	#endif



#endif //_SOFTWARE_FIFO_H_

