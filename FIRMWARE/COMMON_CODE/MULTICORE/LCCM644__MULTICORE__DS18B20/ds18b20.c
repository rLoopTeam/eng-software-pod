/**
 * @file		DS18B20.C
 * @brief		Main module file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS18B20__CORE
 * @ingroup DS18B20
 * @{ */

#include "ds18b20.h"
#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

struct _strDS18B20 sDS18B20;

/***************************************************************************//**
 * @brief
 * Init the DS18B20 device
 * 
 * @note
 * YOU MUST Either start the search process or manually load
 * ROMID values into the tables before doing anything with this module.
 *
 * @st_funcMD5		D8EA8230604994839D2F3F4C48B18E8E
 * @st_funcID		LCCM644R0.FILE.000.FUNC.001
 */
void vDS18B20__Init(void)
{

	//setup
	sDS18B20.sEnum.u16NumDevices = 0U;
	sDS18B20.u8NewData = 0U;
	//setup the vars
	sDS18B20.u32Guard1 = 0x11223344U;
	sDS18B20.u32Guard2 = 0x44556677U;
	sDS18B20.eMainState = DS18B20_STATE__IDLE;


	//setup the vars for the address searching.
	vDS18B20_ADDX__Init();

}

/***************************************************************************//**
 * @brief
 * Process DS18B20 systems
 * Call from main program loop as quick as possible.
 * 
 * @st_funcMD5		CBFDFFAC4C0AD3B6C780F94FED676659
 * @st_funcID		LCCM644R0.FILE.000.FUNC.002
 */
