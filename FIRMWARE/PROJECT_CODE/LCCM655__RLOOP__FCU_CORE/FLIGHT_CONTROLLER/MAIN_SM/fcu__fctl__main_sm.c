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

//TODO: need the following function implemented

//u32FCU_FCTL_NAV__PodSpeed();
//u32FCU_FCTL_NAV__GetFrontPos();
//u32FCU_FCTL_NAV__GetRearPos();
//u32FCU_FCTL_NAV__PodSpeed();
//u32FCU_FCTL_LASERORIENT__Get_Z_Pos()
//u32LandingGearMLPLeftAftValue = u32FCU_LGU__Get_MLP_Value(Luint8 u8Counter);

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		5224534176289DBD9FF1B39936308C7E
 * @st_funcID		LCCM655R0.FILE.020.FUNC.001
 */
void vFCU_FCTL_MAINSM__Init(void)
{
	sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__RESET;

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
	Luint8 u8Counter;
	Luint8 u8Test;
	Luint8 u8TestsSuccesful;
	Lint32 u32Accelmmss;
	Luint32 u32PodSpeed;
	Luint8 ePusherState;
	Luint32 u32PodRearPos;

	//handle the state machine.
	switch(sFCU.sStateMachine.eMissionPhase)
	{

		case MISSION_PHASE__RESET:
			//we have just come out of reset here.
			//init our rPod specific systems

			#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U
				vFCU_PODHEALTH__Init();
			#endif
			//init the auto sequence
			vFCU_MAINSM_AUTO__Init();

			//pusher
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vFCU_PUSHER__Init();
			#endif

			//laser contrast sensors
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
				vFCU_LASERCONT__Init();
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

			//PiComms Layer
			#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
				vFCU_PICOMMS__Init();
			#endif

			//finally init the flight controller
			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
				vFCU_FCTL__Init();
			#endif


			#if C_LOCALDEF__LCCM655__ENABLE_GEOM == 1U
				vFCU_GEOM__Init();
			#endif //C_LOCALDEF__LCCM655__ENABLE_GEOM

			//put the flight computer into startup mode now that everything has been initted.
			sFCU.sStateMachine.eMissionPhase = MISSION_PHASE__DEBUG; //MISSION_PHASE__TEST;

			break;


		case MISSION_PHASE__DEBUG:

			break;

		default:
			//should not get here
			break;

	}//switch(sFCU.eRunState)

	//always process these items after we have been initted
	if(sFCU.sStateMachine.eMissionPhase > MISSION_PHASE__RESET)
	{
		#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U
			vFCU_PODHEALTH__Process();
		#endif

		//LG
		vFCU_FCTL__Process();

		//process the SC16IS interface always
		#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
			{
				vSIL3_SC16__Process(u8Counter);
			}
		#endif

		// process the AMC7812
		// process the throttles
		#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
			vFCU_THROTTLE__Process();
			vAMC7812__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
			vFCU_LASEROPTO__Process();
		#endif

		//laser orientation
		#if C_LOCALDEF__LCCM655__ENABLE_ORIENTATION == 1U
			vFCU_LASER_ORIENTATION__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
			vFCU_LASERCONT__Process();
		#endif


		#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
			vFCU_PUSHER__Process();
		#endif

		//process the brakes.
		#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
			vFCU_BRAKES__Process();
		#endif

		//process the accel channels
		#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
			vFCU_ACCEL__Process();
		#endif

		//ASI RS485 interface
		#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
			vFCU_ASI__Process();
		#endif

		#if C_LOCALDEF__LCCM655__ENABLE_GEOM == 1U
			vFCU_GEOM__Process();
		#endif
		//Start the Hover Engine Control
		#if C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL == 1U
			vFCU_FCTL_HOVERENGINES__Process();
		#endif
	}
	else
	{
		//do nothing.
	}


}


void vFCU_FCTL_MAINSM__10MS_ISR(void)
{

}

void vFCU_FCTL_MAINSM__100MS_ISR(void)
{

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

