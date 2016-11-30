/**
 * @file		DS2482S__LOWLEVEL.C
 * @brief		Lowlevel hardware interface with the I2C subsystem
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.005
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S__LOWLEVEL
 * @ingroup DS2482S
 * @{ */

#include "../ds2482s.h"
#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

/*lint -e934*/
//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]


/***************************************************************************//**
 * @brief
 * Init any low level specifics for this device index
 * 
 * @param[in]		u8DeviceIndex			The device index on the bus
 * @st_funcMD5		60A5416C1E8406DB4BB10F52CEF31C44
 * @st_funcID		LCCM641R0.FILE.005.FUNC.001
 */
void vDS2482S_LOWLEVEL__Init(Luint8 u8DeviceIndex)
{
	//nothing here.

}

/***************************************************************************//**
 * @brief
 * Transmit a byte
 * The DS2482 does not use traditional I2C addx - reg - data modes and requires
 * sometimes that only the reg portion ise sent.
 * 
 * @param[in]		eRegister				The register
 * @param[in]		u8DeviceIndex			Device index on the bus
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		C08FEB01EB95C3FCD26306F0583CCA18
 * @st_funcID		LCCM641R0.FILE.005.FUNC.002
 */
Lint16 s16DS2482S_LOWLEVEL__TxReg(Luint8 u8DeviceIndex, E_DS2482_REGS eRegister)
{
	Lint16 s16R;
	Lint16 s16Return;
	Luint8 u8Addx;

	/*lint -e960*/
	//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers

	//Bus Free Time Between a STOP and START Condition, need 2us
	vDS18B20_DELAYS__Delay_uS(2U);

	//setup the device address
	//Devices should be addressed by AD[00] to AD[11] pins in hardware
	u8Addx = u8DeviceIndex;

	//add in the DS2482-100 addx
	u8Addx |= 0x18U;

	//do the actual write
	#if C_LOCALDEF__LCCM641__USE_ON_RM4 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_TX_REG(u8Addx, (Luint8)eRegister);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#elif C_LOCALDEF__LCCM641__USE_ON_MSP430 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_TX_REG(u8Addx, (Luint8)eRegister);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#else
		#error
	#endif

	return s16Return;
	/*lint +e960*/

}


/***************************************************************************//**
 * @brief
 * Rx a simple register value. Due to the way this device works we often just
 * need to read back a register without addressing it.
 * 
 * @param[in]		*pu8Data				Return register value
 * @param[in]		u8DeviceIndex			The I2C device index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		C2AEAE98623C9D28C0E75AB6CD439B87
 * @st_funcID		LCCM641R0.FILE.005.FUNC.003
 */
Lint16 s16DS2482S_LOWLEVEL__RxReg(Luint8 u8DeviceIndex, Luint8 *pu8Data)
{
	Lint16 s16R;
	Lint16 s16Return;
	Luint8 u8Addx;

	/*lint -e960*/
	//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers

	//Bus Free Time Between a STOP and START Condition, need 2us
	vDS18B20_DELAYS__Delay_uS(2U);

	//setup the device address
	//Devices should be addressed by AD[00] to AD[11] pins in hardware
	u8Addx = u8DeviceIndex;

	//add in the DS2482-100 addx
	u8Addx |= 0x18U;

	/*lint +e960*/

	//do the actual write
	#if C_LOCALDEF__LCCM641__USE_ON_RM4 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_RX_REG(u8Addx, pu8Data);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#elif C_LOCALDEF__LCCM641__USE_ON_MSP430 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_RX_REG(u8Addx, pu8Data);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#else
		#error
	#endif
	return s16Return;

}


/***************************************************************************//**
 * @brief
 * Write a register on the device
 * 
 * @param[in]		u8Value					The value to write to the register
 * @param[in]		eRegister				The register index
 * @param[in]		u8DeviceIndex			Device index on the bus.
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		FD6924149A1B238D92247783C79AE570
 * @st_funcID		LCCM641R0.FILE.005.FUNC.004
 */
Lint16 s16DS2482S_LOWLEVEL__WriteReg(Luint8 u8DeviceIndex, E_DS2482_REGS eRegister, Luint8 u8Value)
{
	Lint16 s16R;
	Lint16 s16Return;
	Luint8 u8Addx;

	/*lint -e960*/
	//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers

	//Bus Free Time Between a STOP and START Condition, need 2us
	vDS18B20_DELAYS__Delay_uS(2U);

	//setup the device address
	//Devices should be addressed by AD[00] to AD[11] pins in hardware
	u8Addx = u8DeviceIndex;

	//add in the DS2482-100 addx
	u8Addx |= 0x18U;

	/*lint +e960*/

	//do the actual write
	#if C_LOCALDEF__LCCM641__USE_ON_RM4 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_TX_BYTE(u8Addx, (Luint8)eRegister, u8Value);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#elif C_LOCALDEF__LCCM641__USE_ON_MSP430 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_TX_BYTE(u8Addx, (Luint8)eRegister, u8Value);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#else
		#error
	#endif
	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Read a single register
 * 
 * @param[in]		*pu8Value				Return register value
 * @param[in]		eRegister				The register type
 * @param[in]		u8DeviceIndex			Device index on the bus
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		7A8803D447E394E96E9561CD82676185
 * @st_funcID		LCCM641R0.FILE.005.FUNC.005
 */
Lint16 s16DS2482S_LOWLEVEL__ReadReg(Luint8 u8DeviceIndex, E_DS2482_REGS eRegister, Luint8 *pu8Value)
{
	Lint16 s16R;
	Lint16 s16Return;
	Luint8 u8Addx;

	/*lint -e960*/
	//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers

	//Bus Free Time Between a STOP and START Condition, need 2us
	vDS18B20_DELAYS__Delay_uS(2U);

	//setup the device address
	//Devices should be addressed by AD[00] to AD[11] pins in hardware
	u8Addx = u8DeviceIndex;

	//add in the DS2482-100 addx
	u8Addx |= 0x18U;

	/*lint +e960*/

	//do the actual write
	#if C_LOCALDEF__LCCM641__USE_ON_RM4 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_RX_BYTE(u8Addx, (Luint8)eRegister, pu8Value);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#elif C_LOCALDEF__LCCM641__USE_ON_MSP430 == 1U
		s16R = M_LOCALDEF__LCCM641__I2C_RX_BYTE(u8Addx, (Luint8)eRegister, pu8Value);

		//we should convert here the I2C layer reuturns to our own returns
		if(s16R < 0)
		{
			s16Return = -1;
		}
		else
		{
			s16Return = 0;
		}
	#else
		#error
	#endif
	return s16Return;
}

/*lint +e934*/


#endif //#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */



