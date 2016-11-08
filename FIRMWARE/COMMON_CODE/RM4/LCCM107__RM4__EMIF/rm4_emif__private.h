/**
 * @file		rm4_emif__private.h
 * @brief		Private structures for EMIF
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM107R0.FILE.004
 */

#ifndef _RM4_EMIF__PRIVATE_H_
#define _RM4_EMIF__PRIVATE_H_

	/* Emif Register Frame Definition */
	/** @struct RM4_EMIF__BASE_T
	*   @brief emifBASE Register Definition
	*
	*   This structure is used to access the EMIF module registers.
	*/
	typedef volatile struct emifBase
	{
		/**< 0x0000 Module ID Register */
		Luint32 MIDR;		  
		Luint32 AWCC;		  /**< 0x0004 Asynchronous wait cycle register*/
		Luint32 SDCR;		  /**< 0x0008 SDRAM configuration register */
		Luint32 SDRCR ;		/**< 0x000C Set Interrupt Enable Register */
		Luint32 CE2CFG;		/**< 0x0010 Asynchronous 1 Configuration Register */
		Luint32 CE3CFG;		/**< 0x0014 Asynchronous 2 Configuration Register */
		Luint32 CE4CFG;		/**< 0x0018 Asynchronous 3 Configuration Register */
		Luint32 CE5CFG;		/**< 0x001C Asynchronous 4 Configuration Register */
		Luint32 SDTIMR;		/**< 0x0020 SDRAM Timing Register */
		Luint32 dummy1[6];	 /** reserved **/
		Luint32 SDSRETR;	   /**< 0x003c SDRAM Self Refresh Exit Timing Register */
		Luint32 INTRAW;		/**< 0x0040 0x0020 Interrupt Vector Offset*/
		Luint32 INTMSK;		/**< 0x0044 EMIF Interrupt Mask Register */
		Luint32 INTMSKSET;	 /**< 48 EMIF Interrupt Mask Set Register */
		Luint32 INTMSKCLR;	 /**< 0x004c EMIF Interrupt Mask Register */
		Luint32 dummy2[6];	 /** reserved **/
		Luint32 PMCR;		  /**< 0x0068 Page Mode Control Register*/

	} RM4_EMIF__BASE_T;

	#define emifREG   ((RM4_EMIF__BASE_T *)0xFCFFE800U)


#endif //_RM4_EMIF__PRIVATE_H_
