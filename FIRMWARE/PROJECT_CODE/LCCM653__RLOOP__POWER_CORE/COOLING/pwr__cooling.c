/**
 * @NOTE
 * http://confluence.rloop.org/display/SD/8.+Control+Cooling+System
 * http://confluence.rloop.org/display/SD/Thermal
 * http://confluence.rloop.org/display/SD/7.+Control+Hover+Engines
 */

#include "../power_core.h"

extern struct _strPWRNODE sPWRNODE;
extern struct _strDS18B20 sDS18B20;

#if C_LOCALDEF__LCCM653__ENABLE_COOLING == 1U

void vPWR_COOLING__Init(void)
{
	Luint8 u8Counter;
	Luint8 u8SolenoidCounter = 0;
	//Init
	sPWRNODE.sCooling.eMainState = COOLING_STATE__RESET;
	sPWRNODE.sCooling.u32100MS_Count = 0U;

	//Config N2HET PIN
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 4U); 		//Brake
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 8U); 		//Hover Engine Pair #1
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 16U);		//Hover Engine Pair #2
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 22U);		//Hover Engine Pair #3
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 23U);		//Hover Engine Pair #4

	//Set PIN STATES
	vPWR_COOLING__Solennoid_TurnAllOff();

	//Init Cooling System
	vPWR_COOLING_EDDY__Init();
	vPWR_COOLING_HOVER__Init();

	//Indexing thermocouples
	//for loop ds18b20 struct
	for(u8Counter = 0; u8Counter < C_LOCALDEF__LCCM644__MAX_DEVICES; u8Counter++)
	{
		//grab 0x3B sensors
		if(sDS18B20.sDevice[u8Counter].u8SerialNumber[0] == 0x3B)
		{
			//Map Thermocouples to Solenoids
			switch(sDS18B20.sDevice[u8Counter].u16UserIndex)
			{
			case C_PWRCORE_HOVERENGINE0_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[0].u8Indexes[0];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE1_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[0].u8Indexes[1];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE2_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[1].u8Indexes[0];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE3_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[1].u8Indexes[1];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE4_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[2].u8Indexes[0];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE5_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[2].u8Indexes[1];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE6_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[3].u8Indexes[0];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_HOVERENGINE7_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[3].u8Indexes[1];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_EDDYBRAKE0_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[0].u8Indexes[0];
				u8SolenoidCounter++;
				break;
			case C_PWRCORE_EDDYBRAKE1_THERMOCOUPLE_USERID:
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[0].u8Indexes[1];
				u8SolenoidCounter++;
				break;
			default:
				//do nothing
				break;
			}
		}
		else
		{
			//do nothing
		}
	}

	//if length of indexed sensors is not 10, then fault
	if(u8SolenoidCounter != 10U)
	{
		//handle fault
	}
}


