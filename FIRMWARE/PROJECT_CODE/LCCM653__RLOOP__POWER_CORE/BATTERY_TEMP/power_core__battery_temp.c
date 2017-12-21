/**
 * @file		POWER_CORE__BATTERY_TEMP.C
 * @brief		Battery Temperature Sensor, Bus Bars and Cells
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.009
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BATTERY_TEMP
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U

extern struct _strPWRNODE sPWRNODE;
extern Luint8 u8AftPack__Default[];
extern Luint8 u8FwdPack__Default[];
extern Luint8 u8FwdPack__Default_Comp2[];


/***************************************************************************//**
 * @brief
 * Init the battery temperature measurement devices
 * 
 * @st_funcMD5		86C09833B06FA3BF0A2875528B492BEA
 * @st_funcID		LCCM653R0.FILE.009.FUNC.001
 */
void vPWRNODE_BATTTEMP__Init(void)
{

	//init the variables
	sPWRNODE.sTemp.f32HighestTemp = 0.0F;
	sPWRNODE.sTemp.f32AverageTemp = 0.0F;
	sPWRNODE.sTemp.u8NewTempAvail = 0U;
	sPWRNODE.sTemp.u16HighestSensorIndex = 0U;
	sPWRNODE.sTemp.u32TempScanCount = 0U;
	sPWRNODE.sTemp.eState = BATT_TEMP_STATE__IDLE;

#ifndef WIN32
	//bring up the 1-wire interface
	vDS2482S__Init();

	//check the result of the status flags for this system and if there is an
	//error decide what to do, either keep going or change to an error state

	//We have a choice here to re-scan each power up or supply the addresses via the network
	//for each sensor. For now we'll search

	//start the temp sensor driver
	vDS18B20__Init();
#endif

	//load up the stored details mem
	vPWRNODE_BATTTEMP_MEM__Init();

}


/***************************************************************************//**
 * @brief
 * Process any battery temp measurement tasks
 * 
 * @st_funcMD5		521412365BC09A1D1CB3B029664377AB
 * @st_funcID		LCCM653R0.FILE.009.FUNC.002
 */
