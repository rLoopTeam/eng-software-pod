/**
 * @file		DAQ__WIN32.C
 * @brief		WIN32 Functions
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM662R0.FILE.003
 */

#include "../daq.h"
/**
 * @addtogroup MULTICORE
 * @{
*/
/**
 * @addtogroup DAQ
 * @ingroup MULTICORE
 * @{
*/
/**
 * @addtogroup DAQ__WIN32
 * @ingroup DAQ
 * @{
*/
#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

extern struct _strDAQ sDAQ;


/***************************************************************************//**
 * @brief
 * Just a fake Tx handler for WIN32 simulation
 * 
 * @param[in]		u16Length		## Desc ##
 * @param[in]		*pu8Buffer		## Desc ##
 * @param[in]		u16PacketIndex		## Desc ##
 * @st_funcMD5		E41636B266AA54E48543E166FC404A0D
 * @st_funcID		LCCM662R0.FILE.003.FUNC.001
 */
Lint16 s16SIL3_DAQ_WIN32__TxHandler(Luint16 u16PacketIndex, Luint8 *pu8Buffer, Luint16 u16Length)
{
	Luint16 u16Counter;

	sDAQ.sWIN32.u8NewPacket[u16PacketIndex] = 1U;
	sDAQ.sWIN32.u16LastPacketType[u16PacketIndex] = u16PacketIndex;

	for (u16Counter = 0U; u16Counter < u16Length; u16Counter++)
	{
		sDAQ.sWIN32.u8LastArray[u16PacketIndex][u16Counter] = pu8Buffer[u16Counter];
	}

	return 0;
}


#endif //win32
#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

