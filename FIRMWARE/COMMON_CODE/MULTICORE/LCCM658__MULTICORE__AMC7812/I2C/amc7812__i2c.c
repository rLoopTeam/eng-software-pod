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

extern struct _strAMC7812 sAMC;

/***************************************************************************//**
 * @brief
 * Init any I2C requirements
 * 
 * @st_funcMD5		18404AD7CC7CC1BD98B3E9DB7192E84A
 * @st_funcID		LCCM658R0.FILE.005.FUNC.001
 */
void vAMC7812_I2C__Init(void)
{
	//nothing here

}


/***************************************************************************//**
 * @brief
 * Transmit only the command byte
 *
 * @param[in]		eRegister				The register / Command
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		94DBEFC252BD4681DDFBF7CC6BA1BA9F
 * @st_funcID		LCCM647R0.FILE.003.FUNC.001
 */
Lint16 s16AMC7812_I2C__TxCommand(Luint8 u8DeviceAddx, Luint8 u8RegisterAddx)
{
	Lint16 s16Return;

#ifndef WIN32

	// write to control register to issue command

	s16Return = -1;
	s16Return = s16RM4_I2C_USER__TxReg(u8DeviceAddx, u8RegisterAddx);

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
 * @st_funcMD5		38D53C2150F57C2A737B0B6DFE011F2D
 * @st_funcID		LCCM658R0.FILE.005.FUNC.002
 */
Lint16 s16AMC7812_I2C__WriteU16(Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint16 u16Value)
{

	Luint8 u8Array[2];
	Luint8 u8ArrayLength;
	Lint16 s16Return;
	Luint8 *pu8ArrayPtr;
	union
	{
		Luint8 u8[2];
		Luint16 u16;
	} unT2;


#ifndef WIN32

	// convert 16-bit number to two-byte array
	//Map
	unT2.u16 = u16Value;
	u8Array[0] = unT2.u8[1];
	u8Array[1] = unT2.u8[0];

	// write data to DAC register

	u8ArrayLength = 2U;
	s16Return = -1;
	s16Return = s16RM4_I2C_USER__TxByteArray(u8DeviceAddx, u8RegisterAddx, &u8Array[0], u8ArrayLength);


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
 * @st_funcMD5		A419EC4615D15A7EF215C8AA3451DA57
 * @st_funcID		LCCM658R0.FILE.005.FUNC.003
 */
Lint16 s16AMC7812_I2C__ReadU16(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint16 *pu16Value)
{

	// declarations

	Luint8 u8Array[2];
	Luint8 u8ArrayLength;
	Lint16 s16Return;
	union
	{
		Luint8 u8[2];
		Luint16 u16;
	}unT2;

	s16Return = -1;

	//read two bytes

#ifndef WIN32

	u8ArrayLength = 2U;

	s16Return = s16RM4_I2C_USER__RxByteArray(u8DeviceAddx, u8RegAddx, &u8Array[0], 	u8ArrayLength);

	//Map
	unT2.u8[1] = u8Array[0];
	unT2.u8[0] = u8Array[1];
	*pu16Value = unT2.u16;
#else
	//fake on win32
	*pu16Value = 0U;
	s16Return = 0;
#endif


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