void vPWRNODE_BATTTEMP__Process(void)
{
	Luint8 u8Test;
	Luint16 u16Counter;
	Luint16 u16NumSensors;
	Luint16 u16User;
	Lfloat32 f32High;
	Lfloat32 f32Temp;
	Lfloat32 f32Sum;
	Luint16 u16Mask;
	Luint32 u32Max;
	Luint8 *u8PtrPackMem;
	Luint32 u32Counter;
	Luint16 u16NumWorkingSensors;

#ifndef WIN32
	//process any search tasks
	vDS18B20_ADDX__SearchSM_Process();
#endif

	//process the DS18B20 devices.
	//devices wont start converting until the network search has completed.
	vDS18B20__Process();

	//see if we have any battery temp systems.
	vPWRNODE_BATTTEMP_MEM__Process();

	switch(sPWRNODE.sTemp.eState)
	{
		case BATT_TEMP_STATE__IDLE:
			//just come out of reset

			//depending on mode
			sPWRNODE.sTemp.eState = BATT_TEMP_STATE__LOAD_DEFAULTS;
			//sPWRNODE.sTemp.eState = BATT_TEMP_STATE__START_SCAN;
			break;

		case BATT_TEMP_STATE__LOAD_DEFAULTS:
			//now load the memory
		    //TODO: Code to save to memory is incomplete
			//s16Return = s16PWRNODE_BATTEMP_MEM__Load();

            //load up the memory default arrays

            u32Max = 0U;
            if(sPWRNODE.ePersonality == PWRNODE_TYPE__PACK_A){
                u8PtrPackMem = (Luint8 *)&u8FwdPack__Default_Comp2[0];
            }else if(sPWRNODE.ePersonality == PWRNODE_TYPE__PACK_B){
                u8PtrPackMem = (Luint8 *)&u8AftPack__Default[0];
            }else{
                //todo: handle this case
            }

            //copy into the driver
            for(u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM644__MAX_DEVICES; u32Counter++)
            {
                //Prevent blank entries at the end from incrementing the number of devices counter
                if(u8PtrPackMem[u32Max] != 0U){
                    //upload
                    s16DS18B20_ADDX__Upload_Addx2(u32Counter, u8PtrPackMem[u32Max + 8U],
                                              (Luint8 *)&u8PtrPackMem[u32Max],
                                              u8PtrPackMem[u32Max + 9U], *((Luint16 *)u8PtrPackMem+10));
                }

                //increment the memory addx size
                u32Max += 12U;
            }

            //signal to the device that we have loaded all our avail data.
            vDS18B20_ADDX__Set_SearchComplete();

			//setup the resolution
			sPWRNODE.sTemp.eState = BATT_TEMP_STATE__CONFIGURE_RESOLUTION;
			break;

		case BATT_TEMP_STATE__CONFIGURE_RESOLUTION:

			//if we have loaded, configure the devices resolution
			//This has been implemented in the DS18B20 stack now, so as soon as the sensors are loaded
			//and ScanComplete is set, the DS18B20 will configure the resolutions per the localdef setting.
			//vDS18B20__Start_ConfigureResolution();
		    if(C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP_SEARCH == 1U){
		        sPWRNODE.sTemp.eState = BATT_TEMP_STATE__START_SCAN;
		    }else{
		        sPWRNODE.sTemp.eState = BATT_TEMP_STATE__RUN;
		    }
			break;

		case BATT_TEMP_STATE__START_SCAN:
			//start a search
#ifndef WIN32
			//start the search state machine
			vDS18B20_ADDX__SearchSM_Start();
#endif

			//wait for the scan
			sPWRNODE.sTemp.eState = BATT_TEMP_STATE__WAIT_SCAN;
			break;

		case BATT_TEMP_STATE__WAIT_SCAN:
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
				sPWRNODE.sTemp.eState = BATT_TEMP_STATE__RUN;
			}
			break;

		case BATT_TEMP_STATE__RUN:

			//clear the vars
			f32High = 0.0F;
			f32Sum = 0.0F;
			//do we have any new updates from the DS18B20 subsystem?
			u8Test = u8DS18B20__Is_NewDataAvail();
			if(u8Test == 1U)
			{
				//clear the hghest index as it will be recomputed below
				sPWRNODE.sTemp.u16HighestSensorIndex = 0U;

				//0x2000 onwards is our BMS sensors
				u16Mask = C_PWRCORE__BMS_TEMP_MASK;
				u16Mask <<= 8U;

				//get the number of sensors in the pack
				u16NumSensors = u16DS18B20__Get_NumEnum_Sensors();
				u16NumWorkingSensors = 0U;
				for(u16Counter = 0U; u16Counter < u16NumSensors; u16Counter++)
				{

					//make sure the sensors belong to us.
					u16User = u162DS18B20__Get_UserIndex(u16Counter);

					//make sure they are in our user group
					if((u16User & 0xFF00) != u16Mask)
					{

						//compute the highest
						f32Temp = f32DS18B20__Get_Temperature_DegC(u16Counter);

						if(f32Temp < 126.0F)
						{

							//inc the number of working sensors
							u16NumWorkingSensors ++;

							if(f32Temp > f32High)
							{
								//this sensor value is > than the last higest reading, save it
								f32High = f32Temp;
								sPWRNODE.sTemp.u16HighestSensorIndex = u16Counter;

							}
							else
							{
								//this sensor was lower than the last sensor
							}

							//add to the sum
							f32Sum += f32Temp;

						}
						else
						{

						}


					}
					else
					{
						//not for us, maybe a BMS sensor
					}


				}//for(u16Counter = 0U; u16Counter < u16NumSensors; u16Counter++)


				//divide
				//math safety
				if(u16NumWorkingSensors != 0U)
				{
					f32Sum /= (Lfloat32)u16NumWorkingSensors;
				}
				else
				{
					//stay the same
				}
#if 0
				if(u16NumSensors != 0U)
				{
					f32Sum /= (Lfloat32)u16NumSensors;
				}
				else
				{
					//stay the same
				}

#endif

				//update our internal vars
				sPWRNODE.sTemp.f32HighestTemp = f32High;
				sPWRNODE.sTemp.f32AverageTemp = f32Sum;
				sPWRNODE.sTemp.u8NewTempAvail = 1U;

				//Inc the scan count
				sPWRNODE.sTemp.u32TempScanCount++;

				//done with the new data now
				vDS18B20__Clear_NewDataAvail();
			}
			else
			{
				//no new temp readings yet
			}
			break;

	} //switch(sPWRNODE.sTemp.eState)

}

/***************************************************************************//**
 * @brief
 * Return 1 if we have the temp system avail?
 * 
 * @st_funcMD5		9225B00F2A81F2A0408B558E15D81756
 * @st_funcID		LCCM653R0.FILE.009.FUNC.005
 */
Luint8 u8PWR_BATTTEMP__Is_Avail(void)
{
	Luint8 u8Return;

	if(sPWRNODE.sTemp.eState == BATT_TEMP_STATE__RUN)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}



#endif //C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

