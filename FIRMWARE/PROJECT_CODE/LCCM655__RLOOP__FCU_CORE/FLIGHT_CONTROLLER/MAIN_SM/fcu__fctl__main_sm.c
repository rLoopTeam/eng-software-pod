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
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;

// @todo: set the state for SpaceX packet

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		5224534176289DBD9FF1B39936308C7E
 * @st_funcID		LCCM655R0.FILE.020.FUNC.001
 */
void vFCU_FCTL_MAINSM__Init(void)
{
	Luint8 u8Counter;

	#ifdef WIN32
	DEBUG_PRINT("vFCU_FCTL_MAINSM__Init()");
	#endif

	// Set the pod state machine to POD_STATE__INIT. It will automatically transition to IDLE once sFCU.eInitStates is in INIT_STATE__RUN (see below)
	sFCU.sStateMachine.sm.eCurrentState = POD_STATE__INIT;

	// Initialize our various state machine related timeouts
	// @todo: Move timeout duration values to config/mission profile

	// Accel to Coast Interlock backup timeout
	init_timeout(&sFCU.sStateMachine.AccelBackupTimeout, 10 * 1000);

	// Coast interlock timeout
	init_timeout(&sFCU.sStateMachine.CoastInterlockTimeout, 1 * 1000);

	// Brake to Spindown backup timeout
	init_timeout(&sFCU.sStateMachine.BrakeToSpindownBackupTimeout, 60 * 1000);

	// Spindown to Idle backup timeout
	init_timeout(&sFCU.sStateMachine.SpindownToIdleBackupTimeout, 120 * 1000);


	// Initialize our commands. They're all interlock commands, so we'll just do them in a loop
	for(u8Counter = 0U; u8Counter < (Luint8)POD_COMMAND__NUM_COMMANDS; u8Counter++)
	{
		// Initialize the interlock commands with a 10 second timeout (you have to hit the second button within 10 seconds)
		init_interlock_command( &sFCU.sStateMachine.command_interlocks[ (TE_POD_COMMAND_T)u8Counter ], 10 * 1000 );
	}

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
	//handle the state machine.

	TS_FCTL__STATE_MACHINE_T *sm = &sFCU.sStateMachine.sm;
	
	// Step the state machine to pick up on state changes etc.
	vFCU_FCTL_MAINSM__Step(sm);
		
	// Process pod state machine
	switch (sm->eCurrentState)
	{
		case POD_STATE__NULL:
			//we must never be here
			break;

		case POD_STATE__INIT:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__INIT) == 1U)
			{
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__INIT\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__INIT");
				#endif
			}
			else
			{
				//we are not entering.
			}
		
			// Handle transitions
			handle_POD_STATE__INIT_transitions();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__INIT) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__INIT\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__IDLE:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__IDLE) == 1U)
			{
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__IDLE\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__IDLE");
				#endif
			}
		
			// Handle transitions
			handle_POD_STATE__IDLE_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__IDLE)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__IDLE\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__TEST_MODE:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__TEST_MODE)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__TEST_MODE\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__TEST_MODE");
				#endif
			}
		
			// Handle transitions
			handle_POD_STATE__TEST_MODE_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__TEST_MODE)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__TEST_MODE\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__DRIVE:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__DRIVE)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__DRIVE\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__DRIVE");
				#endif
			}
		
			// Handle transitions
			handle_POD_STATE__DRIVE_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__DRIVE)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__DRIVE\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__ARMED_WAIT:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__ARMED_WAIT)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__ARMED_WAIT\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__ARMED_WAIT");
				#endif
			}
		
			// Handle transitions
			handle_POD_STATE__ARMED_WAIT_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__ARMED_WAIT)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__ARMED_WAIT\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__FLIGHT_PREP:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__FLIGHT_PREP)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__FLIGHT_PREP\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__FLIGHT_PREP");
				#endif
			}
		
			// Handle transitions
			handle_POD_STATE__FLIGHT_PREP_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__FLIGHT_PREP)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__FLIGHT_PREP\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__READY:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__READY) == 1U)
			{
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__READY\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__READY");
				#endif
				
				// (Re)start the ready expired backup timer that will transition us (where?) 
				// @todo: We now have the capability to transition back to FLIGHT_PREP from READY, so we don't need this any more most likely.
				// timeout_restart(&sFCU.sStateMachine.ReadyExpiredBackupTimeout);
			}
		
			// Handle transitions
			handle_POD_STATE__READY_transitions();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__READY) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__READY\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__ACCEL:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__ACCEL)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__ACCEL\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__ACCEL");
				#endif

				// (Re)start the accel backup timeout. If this expires, we will automatically transition to COAST_INTERLOCK (see below)
				timeout_restart(&sFCU.sStateMachine.AccelBackupTimeout);

			}
		
			// Handle transitions
			handle_POD_STATE__ACCEL_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__ACCEL)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__ACCEL\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__COAST_INTERLOCK:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__COAST_INTERLOCK)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__COAST_INTERLOCK\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__COAST_INTERLOCK");
				#endif
				
				// (Re)start our coast interlock timer. Expiration will transition us to BRAKE (see below)
				timeout_restart(&sFCU.sStateMachine.CoastInterlockTimeout);				
			}
		
			// Handle transitions
			handle_POD_STATE__COAST_INTERLOCK_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__COAST_INTERLOCK)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__COAST_INTERLOCK\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__BRAKE:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__BRAKE)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__BRAKE\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__BRAKE");
				#endif
				
				// (Re)start the BRAKE to SPINDOWN backup timeout. If this expires, we'll transition to SPINDOWN
				timeout_restart(&sFCU.sStateMachine.BrakeToSpindownBackupTimeout);
			}
		
			// Handle transitions
			handle_POD_STATE__BRAKE_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__BRAKE)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__BRAKE\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;
		
		case POD_STATE__SPINDOWN:
		
			if (u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__SPINDOWN)) {
				// Perform entering actions
				#if DEBUG == 1U
					printf("- %s Entering POD_STATE__SPINDOWN\n", "sFCU.sStateMachine.sm");
				#endif
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__SPINDOWN");
				#endif
				
				// (Re)start our spindown backup timeout. If this expires we'll automatically transition to IDLE.
				timeout_restart(&sFCU.sStateMachine.SpindownToIdleBackupTimeout);
			}
		
			// Handle transitions
			handle_POD_STATE__SPINDOWN_transitions();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__SPINDOWN)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
				#if DEBUG == 1U
					printf("- %s Exiting POD_STATE__SPINDOWN\n", "sFCU.sStateMachine.sm");
				#endif
		
			}
			
			break;

		default:
			//should never get here.
			break;

	}// switch(sFCU.sStateMachine.sm.state)
   
	// Clear any command that may have been set for this loop
	vFCU_FCTL_MAINSM__Clear_Command();

}

