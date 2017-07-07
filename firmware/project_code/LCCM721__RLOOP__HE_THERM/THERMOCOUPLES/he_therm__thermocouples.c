/**
 * @file		HE_THERM__THERMOCOUPLES.C
 * @brief		
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM721R0.FILE.006
 */
/**
 * @addtogroup PROJECT_NAME
 * @{
 */
/**
 * @addtogroup PROJECT_NAME
 * @ingroup MODULE_NAME
 * @{
 */
/**
 * @addtogroup MODULE_NAME__CORE
 * @ingroup MODULE_NAME
 * @{
 */
/** @} */
/** @} */
/** @} */


/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM__THERMOCOUPLES
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_HET__MAIN sHET;


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		DCEB6C610D0562CC4E9072C8A94D0587
 * @st_funcID		LCCM721R0.FILE.006.FUNC.001
 */
void vHETHERM_TC__Init(void)
{
	
	//init the variables
	sHET.sTemp.f32HighestTemp = 0.0F;
	sHET.sTemp.f32AverageTemp = 0.0F;
	sHET.sTemp.u8NewTempAvail = 0U;
	sHET.sTemp.u16HighestSensorIndex = 0U;
	sHET.sTemp.u32TempScanCount = 0U;
	sHET.sTemp.eState = HETHERM_TEMP_STATE__IDLE;
	
	//bring up the 1-wire interface
	vDS2482S__Init();

	//start the temp sensor driver
	vDS18B20__Init();
	
}


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		BDD69C5F3E7A05D3C8846C48E3839284
 * @st_funcID		LCCM721R0.FILE.006.FUNC.002
 */
void vHETHERM_TC__Process(void)
{
	Luint8 u8Test;
	Luint16 u16Counter;
	Luint16 u16NumSensors;
	Luint16 u16User;
	Lfloat32 f32High;
	Lfloat32 f32Temp;
	Lfloat32 f32Sum;
	Lint16 s16Return;
	
	#ifndef WIN32
	//process any search tasks
	vDS18B20_ADDX__SearchSM_Process();
#endif

	//process the DS18B20 devices.
	//devices wont start converting until the network search has completed.
	vDS18B20__Process();
	
	//handle scanning of the sensors.
	switch(sHET.sTemp.eState)
	{
		case HETHERM_TEMP_STATE__IDLE:
			//just come out of reset

			sHET.sTemp.eState = HETHERM_TEMP_STATE__CONFIGURE_RESOLUTION;
			break;

		case HETHERM_TEMP_STATE__CONFIGURE_RESOLUTION:

			//if we have loaded, configure the devices resolution
			//This has been implemented in the DS18B20 stack now, so as soon as the sensors are loaded
			//and ScanComplete is set, the DS18B20 will configure the resolutions per the localdef setting.
			//vDS18B20__Start_ConfigureResolution();

			sHET.sTemp.eState = HETHERM_TEMP_STATE__START_SCAN;
			break;

		case HETHERM_TEMP_STATE__START_SCAN:
			//start a search
#ifndef WIN32
			//start the search state machine
			vDS18B20_ADDX__SearchSM_Start();
#endif

			//wait for the scan
			sHET.sTemp.eState = HETHERM_TEMP_STATE__WAIT_SCAN;
			break;

		case HETHERM_TEMP_STATE__WAIT_SCAN:
			//check the satate
#ifndef WIN32
			u8Test = u8DS18B20_ADDX__SearchSM_IsBusy();
#else
			u8Test = 0U;
#endif
			if(u8Test == 1U)
			{
				//stay in the search state
				//ToDo: Update Timeout
			}
			else
			{
				//change state
				sHET.sTemp.eState = HETHERM_TEMP_STATE__RUN;
			}
			break;

		case HETHERM_TEMP_STATE__RUN:

			//clear the vars
			f32High = 0.0F;
			f32Sum = 0.0F;
			//do we have any new updates from the DS18B20 subsystem?
			u8Test = u8DS18B20__Is_NewDataAvail();
			if(u8Test == 1U)
			{
				//clear the hghest index as it will be recomputed belwo
				sHET.sTemp.u16HighestSensorIndex = 0U;

				//get the number of sensors found
				u16NumSensors = u16DS18B20__Get_NumEnum_Sensors();
				for(u16Counter = 0U; u16Counter < u16NumSensors; u16Counter++)
				{

					//make sure the sensors belong to us.
					u16User = u162DS18B20__Get_UserIndex(u16Counter);

					//compute the highest
					f32Temp = f32DS18B20__Get_Temperature_DegC(u16Counter);
					if(f32Temp > f32High)
					{
						//this sensor value is > than the last higest reading, save it
						f32High = f32Temp;
						sHET.sTemp.u16HighestSensorIndex = u16Counter;

					}
					else
					{
						//this sensor was lower than the last sensor
					}

					//add to the sum
					f32Sum += f32Temp;

				}//for(u16Counter = 0U; u16Counter < u16NumSensors; u16Counter++)


				//divide
				//math safety
				if(u16NumSensors != 0U)
				{
					f32Sum /= (Lfloat32)u16NumSensors;
				}
				else
				{
					//stay the same
				}

				//update our internal vars
				sHET.sTemp.f32HighestTemp = f32High;
				sHET.sTemp.f32AverageTemp = f32Sum;
				sHET.sTemp.u8NewTempAvail = 1U;

				//Inc the scan count
				sHET.sTemp.u32TempScanCount++;

				//done with the new data now
				vDS18B20__Clear_NewDataAvail();
				
			}
			else
			{
				//no new temp readings yet
			}
			break;

	} //switch(sHET.sTemp.eState)
	
}

//is the thermocouple system available.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		FBFFD727B05BFBE91BCF3248E5D0AC3C
 * @st_funcID		LCCM721R0.FILE.006.FUNC.003
 */
Luint8 u8HETHERM_TC__Is_Avail(void)
{
	Luint8 u8Return;

	if(sHET.sTemp.eState == HETHERM_TEMP_STATE__RUN)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}



#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

