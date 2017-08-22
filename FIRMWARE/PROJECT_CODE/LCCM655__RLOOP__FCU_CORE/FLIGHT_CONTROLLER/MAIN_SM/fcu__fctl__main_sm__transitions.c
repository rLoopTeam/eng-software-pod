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

Luint8 pod_init_complete(void)
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

Luint8 accel_confirmed(void)
{
	// @todo: implement
	return 0U;
}

Luint8 pusher_separation_confirmed(void)
{
	// @todo: implement
	return 0U;
}

Luint8 pod_stop_confirmed(void)
{
	// @todo: implement
	return 0U;
}

Luint8 spindown_complete_confirmed(void)
{
	// @todo: implement
	return 0U;
}


/////////////////////////////////////////////////////////////////////
//  Pod state transition handling
/////////////////////////////////////////////////////////////////////


void vFCU_FCTL_MAINSM_XSN__POD_STATE__INIT(void)
{

	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Check conditionals (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		if(1/* pod_init_complete() */)
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
		if(u8FCU_ACCEL_THRES__Is_Threshold_Met() == 1U)
#else
		if(1)
#endif
		{
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

		//do we want to use the pusher detection?
		u8Test = u8FCU_FCTL_TRACKDB__Accel__Get_UsePusherSeparaation();
		if(u8Test == 1U)
		{
			if ( pusher_separation_confirmed() )
			{
				sm->eCurrentState = POD_STATE__COAST_INTERLOCK;
			}
			else
			{
				// fall on
			}
		}
		else
		{
			//do not want to use the pusher
		}
	}
	else
	{

	}

	// Check timeouts (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// If our ACCEL backup timeout has expired, automatically go to COAST_INTERLOCK
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max) )
		{
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
		if ( pod_stop_confirmed() )
		{
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
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.BrakeToSpindownBackupTimeout) == 1U)
		{
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
		if ( spindown_complete_confirmed() )
		{
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
		if(u8FCU_FCTL__TIMEOUT__Is_Expired(&sFCU.sStateMachine.sTimers.SpindownToIdleBackupTimeout) == 1U)
		{
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

