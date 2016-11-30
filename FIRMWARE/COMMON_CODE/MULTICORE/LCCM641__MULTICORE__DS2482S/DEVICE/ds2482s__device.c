/**
 * @file		DS2482S__DEVICE.C
 * @brief		Main device functions. This module will interract with the I2C side
 * 				of the device and regsters / reset handling.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.006
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S__DEVICE
 * @ingroup DS2482S
 * @{ */

#include "../ds2482s.h"
#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

/*lint -e934*/
//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
/*lint -e960*/
//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers


//locals
static Lint16 s16DS2482S_DEVICE__Set_ReadPointer(Luint8 u8DeviceIndex, E_DS2482_POINTER_T ePointer);

/***************************************************************************//**
 * @brief
 * Generate a device reset by activating the reset command in software
 * 
 * @note
 * This must be completed before any other transactions occur on the device
 *
 * @note
 * Example Bus Transaction:
 * 0x30 [Wr Addx], 0xF0 [Command Reset Register]
 * 0x31 [Rd Addx], 0x18 [Default Status Register]
 *
 *
 * @param[in]		u8DeviceIndex			The I2C bus device index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		01824614781D8CCD0D8A061064FBBAD2
 * @st_funcID		LCCM641R0.FILE.006.FUNC.001
 */
