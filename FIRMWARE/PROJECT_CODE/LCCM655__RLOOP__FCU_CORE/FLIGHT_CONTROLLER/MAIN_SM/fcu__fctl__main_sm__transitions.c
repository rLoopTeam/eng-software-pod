/**
* @file		FCU__FCTL__MAIN_SM__TRANSITIONS.C
* @brief		Main state machine transitions for the flight control unit
* @author		Ryan Adams
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
//handle the main state machine transition cases

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;


////////////////////////////////////////////////////////////////////
//  Pod transition and command guard functions
/////////////////////////////////////////////////////////////////////

Luint8 u8FCU_FCTL_MAINSM___IsPodInitComplete(void)
{
	return sFCU.eInitStates == INIT_STATE__RUN;
}

Luint8 armed_wait_checks_ok(void)
{
	// @todo: implement
	return 0U;
}

Luint8 drive_checks_ok(void)
{
	// @todo: implement
	return 0U;
}

Luint8 flight_prep_checks_ok(void)
{
	// @todo: implement
	return 0U;
}

Luint8 flight_readiness_checks_ok(void)
{
	// @todo: implement
	return 0U;
}

Luint8 u8FCU_FCTL_MAINSM__IsAccelConfirmed(void)
{
	// Note: Having this method allows us to change how we confirm acceleration without having to change the state machine
	return u8FCU_ACCEL_THRESH__Is_Accel_Threshold_Met();
}

Luint8 u8FCU_FCTL_MAINSM__IsDecelConfirmed(void)
{
	// Note: Having this method allows us to change how we confirm acceleration without having to change the state machine
	return u8FCU_ACCEL_THRESH__Is_Decel_Threshold_Met();
}

Luint8 u8FCU_FCTL_MAINSM__IsPusherSeparationConfirmed(void)
{
	#ifdef WIN32
	DEBUG_PRINT("Pusher separation (not) confirmed?");
	#endif//WIN32

	return 0U;
}

Luint8 u8FCU_FCTL_MAINSM__IsPodStopConfirmed(void)
{
	// @todo: implement
	return 0U;
}

Luint8 u8FCU_FCTL_MAINSM__IsSpindownCompleteConfirmed(void)
{
#ifdef WIN32
	DEBUG_PRINT("Spindown is complete?");
#endif//WIN32

	// @todo: implement
	return 0U;
}


/////////////////////////////////////////////////////////////////////
//  Pod state transition handling
/////////////////////////////////////////////////////////////////////


void vFCU_FCTL_MAINSM_XSN__POD_STATE__INIT(void)
{

	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

#ifdef WIN32
	// No commands are allowed during init state
	vWIN32_DEBUG_PRINT__CommandNotAllowed(sFCU.sStateMachine.command.command);
#endif//WIN32

	// Check conditionals (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if(u8FCU_FCTL_MAINSM___IsPodInitComplete())
		{
			sm->eCurrentState = POD_STATE__IDLE;
		} 
		else
		{
			// fall on
		}
	}


}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__IDLE()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(sFCU.sStateMachine.command.command)
		{
			
			case POD_COMMAND__TEST_MODE:
				sm->eCurrentState = POD_STATE__TEST_MODE;
				break;
			
			case POD_COMMAND__ARMED_WAIT:
				if ( armed_wait_checks_ok() )
				{
					sm->eCurrentState = POD_STATE__ARMED_WAIT;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed armed_wait_checks_ok() check", sPod->absname, lookup_pod_command(POD_COMMAND__ARMED_WAIT), lookup_pod_state(POD_STATE__IDLE));
					#endif
				}
				break;
			
			case POD_COMMAND__DRIVE:
				if ( drive_checks_ok() )
				{
					sm->eCurrentState = POD_STATE__DRIVE;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed drive_checks_ok() check", sPod->absname, lookup_pod_command(POD_COMMAND__DRIVE), lookup_pod_state(POD_STATE__IDLE));
					#endif
				}
				break;

			//LG hack for testing
			case POD_COMMAND__READY:
				sm->eCurrentState = POD_STATE__READY;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__TEST_MODE()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(sFCU.sStateMachine.command.command)
		{
			
			case POD_COMMAND__IDLE:
				sm->eCurrentState = POD_STATE__IDLE;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__DRIVE(void)
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(sFCU.sStateMachine.command.command)
		{
			
			case POD_COMMAND__IDLE:
				sm->eCurrentState = POD_STATE__IDLE;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__ARMED_WAIT(void)
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(sFCU.sStateMachine.command.command)
		{
			
			case POD_COMMAND__IDLE:
				sm->eCurrentState = POD_STATE__IDLE;
				break;
			
			case POD_COMMAND__FLIGHT_PREP:
				if ( flight_prep_checks_ok() )
				{
					sm->eCurrentState = POD_STATE__FLIGHT_PREP;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed flight_prep_checks_ok() check", sPod->absname, lookup_pod_command(POD_COMMAND__FLIGHT_PREP), lookup_pod_state(POD_STATE__ARMED_WAIT));
					#endif
				}
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__FLIGHT_PREP(void)
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(sFCU.sStateMachine.command.command)
		{
			
			case POD_COMMAND__ARMED_WAIT:
				sm->eCurrentState = POD_STATE__ARMED_WAIT;
				break;
			
			case POD_COMMAND__READY:
				if ( flight_readiness_checks_ok() )
				{
					sm->eCurrentState = POD_STATE__READY;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed flight_readiness_checks_ok() check", sPod->absname, lookup_pod_command(POD_COMMAND__READY), lookup_pod_state(POD_STATE__FLIGHT_PREP));
					#endif
				}
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__READY(void)
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(sFCU.sStateMachine.command.command)
		{
			
			case POD_COMMAND__FLIGHT_PREP:
				// Go back to FLIGHT PREP if commanded
				sm->eCurrentState = POD_STATE__FLIGHT_PREP;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	else
	{

	}
	
	// Check conditionals (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{

		//LG, check the various nav sources and determine how we need to
		//transition, for now just threshold it

#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
		if(u8FCU_FCTL_MAINSM__IsAccelConfirmed() == 1U)
#else
		// For testing only
		if(1)
#endif
		{
			#ifdef WIN32
			DEBUG_PRINT("Acceleration confirmed -- transitioning to POD_STATE__ACCEL");
			#endif
			sm->eCurrentState = POD_STATE__ACCEL;
		} 
		else
		{
			// fall on
		}
	}
	else
	{

	}

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__ACCEL(void)
{
	Luint8 u8Test;
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check conditionals (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		/** Determining ACCEL => COAST_INTERLOCK:
			- if using accelerometers AND pusher separation:
				- confirm decel and pusher separation = transition
			- if using accelerometers and NO pusher separation:
				- confirm decel
			- if using pusher separation and NO acclerometers:
				- confirm pusher separation
			- if using neither, just timeout
			- timeout = transition
		*/


		// Have we confirmed deceleration?
		Luint8 u8IsDecelConfirmed = 0U;

		//do we want to use the pusher detection?
		Luint8 u8UsePusherSeparation = u8FCU_FCTL_TRACKDB__Accel__Get_UsePusherSeparaation();

		// Have we confirmed pusher separation?
		Luint8 u8PusherSeparationConfirmed = 0U;

		// Do we feel that we've detected the end of the push?
		Luint8 u8PushCompleteDetected = 0U;


		#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
			u8IsDecelConfirmed = u8FCU_FCTL_MAINSM__IsDecelConfirmed();
		#else
			// For testing only
			u8IsDecelConfirmed = 1U;
		#endif

		// Determine if we've detected the end of the push		
		if (u8UsePusherSeparation == 1U)
		{
			// Use both decel and pusher pin detection to see if we're at the end of the push
			u8PusherSeparationConfirmed = u8FCU_FCTL_MAINSM__IsPusherSeparationConfirmed();
			u8PushCompleteDetected = u8IsDecelConfirmed && u8PusherSeparationConfirmed;
		}
		else
		{
			// Not using the pusher pin detection; rely on deceleration only
			u8PushCompleteDetected = u8IsDecelConfirmed;
		}

		// Handle state change if we've detected the end of the push
		if (u8PushCompleteDetected == 1U)
		{
			#ifdef WIN32
			DEBUG_PRINT("End of push detected -- transitioning to POD_STATE__COAST_INTERLOCK");
			#endif
			sm->eCurrentState = POD_STATE__COAST_INTERLOCK;
		}
		else
		{
			// fall on
		}

	}
	else
	{
		// We're already transitioning
	}

	// Check timeouts (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// If our ACCEL backup timeout has expired, automatically go to COAST_INTERLOCK
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max) )
		{
			#ifdef WIN32
			DEBUG_PRINT("Accel_To_Coast timeout expired -- transitioning to POD_STATE__COAST_INTERLOCK");
			#endif
			sm->eCurrentState = POD_STATE__COAST_INTERLOCK;
		} 
		else 
		{
			// fall on
		}
	}
	else
	{

	}

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__COAST_INTERLOCK(void)
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check timeouts (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.pCoast_To_Brake) == 1U)
		{
			#ifdef WIN32
			DEBUG_PRINT("Coast_To_Brake timeout expired -- transitioning to POD_STATE__BRAKE");
			#endif
			sm->eCurrentState = POD_STATE__BRAKE;
		} 
		else 
		{
			// fall on
		}
	}

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__BRAKE()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check conditionals (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if ( u8FCU_FCTL_MAINSM__IsPodStopConfirmed() )
		{
			#ifdef WIN32
			DEBUG_PRINT("Pod stop confirmed -- transitioning to POD_STATE__SPINDOWN");
			#endif
			sm->eCurrentState = POD_STATE__SPINDOWN;
		} 
		else
		{
			// fall on
		}
	}

	// Check timeouts (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.pBrake_To_Spindown) == 1U)
		{
			#ifdef WIN32
			DEBUG_PRINT("Brake_To_Spindown timeout expired -- transitioning to POD_STATE__SPINDOWN");
			#endif
			sm->eCurrentState = POD_STATE__SPINDOWN;
		} 
		else 
		{
			// fall on
		}
	}

}

void vFCU_FCTL_MAINSM_XSN__POD_STATE__SPINDOWN(void)
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check conditionals (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if ( u8FCU_FCTL_MAINSM__IsSpindownCompleteConfirmed() )
		{
			#ifdef WIN32
			DEBUG_PRINT("Spindown complete confirmed");
			#endif
			sm->eCurrentState = POD_STATE__IDLE;
		} 
		else
		{
			// fall on
		}
	}

	// Check timeouts (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.pSpindown_To_Idle) == 1U)
		{
			#ifdef WIN32
			DEBUG_PRINT("Spindown_To_Idle timeout expired -- transitioning to POD_STATE__IDLE");
			#endif
			sm->eCurrentState = POD_STATE__IDLE;
		} 
		else 
		{
			// fall on
		}
	}

}



//safetys
#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
