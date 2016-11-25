/**
 * @file		rm4_bist.h
 * @brief		Built in self test main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM227R0.FILE.002
 */

#ifndef _RM4_BIST_H_
#define _RM4_BIST_H_

#include <localdef.h>

	#include <RM4/LCCM227__RM4__BIST/rm4_bist__fault_flags.h>
	#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

	struct _strRM4BIST
	{
		FAULT_TREE__PUBLIC_T sFaultFlags;

	};

	/* PBIST Register Frame Definition */
	/** @struct pbistBase
	*   @brief PBIST Base Register Definition
	*
	*   This structure is used to access the PBIST module registers.
	*/
	/** @typedef pbistBASE_t
	*   @brief PBIST Register Frame Type Definition
	*
	*   This type is used to access the PBIST Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct pbistBase
	{
		Luint32 RAMT;			/* 0x0160: RAM Configuration Register */
		Luint32 DLR;			/* 0x0164: Datalogger Register */
		Luint32   rsvd1[6U];	/* 0x0168 */
		Luint32 PACT;			/* 0x0180: PBIST Activate Register */
		Luint32 PBISTID;		/* 0x0184: PBIST ID Register */
		Luint32 OVER;			/* 0x0188: Override Register */
		Luint32   rsvd2;		/* 0x018C */
		Luint32 FSRF0;			/* 0x0190: Fail Status Fail Register 0 */
		Luint32 FSRF1;			/* 0x0194: Fail Status Fail Register 1 */
		Luint32 FSRC0;			/* 0x0198: Fail Status Count Register 0 */
		Luint32 FSRC1;			/* 0x019C: Fail Status Count Register 1 */
		Luint32 FSRA0;			/* 0x01A0: Fail Status Address 0 Register */
		Luint32 FSRA1;			/* 0x01A4: Fail Status Address 1 Register */
		Luint32 FSRDL0;		/* 0x01A8: Fail Status Data Register 0 */
		Luint32   rsvd3;		/* 0x01AC */
		Luint32 FSRDL1;		/* 0x01B0: Fail Status Data Register 1 */
		Luint32   rsvd4[3U];	/* 0x01B4 */
		Luint32 ROM;			/* 0x01C0: ROM Mask Register */
		Luint32 ALGO;			/* 0x01C4: Algorithm Mask Register */
		Luint32 RINFOL;		/* 0x01C8: RAM Info Mask Lower Register */
		Luint32 RINFOU;		/* 0x01CC: RAM Info Mask Upper Register */
	} pbistBASE_t;

	#define pbistREG   ((pbistBASE_t *)0xFFFFE560U)

	//Function Protos
	void vRM4_BIST__Init(void);
	Luint32 u32RM4_BIST__Get_FaultFlags(void);

	Luint8 u8RM4_BIST__PortTestStatus(Luint32 port);
	Luint8 u8RM4_BIST__IsTestPassed(void);
	Luint8 u8RM4_BIST__IsTestCompleted(void);
	void vRM4_BIST__Stop(void);
	void vRM4_BIST__Run(Luint32 raminfoL, Luint32 algomask);
	void vRM4_BIST__SelfCheck(void);

	//errata
	void errata_PBIST_4(void);



#endif //_RM4_BIST_H_
