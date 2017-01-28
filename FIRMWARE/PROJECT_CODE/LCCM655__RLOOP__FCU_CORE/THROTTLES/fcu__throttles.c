/**
 * @file		FCU__THROTTLES.C
 * @brief		Throttle Controller
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__THROTTLES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U

//the structure
extern struct _strFCU sFCU;



// throttle command tolerance
#define u16THROTTLE_TOL			0U

// All-engines flag
#define ALL_HES					0U

#define RAMP_DONE				99U

#define THROTTLE_RAMP_TIMER_INTERVAL 100.0F

//xxxxxxxxxxxxxxxx  DUMMY VALUES - TO BE FINALIZED IN FCU  xxxxxxxxxxxxxxxxx
#define HOVER_ENGINE_MINIMUM_SPEED			0U
#define HOVER_ENGINE_MAXIMUM_SPEED			50000U
#define HOVER_ENGINE_STATIC_HOVER_SPEED		20000U
#define HOVER_ENGINE_STANDBY_SPEED			20000U
#define FCU_MODE							STOPPED_LIFTED
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxx  DUMMY VALUES - TO BE SENT BY GROUND STATION  xxxxxxxxxxxxxx
#define GS_COMMAND_MODE						SET_HEX_SPEED
#define GS_COMMAND_UNITS					0U
#define GS_THROTTLE_COMMAND					15000U
#define GS_ENGINE_NUMBER					6U//0U
#define GS_THROTTLE_RAMP_DURATION			3000U
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// last command values
static Luint16 u16LastThrottleSetPoint;
static Luint16 u16LastThrottleCommandValue;
static Luint16 u16InitThrottleCommand;

//locals
Lfloat32 f32FCU_THROTTLE__RPM_To_Volts(Luint16 u16RPM);
Luint16 u16FCU_THROTTLE__Compute_RPM_StepUp(Luint16 u16RPM);
Luint16 u16FCU_THROTTLE__Compute_RPM_StepDown(Luint16 u16RPM);

/***************************************************************************//**
 * @brief
 * Init any variables
 * 
 * @st_funcMD5		653E038AB9977C3CC60554EFD34C1240
 * @st_funcID		LCCM655R0.FILE.006.FUNC.001
 */
void vFCU_THROTTLE__Init(void)
{

	Luint8 u8Counter;

	//init the AMC devices
	vAMC7812__Init();

	//configure dev mode
	sFCU.sThrottle.sDevMode.u32SecurityKey = 0U;
	sFCU.sThrottle.sDevMode.u8Enabled = 0U;

	sFCU.sThrottle.eState = THROTTLE_STATE__IDLE;
	sFCU.sThrottle.u8RunIndex = 0U;

	vFAULTTREE__Init(&sFCU.sThrottle.sFaultFlags);
	vFAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__03);


	//clear some internal vars.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
	{
		sFCU.sThrottle.u16RequestedRPM[u8Counter] = 0U;
		sFCU.sThrottle.eRequestedMode[u8Counter] = THROTTLE_TYPE__STEP;
		sFCU.sThrottle.u16CurrentRPM[u8Counter] = 0U;
		sFCU.sThrottle.u8100ms_Timer[u8Counter] = 0U;
	}

}


/***************************************************************************//**
 * @brief
 * Process any Throttle tasks
 * 
 * @st_funcMD5		137E6542B68678DBE1491CDA5DBCE3AB
 * @st_funcID		LCCM655R0.FILE.006.FUNC.002
 */
