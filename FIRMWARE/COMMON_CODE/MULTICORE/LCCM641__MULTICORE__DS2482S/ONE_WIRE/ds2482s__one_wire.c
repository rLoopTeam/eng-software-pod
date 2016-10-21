/**
 * @file		DS2482S__ONE_WIRE.C
 * @brief		One wire functions. This module controls the 1-wire side of the device
 * 				and permits discovery of and communication with attached 1-wire devices.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.004
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S__ONE_WIRE
 * @ingroup DS2482S
 * @{ */

#include "../ds2482s.h"
#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

/*lint -e934*/
//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]


static Lint16 s16DS2482S_1WIRE__Set_StrongPullup(Luint8 u8DeviceIndex);
static Lint16 s16DS2482S_1WIRE__Clear_StrongPullup(Luint8 u8DeviceIndex);



/***************************************************************************//**
 * @brief
 * Generates a 1-Wire reset/presence-detect cycle (Figure 4) at the 1-Wire line.
 *
 * @note
 * 1-Wire Reset
 * Command Code				B4h
 * Command Parameter 		None
 * Description				Generates a 1-Wire reset/presence-detect cycle (Figure 4) at the 1-Wire line. The state of the
 * 							1-Wire line is sampled at tSI and tMSP and the result is reported to the host processor through the
 * 							Status Register, bits PPD and SD.
 * Typical Use 				To initiate or end any 1-Wire communication sequence.
 * Restriction				1-Wire activity must have ended before the DS2482-100 can process this command. Strong
 * 							pullup (see the SPU bit) should not be used in conjunction with the 1-Wire Reset command. If SPU
 * 							is enabled, the PPD bit may not be valid and may cause a violation of the devices absolute
 * 							maximum rating.
 * Error Response			Command code is not acknowledged if 1WB = 1 at the time the command code is received and
 * 							the command is ignored.
 * Command Duration			tRSTL (600us) + tRSTH (580us) + maximum 262.5ns, counted from the falling SCL edge of the command code
 * 							acknowledge bit.
 * 1-Wire Activity 			Begins maximum 262.5ns after the falling SCL edge of the command code acknowledge bit.
 * Read Pointer Position 	Status Register (for busy polling).
 * Status Bits Affected 	1WB (set to 1 for tRSTL + tRSTH), PPD is updated at tRSTL + tMSP, SD is updated at tRSTL + tSI.
 * Config Bits Affected 	1WS, APU, SPU apply. *
 *
 * @param[in]		u8DeviceIndex			The device index on the I2C
 * @return			0 = Success\n
 *					1 = pulse presense\n
 *					-10 = Bus short\n
 * 					-ve = error
 * @st_funcMD5		A91936A6D17B5C08BAE336623E8E8F94
 * @st_funcID		LCCM641R0.FILE.004.FUNC.001
 */
