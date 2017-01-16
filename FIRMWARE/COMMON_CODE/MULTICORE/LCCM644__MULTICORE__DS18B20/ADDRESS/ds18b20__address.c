/**
 * @file		DS18B20__ADDRESS.C
 * @brief		Addressing search and support for DS18B20
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.006
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20__ADDRESS
 * @ingroup DS18B20
 * @{ */

#include "../ds18b20.h"
#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

extern struct _strDS18B20 sDS18B20;


/***************************************************************************//**
 * @brief
 * Init the addressing module
 * 
 * @st_funcMD5		035167D86A5C1B6A0F972794E0D0E221
 * @st_funcID		LCCM644R0.FILE.006.FUNC.002
 */
void vDS18B20_ADDX__Init(void)
{

	//init the vars
	sDS18B20.sSearch.sSearchState = SEARCH_STATE__IDLE;
	sDS18B20.sSearch.u8WireChannelCounter = 0U;
	sDS18B20.sSearch.u8FirstSearched = 0U;
	sDS18B20.sSearch.u8SearchCompleted = 0U;

}


/***************************************************************************//**
 * @brief
 * Search for all devices on the bus on all channels
 * 
 * @note
 * This is a single blocking function that will try and search for everything via
 * binary tree searching of the ROM ID's.
 * THIS IS VERY SLOW.  Several hundred sensors can take minutes to search.
 * If this is a problem, use the state machine based search.
 *
 * @st_funcMD5		03D56F57CC4B53C6E8DDFB5E41E53B27
 * @st_funcID		LCCM644R0.FILE.006.FUNC.001
 */
Lint16 s16DS18B20_ADDX__Search(void)
{

	Luint8 u8ChannelCounter;
	Luint16 u16DeviceCounter;
	Lint16 s16Return;
	Luint16 u16Counter;
	Luint8 u8FirstSearched;
	Luint8 u8Flag;

	//setup
	sDS18B20.sEnum.u16NumDevices = 0U;

	//flag to indicat that we have already searched for the first device.
	u8FirstSearched = 0U;
	u8Flag = 0U;

	//search each 1 wire channel
	for(u8ChannelCounter = 0U; u8ChannelCounter < C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS; u8ChannelCounter++)
	{

		//handle the max devices the user has allocated space for
		for(u16DeviceCounter = 0U; u16DeviceCounter < C_LOCALDEF__LCCM644__MAX_DEVICES; u16DeviceCounter++)
		{
			//see if we have not searched our fist device
			if(u8FirstSearched == 0U)
			{
				//set the flag to indicate that the first search has been done.
				u8FirstSearched = 1U;

				//search for the first device on a channel
				s16Return = s16DS18B20_SEARCH__SearchFirstDevice(u8ChannelCounter, &sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8SerialNumber[0]);
				if(s16Return > 0)
				{
					//we have found a device
					//set the channel index we are on
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8ChannelIndex = u8ChannelCounter;
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8Resolution = 0U;
					
					//set to our known max temp
					sDS18B20.sTemp[sDS18B20.sEnum.u16NumDevices].f32Temperature = 127.0F;
					//inc
					sDS18B20.sEnum.u16NumDevices++;

					//protect
					if(sDS18B20.sEnum.u16NumDevices < C_LOCALDEF__LCCM644__MAX_DEVICES)
					{
						//fall on
					}
					else
					{
						//limit
						sDS18B20.sEnum.u16NumDevices = C_LOCALDEF__LCCM644__MAX_DEVICES - 1U;
					}

				}
				else
				{
					//nothign on this channel or channel fault
					u8Flag = 1U;
				}

			}
			else
			{
				//search for other devices
				s16Return = s16DS18B20_SEARCH__SearchNextDevice(u8ChannelCounter, &sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8SerialNumber[0]);
				if(s16Return > 0)
				{
					//set the channel index we are on
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8ChannelIndex = u8ChannelCounter;
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8Resolution = 0U;
					
					//set to our known max temp.
					sDS18B20.sTemp[sDS18B20.sEnum.u16NumDevices].f32Temperature = 127.0F;

					//inc
					sDS18B20.sEnum.u16NumDevices++;

					//protect
					if(sDS18B20.sEnum.u16NumDevices < C_LOCALDEF__LCCM644__MAX_DEVICES)
					{
						//fall on
					}
					else
					{
						//limit
						sDS18B20.sEnum.u16NumDevices = C_LOCALDEF__LCCM644__MAX_DEVICES - 1U;
					}
				}
				else
				{
					//no devices or no more devices
					u8Flag = 1U;

				}
			}

			if(u8Flag == 1U)
			{
				//MISRA-C only one break point per loop.
				break;
			}
			else
			{
				//keep going
			}
			
		}//for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM644__MAX_DEVICES; u8DeviceCounter++)


		//reset for next channel
		u8FirstSearched = 0U;


	}//for(u8ChannelCounter = 0U; u8ChannelCounter < C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS; u8ChannelCounter++)


	//we must find the resolutions of the devices, do this now
	for(u16Counter = 0U; u16Counter < sDS18B20.sEnum.u16NumDevices; u16Counter++)
	{

		s16Return = s16DS18B20_TEMP__Get_Resolution(u16Counter, &sDS18B20.sDevice[u16Counter].u8Resolution);
		if(s16Return >= 0)
		{
			//all good
		}
		else
		{
			//issues
			break;
		}

	}//for(u8Counter = 0U; u8Counter < sDS18B20.sEnum.u8NumDevices; u8Counter++)

	//indicate that we have completed searching
	sDS18B20.sSearch.u8SearchCompleted = 1U;


	return 0;
}

