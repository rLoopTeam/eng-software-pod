/**
 * @file		rm4_gio__private.h
 * @brief		Private defs for the GIO
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM133R0.FILE.005
 */

#ifndef _RM4_GIO_PRIVATE_H_
#define _RM4_GIO_PRIVATE_H_

	/* Gio Register Frame Definition */
	/** @struct gioBase
	* @brief GIO Base Register Definition
	*
	* This structure is used to access the GIO module registers.
	*/
	/** @typedef RM4_GIO__BASE_T
	* @brief GIO Register Frame Type Definition
	*
	* This type is used to access the GIO Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct gioBase
	{
		Luint32 GCR0;	 /**< 0x0000: Global Control Register */
		Luint32 u32RM4_GIO__rsvd;	/**< 0x0004: Reserved*/
		Luint32 INTDET;	/**< 0x0008: Interrupt Detect Register*/
		Luint32 POL;	 /**< 0x000C: Interrupt Polarity Register */
		Luint32 ENASET;	/**< 0x0010: Interrupt Enable Set Register */
		Luint32 ENACLR;	/**< 0x0014: Interrupt Enable Clear Register */
		Luint32 LVLSET;	/**< 0x0018: Interrupt Priority Set Register */
		Luint32 LVLCLR;	/**< 0x001C: Interrupt Priority Clear Register */
		Luint32 FLG;	 /**< 0x0020: Interrupt Flag Register */
		Luint32 OFF1;	 /**< 0x0024: Interrupt Offset A Register */
		Luint32 OFF2;	 /**< 0x0028: Interrupt Offset B Register */
	} RM4_GIO__BASE_T;


	/** @struct gioPort
	* @brief GIO Port Register Definition
	*/
	/** @typedef RM4_GIO__PORT_T
	* @brief GIO Port Register Type Definition
	*
	* This type is used to access the GIO Port Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct gioPort
	{
		Luint32 DIR;	/**< 0x0000: Data Direction Register */
		Luint32 DIN;	/**< 0x0004: Data Input Register */
		Luint32 DOUT; /**< 0x0008: Data Output Register */
		Luint32 DSET; /**< 0x000C: Data Output Set Register */
		Luint32 DCLR; /**< 0x0010: Data Output Clear Register */
		Luint32 PDR;	/**< 0x0014: Open Drain Register */
		Luint32 PULDIS; /**< 0x0018: Pullup Disable Register */
		Luint32 PSL;	/**< 0x001C: Pull Up/Down Selection Register */
	} RM4_GIO__PORT_T;


	/** @def gioREG
	* @brief GIO Register Frame Pointer
	*
	* This pointer is used by the GIO driver to access the gio module registers.
	*/
	#define gioREG ((RM4_GIO__BASE_T *)0xFFF7BC00U)

	/** @def gioPORTA
	* @brief GIO Port (A) Register Pointer
	*
	* Pointer used by the GIO driver to access PORTA
	*/
	#define gioPORTA ((RM4_GIO__PORT_T *)0xFFF7BC34U)

	/** @def gioPORTB
	* @brief GIO Port (B) Register Pointer
	*
	* Pointer used by the GIO driver to access PORTB
	*/
	#define gioPORTB ((RM4_GIO__PORT_T *)0xFFF7BC54U)



#endif //_RM4_GIO_PRIVATE_H_
