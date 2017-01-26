/**
 * @NOTE
 * http://confluence.rloop.org/display/SD/8.+Control+Cooling+System
 * http://confluence.rloop.org/display/SD/Thermal
 * http://confluence.rloop.org/display/SD/7.+Control+Hover+Engines
 */

#include "../power_core.h"

extern struct _strPWRNODE sPWRNODE;

#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U

void vPWR_COOLING__Init(void)
{
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
}


void vPWR_COOLING__Process(void)
{
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
	case COOLING_STATE__CHECK_TEMPERATURES:
		//TODO check temperatures
		//UPDATE Cooling System Status
			//Hover Engines:
				//COOLING_STATE__NORMAL,
				//COOLING_STATE__WARNING, T warning: 75C
				//COOLING_STATE__CRITICAL, T critical: 95C
				//COOLING_STATE__EMERGENCY T off: 105C
			//Eddy Brakes:
				//TODO
		sPWRNODE.sCooling.eMainState = COOLING_STATE__PROCESS_TEMPERATURES;
		break;
	case COOLING_STATE__PROCESS_TEMPERATURES:
		//Process Cooling System
		vPWR_COOLING_EDDY__Process();		//TODO need switch case statement in process function to handle NORMAL, WANRING, CRITICAL, CONTINUOUS statuses
		vPWR_COOLING_HOVER__Process();		//TODO need switch case statement in process function to handle NORMAL, WANRING, CRITICAL, CONTINUOUS statuses
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
		sPWRNODE.sCooling.eMainState = COOLING_STATE__IDLE;
	}

}

//100ms interrupt
void vPWR_COOLING__100MS_ISR(void)
{
	sPWRNODE.sCooling.u32100MS_Count++;
}

#endif //C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
#ifndef C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
	#error
#endif