/***************************************************************************//**
 * @brief
 * Start the search
 * 
 * @st_funcMD5		24F9B9296E21F4BD8177F4D713AB4017
 * @st_funcID		LCCM644R0.FILE.006.FUNC.003
 */
void vDS18B20_ADDX__SearchSM_Start(void)
{
	//if we are idle, move to the start state
	if(sDS18B20.sSearch.sSearchState == SEARCH_STATE__IDLE)
	{
		sDS18B20.sSearch.sSearchState = SEARCH_STATE__START;
	}
	else
	{
		//do not allow a resetart
	}
}

/***************************************************************************//**
 * @brief
 * State machine based search processing
 * 
 * @st_funcMD5		43A0A3E0F1548582B19735246BA11219
 * @st_funcID		LCCM644R0.FILE.006.FUNC.004
 */
void vDS18B20_ADDX__SearchSM_Process(void)
{
	Lint16 s16Return;
	Luint8 u8Flag;

	//handle the search processing states
	switch(sDS18B20.sSearch.sSearchState)
	{

		case SEARCH_STATE__IDLE:
			//in idle state do nothing.
			break;

		case SEARCH_STATE__START:
			//setup some variables
			sDS18B20.sSearch.u8WireChannelCounter = 0U;
			sDS18B20.sSearch.u8FirstSearched = 0U;

			//clear the enumerated devices
			sDS18B20.sEnum.u16NumDevices = 0U;

			//move state
			sDS18B20.sSearch.sSearchState = SEARCH_STATE__RUN;
			break;

		case SEARCH_STATE__RUN:
			//running the search
			if(sDS18B20.sSearch.u8FirstSearched == 0U)
			{
				//update the flag
				sDS18B20.sSearch.u8FirstSearched  = 1U;

				//search for the first device on a channel
				s16Return = s16DS18B20_SEARCH__SearchFirstDevice(sDS18B20.sSearch.u8WireChannelCounter, &sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8SerialNumber[0]);
				if(s16Return > 0)
				{
					u8Flag = 0U;

					//we have found a device
					//set the channel index we are on
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8ChannelIndex = sDS18B20.sSearch.u8WireChannelCounter;
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8Resolution = 0U;

					//set to our known max temp
					sDS18B20.sTemp[sDS18B20.sEnum.u16NumDevices].f32Temperature = 127.0F;
					//inc
					sDS18B20.sEnum.u16NumDevices++;
					//protect
					if(sDS18B20.sEnum.u16NumDevices < C_LOCALDEF__LCCM644__MAX_DEVICES)
					{
						//fall on
					}
					else
					{
						//limit
						sDS18B20.sEnum.u16NumDevices = C_LOCALDEF__LCCM644__MAX_DEVICES - 1U;
					}

				}
				else
				{
					//nothign on this channel or channel fault
					u8Flag = 1U;
				}
			}//if(sDS18B20.sSearch.u8FirstSearched == 0U)
			else
			{
				//search for other devices
				s16Return = s16DS18B20_SEARCH__SearchNextDevice(sDS18B20.sSearch.u8WireChannelCounter, &sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8SerialNumber[0]);
				if(s16Return > 0)
				{
					//set the channel index we are on
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8ChannelIndex = sDS18B20.sSearch.u8WireChannelCounter;
					sDS18B20.sDevice[sDS18B20.sEnum.u16NumDevices].u8Resolution = 0U;

					//set to our known max temp.
					sDS18B20.sTemp[sDS18B20.sEnum.u16NumDevices].f32Temperature = 127.0F;

					//inc
					sDS18B20.sEnum.u16NumDevices++;

					//protect
					if(sDS18B20.sEnum.u16NumDevices < C_LOCALDEF__LCCM644__MAX_DEVICES)
					{
						//fall on
					}
					else
					{
						//limit
						sDS18B20.sEnum.u16NumDevices = C_LOCALDEF__LCCM644__MAX_DEVICES - 1U;
					}

					u8Flag = 0U;
				}
				else
				{
					//no devices
					u8Flag = 1U;
				}

			}//else if(sDS18B20.sSearch.u8FirstSearched == 0U)

			if(u8Flag == 0U)
			{
				//stay in this state and loop back around
				sDS18B20.sSearch.sSearchState = SEARCH_STATE__RUN;
			}
			else
			{
				//try the next 1-wire channel
				sDS18B20.sSearch.sSearchState = SEARCH_STATE__INC_CHANNEL;
			}

			break;

		case SEARCH_STATE__INC_CHANNEL:

			//reset the variables
			sDS18B20.sSearch.u8FirstSearched = 0U;

			//increment to the next channel
			sDS18B20.sSearch.u8WireChannelCounter++;

			if(sDS18B20.sSearch.u8WireChannelCounter < C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS)
			{
				//go back for more
				sDS18B20.sSearch.sSearchState = SEARCH_STATE__RUN;
			}
			else
			{
				//we have no more channels to search, we are done
				sDS18B20.sSearch.sSearchState = SEARCH_STATE__CLEANUP;
			}

			break;

		case SEARCH_STATE__CLEANUP:

			//indicate that we have completed searching
			sDS18B20.sSearch.u8SearchCompleted = 1U;

			//back to idle
			sDS18B20.sSearch.sSearchState = SEARCH_STATE__IDLE;

			break;

		default:
			//do nothing
			break;

	}//switch(sDS18B20.sSearchState)
}


