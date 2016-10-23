/**
 * @file		RM4_EFUSE.H
 * @brief		Efuse Header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @st_fileID	LCCM224R0.FILE.002
 */

#ifndef _RM4_EFUSE_H_
#define _RM4_EFUSE_H_

	#include <localdef.h>
	/* Efc Register Frame Definition */
	/** @struct efcBase
	*   @brief Efc Register Frame Definition
	*
	*   This type is used to access the Efc Registers.
	*/
	/** @typedef efcBASE_t
	*   @brief Efc Register Frame Type Definition
	*
	*   This type is used to access the Efc Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct efcBase
	{
		Luint32 INSTRUCTION;    			/* 0x0	INSTRUCTION AN DUMPWORD REGISTER	*/
		Luint32 ADDRESS;			    	/* 0x4 ADDRESS REGISTER    					*/
		Luint32 DATA_UPPER;			    /* 0x8 DATA UPPER REGISTER    				*/
		Luint32 DATA_LOWER;				/* 0xc DATA LOWER REGISTER    				*/
		Luint32 SYSTEM_CONFIG;				/* 0x10 SYSTEM CONFIG REGISTER    			*/
		Luint32 SYSTEM_STATUS;				/* 0x14 SYSTEM STATUS REGISTER    			*/
		Luint32 ACCUMULATOR;				/* 0x18 ACCUMULATOR REGISTER    			*/
		Luint32 BOUNDARY;			    	/* 0x1C BOUNDARY REGISTER 					*/
		Luint32 KEY_FLAG;			    	/* 0x20 KEY FLAG REGISTER    				*/
		Luint32 KEY;			        	/* 0x24	KEY REGISTER 						*/
		Luint32   rsvd1;			        /* 0x28	RESERVED 							*/
		Luint32 PINS;				        /* 0x2C  PINS REGISTER						*/
		Luint32 CRA;				        /* 0x30  CRA								*/
		Luint32 READ;				        /* 0x34 READ REGISTER						*/
		Luint32 PROGRAMME;				    /* 0x38 PROGRAMME REGISTER					*/
		Luint32 ERROR;				        /* 0x3C	ERROR STATUS REGISTER				*/
		Luint32 SINGLE_BIT;				/* 0x40	SINGLE BIT ERROR 					*/
		Luint32 TWO_BIT_ERROR;				/* 0x44	DOUBLE BIT ERROR 					*/
		Luint32 SELF_TEST_CYCLES;			/* 0x48	SELF TEST CYCLEX					*/
		Luint32 SELF_TEST_SIGN;			/* 0x4C SELF TEST SIGNATURE					*/
	} efcBASE_t;

	#define efcREG   ((efcBASE_t *)0xFFF8C000U)



#endif //_RM4_EFUSE_H_

