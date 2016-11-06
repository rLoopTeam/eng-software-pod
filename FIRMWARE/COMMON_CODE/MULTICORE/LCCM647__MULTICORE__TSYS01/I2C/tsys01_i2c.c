/**
 * @file		TSYS01_I2C.C
 * @brief		I2C interface Layer
 * @author		Dean, Lachlan Grogan
 * @st_fileID	LCCM647R0.FILE.003
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup TSYS01
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup TSYS01__I2C
 * @ingroup TSYS01
 * @{ */

#include "../tsys01.h"


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
Lint16 s16TSYS01_I2C__TxCommand(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister)
{
	Lint16 s16Return;

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
 * Transmit a byte
 * 
 * @param[in]		u8Byte					The byte to transmit
 * @param[in]		eRegister				Target Register
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		CD242B8D453CCE360DB82056F4E4B67D
 * @st_funcID		LCCM647R0.FILE.003.FUNC.002
 */
Lint16 s16TSYS01_I2C__TxU8(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint8 u8Byte)
{
	Lint16 s16Return;

#ifndef WIN32
	//Tx a byte
	s16Return = s16RM4_I2C_USER__TxByte(u8DeviceAddx, (Luint8)eRegister, u8Byte);
#else
	//fake on win32
	s16Return = 0;
#endif
	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Read a U16
 * 
 * @param[in]		*pu16					Pointer to returned data
 * @param[in]		eRegister				The read register
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		7977DB456C18C277D5B70AE1F2910968
 * @st_funcID		LCCM647R0.FILE.003.FUNC.003
 */
Lint16 s16TSYS01_I2C__RxU16(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint16 *pu16)
{
	Luint8 u8Array[2];
	Lint16 s16Return;
	union
	{
		Luint8 u8[2];
		Luint16 u16;
	}unT2;

	//read two bytes
#ifndef WIN32
	s16Return = s16RM4_I2C_USER__RxByteArray(u8DeviceAddx, (Luint8)eRegister, &u8Array[0], 2U);

	//Map
	unT2.u8[1] = u8Array[0];
	unT2.u8[0] = u8Array[1];
	*pu16 = unT2.u16;
#else
	//fake on win32
	*pu16 = 0U;
	s16Return = 0;
#endif

	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Rx a 24 bit value
 * 
 * @param[in]		*pu32					Pointer to return data
 * @param[in]		eRegister				Read register
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		9966CF0EA03842BEC8D0A3B08C6DC26B
 * @st_funcID		LCCM647R0.FILE.003.FUNC.004
 */
Lint16 s16TSYS01_I2C__RxU24(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint32 *pu32)
{
	Lint16 s16Return;
	Luint8 u8Array[3];
	union
	{
		Luint8 u8[4];
		Luint32 u32;
	}unT2;

	//read two bytes
#ifndef WIN32
	s16Return = s16RM4_I2C_USER__RxByteArray(u8DeviceAddx, (Luint8)eRegister, &u8Array[0], 3U);

	//do the mapping
	unT2.u8[0] = u8Array[2];
	unT2.u8[1] = u8Array[1];
	unT2.u8[2] = u8Array[0];
	unT2.u8[3] = 0U;
	*pu32 = unT2.u32;
#else
	//fake on win32
	*pu32 = 0U;
	s16Return = 0;
#endif

	return s16Return;
}
/** @} */
/** @} */
/** @} */

