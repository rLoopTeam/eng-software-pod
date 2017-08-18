/**
 * @file		HE_THERM__THERMOCOUPLES.C
 * @brief		TC Interface
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.006
 */

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

//ROM ID's
#ifndef WIN32
	extern const Luint8 u8HETherm_ROMID[];
#else
	extern Luint8 u8HETherm_ROMID[];
#endif

/***************************************************************************//**
 * @brief
 * Init the thermocouple interface
 * 
 * @st_funcMD5		C45DF4E220392279BA5EB09137BFD982
 * @st_funcID		LCCM721R0.FILE.006.FUNC.001
 */
void vHETHERM_TC__Init(void)
{
	
	//init the variables
	sHET.sTemp.u8NewTempAvail = 0U;
	sHET.sTemp.u32TempScanCount = 0U;
	sHET.sTemp.eState = HETHERM_TEMP_STATE__IDLE;
	
	sHET.sMotorTemp.sLeftHE.f32HighestTemp = 0.0F;
	sHET.sMotorTemp.sRightHE.f32HighestTemp = 0.0F;
	sHET.sMotorTemp.sBrakeMotor.f32HighestTemp = 0.0F;

	sHET.sMotorTemp.sLeftHE.f32AverageTemp = 0.0F;
	sHET.sMotorTemp.sRightHE.f32AverageTemp = 0.0F;
	sHET.sMotorTemp.sBrakeMotor.f32AverageTemp = 0.0F;

	//bring up the 1-wire interface
	vDS2482S__Init();

	//start the temp sensor driver
	vDS18B20__Init();
	
}


/***************************************************************************//**
 * @brief
 * Process the TC interface
 * 
 * @st_funcMD5		713358EA45B2551C135CB8A148ADA787
 * @st_funcID		LCCM721R0.FILE.006.FUNC.002
 */
