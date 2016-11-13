//I2C Interface layer
#include "../ms5607.h"


Lint16 s16MS5607_I2C__TxCommand(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister)
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

//perform the actual transmission
Lint16 s16MS5607_I2C__TxU8(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint8 u8Byte)
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

Lint16 s16MS5607_I2C__RxU16(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint16 *pu16)
{
	Lint16 s16Return;
	union
	{
		Luint8 u8[2];
		Luint16 u16;
	}unT;

	//read two bytes
#ifndef WIN32
	s16Return = s16RM4_I2C_USER__RxByteArray(u8DeviceAddx, (Luint8)eRegister, &unT.u8[0], 2U);

	//todo: check mapping
	*pu16 = unT.u16;
#else
	//fake on win32
	*pu16 = 0U;
	s16Return = 0;
#endif

	return s16Return;
}

Lint16 s16MS5607_I2C__RxU24(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint32 *pu32)
{
	Lint16 s16Return;
	union
	{
		Luint8 u8[3];
		Luint32 u32;
	}unT;

	//read three bytes
#ifndef WIN32
	s16Return = s16RM4_I2C_USER__RxByteArray(u8DeviceAddx, (Luint8)eRegister, &unT.u8[0], 3U);

	//todo: check mapping
	*pu32 = unT.u32;
#else
	//fake on win32
	*pu32 = 0U;
	s16Return = 0;
#endif

	return s16Return;
}

