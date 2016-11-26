/**
 * @file		rm4_emac__dp83460_private.h
 * @brief		Private defines for the DP83640 PHY
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM254R0.FILE.004
 */


#ifndef RM4_EMAC__DP83640_PRIVATE_H_
#define RM4_EMAC__DP83640_PRIVATE_H_

	/*
	To simplify testing and the desing we only implement one of the 32 possible
	PHY's connected to the MDIO device. During reset we bootstrap the DP83640
	by setting the COL = 1 (via pullup) and the RXD pins low (via internal pulldowns)
	which has the effect of setting the address to 1
	 */
	#define C_DP83640__PHY_INDEX		1



#endif /* RM4_EMAC__DP83640_PRIVATE_H_ */
