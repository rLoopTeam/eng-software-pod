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

#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>
extern TS_TSYS01__MAIN sTSYS;

/***************************************************************************//**
 * @brief
 * Transmit only the command byte
 * 
 * @st_image
 * The image below shows adc sample start command
 * ![](D:/SIL3/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM647__MULTICORE__TSYS01/DOXYGEN/IMAGES/TSYS01__ADC_START_TO_SAMPLE_READ.PNG)
 * @image latex D:/SIL3/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM647__MULTICORE__TSYS01/DOXYGEN/IMAGES/TSYS01__ADC_START_TO_SAMPLE_READ.PNG
 *
 * @param[in]		eRegister				The register / Command
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		7A76FB914FA3B00E23639630F5B6BA4C
 * @st_funcID		LCCM647R0.FILE.003.FUNC.001
 */
Lint16 s16TSYS01_I2C__TxCommand(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister)
{
	Lint16 s16Return;

#ifndef WIN32
	//tx only the command
	#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U)
		//s16Return = s16RM4_I2C_USER__TxReg(RM4_I2C_CH__1, u8DeviceAddx, (Luint8)eRegister);
		s16Return = s16RM4_I2C_USER__Tx_U8(RM4_I2C_CH__1, u8DeviceAddx, (Luint8)eRegister, 0U);
	#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
		s16Return = s16MSP430_I2C_USER__TxReg(MSP430_USCI_B0_I2C_BASE, u8DeviceAddx, (Luint8)eRegister);
	#else
		#error
	#endif
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
 * @st_funcMD5		493DE96A1CD7E223833E8C265719899C
 * @st_funcID		LCCM647R0.FILE.003.FUNC.002
 */
Lint16 s16TSYS01_I2C__TxU8(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint8 u8Byte)
{
	Lint16 s16Return;

#ifndef WIN32
	//Tx a byte
	#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U)
		s16Return = s16RM4_I2C_USER__Tx_U8(RM4_I2C_CH__1, u8DeviceAddx, (Luint8)eRegister, u8Byte);
	#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
		s16Return = s16MSP430_I2C_USER__Tx_U8(MSP430_USCI_B0_I2C_BASE, u8DeviceAddx, (Luint8)eRegister, u8Byte);
	#else
		#error
	#endif
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
 *@st_image
 * The image below shows reading a constant
 * ![](D:/SIL3/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM647__MULTICORE__TSYS01/DOXYGEN/IMAGES/TSYS01__READ_CONSTANT_K0.PNG)
 * @image latex D:/SIL3/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM647__MULTICORE__TSYS01/DOXYGEN/IMAGES/TSYS01__READ_CONSTANT_K0.PNG
 *
 * @param[in]		*pu16					Pointer to returned data
 * @param[in]		eRegister				The read register
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		50EE7EC961C68823AE4651BC0D2F615C
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
	#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U)
		s16Return = s16RM4_I2C_USER__Rx_U8Array(RM4_I2C_CH__1, u8DeviceAddx, (Luint8)eRegister, &u8Array[0], 2U);
		//Map
		unT2.u8[1] = u8Array[0];
		unT2.u8[0] = u8Array[1];
	#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
		s16Return = s16MSP430_I2C_USER__Rx_U8Array(MSP430_USCI_B0_I2C_BASE, u8DeviceAddx, (Luint8)eRegister, &u8Array[0], 2U);
		//Map
		unT2.u8[1] = u8Array[0];
		unT2.u8[0] = u8Array[1];
	#else
		#error
	#endif

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
 * @st_image
 * The image below shows the read command
 * ![](D:/SIL3/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM647__MULTICORE__TSYS01/DOXYGEN/IMAGES/TSYS01__CONVERT_READ_24BIT.PNG)
 * @image latex D:/SIL3/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM647__MULTICORE__TSYS01/DOXYGEN/IMAGES/TSYS01__CONVERT_READ_24BIT.PNG
 *
 * @param[in]		*pu32					Pointer to return data
 * @param[in]		eRegister				Read register
 * @param[in]		u8DeviceAddx			I2C Bus Address
 * @return			I2C Error Code
 * @st_funcMD5		4F32BD32B20CF7AC5C02958166BB20DC
 * @st_funcID		LCCM647R0.FILE.003.FUNC.004
 */
Lint16 s16TSYS01_I2C__RxU24(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint32 *pu32)
{
	Lint16 s16Return;
	Luint8 u8Array[3];
	
	//Reviewed LG
	/*line -e960*/
	union
	{
		Luint8 u8[4];
		Luint32 u32;
	}unT2;
	/*line +e960*/

	//read three bytes
#ifndef WIN32
	#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U)
		s16Return = s16RM4_I2C_USER__Rx_U8Array(RM4_I2C_CH__1, u8DeviceAddx, (Luint8)eRegister, &u8Array[0], 3U);
		//do the mapping
		unT2.u8[0] = u8Array[2];
		unT2.u8[1] = u8Array[1];
		unT2.u8[2] = u8Array[0];
		unT2.u8[3] = 0U;
	#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
		s16Return = s16MSP430_I2C_USER__Rx_U8Array(MSP430_USCI_B0_I2C_BASE, u8DeviceAddx, (Luint8)eRegister, &u8Array[0], 3U);
		//do the mapping
		unT2.u8[0] = u8Array[2];
		unT2.u8[1] = u8Array[1];
		unT2.u8[2] = u8Array[0];
		unT2.u8[3] = 0U;
	#else
		#error
	#endif

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

