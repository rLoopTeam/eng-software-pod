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

void vFCU_FCTL_EDDY_BRAKES__Init(void)
{
	sFCU.sEddyBrakes.eEddyBrakesState = EDDY_BRAKES_STATE__RETRACTED;
}

Luint32 vFCU_FCTL_EDDY_BRAKES__PolinomialApproximation(Luint32 u32xvalue)
{
	//square of the input value
	Luint32  u32xvalue_p2;
	// cube of the input value
	Luint32  u32xvalue_p3;
	// result of the polynomial approximation, return value
	Lfloat32 f32PolinomialApproximation;
	// calculate the x value square
	u32xvalue_p2 = u32xvalue * u32xvalue;
	// calculate the x value cube
	u32xvalue_p3 = u32xvalue * u32xvalue_p2;
	// Calculate the 3rd order polynomial FCU_FCTL_EDDY_BRAKES__PolinomialApproximationsed on the constant coeficients
	f32PolinomialApproximation = (C_FCU__EDDY_BRAKES_POLY_COEF_ORDER3 * u32xvalue_p3) + (C_FCU__EDDY_BRAKES_POLY_COEF_ORDER2 * u32xvalue_p2) + (C_FCU__EDDY_BRAKES_POLY_COEF_ORDER1 * u32xvalue) +  C_FCU__EDDY_BRAKES_POLY_COEF_ORDER0;

	return f32PolinomialApproximation;
}

Luint8 vFCU_FCTL_EDDY_BRAKES__GetPodSpeedTooHigh(void)
{
	Luint32  u32PodFrontPosition;
	Luint32  u32PodSpeed;
	Luint32  u32PolinomialInput;
	Lfloat32 f32V_Trigger;
	Luint8   u8PodSpeedTooHigh;

	// get the Pod front position
	u32PodFrontPosition = u32FCU_FCTL_NAV__GetFrontPos();

	// get the Pod speed
	u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();

	//apply the safety margine to the x position (in mm)
	u32PolinomialInput =  u32PodFrontPosition - C_FCU__EDDY_BRAKES_FOAM_PIT_X_POSITION - C_FCU__EDDY_BRAKES_TRIGGER_VELOCITY_SAFETY_MARGIN;

	// Calculate the trigger velocity based on the 3rd order polinomial approximation (in mm)
	f32V_Trigger =  vFCU_FCTL_EDDY_BRAKES__PolinomialApproximation(u32PolinomialInput);

	// If the trigger velocity is higher than the threshold, set the too high speed flag
	if(u32PodSpeed > f32V_Trigger)
	{
		u8PodSpeedTooHigh = 1U;
	}
	else
	{
		u8PodSpeedTooHigh = 0U;
	}

	// return the too high speed flag
	return u8PodSpeedTooHigh;
}

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
	return sFCU.sEddyBrakes.eEddyBrakesState;
}

void vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake()
{
	vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes();
	sFCU.sEddyBrakes.eEddyBrakesState = EDDY_BRAKES_STATE__CONTROLLED_BRAKING;
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
