/**
 * @file		AMC7812__I2C.C
 * @brief		I2C Interface Layer
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.005
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__I2C
 * @ingroup AMC7812
 * @{ */

#include "../amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

/***************************************************************************//**
 * @brief
 * Init any I2C requirements
 * 
 * @st_funcMD5		69922844C23BC4ED90109040C0E6E4CF
 * @st_funcID		LCCM658R0.FILE.005.FUNC.001
 */
void vAMC7812_I2C__Init(void)
{


}


/***************************************************************************//**
 * @brief
 * Write a U16 to the device
 * 
 * @param[in]		u16Value				The value to write
 * @param[in]		u8RegAddx				The register to write to
 * @param[in]		u8DeviceAddx			I2C Bus addx
 * @return			I2C Status
 * @st_funcMD5		404AE153C899FAAAD485205AB8616729
 * @st_funcID		LCCM658R0.FILE.005.FUNC.002
 */
Lint16 s16AMC7812_I2C__WriteU16(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint16 u16Value)
{


	return 0;
}

/***************************************************************************//**
 * @brief
 * Read a U16 from the device
 * 
 * @param[out]		*pu16Value				Return pointer to the read value
 * @param[in]		u8RegAddx				The register to write to
 * @param[in]		u8DeviceAddx			The I2C device address
 * @st_funcMD5		920EC5F4487D524CBA82E9759E84475F
 * @st_funcID		LCCM658R0.FILE.005.FUNC.003
 */
Lint16 s16AMC7812_I2C__ReadU16(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint16 *pu16Value)
{

	*pu16Value = 0U;
	return 0;
}



#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

