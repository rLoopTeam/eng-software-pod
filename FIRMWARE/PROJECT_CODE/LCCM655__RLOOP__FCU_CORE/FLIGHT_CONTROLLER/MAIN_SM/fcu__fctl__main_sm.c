/**
 * @file		FCU__FCTL__MAIN_SM.C
 * @brief		Main state machine for the flight control unit
 * @author		Lachlan Grogan, Ryan Adams
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
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
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
	vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max_x10ms, 10 * 100);

	// Coast interlock timeout
	vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pCoast_To_Brake_x10ms, 1 * 100);

	// Brake to Spindown backup timeout
	vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pBrake_To_Spindown_x10ms, 60 * 100);

	// Spindown to Idle backup timeout
	vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pSpindown_To_Idle_x10ms, 120 * 100);


	// Initialize some interlock guards for command requests coming in over the network
	// Note: These are only used to determine if a cmd_POD_COMMAND__* function should be
	//       called when we receive a NET_PKT__FCU_GEN__POD_COMMAND. You can always call 
	//       cmd_POD_COMMAND__* functions directly to bypass the interlock guards. 
	for(u8Counter = 0U; u8Counter < (Luint8)POD_COMMAND__NUM_COMMANDS; u8Counter++)
	{
		// Initialize the interlock commands with a 10 second timeout
		Luint32 u32InterlockDuration_x10ms = 10 * 100; // 10 seconds = 10 * (10ms * 100) 
		vFCU_FCTL_MAINSM__InterlockGuard__Init( &sFCU.sStateMachine.sInterlockGuards[ (TE_POD_COMMAND_T)u8Counter ], u32InterlockDuration_x10ms);
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
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__INIT");
				#endif
			}
			else
			{
				//we are not entering.
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__INIT();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__INIT) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...
		
			}
			
			break;
		
		case POD_STATE__IDLE:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__IDLE) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__IDLE");
				#endif
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__IDLE();
		 
			if (u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__IDLE)) 
			{
				// We're exiting this state -- perform any exit actions
				// ...		
			}
			
			break;
		
		case POD_STATE__TEST_MODE:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__TEST_MODE) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__TEST_MODE");
				#endif
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__TEST_MODE();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__TEST_MODE) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...		
			}
			
			break;
		
		case POD_STATE__DRIVE:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__DRIVE) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__DRIVE");
				#endif
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__DRIVE();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__DRIVE) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...		
			}
			
			break;
		
		case POD_STATE__ARMED_WAIT:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__ARMED_WAIT) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__ARMED_WAIT");
				#endif
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__ARMED_WAIT();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__ARMED_WAIT) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...
			}
			
			break;
		
		case POD_STATE__FLIGHT_PREP:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__FLIGHT_PREP) == 1U)
			{

				//During flight prep, we must re-load the track specific data
				vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max_x10ms, u32FCU_FCTL_TRACKDB__Time__Get_Accel_to_Coast_Max());

				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__FLIGHT_PREP");
				#endif
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__FLIGHT_PREP();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__FLIGHT_PREP) == 1U) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
			}
			
			break;
		
		case POD_STATE__READY:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__READY) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__READY");
				#endif
				
				// (Re)start the ready expired backup timer that will transition us (where?) 
				// @todo: We now have the capability to transition back to FLIGHT_PREP from READY, so we don't need this any more most likely.
				// vFCU_FCTL__TIMEOUT__Restart(&sFCU.sStateMachine.ReadyExpiredBackupTimeout);

				//reload all the timers
				// Accel to Coast Interlock backup timeout
				vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max_x10ms, u32FCU_FCTL_TRACKDB__Time__Get_Accel_to_Coast_Max());

				// Coast interlock timeout
				vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pCoast_To_Brake_x10ms, u32FCU_FCTL_TRACKDB__Time__Get_Coast_to_Brake());

				// Brake to Spindown backup timeout
				vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pBrake_To_Spindown_x10ms, u32FCU_FCTL_TRACKDB__Time__Get_Brake_To_Spindown());

				// Spindown to Idle backup timeout
				vFCU_FCTL__TIMEOUT__Init(&sFCU.sStateMachine.sTimers.pSpindown_To_Idle_x10ms, u32FCU_FCTL_TRACKDB__Time__Get_Spindown_To_Idle());

			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__READY();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__READY) == 1U)
			{
				// We're exiting this state -- perform any exit actions
				// ...		
			}
			
			break;
		
		case POD_STATE__ACCEL:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__ACCEL) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__ACCEL");
				#endif

				// (Re)start the accel backup timeout. If this expires, we will automatically transition to COAST_INTERLOCK (see below)
				vFCU_FCTL__TIMEOUT__Restart(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max_x10ms);

			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__ACCEL();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__ACCEL) == 1U) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
			}
			
			break;
		
		case POD_STATE__COAST_INTERLOCK:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__COAST_INTERLOCK) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__COAST_INTERLOCK");
				#endif
				
				// (Re)start our coast interlock timer. Expiration will transition us to BRAKE (see below)
				vFCU_FCTL__TIMEOUT__Restart(&sFCU.sStateMachine.sTimers.pCoast_To_Brake_x10ms);
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__COAST_INTERLOCK();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__COAST_INTERLOCK) == 1U) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
			}
			
			break;
		
		case POD_STATE__BRAKE:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__BRAKE) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__BRAKE");
				#endif
				
				// (Re)start the BRAKE to SPINDOWN backup timeout. If this expires, we'll transition to SPINDOWN
				vFCU_FCTL__TIMEOUT__Restart(&sFCU.sStateMachine.sTimers.pBrake_To_Spindown_x10ms);
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__BRAKE();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__BRAKE) == 1U) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
			}
			
			break;
		
		case POD_STATE__SPINDOWN:
		
			if(u8FCU_FCTL_MAINSM__Check_IsEntering(sm, POD_STATE__SPINDOWN) == 1U)
			{
				// Perform entering actions
				#ifdef WIN32
					DEBUG_PRINT("Entering POD_STATE__SPINDOWN");
				#endif
				
				// (Re)start our spindown backup timeout. If this expires we'll automatically transition to IDLE.
				vFCU_FCTL__TIMEOUT__Restart(&sFCU.sStateMachine.sTimers.pSpindown_To_Idle_x10ms);
			}
		
			// Handle transitions
			vFCU_FCTL_MAINSM_XSN__POD_STATE__SPINDOWN();
		 
			if(u8FCU_FCTL_MAINSM__Check_IsExiting(sm, POD_STATE__SPINDOWN) == 1U) 
			{
				// We're exiting this state -- perform any exit actions
				// ...
			}
			
			break;

		default:
			//should never get here.
			break;

	}// switch(sFCU.sStateMachine.sm.state)
   

	 // Clear command (we will have handled it in the transition functions)
	vFCU_FCTL_MAINSM__Clear_Command();


}

/** Step the state machine -- detect state changes and update sm status */
void vFCU_FCTL_MAINSM__Step(TS_FCTL__STATE_MACHINE_T *p_sm)
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
	Luint8 u8Counter;

	/** Accel to Coast Interlock backup timeout */
	vFCU_FCTL__TIMEOUT__Update_x10ms(&sFCU.sStateMachine.sTimers.pAccel_To_Coast_Max_x10ms);

	/** Coast interlock timeout */
	vFCU_FCTL__TIMEOUT__Update_x10ms(&sFCU.sStateMachine.sTimers.pCoast_To_Brake_x10ms);

	/** Brake to Spindown backup timeout */
	vFCU_FCTL__TIMEOUT__Update_x10ms(&sFCU.sStateMachine.sTimers.pBrake_To_Spindown_x10ms);

	/** Spindown to Idle backup timeout */
	vFCU_FCTL__TIMEOUT__Update_x10ms(&sFCU.sStateMachine.sTimers.pSpindown_To_Idle_x10ms);

	/** Update the timeouts for our net command interlock guards */
	for (u8Counter = 0U; u8Counter < (Luint8)POD_COMMAND__NUM_COMMANDS; u8Counter++)
	{
		vFCU_FCTL_MAINSM__InterlockGuard__UpdateTimeout_x10ms(&sFCU.sStateMachine.sInterlockGuards[(TE_POD_COMMAND_T)u8Counter]);
	}

}

void vFCU_FCTL_MAINSM__100MS_ISR(void)
{
	Luint8 u8Counter;

    // Update Timeouts
	// Note that these will only update the time if the timeout has been started (elsewhere)
	
	// Update our state machine timeouts. 

#if 0


	// Update interlock command timeouts
	// Initialize our commands. They're all interlock commands, so we'll just do them in a loop
	for(u8Counter = 0U; u8Counter < (Luint8)POD_COMMAND__NUM_COMMANDS; u8Counter++)
	{
		// Initialize the interlock commands with a 10 second timeout (you have to hit the second button within 10 seconds)
		vFCU_FCTL_MAINSM__InterlockGuard__Init( &sFCU.sStateMachine.command_interlocks[ (TE_POD_COMMAND_T)u8Counter ], 10 * 1000 );
	}

#endif //0

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

#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
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

