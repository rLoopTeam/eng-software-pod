 /**
 * @file		FCU__NAVIGATION.c
 * @brief		Determine Pod Front and Rear x Position, Speed and Acceleration in tube
 * @author		Paul Le Henaff, Nazneen Khan, Marek Gutt-Mostowy
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */

// All units in mm, but the math doesn't care as long as you're consistent

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U

//the structure
extern struct _strFCU sFCU;
//
////locals
//static void vFCU_FLIGHTCTL_NAV__CalcLongitudinalPosition(void);
//static void vFCU_FLIGHTCTL_NAV__CalcLongitudinalSpeed(void);
//static void vFCU_FLIGHTCTL_NAV__CalcLongitudinalAcceleration(void);
//
//#define ACCELERATION_ARRAY_SIZE = 10
//#define MAX_LONGETIUDENAL_POSITION_USE_ACCELEROMETER =
//
//E_FCU__LASER_CONT_INDEX_T Get_LC_Enum(Luint8 u8CSIndex)
//{
//	switch(u8CSIndex)
//	{
//		case 0:
//			return LASER_CONT__FWD;
//		case 1:
//			return LASER_CONT__MID;
//		case 2:
//			return LASER_CONT__AFT;
//	}
//}
//
//
///***************************************************************************//**
// * @brief
// * Init any navigation variables, etc.
// *
// *
// */
//void vFCU_FLIGHTCTL_NAV__Init(void)
//{
//	Luint8 u8CSIndex;
//
//	sFCU.sNavigation.f32LongitudinalPosition = 0; // distance along tube
//	sFCU.sNavigation.f32LongitudinalSpeed = 0; // velocity
//	sFCU.sNavigation.u8LongitudinalSpeedValidity = 1;
//	sFCU.sNavigation.f32LongitudinalAcceleration = 0; // acceleration
//	sFCU.sNavigation.u8LongitudinalAccelerationValidity = 1;
//
//	// TODO check if accelerometers are working?
//
//	sFCU.sNavigation.u8GeneralStripeCount = 0;
//	sFCU.sNavigation.u8masterSensor = 0;
//	sFCU.sNavigation.f32PositionValidity = 1;
//	sFCU.sNavigation.u8LRFAvailable = 0;
//
//	// initialize each CS
//	for (u8CSIndex = 0; u8CSIndex < C_FCU__NAV_NUM_CONTRAST_SENSORS; u8CSIndex++)
//	{
//		sFCU.sNavigation.sCS[u8CSIndex].u8Valid = 1;
//		sFCU.sNavigation.sCS[u8CSIndex].u32StripeCount = 0;
//		sFCU.sNavigation.sCS[u8CSIndex].u32Score = 0;
//		sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
//	}
//	sFCU.sNavigation.sCS[0].u32Xpos = C_FCU__NAV_STARTING_XPOS_LC_FWD;
//	sFCU.sNavigation.sCS[1].u32Xpos = C_FCU__NAV_STARTING_XPOS_LC_MID;
//	sFCU.sNavigation.sCS[2].u32Xpos = C_FCU__NAV_STARTING_XPOS_LC_AFT;
//
//	sFCU.sNavigation.sCS[0].u32NoseToSensorDist = C_FCU__NAV_POD_LENGTH - C_FCU__NAV_STARTING_XPOS_LC_FWD;
//	sFCU.sNavigation.sCS[1].u32NoseToSensorDist = C_FCU__NAV_POD_LENGTH - C_FCU__NAV_STARTING_XPOS_LC_MID;
//	sFCU.sNavigation.sCS[2].u32NoseToSensorDist = C_FCU__NAV_POD_LENGTH - C_FCU__NAV_STARTING_XPOS_LC_AFT;
//
//	sFCU.sNavigation.u3210MSNavTimer = 0;
//	// initialise arrays for filtering purposes
//	sFCU.sNavigation.f32AccelerationArray[ACCELERATION_ARRAY_SIZE] = {0};
//
//}
//
//
///***************************************************************************//**
// * @brief
// * Process the calculation of pod NAVIGATION
// *
// */
//void vFCU_FLIGHTCTL_NAV__Process(void)
//{
//	if (sFCU.sNavigation.u3210MSNavTimer > 3)	// calculate every 30 ms
//	{
//		vFCU_FLIGHTCTL_NAV__CalcAcceleration();
//		vFCU_FLIGHTCTL_NAV__CalcLongitudinalPositionAndSpeed();
//		sFCU.sNavigation.u3210MSNavTimer = 0;
//	}
//}
//
//Luint8 searchStripsInRange(Luint8 u8CS)
//{
//	Luint8 u8Index;
//	Luint32 u32xPosStart;
//	Luint32 u32xPosEnd;
//	Luint32 u32Dist;
//	Luint8 u8Min=54;
//	Luint32 u32CurStripeCount = sFCU.sNavigation.u8GeneralStripeCount;
//
//	for (u8Index = u32CurStripeCount; u8Index < 54; u8Index ++)
//	{
//		u32xPosStart=sFCU.sNavigation.f32LongitudinalPosition - sFCU.sNavigation.sCS[u8CS].u32XPosUncert;
//		u32xPosEnd=sFCU.sNavigation.f32LongitudinalPosition + sFCU.sNavigation.sCS[u8CS].u32XPosUncert;
//		u32Dist = sFCU.sContrast.sTrackDatabase[u8CS].u32DistanceElapsed_mm[u8Index];
//		if (u32Dist > u32xPosStart) && (u32Dist < u32xPosEnd)
//		{
//			return u8Index;
//		}
//	};
//	return 0;
//}
//
//Luint8 findDetectStripeMode(Luint8 u8CS)
//{
//	//TODO:  call lower level module
//}
//
//void vFCU_FLIGHTCTL_NAV__ContrastSensor_Distance(void)
//{
//	Luint8 u8CSIndex;
//	Luint32 u32xPosIndex;
//	Luint32 u32xPosStart;
//	Luint32 u32xPosEnd;
//	Luint8 u8ExpectedStripeNum;
//	Luint8 u8DetectedStripMode;
//	Lfloat32 f32speedSt;
//	Lfloat32 f32speedAc;
//
//	for (u8CSIndex = 0; u8CSIndex < C_FCU__NAV_NUM_CONTRAST_SENSORS; u8CSIndex++)
//	{
//		E_FCU__LASER_CONT_INDEX_T u8CS = Get_LC_Enum(u8CSIndex);
//		u8ExpectedStripeNum = searchStripsInRange(u8CSIndex);
//		u8DetectedStripMode = findDetectStripeMode(u8CSIndex);
//
//		if (u8DetectedStripMode)
//		{
//			// detected stripe
//			sFCU.sNavigation.u3210MSBetweenStripeTimer = 0;
//			if (u8ExpectedStripeNum)
//			{
//				sFCU.sNavigation.sCS[u8CSIndex].u32StripeCount = u8ExpectedStripeNum;
//				sFCU.sNavigation.sCS[u8CSIndex].u32Xpos = sFCU.sContrast.sTrackDatabase[u8CS].u32DistanceElapsed_mm[u8ExpectedStripeNum];
//				sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
//				f32speedSt = C_FCU__NAV_STRIPE_LENGTH/sFCU.sNavigation.u3210MSDetectStripeTimer;
//				sFCU.sNavigation.f32LongitudinalSpeed = f32speedSt;
//				sFCU.sNavigation.f32LogintudenalSpeedUncertainty = C_FCU__NAV_SPEED_UNCERTAINTY_OFFSET;
//			}
//			else
//			{
//				// stripe not expected here
//				sFCU.sNavigation.f32LongitudinalSpeed += sFCU.sNavigation.f32LongitudinalAcceleration * sFCU.sNavigation.sFCU.sNavigation.u3210MSNavTimer;
//				sFCU.sNavigation.sCS[u8CSIndex].u32Xpos += sFCU.sNavigation.f32LongitudinalSpeed * sFCU.sNavigation.sFCU.sNavigation.u3210MSNavTimer;
//				//sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert = ; //TODO
//				sFCU.sNavigation.sCS[u8CSIndex].u32Score--;
//			}
//		}
//		else if (u8ExpectedStripeNum)
//		{
//			// expected but not detected
//			sFCU.sNavigation.u3210MSDetectStripeTimer = 0;
//			sFCU.sNavigation.f32LongitudinalSpeed += sFCU.sNavigation.f32LongitudinalAcceleration * sFCU.sNavigation.sFCU.sNavigation.u3210MSNavTimer;
//			sFCU.sNavigation.sCS[u8CSIndex].u32Xpos += sFCU.sNavigation.f32LongitudinalSpeed * sFCU.sNavigation.sFCU.sNavigation.u3210MSNavTimer;
//			//sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert = ; //TODO
//			sFCU.sNavigation.sCS[u8CSIndex].u32Score--;
//		}
//		if (sFCU.sNavigation.u3210MSDetectStripeTimer > C_FCU__NAV_STRIPE_DETECTION_NAV_DELAY ||
//				sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert > C_FCU__NAV_MAX_X_POS_UNCERTAINTY )
//		{
//			sFCU.sNavigation.sCS[u8CSIndex].u8Valid = 0;
//		}
//		else
//		{
//			sFCU.sNavigation.sCS[u8CSIndex].u8Valid = 1;
//		}
//	}
//
//	// set x pos based on current master sensor
//	sFCU.sNavigation.f32LongitudinalPosition = sFCU.sNavigation.sCS[sFCU.sNavigation.u8masterSensor].u32Xpos +
//			sFCU.sNavigation.sCS[sFCU.sNavigation.u8masterSensor].u32NoseToSensorDist;
//
//	// see laser finder range becomes active
//	if (sFCU.sNavigation.u8LRFAvailable == 0U &&
//			sFCU.sNavigation.f32LongitudinalPosition >= C_FCU__NAV_LRF_MIN_POS_TO_ACTIVATE &&
//			f32FCU_LASERDIST__Get_Distance() >= C_FCU__NAV_LRF_FIRST_EXPECTED_RANGE_MIN &&
//			f32FCU_LASERDIST__Get_Distance() <= C_FCU__NAV_LRF_FIRST_EXPECTED_RANGE_MAX)
//	{
//		sFCU.sNavigation.u8LRFAvailable = 1U;
//		sFCU.sNavigation.u3210MSLRFTimer = 0;
//	}
//
//	sFCU.sNavigation.u8GeneralStripeCount = sFCU.sNavigation.sCS[sFCU.sNavigation.u8masterSensor].u32StripeCount;
//
//	// determine new master sensor
//	Luint32 maxScore=sFCU.sNavigation.sCS[0].u32Score;
//	Luint32 same = 0;
//	sFCU.sNavigation.u8masterSensor = 0;
//	for (u8CSIndex = 1; u8CSIndex < C_FCU__NAV_NUM_CONTRAST_SENSORS; u8CSIndex++)
//	{
//		// figure out sensor with highest score
//		if (sFCU.sNavigation.sCS[u8CSIndex].u32Score > maxScore)
//		{
//			maxScore = sFCU.sNavigation.sCS[u8CSIndex].u32Score;
//			sFCU.sNavigation.u8masterSensor = u8CSIndex;
//			same = 0;
//		}
//		else if (sFCU.sNavigation.sCS[u8CSIndex].u32Score == maxScore)
//		{
//			same = 1;
//		}
//		else
//		{
//			same = 0;
//		}
//	}
//	if (same = 0)
//	{
//		// figure out sensor with least uncertainty
//		Luint32 minUncert=sFCU.sNavigation.sCS[0].u32XPosUncert;
//		for (u8CSIndex = 1; u8CSIndex < C_FCU__NAV_NUM_CONTRAST_SENSORS; u8CSIndex++)
//		{
//			if (sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert < minUncert)
//			{
//				minUncert = sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert
//				sFCU.sNavigation.u8masterSensor = u8CSIndex;
//			}
//		}
//	}
//}
//
//void vFCU_FLIGHTCTL_NAV__CalcLongitudinalPositionAndSpeed(void)
//{
//	Luint32 u32TransitionA;
//	Lfloat32 f32XPos_ContrastSensors;
//	Lfloat32 f32XPos_LRF;
//
//	if (sFCU.eMissionPhase == MISSION_PHASE__PUSH_INTERLOCK_PHASE)
//	{
//		// initial
//		sFCU.sNavigation.sCS[0].u32Xpos = C_FCU__NAV_PUSHER_START_XPOS + C_FCU__NAV_STARTING_XPOS_LC_FWD;
//		sFCU.sNavigation.sCS[1].u32Xpos = C_FCU__NAV_PUSHER_START_XPOS + C_FCU__NAV_STARTING_XPOS_LC_MID;
//		sFCU.sNavigation.sCS[2].u32Xpos = C_FCU__NAV_PUSHER_START_XPOS + C_FCU__NAV_STARTING_XPOS_LC_AFT;
//		sFCU.sNavigation.sCS[0].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
//		sFCU.sNavigation.sCS[1].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
//		sFCU.sNavigation.sCS[2].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
//	}
//	else if (sFCU.sNavigation.u8LRFAvailable == 1U &&
//			sFCU.sNavigation.u3210MSLRFTimer < C_FCU__NAV_LRF_TRANSITION_DELAY_FROM_CONTRAST_SENSORS )
//	{
//		// transition between contrast sensor and LRF
//		u32TransitionA = 1 - sFCU.sNavigation.u3210MSLRFTimer - C_FCU__NAV_LRF_TRANSITION_DELAY_FROM_CONTRAST_SENSORS;
//		f32XPos_ContrastSensors = (Lfloat32)u32vFCU_FCTL_NAV__ContrastSensor_Get_Distance();
//		f32XPos_LRF = f32FCU_LASERDIST__Get_Distance();
//		sFCU.sNavigation.f32LongitudinalPosition = (1 - u32TransitionA) * f32XPos_ContrastSensors + u32TransitionA * f32XPos_LRF;
//	}
//	else if (sFCU.sNavigation.u8LRFAvailable == 1U)
//	{
//		// laser range finder
//		sFCU.sNavigation.f32LongitudinalPosition = f32FCU_LASERDIST__Get_Distance();
//		sFCU.sNavigation.f32LongitudinalSpeed += sFCU.sNavigation.f32LongitudinalAcceleration * sFCU.sNavigation.sFCU.sNavigation.u3210MSNavTimer;
//		sFCU.sNavigation.sCS[u8CSIndex].u32Xpos += sFCU.sNavigation.f32LongitudinalSpeed * sFCU.sNavigation.sFCU.sNavigation.u3210MSNavTimer;
//	}
//	else
//	{
//		// contrast sensor
//		vFCU_FLIGHTCTL_NAV__ContrastSensor_Distance();
//	}
//
//	// TODO filter
//
//}
//
//void vFCU_FLIGHTCTL_NAV__CalcAcceleration(void)
//{
//
//	Luint8 u8Device;
//	Luint8 u8ValidDevices=0;
//	Lfloat32 f32TotalAccel=0
//	Lfloat32 f32Accel;
//	// get validity
//	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)
//	{
//		//If the value of an accelerometer is above max possible acceleration for more than accelerometer high value failure delay, the FCU shall set the acceleration validity to false.
//		f32Accel = sFCU.sNavigation.sAccel[u8Device].f32Accel = s32FCU_ACCELL__Get_CurrentAccel_mmss(u8Device);
//		if (f32Accel <= C_FCU__NAV_MAX_ACCELERATION)
//		{
//			sFCU.sNavigation.u3210MSAccelHiValTimer = 0;
//			sFCU.sNavigation.sAccel[u8Device].u8Valid = 1;
//		}
//		elseif (f32Accel > C_FCU__NAV_MAX_ACCELERATION &&
//				sFCU.sNavigation.u3210MSAccelHiValTimer > C_FCU__NAV_ACCELEROMETER_HIGH_VAL_DELAY)
//		{
//			sFCU.sNavigation.sAccel[u8Device].u8Valid = 0;
//		}
//		if (f32Accel > 0)
//		{
//			sFCU.sNavigation.u3210MSAccelLoValTimer = 0;
//		}
//		elseif (f32Accel > C_FCU__NAV_MAX_ACCELERATION &&
//				sFCU.sNavigation.u3210MSAccelLoValTimer > C_FCU__NAV_ACCELEROMETER_LOW_VAL_DELAY)
//		{
//			sFCU.sNavigation.sAccel[u8Device].u8Valid = 0;
//		}
//
//	}
//	// TODO: If an accelerometer is in acceleration phase expected range or in deceleration phase expected range, while the other accelerometer indicates 0 for more than accelerometer low value failure delay, the FCU shall set the acceleration validity to false.
//	// If at least one accelerometer is valid, the FCU shall set the acceleration validity to true. Otherwise, it shall the FCU shall set the acceleration validity to false.
//	sFCU.sNavigation.u8LongitudinalAccelerationValidity = 0;
//	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)
//	{
//		if (sFCU.sNavigation.sAccel[u8Device].u8Valid)
//		{
//			sFCU.sNavigation.u8LongitudinalAccelerationValidity = 1;
//		}
//	}
//
//	// accumulate accelerometers that are valid
//	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)
//	{
//		if (sFCU.sNavigation.sAccel[u8Device].u8Valid)
//		{
//			f32TotalAccel = sFCU.sNavigation.sAccel[u8Device].f32Accel;
//			u8ValidDevices++;
//		}
//	}
//
//	sFCU.sNavigation.f32LongitudinalAcceleration = f32TotalAccel/u8ValidDevices;
//
//	// TODO filter
//	// TODO compensate for thermal drift?
//}
//
//
//void vFCU_FCTL_NAV__10MS_ISR(void)
//{
//	sFCU.sNavigation.u3210MSNavTimer++;
//	sFCU.sNavigation.u3210MSLRFTimer++;
//	sFCU.sNavigation.u3210MSDetectStripeTimer++;
//	sFCU.sNavigation.u3210MSBetweenStripeTimer++;
//	sFCU.sNavigation.u3210MSAccelHiValTimer++;
//	sFCU.sNavigation.u3210MSAccelLoValTimer++;
//}


/****************************************************************************/
/** Functions to retrieve NAVIGATION parameters, to be called from other files */

Luint8 u8FCU_FCTL_NAV__GetPodSpeedTooHigh(void)
{
	Luint8 u8Test;
	return u8Test;
}

Luint32 u32FCU_FCTL_NAV__PodSpeed(void)
{
	return round(sFCU.sNavigation.f32LongitudinalSpeed);
}

Luint32 u32FCU_FCTL_NAV__GetFrontPos(void)
{
	return round(sFCU.sNavigation.f32LongitudinalPosition);
}

Luint32 u32FCU_FCTL_NAV__GetRearPos(void)
{
	return round(sFCU.sNavigation.f32LongitudinalPosition - C_FCU__NAV_POD_LENGTH);
}

Luint32 u32FCU_FCTL_NAV__Get_Accel_mmss(void)
{
//do something with it
	return 0U;
}

Luint32 u32FCU_FCTL_LASERORIENT__Get_Z_Pos()
{
	//TODO: WRITE THIS ONE
	return 0U;
}

Luint8 u8FCU_FCTL_NAV__IsInFailure(void)
{
	return 0U;
}

/****************************************************************************/
/** Functions to retrieve NAVIGATION parameters, to be called from other files */



#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
