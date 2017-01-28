/**
* @file       FCU__FCTL__BRAKE_PID.C
* @brief      PID to control brake profile
* @author	  Nazneen Khan, Sean, Lachlan Grogan
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
 * @addtogroup FCU__FLIGHT_CTL__BRAKEPID
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKEPID == 1U

extern struct _strFCU sFCU;

#ifndef WIN32
extern const Lfloat32 f32A34_BrakeTable[];
#else
extern Lfloat32 f32A34_BrakeTable[];
#endif

#ifndef WIN32
extern const Lfloat32 f32A34_BrakeTable[];
#else
extern Lfloat32 f32A34_GainsTable[];
#endif

#ifndef WIN32
extern const Lfloat32 f32A34_SetPointVelocityTable[];
#else
extern Lfloat32 f32A34_SetPointVelocityTable[];
#endif

// TODO: add struct to fcu_core.h inside of _strFCU:
#if C_LOCALDEF__LCCM655__ENABLE_BRAKEPID == 1U
struct
{
	Lfloat32 f32LastError;
	Lfloat32 f32LastIntegral;

}sBrakesPid;
#endif


void vFCU_FLIGHTCTL_BRAKEPID__Init(void)
{
	// set initial conditions for pid
	sBrakesPid.f32LastError = 0;
	sBrakesPid.f32LastIntegral = 0;
}


void vFCU_FLIGHTCTL_BRAKEPID__Process(void)
{
//	Lint32 kp, ki, kd;
//	Lfloat32 f32MeasDistance, f32MeasVelocity, f32SetPointVelocity;
//	Lfloat32 f32Error, f32LastError;
//	Lfloat32 f32Integral, f32Derivative;
//	Lfloat32 f32BrakeGap, f32BrakePos;
//
//	// measured distance and scale it appropriately so can use as index
//	f32MeasDistance = u32FCU_FCTL_NAV__GetFrontPos();
//	// scale it so can use as index

//	// look up SetPoint velocity
//	f32SetPointVelocity = f32A34_SetPointVelocityTable[f32MeasDistance];
//
//	// measure velocity
//	f32MeasVelocity = u32FCU_FCTL_NAV__PodSpeed();
//	// scale it so can use as index
//
//	// compute error
//	// TODO: check scaling
//	f32Error = f32SetPointVelocity - f32MeasVelocity;
//
//	// compute integral
//	f32Integral = (f32LastIntegral + f32Error) * C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ;
//
//	// compute derivative
//	f32Derivative = (f32Error - f32LastError)/C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ;
//
//	// look up pid gains
//	kp = f32A34_GainsTable[s32MeasVelocity];
//	ki = f32A34_GainsTable[s32MeasVelocity + 1U];
//	kd = f32A34_GainsTable[s32MeasVelocity + 2U];
//
//	// calculate brake position increment (brake gap) from pid equations
//	// TODO: verify this represents the equation
//	// u = [ kp + ki * 1/s + kd * (s/(Tf*s + 1) ] * e
//	f32BreakGap = (kp * f32Error) + (ki * f32Integral) + (kd * f32Derivative);
//
//	// get current brake position
//	//TODO: Clarify this
//	f32BrakePos = (s32FCU_BRAKES__Get_CurrentPos(FCU_BRAKE__LEFT ) + s32FCU_BRAKES__Get_CurrentPos(FCU_BRAKE__RIGHT )) >> 1U;
//
//	// add brake gap to current brake position
//	f32BrakePos += f32BreakGap;
//
//	// set new brake position
//	// TODO: check units, need in microns for this function
//	vFCU_BRAKES__Move_IBeam_Distance_mm(Lfloat32 f32BrakePos)
//
//	// save current error
//	f32LastError = f32Error;
//	f32LastIntegral = f32Integral;

}





#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKEPID
#ifndef C_LOCALDEF__LCCM655__ENABLE_BRAKEPID
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