Lint16 s16DS2482S_1WIRE__Generate_Reset(Luint8 u8DeviceIndex)
{

	Luint8 u8Test;
	Lint16 s16Return;
	Luint8 u8Status;
	Luint8 u8Status2;

	//init for easier code review
	s16Return = -1;

	//must not execute during 1-wire commands
	// 0 = not busy or success
	// 1 = timeout
	u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status2);
	if(u8Test == 0U)
	{
		/* Strong pullup (see the SPU bit) should not be used in conjunction with the 1-Wire Reset command. If SPU
		 * is enabled, the PPD bit may not be valid and may cause a violation of the device's absolute
		 * maximum rating.
		 */
		s16Return = s16DS2482S_1WIRE__Clear_StrongPullup(u8DeviceIndex);
		if(s16Return >= 0)
		{

			//write the reset command
			s16Return = s16DS2482S_LOWLEVEL__TxReg(u8DeviceIndex, DS2482_REGS__COMMAND_1_WIRE_RESET);
			if(s16Return >= 0)
			{

				//we must wait for the busy flag.
				//this could take > 1200us.
				u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status2);
				if(u8Test == 0U)
				{

					//now check again for a short circuit
					s16Return = s16DS2482S_DEVICE__Get_Status(u8DeviceIndex, &u8Status);
					if(s16Return >= 0)
					{
						/**
						 * Short Detected SD
						 * The SD bit is updated with every 1-Wire Reset command.
						 * If the DS2482-100 detects a logic 0 on the 1-Wire line at tSI during the presence-detect cycle, the
						 * SD bit is set to 1. This bit returns to its default 0 with a subsequent 1-Wire Reset command provided that the
						 * short has been removed. If SD is 1, PPD is 0. The DS2482-100 cannot distinguish between a short and a
						 * DS1994 or DS2404 signaling a 1-Wire interrupt. For this reason, if a DS2404 or DS1994 is used in the application,
						 * the interrupt function must be disabled. The interrupt signaling is explained in the respective 1-Wire
						 * device data sheets.
						 */
						if((u8Status & 0x04U) == 0x00U)
						{
							//good

							//check the pulse presense
							/** Presence-Pulse Detect PPD
							 * The PPD bit is updated with every 1-Wire Reset command.
							 * If the DS2482-100 detects a presence pulse from a 1-Wire device at tMSP during the presence-detect
							 * cycle, the PPD bit is set to 1. This bit returns to its default
							 * 0 if there is no presence pulse or if the 1-Wire line is shorted during a subsequent 1-Wire Reset command.
							 */
							if((u8Status & 0x02U) == 0x00U)
							{
								s16Return = 0;
							}
							else
							{
								//pulse presense
								s16Return = 1;
							}

						}
						else
						{
							//bus short circuit
							s16Return = -10;
						}
					}
					else
					{
						//fall on
					}

				}
				else
				{
					//timeout
					s16Return = -1;
				}

			}
			else
			{
				//fall on with the return code.
			}
		}
		else
		{
			//fall on with error code
		}

	}
	else
	{
		s16Return = -1;
	}

	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Set the strong pullup to ON
 * 
 * @param[in]		u8DeviceIndex			Device index on the bus
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		9FBF8AE61DB353678480886D681F9ADF
 * @st_funcID		LCCM641R0.FILE.004.FUNC.002
 */
Lint16 s16DS2482S_1WIRE__Set_StrongPullup(Luint8 u8DeviceIndex)
{

	Lint16 s16Return;
	Luint8 u8Reg;

	s16Return = s16DS2482S_DEVICE__Read_ConfigRegister(u8DeviceIndex, &u8Reg);
	if(s16Return >= 0)
	{

		//set the SPU bit
		u8Reg |= 0x04U;

		//update it back again
		s16Return = s16DS2482S_LOWLEVEL__TxReg(u8DeviceIndex, (E_DS2482_REGS)u8Reg);

		//fall on with the return code

	}
	else
	{
		//fall on with error code
	}

	return s16Return;

}


/***************************************************************************//**
 * @brief
 * Set the strong pullup to OFF
 * 
 * @param[in]		u8DeviceIndex				Device index on the bus
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		2C3B1BD13DB727B47151853D3B03D1A4
 * @st_funcID		LCCM641R0.FILE.004.FUNC.003
 */
