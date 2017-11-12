/**
 * @file		software_fifo__public.h
 * @brief		Public data types for the sofware fifo
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM357R0.FILE.004
 */



#ifndef __SOFTWARE_FIFO_PUBLIC_H_
#define __SOFTWARE_FIFO_PUBLIC_H_

	/*******************************************************************************
	Defines
	*******************************************************************************/
	#if C_LOCALDEF__LCCM357__FIFO_DEPTH_U16 == 1U
		#define C_SOFTFIFO__DT												Luint16
	#elif C_LOCALDEF__LCCM357__FIFO_DEPTH_U8 == 1U
		#define C_SOFTFIFO__DT												Luint8
	#else
		#error
	#endif

	/** FIFO Structure */
	typedef struct
	{
		/** user configurable fifo depth */
		C_SOFTFIFO__DT uFIFO_Depth;
	
		/** FIFO Write Position */
		C_SOFTFIFO__DT uFIFO_WritePosition;

		/** FIFO Read Position */
		C_SOFTFIFO__DT uFIFO_ReadPosition;
				
		//the full flag is set by the write position going to the end.
		Luint8 u8FIFO_Full;
		Luint8 u8FIFO_Empty;

		/** The current fill level of the FIFO */
		C_SOFTFIFO__DT uFIFO_FillLevel;

		/** Indicates that the FIFO is busy writing, and therfore a read should be delayed*/
		Luint8 u8FIFO_WriteBusy;
		Luint8 u8FIFO_ReadBusy;

	
	}SOFTWARE_FIFO__USER_T;


#endif //__SOFTWARE_FIFO_PUBLIC_H_

