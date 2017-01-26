/**
* @file       FCU__FCTL__AUX_PROPULSION.C
* @brief      Pod drive control
* @author	  Paul Le Henaff
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
 * @addtogroup FCU__FLIGHT_CTL__AUX_PROPULSION
 * @ingroup FCU
 * @{ */

/*
4.1. Enable Auxiliary Propulsion
Upon reception of Enable Auxiliary Propulsion command from Ground Station, if the mission phase is:
- test phase, 
- pre-run phase 
- post-run phase 
and if all hover engine RPM feedback are 0, then the FCU shall set aux prop enabled to true.

# receive enable command
#	if phase == (test || prerun || postrun) && all rpm == 0
#		aux prop enable = true

4.2. Disable Auxiliary Propulsion
Upon reception of Disable Auxiliary Propulsion command from Ground Station, then the FCU shall set aux prop enabled to false.
If the mission phase is different from test phase, pre-run phase or post-run phase, then the FCU shall automatically set aux prop enabled to false.

# receive disable command
#	aux prop enable = false

# state machine:
# if phase != (test || prerun || postrun)
#	aux prop enable = false

4.3. Drive Pod with Auxiliary Propulsion
Upon reception of Auxiliary Propuslion Speed from Ground Station, if aux prop enabled is true, then the FCU shall command this speed to each auxiliary propulsion motor (to be detailed).
If the rPod is being propelled by its auxiliary propulsion, the Ground Station may command the rPod to disable the auxiliary propulsion (Nominal mode: Disable Auxiliary Propulsion). This will render any auxiliary propulsion speed values ineffective and the rPod will come to a full stop by inertial forces.
*/

// MY CODE
#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_AUX_PROPULSION_CONTROL == 1U

extern struct _strFCU sFCU;

//// TODO: add struct to fcu_core.h inside of _strFCU:
//#if C_LOCALDEF__LCCM655__ENABLE_AUX_PROPULSION_CONTROL == 1U
//struct
//{
//	Luint8 u8AuxPropulsionEnabled;
//}sAuxPropulsion;
//#endif
//
//// add to fcu_core_defines.h in aux propulsion section:
//#define C_FCU__AUX_PROPULSION_NUM_MOTORS
//
//void vFCU_FLIGHTCTL_AUX_PROPULSION__Enable(void)
//{
//	Luint16 pu16HE0RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(0, &pu16HE0RPM);
//	Luint16 pu16HE1RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(1, &pu16HE1RPM);
//	Luint16 pu16HE2RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(2, &pu16HE2RPM);
//	Luint16 pu16HE3RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(3, &pu16HE3RPM);
//	Luint16 pu16HE4RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(4, &pu16HE4RPM);
//	Luint16 pu16HE5RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(5, &pu16HE5RPM);
//	Luint16 pu16HE6RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(6, &pu16HE6RPM);
//	Luint16 pu16HE7RPM = 0U;
//	s16FCU_ASI_CTRL__ReadMotorRpm(7, &pu16HE7RPM);
//
//	// if all engines have RPM 0 then enable the aux propulsion
//	if ((sFCU.eMissionPhase == MISSION_PHASE__TEST_PHASE ||
//			sFCU.eMissionPhase == MISSION_PHASE__PRE_RUN_PHASE ||
//			sFCU.eMissionPhase == MISSION_PHASE__POST_RUN) &&
//		u16HE0RPM == 0U &&
//		u16HE1RPM == 0U &&
//		u16HE2RPM == 0U &&
//		u16HE3RPM == 0U &&
//		u16HE4RPM == 0U &&
//		u16HE5RPM == 0U &&
//		u16HE6RPM == 0U &&
//		u16HE7RPM == 0U )
//	{
//		sFCU.sAuxPropulsion.u8AuxPropulsionEnabled = 1U;
//	}
//}
//
//void vFCU_FLIGHTCTL_AUX_PROPULSION__Disable(void)
//{
//	sFCU.sAuxPropulsion.u8AuxPropulsionEnabled = 0U;
//}
//
//void vFCU_FLIGHTCTL_AUX_PROPULSION__DrivePod(Luint8 distance, Luint8 speed)
//{
//	if (sFCU.sAuxPropulsion.u8AuxPropulsionEnabled == 1U)
//		vFCU_FLIGHTCTL_AUX_PROPULSION_SetSpeedAll(distance, speed);
//
//}
//
//void vFCU_FLIGHTCTL_AUX_PROPULSION__Process(void)
//{
//	if (sFCU.eMissionPhase == MISSION_PHASE__FLIGHT_MODE ||
//		sFCU.eMissionPhase == MISSION_PHASE__PUSH_INTERLOCK_PHASE)
//	{
//		sFCU.sAuxPropulsion.u8AuxPropulsionEnabled = 0U;
//	}
//}
//
//void vFCU_FLIGHTCTL_AUX_PROPULSION_SetSpeedAll(Luint8 distance, Luint8 speed)
//{
//	Luint8 u8motorIndex;
//
//	for (u8motorIndex=0; u8motorIndex < C_FCU__AUX_PROPULSION_NUM_MOTORS; u8motorIndex++)
//	{
//		vFCU_FLIGHTCTL_AUX_PROPULSION_SetSpeed(u8motorIndex, direction, speed);
//	}
//}
//
//void vFCU_FLIGHTCTL_AUX_PROPULSION_SetSpeed(Luint8 motorIndex, Luint8 direction, Luint8 speed)
//{
//	if (sFCU.sAuxPropulsion.u8AuxPropulsionEnabled == 1U)
//	{
//		vFCU_FLIGHTCTL_AUX_PROPULSION_Dir(motorIndex, direction);
//		vFCU_FLIGHTCTL_AUX_PROPULSION_Speed(motorIndex, speed);
//	}
//}

void vFCU_FCTL_AUX_PROP__Stop(void)
{
//todo
}

void vFCU_FCTL_AUX_PROP__Disable(void)
{
//todo
}


#endif //C_LOCALDEF__LCCM655__ENABLE_AUX_PROPULSION_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_AUX_PROPULSION_CONTROL
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

