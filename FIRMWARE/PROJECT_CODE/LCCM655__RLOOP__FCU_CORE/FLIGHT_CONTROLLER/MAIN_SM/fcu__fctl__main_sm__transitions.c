//handle the main state machine transition cases

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;


////////////////////////////////////////////////////////////////////
//  Pod transition and command guard functions
/////////////////////////////////////////////////////////////////////

bool pod_init_complete()
{
	return sFCU.eInitStates == INIT_STATE__RUN;
}

bool armed_wait_checks_ok()
{
	// @todo: implement
	return false;
}

bool drive_checks_ok()
{
	// @todo: implement
	return false;
}

bool flight_prep_checks_ok()
{
	// @todo: implement
	return false;
}

bool flight_readiness_checks_ok()
{
	// @todo: implement
	return false;
}

bool accel_confirmed()
{
	// @todo: implement
	return false;
}

bool pusher_separation_confirmed()
{
	// @todo: implement
	return false;
}

bool pod_stop_confirmed()
{
	// @todo: implement
	return false;
}

bool spindown_complete_confirmed()
{
	// @todo: implement
	return false;
}


/////////////////////////////////////////////////////////////////////
//  Pod state transition handling
/////////////////////////////////////////////////////////////////////


void handle_POD_INIT_STATE_transitions()
{

	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_INIT_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check conditionals (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( pod_init_complete() )
		{
			sm->state = POD_IDLE_STATE;
		} 
		else
		{
			// fall on
		}
	}


}

void handle_POD_IDLE_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_IDLE_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_TEST_MODE:
				sm->state = POD_TEST_MODE_STATE;
				break;
			
			case POD_ARMED_WAIT:
				if ( armed_wait_checks_ok() )
				{
					sm->state = POD_ARMED_WAIT_STATE;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed armed_wait_checks_ok() check", sPod->absname, lookup_pod_command(POD_ARMED_WAIT), lookup_pod_state(POD_IDLE_STATE));
					#endif
				}
				break;
			
			case POD_DRIVE:
				if ( drive_checks_ok() )
				{
					sm->state = POD_DRIVE_STATE;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed drive_checks_ok() check", sPod->absname, lookup_pod_command(POD_DRIVE), lookup_pod_state(POD_IDLE_STATE));
					#endif
				}
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void handle_POD_TEST_MODE_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_TEST_MODE_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_IDLE:
				sm->state = POD_IDLE_STATE;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void handle_POD_DRIVE_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_DRIVE_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_IDLE:
				sm->state = POD_IDLE_STATE;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void handle_POD_ARMED_WAIT_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_ARMED_WAIT_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_IDLE:
				sm->state = POD_IDLE_STATE;
				break;
			
			case POD_FLIGHT_PREP:
				if ( flight_prep_checks_ok() )
				{
					sm->state = POD_FLIGHT_PREP_STATE;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed flight_prep_checks_ok() check", sPod->absname, lookup_pod_command(POD_FLIGHT_PREP), lookup_pod_state(POD_ARMED_WAIT_STATE));
					#endif
				}
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void handle_POD_FLIGHT_PREP_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_FLIGHT_PREP_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_ARMED_WAIT:
				sm->state = POD_ARMED_WAIT_STATE;
				break;
			
			case POD_READY:
				if ( flight_readiness_checks_ok() )
				{
					sm->state = POD_READY_STATE;
				} 
				else 
				{
					#if DEBUG == 1U
					printf("%s -- REJECTING COMMAND %s in state %s: failed flight_readiness_checks_ok() check", sPod->absname, lookup_pod_command(POD_READY), lookup_pod_state(POD_FLIGHT_PREP_STATE));
					#endif
				}
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	

}

void handle_POD_READY_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_READY_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check commands (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// Handle commands
		switch(command) {
			
			case POD_FLIGHT_PREP:
				// Go back to FLIGHT PREP if commanded
				sm->state = POD_FLIGHT_PREP_STATE;
				break;
		
			default:
				// Nothing to do
				break;
		}
	}
	
	// Check conditionals (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( accel_confirmed() )
		{
			sm->state = POD_ACCEL_STATE;
		} 
		else
		{
			// fall on
		}
	}

}

void handle_POD_ACCEL_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_ACCEL_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check conditionals (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( pusher_separation_confirmed() )
		{
			sm->state = POD_COAST_INTERLOCK_STATE;
		} 
		else
		{
			// fall on
		}
	}

	// Check timeouts (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		// If our ACCEL backup timeout has expired, automatically go to COAST_INTERLOCK
		if ( timeout_expired(&sFCU.sPodStateMachine.AccelBackupTimeout) ) 
		{
			sm->state = POD_COAST_INTERLOCK_STATE;
		} 
		else 
		{
			// fall on
		}
	}

}

void handle_POD_COAST_INTERLOCK_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_COAST_INTERLOCK_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check timeouts (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( timeout_expired(&sFCU.sPodStateMachine.CoastInterlockTimeout) ) 
		{
			sm->state = POD_BRAKE_STATE;
		} 
		else 
		{
			// fall on
		}
	}

}

void handle_POD_BRAKE_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_BRAKE_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check conditionals (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( pod_stop_confirmed() )
		{
			sm->state = POD_SPINDOWN_STATE;
		} 
		else
		{
			// fall on
		}
	}

	// Check timeouts (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( timeout_expired(&sFCU.sPodStateMachine.BrakeToSpindownBackupTimeout) ) 
		{
			sm->state = POD_SPINDOWN_STATE;
		} 
		else 
		{
			// fall on
		}
	}

}

void handle_POD_SPINDOWN_STATE_transitions()
{
	StateMachine *sm = &sFCU.sPodStateMachine.sm;

	// Convenience
	E_POD_STATE_T state = POD_SPINDOWN_STATE;
	E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

	// Check conditionals (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( spindown_complete_confirmed() )
		{
			sm->state = POD_IDLE_STATE;
		} 
		else
		{
			// fall on
		}
	}

	// Check timeouts (if we aren't already transitioning)
	if ( ! sm_transitioning(sm) )
	{
		if ( timeout_expired(&sFCU.sPodStateMachine.SpindownToIdleBackupTimeout) ) 
		{
			sm->state = POD_IDLE_STATE;
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

void cmd_POD_IDLE()
{
	#if DEBUG == 1U
		printf("cmd_POD_IDLE() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sPodStateMachine.command;
	cmd->command = POD_IDLE;

}

void cmd_POD_TEST_MODE()
{
	#if DEBUG == 1U
		printf("cmd_POD_TEST_MODE() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sPodStateMachine.command;
	cmd->command = POD_TEST_MODE;

}

void cmd_POD_DRIVE()
{
	#if DEBUG == 1U
		printf("cmd_POD_DRIVE() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sPodStateMachine.command;
	cmd->command = POD_DRIVE;

}

void cmd_POD_FLIGHT_PREP()
{
	#if DEBUG == 1U
		printf("cmd_POD_FLIGHT_PREP() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sPodStateMachine.command;
	cmd->command = POD_FLIGHT_PREP;

}

void cmd_POD_ARMED_WAIT()
{
	#if DEBUG == 1U
		printf("cmd_POD_ARMED_WAIT() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sPodStateMachine.command;
	cmd->command = POD_ARMED_WAIT;

}

void cmd_POD_READY()
{
	#if DEBUG == 1U
		printf("cmd_POD_READY() called\n");
	#endif
	
	strPodCmd * cmd = &sFCU.sPodStateMachine.command;
	cmd->command = POD_READY;

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