void vFCU_THROTTLE__Process(void)
{
	Lfloat32 f32Temp;
	Luint32 u32Test;

	//process the AMC device
	vAMC7812__Process();

	//Now that processing has occurred, check any issues
	u32Test = u32AMC7812__Get_FaultFlags();
	if(u32Test != 0x00000000U)
	{
		//we have a fault, log it
		vFAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__01);
	}
	else
	{
		//fall on
	}

	//hande our state machine
	switch(sFCU.sThrottle.eState)
	{
		case THROTTLE_STATE__IDLE:
			//in idle we do nothing, but protect the HE's from accidential startup
			//by not permitting run mode until we are safe to do so
			break;

		case THROTTLE_STATE__RUN:

			//Clear the not in run flag
			vFAULTTREE__Clear_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__03);


			//do we need to do anything with this throttle
			if(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] != sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex])
			{
				//we have a difference between the current RPM and the requested RPM

				//determine what mode the user wanted
				if(sFCU.sThrottle.eRequestedMode[sFCU.sThrottle.u8RunIndex] == THROTTLE_TYPE__RAMP)
				{

					//Determine to spin up or spin down
					if(sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex] > sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex])
					{
						sFCU.sThrottle.eState = THROTTLE_STATE__RAMP_UP;
					}
					else
					{
						sFCU.sThrottle.eState = THROTTLE_STATE__RAMP_DOWN;
					}

				}
				else
				{
					//default to step mode for all other cases
					sFCU.sThrottle.eState = THROTTLE_STATE__STEP;
				}
			}
			else
			{
				//no need to service this HE, check again later
				sFCU.sThrottle.eState = THROTTLE_STATE__INC_INDEX;
			}
			break;


		case THROTTLE_STATE__STEP:

			//simply supply a step change to the throttle

			//compute the voltage for the corresponding RPM
			f32Temp = f32FCU_THROTTLE__RPM_To_Volts(sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex]);

			//set DAC
			vAMC7182__DAC_SetVoltage(sFCU.sThrottle.u8RunIndex, f32Temp);

			//update the actual RPM based on the change
			sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] = sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex];

			//move onto the next channel to scan
			sFCU.sThrottle.eState = THROTTLE_STATE__INC_INDEX;
			break;

		case THROTTLE_STATE__RAMP_UP:
			//compute the ramp change to the throttle

			//only do if we have seen a timer
			if(sFCU.sThrottle.u8100ms_Timer[sFCU.sThrottle.u8RunIndex] == 1U)
			{
				//increment the current RPM
				sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] = u16FCU_THROTTLE__Compute_RPM_StepUp(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex]);

				//limit
				if(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] > sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex])
				{
					//set to max
					sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] = sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex];
				}
				else
				{
					//ok, fall on
				}

				//compute the voltage for the corresponding RPM
				f32Temp = f32FCU_THROTTLE__RPM_To_Volts(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex]);

				//set DAC
				vAMC7182__DAC_SetVoltage(sFCU.sThrottle.u8RunIndex, f32Temp);

				//clear the flag
				sFCU.sThrottle.u8100ms_Timer[sFCU.sThrottle.u8RunIndex] = 0U;
			}
			else
			{
				//come back around again
			}

			sFCU.sThrottle.eState = THROTTLE_STATE__INC_INDEX;
			break;

		case THROTTLE_STATE__RAMP_DOWN:

			//only do if we have seen a timer
			if(sFCU.sThrottle.u8100ms_Timer[sFCU.sThrottle.u8RunIndex] == 1U)
			{
				//increment the current RPM
				sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] = u16FCU_THROTTLE__Compute_RPM_StepDown(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex]);

				//limit
				if(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] < sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex])
				{
					//set to max
					sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex] = sFCU.sThrottle.u16RequestedRPM[sFCU.sThrottle.u8RunIndex];
				}
				else
				{
					//ok, fall on
				}

				//compute the voltage for the corresponding RPM
				f32Temp = f32FCU_THROTTLE__RPM_To_Volts(sFCU.sThrottle.u16CurrentRPM[sFCU.sThrottle.u8RunIndex]);

				//set DAC
				vAMC7182__DAC_SetVoltage(sFCU.sThrottle.u8RunIndex, f32Temp);

				//clear the flag
				sFCU.sThrottle.u8100ms_Timer[sFCU.sThrottle.u8RunIndex] = 0U;
			}
			else
			{
				//come back around again
			}

			sFCU.sThrottle.eState = THROTTLE_STATE__INC_INDEX;
			break;

		case THROTTLE_STATE__INC_INDEX:
			//increment to the next index
			if(sFCU.sThrottle.u8RunIndex < (C_FCU__NUM_HOVER_ENGINES - 1))
			{
				sFCU.sThrottle.u8RunIndex++;
			}
			else
			{
				//roll around
				sFCU.sThrottle.u8RunIndex = 0U;
			}

			//see what else needs doing
			sFCU.sThrottle.eState = THROTTLE_STATE__RUN;

			break;

		case THROTTLE_STATE__ERROR:
			//some issue
			break;

		default:
			//log the fault
			break;


	}//switch(sFCU.sThrottle.eState)

}


/***************************************************************************//**
 * @brief
 * Compute the step to the next RPM increment
 * 
 * @param[in]		u16RPM				RPM
 * @st_funcMD5		55FA32EE2926B39A2247666B10DA85EC
 * @st_funcID		LCCM655R0.FILE.006.FUNC.003
 */
