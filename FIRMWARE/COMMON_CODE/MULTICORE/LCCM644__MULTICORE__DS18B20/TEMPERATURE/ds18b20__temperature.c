/**
 * @file		DS18B20__TEMPERATURE.C
 * @brief		Temperature read and conversion functions
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.003
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20__TEMPERATURE
 * @ingroup DS18B20
 * @{ */

#include "../ds18b20.h"
#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

extern struct _strDS18B20 sDS18B20;

//locals
static void vDS18B20_TEMP__Scratch_To_Temp(Luint16 u16SensorIndex, const Luint8 *pu8Scratch, Lfloat32 *pf32Temp);

/***************************************************************************//**
 * @brief
 * Read the temperature from a device ONCE the conversion is complete
 *
 * @param[in]		u16SensorIndex				The sensor index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		A078A4525D85F13160DDAF5DF26FE1E2
 * @st_funcID		LCCM644R0.FILE.003.FUNC.006
 */
Lint16 s16DS18B20_TEMP__Read(Luint16 u16SensorIndex)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	Lint16 s16Return;

	//read the scratch
	s16Return = s16DS18B20_SCRATCH__Read(u16SensorIndex, &sDS18B20.u8TempScratch[0]);
	if(s16Return >= 0)
	{
		//convert scratch RAM to a temperature
		vDS18B20_TEMP__Scratch_To_Temp(u16SensorIndex, &sDS18B20.u8TempScratch[0], &sDS18B20.sTemp[u16SensorIndex].f32Temperature);

	}
	else
	{
		//fall through with error code
	}


	return s16Return;
	/*lint +e934*/
}

/***************************************************************************//**
 * @brief
 * Issue a global command to start conversion of all devices on the wire
 * This is most useful for starting thousands of sensors to convert.
 * 
 * @param[in]		u8Wait					Set to 1 to wait the desired conversion time.
 * @param[in]		u16SensorIndex				The sensor index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		2A3FA2AC34982FD9EA9455F9CB0482D1
 * @st_funcID		LCCM644R0.FILE.003.FUNC.003
 */
Lint16 s16DS18B20_TEMP__All_Request(Luint16 u16SensorIndex, Luint8 u8Wait)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	
	Lint16 s16Return;

	//generate a reset on the wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);

	//issue the skip command, no serial number needed.
	s16Return =  s16DS18B20_1WIRE__Skip(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);

	//start the convert
	s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, 0x44U);

	//wait for conversion?
	if(u8Wait == 1U)
	{

		switch(sDS18B20.sDevice[u16SensorIndex].u8Resolution)
		{
			case 9:
				vDS18B20_DELAYS__Delay_mS(94U);
				break;
			case 10:
				vDS18B20_DELAYS__Delay_mS(188U);
				break;
			case 11:
				vDS18B20_DELAYS__Delay_mS(375U);
				break;
			case 12:
				vDS18B20_DELAYS__Delay_mS(750U);
				break;
			default:
				//not sure what to do here?
				break;

		}//switch(sDS18B20.sDevice[u8DSIndex].u8Resolution)

		//now that we have waited, the user can read it

		s16Return = 0;

	}
	else
	{
		//exit
	}

	//at this point here, either we are ready to read, or we have an error

	return s16Return;
	
	/*lint +e934*/
	
}


Lint16 s16DS18B20_TEMP__All_Request_ByChannel(Luint8 u8ChannelIndex, Luint8 u8Wait)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]

	Lint16 s16Return;

	//generate a reset on the wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(u8ChannelIndex);

	//issue the skip command, no serial number needed.
	s16Return =  s16DS18B20_1WIRE__Skip(u8ChannelIndex);

	//start the convert
	s16Return = s16DS18B20_1WIRE__WriteByte(u8ChannelIndex, 0x44U);

	//wait for conversion?
	if(u8Wait == 1U)
	{

		//only use sensor 0 res, assum all the same
		switch(sDS18B20.sDevice[0].u8Resolution)
		{
			case 9:
				vDS18B20_DELAYS__Delay_mS(94U);
				break;
			case 10:
				vDS18B20_DELAYS__Delay_mS(188U);
				break;
			case 11:
				vDS18B20_DELAYS__Delay_mS(375U);
				break;
			case 12:
				vDS18B20_DELAYS__Delay_mS(750U);
				break;
			default:
				//not sure what to do here?
				break;

		}//switch(sDS18B20.sDevice[u8DSIndex].u8Resolution)

		//now that we have waited, the user can read it

		s16Return = 0;

	}
	else
	{
		//exit
	}

	//at this point here, either we are ready to read, or we have an error

	return s16Return;

	/*lint +e934*/

}

/***************************************************************************//**
 * @brief
 * Request the temperature.
 * If successful the temperature will be updated in the memory structure
 * 
 * @param[in]		u8Wait					Set this to 1 to wait the required time for conversion
 * @param[in]		u16SensorIndex				The addressed index of the device.
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		860D63E72330497D8ACB60F9EBF50D2D
 * @st_funcID		LCCM644R0.FILE.003.FUNC.004
 */
