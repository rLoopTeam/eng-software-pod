/**
 * @file		FCU__MAIN_SM.C
 * @brief		Main state machine for the flight control unit
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
 * @addtogroup FCU__MAIN_SM
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_MAINSM__Init(void)
{
	sFCU.eRunState = RUN_STATE__RESET;

}


/***************************************************************************//**
 * @brief
 * Process the main state machine
 * 
 */
void vFCU_MAINSM__Process(void)
{

	//hande the state machine.
	switch(sFCU.eRunState)
	{

		case RUN_STATE__RESET:
			//we have just come out of reset here.

			//change state.
			sFCU.eRunState = RUN_STATE__INIT_SYSTEMS;
			break;

		case RUN_STATE__INIT_SYSTEMS:
			//init our rPod specific systems

			//init the brake systems
			vFCU_BRAKES__Init();

			//Init the throttles
			vFCU_THROTTLE__Init();

			//init the ASI RS485 interface
			vFCU_ASI__Init();

			//init the acclerometer system
			vFCU_ACCEL__Init();

			//laser opto's

			//laser distance

			//laser contrast

			//PiComms Layer
			#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
				vFCU_PICOMMS__Init();
			#endif


			break;

		case RUN_STATE__STARTUP_MODE:
			//run what we need to in startup mode, checkout sensors and other diagnostics
			break;

		case RUN_STATE__FLIGHT_MODE:
			//this is the flight mode controller
			break;
	}

	//always process pi comms
	#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
	if(sFCU.eRunState > RUN_STATE__RESET)
	{
		//process the pi comss
		vFCU_PICOMMS__Process();
	}
	else
	{
		//do nothing.
	}

	#endif

}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

