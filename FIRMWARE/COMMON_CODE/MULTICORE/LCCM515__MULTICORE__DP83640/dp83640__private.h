/**
 * @file		DP83640__PRIVATE.H
 * @brief		Private Types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM515R0.FILE.007
 */


#ifndef SOURCE_LCCM515__MULTICORE__DP83640_DP83640__PRIVATE_H_
#define SOURCE_LCCM515__MULTICORE__DP83640_DP83640__PRIVATE_H_



	#define DPS83640_PHYID			0x20005CE1u	/** PHY ID Register 1 & 2 values for DPS83640 (Same for TMS570 & RM devices */

	/* PHY register offset definitions */
	#define DP83640_PHY_BCR									(0u)
	#define DP83640_PHY_BSR									(1u)
	#define DP83640_PHY_ID1									(2u)
	#define DP83640_PHY_ID2									(3u)
	#define DP83640_PHY_AUTONEG_ADV							(4u)
	#define DP83640_PHY_REGISTER__LINK_PARTNER_ABLTY		(5u)
	#define DP83640_PHY_REGISTER__STATUS					(0x10U)
	#define DP83640_PHY_REGISTER__PAGESEL					(0x13U)
	#define DP83640_PHY_REGISTER__RMII_AND_BYPASS			 (0x17U)

	#define DP83640_PHY_PHYCR						 0x19U
	#define DP83640_PHY_CDCTRL1						0x1BU

	#define DP83640_PHY__PAGE2__LNE100_DET					(0x14U)


	/* PHY status definitions */
	#define DP83640_PHY_ID_SHIFT					 (16u)
	#define DP83640_PHY_SOFTRESET					 (0x8000)
	#define DP83640_PHY_AUTONEG_ENABLE				(0x1000u)
	#define DP83640_PHY_AUTONEG_RESTART			 (0x0200u)
	#define DP83640_PHY_AUTONEG_COMPLETE			 (0x0020u)
	#define DP83640_PHY_AUTONEG_INCOMPLETE			(0x0000u)
	#define DP83640_PHY_AUTONEG_STATUS				(0x0020u)
	#define DP83640_PHY_AUTONEG_ABLE				 (0x0008u)
	#define DP83640_PHY_LPBK_ENABLE				 (0x4000u)
	#define DP83640_PHY_LINK_STATUS				 (0x0004u)



	/* PHY ID. The LSB nibble will vary between different phy revisions */
	#define DP83640_PHY_ID				 (0x0007C0F0u)
	#define DP83640_PHY_ID_REV_MASK		 (0x0000000Fu)

	/* Pause operations */
	#define DP83640_PAUSE_NIL				(0x0000u)
	#define DP83640_PAUSE_SYM				(0x0400u)
	#define DP83640_PAUSE_ASYM			 (0x0800u)
	#define DP83640_PAUSE_BOTH_SYM_ASYM	 (0x0C00u)

	/* 100 Base TX Full Duplex capablity */
	#define DP83640_100BTX_HD				(0x0000u)
	#define DP83640_100BTX_FD				(0x0100u)

	/* 100 Base TX capability */
	#define DP83640_NO_100BTX				(0x0000u)
	#define DP83640_100BTX				 (0x0080u)

	/* 10 BaseT duplex capabilities */
	#define DP83640_10BT_HD				 (0x0000u)
	#define DP83640_10BT_FD				 (0x0040u)

	/* 10 BaseT ability*/
	#define DP83640_NO_10BT				 (0x0000u)
	#define DP83640_10BT					 (0x0020u)



#endif /* SOURCE_LCCM515__MULTICORE__DP83640_DP83640__PRIVATE_H_ */
