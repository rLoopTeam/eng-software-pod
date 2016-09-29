/**
 * @file		DS18B20.C
 * @brief		Main module file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20__CORE
 * @ingroup DS18B20
 * @{ */

#include "ds18b20.h"
#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

struct _strDS18B20 sDS18B20;

/***************************************************************************//**
 * @brief
 * Init the DS18B20 device
 * 
 * @st_funcMD5		F9EE967EC67F9DAD0866F756CF98A726
 * @st_funcID		LCCM644R0.FILE.000.FUNC.001
 */
void vDS18B20__Init(void)
{
	Lint16 s16Return;
	Luint8 u8Temp[9];
	Luint8 u8ChannelIndex;
	Luint8 u8DSIndex;

	//setup
	sDS18B20.sEnum.u8NumDevices = 0U;

	//setup the vars for the address searching.
	vDS18B20_ADDX__Init();

	//search for devices.
	s16Return = s16DS18B20_ADDX__Search();

#if 0
	//precondition that the DS2482 is operational

	u8ChannelIndex = 0U;
	u8DSIndex = 0U;

	s16Return = s16DS2482S_SEARCH__SearchFirstDevice(u8ChannelIndex, &sDS18B20.sDevice[u8DSIndex].u8SerialNumber[0]);
	if(s16Return >= 0)
	{
		sDS18B20.sDevice[u8DSIndex].u8ChannelIndex = 0U;

		s16Return = s16DS18B20_TEMP__Get_Resolution(u8DSIndex, &sDS18B20.sDevice[u8DSIndex].u8Resolution);

		s16Return = s16DS18B20_TEMP__Request(u8DSIndex, 1U);

		//success
		s16Return = s16DS18B20_SCRATCH__Read(u8DSIndex, &u8Temp[0]);
		if(s16Return >= 0)
		{



		}
		else
		{
			//fall on
		}

	}
	else
	{

	}
#endif

}

/***************************************************************************//**
 * @brief
 * Process DS18B20 systems
 * Call from main program loop as quick as possible.
 * 
 * @st_funcMD5		231B3835C46BE862352D9F1FB404D4C2
 * @st_funcID		LCCM644R0.FILE.000.FUNC.002
 */
void vDS18B20__Process(void)
{

	//if need be process the search functions
	vDS18B20_ADDX__SearchSM_Process();

}


#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

