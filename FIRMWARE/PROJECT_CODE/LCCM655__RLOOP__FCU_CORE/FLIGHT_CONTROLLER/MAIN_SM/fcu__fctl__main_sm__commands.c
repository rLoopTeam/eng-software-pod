#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;


/////////////////////////////////////////////////////////////////////
//  Pod command functions
/////////////////////////////////////////////////////////////////////

void cmd_POD_COMMAND__IDLE(void)
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__IDLE() called\n");
	#endif

	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__IDLE;

}

void cmd_POD_COMMAND__TEST_MODE(void)
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__TEST_MODE() called\n");
	#endif

	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__TEST_MODE;

}

void cmd_POD_COMMAND__DRIVE(void)
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__DRIVE() called\n");
	#endif

	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__DRIVE;

}

void cmd_POD_COMMAND__FLIGHT_PREP(void)
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__FLIGHT_PREP() called\n");
	#endif

	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__FLIGHT_PREP;

}

void cmd_POD_COMMAND__ARMED_WAIT(void)
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__ARMED_WAIT() called\n");
	#endif

	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__ARMED_WAIT;

}

void cmd_POD_COMMAND__READY(void)
{
	#if DEBUG == 1U
		printf("cmd_POD_COMMAND__READY() called\n");
	#endif

	strPodCmd * cmd = &sFCU.sStateMachine.command;
	cmd->command = POD_COMMAND__READY;

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
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
