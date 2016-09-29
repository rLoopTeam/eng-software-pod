/**
 * @file		DS2482S__CRC.C
 * @brief		Implements the CRC8 protocols as per Dallas application note.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.007
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S__CRC
 * @ingroup DS2482S
 * @{ */

#include "../ds2482s.h"
#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

/*lint -e934*/
//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
/*lint -e960*/
//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers



#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 1U
	// Copyright (C) 2000 Dallas Semiconductor Corporation, free for public use.
	static const Luint8 DS2482_CRC_TABLE[] =
	{
		0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
		157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
		35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
		190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
		70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
		219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
		101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
		248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
		140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
		17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
		175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
		50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
		202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
		87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
		233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
		116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
	};
#endif


//locals
#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 1U
	static Luint8 u8DS2482S_CRC__CRC8_Table(const Luint8 *pu8Data, Luint8 u8Length);
#elif C_LOCALDEF__LCCM641__USE_TABLE_CRC == 0U
	static Luint8 u8DS2482S_CRC__CRC8_Calc(const Luint8 *pu8Data, Luint8 u8Length);
#endif



/***************************************************************************//**
 * @brief
 * Calculate the CRC8 using avail methods.
 * 
 * @param[in]		u8Length			Length of data to CRC
 * @param[in]		*pu8Data			Pointer to data array
 * @return			The CRC8
 * @st_funcMD5		E0B983F4A5D63637ED7D40E0B7804FF6
 * @st_funcID		LCCM641R0.FILE.007.FUNC.001
 */
Luint8 u8DS2482S_CRC__CRC8(const Luint8 *pu8Data, Luint8 u8Length)
{
	Luint8 u8Return;
	#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 1U
		u8Return = u8DS2482S_CRC__CRC8_Table(pu8Data, u8Length);
	#elif C_LOCALDEF__LCCM641__USE_TABLE_CRC == 0U
		u8Return = u8DS2482S_CRC__CRC8_Calc(pu8Data, u8Length);
	#else
		#error
	#endif

	return u8Return;
}

#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 1U
/***************************************************************************//**
 * @brief
 * Calc the CRC using table methods
 * 
 * @param[in]		u8Length			Length of data to CRC
 * @param[in]		*pu8Data			Pointer to data array
 * @return			The CRC8
 * @st_funcMD5		E71B889462456BBB3BE8DD452CFAB691
 * @st_funcID		LCCM641R0.FILE.007.FUNC.002
 */
Luint8 u8DS2482S_CRC__CRC8_Table(const Luint8 *pu8Data, Luint8 u8Length)
{

	Luint8 u8Counter;
	Luint8 u8CRC;
	Luint8 u8Addx;

	//initial conditions
	u8CRC = 0U;

	for(u8Counter = 0U; u8Counter < u8Length; u8Counter++)
	{

		//compute the table addx
		u8Addx = u8CRC;
		u8Addx ^= pu8Data[u8Counter];

		//get the next CRC;
		u8CRC = DS2482_CRC_TABLE[u8Addx];
	}

	return u8CRC;
}
#endif //#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 1U

#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 0U
/***************************************************************************//**
 * @brief
 * Calc the CRC using math methods
 * 
 * @param[in]		u8Length			Length of data to CRC
 * @param[in]		*pu8Data			Pointer to data array
 * @return			The CRC8
 * @st_funcMD5		B9C82458D520779957DC9DD5FD23A236
 * @st_funcID		LCCM641R0.FILE.007.FUNC.003
 */
Luint8 u8DS2482S_CRC__CRC8_Calc(const Luint8 *pu8Data, Luint8 u8Length)
{
	Luint8 u8CRC;
	Luint8 u8InputByte;
	Luint8 u8Counter;
	Luint8 u8Mix;

	//init conditions
	u8CRC = 0U;
	
	while(len--)
	{
		u8InputByte = *pu8Data++;
	
		for(u8Counter = 8U; u8Counter; u8Counter--)
		{
			u8Mix = (u8CRC ^ u8InputByte) & 0x01U;
			u8CRC >>= 1U;
			if(u8Mix != 0U)
			{
				u8CRC ^= 0x8CU;
			}
			else
			{
				//fall on
			}
			
			u8InputByte >>= 1U;
		}
	}
return u8CRC;

}
#endif //#if C_LOCALDEF__LCCM641__USE_TABLE_CRC == 0U

/*lint +e934*/
/*lint +e960*/

//safetys
#ifndef C_LOCALDEF__LCCM641__USE_TABLE_CRC
	#error
#endif

#endif //#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
