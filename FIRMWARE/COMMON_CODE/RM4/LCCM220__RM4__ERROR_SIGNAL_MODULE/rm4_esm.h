/**
 * @file		rm4_esm.h
 * @brief		Header for error signalling module
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM220R0.FILE.002
 */

#ifndef _RM4_ESM_H_
#define _RM4_ESM_H_
#ifndef WIN32

	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE == 1U
		/*****************************************************************************
		Includes
		*****************************************************************************/
		#include <RM4/LCCM220__RM4__ERROR_SIGNAL_MODULE/rm4_esm__private.h>
		#include <RM4/LCCM220__RM4__ERROR_SIGNAL_MODULE/rm4_esm__fault_flags.h>
		#include <RM4/LCCM220__RM4__ERROR_SIGNAL_MODULE/rm4_esm__fault_flags_g2.h>
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*****************************************************************************
		Structures
		*****************************************************************************/
		struct _strRM4ESM
		{

			/** Faults for ESM group 1 */
			FAULT_TREE__PUBLIC_T sFaultTree__Group1;

			/** Faults for ESM group 2 */
			FAULT_TREE__PUBLIC_T sFaultTree__Group2;

		};


	/** @typedef esmSelfTestFlag_t
	*   @brief ESM Self-Test Status Type Definition
	*
	*   This type is used to represent ESM Self-Test Status.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef enum esmSelfTestFlag
	{
		esmSelfTest_Passed = 0U,
		esmSelfTest_Active = 1U,
		esmSelfTest_NotStarted = 2U,
		esmSelfTest_Failed = 3U
	}esmSelfTestFlag_t;

	/* Configuration registers */
	/*****************************************************************************
	*****************************************************************************/
	typedef struct esm_config_reg
	{
		Luint32 CONFIG_EEPAPR1;
		Luint32 CONFIG_IESR1;
		Luint32 CONFIG_ILSR1;
		Luint32 CONFIG_LTCPR;
		Luint32 CONFIG_EKR;
		Luint32 CONFIG_IEPSR4;
		Luint32 CONFIG_IESR4;
		Luint32 CONFIG_ILSR4;
	} esm_config_reg_t;


	//function ptoros
	void vRM4_ESM__Init(void);
	Luint32 u32RM4_ESM__Get_FaultFlags_G1(void);
	Luint32 u32RM4_ESM__Get_FaultFlags_G2(void);

	void vRM4_ESM__Group1_Notification(Luint32 channel);
	void vRM4_ESM__Group2_Notification(Luint32 channel);

	Luint32 u32RM4_ESM__Get_Error(void);
	void vRM4_ESM__Enable_Error(Luint64 channels);


	void vRM4_ESM__HighInterrupt(void);
	esmSelfTestFlag_t tRM4_ESM__SelfTestStatus(void);
	esmSelfTestFlag_t pRM4_ESM__EnterSelfTest(void);
	Luint64 vRM4_ESM__Get_StatusBuffer(Luint64 u64Channels);
	Luint64 vRM4_ESM__Get_Status(Luint32 u32Group, Luint64 u64Channels);
	void vRM4_ESM__Set_CounterPreloadValue(Luint32 u32Value);
	void vRM4_ESM__ClearStatusBuffer(Luint64 u64Channels);
	void vRM4_ESM__ClearStatus(Luint32 u32Group, Luint64 u64Channels);
	void vRM4_ESM__Set_InterruptLevel(Luint64 u64Channels, Luint64 u64Flags);
	void vRM4_ESM__DisableInterrupt(Luint64 u64Channels);
	void vRM4_ESM__EnableInterrupt(Luint64 u64Channels);
	void vRM4_ESM__ActivateNormalOperation(void);
	void vRM4_ESM__TriggerErrorPinReset(void);
	void vRM4_ESM__DisableError(Luint64 u64Channels);





	#endif //C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE
#endif //WIN32
#endif//