/** Step the state machine -- detect state changes and update sm status */
void vFCU_FCTL_MAINSM__Step(TS_FCTL__STATE_MACHINE_T* p_sm)
{

	// Update old state and signal that a state change has occurred
	if(p_sm->ePrevState != p_sm->eCurrentState)
	{
		// printf("State changed! %d to %d\n", p_sm->ePrevState, p_sm->state);
		p_sm->u8StateChanged = 1U;
		p_sm->ePrevState = p_sm->eCurrentState;
	}
	else
	{
		if(p_sm->u8StateChanged == 1U)
		{
			// the 'else' means that we go through the loop exactly once with the 'u8StateChanged' variable set to 1U once a state change has occured
			// Note that if the state changes again on the next loop, the ePrevState != state stanza gets triggered and starts this over again, which is what we want
			p_sm->u8StateChanged = 0U;
		}
		else
		{
			//do not step
		}
	}

}


void vFCU_FCTL_MAINSM__10MS_ISR(void)
{

}

void vFCU_FCTL_MAINSM__100MS_ISR(void)
{
	Luint8 u8Counter;

    // Update Timeouts
	// Note that these will only update the time if the timeout has been started (elsewhere)
	
	// Update our state machine timeouts. 

	/** Accel to Coast Interlock backup timeout */
	timeout_update(&sFCU.sStateMachine.AccelBackupTimeout, 100);

	/** Coast interlock timeout */
	timeout_update(&sFCU.sStateMachine.CoastInterlockTimeout, 100);

	/** Brake to Spindown backup timeout */
	timeout_update(&sFCU.sStateMachine.BrakeToSpindownBackupTimeout, 100);

	/** Spindown to Idle backup timeout */
	timeout_update(&sFCU.sStateMachine.SpindownToIdleBackupTimeout, 100);


	// Update interlock command timeouts
	for(u8Counter = 0U; u8Counter < (Luint8)POD_COMMAND__NUM_COMMANDS; u8Counter++)
	{
		// Add 100ms to our interlock command timeout elapsed time
		interlock_command_update_timeout( &sFCU.sStateMachine.command_interlocks[ (TE_POD_COMMAND_T)u8Counter ], 100 );
	}

}


