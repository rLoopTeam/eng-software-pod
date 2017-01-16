/**
 * @file		DS18B20__SCRATCHPAD.C
 * @brief		DS18B20 Scratchpad read and write functions.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.004
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20__SCRATCHPAD
 * @ingroup DS18B20
 * @{ */
#include "../ds18b20.h"
#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

extern struct _strDS18B20 sDS18B20;


/***************************************************************************//**
 * @brief
 * Write to the scratch pad, and then commit to the device
 * 
 * @param[in]		*pu8Scratch				Buffer holding scratchpad data
 * @param[in]		u16SensorIndex				Address index
 * @return			0 = success\n
 * 					-ve = error
 * @st_funcMD5		0F8658952A33463C9CEB88D97FF1A6EE
 * @st_funcID		LCCM644R0.FILE.004.FUNC.002
 */
Lint16 s16DS18B20_SCRATCH__Write(Luint16 u16SensorIndex, const Luint8 *pu8Scratch)
{
	Lint16 s16Return;

	//reset the one-wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);
	if(s16Return >= 0)
	{
		//select the correct device
		s16Return = s16DS18B20_1WIRE__SelectDevice(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, &sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[0]);
		if(s16Return >= 0)
		{

			//select the WRITE scratchpad = 0x4E
			s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, 0x4EU);
			if(s16Return >= 0)
			{

				//we can only write some parts of the scratchpad
				//Temp Alarm - High
				s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, pu8Scratch[2U]);
				//Temp Alarm - Low
				s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, pu8Scratch[3U]);

				//generate the reset
				s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);

				//select the device again
				s16Return = s16DS18B20_1WIRE__SelectDevice(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, &sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[0]);

				//issue a copy command 0x48
				s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, 0x48U);

				//must wait for 10ms
				vDS18B20_DELAYS__Delay_mS(10U);

				//fall on.


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
}

/***************************************************************************//**
 * @brief
 * Read the scratch memory, 9 bytes
 *
 * @note
 * The DSIndex must be a valid already searched or already known ROM serial number.
 * 
 * @note
 * Scratchpad Byte Allocation:
 * 0: 	Temperature LSB
 * 1: 	Temperature MSB
 * 2: 	High alarm temp
 * 3: 	Low alarm temp
 * 4: 	DS18S20: store for crc
 * 	  	DS18B20 & DS1822: configuration register
 * 5: 	Internal use & crc
 * 6: 	DS18S20: COUNT_REMAIN
 *		DS18B20 & DS1822: store for crc
 * 7: 	DS18S20: COUNT_PER_C
 * 		DS18B20 & DS1822: store for crc
 * 8: 	SCRATCHPAD_CRC
 *
 * @param[in]		*pu8Scratch				Pointer to return scratchpad memory.
 * @param[in]		u16SensorIndex				The index of the DS2482 device ROM serial number
 * @return			0 = success\n
 * 					-ve = error
 * @st_funcMD5		F5C21A2413EB188C980C35D9929417EC
 * @st_funcID		LCCM644R0.FILE.004.FUNC.001
 */
Lint16 s16DS18B20_SCRATCH__Read(Luint16 u16SensorIndex, Luint8 *pu8Scratch)
{

	Lint16 s16Return;
	Luint8 u8Counter;
	Luint8 u8CRC;

	//reset the one-wire
	s16Return = s16DS18B20_1WIRE__Generate_Reset(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex);
	if(s16Return >= 0)
	{
		//select the correct device
		s16Return = s16DS18B20_1WIRE__SelectDevice(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, &sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[0]);
		if(s16Return >= 0)
		{

			//select the read scratchpad = 0xBE
			s16Return = s16DS18B20_1WIRE__WriteByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, 0xBEU);
			if(s16Return >= 0)
			{

				//read the scratchpad
				for(u8Counter = 0U; u8Counter < C_DS18B20__SCRATCHPAD_SIZE; u8Counter++)
				{
					s16Return = s16DS18B20_1WIRE__ReadByte(sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex, &pu8Scratch[u8Counter]);
					if(s16Return < 0)
					{

						//fall through with error code
						break;
					}
					else
					{
						//continue on
					}

				}//for(u8Counter = 0U; u8Counter < 9U; u8Counter++)
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
	if(s16Return >= 0)
	{

		//check the CRC
		u8CRC = u8DS18B20_SCRATCH__Compute_CRC(pu8Scratch);

		if(u8CRC != pu8Scratch[8U])
		{
			//CRC fault
			s16Return = -10;
		}
		else
		{
			//good
			s16Return = 0;
		}

	}
	else
	{
		//fault fall on
	}


	return s16Return;
}

/***************************************************************************//**
 * @brief
 * compute the CRC on the scratch pad
 *
 * @note
 * http://pdfserv.maximintegrated.com/en/an/AN27.pdf
 * 
 * @param[in]		*pu8Scratch				Pointer to the scratch ram buffer
 * @return			The computed CRC
 * @st_funcMD5		AEAF986D7CBDBAA8D8CD0B4C903D15DE
 * @st_funcID		LCCM644R0.FILE.004.FUNC.003
 */
Luint8 u8DS18B20_SCRATCH__Compute_CRC(Luint8 *pu8Scratch)
{

	Luint8 u8ByteCounter;
	Luint8 u8BitCounter;
	Luint8 u8CRC;
	Luint8 u8Current;
	Luint8 u8Test;

	//init
	u8CRC = 0U;

	//go through each of the 8 bytes
	//scratch is 9 bytes, but the last byte is the actual CRC.
	for(u8ByteCounter = 0U; u8ByteCounter < 8U; u8ByteCounter++)
	{
		//get a copy of the current byte
		u8Current = pu8Scratch[u8ByteCounter];

		for(u8BitCounter = 0U; u8BitCounter < 8U; u8BitCounter++)
		{
			//compute
			u8Test = (u8CRC ^ u8Current) & 0x01U;

			//move across
			u8CRC >>= 0x01U;

			//see if we are a 1
			if(u8Test != 0x00U)
			{
				u8CRC ^= 0x8CU;
			}

			//shift
			u8Current >>= 0x01U;

		}//for(u8BitCounter = 0U; u8BitCounter < 8U; u8BitCounter++)

	}//for(u8ByteCounter = 0U; u8ByteCounter < 8U; u8ByteCounter++)

	return u8CRC;

}


#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

