/**
 * @file		FCU__FCTL__MAIN_SM.C
 * @brief		Main state machine for the flight control unit
 * @author		Lachlan Grogan, Marek Gutt-Mostowy
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
 * @addtogroup FCU__FCTL__MAIN_SM
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAINSM == 1U

//the structure
extern struct _strFCU sFCU;

//TODO: need the following function implemented

//u32FCU_FCTL_NAV__PodSpeed();
//u32FCU_FCTL_NAV__GetFrontPos();
//u32FCU_FCTL_NAV__GetRearPos();
//u32FCU_FCTL_NAV__PodSpeed();
//u32FCU_FCTL_LASERORIENT__Get_Z_Pos()
//u32LandingGearMLPLeftAftValue = u32FCU_LGU__Get_MLP_Value(Luint8 u8Counter);

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		5224534176289DBD9FF1B39936308C7E
 * @st_funcID		LCCM655R0.FILE.020.FUNC.001
 */
void vFCU_FCTL_MAINSM__Init(void)
{
	sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__RESET;

}


/***************************************************************************//**
 * @brief
 * Process the main state machine
 * 
 * @st_funcMD5		2C23D1564E9845C3BED5E00B06C0BBB3
 * @st_funcID		LCCM655R0.FILE.020.FUNC.002
 */
