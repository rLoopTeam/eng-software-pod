/**
 * @file		fault_tree__public.h
 * @brief		Public structures for the fault tree
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM284R0.FILE.011
 */

#ifndef _FAULT_TREE_PUBLIC_H_
#define _FAULT_TREE_PUBLIC_H_


	/** The public structure for the fault tree data type to be used with every application */
	typedef struct
	{

		/** This is the fault flag.  It is set if any of the fault bits are set. */
		Luint8 u8FaultFlag;

		/** Support up to a maximum of 64 bits of fault data. */
		Luint32 u32Flags[2U];

	}FAULT_TREE__PUBLIC_T;


#endif //_FAULT_TREE_PUBLIC_H_