void vHETHERM_TC__Process(void)
{
	Luint8 u8Test;
	Luint16 u16Counter;
	Luint16 u16NumSensors;
	Luint16 u16User;
	Lfloat32 f32Temp;
	// Lint16 s16Return;
	Luint32 u32Counter;
	Luint32 u32Max;
	union
	{
		Luint8 u8[2];
		Luint16 u16;
	}unT;
	
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
			sHET.sTemp.eState = HETHERM_TEMP_STATE__LOAD_DEFAULTS;
			break;

		case HETHERM_TEMP_STATE__LOAD_DEFAULTS:

			//load up the memory default arrays

			u32Max = 0U;

			//copy into the driver
			for(u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM644__MAX_DEVICES; u32Counter++)
			{

				//Get the user ID
				unT.u8[0] = u8HETherm_ROMID[u32Max + 11U];
				unT.u8[1] = u8HETherm_ROMID[u32Max + 10U];

				//upload
				s16DS18B20_ADDX__Upload_Addx2(u32Counter, u8HETherm_ROMID[u32Max + 8U], (Luint8 *)&u8HETherm_ROMID[u32Max], u8HETherm_ROMID[u32Max + 9U], unT.u16);

				//increment the memory addx size
				u32Max += 12U;

			}

			//signal to the device that we have loaded all our avail data.
			vDS18B20_ADDX__Set_SearchComplete();

			sHET.sTemp.eState = HETHERM_TEMP_STATE__START_SCAN; // HETHERM_TEMP_STATE__CONFIGURE_RESOLUTION;
			break;


		case HETHERM_TEMP_STATE__CONFIGURE_RESOLUTION:

			//if we have loaded, configure the devices resolution
			//This has been implemented in the DS18B20 stack now, so as soon as the sensors are loaded
			//and ScanComplete is set, the DS18B20 will configure the resolutions per the localdef setting.
			//vDS18B20__Start_ConfigureResolution();

			sHET.sTemp.eState = HETHERM_TEMP_STATE__RUN;

			//no need to scan.
			//sHET.sTemp.eState = HETHERM_TEMP_STATE__START_SCAN;
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


			//not the most efficient, but will do for now
			sHET.sMotorTemp.sLeftHE.f32High = 0.0F;
			sHET.sMotorTemp.sLeftHE.f32Sum = 0.0F;
			sHET.sMotorTemp.sRightHE.f32High = 0.0F;
			sHET.sMotorTemp.sRightHE.f32Sum = 0.0F;
			sHET.sMotorTemp.sBrakeMotor.f32High = 0.0F;
			sHET.sMotorTemp.sBrakeMotor.f32Sum = 0.0F;

			sHET.sMotorTemp.sRightHE.u16TotalCount = 0U;
			sHET.sMotorTemp.sLeftHE.u16TotalCount = 0U;
			sHET.sMotorTemp.sBrakeMotor.u16TotalCount = 0U;

			//do we have any new updates from the DS18B20 subsystem?
			u8Test = u8DS18B20__Is_NewDataAvail();
			if(u8Test == 1U)
			{
				//clear the hghest index as it will be recomputed below
				sHET.sMotorTemp.sLeftHE.u16HighestSensorIndex = 0U;
				sHET.sMotorTemp.sRightHE.u16HighestSensorIndex = 0U;
				sHET.sMotorTemp.sBrakeMotor.u16HighestSensorIndex = 0U;

				//get the number of sensors found
				u16NumSensors = u16DS18B20__Get_NumEnum_Sensors();
				for(u16Counter = 0U; u16Counter <= u16NumSensors; u16Counter++)
				{

					//make sure the sensors belong to us.
					u16User = u162DS18B20__Get_UserIndex(u16Counter);

					//get the temp;
					f32Temp = f32DS18B20__Get_Temperature_DegC(u16Counter);

					if (f32Temp < 2000.0F) {  // throw away unconnected sensor temps.
					//do the left
					    switch(u16User)
					    {
						    case 0x100:

							    //inc the count of sensors on this side
							    sHET.sMotorTemp.sLeftHE.u16TotalCount++;

							    //Compare
							    if(f32Temp > sHET.sMotorTemp.sLeftHE.f32High)
							    {
							        //this sensor value is > than the last highest reading, save it
							        sHET.sMotorTemp.sLeftHE.f32High = f32Temp;
							        sHET.sMotorTemp.sLeftHE.u16HighestSensorIndex = u16Counter;
							        //add to the sum
							        sHET.sMotorTemp.sLeftHE.f32Sum += f32Temp;

							    }
							    else
							    {
							        //this sensor was lower than the last sensor
							    }
							    break;


						    case 0x200:

						        //inc the count of sensors on this side
							    sHET.sMotorTemp.sRightHE.u16TotalCount++;

							    //Compare
							    if(f32Temp > sHET.sMotorTemp.sRightHE.f32High)
							    {
							        //this sensor value is > than the last highest reading, save it
							        sHET.sMotorTemp.sRightHE.f32High = f32Temp;
							        sHET.sMotorTemp.sRightHE.u16HighestSensorIndex = u16Counter;
							        //add to the sum
							        sHET.sMotorTemp.sRightHE.f32Sum += f32Temp;

							    }
							    else
							    {
							        //this sensor was lower than the last sensor
							    }
							    break;

						    case 0x0400:
						        //inc the count of sensors on this side
							    sHET.sMotorTemp.sBrakeMotor.u16TotalCount++;

							    //Compare
							    if(f32Temp > sHET.sMotorTemp.sBrakeMotor.f32High)
							    {
								    //this sensor value is > than the last highest reading, save it
								    sHET.sMotorTemp.sBrakeMotor.f32High = f32Temp;
								    sHET.sMotorTemp.sBrakeMotor.u16HighestSensorIndex = u16Counter;
								    //add to the sum
							        sHET.sMotorTemp.sBrakeMotor.f32Sum += f32Temp;

							    }
							    else
							    {
								    //this sensor was lower than the last sensor
							    }
							    break;

						    default:
							        //do nothing
							    break;
					    }//switch(u16User)
					}// if (f32Temp < 500.0F)
				}//for(u16Counter = 0U; u16Counter < u16NumSensors; u16Counter++)


				//finished with the sensors, now do the math
				//math safety
				if(sHET.sMotorTemp.sLeftHE.u16TotalCount != 0U)
				{
					sHET.sMotorTemp.sLeftHE.f32Sum /= (Lfloat32)sHET.sMotorTemp.sLeftHE.u16TotalCount;
				}
				else
				{
					//stay the same
				}
				if(sHET.sMotorTemp.sRightHE.u16TotalCount != 0U)
				{
					sHET.sMotorTemp.sRightHE.f32Sum /= (Lfloat32)sHET.sMotorTemp.sRightHE.u16TotalCount;
				}
				else
				{
					//stay the same
				}
				if(sHET.sMotorTemp.sBrakeMotor.u16TotalCount != 0U)
				{
					sHET.sMotorTemp.sBrakeMotor.f32Sum /= (Lfloat32)sHET.sMotorTemp.sBrakeMotor.u16TotalCount;
				}
				else
				{
					//stay the same
				}


				//update our internal vars
				sHET.sMotorTemp.sLeftHE.f32HighestTemp = sHET.sMotorTemp.sLeftHE.f32High;
				sHET.sMotorTemp.sRightHE.f32HighestTemp = sHET.sMotorTemp.sRightHE.f32High;
				sHET.sMotorTemp.sBrakeMotor.f32HighestTemp = sHET.sMotorTemp.sBrakeMotor.f32High;

				sHET.sMotorTemp.sLeftHE.f32AverageTemp = sHET.sMotorTemp.sLeftHE.f32Sum;
				sHET.sMotorTemp.sRightHE.f32AverageTemp = sHET.sMotorTemp.sRightHE.f32Sum;
				sHET.sMotorTemp.sBrakeMotor.f32AverageTemp = sHET.sMotorTemp.sBrakeMotor.f32Sum;

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

/***************************************************************************//**
 * @brief
 * Is the thermocouple system available.
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