/***************************************************************************//**
 * @brief
 * Manually upload an address into the device table.
 *
 * @note
 * WARNING: Addresses must be loaded incrementally from 0 to n.  This function
 * Will set the maximum enumerated index as +1 from the last supplied index
 * 
 * @param[in]		*pu8Addx				Pointer to the ROM ID
 * @param[in]		u8ChannelIndex				The 1-wire channel (0 ro 1)
 * @param[in]		u16SensorIndex					The index in the device table.
 * @return			0 = success\n
 *					-ve = error
 * @st_funcMD5		C5F366E226D6FBF235ACD5DE610D696C
 * @st_funcID		LCCM644R0.FILE.006.FUNC.006
 */
Lint16 s16DS18B20_ADDX__Upload_Addx(Luint16 u16SensorIndex, Luint8 u8ChannelIndex, Luint8 *pu8Addx)
{
	Lint16 s16Return;

	if(u16SensorIndex < C_LOCALDEF__LCCM644__MAX_DEVICES)
	{

		//addx was in range, save addx data.
		//Do this manually
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[0] = pu8Addx[0];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[1] = pu8Addx[1];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[2] = pu8Addx[2];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[3] = pu8Addx[3];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[4] = pu8Addx[4];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[5] = pu8Addx[5];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[6] = pu8Addx[6];
		sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[7] = pu8Addx[7];

		sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex = u8ChannelIndex;

		//set the num devices to the max index.
		//expected that user updates in order
		sDS18B20.sEnum.u16NumDevices = u16SensorIndex + 1U;

		//good
		s16Return = 0;

	}
	else
	{
		//error
		s16Return = -1;
	}

	//return the fault code
	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Returns the number of enumerated devices.
 * 
 * @return			The num enumerated, or manually added devices
 * @st_funcMD5		78A160EF3A561E598B4CEED556011A47
 * @st_funcID		LCCM644R0.FILE.006.FUNC.007
 */
Luint16 u16DS18B20_ADDX__Get_NumEnumerated(void)
{
	return sDS18B20.sEnum.u16NumDevices;
}


//if you are manually loading up addresses, set this to 1 after the manual load.
void vDS18B20_ADDX__Set_SearchComplete(void)
{
	sDS18B20.sSearch.u8SearchCompleted = 1U;
}

/***************************************************************************//**
 * @brief
 * Checks to see if the search state machine is busy or not
 * 
 * @return			1 = We are busy\n
 *					0 = Not busy / Idle
 * @st_funcMD5		E720061D5D7EB748E726EFDCFBCD7CB4
 * @st_funcID		LCCM644R0.FILE.006.FUNC.005
 */
Luint8 u8DS18B20_ADDX__SearchSM_IsBusy(void)
{
	Luint8 u8Return;

	//if we are idle, return not busy
	if(sDS18B20.sSearch.sSearchState == SEARCH_STATE__IDLE)
	{
		u8Return = 0U;
	}
	else
	{
		//busy
		u8Return = 1U;
	}

	return u8Return;
}

//safetys
#ifndef C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS
	#error
#endif

#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

