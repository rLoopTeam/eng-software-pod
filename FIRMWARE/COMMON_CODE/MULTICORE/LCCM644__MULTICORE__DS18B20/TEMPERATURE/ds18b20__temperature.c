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
static void vDS18B20_TEMP__Scratch_To_Temp(Luint8 u8DSIndex, const Luint8 *pu8Scratch, Lfloat32 *pf32Temp);


/***************************************************************************//**
 * @brief
 * Issue a global command to start conversion of all devices on the wire
 * This is most useful for starting thousands of sensors to convert.
 * 
 * @param[in]		u8Wait					Set to 1 to wait the desired conversion time.
 * @param[in]		u8DSIndex				The address index
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		6140433336A0CA8489B98F68D99BCC2D
 * @st_funcID		LCCM644R0.FILE.003.FUNC.003
 */
Lint16 s16DS18B20_TEMP__All_Request(Luint8 u8DSIndex, Luint8 u8Wait)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	
	Lint16 s16Return;
	Luint8 u8Scratch[9U];

	//generate a reset on the wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u8DSIndex].u8ChannelIndex);

	//issue the skip command, no serial number needed.
	s16Return =  s16DS18B20_1WIRE__Skip(sDS18B20.sDevice[u8DSIndex].u8ChannelIndex);

	//wait for conversion?
	if(u8Wait == 1U)
	{

		switch(sDS18B20.sDevice[u8DSIndex].u8Resolution)
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
		s16Return = s16DS18B20_SCRATCH__Read(u8DSIndex, &u8Scratch[0]);

		vDS18B20_TEMP__Scratch_To_Temp(u8DSIndex, &u8Scratch[0], &sDS18B20.sDevice[u8DSIndex].f32Temperature);

		s16Return = 0;

	}
	else
	{
		//exit
	}

	return s16Return;
	
	/*lint +e934*/
	
}


/***************************************************************************//**
 * @brief
 * Request the temperature.
 * If successful the temperature will be updated in the memory structure
 * 
 * @param[in]		u8Wait					Set this to 1 to wait the required time for conversion
 * @param[in]		u8DSIndex				The addressed index of the device.
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		90A173BE636B190FE2355EA7AF485384
 * @st_funcID		LCCM644R0.FILE.003.FUNC.004
 */
Lint16 s16DS18B20_TEMP__Request(Luint8 u8DSIndex, Luint8 u8Wait)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	Lint16 s16Return;
	Luint8 u8Scratch[9];

	//reset the one-wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u8DSIndex].u8ChannelIndex);
	if(s16Return >= 0)
	{
		//select the correct device
		s16Return = s16DS18B20_1WIRE__SelectDevice(sDS18B20.sDevice[u8DSIndex].u8ChannelIndex, &sDS18B20.sDevice[u8DSIndex].u8SerialNumber[0]);
		if(s16Return >= 0)
		{

			//select to start the conversion and put value into scratchpad
			s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u8DSIndex].u8ChannelIndex, 0x44U);
			if(s16Return >= 0)
			{

				//wait for conversion?
				if(u8Wait == 1U)
				{

					switch(sDS18B20.sDevice[u8DSIndex].u8Resolution)
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
					s16Return = s16DS18B20_SCRATCH__Read(u8DSIndex, &u8Scratch[0]);

					vDS18B20_TEMP__Scratch_To_Temp(u8DSIndex, &u8Scratch[0], &sDS18B20.sDevice[u8DSIndex].f32Temperature);

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
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u8DSIndex].u8ChannelIndex);

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
 * @param[in]		u8DSIndex				Index of the device so as we know our resoltion
 * @st_funcMD5		9A0ED5AB3219331A1C1DC2C700DED3E6
 * @st_funcID		LCCM644R0.FILE.003.FUNC.005
 */
void vDS18B20_TEMP__Scratch_To_Temp(Luint8 u8DSIndex, const Luint8 *pu8Scratch, Lfloat32 *pf32Temp)
{
	/*lint -e960*/
	//Note 960: Violates MISRA 2004 Required Rule 18.4, unions shall not be used
	//reviewed OK
	union
	{
		Luint8 u8[2];
		Lint16 s16;

	}unT;
	/*lint +e960*/

	//assign
	unT.u8[0U] = pu8Scratch[0U];
	unT.u8[1U] = pu8Scratch[1U];

	//todo, check teh "S" bit.


	*pf32Temp = (Lfloat32)unT.s16;

	//essentially the temp is in 1/16th of a degree for 12 but.
	switch(sDS18B20.sDevice[u8DSIndex].u8Resolution)
	{
		case 12U:
			*pf32Temp /= 16.0F;
			break;
		case 11U:
			*pf32Temp /= 8.0F;
			break;
		case 10U:
			*pf32Temp /= 4.0F;
			break;
		case 9U:
			*pf32Temp /= 2.0F;
			break;
		default:
			//set to 128C indicating a problem
			*pf32Temp = 128.0F;
			break;
	}//switch(&sDS18B20.sDevice[u8DSIndex].u8Resolution)


	//noting to return, already updated.

}

/***************************************************************************//**
 * @brief
 * Gets the current resolution by reading the scratchpad memory
 * 
 * @param[out]		*pu8Resolution			Returned resolution value
 * @param[in]		u8DSIndex				Already enumerated address ID
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		B97FF5A7F9DAABC011F2404905B8614A
 * @st_funcID		LCCM644R0.FILE.003.FUNC.002
 */
Lint16 s16DS18B20_TEMP__Get_Resolution(Luint8 u8DSIndex, Luint8 *pu8Resolution)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]

	Lint16 s16Return;
	Luint8 u8Scratch[9U];


	//read the scratch
	s16Return = s16DS18B20_SCRATCH__Read(u8DSIndex, &u8Scratch[0]);

	//determine from the scratchpad
	switch(u8Scratch[4U])
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


/***************************************************************************//**
 * @brief
 * Set the temperature resolution
 * 
 * @param[in]		u8Resolution			New Res: 12,11,10 or 9 bit
 * @param[in]		u8DSIndex				Device index address
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		A4C1E4D505C049983604EE4E068E1DCC
 * @st_funcID		LCCM644R0.FILE.003.FUNC.001
 */
Lint16 s16DS18B20_TEMP__Set_Resolution(Luint8 u8DSIndex, Luint8 u8Resolution)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	Lint16 s16Return;
	Luint8 u8Scratch[9U];

	//read the scratch
	s16Return = s16DS18B20_SCRATCH__Read(u8DSIndex, &u8Scratch[0]);

	//todo, check CRC

	//configure the new resolution in the scratchpad
	switch(u8Resolution)
	{
		case 12:
			u8Scratch[4U] = 0x7FU;
			break;

		case 11:
			u8Scratch[4U] = 0x5FU;
			break;

		case 10:
			u8Scratch[4U] = 0x3FU;
			break;

		case 9:
			u8Scratch[4U] = 0x1FU;
			break;

		default:
			//default at 12bit
			u8Scratch[4U] = 0x7FU;
			break;

	}//switch(u8Resolution)

	//update the scratchpad
	s16Return = s16DS18B20_SCRATCH__Write(u8DSIndex, &u8Scratch[0]);

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

