#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;




#if 0
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
	vFCU_FCTL_MAINSM_TIMER__Init(&ic->commandTimeout, duration_ms);
	ic->enabled = 0U;
}

// Call this when the first packet is received. Ok to call it multiple times; it will just reset the timer.
void interlock_command_enable(strInterlockCommand *ic)
{
	ic->enabled = 1;
	vFCU_FCTL_MAINSM_TIMER__Restart(&ic->commandTimeout);
}

// Call this when the second packet is received to check whether the command can execute (i.e. timeout has not expired)
Luint8 interlock_command_can_execute(strInterlockCommand *ic)
{
	Luint8 can_execute;

	// Note: I know this is not great code style but under time crunch
	if (ic->enabled && ! u8FCU_FCTL_MAINSM_TIMER__Is_Expired(&ic->commandTimeout) )
	{
		can_execute = 1;
	}
	else
	{
		can_execute = 0U;
	}
	return can_execute;
}

// Call this if the command was executed and we're ready to listen for the initial packet again
// @todo: do we even need this? if we receive another enable packet, we will restart the timeout. Once its timed out, it will not keep counting, so we're ok.
void interlock_command_reset(strInterlockCommand *ic)
{
	// Reset the timeout (stop it and set the elapsed time to 0)
	timeout_reset(&ic->commandTimeout);
}

// Call this in one of our timer ISRs. Ok to call this since the timeout has to be started for the update to have any effect.
void interlock_command_update_timeout(strInterlockCommand *ic, Luint8 time_ms)
{
	// Update the timeout
	vFCU_FCTL_MAINSM_TIMER__Update_x10ms(&ic->commandTimeout, time_ms);
}



// Interlock command integration functions (depends on sFCU and state machine -- the functions above do not)
void unlock_pod_interlock_command(TE_POD_COMMAND_T command)
{
	// @todo: unlock the command
	interlock_command_enable(&sFCU.sStateMachine.command_interlocks[command]);
}



#endif //0


void attempt_pod_interlock_command(TE_POD_COMMAND_T command)
{
	// Attempt to execute the command (provided that the interlock timeout has not expired)
	switch(command)
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
			// do nothing
			break;
	}

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