void vPWR_COOLING__Process(void)
{
	Luint8 u8Counter;
	Lfloat32 f32TempA;
	Lfloat32 f32TempB;

	//main state machine
	switch(sPWRNODE.sCooling.eMainState)
	{
	case COOLING_STATE__RESET:
		//do nothing here
		break;
	case COOLING_STATE__IDLE:
		//in this state we are only getting to here once we have been enabled
		sPWRNODE.sCooling.eMainState = COOLING_HARDWARE__CHECK;
		break;
	case COOLING_HARDWARE__CHECK:
		//in this state, we want to check to see if all our thermocouples are online
		sPWRNODE.sCooling.eMainState = COOLING_STATE__CHECK_TEMPERATURES;
		break;

	case COOLING_STATE__STARTTESTING_01:
		sPWRNODE.sCooling.u32100MS_Count = 0U;
		vPWR_COOLING__Solennoid_TurnOn(4U);
		sPWRNODE.sCooling.eMainState = COOLING_STATE__ENDTESTING;
		break;
	case COOLING_STATE__STARTTESTING_02:
		sPWRNODE.sCooling.u32100MS_Count = 0U;
		vPWR_COOLING__Solennoid_TurnOn(8U);
		sPWRNODE.sCooling.eMainState = COOLING_STATE__ENDTESTING;
		break;
	case COOLING_STATE__STARTTESTING_03:
		sPWRNODE.sCooling.u32100MS_Count = 0U;
		vPWR_COOLING__Solennoid_TurnOn(16U);
		sPWRNODE.sCooling.eMainState = COOLING_STATE__ENDTESTING;
		break;
	case COOLING_STATE__STARTTESTING_04:
		sPWRNODE.sCooling.u32100MS_Count = 0U;
		vPWR_COOLING__Solennoid_TurnOn(22U);
		sPWRNODE.sCooling.eMainState = COOLING_STATE__ENDTESTING;
		break;
	case COOLING_STATE__STARTTESTING_05:
		sPWRNODE.sCooling.u32100MS_Count = 0U;
		vPWR_COOLING__Solennoid_TurnOn(23U);
		sPWRNODE.sCooling.eMainState = COOLING_STATE__ENDTESTING;
		break;
	case COOLING_STATE__ENDTESTING:
		if (sPWRNODE.sCooling.u32100MS_Count < 5)
		{
			//stay here
		}
		else
		{
			vPWR_COOLING__Solennoid_TurnAllOff();
			sPWRNODE.sCooling.eMainState = COOLING_STATE__RESET;
		}
		break;

	case COOLING_STATE__CHECK_TEMPERATURES:
		for (u8Counter = 0; u8Counter < POWER_COOLING__MAX_HOVERENG; u8Counter++)
		{
			f32TempA = f32DS18B20__Get_Temperature_DegC(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8Indexes[0]);
			f32TempB = f32DS18B20__Get_Temperature_DegC(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8Indexes[1]);

			//compare temp
			if (f32TempA > f32TempB)
			{
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature = f32TempA;
			}
			else
			{
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature = f32TempB;
			}

			//update NORMAL, CRITICAL, WARNING states
			//COOLING_STATE__NORMAL,
			//COOLING_STATE__WARNING, T warning: 75C
			if(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature < C_PWRCORE_COOLING_WARNING_THREHOLD)
			{
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState = COOLING_STATE__NORMAL;
			}
			//COOLING_STATE__CRITICAL, T critical: 95C
			else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature > C_PWRCORE_COOLING_WARNING_THREHOLD && sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature < C_PWRCORE_COOLING_CRITICAL_THREHOLD)
			{
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState = COOLING_STATE__WARNING;
			}
			//COOLING_STATE__EMERGENCY T off: 105C
			else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature > C_PWRCORE_COOLING_CRITICAL_THREHOLD && sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature < C_PWRCORE_COOLING_EMERGENCY_THREHOLD)
			{
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState = COOLING_STATE__CRITICAL;
			}
			else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature > C_PWRCORE_COOLING_EMERGENCY_THREHOLD)
			{
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState = COOLING_STATE__EMERGENCY;
			}
			else
			{
				//do nothing
			}
		}

		u8Counter =0;
		for (u8Counter = 0; u8Counter < POWER_COOLING__MAX_EDDYBRAKES; u8Counter++)
		{
			f32DS18B20__Get_Temperature_DegC(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8Indexes[0]);
			f32DS18B20__Get_Temperature_DegC(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8Indexes[1]);

			f32TempA = f32DS18B20__Get_Temperature_DegC(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8Indexes[0]);
			f32TempB = f32DS18B20__Get_Temperature_DegC(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8Indexes[1]);

			//compare temp
			if (f32TempA > f32TempB)
			{
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature = f32TempA;
			}
			else
			{
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature = f32TempB;
			}

			//update NORMAL, CRITICAL, WARNING states
			//COOLING_STATE__NORMAL,
			//COOLING_STATE__WARNING, T warning: 75C
			if(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature < C_PWRCORE_COOLING_WARNING_THREHOLD)
			{
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLING_STATE__NORMAL;
			}
			//COOLING_STATE__CRITICAL, T critical: 95C
			else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature > C_PWRCORE_COOLING_WARNING_THREHOLD && sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature < C_PWRCORE_COOLING_CRITICAL_THREHOLD)
			{
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLING_STATE__WARNING;
			}
			//COOLING_STATE__EMERGENCY T off: 105C
			else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature > C_PWRCORE_COOLING_CRITICAL_THREHOLD && sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature < C_PWRCORE_COOLING_EMERGENCY_THREHOLD)
			{
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLING_STATE__CRITICAL;
			}
			else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature > C_PWRCORE_COOLING_EMERGENCY_THREHOLD)
			{
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLING_STATE__EMERGENCY;
			}
			else
			{
				//do nothing
			}
		}

		sPWRNODE.sCooling.eMainState = COOLING_STATE__PROCESS_TEMPERATURES;
		break;
	case COOLING_STATE__PROCESS_TEMPERATURES:
		//Process Cooling System
		vPWR_COOLING_EDDY__Process();
		vPWR_COOLING_HOVER__Process();
		sPWRNODE.sCooling.eMainState = COOLING_STATE__CHECK_TEMPERATURES;
		break;
	case COOLING_STATE__FAULT:
		//stay here in fault
		vPWR_COOLING__Solennoid_TurnAllOff();
		break;
	default:
		//do nothing
		break;

	}//switch(sPWRNODE.sCooling.eMainState)
}

/***************************************************************************//**
 * @brief
 * Set Solenoid ON
 *
 * @param[in]	N2HET Pin Index
 * @st_funcMD5
 * @st_funcID
 */
void vPWR_COOLING__Solennoid_TurnOn(Luint32 u32PinNumber)
{
	vRM4_N2HET_PINS__Set_PinHigh(N2HET_CHANNEL__1, u32PinNumber);
}

/***************************************************************************//**
 * @brief
 * Set Solenoid OFF
 *
 * @param[in]		N2HET Pin Index
 * @st_funcMD5
 * @st_funcID
 */
void vPWR_COOLING__Solennoid_TurnOff(Luint32 u32PinNumber)
{
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, u32PinNumber);
}

/***************************************************************************//**
 * @brief
 * Set ALL Solenoid OFF
 *
 * @param[in]
 * @st_funcMD5
 * @st_funcID
 */
void vPWR_COOLING__Solennoid_TurnAllOff(void)
{
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, 4U);
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, 8U);
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, 16U);
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, 22U);
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, 23U);
}

//to be called from GS to enable the cooling system as its dangerous
void vPWR_COOLING__Enable(Luint32 u32Value)
{
	if(u32Value == 1U)
	{
		//go from reset to idle.
		sPWRNODE.sCooling.eMainState = COOLING_STATE__IDLE;
	}
	else
	{
		//off
		sPWRNODE.sCooling.eMainState = COOLING_STATE__RESET;
	}

}

//100ms interrupt
void vPWR_COOLING__100MS_ISR(void)
{
	sPWRNODE.sCooling.u32100MS_Count++;
}


#endif //C_LOCALDEF__LCCM653__ENABLE_COOLING
#ifndef C_LOCALDEF__LCCM653__ENABLE_COOLING
	#error
#endif