Lint16 s16DS2482S_1WIRE__Clear_StrongPullup(Luint8 u8DeviceIndex)
{

	Lint16 s16Return;
	Luint8 u8Reg;

	s16Return = s16DS2482S_DEVICE__Read_ConfigRegister(u8DeviceIndex, &u8Reg);
	if(s16Return >= 0)
	{

		//clear the SPU bit
		u8Reg &= 0x0BU;

		//update it back again
		s16Return = s16DS2482S_DEVICE__Set_ConfigRegister(u8DeviceIndex, u8Reg);

		//fall on with the return code

	}
	else
	{
		//fall on with error code
	}

	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Read a byte on the 1-wire
 * 
 * @param[in]		u8PowerUp				1 = Enable high power
 * @param[in]		*pu8Byte				Pointer to the returned byte
 * @param[in]		u8DeviceIndex			I2C bus index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		E711932042EC46EE7C765C8CEAB06A7D
 * @st_funcID		LCCM641R0.FILE.004.FUNC.007
 */
Lint16 s16DS2482S_1WIRE__ReadByte(Luint8 u8DeviceIndex, Luint8 *pu8Byte, Luint8 u8PowerUp)
{
	Lint16 s16Return;
	Luint8 u8Test;
	Luint8 u8Flag;
	Luint8 u8Status;

	//init for easier code review
	s16Return = -1;
	
	//must not execute during 1-wire commands
	// 0 = not busy or success
	// 1 = timeout
	u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
	if(u8Test == 0U)
	{

		//if we need to put the strong pullup on to power the device, then do it now
		if(u8PowerUp == 1U)
		{
			s16Return = s16DS2482S_1WIRE__Set_StrongPullup(u8DeviceIndex);
			if(s16Return >= 0)
			{
				//all good
				u8Flag = 1U;
			}
			else
			{
				u8Flag = 0U;
				s16Return = -1;
			}

		}
		else
		{
			//no power up required
			u8Flag = 1U;
		}

		//make sure our last operation was good
		if(u8Flag == 1U)
		{

			//issue the data on the bus
			s16Return = s16DS2482S_LOWLEVEL__TxReg(u8DeviceIndex, DS2482_REGS__COMMAND_1_WIRE_READ_BYTE);
			if(s16Return >= 0)
			{
				//success

				//wait until not busy
				u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
				if(u8Test == 0U)
				{
					//read the data
					s16Return = s16DS2482S_DEVICE__Read_Byte(u8DeviceIndex, pu8Byte);
					if(s16Return >= 0)
					{

					}
					else
					{

					}
					//fall down with return code

				}
				else
				{
					s16Return = -1;
				}

			}
			else
			{
				//fall on with error code
			}

		}
		else
		{
			//fall on with the s16Return code
		}

	}
	else
	{
		//device timeout after busy
		s16Return = -1;
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Write a byte on the 1-wire device
 * 
 * @param[in]		u8PowerUp				Put the wire into high power mode?
 * @param[in]		u8Byte					The byte of data to write
 * @param[in]		u8DeviceIndex			I2C device index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		F587F6697D8F6FA3C44646DF3D56ACBA
 * @st_funcID		LCCM641R0.FILE.004.FUNC.004
 */
Lint16 s16DS2482S_1WIRE__WriteByte(Luint8 u8DeviceIndex, Luint8 u8Byte, Luint8 u8PowerUp)
{

	Lint16 s16Return;
	Luint8 u8Test;
	Luint8 u8Flag;
	Luint8 u8Status;

	//init for easier code review
	s16Return = -1;
	
	//must not execute during 1-wire commands
	// 0 = not busy or success
	// 1 = timeout
	u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
	if(u8Test == 0U)
	{

		//if we need to put the strong pullup on to power the device, then do it now
		if(u8PowerUp == 1U)
		{
			s16Return = s16DS2482S_1WIRE__Set_StrongPullup(u8DeviceIndex);
			if(s16Return >= 0)
			{
				//all good
				u8Flag = 1U;
			}
			else
			{
				u8Flag = 0U;
				s16Return = -1;
			}

		}
		else
		{
			//no power up required
			u8Flag = 1U;
		}

		//make sure our last operation was good
		if(u8Flag == 1U)
		{

			//issue the data on the bus
			s16Return = s16DS2482S_LOWLEVEL__WriteReg(u8DeviceIndex, DS2482_REGS__COMMAND_1_WIRE_WRITE_BYTE, u8Byte);
			if(s16Return >= 0)
			{
				//success?
				//fall on with error code

			}
			else
			{
				//fall on with erro code
			}

		}
		else
		{
			//fall on with the s16Return code
		}

	}
	else
	{
		//device timeout after busy
		s16Return = -1;
	}

	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Write a bit on the 1-wire device
 * 
 * @note
 * Generates a single 1-Wire time slot with a bit value as specified by the bit byte at the 1-Wire line
 * A value of 0b generates a write-zero time slot; a value of 1b generates a
 * write-one time slot, which also functions as a read-data time slot. In either case, the logic
 * level at the 1-Wire line is tested at tMSR and SBR is updated.
 *
 * @param[in]		u8PowerUp				Put wire into max power mode
 * @param[in]		u8Byte					The bit 1 or 0 to write
 * @param[in]		u8DeviceIndex			I2C device index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		436E87F085FF0CE58C1AFFF5782F6D11
 * @st_funcID		LCCM641R0.FILE.004.FUNC.005
 */
Lint16 s16DS2482S_1WIRE__WriteBit(Luint8 u8DeviceIndex, Luint8 u8Byte, Luint8 u8PowerUp)
{

	Lint16 s16Return;
	Luint8 u8Test;
	Luint8 u8Flag;
	Luint8 u8Status;

	//init for easier code review
	s16Return = -1;
	
	//must not execute during 1-wire commands
	// 0 = not busy or success
	// 1 = timeout
	u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
	if(u8Test == 0U)
	{

		//if we need to put the strong pullup on to power the device, then do it now
		if(u8PowerUp == 1U)
		{
			s16Return = s16DS2482S_1WIRE__Set_StrongPullup(u8DeviceIndex);
			if(s16Return >= 0)
			{
				//all good
				u8Flag = 1U;
			}
			else
			{
				u8Flag = 0U;
				s16Return = -1;
			}

		}
		else
		{
			//no power up required
			u8Flag = 1U;
		}

		//make sure our last operation was good
		if(u8Flag == 1U)
		{

			if(u8Byte != 0U)
			{
				u8Byte = 0x80U;
			}
			else
			{
				//we are zero
			}

			//issue the data on the bus
			s16Return = s16DS2482S_LOWLEVEL__WriteReg(u8DeviceIndex, DS2482_REGS__COMMAND_1_WIRE_SINGLE_BIT, u8Byte);
			if(s16Return >= 0)
			{
				//success?
				//fall on with error code

			}
			else
			{
				//fall on with erro code
			}

		}
		else
		{
			//fall on with the s16Return code
		}


	}
	else
	{
		//device timeout after busy
		s16Return = -1;
	}

	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Read a bit from the bus
 * 
 * @param[in]		*pu8Byte				Returned bit, 1 or 0
 * @param[in]		u8DeviceIndex			I2C Bus device index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		FD63571E1566B0028E8B2738B1CF44AC
 * @st_funcID		LCCM641R0.FILE.004.FUNC.006
 */
Lint16 s16DS2482S_1WIRE__ReadBit(Luint8 u8DeviceIndex, Luint8 *pu8Byte)
{
	Lint16 s16Return;
	Luint8 u8Test;
	Luint8 u8Status;

	//init for easier code review
	s16Return = -1;
	
	s16Return =  s16DS2482S_1WIRE__WriteBit(u8DeviceIndex, 1U, 0U);
	if(s16Return >= 0)
	{

		u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
		if(u8Test == 0U)
		{

			//check the SBR bit
			if((u8Status & 0x20U) == 0x20U)
			{
				*pu8Byte = 1U;
			}
			else
			{
				*pu8Byte = 0U;
			}

			s16Return = 0;
		}
		else
		{
			//timeout
			s16Return = -1;
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
 * Select a device on the 1-wire bus.
 * Uses the devices serial number to select it.
 * 
 * @param[in]		*pu8Addx				Pointer to device serial number
 * @param[in]		u8DeviceIndex			Index on I2C
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		74880CA462C65A17762CFBC9429F1E36
 * @st_funcID		LCCM641R0.FILE.004.FUNC.008
 */
Lint16 s16DS2482S_1WIRE__SelectDevice(Luint8 u8DeviceIndex, const Luint8 *pu8Addx)
{
	Lint16 s16Return;
	Luint8 u8Counter;

	//init for easier code review
	s16Return = -1;

	//write wire command select
	s16Return = s16DS2482S_1WIRE__WriteByte(u8DeviceIndex, 0x55U, 0U);
	if(s16Return >= 0)
	{

		//clock out the array
		for(u8Counter = 0U; u8Counter < 8U; u8Counter++)
		{

			s16Return = s16DS2482S_1WIRE__WriteByte(u8DeviceIndex, pu8Addx[u8Counter], 0U);
			if(s16Return < 0)
			{
				break;
			}
			else
			{
				//keep oging
			}

		}

	}
	else
	{
		//fall on
	}


	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Issue a skip command on the 1 wire
 * 
 * @param[in]		u8DeviceIndex			Index of device on I2C
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		D998B0A5EA6FC05DFD3446449B800E90
 * @st_funcID		LCCM641R0.FILE.004.FUNC.009
 */
Lint16 s16DS2482S_1WIRE__Skip(Luint8 u8DeviceIndex)
{
	Lint16 s16Return;

	//init for easier code review
	s16Return = -1;
	
	//write wire Skip Command
	s16Return = s16DS2482S_1WIRE__WriteByte(u8DeviceIndex, 0xCCU, 0U);
	if(s16Return >= 0)
	{
		//fall on

	}
	else
	{
		//fall on
	}


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

