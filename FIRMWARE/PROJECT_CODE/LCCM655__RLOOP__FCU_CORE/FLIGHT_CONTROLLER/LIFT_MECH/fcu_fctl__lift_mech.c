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


// start of this module
//void vFCU_FCTL_LIFTMECH__Extend(void)
//{
//	// Check whether we are in the Test Phase or the Post Run Phase
//	if ((sFCU.sStateMachine.eMissionPhase == MISSION_PHASE__TEST) || (sFCU.sStateMachine.eMissionPhase == MISSION_PHASE__POST_RUN))
//	{
//		//Get current Pod Speed
//		Luint32 u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
//		//Check if we are Lifted and still stationary
//		if (sFCU.sStateMachine.sOpStates.u8Lifted && (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
//		{
//			//TODO:REVIEW CONFLUENCE SPECCS
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
//		}
//		else
//		{
//		//do nothing
//		}
//	}
//}
//
//Luint32 u32FCU_FCTL_LIFTMECH__Get_MLP(void)
//{
//	// report MLP distance
//	// add lower level function for this
//	// not sure how to combine 4 values into one
//	//TODO: return
//	return 0U;
//}
//void vFCU_FCTL_LIFTMECH__Dir(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir)
//{
//		// TODO: lower level function
//}

//void vFCU_FCTL_LIFTMECH__SetDirAll(E_FCU__LIFTMECH_DIRECTION dir)
//{
//	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_AftLeft, dir);
//	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_AftRight, dir);
//	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_ForwardLeft, dir);
//	vFCU_FCTL_LIFTMECH_Dir(LIFTMECH_ForwardRight, dir);
//	sFCU.sLiftMech.u8DirSet = 1;
//}

//void vFCU_FCTL_LIFTMECH__SetSpeedAll(Luint32 u32speed)
//{
//	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_AftLeft, u32speed);
//	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_AftRight, u32speed);
//	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_ForwardLeft, u32speed);
//	vFCU_FCTL_LIFTMECH_Speed(LIFTMECH_ForwardRight, u32speed);
//}


//void vFCU_FCTL_LIFTMECH_Speed(E_FCU__LIFTMECH_ACTUATOR actuator, Luint32 speed)
//{
//interface with lower level
//}


void vFCU_FCTL_LIFTMECH__Deploy(E_FCU__LIFTMECH_ACTUATOR actuator)
{
	// put wheels down
	// TODO: lower level function to deploy, set direction to down
}

void vFCU_FCTL_LIFTMECH__DeployAll(void)
{
	vFCU_FCTL_LIFTMECH__Deploy(LIFTMECH_AftLeft);
	vFCU_FCTL_LIFTMECH__Deploy(LIFTMECH_AftRight);
	vFCU_FCTL_LIFTMECH__Deploy(LIFTMECH_ForwardLeft);
	vFCU_FCTL_LIFTMECH__Deploy(LIFTMECH_ForwardRight);
	sFCU.sLiftMech.u8100MS_Timer = 0;
}

void vFCU_FCTL_LIFTMECH__Retract(E_FCU__LIFTMECH_ACTUATOR actuator)
{
	// put wheels up
	// TODO: lower level function to retract
}

void vFCU_FCTL_LIFTMECH__RetractAll(void)
{
	vFCU_FCTL_LIFTMECH__Retract(LIFTMECH_AftLeft);
	vFCU_FCTL_LIFTMECH__Retract(LIFTMECH_AftRight);
	vFCU_FCTL_LIFTMECH__Retract(LIFTMECH_ForwardLeft);
	vFCU_FCTL_LIFTMECH__Retract(LIFTMECH_ForwardRight);
	sFCU.sLiftMech.u8100MS_Timer = 0;
}

Luint8 u8FCU_FCTL_LIFTMECH__IsRetracted(void)
{
	Luint8 isRetracted = 0;
	if (sFCU.sLiftMech.u8100MS_Timer > 150)
	{
		isRetracted = 1;
	}
	return isRetracted;

}

Luint8 u8FCU_FCTL_LIFTMECH__IsLifted(void)
{
	Luint8 isLifted = 0;
	if (sFCU.sLiftMech.u8100MS_Timer > 150)
	{
		isLifted = 1;
	}
	return isLifted;

}


//E_FCU_LIFTMECH_STATE eFCU_FCTL_LIFTMECH__Get_State(void)
//{
	//implement this one
//	E_FCU_LIFTMECH_STATE eLIFTMECH_STATE;
//	eLIFTMECH_STATE = LIFT_MECH_STATE__RETRACTED;
//	return eLIFTMECH_STATE;
//}

void vFCU_FCTL_LIFTMECH__100MS_ISR(void)
{
	sFCU.sLiftMech.u8100MS_Timer++;
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
