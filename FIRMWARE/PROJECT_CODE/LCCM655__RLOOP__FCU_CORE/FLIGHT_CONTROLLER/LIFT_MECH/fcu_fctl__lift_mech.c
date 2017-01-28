/**
* @file       FCU__FCTL__LIFT_MECH.C
* @brief      Lift Mechanism Control
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
 * @addtogroup FCU__FLIGHT_CTL__LIFTMECH
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL == 1U

extern struct _strFCU sFCU;

// need to implement these functions
//vFCU_FCTL_LIFTMECH_Get_MLP
//vFCU_FCTL_LIFTMECH_Dir
//vFCU_FCTL_LIFTMECH_Speed

// start of this module
void vFCU_FCTL_LIFTMECH__Extend(void)
{
	// Check whether we are in the Test Phase or the Post Run Phase
	if ((sFCU.sStateMachine.eMissionPhase == MISSION_PHASE__TEST) || (sFCU.sStateMachine.eMissionPhase == MISSION_PHASE__POST_RUN))
	{
		//Get current Pod Speed
		Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
		//Check if we are Lifted and still stationary
		if (sFCU.sStateMachine.sOpStates.u8Lifted && (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
		{
			//TODO:REVIEW CONFLUENCE SPECCS
//			//Set The Lift Mechanism Actuators UP, so that we can retract them
//			vFCU_FCTL_LIFTMECH__SetDirAll(LIFTMECH_DIR_UP);
//			vFCU_FCTL_LIFTMECH__SetSpeedAll(C_FCU__LIFTMECH_ACTUATOR_NOM_UNLIFT_SPEED);
//
//			Luint8 u8Unlifted = u8FCU_FCTL_MAINSM__CheckIfUnlifted();
//			if(u8Unlifted == 1U)
//			{
//				vFCU_FCTL_LIFTMECH__SetSpeedAll(0);
//			}
//			else
//			{
//				vFCU_FCTL_LIFTMECH__SetSpeedAll(C_FCU__LIFTMECH_ACTUATOR_NOM_UNLIFT_SPEED);
//			}
		}
		else
		{
		//do nothing
		}
	}
}

Luint32 u32FCU_FCTL_LIFTMECH__Get_MLP(void)
{
	// report MLP distance
	// add lower level function for this
	// not sure how to combine 4 values into one
	//TODO: return
}

void vFCU_FCTL_LIFTMECH__SetDirAll(E_FCU__LIFTMECH_DIRECTION dir)
{
	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_AftLeft, dir);
	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_AftRight, dir);
	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_ForwardLeft, dir);
	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_ForwardRight, dir);
}

void vFCU_FCTL_LIFTMECH__SetSpeedAll(Luint32 u32speed)
{
	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_AftLeft, u32speed);
	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_AftRight, u32speed);
	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_ForwardLeft, u32speed);
	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_ForwardRight, u32speed);
}

void vFCU_FCTL_LIFTMECH_Dir(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir)
{
//interface with lower level
}

void vFCU_FCTL_LIFTMECH_Speed(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir)
{
//interface with lower level
}

E_FCU_LIFTMECH_STATE eFCU_FCTL_LIFTMECH__Get_State(void)
{
	//implement this one
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
