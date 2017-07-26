/**
 * @file		DS2482S.C
 * @brief		Main source file, provides user level interraction.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S__CORE
 * @ingroup DS2482S
 * @{ */
 

#include "ds2482s.h"
#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

//main structure
struct _strDS2482S sDS2482S;

/***************************************************************************//**
 * @brief
 * Init the DS2482 device
 * User should call this first up after the I2C driver is operational.
 * 
 * @st_funcMD5		84B03F177A28004719FBAB95581F4291
 * @st_funcID		LCCM641R0.FILE.000.FUNC.001
 */
void vDS2482S__Init(void)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable 'u8Status' (arg. no. 2) [MISRA 2004 Rule 1.2]

	Lint16 s16Return;
	Luint8 u8Status;
	Luint8 u8Counter;

	//Note 15: I2C communication should not take place for the max tOSCWUP time following a power-on reset.
	vDS18B20_DELAYS__Delay_uS(100U);

	//go through the devices.
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM641__NUM_DEVICS; u8Counter++)
	{
		//init
		sDS2482S.sSearch[u8Counter].u8CRC8 = 0U;

		//init the device specifc fault flags
		vSIL3_FAULTTREE__Init(&sDS2482S.sDevice[u8Counter].sFaultFlags);

		//setup any lowlevel issues
		vDS2482S_LOWLEVEL__Init(u8Counter);
	
		//do a device reset, should return 0 as success.
		s16Return = s16DS2482S_DEVICE__Reset(u8Counter);
		if(s16Return >= 0)
		{
			//do a status read
			s16Return = s16DS2482S_DEVICE__Get_Status(u8Counter, &u8Status);
			if(s16Return >= 0)
			{
				//all good.
			}
			else
			{
				//log the error
				vSIL3_FAULTTREE__Set_Flag(&sDS2482S.sDevice[u8Counter].sFaultFlags, C_LCCM641__CORE__FAULT_INDEX__00);
				vSIL3_FAULTTREE__Set_Flag(&sDS2482S.sDevice[u8Counter].sFaultFlags, C_LCCM641__CORE__FAULT_INDEX__01);
			}

		}
		else
		{
			//log the error
			vSIL3_FAULTTREE__Set_Flag(&sDS2482S.sDevice[u8Counter].sFaultFlags, C_LCCM641__CORE__FAULT_INDEX__00);
			vSIL3_FAULTTREE__Set_Flag(&sDS2482S.sDevice[u8Counter].sFaultFlags, C_LCCM641__CORE__FAULT_INDEX__01);
		}

	}//for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM641__NUM_DEVICS; u8Counter++)


	/*lint +e934*/
}


/***************************************************************************//**
 * @brief
 * Process any DS2482 tasks.
 * The user should call this in their main program loop as fast as possible.
 * 
 * @st_funcMD5		88AB41C00C534DD2DCE01D8AF6B0FECE
 * @st_funcID		LCCM641R0.FILE.000.FUNC.002
 */
void vDS2482S__Process(void)
{

	//nothing here

}

Luint32 u32DS2482S__Get_FaultFlags(Luint8 u8DeviceIndex)
{
	return sDS2482S.sDevice[u8DeviceIndex].sFaultFlags.u32Flags[0];
}

/***************************************************************************//**
 * @brief
 * User level function to generate a reset on the one wire bus
 * 
 * @param[in]		u8DeviceIndex			I2C bus device index
 * @return			0 = fault or no devices found\n
 * 					1 = at least one device found
 * @st_funcMD5		7D4FF1951AA3DF6D9E6DF62D02B7C002
 * @st_funcID		LCCM641R0.FILE.000.FUNC.003
 */
Luint8 u8DS2482S_USER__1Wire_Reset(Luint8 u8DeviceIndex)
{
	Lint16 s16Return;
	Luint8 u8Return;

	s16Return = s16DS2482S_1WIRE__Generate_Reset(u8DeviceIndex);
	if(s16Return <= 0)
	{
		u8Return = 0U;
	}
	else if(s16Return == 1)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}

//safetys
#ifndef C_LOCALDEF__LCCM641__NUM_DEVICS
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

