/**
 * @file		FCU__FLIGHT_CONTROLLER.C
 * @brief		The actual flight control algo's
 * @author		Lachlan Grogan
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
 * @addtogroup FCU__FLIGHT_CTL
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		61224CE144104FD40882DF507A463938
 * @st_funcID		LCCM655R0.FILE.035.FUNC.001
 */
void vFCU_FCTL__Init(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		//setup laser orientation module
		vFCU_FLIGHTCLT_LASERORIENT__Init();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U
		//setup contrast sensor nav module
		vFCU_FLIGHTCTL_CONTRASTNAV__Init();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
		//getting the track databse loaded configures our data
		vFCU_FCTL_TRACKDB__Init();
	#endif

	//now that the track database was loaded, we need to configure our settings
	vFCU_FCTL__Config_From_Database();

	//Configure the main state machine
	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
		vFCU_FCTL_MAINSM__Init();
	#endif

	//init the navigation system
	vFCU_FCTL_NAV__Init();

}


/***************************************************************************//**
 * @brief
 * Process the flight controller
 * 
 * @st_funcMD5		905B1E3D5EF9A5AECFDF568F73F372C4
 * @st_funcID		LCCM655R0.FILE.035.FUNC.002
 */
void vFCU_FCTL__Process(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		vFCU_FLIGHTCLT_LASERORIENT__Process();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U
		vFCU_FLIGHTCTL_CONTRASTNAV__Process();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
		vFCU_FCTL_TRACKDB__Process();
	#endif

	//process navigation
	vFCU_FCTL_NAV__Process();

	//process the main state machine
	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
		vFCU_FCTL_MAINSM__Process();
	#endif

}


//based on our current track ID, configure all the subsystems from the
//track database
void vFCU_FCTL__Config_From_Database(void)
{

	//accel system
	//enable the Accel system
	vFCU_ACCEL_VALID__Enable(u8FCU_FCTL_TRACKDB__Accel__Get_Use());

	//load up the thresholding
	vFCU_ACCEL_THRESH__Set_Threshold(s32FCU_FCTL_TRACKDB__Accel__Get_Threshold_mm_ss(), s32FCU_FCTL_TRACKDB__Accel__Get_ThresholdTime_x10ms());


	//fwd laser

	//contrast laser

	//state machine options


	//track options


}


/////////////////////////////////////////////////////////////////////
//  Interlock command handling
/////////////////////////////////////////////////////////////////////


// Initialize an existing interlock command
void vFCU_FCTL__InterlockGuard__Init(strInterlockCommand *ic, Luint32 duration_ms)
{
	vFCU_FCTL__TIMEOUT__Init(&ic->commandTimeout, duration_ms);
	ic->enabled = 0U;
}

// Call this when the first packet is received. Ok to call it multiple times; it will just reset the timer.
void vFCU_FCTL__InterlockGuard__Unlock(strInterlockCommand *ic)
{
	ic->enabled = 1;
	vFCU_FCTL__TIMEOUT__Restart(&ic->commandTimeout);
}

// Call this when the second packet is received to check whether the command can execute (i.e. timeout has not expired)
Luint8 u8FCU_FCTL__InterlockGuard__IsUnlocked(strInterlockCommand *ic)
{
	Luint8 can_execute;

	// Note: I know this is not great code style but under time crunch
	if (ic->enabled && !u8FCU_FCTL__TIMEOUT__Is_Expired(&ic->commandTimeout))
	{
		can_execute = 1U;
	}
	else
	{
		can_execute = 0U;
	}
	return can_execute;
}


// Call this if the command was executed and we're ready to listen for the initial packet again
// @todo: do we even need this? if we receive another enable packet, we will restart the timeout. Once its timed out, it will not keep counting, so we're ok.
void vFCU_FCTL__InterlockGuard__Reset(strInterlockCommand *ic)
{
	// Reset the timeout (stop it and set the elapsed time to 0)
	vFCU_FCTL__TIMEOUT__Reset(&ic->commandTimeout);
}

// Call this in one of our timer ISRs. Ok to call this since the timeout has to be started for the update to have any effect.
void vFCU_FCTL__InterlockGuard__UpdateTimeout_x10ms(strInterlockCommand *ic, Luint8 time_ms)
{
	// Update the timeout
	vFCU_FCTL__TIMEOUT__Update_x10ms(&ic->commandTimeout);
}


// Convenience functions for interlocked commands

Luint8 vFCU_FCTL__NetCommand_IsUnlocked(TE_POD_COMMAND_T command)
{
	return u8FCU_FCTL__InterlockGuard__IsUnlocked(&sFCU.sStateMachine.command_interlocks[command]);
}


// Interlock command integration functions (depends on sFCU and state machine -- the functions above do not)
void vFCU_FCTL__NetCommand_Unlock(TE_POD_COMMAND_T command)
{
	vFCU_FCTL__InterlockGuard__Unlock(&sFCU.sStateMachine.command_interlocks[command]);
}

void vFCU_FCTL__PutCommand(TE_POD_COMMAND_T command)
{
	// Attempt to execute the command (provided that the interlock timeout has not expired)
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
		// do nothing
		break;
	}

}



#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

