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

/*
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
*/

// last command values
//static Luint16 u16LastThrottleSetPoint;
//static Luint16 u16LastThrottleCommandValue;
//static Luint16 u16InitThrottleCommand;

//locals
Lfloat32 f32FCU_THROTTLE__RPM_To_Volts(Luint16 u16RPM);
Luint16 u16FCU_THROTTLE__Compute_RPM_StepUp(Luint16 u16RPM);
Luint16 u16FCU_THROTTLE__Compute_RPM_StepDown(Luint16 u16RPM);

/***************************************************************************//**
 * @brief
 * Init any variables
 * 
 * @st_funcMD5		3D83D3CBE94E074C73347E324EE431FB
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
	sFCU.sThrottle.u32KeepAlive = 0U;

	vSIL3_FAULTTREE__Init(&sFCU.sThrottle.sFaultFlags);
	vSIL3_FAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__03);


	//clear some internal vars.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
	{
		//set our min safety voltage.
		vAMC7182__DAC_SetVoltage(u8Counter, 0.95F * 1.15F);

		sFCU.sThrottle.u16RequestedRPM[u8Counter] = 0U;
		sFCU.sThrottle.eRequestedMode[u8Counter] = THROTTLE_TYPE__STEP;
		sFCU.sThrottle.u16CurrentRPM[u8Counter] = 0U;
		sFCU.sThrottle.f32CurrentVolts[u8Counter] = 0.0F;
		sFCU.sThrottle.u8100ms_Timer[u8Counter] = 0U;
	}

	//set to 1 to prevent clearing the throttle.
	sFCU.sThrottle.u8KeepAliveActive = 1U;

}


/***************************************************************************//**
 * @brief
 * Process any Throttle tasks
 * 
 * @st_funcMD5		519F9282320179D5EA89621405D7BACA
 * @st_funcID		LCCM655R0.FILE.006.FUNC.002
 */
void vFCU_THROTTLE__Process(void)
{
	Lfloat32 f32Temp;
	Luint32 u32Test;
	Luint8 u8Counter;

	//process the AMC device
	vAMC7812__Process();

	//Now that processing has occurred, check any issues
	u32Test = u32AMC7812__Get_FaultFlags();
	if(u32Test != 0x00000000U)
	{
		//we have a fault, log it
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__01);
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
			vSIL3_FAULTTREE__Clear_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__03);


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
			sFCU.sThrottle.f32CurrentVolts[sFCU.sThrottle.u8RunIndex] = f32Temp;
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
				sFCU.sThrottle.f32CurrentVolts[sFCU.sThrottle.u8RunIndex] = f32Temp;
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
				sFCU.sThrottle.f32CurrentVolts[sFCU.sThrottle.u8RunIndex] = f32Temp;
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
			sFCU.sThrottle.eState = THROTTLE_STATE__CHECK_KEEPALIVE;

			break;

		case THROTTLE_STATE__CHECK_KEEPALIVE:

			//30 seconds
			if((sFCU.sThrottle.u32KeepAlive >= 30U) && (sFCU.sThrottle.u8KeepAliveActive == 0U))
			{
				//clear all
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					//set to zero and trip out.
					vAMC7182__DAC_SetVoltage(sFCU.sThrottle.u8RunIndex, 0.0F);
				}

				sFCU.sThrottle.u8KeepAliveActive = 1U;
			}
			else
			{
				//safe
			}

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
	if(u16Return >= 20U)
	{
		//sub the step
		u16Return -= 20U;
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
 * @st_funcMD5		67F20EE1B480E01FC261370E4AD8190C
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

		//clear the keepalive
		sFCU.sThrottle.u32KeepAlive = 0U;
		sFCU.sThrottle.u8KeepAliveActive = 0U;

	}
	else if(u8EngineIndex == C_FCU__NUM_HOVER_ENGINES)
	{
		//set each engine
		for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
		{
			sFCU.sThrottle.u16RequestedRPM[u8Counter] = u16RPM;
			sFCU.sThrottle.eRequestedMode[u8Counter] = eRampType;
		}

		//clear the keepalive
		sFCU.sThrottle.u32KeepAlive = 0U;
		if(u16RPM == 0U)
		{
			//prevent clearing.
			sFCU.sThrottle.u8KeepAliveActive = 1U;
		}
		else
		{
			sFCU.sThrottle.u8KeepAliveActive = 0U;
		}

	}
	else
	{
		//log the error.
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sThrottle.sFaultFlags, C_LCCM655__THROTTLES__FAULT_INDEX__02);

	}

}

//
/***************************************************************************//**
 * @brief
 * Compute volts to DAC based on RPM for a single engine only
 * 
 * @param[in]		u16RPM				Desired RPM
 * @return			DAC Volts
 * @st_funcMD5		54F536DCC5134D617078F6E61B6D2FAB
 * @st_funcID		LCCM655R0.FILE.006.FUNC.007
 */
Lfloat32 f32FCU_THROTTLE__RPM_To_Volts(Luint16 u16RPM)
{
	Lfloat32 f32Temp;

	//example 0.5 to 4.5v = 0 to 2000 rpm.
	f32Temp = (Lfloat32)u16RPM;

	//scale to volts, range of 1-4V
	f32Temp *= 0.004F;

	//add zero offset
	//for now add in 0.95V, actually 1.0v on the controller, but we don't want to have any issues
	f32Temp += (0.95F * 1.15F);

	//return
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

	//inc the keepalive timer.
	sFCU.sThrottle.u32KeepAlive += 1U;

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