void vDS18B20__Process(void)
{
	Lint16 s16Return;
	Luint8 u8Counter;

	//if need be process the search functions
	vDS18B20_ADDX__SearchSM_Process();

	//check the guards
	if(sDS18B20.u32Guard1 != 0x11223344)
	{
		//todo: fault
	}
	if(sDS18B20.u32Guard2 != 0x44556677)
	{
		//todo: fault
	}


	//handle our main SM
	switch(sDS18B20.eMainState)
	{
		case DS18B20_STATE__IDLE:
			//do nothing.

			if(sDS18B20.sSearch.u8SearchCompleted == 1U)
			{

				if(sDS18B20.sEnum.u16NumDevices > 0U)
				{

					//clear our device counter now.
					sDS18B20.u16MainStateCounter = 0U;

					//setup the resolutions
					//todo: could change to configure resoltution, BUT ONLY ONCE.
					sDS18B20.eMainState = DS18B20_STATE__CONFIGURE_RESOLUTION; //DS18B20_STATE__READ_RESOLUTION;
				}
				else
				{
					//stay here
				}

			}
			else
			{
				//stay here
			}

			break;

		case DS18B20_STATE__CONFIGURE_RESOLUTION:
			//once we have searched and we have a valid search array, we need to configure
			//the devices onboard resolution before we can start converting.

			/* WARNING
			 * The DS18B20 has EEPROM
			 * There is no-need to configure the resolution each time
			 * This could ruin the device.
			 *
			 */

			//configure the resolution
			if(sDS18B20.sDevice[sDS18B20.u16MainStateCounter].u8SerialNumber[0] != 0x3B) //Thermocouples don't have resolution settings
			{
				s16Return = s16DS18B20_TEMP__Set_Resolution(sDS18B20.u16MainStateCounter, C_LOCALDEF__LCCM644__RESOLUTION_SETTING);
				if(s16Return >= 0)
				{
					//res was set good.
				}
				else
				{
					//some error
				}
			}else{
				//Do nothing
			}


			sDS18B20.u16MainStateCounter++;
			if(sDS18B20.u16MainStateCounter > sDS18B20.sEnum.u16NumDevices)
			{
				//move on and read-back the resolution.
				sDS18B20.u16MainStateCounter = 0U;
				sDS18B20.eMainState = DS18B20_STATE__READ_RESOLUTION;
			}
			else
			{
				//keep going
			}
			break;

		case DS18B20_STATE__READ_RESOLUTION: //And User ID
			//once we have searched and we have a valid search array, we need to configure
			//the devices onboard resolution before we can start converting.

			if(sDS18B20.sDevice[sDS18B20.u16MainStateCounter].u8SerialNumber[0] != 0x3B) //Thermocouples don't have resolution settings
			{
				//configure the resolution
				s16Return = s16DS18B20_TEMP__Get_Resolution(sDS18B20.u16MainStateCounter, &sDS18B20.sDevice[sDS18B20.u16MainStateCounter].u8Resolution);
				if(s16Return >= 0)
				{
					//res get was set good.

					//todo: compare with what we were expecting.

				}
				else
				{
					//some error
				}
			}else{
				//configure the resolution
				// s16Return = s16DS18B20_TEMP__Get_UserID(sDS18B20.u16MainStateCounter);  // this wipes out the userID  set to 0.
				if(s16Return >= 0)
				{
					//res get was set good.

					//todo: compare with what we were expecting.

				}
				else
				{
					//some error
				}
			}


			sDS18B20.u16MainStateCounter++;
			if(sDS18B20.u16MainStateCounter > sDS18B20.sEnum.u16NumDevices)
			{
				sDS18B20.eMainState = DS18B20_STATE__START_CONVERT_ALL;
			}
			else
			{
				//keep going
			}
			break;

		case DS18B20_STATE__START_CONVERT_ALL:

			//do the conversion

			//TODO:
			//There is going to be a big problem as we only do a request all on
			//one BUS. IF we have devices on multiple busses we need to also do a request all on the
			//second bus too.
			#if C_LOCALDEF__LCCM644__USE_10MS_ISR == 0U
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS; u8Counter++)
			{
				s16Return = s16DS18B20_TEMP__All_Request_ByChannel(u8Counter, 1U);
			}
			#else
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS; u8Counter++)
			{
				s16Return = s16DS18B20_TEMP__All_Request_ByChannel(u8Counter, 0U);
			}
			#endif
			if(s16Return >= 0)
			{

			}
			else
			{
				//some error
			}

			//depending if we have interrupts avail or not, either wait or go to read.
			#if C_LOCALDEF__LCCM644__USE_10MS_ISR == 0U
				//clear the counter
				sDS18B20.u32ISR_Counter = 0U;

				//clear our device counter now.
				sDS18B20.u16MainStateCounter = 0U;

				//just jump to reading the sensors are we are not using ISR's to count time.
				sDS18B20.eMainState = DS18B20_STATE__READ_SENSORS;
			#else

				//clear the counter
				sDS18B20.u32ISR_Counter = 0U;

				//clear our device counter now.
				sDS18B20.u16MainStateCounter = 0U;

				//change state
				sDS18B20.eMainState = DS18B20_STATE__WAIT_CONVERT;
			#endif

			break;

		case DS18B20_STATE__WAIT_CONVERT:


			#if C_LOCALDEF__LCCM644__RESOLUTION_SETTING == 9U
				if(sDS18B20.u32ISR_Counter > 10U)
				{
					//go and read the sensor now
					sDS18B20.eMainState = DS18B20_STATE__READ_SENSORS;
				}
				else
				{
					//wait here.
				}
			#elif C_LOCALDEF__LCCM644__RESOLUTION_SETTING == 10U
				if(sDS18B20.u32ISR_Counter > 19U)
				{
					//go and read the sensor now
					sDS18B20.eMainState = DS18B20_STATE__READ_SENSORS;
				}
				else
				{
					//wait here.
				}
			#elif C_LOCALDEF__LCCM644__RESOLUTION_SETTING == 11U
				if(sDS18B20.u32ISR_Counter > 38U)
				{
					//go and read the sensor now
					sDS18B20.eMainState = DS18B20_STATE__READ_SENSORS;
				}
				else
				{
					//wait here.
				}
			#elif C_LOCALDEF__LCCM644__RESOLUTION_SETTING == 12U
				if(sDS18B20.u32ISR_Counter > 76U)
				{
					//go and read the sensor now
					sDS18B20.eMainState = DS18B20_STATE__READ_SENSORS;
				}
				else
				{
					//wait here.
				}
			#endif

			break;

		case DS18B20_STATE__READ_SENSORS:


			//get the temp data from each sensor
			s16Return = s16DS18B20_TEMP__Read(sDS18B20.u16MainStateCounter);
			if(s16Return >= 0)
			{
				//all good.
			}
			else
			{
				//error
			}


			sDS18B20.u16MainStateCounter++;
			if(sDS18B20.u16MainStateCounter > sDS18B20.sEnum.u16NumDevices)
			{
				sDS18B20.eMainState = DS18B20_STATE__READ_DONE;
			}
			else
			{
				//keep going
				//clear the counter
				sDS18B20.u32ISR_Counter = 0U;

				sDS18B20.eMainState = DS18B20_STATE__READ_SENSOR_STATE_DELAY;
			}

			break;

		case DS18B20_STATE__READ_SENSOR_STATE_DELAY:

			//wait for 50ms between sensor reads so as not to flog the I2C
			if(sDS18B20.u32ISR_Counter > 4U)
			{
				//read more
				sDS18B20.eMainState = DS18B20_STATE__READ_SENSORS;
			}
			else
			{
				//stay in state
			}
			break;

		case DS18B20_STATE__READ_DONE:

			//signal that new temp data is avail
			sDS18B20.u8NewData = 1U;

			//go back and do more
			sDS18B20.eMainState = DS18B20_STATE__START_CONVERT_ALL;
			break;

	}//switch(sDS18B20.eMainState)

}

