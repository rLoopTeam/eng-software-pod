/**
 * @file		DAQ__LOCALDEF.H
 * @brief		DAQ localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM662R0.FILE.002
 */

#if 0

/*******************************************************************************
MULTIPURPOSE DAQ MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

		/** Number of DAQ channels in each data format
		* The channels are allocated on an index basis in descending order
		* with F32 being the last channel. If you change the number of channels
		* The indexing needs to change. Macros are avail for this.
		*/
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U64					(1U)

		/** Maximum length of DAQ data for each channel in 4 byte blocks
		* WARNING: Value must be divisible by 4 and will be aligned.*/
		#define C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS					(128U)

		/** The level at which a notification should occur on all buffers
		 * For buffers that are not 4 bytes, this value will be expanded.
		 *  */
		#define C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL					(64U)
		
		/** enable double buffering of DAQ channels */
		#define C_LOCALDEF__LCCM662__ENABLE_DOUBLE_BUFFER					(0U)

		/** Enable user payload types, otherwise use the standard 0x1210+ for up
		 * to 128 streams. Typically this is 0
		 */
		#define C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES				(0U)

		/** Enable a snapshot of the core timer along with each channel of data
		* this chews NUM_CHANNELS * 4 worth of bytes and will have a slight performance
		* penalty */
		#define C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA					(0U)
		
		/** Transmission notification handler */
		#define M_LOCALDEF__LCCM662__TX_HANDLER(index, pbuffer, length)
		
		/** Testing Options */
		#define C_LOCALDEF__LCCM662__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <MULTICORE/LCCM662__MULTICORE__DAQ/daq.h>
	#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

#endif //#if 0