void vFCU_FCTL_MAINSM__Process(void)
{
	Luint8 u8Counter;
	Luint8 u8Test;
	Luint8 u8TestsSuccesful;
	Lint32 u32Accelmmss;
	Luint32 u32PodSpeed;
	Luint8 ePusherState;
	Luint32 u32PodRearPos;

	//handle the state machine.
	switch(sFCU.sStateMachine.eMissionPhase)
	{

		case MISSION_PHASE__RESET:
			//we have just come out of reset here.
			//init our rPod specific systems

			#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U
				vFCU_PODHEALTH__Init();
			#endif

			//init the auto sequence
			vFCU_MAINSM_AUTO__Init();

			//pusher
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vFCU_PUSHER__Init();
			#endif

			//laser contrast sensors
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
				vFCU_LASERCONT__Init();
			#endif

			//laser distance
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
				vFCU_LASERDIST__Init();
			#endif

			//init the brake systems
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vFCU_BRAKES__Init();
			#endif

			//Init the throttles
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
				vFCU_THROTTLE__Init();
			#endif

			//init the ASI RS485 interface
			#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
				vFCU_ASI__Init();
			#endif

			//init the acclerometer system
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL__Init();
			#endif

			//laser opto's
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
				vFCU_LASEROPTO__Init();
			#endif

			//PiComms Layer
			#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
				vFCU_PICOMMS__Init();
			#endif

			//finally init the flight controller
			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
				vFCU_FCTL__Init();
			#endif

			//start the LGU interface
			#if C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM == 1U
				vFCU_LGU__Init();
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_GEOM == 1U
				vFCU_GEOM__Init();
			#endif //C_LOCALDEF__LCCM655__ENABLE_GEOM

			//put the flight computer into startup mode now that everything has been initted.
			sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__DEBUG; //MISSION_PHASE__TEST;

			break;

#if 0

		case MISSION_PHASE__TEST:

			//in this mode we are performing tests of all of the sensors and motors pl an auto-sequence

			//see if we have an auto sequence abort
			u8Test = u8FCU_MAINSM_AUTO__Is_Abort();
			if(u8Test == 1U)
			{
				//move to RESET if tests aborted
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__RESET;
			}
			else
			{
				u8Test = u8FCU_MAINSM_AUTO__Is_Busy();
				if(u8Test == 1U)
				{
					//stay in state, we are still busy
				}
				else
				{
					//not busy and not abort, set flag indicating tests succesful
					u8TestsSuccesful = 1U;
				}
			}

			u32Accelmmss = u32FCU_FCTL_NAV__Get_Accel_mmss();

			if (u32Accelmmss > C_FCU__NAV_MIN_PUSHER_ACCEL)
			{
				sFCU.sStateMachine.EnableAccelCounter = 1U;
			}
			else
			{
				sFCU.sStateMachine.EnableAccelCounter = 0U;
			}

			//Get Pod Speed
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

			if ((u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY) && (sFCU.sStateMachine.eGSCommands == MAINSM_GS_ENTER_PRE_RUN_PHASE))
			{

					sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__PRE_RUN;
					sFCU.sStateMachine.eGSCommands = MAINSM_GS_NO_CMD;
			}
			else
			{

				if((sFCU.sStateMachine.AccelCounter > C_FCU__MAINSM_PUSHER_START_CONFIRM_DELAY) || u32PodSpeed > C_FCU__NAV_MIN_PUSHER_SPEED)
				{
					sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__PUSHER_INTERLOCK;
					sFCU.sStateMachine.EnableAccelCounter = 0U;
				}
				else
				{
					sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__TEST;
				}
			}
			break;

		case MISSION_PHASE__PRE_RUN:

			//Transition to Pusher Interlock Phase based on the acceleration
			//Not sure about how to call the right accelerometer and whether it indicates the right axis

			u32Accelmmss = u32FCU_FCTL_NAV__Get_Accel_mmss();

			if (u32Accelmmss > C_FCU__NAV_MIN_PUSHER_ACCEL)
			{
				sFCU.sStateMachine.EnableAccelCounter = 1U;
			}
			else
			{
				sFCU.sStateMachine.EnableAccelCounter = 0U;
			}

			//Get Pod Speed
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

			if((sFCU.sStateMachine.AccelCounter > C_FCU__MAINSM_PUSHER_START_CONFIRM_DELAY) || u32PodSpeed > C_FCU__NAV_MIN_PUSHER_SPEED)
			{
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__PUSHER_INTERLOCK;
				sFCU.sStateMachine.EnableAccelCounter = 0U;
			}
			else
			{
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__PRE_RUN;
			}

			break;


		case MISSION_PHASE__PUSHER_INTERLOCK:

			//transition to FLIGHT mode if the pod has reached the min_x_pos AND 1 second elapsed from the disconnection from the pusher
			sFCU.sStateMachine.PusherPhaseCounter = 0U;
			ePusherState = eFCU_PUSHER__Get_PusherState();
			u32PodRearPos = u32FCU_FCTL_NAV__GetRearPos();

			// Check if counter for pusher pin release should be enabled
			if(ePusherState == 0U)
			{
				//Enable the counter
				sFCU.sStateMachine.EnablePusherCounter == 1U;
			}
			else
			{
				sFCU.sStateMachine.EnablePusherCounter == 0U;
			}

			// Check if counter for miserable stop should be enabled
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
			{
				//Enable the counter
				sFCU.sStateMachine.EnableMiserableStopCounter == 1U;
			}
			else
			{
				sFCU.sStateMachine.EnableMiserableStopCounter == 0U;
			}

			if((((u32PodRearPos > C_FCU__NAV_POD_MIN_X_POS) || u8FCU_FCTL_NAV__IsInFailure() == 1U) && (sFCU.sStateMachine.PusherCounter >= C_FCU__MAINSM_PUSHER_RELEASE_DELAY)) || sFCU.sStateMachine.PusherPhaseCounter >= C_FCU__MAINSM_MAX_PUSHER_INTERLOCK_PHASE_DURATION)
			{
				//Switch to Mission Phase Flight
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__FLIGHT;
				//Disable the counter
				sFCU.sStateMachine.EnablePusherCounter = 0U;
			}
			else
			{
				//Both Timers need to elapse in order to transition to POST RUN PHASE
				if ((sFCU.sStateMachine.MiserableStopCounter > C_FCU__NAV_MISERABLE_STOP_CONFIRM_DELAY) && (sFCU.sStateMachine.PusherPhaseCounter > C_FCU__MAINSM_MAX_PUSHER_INTERLOCK_PHASE_DURATION))
				{
					//Switch to Mission Phase Flight
					sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__POST_RUN;
					//Disable the counter
					sFCU.sStateMachine.EnableMiserableStopCounter = 0U;
				}
				else
				{
					sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__PUSHER_INTERLOCK;
				}
			}

			break;


		case MISSION_PHASE__FLIGHT:
			//this is the flight mode controller

			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
				vFCU_FCTL__Process();
			#endif

			vFCU_FLIGHTCTL_BRAKEPID__Init();

			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)

			{
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__POST_RUN;
			}

			else
			{
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__FLIGHT;
			}

			//Disable the counter
			sFCU.sStateMachine.EnablePusherCounter == 0U;

			break;

		case MISSION_PHASE__POST_RUN:
			//post run state

			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			//void vFCU_FCTL_MAINSM__EnterPreRun_Phase(Luint32 u32Key);

			if((u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY) && (sFCU.sStateMachine.eGSCommands == MAINSM_GS_ENTER_PRE_RUN_PHASE))
			{
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__PRE_RUN;
				sFCU.sStateMachine.eGSCommands = MAINSM_GS_NO_CMD;
			}
			else
			{
				sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__POST_RUN;
			}
			break;
#endif

		case MISSION_PHASE__DEBUG:

			break;

		default:
			//should not get here
			break;

	}//switch(sFCU.eRunState)

	//always process these items after we have been initted
	if(sFCU.sStateMachine.eMissionPhase > MISSION_PHASE__RESET)
	{
		#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U
			vFCU_PODHEALTH__Process();
		#endif

		//LG
		vFCU_FCTL__Process();

		//process the SC16IS interface always
		#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
			{
				vSC16__Process(u8Counter);
			}
		#endif

		// process the AMC7812
		// process the throttles
		#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
			vFCU_THROTTLE__Process();
			vAMC7812__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
			vFCU_LASEROPTO__Process();
		#endif

		//laser orientation
		#if C_LOCALDEF__LCCM655__ENABLE_ORIENTATION == 1U
			vFCU_LASER_ORIENTATION__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
			vFCU_LASERCONT__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
			vFCU_LASERDIST__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
			vFCU_PUSHER__Process();
		#endif

		//process the brakes.
		#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
			vFCU_BRAKES__Process();
		#endif

		//process the accel channels
		#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
			vFCU_ACCEL__Process();
		#endif

		//ASI RS485 interface
		#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
			vFCU_ASI__Process();
		#endif

		//process any Pi Comms
		#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
			vFCU_PICOMMS__Process();
		#endif

		//start the LGU interface
		#if C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM == 1U
			vFCU_LGU__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_GEOM == 1U
			vFCU_GEOM__Process();
		#endif
		//Start the Hover Engine Control
		#if C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL == 1U
			vFCU_FCTL_HOVERENGINES__Process();
		#endif

		//TODO: NOT MENTIONED ANYWHERE ELSE
		//process auto-sequence control
		//vFCU_FCTL_MAINSM_AUTO__Process();

		//Update operating states
#if 0
		sFCU.sStateMachine.sOpStates.u8Unlifted = u8FCU_FCTL_MAINSM__CheckIfUnlifted();

		sFCU.sStateMachine.sOpStates.u8Lifted = u8FCU_FCTL_MAINSM__CheckIfLifted();

		sFCU.sStateMachine.sOpStates.u8StaticHovering = u8FCU_FCTL_MAINSM__CheckIfHoveringStatically();

		sFCU.sStateMachine.sOpStates.u8ReadyForPush = u8FCU_FCTL_MAINSM__CheckIfReadyForPush();

		sFCU.sStateMachine.sOpStates.u8Pushing = u8FCU_FCTL_MAINSM__CheckIfPushing();

		sFCU.sStateMachine.sOpStates.u8Coasting = u8FCU_FCTL_MAINSM__CheckIfCoasting();

		sFCU.sStateMachine.sOpStates.u8Braking = u8FCU_FCTL_MAINSM__CheckIfBraking();

		sFCU.sStateMachine.sOpStates.u8CtlEmergBraking = u8FCU_FCTL_MAINSM__CheckIfControlledBraking();
#endif
	}
	else
	{
		//do nothing.
	}


}


