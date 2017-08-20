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
#ifdef WIN32
	DEBUG_PRINT("Armed wait checks (not really) passed");
#endif
	return 1U;
}

Luint8 drive_checks_ok()
{
	// @todo: implement
#ifdef WIN32
	DEBUG_PRINT("Drive checks (not really) passed");
#endif
	return 1U;
}

Luint8 flight_prep_checks_ok()
{
	// @todo: implement
#ifdef WIN32
	DEBUG_PRINT("Flight prep checks (not really) passed");
#endif
	return 1U;
}

Luint8 flight_readiness_checks_ok()
{
	// @todo: implement
#ifdef WIN32
	DEBUG_PRINT("Flight readiness checks (not really) passed");
#endif
	return 1U;
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

#ifdef WIN32
void vWIN32_DEBUG_PRINT__CommandNotAllowed(TE_POD_COMMAND_T command)
{
	switch (command)
	{
		case POD_COMMAND__NO_COMMAND:
			break;
		case POD_COMMAND__IDLE:
			DEBUG_PRINT("POD_COMMAND__IDLE not allowed in this state");
			break;
		case POD_COMMAND__TEST_MODE:
			DEBUG_PRINT("POD_COMMAND__TEST_MODE not allowed in this state");
			break;
		case POD_COMMAND__DRIVE:
			DEBUG_PRINT("POD_COMMAND__DRIVE not allowed in this state");
			break;
		case POD_COMMAND__ARMED_WAIT:
			DEBUG_PRINT("POD_COMMAND__ARMED_WAIT not allowed in this state");
			break;
		case POD_COMMAND__FLIGHT_PREP:
			DEBUG_PRINT("POD_COMMAND__FLIGHT_PREP not allowed in this state");
			break;
		case POD_COMMAND__READY:
			DEBUG_PRINT("POD_COMMAND__READY not allowed in this state");
			break;
		default:
			// Nothing to do
			break;
	}
}
#endif


void handle_POD_STATE__INIT_transitions()
{

	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__INIT;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

#ifdef WIN32
	// Note: no commands are allowed during INIT
	vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif


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
			
			case POD_COMMAND__NO_COMMAND:
				break;

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
					// fall on
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
#ifdef WIN32
				vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif
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
			case POD_COMMAND__NO_COMMAND:
				break;

			case POD_COMMAND__IDLE:
				sm->eCurrentState = POD_STATE__IDLE;
				break;
		
			default:
#ifdef WIN32
				vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif
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
		switch(command) {
			case POD_COMMAND__NO_COMMAND:
				break;

			case POD_COMMAND__IDLE:
				sm->eCurrentState = POD_STATE__IDLE;
				break;
		
			default:
#ifdef WIN32
				vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif
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
			case POD_COMMAND__NO_COMMAND:
				break;

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
					#ifdef WIN32
					DEBUG_PRINT("ARMED_WAIT transition to FLIGHT_PREP blocked: pod did not pass flight prep checks");
					#endif
				}
				break;
		
			default:
#ifdef WIN32
				vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif
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
			case POD_COMMAND__NO_COMMAND:
				break;

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
					#ifdef WIN32
					DEBUG_PRINT("Transition to READY blocked: pod did not pass flight readiness checks.");
					#endif
				}
				break;
		
			default:
#ifdef WIN32
				vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif
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
			case POD_COMMAND__NO_COMMAND:
				break;

			case POD_COMMAND__FLIGHT_PREP:
				// Go back to FLIGHT PREP if commanded
				sm->eCurrentState = POD_STATE__FLIGHT_PREP;
				break;
		
			default:
#ifdef WIN32
				vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif
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
			#ifdef WIN32
			DEBUG_PRINT("READY state: Pod acceleration confirmed");
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

void handle_POD_STATE__ACCEL_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__ACCEL;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

#ifdef WIN32
	// Note: no commands allowed in ACCEL state
	vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif

	// Check conditionals (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( pusher_separation_confirmed() )
		{
			#ifdef WIN32
			DEBUG_PRINT("ACCEL state: Pusher separation confirmed");
			#endif
			sm->eCurrentState = POD_STATE__COAST_INTERLOCK;
		} 
		else
		{
			// fall on
		}
	}

	// Check timeouts (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		// If our ACCEL backup timeout has expired, automatically go to COAST_INTERLOCK
		if ( timeout_expired(&sFCU.sStateMachine.AccelBackupTimeout) ) 
		{
			#ifdef WIN32
			DEBUG_PRINT("ACCEL state: backup transition timer expired");
			#endif
			sm->eCurrentState = POD_STATE__COAST_INTERLOCK;
		} 
		else 
		{
			// fall on
		}
	}

}

void handle_POD_STATE__COAST_INTERLOCK_transitions()
{
	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;

	// Convenience
	TE_POD_STATE_T state = POD_STATE__COAST_INTERLOCK;
	TE_POD_COMMAND_T command = sFCU.sStateMachine.command.command;

#ifdef WIN32
	// No commands allowed during COAST_INTERLOCK
	vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif

	// Check timeouts (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( timeout_expired(&sFCU.sStateMachine.CoastInterlockTimeout) ) 
		{
			#ifdef WIN32
			DEBUG_PRINT("COAST_INTERLOCK state: Coast timer expired");
			#endif
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

#ifdef WIN32
	// No commands allowed during BRAKE
	vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif

	// Check conditionals (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( pod_stop_confirmed() )
		{
			#ifdef WIN32
			DEBUG_PRINT("BRAKE state: pod stop confirmed");
			#endif
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
		if ( timeout_expired(&sFCU.sStateMachine.BrakeToSpindownBackupTimeout) ) 
		{
			#ifdef WIN32
			DEBUG_PRINT("BRAKE state: Braking timeout expired");
			#endif
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

#ifdef WIN32
	// No commands allowed during spindown
	vWIN32_DEBUG_PRINT__CommandNotAllowed(command);
#endif

	// Check conditionals (if we aren't already transitioning)
	if ( ! u8FCU_FCTL_MAINSM__Check_IsTransitioning(sm) )
	{
		if ( spindown_complete_confirmed() )
		{
			#ifdef WIN32
			DEBUG_PRINT("SPINDOWN state: spindown is complete");
			#endif
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
		if ( timeout_expired(&sFCU.sStateMachine.SpindownToIdleBackupTimeout) ) 
		{
			#ifdef WIN32
			DEBUG_PRINT("SPINDOWN state: spindown timeout triggered");
			#endif
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
