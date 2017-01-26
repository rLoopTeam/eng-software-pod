/**
* @file       FCU__FCTL__EDDY_BRAKES.C
* @brief      Eddy Brakes Higher Level Control
* @author     Nazneen Khan, Marek Gutt-Mostowy
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
 * @addtogroup FCU__FLIGHT_CTL__EDDYBRAKES
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U

extern struct _strFCU sFCU;

//// GS comm packet types to add to fcu_core_net_packet_types.h
//NET_PKT__FCU_EDDYBRAKES__SET_DIR
//NET_PKT__FCU_EDDYBRAKES__SET_SPEED
//NET_PKT__FCU_EDDYBRAKES__SET_GROUP_DIR
//NET_PKT__FCU_EDDYBRAKES__SET_GROUP_SPEED
//NET_PKT__FCU_EDDYBRAKES__RELEASE_BRAKES
//NET_PKT__FCU_EDDYBRAKES__FULL_BRAKES
//
//// GS lift mech commands to add to fcu_core_net_rx.c:
//// assuming get actuator and value in u32blocks
//case NET_PKT__FCU_EDDYBRAKES__SET_DIR:
//	//set direction of specific eddy brake
//	#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U
//		if (sFCU.eMissionPhase != MISSION_PHASE__PUSH_INTERLOCK_PHASE)
//		{
//			E_FCU_FCTL_EDDYBRAKES_ACTUATOR actuator;
//			E_FCU_FCTL_EDDYBRAKES_DIRECTION dir;
//			switch(u32Block[0])
//			{
//				case 0:
//					actuator = EDDYBRAKES_Left;
//					break;
//				case 1:
//					actuator = EDDYBRAKES_Right;
//					break;
//				case default:
//					//report error
//					break;
//			}
//			switch(u32Block[1])
//			{
//				case 0:
//					dir = EDDYBRAKES_OUTWARD;
//					break;
//				case 1:
//					dir = EDDYBRAKES_INWARD;
//					break;
//				case default:
//					//report error
//					break;
//			}
//			vFCU_FCTL_EDDYBRAKES_Dir(actuator, dir);
//		}
//	#endif
//	break;
//
//case NET_PKT__FCU_EDDYBRAKES__SET_SPEED:
//	//set speed of specific eddy brake
//	#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U
//		if (sFCU.eMissionPhase != MISSION_PHASE__PUSH_INTERLOCK_PHASE)
//		{
//			E_FCU_FCTL_EDDYBRAKES_ACTUATOR actuator;
//			switch(u32Block[0])
//			{
//				case 0:
//					actuator = EDDYBRAKES_Left;
//					break;
//				case 1:
//					actuator = EDDYBRAKES_Right;
//					break;
//				case default:
//					//report error
//					break;
//			}
//			vFCU_FCTL_EDDYBRAKES_Speed(actuator, u32Block[1]);
//		}
//	#endif
//	break;
//
//case NET_PKT__FCU_EDDYBRAKES__SET_GROUP_DIR:
//	//set direction of both eddy brakes
//	#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U
//		if (sFCU.eMissionPhase != MISSION_PHASE__PUSH_INTERLOCK_PHASE)
//		{
//			E_FCU_FCTL_EDDYBRAKES_DIRECTION dir;
//			switch(u32Block[0])
//			{
//				case 0:
//					dir = EDDYBRAKES_OUTWARD;
//					break;
//				case 1:
//					dir = EDDYBRAKES_INWARD;
//					break;
//				case default:
//					//report error
//					break;
//			}
//			vFCU_FCTL_EDDYBRAKES__SetDirAll(dir);
//		}
//	#endif
//	break;
//
//case NET_PKT__FCU_EDDYBRAKES__SET_GROUP_SPEED:
//	//set speed of all both eddy brakes
//	#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U
//		if (sFCU.eMissionPhase != MISSION_PHASE__PUSH_INTERLOCK_PHASE)
//		{
//			vFCU_FCTL_EDDYBRAKES__SetSpeedAll(u32Block[0]);
//		}
//	#endif
//	break;
//case NET_PKT__FCU_EDDYBRAKES__RELEASE_BRAKES:
//	//release eddy brakes
//	#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U
//		vFCU_FCTL_EDDYBRAKES__Release();
//	#endif
//	break;
//case NET_PKT__FCU_EDDYBRAKES__FULL_BRAKES:
//	//apply full eddy brakes
//	#if C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES == 1U
//		vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes();
//	#endif
//	break;
//

// need to implement:
//vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake    // controlled full eddy brakes until speed < C_FCU__PODSPEED_STANDBY
//vFCU_FCTL_EDDY_BRAKES__GainScheduleController	// pid controller for brakes until position < C_FCU__POD_STOP_X_PO
//vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController		// pid controller for gimbals when speed < C_FCU__PODSPEED_MAX_SPEED_TO_STABILIZE
//u8FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp
//vFCU_FCTL_EDDYBRAKES_Dir
//vFCU_FCTL_EDDYBRAKES_Speed



// start of this module

void vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake()
{
	// controlled full eddy brakes until speed < C_FCU__PODSPEED_STANDBY
	// need a PID for this
}

void vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes(void)
{
	vFCU_FCTL_EDDYBRAKES__SetDirAll(EDDYBRAKES_INWARD);
	vFCU_FCTL_EDDYBRAKES__SetSpeedAll(C_FCU__EDDYBRAKES_NOM_APPL_SPEED); //todo add time
}



void vFCU_FCTL_EDDY_BRAKES__Release(void)
{
	vFCU_FCTL_EDDYBRAKES__SetDirAll(EDDYBRAKES_OUTWARD);
	vFCU_FCTL_EDDYBRAKES__SetSpeedAll(C_FCU__EDDYBRAKES_NOM_RELEASE_SPEED); //todo add time
}

void vFCU_FCTL_EDDY_BRAKES__GainScheduleController(Luint32 u32speed)
{
	// call Sean's controller
	// pid controller for brakes until position < C_FCU__POD_STOP_X_PO
	// pid controller should ensure eddy brakes are actuated symmetrically
}

void vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController(void)
{
	// call Adrian's controller
	// pid controller for gimbals when speed < C_FCU__PODSPEED_MAX_SPEED_TO_STABILIZE
	// pid controller should ensure eddy brakes are actuated symmetrically
}

Luint8 u8FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator)
{
	// lower level function to get stepper motor for the actuator specified
}

void vFCU_FCTL_EDDYBRAKES__SetDirAll(E_FCU__FCTL_EDDYBRAKES_DIRECTION dir)
{
	vFCU_FCTL_EDDYBRAKES_Dir(EDDYBRAKES_Left, dir);
	vFCU_FCTL_EDDYBRAKES_Dir(EDDYBRAKES_Right, dir);
}

void vFCU_FCTL_EDDYBRAKES__SetSpeedAll(Luint32 u32speed)
{
	vFCU_FCTL_EDDYBRAKES_Speed(EDDYBRAKES_Left, u32speed);
	vFCU_FCTL_EDDYBRAKES_Speed(EDDYBRAKES_Right, u32speed);
}

void vFCU_FCTL_EDDYBRAKES_Dir(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator, E_FCU__FCTL_EDDYBRAKES_DIRECTION dir)
{
	// need to interface with lower level stuff here
}

void vFCU_FCTL_EDDYBRAKES_Speed(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator, Luint32 u32speed)
{
	// need to interface with lower level stuff here
}
void vFCU_FCTL_EDDYBRAKES__Get_State(void)
{
	//TODO:IMPLEMENT THIS
}

Luint32 u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(void)
{
	//TODO:IMPLEMENT THIS
}

#endif //C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL
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