Lint16 s16DS18B20_TEMP__Request(Luint16 u16SensorIndex, Luint8 u8Wait)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	Lint16 s16Return;

	//reset the one-wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);
	if(s16Return >= 0)
	{
		//select the correct device
		s16Return = s16DS18B20_1WIRE__SelectDevice(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, &sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[0]);
		if(s16Return >= 0)
		{

			//select to start the conversion and put value into scratchpad
			s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, 0x44U);
			if(s16Return >= 0)
			{

				//wait for conversion?
				if(u8Wait == 1U)
				{

					switch(sDS18B20.sDevice[u16SensorIndex].u8Resolution)
					{
						case 9:
							vDS18B20_DELAYS__Delay_mS(94U);
							break;
						case 10:
							vDS18B20_DELAYS__Delay_mS(188U);
							break;
						case 11:
							vDS18B20_DELAYS__Delay_mS(375U);
							break;
						case 12:
							vDS18B20_DELAYS__Delay_mS(750U);
							break;
						default:
							//not sure what to do here?
							break;

					}//switch(sDS18B20.sDevice[u8DSIndex].u8Resolution)

					//now that we have waited, read it


					//read the scratch
					s16Return = s16DS18B20_SCRATCH__Read(u16SensorIndex, &sDS18B20.u8TempScratch[0]);

					//convert scratch to temp
					vDS18B20_TEMP__Scratch_To_Temp(u16SensorIndex, &sDS18B20.u8TempScratch[0], &sDS18B20.sTemp[u16SensorIndex].f32Temperature);

					//success code
					s16Return = 0;

				}
				else
				{
					//exit
				}

			}
			else
			{
				//fall on with error
			}

		}
		else
		{
			//fall on with error code
		}

	}
	else
	{
		//return with the error code
	}

	//reset again
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);

	return s16Return;
	/*lint +e934*/

}

/***************************************************************************//**
 * @brief
 * Convert scratchpad to temperature
 * Takes the two temp bytes in the scratchpad and converts to floating point temp;
 *
 * @note
 * Resolution must be known at this stage, otherwise reported temperature is 128.0C
 * 
 * @param[out]		*pf32Temp				Pointer to return temperature value
 * @param[in]		*pu8Scratch				Pointer to scratchpad memory
 * @param[in]		u16SensorIndex				Index of the device so as we know our resoltion
 * @st_funcMD5		65DE1541B347FC9CA29984F03A7B741D
 * @st_funcID		LCCM644R0.FILE.003.FUNC.005
 */
void vDS18B20_TEMP__Scratch_To_Temp(Luint16 u16SensorIndex, const Luint8 *pu8Scratch, Lfloat32 *pf32Temp)
{
	/*lint -e960*/
	//Note 960: Violates MISRA 2004 Required Rule 18.4, unions shall not be used
	//reviewed OK
	union
	{
		Luint8 u8[2];
		Lint16 s16;
		Luint16 u16;
	}unT, unT2;
	Luint16 u16WholeCelcius;
	Luint16 u16Fraction;

	/*lint +e960*/

	//assign
	#ifdef _WE_ARE_ON_MSP430_
		unT.u8[0U] = pu8Scratch[0U];
		unT.u8[1U] = pu8Scratch[1U];
	#else
		unT.u8[0U] = pu8Scratch[0U];
		unT.u8[1U] = pu8Scratch[1U];
	#endif

	if(sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[0] != 0x3BU) //Thermocouples don't have resolution settings
		{

		//save off.
		u16WholeCelcius = unT.u16;

		//essentially the temp is in 1/16th of a degree for 12 but.
		switch(sDS18B20.sDevice[u16SensorIndex].u8Resolution)
		{
			case 12U:

				//clear the undefined bits
				//none
				u16WholeCelcius >>= 0U;

				//check for negative
				if((unT.u16 & 0x8000U) == 0x8000U)
				{
					//two's complement
					u16WholeCelcius ^= 0xFFFFU;
					u16WholeCelcius += 1U;
				}

				unT2.u16 = u16WholeCelcius;

				//raw conversion
				*pf32Temp = (Lfloat32)unT2.s16;
				*pf32Temp /= 16.0F;

				break;
			case 11U:

				//clear undefined bits
				u16WholeCelcius >>= 1U;

				//check for negative
				if((unT.u16 & 0x8000U) == 0x8000U)
				{
					//two's complement
					u16WholeCelcius ^= 0xFFFFU;
					u16WholeCelcius += 1U;
				}

				unT2.u16 = u16WholeCelcius;

				//raw conversion
				*pf32Temp = (Lfloat32)unT2.s16;
				*pf32Temp /= 8.0F;
				break;

			case 10U:
				//clear undefined bits
				u16WholeCelcius >>= 2U;

				//check for negative
				if((unT.u16 & 0x8000U) == 0x8000U)
				{
					//two's complement
					u16WholeCelcius ^= 0xFFFFU;
					u16WholeCelcius += 1U;
				}

				unT2.u16 = u16WholeCelcius;

				//raw conversion
				*pf32Temp = (Lfloat32)unT2.s16;
				*pf32Temp /= 4.0F;
				break;

			case 9U:
				//clear undefined bits
				u16WholeCelcius >>= 3U;

				//check for negative
				if((unT.u16 & 0x8000U) == 0x8000U)
				{
					//two's complement
					u16WholeCelcius ^= 0xFFFFU;
					u16WholeCelcius += 1U;
				}

				unT2.u16 = u16WholeCelcius;

				//raw conversion
				*pf32Temp = (Lfloat32)unT2.s16;
				*pf32Temp /= 2.0F;
				break;

			default:
				//set to 128C indicating a problem
				*pf32Temp = 128.0F;
				break;
		}//switch(&sDS18B20.sDevice[u16SensorIndex].u8Resolution)

	}else{
		unT.u8[0U] = pu8Scratch[0U];
		unT.u8[1U] = pu8Scratch[1U];

		//save off.
		u16WholeCelcius = unT.u16 >> 2;

		//check for negative
		if((u16WholeCelcius & 0x2000U) == 0x2000U)
		{
			//two's complement
			u16WholeCelcius |= 0xC000;
		}

		unT2.u16 = u16WholeCelcius;

		//raw conversion
		*pf32Temp = (Lfloat32)unT2.s16;
		*pf32Temp /= 4.0F;
	}

	//noting to return, already updated.

}

