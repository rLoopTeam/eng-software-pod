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
	Luint8 u8Counter;

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

			//pusher
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vFCU_PUSHER__Init();
			#endif

			//init the brake systems
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vFCU_BRAKES__Init();
			#endif

			//Init the throttles
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
				vFCU_THROTTLE__Init();
			#endif

			//init the ASI RS485 interface
			#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
				vFCU_ASI__Init();
			#endif

			//init the acclerometer system
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL__Init();
			#endif

			//laser opto's
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
				vFCU_LASEROPTO__Init();
			#endif

			//laser distance

			//laser contrast

			//PiComms Layer
			#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
				vFCU_PICOMMS__Init();
			#endif

			//put the flight computer into startup mode now that everything has been initted.
			sFCU.eRunState = RUN_STATE__STARTUP_MODE;

			break;

		case RUN_STATE__STARTUP_MODE:
			//run what we need to in startup mode, checkout sensors and other diagnostics
			break;

		case RUN_STATE__FLIGHT_MODE:
			//this is the flight mode controller
			break;

	}//switch(sFCU.eRunState)

	//always process these items
	if(sFCU.eRunState > RUN_STATE__RESET)
	{
		//process the SC16IS interface always
		for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
		{
			vSC16__Process(u8Counter);
		}

		#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
			vFCU_LASEROPTO__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
			vFCU_PUSHER__Pusher();
		#endif

		//process the brakes.
		#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
			vFCU_BRAKES__Process();
		#endif

		//process the accel channels
		#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
			vFCU_ACCEL__Process();
		#endif

		//process any Pi Comms
		#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
			vFCU_PICOMMS__Process();
		#endif
	}
	else
	{
		//do nothing.
	}


}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

