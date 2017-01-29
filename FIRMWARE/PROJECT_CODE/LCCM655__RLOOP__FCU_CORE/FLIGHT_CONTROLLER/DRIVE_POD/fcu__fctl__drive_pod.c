/**
* @file       FCU__FCTRL__POD_DRIVE.C
* @brief      Pod Drive Control
* @author	  Nazneen Khan, Marek Gutt-Mostowy
* @copyright  rLoop Inc.
*/
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__FLIGHT_CTL__DRIVEPOD
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL == 1U

extern struct _strFCU sFCU;

void vFCU_FCTL_DRIVEPOD__Init(void)
{
	sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_INITIAL_STATE;
	sFCU.sDrivePod.u8IsBrakesInhibitedInPreRunPhase = 0;
	sFCU.sDrivePod.u8IsBrakesInhibitedInPusherInterlockPhase = 0;
	sFCU.sDrivePod.u8startedPreRunAction = 0;
	sFCU.sDrivePod.u8startedPostRunAction = 0;
}

void vFCU_FCTL_DRIVEPOD__Stop(void)
{
	vFCU_FCTL_HOVERENGINES__Stop();
	vFCU_FCTL_AUX_PROP__Stop();
}

void vFCU_FCTL_DRIVEPOD__Process(void)
{

	switch(sFCU.sStateMachine.eMissionPhase)
	{
		Luint32 u32PodSpeed;
		Luint32 u32PodPos;

		case MISSION_PHASE__TEST:
			// Confirm that our GS comm timer is not greater than 2 sec, else proceed with stop
			if (u8FCU_FCTL_DRIVEPOD__LossOfComm())
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			else
			{
				//do nothing
			}
			break;

		case MISSION_PHASE__PRE_RUN:
			// release brakes regardless of anything, once
			if (sFCU.sDrivePod.u8IsBrakesInhibitedInPreRunPhase == 0)
			{
				vFCU_FCTL_EDDY_BRAKES__Release();	// TODO: make sure this is implemented
				sFCU.sDrivePod.u8IsBrakesInhibitedInPreRunPhase = 1;	// indicate we started the action
			}
			// Confirm that our GS comm timer is not greater than 2 sec, else proceed with stop
			if (u8FCU_FCTL_DRIVEPOD__LossOfComm())
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			else
			{
				switch(sFCU.sDrivePod.ePreRunState)
				{
					case DRIVEPOD_PRERUN_INITIAL_STATE:   // TODO: confirm with ground station if PRERUN command is implemented
						if (sFCU.sDrivePod.u8startedPreRunAction == 0)
						{
							sFCU.sDrivePod.u8100MS_Timer = 0;
							sFCU.sDrivePod.u8startedPreRunAction = 1;	// indicate we started the action
						}
						u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
						if (/*sFCU.sStateMachine.sOpStates.u8Lifted &&*/ (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
						{
							sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_START_HE_STATE;
							sFCU.sDrivePod.u8startedPreRunAction = 0;
							sFCU.sDrivePod.u8100MS_Timer = 0; // action was successful
						}
						else
						{
							//do nothing
						}
						// If we are in this state more than 10 sec, send error to GS command
						if (sFCU.sDrivePod.u8100MS_Timer >= 100)
						{
							// TODO: report error to ground station
							// exit?
						}
						else
						{
							//do nothing
						}
						break;
					case DRIVEPOD_PRERUN_START_HE_STATE:
						// Confirm that we do this only once in this state
						if (sFCU.sDrivePod.u8startedPreRunAction == 0)
						{
							vFCU_FCTL_HOVERENGINES__Start();
							sFCU.sDrivePod.u8100MS_Timer = 0;
							sFCU.sDrivePod.u8startedPreRunAction = 1;
						}

						if (eFCU_FCTL_HOVERENGINES__Get_State() == HOVERENGINES_STATE__HOVERING)
						{
							sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_RETRACT_LIFTMECH;
							sFCU.sDrivePod.u8startedPreRunAction = 0;
							sFCU.sDrivePod.u8100MS_Timer = 0;
						}
						else
						{
							//do nothing
						}

						// If we are in this state more than 10 sec, send error to GS command
						if (sFCU.sDrivePod.u8100MS_Timer >= 100)
						{
							// TODO: report error to ground station
							// exit?
						}
						else
						{
							//do nothing
						}

						break;
					case DRIVEPOD_PRERUN_RETRACT_LIFTMECH:
						// Confirm that we do this only once in this state
						if (sFCU.sDrivePod.u8startedPreRunAction == 0)
						{
							vFCU_FCTL_LIFTMECH__RetractAll();
							sFCU.sDrivePod.u8100MS_Timer = 0;
							sFCU.sDrivePod.u8startedPreRunAction = 1;

						}
						// no need to do anything else for this mission state
						//if (u8FCU_FCTL_LIFTMECH__IsRetracted())
						//{
						//}
//						if (sFCU.sDrivePod.u8100MS_Timer >= 100)
//						{
//							// TODO: report error to ground station
//							// exit?
//						}
//						break;
//					case DRIVEPOD_PRERUN_GIMBAL_BACKWARD:
//
//						if (sFCU.sDrivePod.u8100MS_Timer == 0)
//						{
//							vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_BACKWARD_LEVEL);
//						}
//						if (u8FCU_PUSHER__Get_PusherState() == 1U)	// connected to pusher
//						{
//							sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_GIMBAL_MAINTAIN;
//							sFCU.sDrivePod.u8100MS_Timer = 0;
//						}
//						if (sFCU.sDrivePod.u8100MS_Timer >= 100)
//						{
//							// TODO: report error to ground station
//							// exit?
//						}
//						break;
//					case DRIVEPOD_PRERUN_GIMBAL_MAINTAIN:
//
//						// maintain gimbal: do nothing, we are already gimbaling backward
//						break;
				}
			}
			break;

		case MISSION_PHASE__PUSHER_INTERLOCK:
			// release brakes (should be the case already but we do it again once in case brakes were manually triggered during pre-run phase
			if (sFCU.sDrivePod.u8IsBrakesInhibitedInPusherInterlockPhase == 0)
			{
				vFCU_FCTL_EDDY_BRAKES__Release();	// TODO: make sure this is implemented
				sFCU.sDrivePod.u8IsBrakesInhibitedInPusherInterlockPhase = 1;	// indicate we started the action
			}
			// vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_NEUTRAL_LEVEL);
			break;

		case MISSION_PHASE__FLIGHT:

			if (eFCU_FCTL_EDDY_BRAKES__Get_State() != EDDY_BRAKES_STATE__CONTROLLED_BRAKING)
			{
				u32PodPos = u32FCU_FCTL_NAV__GetFrontPos();
				u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

				//TODO: Check if the watchdog failure should be in
				if ((sFCU.sDrivePod.eGSCommand == DRIVEPOD_GS_POD_STOP) ||
						vFCU_FCTL_EDDY_BRAKES__GetPodSpeedTooHigh() ||
						(u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(EDDY_BRAKES_Left) > C_FCU__EDDY_BRAKES_STEPPER_MOTOR_MAX_TEMP) ||
						(u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(EDDY_BRAKES_Right) > C_FCU__EDDY_BRAKES_STEPPER_MOTOR_MAX_TEMP))
				{
					// controlled emergency breaking
					vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake();  // add full eddy brakes until speed < C_FCU__NAV_PODSPEED_STANDBY
				}
				else
				{
	//				vFCU_FCTL_EDDY_BRAKES__GainScheduleController(u32PodSpeed);	// pid controller for brakes until position < C_FCU__POD_STOP_X_POS
	//
	////				if (u32PodSpeed >= C_FCU__NAV_PODSPEED_MAX_SPEED_TO_STABILIZE)
	////				{
	////					vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_NEUTRAL_LEVEL);
	////				}
	////				else
	////				{
	////					vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController();	// pid controller for gimbals when speed < C_FCU__PODSPEED_MAX_SPEED_TO_STABILIZE
	////				}
				}
			}
			break;

		case MISSION_PHASE__POST_RUN:
			if (sFCU.sDrivePod.u8startedPostRunAction == 0)
			{
				//Luint32 u32PodPos = u32FCU_FCTL_NAV__GetFrontPos();
				//Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
				//TODO:  do we need to do deploy here
				//vFCU_FCTL_LIFTMECH__DeployAll

				vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes();
				vFCU_FCTL_HOVERENGINES__Stop();
//				if ((C_FCU__POD_STOP_X_POS - u32PodPos) > C_FCU__POD_TARGET_POINT_MARGIN_POS)
//				{
//					vFCU_FCTL_EDDY_BRAKES__Release();
//					vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController();	// until reach target position
//					vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes();
//				}
//				else if (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
//				{
//					vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_NEUTRAL_LEVEL);
//					vFCU_FCTL_HOVERENGINES__Stop();
//				}
				sFCU.sDrivePod.u8startedPostRunAction = 1;	// indicate we started the action
			}

			// Confirm that our GS comm timer is not greater than 2 sec, else proceed with stop
			if (u8FCU_FCTL_DRIVEPOD__LossOfComm())
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			break;
	}
}

Luint8 u8FCU_FCTL_DRIVEPOD__LossOfComm(void)
{
	Luint8 u8LossOfComm;
	if (sFCU.sUDPDiag.u32_10MS_GS_COMM_Timer > 200U)
	{
		u8LossOfComm = 1U;
	}
	else
	{
		u8LossOfComm = 0U;
	}
	return u8LossOfComm;
}

void vFCU_FCTL_DRIVEPOD__SetPodStopCmd(void)
{
	sFCU.sDrivePod.eGSCommand = DRIVEPOD_GS_POD_STOP;
}

void vFCU_FCTL_DRIVEPOD__100MS_ISR(void)
{
	sFCU.sDrivePod.u8100MS_Timer++;
}
void vFCU_FCTL_DRIVEPOD__10MS_ISR(void)
{
	sFCU.sUDPDiag.u32_10MS_GS_COMM_Timer++;
}

void vFCU_FCTL_DRIVEPOD__Reset_GSCommTimer(void)
{
	sFCU.sUDPDiag.u32_10MS_GS_COMM_Timer = 0;
}



#endif //C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL
	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

