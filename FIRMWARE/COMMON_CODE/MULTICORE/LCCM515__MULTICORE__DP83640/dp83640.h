/**
 * @file		DP83640.H
 * @brief		Main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM515R0.FILE.002
 */

#ifndef _DP83640_H_
#define _DP83640_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM515__MULTICORE__DP83640/dp83640__private.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct	_strDP83640
		{
			//This is the PHY Addx on the MDIO, only available after the PHY is up
			Luint16 u16PHY_Addx;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vDP83640__Init(void);
		void vDP83640__Process(void);
		Luint16 u16DP83640__PHY_Detect(void);
		Luint16 u16DP83640__Get_PHY_Addx(void);

		Luint32 u32DP83640__Get_ID(Luint32 u32PhyIndex);
		void vDP83640__Page_Select(Luint32 u32PhyIndex, Luint8 u8Page);
		Lint16 s16DP83640__AutoNegotiate(Luint32 u32PhyIndex, Luint16 u16Value);
		Lint16 s16DP83640__AutoNegotiate_AsyncStart(Luint32 u32PhyIndex, Luint16 u16Value);
		Lint16 s16DP83640__AutoNegotiate_AsyncCheck(Luint32 u32PhyIndex, Luint16 u16Value);

		Lint16 s16DP83640__Get_PartnerAbility(Luint32 u32PhyIndex, Luint16 * pu16PartnerAbility);
		Luint8 u8DP83640__Get_LinkStatus(Luint32 u32PhyIndex);
		Luint8 u8DP83640__Get_PartnerSpeed100Mb(Luint32 u32PhyIndex);
		Luint8 u8DP83640__Enable_Loopback(Luint32 u32PhyIndex);
		Lint16 s16DP83640__Force_100M_FD(Luint32 u32PhyIndex);
		Lint16 s16DP83640__Enable_BIST(Luint32 u32PhyIndex);
		Luint8 u8DP83640__Is_BISTComplete(Luint32 u32PhyIndex);

		//cable detect
		Luint8 u8DP83640_CABLE__Get_CableLength(Luint32 u32PhyIndex);
		Luint8 u8DP83640_CABLE__Get_MDIPairs_Swapped(Luint32 u32PhyIndex);
		Luint8 u8DP83640_CABLE__Get_InvertedPolarity(Luint32 u32PhyIndex);


		//atchitecture specific stuff.
		Lint16 s16DP83640_MDIO__Read_Register(Luint32 u32PhyIndex, Luint32 u32RegisterNum, Luint16 * pu16Data);
		void vDP83640_MDIO__Write_Register(Luint32 u32PhyIndex, Luint32 u32RegIndex, Luint16 u16Value);

		//testing
		#if C_LOCALDEF__LCCM515__ENABLE_TEST_SPEC == 1U

		#endif

		//safetys
		#if C_LOCALDEF__LCCM515__USE_ON_RM4 == 0U
			#if C_LOCALDEF__LCCM515__USE_ON_XILINX == 0U
				#error
			#endif
		#endif


	#endif //#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE
		#error
	#endif

#endif //_DP83640_H_