/***************************************************************************//**
 * @brief
 * Gets the current resolution by reading the scratchpad memory
 * 
 * @param[out]		*pu8Resolution			Returned resolution value
 * @param[in]		u16SensorIndex				Already enumerated address ID
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		79132391B133E345569932CFFF9C4316
 * @st_funcID		LCCM644R0.FILE.003.FUNC.002
 */
Lint16 s16DS18B20_TEMP__Get_Resolution(Luint16 u16SensorIndex, Luint8 *pu8Resolution)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]

	Lint16 s16Return;

	//read the scratch
	s16Return = s16DS18B20_SCRATCH__Read(u16SensorIndex, &sDS18B20.u8TempScratch[0]);

	//determine from the scratchpad
	switch(sDS18B20.u8TempScratch[4U])
	{

		case 0x7FU:
			*pu8Resolution = 12U;
			break;
		case 0x5FU:
			*pu8Resolution = 11U;
			break;
		case 0x3FU:
			*pu8Resolution = 10U;
			break;
		case 0x1FU:
			*pu8Resolution = 9U;
			break;

		default:
			*pu8Resolution = 0U;
			break;
	}


	return s16Return;
	/*lint +e934*/

}

Lint16 s16DS18B20_TEMP__Get_UserID(Luint16 u16SensorIndex)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]

	Lint16 s16Return;

	//read the scratch
	s16Return = s16DS18B20_SCRATCH__Read(u16SensorIndex, &sDS18B20.u8TempScratch[0]);

	sDS18B20.sDevice[u16SensorIndex].u16UserIndex = sDS18B20.u8TempScratch[4] & 0xF;


	return s16Return;
	/*lint +e934*/

}

/***************************************************************************//**
 * @brief
 * Set the temperature resolution
 * 
 * @param[in]		u8Resolution			New Res: 12,11,10 or 9 bit
 * @param[in]		u16SensorIndex				Device index address
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		AA30E950FFA1C69214EC088D9D467661
 * @st_funcID		LCCM644R0.FILE.003.FUNC.001
 */
Lint16 s16DS18B20_TEMP__Set_Resolution(Luint16 u16SensorIndex, Luint8 u8Resolution)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	Lint16 s16Return;
	Luint8 u8CRC;

	//read the scratch
	s16Return = s16DS18B20_SCRATCH__Read(u16SensorIndex, &sDS18B20.u8TempScratch[0]);

	//check CRC
	u8CRC = u8DS18B20_SCRATCH__Compute_CRC(&sDS18B20.u8TempScratch[0]);
	if(u8CRC == sDS18B20.u8TempScratch[8])
	{
		//configure the new resolution in the scratchpad
		switch(u8Resolution)
		{
			case 12:
				sDS18B20.u8TempScratch[4U] = 0x7FU;
				break;

			case 11:
				sDS18B20.u8TempScratch[4U] = 0x5FU;
				break;

			case 10:
				sDS18B20.u8TempScratch[4U] = 0x3FU;
				break;

			case 9:
				sDS18B20.u8TempScratch[4U] = 0x1FU;
				break;

			default:
				//default at 12bit
				sDS18B20.u8TempScratch[4U] = 0x7FU;
				break;

		}//switch(u8Resolution)

		//update the scratchpad
		s16Return = s16DS18B20_SCRATCH__Write(u16SensorIndex, &sDS18B20.u8TempScratch[0]);
	}
	else
	{
		//todo, log error
		//CRC FAULT
		s16Return = -2;
	}

	return s16Return;
	/*lint +e934*/

}




#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