/////////////////////////////////////////////////////////////////////
//  Timers and timeouts
/////////////////////////////////////////////////////////////////////

strTimeout create_timeout(Luint32 duration_ms)
{
	strTimeout t;
	t.duration_ms = duration_ms;
	t.elapsed_ms = 0;
	t.started = 0U;
	return t;
}

void init_timeout(strTimeout *timeout, Luint32 duration_ms)
{
	timeout->duration_ms = duration_ms;
	timeout->elapsed_ms = 0;
	timeout->started = 0U;
}

void timeout_restart(strTimeout *timeout)
{
	// Call this to start or restart a timeout
	timeout->elapsed_ms = 0U;
	timeout->started = 1;
}

void timeout_reset(strTimeout *timeout)
{
	timeout->elapsed_ms = 0U;
	timeout->started = 0U;
}

void timeout_ensure_started(strTimeout *timeout)
{
	if ( ! timeout->started ) {
		// If we're not started, make sure we are and reset our elapsed time
		timeout_restart(timeout);
	} else {
		// We're already started; nothing to do
	}
}

Luint8 timeout_expired(strTimeout *timeout)
{
	return timeout->elapsed_ms > timeout->duration_ms;
}

void timeout_update(strTimeout *timeout, Luint32 elapsed_ms)
{
	if ( ! timeout_expired(timeout) ) 
	{
		// If we haven't expired, update our timeout. We have no reason to keep adding once we've expired.
		timeout->elapsed_ms += elapsed_ms;
	}
}


/////////////////////////////////////////////////////////////////////
//  Interlock command handling
/////////////////////////////////////////////////////////////////////

strInterlockCommand create_interlock_command(const Luint32 duration_ms)
{
	strInterlockCommand ic;
	ic.commandTimeout = create_timeout(duration_ms);
	ic.enabled = 0U;
	return ic;
}

// Initialize an existing interlock command
void init_interlock_command(strInterlockCommand *ic, Luint32 duration_ms)
{
	init_timeout(&ic->commandTimeout, duration_ms);
	ic->enabled = 0U;
}

// Call this when the first packet is received. Ok to call it multiple times; it will just reset the timer.
void interlock_command_enable(strInterlockCommand *ic)
{
	ic->enabled = 1;
	timeout_restart(&ic->commandTimeout);
}

// Call this when the second packet is received to check whether the command can execute (i.e. timeout has not expired)
Luint8 interlock_command_can_execute(strInterlockCommand *ic)
{
	Luint8 can_execute = 0;
	Luint8 expired = timeout_expired(&ic->commandTimeout);
	Luint8 enabled = ic->enabled == 1;
	if (enabled == 1 && expired != 1)
	{
		can_execute = 1;
	}
	else
	{
#ifdef WIN32
		if (expired)
		{
			DEBUG_PRINT("Can not execute interlock command: timeout expired.");
		}
		else
		{
			DEBUG_PRINT("Can not execute interlock command: command not enabled.");
		}
#endif
		can_execute = 0;
	}

	return can_execute;
}