/***************************************************************************//**
 * @brief
 * Return if any new data is avail.
 * 
 * @st_funcMD5		E782611D5C32A4F38153FEE200AC5AB5
 * @st_funcID		LCCM644R0.FILE.000.FUNC.005
 */
Luint8 u8DS18B20__Is_NewDataAvail(void)
{
	return sDS18B20.u8NewData;
}

/***************************************************************************//**
 * @brief
 * Clear the new data avail flag.
 * 
 * @st_funcMD5		C2780A64BC9FD30831AB63C07B76C8BD
 * @st_funcID		LCCM644R0.FILE.000.FUNC.006
 */
void vDS18B20__Clear_NewDataAvail(void)
{
	sDS18B20.u8NewData = 0U;
}

/***************************************************************************//**
 * @brief
 * Start the temperature read state machine
 * 
 * @st_funcMD5		506F869ABA240892F387AF5B18B8B8E3
 * @st_funcID		LCCM644R0.FILE.000.FUNC.003
 */
void vDS18B20__Start_TempRead(void)
{
	if(sDS18B20.eMainState == DS18B20_STATE__IDLE)
	{
		sDS18B20.eMainState = DS18B20_STATE__START_CONVERT_ALL;
	}
	else
	{
		//do not allow the state change
	}
}

/***************************************************************************//**
 * @brief
 * Setup the resolutions
 * 
 * @st_funcMD5		55785263636692BDA22431A15B8024B7
 * @st_funcID		LCCM644R0.FILE.000.FUNC.013
 */
void vDS18B20__Start_ConfigureResolution(void)
{
	if(sDS18B20.eMainState == DS18B20_STATE__IDLE)
	{
		if(sDS18B20.sSearch.u8SearchCompleted == 1U)
		{
			sDS18B20.eMainState = DS18B20_STATE__CONFIGURE_RESOLUTION;
		}
		else
		{
			//cant start yet
		}
	}
	else
	{
		//do not allow the state change
	}
}

/***************************************************************************//**
 * @brief
 * Get the last measured temperature
 * 
 * @param[in]		u16SensorIndex				Sensor index
 * @st_funcMD5		55BED7741DD61A81EFDDBD54FEE78923
 * @st_funcID		LCCM644R0.FILE.000.FUNC.007
 */
Lfloat32 f32DS18B20__Get_Temperature_DegC(Luint16 u16SensorIndex)
{
	return sDS18B20.sTemp[u16SensorIndex].f32Temperature;
}

/***************************************************************************//**
 * @brief
 * Returns the number of enumerated sensors found
 * 
 * @st_funcMD5		8D0E870089BAC035DFA5BF2426DE7C7C
 * @st_funcID		LCCM644R0.FILE.000.FUNC.014
 */
