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


void vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake()
{
	// controlled full eddy brakes until speed < C_FCU__PODSPEED_STANDBY
	// need a PID for this
}

void vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes(void)
{
	vFCU_FCTL_EDDY_BRAKES__SetDirAll(EDDYBRAKES_INWARD);
	vFCU_FCTL_EDDY_BRAKES__SetSpeedAll(C_FCU__EDDYBRAKES_NOM_APPL_SPEED); //todo add time
}



void vFCU_FCTL_EDDY_BRAKES__Release(void)
{
	vFCU_FCTL_EDDY_BRAKES__SetDirAll(EDDYBRAKES_OUTWARD);
	vFCU_FCTL_EDDY_BRAKES__SetSpeedAll(C_FCU__EDDYBRAKES_NOM_RELEASE_SPEED); //todo add time
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

//Luint8 u8FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator)
//{
//	// lower level function to get stepper motor for the actuator specified
//}

void vFCU_FCTL_EDDY_BRAKES__SetDirAll(E_FCU__FCTL_EDDYBRAKES_DIRECTION dir)
{
//	vFCU_FCTL_EDDY_BRAKES_Dir(EDDYBRAKES_Left, dir);
//	vFCU_FCTL_EDDY_BRAKES_Dir(EDDYBRAKES_Right, dir);
}

void vFCU_FCTL_EDDY_BRAKES__SetSpeedAll(Luint32 u32speed)
{
//	vFCU_FCTL_EDDY_BRAKES_Speed(EDDYBRAKES_Left, u32speed);
//	vFCU_FCTL_EDDY_BRAKES_Speed(EDDYBRAKES_Right, u32speed);
}

void vFCU_FCTL_EDDY_BRAKES_Dir(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator, E_FCU__FCTL_EDDYBRAKES_DIRECTION dir)
{
	// need to interface with lower level stuff here
}

void vFCU_FCTL_EDDY_BRAKES_Speed(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator, Luint32 u32speed)
{
	// need to interface with lower level stuff here
}
E_FCU__FCTL_EDDYBRAKES_STATE eFCU_FCTL_EDDY_BRAKES__Get_State(void)
{
	//TODO:IMPLEMENT THIS
	E_FCU__FCTL_EDDYBRAKES_STATE eEDDYBRAKES_STATE;
	eEDDYBRAKES_STATE = EDDYBRAKES_STATE__RETRACTED;
	return eEDDYBRAKES_STATE;
}

Luint32 u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp(void)
{
	//TODO:IMPLEMENT THIS
	return 0;
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
