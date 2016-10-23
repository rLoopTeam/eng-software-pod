/**
 * @file		software_crc.h
 * @brief		Software based CRC header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM012R0.FILE.002
 */

#ifndef _SOFTWARE_CRC_H_
#define _SOFTWARE_CRC_H_

	/*******************************************************************************
	Includes
	*******************************************************************************/
	/*lint -e537*/
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE
		#error
	#endif

	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

	/*******************************************************************************
	Defines
	*******************************************************************************/
	
	/*******************************************************************************
	Structures
	*******************************************************************************/
	struct _strCRC
	{
		Luint8 u8Dummy;
	};
	
	/*******************************************************************************
	Function Prototypes
	*******************************************************************************/
	DLL_DECLARATION Luint8 u8SWCRC__7Bit_CRC_Add(Luint8 u8ExistingCRC, Luint8 u8NewData);
	DLL_DECLARATION Luint8 u8SWCRC__7Bit_CRC_Finalise(Luint8 u8OldCRC);
	DLL_DECLARATION Luint16 u16SWCRC__16Bit_CRC_Finalise(Luint16 u16OldCRC);
	DLL_DECLARATION Luint16 u16SWCRC__16Bit_CRC_Add(Luint16 u16Existing_CRC, Luint8 u8NewData);
	DLL_DECLARATION Luint16 u16SWCRC__CRC(const Luint8 *cpu8Data, Luint32 u32Length);
	DLL_DECLARATION Luint8 u8SWCRC__CRC8(const Luint8 *pu8Message, Luint32 u32Length);

	//locals (not for user calling
	DLL_DECLARATION Luint8 u8SWCRC__GetBit(Luint8 u8Byte, Luint8 u8Position);
	DLL_DECLARATION Luint16 u16SWCRC__GetBit(Luint16 u16Word, Luint8 u8Position);

	#if C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC == 1U
		DLL_DECLARATION void vLCCM012_TS(void);
		DLL_DECLARATION void vLCCM012_TS_005(void);
		DLL_DECLARATION void vLCCM012_TS_006(void);
		DLL_DECLARATION void vLCCM012_TS_007(void);
		DLL_DECLARATION void vLCCM012_TS_008(void);
		DLL_DECLARATION void vLCCM012_TS_009(void);
		DLL_DECLARATION void vLCCM012_TS_010(void);
		DLL_DECLARATION void vLCCM012_TS_011(void);
		DLL_DECLARATION void vLCCM012R0_TS_012(void);
		DLL_DECLARATION void vLCCM012R0_TS_013(void);
		DLL_DECLARATION void vLCCM012R0_TS_014(void);
		DLL_DECLARATION void vLCCM012R0_TS_015(void);
		DLL_DECLARATION void vLCCM012R0_TS_016(void);
		DLL_DECLARATION void vLCCM012R0_TS_017(void);
	#endif
	
	#endif //C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

#endif //_SOFTWARE_CRC_