Lint16 s16DS2482S_DEVICE__Reset(Luint8 u8DeviceIndex)
{

	Lint16 s16Return;
	Luint8 u8Status;

	//issue the reset command
	s16Return = s16DS2482S_LOWLEVEL__TxReg(u8DeviceIndex, DS2482_REGS__COMMAND_RESET);
	if(s16Return >= 0)
	{
		//the read pointer is already set to the status register

		/**
		 * If the RST bit is 1, the DS2482-100 has performed an internal reset cycle, either caused by a power-on reset
		 * or from executing the Device Reset command. The RST bit is cleared automatically when the DS2482-100 executes
		 * a Write Configuration command to restore the selection of the desired 1-Wire features
		 */

		//check the status register, the RST bit should be 1.
		s16Return = s16DS2482S_LOWLEVEL__RxReg(u8DeviceIndex, &u8Status);
		if(s16Return >= 0)
		{

			//make sure we occurred
			if((u8Status & 0x10U) == 0x10U)
			{
				//good

				//After a device reset (power-up cycle or initiated by the Device Reset command), the Configuration Register
				//reads 00h.

				//give us some good config register values
				//no APU, etc, but setting config will give us good values
				s16Return = s16DS2482S_DEVICE__Set_ConfigRegister(u8DeviceIndex, 0x01U);

				//fall on with return code
			}
			else
			{
				//fault.
			}

		}
		else
		{
			//fall on with the error code
		}





	}
	else
	{
		//fall on with error code
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Sets the devices read pointer to one of a few predetermined values
 * 
 * @param[in]		ePointer				The register pointer enum.
 * @param[in]		u8DeviceIndex			The I2C bus device index
 * @return			0 = success\n
 * 					-ve = error
 * @st_funcMD5		542AC92DAF70666F055287D2AE3A388A
 * @st_funcID		LCCM641R0.FILE.006.FUNC.002
 */
Lint16 s16DS2482S_DEVICE__Set_ReadPointer(Luint8 u8DeviceIndex, E_DS2482_POINTER_T ePointer)
{

	Lint16 s16Return;

	s16Return = s16DS2482S_LOWLEVEL__WriteReg(u8DeviceIndex, DS2482_REGS__COMMAND_SET_READ_POINTER, (Luint8)ePointer);

	return s16Return;

}


/***************************************************************************//**
 * @brief
 * Gets the status register
 * 
 * @st_image
 * The image below shows a get status transaction.
 * ![](D:/LOCKIE/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM641__MULTICORE__DS2482S/DOXYGEN/IMAGES/DS2482S_GET_STATUS.PNG)
 * @image latex D:/LOCKIE/DESIGN/LDL/COMMON_CODE/MULTICORE/LCCM641__MULTICORE__DS2482S/DOXYGEN/IMAGES/DS2482S_GET_STATUS.PNG
 * 
 * @param[in]		*pu8Status				Returned status register data
 * @param[in]		u8DeviceIndex			The I2C bus device index
 * @return			0 = success\n
 * 					-ve = error
 * @st_funcMD5		277602DD6823722E0663391C3ED64F36
 * @st_funcID		LCCM641R0.FILE.006.FUNC.003
 */
Lint16 s16DS2482S_DEVICE__Get_Status(Luint8 u8DeviceIndex, Luint8 *pu8Status)
{

	Lint16 s16Return;

	//set the read pointer to the status register
	s16Return = s16DS2482S_DEVICE__Set_ReadPointer(u8DeviceIndex, DS2482_POINTER__STATUS);
	if(s16Return == 0)
	{
		//read just a byte
		s16Return = s16DS2482S_LOWLEVEL__RxReg(u8DeviceIndex, pu8Status);

		//fall on
	}
	else
	{
		//fall on with the error
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Read from the configuration register
 * 
 * @note
 * Example Bus transaction:
 * 0x30 [Wr Addx], 0xE1 [Pointer Addx], 0xC3[Config Pointer]
 * 0x31 [Rd Addx], 0x00 [Config Value]
 *
 * @param[in]		*pu8Value				The config reg value if read was successful
 * @param[in]		u8DeviceIndex			The I2C device index
 * @return			0 = success\n
 *					-ve = error
 *					-10, -11
 * @st_funcMD5		8A8D230646F047DF454D3CD270B5F6A8
 * @st_funcID		LCCM641R0.FILE.006.FUNC.004
 */
Lint16 s16DS2482S_DEVICE__Read_ConfigRegister(Luint8 u8DeviceIndex, Luint8 *pu8Value)
{
	Lint16 s16Return;

	//set the read pointer to the status register
	s16Return = s16DS2482S_DEVICE__Set_ReadPointer(u8DeviceIndex, DS2482_POINTER__CONFIG);
	if(s16Return == 0)
	{

		//read just a byte
		s16Return = s16DS2482S_LOWLEVEL__RxReg(u8DeviceIndex, pu8Value);
		if(s16Return >= 0)
		{
			/**
			 * Remember here that the config register contains not bits:
			 * Configuration Register Bit Assignment:
			 * BIT 7 	BIT 6 	BIT 5 	BIT 4 	BIT 3 	BIT 2 	BIT 1 	BIT 0
			 * n1WS 	nSPU 	1 		nAPU 	1WS 	SPU 	0 		APU
			 */

			//We should do some sanity checks to make sure the upper layer knows it has valid data.

			//NO WE CANT:
			//When read, the upper nibble is always 0h.
			//BITCH

			/*
			if((u8Read & 0x40U) == 0x40U)
			{

				//do another check
				if((u8Read & 0x01) == 0x00U)
				{
					if((u8Read & 0x10) == 0x10U)
					{
						//register seems good
						*pu8Value = u8Read;
						s16Return = 0;
					}
					else
					{
						//fault, not a mirrored bit
						*pu8Value = 0x00U;
						s16Return = -11;
					}
				}
				else
				{
					if((u8Read & 0x10) == 0x00U)
					{
						//register seems good
						*pu8Value = u8Read;
						s16Return = 0;
					}
					else
					{
						//fault, not a mirrored bit
						*pu8Value = 0x00U;
						s16Return = -12;
					}

				}

			}
			else
			{
				//can't find the 1 in the byte, error
				*pu8Value = 0x00U;
				s16Return = -10;
			}
			 */

		}
		else
		{
			//fall on with error code
		}
	}
	else
	{
		//fall on with the error
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Sets the config register
 * 
 * @param[in]		u8Value					New register value
 * @param[in]		u8DeviceIndex			Device index on the bus
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		14FDE7539F053AFD61DD8AC597D59C37
 * @st_funcID		LCCM641R0.FILE.006.FUNC.005
 */
Lint16 s16DS2482S_DEVICE__Set_ConfigRegister(Luint8 u8DeviceIndex, Luint8 u8Value)
{

	Lint16 s16Return;
	Luint8 u8Test;
	Luint8 u8Config;
	Luint8 u8Temp;
	Luint8 u8Status;

	/**
	 * Write Configuration
	 * Description				Writes a new configuration byte. The new settings take effect immediately. Note: When writing to
	 * 							the Configuration Register, the new data is accepted only if the upper nibble (bits 7 to 4) is the
	 * 							one's complement of the lower nibble (bits 3 to 0). When read, the upper nibble is always 0h.
	 * Typical Use 				Defining the features for subsequent 1-Wire communication.
	 * Restriction 				1-Wire activity must have ended before the DS2482-100 can process this command.
	 * Error Response			Command code and parameter are not acknowledged if 1WB = 1 at the time the command code
	 * 							is received and the command is ignored.
	 * Command Duration			None. The Configuration Register is updated on the rising SCL edge of the configuration-byte
	 * 							acknowledge bit.
	 * 1-Wire Activity 			None
	 * Read Pointer Position 	Configuration Register (to verify write).
	 * Status Bits Affected 	RST set to 0.
	 * Config Bits Affected 	1WS, SPU, APU updated.
	 */
	u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
	if(u8Test == 0U)
	{

		//we can modify any of the first 4 bits, however bit 1 must be 0
		u8Temp = u8Value;

		//mask off bit zero
		u8Temp &= 0xFDU;

		//create the register
		u8Config = ~u8Temp;
		u8Config <<= 4U;
		u8Config |= u8Value;

		//update the config register
		s16Return = s16DS2482S_LOWLEVEL__WriteReg(u8DeviceIndex, DS2482_REGS__COMMAND_WRITE_CONFIG, u8Config);
		if(s16Return >= 0)
		{
			//now read it back again
			s16Return = s16DS2482S_LOWLEVEL__RxReg(u8DeviceIndex, &u8Test);
			if(s16Return >= 0)
			{
				//remember when reading back the upper nibble is always zero, so mask
				//off our config register.
				u8Config &= 0x0FU;

				//check for a match
				if(u8Test == u8Config)
				{
					//pass
					s16Return = 0;
				}
				else
				{
					//fault
					s16Return = -4;
				}

			}
			else
			{
				s16Return = -3;
			}

		}
		else
		{
			//error
			s16Return = -2;
		}

	}
	else
	{
		//timeout
		s16Return = -1;
	}


	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Waits for the Busy bit to be clear before continuing
 * 
 * @param[in]		u8DeviceIndex			Device index on the bus
 * @return			0 = not busy or not time out\n
 * 					1 = Timeout (busy status unknown)
 * @st_funcMD5		0F8EE83B4B12802BCBC13DF1612ED35C
 * @st_funcID		LCCM641R0.FILE.006.FUNC.006
 */
Luint8 u8DS2482S_DEVICE__Wait_Busy(Luint8 u8DeviceIndex, Luint8 *pu8Status)
{
	Lint16 s16Return;
	Luint8 u8Status;
	Luint32 u32Counter;
	Luint8 u8Return;

	//preconditions.
	u8Return = 1U;

	for(u32Counter = 0U; u32Counter < 100U; u32Counter++)
	{

		//get the status
		s16Return = s16DS2482S_DEVICE__Get_Status(u8DeviceIndex, &u8Status);
		if(s16Return >= 0)
		{

			//check the bit
			if((u8Status & 0x01U) == 0U)
			{
				//not busy
				u8Return = 0U;
				//make a copy for other purposes
				*pu8Status = u8Status;
				break;
			}
			else
			{
				//keep going
			}

			//wait a little bit
			vDS18B20_DELAYS__Delay_uS(10U);
		}
		else
		{
			//fault
			u8Return = 1U;
			*pu8Status = 0U;
			break;
		}
	}

	return u8Return;
}



/***************************************************************************//**
 * @brief
 * Read a byte from the device's data register
 * 
 * @param[out]		*pu8Value				Pointer to the returned value
 * @param[in]		u8DeviceIndex			The I2C device index
 * @st_funcMD5		87B1F205394A2E2D098CDB8F82DDF31C
 * @st_funcID		LCCM641R0.FILE.006.FUNC.007
 */
Lint16 s16DS2482S_DEVICE__Read_Byte(Luint8 u8DeviceIndex, Luint8 *pu8Value)
{
	Lint16 s16Return;

	//set the read pointer to the status register
	s16Return = s16DS2482S_DEVICE__Set_ReadPointer(u8DeviceIndex, DS2482_POINTER__DATA);
	if(s16Return == 0)
	{

		//read just a byte
		s16Return = s16DS2482S_LOWLEVEL__RxReg(u8DeviceIndex, pu8Value);
		if(s16Return >= 0)
		{
			//success
		}
		else
		{
			//fall on with error code
		}
	}
	else
	{
		//fall on with the error
	}

	return s16Return;
}


/*lint +e934*/
/*lint +e960*/

//safetys
#ifndef C_LOCALDEF__LCCM641__MAX_TIMEOUT_LOOPS
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
