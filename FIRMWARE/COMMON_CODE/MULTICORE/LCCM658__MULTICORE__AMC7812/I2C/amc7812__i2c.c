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
 * Transmit only the command byte
 *
 * @param[in]		eRegister				The register / Command
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		9A98D912BAD5639D22BB440479EE1774
 * @st_funcID		LCCM647R0.FILE.003.FUNC.001
 */
Lint16 s16AMC7812_I2C__TxCommand( Luint8 u8DeviceAddx, E_AMC7812_DAC_CONTROL_REG_ADDRESSES eRegister )
{
	Lint16 s16Return = 0;

#ifndef WIN32
	//tx only the command
	s16Return = s16RM4_I2C_USER__TxReg(u8DeviceAddx, (Luint8)eRegister);
#else
	//fake on win32
	s16Return = 0;
#endif
	return s16Return;
}




/***************************************************************************//**
 * @brief
 * Write a U16 to the ACM7812 DAC
 * 
 * @param[in]		u16Value				The value to write
 * @param[in]		u8RegAddx				The register to write to
 * @param[in]		u8DeviceAddx			I2C Bus addx
 * @return			I2C Status
 * @st_funcMD5		404AE153C899FAAAD485205AB8616729
 * @st_funcID		LCCM658R0.FILE.005.FUNC.002
 */
Lint16 s16AMC7812_I2C__WriteU16( Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint16 u16Value )
{

	Luint8 u8Array[2];
	Luint8 u8ArrayLength = 2U;
	Lint16 s16Return  = 0;

	union
	{
		Luint8 u8[2];
		Luint16 u16;
	} unT2;


	// write data to DAC 16-bit register as two bytes
#ifndef WIN32

	//Map
	unT2.u8[1] = u8Array[0];
	unT2.u8[0] = u8Array[1];
	unT2.u16 = u16Value;

	s16Return = s16RM4_I2C_USER__TxByteArray( u8DeviceAddx, u8RegisterAddx, u8Array, u8ArrayLength );

#else
	//fake on win32

	s16Return = 0;
#endif
//
	return s16Return;
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

//	*pu16Value = 0U;
//	return 0;
	Luint8 u8Array[2];
	Lint16 s16Return = 0;

	return s16Return;
}



#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

