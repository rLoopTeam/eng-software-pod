/**
 * @file		fault_tree.h
 * @brief		Main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM284R0.FILE.009
 */

#ifndef _FAULT_TREE_H_
#define _FAULT_TREE_H_

	
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE == 1U
		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>


		/*******************************************************************************
		Function Protos
		*******************************************************************************/
		void vSIL3_FAULTTREE__Init(FAULT_TREE__PUBLIC_T *pFaultTree);
		void vSIL3_FAULTTREE__Set_Flag(FAULT_TREE__PUBLIC_T *pFaultTree, Luint32 u32FlagIndex);
		void vSIL3_FAULTTREE__Clear_Flag(FAULT_TREE__PUBLIC_T *pFaultTree, Luint32 u32FlagIndex);
		Luint8 u8SIL3_FAULTTREE__Get_Fault(const FAULT_TREE__PUBLIC_T *pFaultTree, Luint32 u32FlagIndex);
		

		//testing
		#if C_LOCALDEF__LCCM284__ENABLE_TEST_SPEC == 1U
			DLL_DECLARATION void vLCCM284_TS_001(void);
			DLL_DECLARATION void vLCCM284_TS_002(void);
			DLL_DECLARATION void vLCCM284_TS_003(void);
			DLL_DECLARATION void vLCCM284_TS_004(void);
			DLL_DECLARATION void vLCCM284_TS_005(void);
			DLL_DECLARATION void vLCCM284_TS_006(void);
			DLL_DECLARATION void vLCCM284_TS_007(void);
			DLL_DECLARATION void vLCCM284_TS_008(void);
			DLL_DECLARATION void vLCCM284_TS_009(void);
			DLL_DECLARATION void vLCCM284_TS_010(void);
		#endif

	#endif //C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE



#endif //FAULT_TREE