Luint16 u16DS18B20__Get_NumEnum_Sensors(void)
{
	return sDS18B20.sEnum.u16NumDevices;
}

/***************************************************************************//**
 * @brief
 * Gets the device memory address
 * 
 * @st_funcMD5		0003E6324F8E85F37E1E0C51290EFBFC
 * @st_funcID		LCCM644R0.FILE.000.FUNC.008
 */
Luint32 u32DS18B20__Get_DeviceAddx(void)
{
	return (Luint32)&sDS18B20.sDevice[0];
}

/***************************************************************************//**
 * @brief
 * Get the user variable index
 * 
 * @param[in]		u16SensorIndex			Sensor Index
 * @st_funcMD5		C9056334031B2B7EBD1E524C882811A1
 * @st_funcID		LCCM644R0.FILE.000.FUNC.009
 */
Luint16 u162DS18B20__Get_UserIndex(Luint16 u16SensorIndex)
{
	return sDS18B20.sDevice[u16SensorIndex].u16UserIndex;
}

/***************************************************************************//**
 * @brief
 * Get the sensor resolution
 * 
 * @param[in]		u16SensorIndex			Sensor index
 * @st_funcMD5		882A8C0560C0082E8FFA36513C1B4D1A
 * @st_funcID		LCCM644R0.FILE.000.FUNC.010
 */
Luint8 u82DS18B20__Get_Resolution(Luint16 u16SensorIndex)
{
	return sDS18B20.sDevice[u16SensorIndex].u8Resolution;
}

/***************************************************************************//**
 * @brief
 * Get the BUS index that the sensor is located on
 * 
 * @param[in]		u16SensorIndex			Sensor index
 * @st_funcMD5		6347AE473D815D032A6825EAB1BBE65D
 * @st_funcID		LCCM644R0.FILE.000.FUNC.011
 */
Luint8 u82DS18B20__Get_BusIndex(Luint16 u16SensorIndex)
{
	return sDS18B20.sDevice[u16SensorIndex].u8ChannelIndex;
}

/***************************************************************************//**
 * @brief
 * Return the ROMID
 * 
 * @param[in]		*pu8Buffer					Pointer to buffer to hold the ROM ID
 * @param[in]		u16SensorIndex				Sensor index in its array
 * @st_funcMD5		CA517A05118D37B938859E5CBF55777B
 * @st_funcID		LCCM644R0.FILE.000.FUNC.012
 */
void vDS18B20__Get_ROMID(Luint16 u16SensorIndex, Luint8 *pu8Buffer)
{
	Luint8 u8Counter;
	for(u8Counter = 0U; u8Counter < C_DS18B20__ROMID_SIZE; u8Counter++)
	{
		pu8Buffer[u8Counter] = sDS18B20.sDevice[u16SensorIndex].u8SerialNumber[u8Counter];
	}
}

#if C_LOCALDEF__LCCM644__USE_10MS_ISR == 1U
/***************************************************************************//**
 * @brief
 * If we have access to a 10ms ISR then use it, else we need to wait manually
 * 
 * @st_funcMD5		2EFF2F9513ECDACF63F2615A2C620299
 * @st_funcID		LCCM644R0.FILE.000.FUNC.004
 */
void vDS18B20__10MS_ISR(void)
{
	//inc the count of 10ms interrupts.
	sDS18B20.u32ISR_Counter++;
}

#endif


//safetys
#ifndef C_LOCALDEF__LCCM644__RESOLUTION_SETTING
	#error
#else
	//check the valid res
	#if C_LOCALDEF__LCCM644__RESOLUTION_SETTING != 9U
	#if C_LOCALDEF__LCCM644__RESOLUTION_SETTING != 10U
	#if C_LOCALDEF__LCCM644__RESOLUTION_SETTING != 11U
	#if C_LOCALDEF__LCCM644__RESOLUTION_SETTING != 12U
		#error
	#endif
	#endif
	#endif
	#endif
#endif
#ifndef C_LOCALDEF__LCCM644__USE_10MS_ISR
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

