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



void vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes(void)
{
	vFCU_BRAKES__Move_IBeam_Distance_mm(C_FCU__BRAKES__MIN_IBEAM_DIST_MM);
}



void vFCU_FCTL_EDDY_BRAKES__Release(void)
{
	vFCU_BRAKES__Move_IBeam_Distance_mm(C_FCU__BRAKES__MAX_IBEAM_DIST_MM);
}



void vFCU_FCTL_EDDY_BRAKES__SetDistance(Luint32 u32value)
{
//	Lfloat32 f32setvalue =  ( (Lfloat32)u32value )/ 1000.0;
//	if((f32SetValue < C_FCU__BRAKES__MAX_IBEAM_DIST_MM) && (u32value > C_FCU__BRAKES__MIN_IBEAM_DIST_MM) )
//	{
//		// receive the value in um from GS and send to the Brakes lower level
//		vFCU_BRAKES__Move_IBeam_Distance_mm(f32setvalue);
//	}

}


E_FCU__FCTL_EDDY_BRAKES_STATE eFCU_FCTL_EDDY_BRAKES__Get_State(void)
{
	E_FCU__FCTL_EDDY_BRAKES_STATE yo = EDDY_BRAKES_STATE__RETRACTED;
	return yo;
}

void vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake()
{
	//do something
}

Luint32 u32FCU_FCTL_EDDY_BRAKES_GetStepMotorTemp()
{
	return 0;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES
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
