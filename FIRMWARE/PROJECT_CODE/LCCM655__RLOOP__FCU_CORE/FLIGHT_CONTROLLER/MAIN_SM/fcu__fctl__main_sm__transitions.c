//handle the main state machine transition cases

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;


////////////////////////////////////////////////////////////////////
//  Pod transition and command guard functions
/////////////////////////////////////////////////////////////////////

Luint8 pod_init_complete()
{
	return sFCU.eInitStates == INIT_STATE__RUN;
}

Luint8 armed_wait_checks_ok()
{
	// @todo: implement
	return 0U;
}

Luint8 drive_checks_ok()
{
	// @todo: implement
	return 0U;
}

Luint8 flight_prep_checks_ok()
{
	// @todo: implement
	return 0U;
}

Luint8 flight_readiness_checks_ok()
{
	// @todo: implement
	return 0U;
}

Luint8 accel_confirmed()
{
	// @todo: implement
	return 0U;
}

Luint8 pusher_separation_confirmed()
{
	// @todo: implement
	return 0U;
}

Luint8 pod_stop_confirmed()
{
	// @todo: implement
	return 0U;
}

Luint8 spindown_complete_confirmed()
{
	// @todo: implement
	return 0U;
}


/////////////////////////////////////////////////////////////////////
//  Pod state transition handling
/////////////////////////////////////////////////////////////////////


void handle_POD_STATE__INIT_transitions()
{

	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__INIT;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

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

void handle_POD_STATE__IDLE_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__IDLE;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
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

void handle_POD_STATE__TEST_MODE_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__TEST_MODE;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_COMMAND__IDLE:
				sm->eCurrentState = POD_STATE__IDLE;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void handle_POD_STATE__DRIVE_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__DRIVE;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		// Handle commands
		switch(command)
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

void handle_POD_STATE__ARMED_WAIT_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__ARMED_WAIT;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
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

void handle_POD_STATE__FLIGHT_PREP_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__FLIGHT_PREP;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
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

void handle_POD_STATE__READY_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__READY;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if(u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) == 0U)
	{
		// Handle commands
		switch(command)
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

		if(u8FCU_ACCEL_THRES__Is_Threshold_Met() == 1U)
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

void handle_POD_STATE__ACCEL_transitions()
{
	Luint8 u8Test;
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__ACCEL;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

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
		if(u8FCU_FCTL_MAINSM_TIMER__Is_Expired(&sFCU.sStateMachine.sTimers.pAccel_To_Coast) )
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

void handle_POD_STATE__COAST_INTERLOCK_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__COAST_INTERLOCK;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check timeouts (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( u8FCU_FCTL_MAINSM_TIMER__Is_Expired(&sFCU.sStateMachine.sTimers.pCoast_To_Brake) )
		{
			sm->eCurrentState = POD_STATE__BRAKE;
		} 
		else 
		{
			// fall on
		}
	}

}

void handle_POD_STATE__BRAKE_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__BRAKE;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check conditionals (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
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
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( u8FCU_FCTL_MAINSM_TIMER__Is_Expired(&sFCU.sStateMachine.sTimers.BrakeToSpindownBackupTimeout) )
		{
			sm->eCurrentState = POD_STATE__SPINDOWN;
		} 
		else 
		{
			// fall on
		}
	}

}

void handle_POD_STATE__SPINDOWN_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__SPINDOWN;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

	// Check conditionals (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
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
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( u8FCU_FCTL_MAINSM_TIMER__Is_Expired(&sFCU.sStateMachine.sTimers.SpindownToIdleBackupTimeout) )
		{
			sm->eCurrentState = POD_STATE__IDLE;
		} 
		else 
		{
			// fall on
		}
	}

}


/////////////////////////////////////////////////////////////////////
//  Pod command functions
/////////////////////////////////////////////////////////////////////

void cmd_POD_COMMAND__IDLE()
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__IDLE() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__IDLE;

}

void cmd_POD_COMMAND__TEST_MODE()
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__TEST_MODE() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__TEST_MODE;

}

void cmd_POD_COMMAND__DRIVE()
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__DRIVE() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__DRIVE;

}

void cmd_POD_COMMAND__FLIGHT_PREP()
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__FLIGHT_PREP() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__FLIGHT_PREP;

}

void cmd_POD_COMMAND__ARMED_WAIT()
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__ARMED_WAIT() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__ARMED_WAIT;

}

void cmd_POD_COMMAND__READY()
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__READY() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__READY;

}


#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