Luint16 u16FCU_THROTTLE__Compute_RPM_StepUp(Luint16 u16RPM)
{

	Luint16 u16Return;

	u16Return = u16RPM;

	//add the step
	u16Return += 200U;

	return u16Return;


}


/***************************************************************************//**
 * @brief
 * Compute the step to the next RPM Decrement
 * 
 * @param[in]		u16RPM				Current RPM
 * @st_funcMD5		BABD3902310B5EA38BC850114E39C924
 * @st_funcID		LCCM655R0.FILE.006.FUNC.004
 */
Luint16 u16FCU_THROTTLE__Compute_RPM_StepDown(Luint16 u16RPM)
{

	Luint16 u16Return;

	u16Return = u16RPM;

	//protect the math
	if(u16Return >= 200U)
	{
		//sub the step
		u16Return -= 200U;
	}
	else
	{
		u16Return = 0U;
	}


	return u16Return;
}


/***************************************************************************//**
 * @brief
 * Enable the throttle system into RUN mode. This is needed
 * To be done via flight control to prevent unintended HE startup
 * 
 * @st_funcMD5		49C9345E807752C9DD7876859EDD2F73
 * @st_funcID		LCCM655R0.FILE.006.FUNC.005
 */
void vFCU_THROTTLE__Enable_Run(void)
{
	//protect the run state by only changing if we are idle.
	if(sFCU.sThrottle.eState == THROTTLE_STATE__IDLE)
	{
		sFCU.sThrottle.eState = THROTTLE_STATE__RUN;
	}
	else
	{
		//unable to change mode here.
	}
}

/***************************************************************************//**
 * @brief
 * Application layer to enable throttles to be set
 * 
 * @param[in]		eRampType				The type of throttle ramp
 * @param[in]		u16RPM					Required RPM
 * @param[in]		u8EngineIndex			HE Index, 8 = all HE's
 * @st_funcMD5		91F8E606B73C320B38326AF4D5A62257
 * @st_funcID		LCCM655R0.FILE.006.FUNC.006
 */
void vFCU_THROTTLE__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, E_THROTTLE_CTRL_T eRampType)
{
	Luint8 u8Counter;

	//safety
	if(u8EngineIndex < C_FCU__NUM_HOVER_ENGINES)
	{
		//just set the RPM
		sFCU.sThrottle.u16RequestedRPM[u8EngineIndex] = u16RPM;
		sFCU.sThrottle.eRequestedMode[u8EngineIndex] = eRampType;
	}
	else if(u8EngineIndex == C_FCU__NUM_HOVER_ENGINES)
	{
		//set each engine
		for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
		{
			sFCU.sThrottle.u16RequestedRPM[u8Counter] = u16RPM;
			sFCU.sThrottle.eRequestedMode[u8Counter] = eRampType;
		}
	}
	else
	{
		//log the error.
		vFAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__02);

	}

}

//
/***************************************************************************//**
 * @brief
 * Compute volts to DAC based on RPM for a single engine only
 * 
 * @param[in]		u16RPM				Desired RPM
 * @return			DAC Volts
 * @st_funcMD5		104E1A0088369417D74427715DC40585
 * @st_funcID		LCCM655R0.FILE.006.FUNC.007
 */
Lfloat32 f32FCU_THROTTLE__RPM_To_Volts(Luint16 u16RPM)
{
	Lfloat32 f32Temp;

	//example 0.5 to 4.5v = 0 to 2000 rpm.
	//todo after hardware rest.

	f32Temp = (Lfloat32)u16RPM;

	//scale to volts, range of 1-4V
	f32Temp *= 0.002F;

	//add zero offset
	//for now add in 0.95V, actually 1.0v on the controller, but we don't want to have any issues
	f32Temp += 0.95F;


	return f32Temp;

}

/***************************************************************************//**
 * @brief
 * Timer function, returns after 100 milliseconds
 * 
 * @st_funcMD5		BD90C8C26FABACCFB1ECCA3E4C0460FD
 * @st_funcID		LCCM655R0.FILE.006.FUNC.008
 */
void vFCU_THROTTLE__100MS_ISR(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
	{
		sFCU.sThrottle.u8100ms_Timer[u8Counter] = 1U;
	}

}


#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLE
#ifndef C_LOCALDEF__LCCM655__ENABLE_THROTTLE
	#error
#endif
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

