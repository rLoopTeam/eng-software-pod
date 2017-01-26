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

// TODO: need the following functions:
//vFCU_FCTL_AUX_PROP__Stop()
//vFCU_FCTL_AUX_PROP__Disable()
//vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_BACKWARD_LEVEL/GIMBAL_NEUTRAL_LEVEL/GIMBAL_FORWARD_LEVEL)
//vFCU_FCTL_NAV__GetFrontPos()
//u32FCU_FCTL_NAV__PodSpeed()
//vFCU_NET_RX__GetGsCommTimer()
//u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(EDDYBRAKES_Left)

void vFCU_FCTL_DRIVEPOD__Stop(void)
{
	vFCU_FCTL_HOVERENGINES__Stop();
	vFCU_FCTL_AUX_PROP__Stop();
	vFCU_FCTL_AUX_PROP__Disable();
}

void vFCU_FCTL_DRIVEPOD__Process(void)
{

	switch(sFCU.sStateMachine.eMissionPhase)
	{
		Luint32 u32PodSpeed;
		Luint32 u32PodPos;
		Luint8 u8PodSpeedTooHigh;

		case MISSION_PHASE__TEST:
			if (vFCU_NET_RX__GetGsCommTimer() > C_FCU__GS_COMM_LOSS_DELAY)
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			else
			{
				//do nothing
			}
			break;

		case MISSION_PHASE__PRE_RUN:

			if (vFCU_NET_RX__GetGsCommTimer() > C_FCU__GS_COMM_LOSS_DELAY)
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			else
			{
				switch(sFCU.sDrivePod.ePreRunState)
				{
					case DRIVEPOD_PRERUN_INITIAL_STATE:

						if (sFCU.sDrivePod.u8100MS_Timer == 0)
						{
							vFCU_FCTL_EDDY_BRAKES__Release();
						}
						else
						{
							//do nothing
						}
						u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
						if (sFCU.sStateMachine.sOpStates.u8Lifted && (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
						{
							sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_START_HE_STATE;
							sFCU.sDrivePod.u8100MS_Timer = 0;
						}
						else
						{
							//do nothing
						}
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

						if (sFCU.sDrivePod.u8100MS_Timer == 0)
						{
							vFCU_FCTL_HOVERENGINES__Start();
						}
						else
						{
							//do nothing;
						}

						if (eFCU_FCTL_HOVERENGINES__Get_State() == HOVERENGINES_STATE__HOVERING)
						{
							sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_RETRACT_LIFTMECH;
							sFCU.sDrivePod.u8100MS_Timer = 0;
						}
						else
						{
							//do nothing
						}

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

						if (sFCU.sDrivePod.u8100MS_Timer == 0)
						{
							//TODO: DEFINE ENUM FOR THE LIFTMECH
							vFCU_FCTL_LIFTMECH__SetDirAll(0); //SET DIRECTION UP
							vFCU_FCTL_LIFTMECH__SetSpeedAll(C_FCU__LIFTMECH_ACTUATOR_NOM_UNLIFT_SPEED);
						}
						if (vFCU_FCTL_LIFTMECH__Get_State() == LIFT_MECH_STATE__RETRACTED)
						{
//							sFCU.sDrivePod.ePreRunState = DRIVEPOD_PRERUN_GIMBAL_BACKWARD;
							sFCU.sDrivePod.u8100MS_Timer = 0;
						}
						if (sFCU.sDrivePod.u8100MS_Timer >= 100)
						{
							// TODO: report error to ground station
							// exit?
						}
						break;
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
			if (vFCU_NET_RX__GetGsCommTimer() > C_FCU__GS_COMM_LOSS_DELAY)
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			else
			{
				vFCU_FCTL_EDDY_BRAKES__Release();
				// vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_NEUTRAL_LEVEL);
			}
			break;

		case MISSION_PHASE__FLIGHT:

			u32PodPos = u32FCU_FCTL_NAV__GetFrontPos();
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			u8PodSpeedTooHigh = u8FCU_FCTL_NAV__GetPodSpeedTooHigh();

			//TODO: Check if the watchdog failure should be in
			if ((sFCU.sDrivePod.eGSCommand == DRIVEPOD_GS_POD_STOP) || (u32PodSpeed > u8PodSpeedTooHigh) || ((u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(EDDYBRAKES_Left) > C_FCU__EDDYBRAKES_STEPPER_MOTOR_MAX_TEMP)) || ((u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(EDDYBRAKES_Right) > C_FCU__EDDYBRAKES_STEPPER_MOTOR_MAX_TEMP)))
			{
				// controlled emergency breaking
				vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake();  // add full eddy brakes until speed < C_FCU__NAV_PODSPEED_STANDBY
			}
			else
			{
				vFCU_FCTL_EDDY_BRAKES__GainScheduleController(u32PodSpeed);	// pid controller for brakes until position < C_FCU__POD_STOP_X_POS

//				if (u32PodSpeed >= C_FCU__NAV_PODSPEED_MAX_SPEED_TO_STABILIZE)
//				{
//					vFCU_FCTL_GIMBAL__SetLevel(GIMBAL_NEUTRAL_LEVEL);
//				}
//				else
//				{
//					vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController();	// pid controller for gimbals when speed < C_FCU__PODSPEED_MAX_SPEED_TO_STABILIZE
//				}
			}
			break;

		case MISSION_PHASE__POST_RUN:
			// TODO: need to rethink this part if hover engines are not running in this phase
			if (vFCU_NET_RX__GetGsCommTimer() > C_FCU__GS_COMM_LOSS_DELAY)
			{
				vFCU_FCTL_DRIVEPOD__Stop();
			}
			else
			{
				Luint32 u32PodPos = u32FCU_FCTL_NAV__GetFrontPos();
				Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

				vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes();
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
			}
			break;
	}
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

void vFCU_NET_RX__GetGsCommTimer(void)
{
return sFCU.sUDPDiag.u32_10MS_GS_COMM_Timer;
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