// Call this if the command was executed and we're ready to listen for the initial packet again
// @todo: do we even need this? if we receive another enable packet, we will restart the timeout. Once its timed out, it will not keep counting, so we're ok. 
void interlock_command_reset(strInterlockCommand *ic)
{
	// Reset the timeout (stop it and set the elapsed time to 0)
	timeout_reset(&ic->commandTimeout);
	ic->enabled = 0;
}

// Call this in one of our timer ISRs. Ok to call this since the timeout has to be started for the update to have any effect. 
void interlock_command_update_timeout(strInterlockCommand *ic, Luint8 time_ms)
{
	// Update the timeout
	timeout_update(&ic->commandTimeout, time_ms);
}



// Interlock command integration functions (depends on sFCU and state machine -- the functions above do not)
void unlock_pod_interlock_command(TE_POD_COMMAND_T command)
{
	// @todo: unlock the command
	interlock_command_enable(&sFCU.sStateMachine.command_interlocks[command]);
}

Luint8 attempt_pod_interlock_command(TE_POD_COMMAND_T command)
{
	Luint8 command_sent = 0U;
	// Attempt to execute the command (provided that the interlock timeout has not expired)
	if (interlock_command_can_execute(&sFCU.sStateMachine.command_interlocks[command]) == 1)
	{
		switch (command)
		{
			case POD_COMMAND__IDLE:
				cmd_POD_COMMAND__IDLE();
				break;
			case POD_COMMAND__TEST_MODE:
				cmd_POD_COMMAND__TEST_MODE();
				break;
			case POD_COMMAND__DRIVE:
				cmd_POD_COMMAND__DRIVE();
				break;
			case POD_COMMAND__FLIGHT_PREP:
				cmd_POD_COMMAND__FLIGHT_PREP();
				break;
			case POD_COMMAND__ARMED_WAIT:
				cmd_POD_COMMAND__ARMED_WAIT();
				break;
			case POD_COMMAND__READY:
				cmd_POD_COMMAND__READY();
				break;
			default:
				// Do nothing
				break;
		}
		command_sent = 1U;
	}
	else
	{	
		// Reset the interlock command (note that this does not restart the timer)
		interlock_command_reset(&sFCU.sStateMachine.command_interlocks[command]);
		command_sent = 0U;
	}
	return command_sent;
}

// Determine if we've just entered test_state on this step (a step is a go-round of the main loop)
Luint8 u8FCU_FCTL_MAINSM__Check_IsEntering(const TS_FCTL__STATE_MACHINE_T *cpSM, TE_POD_STATE_T eTestState)
{
	Luint8 u8Return;

	if((cpSM->u8StateChanged == 1U) && (cpSM->eCurrentState == eTestState))
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}

// Determine if we're marked to exit this state. Put this in your case statements after anything that could cause a state change.
Luint8 u8FCU_FCTL_MAINSM__Check_IsExiting(const TS_FCTL__STATE_MACHINE_T *cpSM, TE_POD_STATE_T eTestState)
{
	Luint8 u8Return;

	if(cpSM->eCurrentState != eTestState)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}

Luint8 u8FCU_FCTL_MAINSM__Check_IsTransitioning(const TS_FCTL__STATE_MACHINE_T *cpSM)
{
	Luint8 u8Return;

	// If our state is different from our old state, we are transitioning (?)
	if(cpSM->eCurrentState != cpSM->ePrevState)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}


void vFCU_FCTL_MAINSM__Clear_Command()
{
	sFCU.sStateMachine.command.command = POD_COMMAND__NO_COMMAND;
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
/** @} */
/** @} */
/** @} */