void vFCU_FCTL_MAINSM__10MS_ISR(void)
{
	//Enable/Disable Counter
   if (sFCU.sStateMachine.EnableAccelCounter == 1U)
   {
        sFCU.sStateMachine.AccelCounter++;
   }
   else
   {
		sFCU.sStateMachine.AccelCounter = 0U;
   }
}

void vFCU_FCTL_MAINSM__100MS_ISR(void)
{
	//Enable/Disable Counter
   if (sFCU.sStateMachine.EnablePusherCounter == 1U)
   {
        sFCU.sStateMachine.PusherCounter++;
   }
   else
   {
       sFCU.sStateMachine.PusherCounter = 0U;
   }
}

void vFCU_FCTL_MAINSM__PUSHER_PHASE_COUNTER_100MS_ISR(void)
	{
		sFCU.sStateMachine.PusherPhaseCounter++;
	}


void vFCU_FCTL_MAINSM__MISERABLE_STOP_100MS_ISR(void)
{
	//Enable/Disable Counter
   if (sFCU.sStateMachine.EnableMiserableStopCounter == 1U)
   {
        sFCU.sStateMachine.MiserableStopCounter++;
   }
   else
   {
       sFCU.sStateMachine.MiserableStopCounter = 0U;
   }
}


#if 0
//allows us to enter pre-run phase from ethernet
void vFCU_FCTL_MAINSM__EnterPreRun_Phase()
{
	Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

	if (((sFCU.sStateMachine.eMissionPhase == MISSION_PHASE__TEST && sFCU.sStateMachine.sOpStates.u8Lifted ) || sFCU.sStateMachine.eMissionPhase == MISSION_PHASE__POST_RUN) && (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
	{
		sFCU.sStateMachine.eGSCommands = MAINSM_GS_ENTER_PRE_RUN_PHASE;
	}
	else
	{
		//do nothing
	}
}





E_FCU__MISSION_PHASE_T eFCU_FCTL_MAIN_SM__GetCurrentMissionPhase()
{
	return sFCU.sStateMachine.eMissionPhase;
}

/** OPERATING STATES */


Luint8 u8FCU_FCTL_MAINSM__CheckIfUnlifted(void)
{

	//Determine if Lifted

	Luint32 u32PodZPos = u32FCU_FCTL_LASERORIENT__Get_Z_Pos();
	Luint8 u8Test;

	if(u32PodZPos < C_FCU__LASERORIENT_MAX_UNLIFTED_HEIGHT)
	{
		u8Test = 0U;
	}
	else
	{
		u8Test = 1U;
	}

	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__CheckIfLifted(void)
{
	//Determine if Unlifted

	Luint32	u32PodZPos = u32FCU_FCTL_LASERORIENT__Get_Z_Pos();
	Luint8 u8Test;

	if(u32PodZPos > C_FCU__LASERORIENT_MIN_LIFTED_HEIGHT)
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}


Luint8 u8FCU_FCTL_MAINSM__CheckIfHoveringStatically(void)
{
	//Determine if Hovering Statically

	Luint8 u8Test;
	if(sFCU.sHoverEngines.eState == HOVERENGINES_STATE__HOVERING)
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__CheckIfReadyForPush(void)
{
	//Determine if Ready for Push

	Luint8 u8Test;
	//Get Pod Current Z Position
	Luint32 u32PodZPos = u32FCU_FCTL_LASERORIENT__Get_Z_Pos();
	//Get Current Pod Speed
	Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

	//Get values on checking the conditions for Pusher Interlock
	//Get Pusher Interlock Switch 1 Status
	Luint8 u8PusherSwitch1 = u8FCU_PUSHER__Get_Switch(0);
	//Get Pusher Interlock Switch 2 Status
	Luint8 u8PusherSwitch2 = u8FCU_PUSHER__Get_Switch(1);

	//Check if we are connected to the pusher, speed is below standby, the height makes sense to be pushed + each of our landing gear units is retracted
	if((u32PodZPos > C_FCU__LASERORIENT_MIN_RUN_MODE_HEIGHT) &&  (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY) && (u8PusherSwitch1 == 1U) && (u8PusherSwitch2 == 1U) && (eFCU_FCTL_LIFTMECH__Get_State() == LIFT_MECH_STATE__RETRACTED))
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__CheckIfPushing(void)
{
	Luint8 u8Test;
	//Get Pusher Interlock Switch 1 Status
	Luint8 u8PusherSwitch1 = u8FCU_PUSHER__Get_Switch(0);
	//Get Pusher Interlock Switch 2 Status
	Luint8 u8PusherSwitch2 = u8FCU_PUSHER__Get_Switch(1);
	//Get Pod Speed
	Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

	//Determine if in Pushing State
	if(u32PodSpeed > C_FCU__NAV_MIN_PUSHER_SPEED && (u8PusherSwitch1 == 1U) && (u8PusherSwitch2 == 1U))
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__CheckIfCoasting(void)
{
	Luint8 u8Test;
	//Get Pusher Interlock Switch 1 Status
	Luint8 u8PusherSwitch1 = u8FCU_PUSHER__Get_Switch(0);
	//Get Pusher Interlock Switch 2 Status
	Luint8 u8PusherSwitch2 = u8FCU_PUSHER__Get_Switch(1);
	//Get Pod Speed
	Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
	//
	if(u32PodSpeed && (u8PusherSwitch1 == 0U) && (u8PusherSwitch2 == 0U) && (eFCU_FCTL_EDDY_BRAKES__Get_State() == EDDY_BRAKES_STATE__RETRACTED))
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__CheckIfBraking(void)
{
	Luint8 u8Test;
	if(eFCU_FCTL_EDDY_BRAKES__Get_State() == EDDY_BRAKES_STATE__BRAKING)
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__CheckIfControlledBraking(void)
{
	Luint8 u8Test;
	if(eFCU_FCTL_EDDY_BRAKES__Get_State() == EDDY_BRAKES_STATE__CONTROLLED_BRAKING)
	{
		u8Test = 1U;
	}
	else
	{
		u8Test = 0U;
	}
	return u8Test;
}

Luint8 u8FCU_FCTL_MAINSM__LossOfComm(void)
{
	Luint8 u8LossOfComm;
	if (sFCU.sUDPDiag.u32_10MS_GS_COMM_Timer > 200U)
	{
		u8LossOfComm = 1U;
	}
	else
	{
		u8LossOfComm = 0U;
	}
	return u8LossOfComm;
}

#endif //C_LOCALDEF__LCCM655__ENABLE_MAINSM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAINSM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

