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

///***************************************************************************//**
// * @brief
// * Init any navigation variables, etc.
// *
// *
// */
void vFCU_FLIGHTCTL_NAV__Init(void)
{
	Luint8 u8CSIndex;
	Luint8 u8Device;

	sFCU.sNavigation.f32LongitudinalPosition = 0;
	sFCU.sNavigation.f32LongitudinalLastPosition = 0;
	sFCU.sNavigation.f32LongitudinalSpeed = 0;
	sFCU.sNavigation.f32LongitudinalLastSpeed = 0;
	sFCU.sNavigation.u8LongitudinalSpeedValidity = 1;
	sFCU.sNavigation.f32LongitudinalAcceleration = 0;
	sFCU.sNavigation.u8LongitudinalAccelerationValidity = 1;
	sFCU.sNavigation.u8InLaserRangeFinderArea = 0;

	sFCU.sNavigation.u8GeneralStripeCount = 0;
	sFCU.sNavigation.u8masterSensor = 0;
	sFCU.sNavigation.f32PositionValidity = 1;

	// initialize each CS
	for (u8CSIndex = 0; u8CSIndex < C_FCU__NAV_NUM_CONTRAST_SENSORS; u8CSIndex++)
	{
		sFCU.sNavigation.sCS[u8CSIndex].u8Valid = 1;
		sFCU.sNavigation.sCS[u8CSIndex].u32StripeCount = 0;
		sFCU.sNavigation.sCS[u8CSIndex].u32Score = 0;
		sFCU.sNavigation.sCS[u8CSIndex].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
	}
	sFCU.sNavigation.sCS[0].u32Xpos = C_FCU__NAV_STARTUP_REAR_X_POSITION + C_FCU__NAV_POD_LENGTH - C_FCU__NAV_DISTANCE_BETWEEN_CONTRAST_SENSOR_1_AND_NOSE;
	sFCU.sNavigation.sCS[1].u32Xpos = C_FCU__NAV_STARTUP_REAR_X_POSITION + C_FCU__NAV_POD_LENGTH - C_FCU__NAV_DISTANCE_BETWEEN_CONTRAST_SENSOR_2_AND_NOSE;;
	sFCU.sNavigation.sCS[2].u32Xpos = C_FCU__NAV_STARTUP_REAR_X_POSITION + C_FCU__NAV_POD_LENGTH - C_FCU__NAV_DISTANCE_BETWEEN_CONTRAST_SENSOR_3_AND_NOSE;;

	// initialize each accel
	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)
	{
		sFCU.sNavigation.sAccel[u8Device].f32Accel = 0;
		sFCU.sNavigation.sAccel[u8Device].u8Valid = 0;
		sFCU.sNavigation.sAccel[u8Device].u8Available = 1;
	}

	sFCU.sNavigation.u3210MSNavTimer = 0;
}


//
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

void vFCU_FLIGHTCTL_NAV__ContrastSensor(void)
{
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
//	//TODO: FIX HOW TO DETECT
//	if (u8IsLaserRangeFinderAvailable())
//		sFCU.sNavigation.u3210MSLRFTimer = 0;
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
}
//
// Blending between contrast sensor and LRF
//	Luint32 u32TransitionA;
//	Lfloat32 f32XPos_ContrastSensors;
//	Lfloat32 f32XPos_LRF;
//
//	else if (sFCU.sNavigation.u8LRFAvailable == 1U &&
//			sFCU.sNavigation.u3210MSLRFTimer < C_FCU__NAV_LRF_TRANSITION_DELAY_FROM_CONTRAST_SENSORS )
//	{
//		// transition between contrast sensor and LRF
//		u32TransitionA = 1 - sFCU.sNavigation.u3210MSLRFTimer - C_FCU__NAV_LRF_TRANSITION_DELAY_FROM_CONTRAST_SENSORS;
//		f32XPos_ContrastSensors = (Lfloat32)u32vFCU_FCTL_NAV__ContrastSensor_Get_Distance();
//		f32XPos_LRF = s32FCU_LASERDIST__Get_Distance_mm();
//		sFCU.sNavigation.f32LongitudinalPosition = (1 - u32TransitionA) * f32XPos_ContrastSensors + u32TransitionA * f32XPos_LRF;
//	}


Luint8 u8InLaserRangeFinderArea(void)
{
	if (!sFCU.sNavigation.u8InLaserRangeFinderArea)
	{
		if (sFCU.sNavigation.f32LongitudinalPosition >= C_FCU__NAV_LRF_MIN_POS_TO_ACTIVATE &&
				abs(sFCU.sNavigation.f32LongitudinalPosition - s32FCU_LASERDIST__Get_Distance_mm()) < C_FCU__NAV_MAX_DISCREPANCY_BETWEEN_CURRENT_POSITION_AND_LRF_VALUE)
		{
			sFCU.sNavigation.u8InLaserRangeFinderArea = 1U;
		}
	}
	return sFCU.sNavigation.u8InLaserRangeFinderArea;

}

Luint8 u8IsAccelerometerAvailable(void)
{
	Luint8 available = 0;

	sFCU.sNavigation.sAccel[0].u8Available =  (u32MMA8451__Get_FaultFlags(0U) == 0x00000000U);
	sFCU.sNavigation.sAccel[1].u8Available =  (u32MMA8451__Get_FaultFlags(1U) == 0x00000000U);

	if (sFCU.sNavigation.sAccel[0].u8Available || sFCU.sNavigation.sAccel[1].u8Available)
	{
		available = 1;
	}

	return available;
}

Lfloat32 getOtherAccelDeviceId(Luint8 u8Device)
{
	Luint8 u8OtherDevice=0;
	if (u8Device == 0)
		u8OtherDevice = 1;
	return u8OtherDevice;
}


///***************************************************************************//**
// * @brief
// * Process the calculation of pod NAVIGATION
// *
// */
void vFCU_FLIGHTCTL_NAV__Process(void)
{

	Luint8 u8Device;
	Luint8 u8OtherDevice;
	Luint8 u8ValidDevices=0;
	Lfloat32 f32TotalAccel=0;

	sFCU.sNavigation.u8LongitudinalAccelerationValidity = 0;

	// If available, use LRF in priority (and only it)
	if (u8InLaserRangeFinderArea() && (sFCU.sLaserDist.eLaserState != LASERDIST_STATE__RESET))	//TODO: check lrf working?
	{
		sFCU.sNavigation.f32LongitudinalPosition = s32FCU_LASERDIST__Get_Distance_mm();
		sFCU.sNavigation.f32LongitudinalSpeed = (sFCU.sNavigation.f32LongitudinalPosition - sFCU.sNavigation.f32LongitudinalLastPosition)/C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ;
		sFCU.sNavigation.f32LongitudinalAcceleration = (sFCU.sNavigation.f32LongitudinalSpeed - sFCU.sNavigation.f32LongitudinalLastSpeed)/C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ;
		sFCU.sNavigation.f32LongitudinalLastPosition = sFCU.sNavigation.f32LongitudinalPosition;
		sFCU.sNavigation.f32LongitudinalLastSpeed = sFCU.sNavigation.f32LongitudinalSpeed;
		sFCU.sNavigation.u8LongitudinalAccelerationValidity = 1;
	}
	else if (u8IsAccelerometerAvailable()) //Otherwise, if available, use accels
	{
		// Go through all devices
		for (u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)
		{
			if (sFCU.sNavigation.sAccel[u8Device].u8Available)
			{
				// Get acceleration value
				sFCU.sNavigation.sAccel[u8Device].f32Accel = 0; //s32FCU_ACCELL__Get_CurrentAccel_mmss(u8Device);

				// If the value of an accelerometer is above max possible acceleration for more than accelerometer high value failure delay, the FCU shall set the acceleration validity to false.
				// If value is in range, reset timer
				if (abs(sFCU.sNavigation.sAccel[u8Device].f32Accel) <= C_FCU__NAV_MAX_ACCELERATION)
				{
					sFCU.sNavigation.u3210MSAccelHiValTimer = 0;
					sFCU.sNavigation.sAccel[u8Device].u8Valid = 1;
				}// Else check timer
				else if (abs(sFCU.sNavigation.sAccel[u8Device].f32Accel) > C_FCU__NAV_MAX_ACCELERATION &&
						sFCU.sNavigation.u3210MSAccelHiValTimer > C_FCU__NAV_ACCELEROMETER_HIGH_VAL_DELAY)
				{
					sFCU.sNavigation.sAccel[u8Device].u8Valid = 0;
				}

				// Check discrepancy: this is zero while other accel is not
				u8OtherDevice = getOtherAccelDeviceId(u8Device);
				// If this accel is not zero, no discrepancy to check: reset the timer
				if (sFCU.sNavigation.sAccel[u8Device].f32Accel > 0)
				{
					sFCU.sNavigation.u3210MSAccelLoValTimer = 0;
					sFCU.sNavigation.sAccel[u8Device].u8Valid = 1;
				}
				// Else, if this is zero while other is not, check timer
				else if (sFCU.sNavigation.sAccel[u8Device].f32Accel == 0  &&
						sFCU.sNavigation.u3210MSAccelLoValTimer > C_FCU__NAV_ACCELEROMETER_LOW_VAL_DELAY &&
						sFCU.sNavigation.sAccel[u8OtherDevice].u8Available &&
						(sFCU.sNavigation.sAccel[u8OtherDevice].f32Accel != 0) &&
						(abs(sFCU.sNavigation.sAccel[u8OtherDevice].f32Accel) < C_FCU__NAV_MAX_ACCELERATION))
				{
					sFCU.sNavigation.sAccel[u8Device].u8Valid = 0;
				}
			}
		}
		 //accumulate accelerometers that are valid
		for (u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)
		{
			if (sFCU.sNavigation.sAccel[u8Device].u8Available && sFCU.sNavigation.sAccel[u8Device].u8Valid)
			{
				//If at least one accelerometer is valid, the FCU shall set the acceleration validity to true. Otherwise, it shall the FCU shall set the acceleration validity to false.
				sFCU.sNavigation.u8LongitudinalAccelerationValidity = 1;
				//Accumulate
				f32TotalAccel += sFCU.sNavigation.sAccel[u8Device].f32Accel;
				u8ValidDevices++;
			}
		}
		sFCU.sNavigation.f32LongitudinalAcceleration = f32TotalAccel/u8ValidDevices;

		 //TODO filter
		 //TODO compensate for thermal drift?
	}
	else  // otherwise use constrast sensors
	{
		if (sFCU.sStateMachine.sOpStates.u8ReadyForPush == 1U)
		{
			// initial
			sFCU.sNavigation.sCS[0].u32Xpos = C_FCU__NAV_PUSHER_START_XPOS + C_FCU__NAV_POD_LENGTH - C_FCU__NAV_DISTANCE_BETWEEN_CONTRAST_SENSOR_1_AND_NOSE;
			sFCU.sNavigation.sCS[1].u32Xpos = C_FCU__NAV_PUSHER_START_XPOS + C_FCU__NAV_POD_LENGTH - C_FCU__NAV_DISTANCE_BETWEEN_CONTRAST_SENSOR_2_AND_NOSE;
			sFCU.sNavigation.sCS[2].u32Xpos = C_FCU__NAV_PUSHER_START_XPOS + C_FCU__NAV_POD_LENGTH - C_FCU__NAV_DISTANCE_BETWEEN_CONTRAST_SENSOR_3_AND_NOSE;
			sFCU.sNavigation.sCS[0].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
			sFCU.sNavigation.sCS[1].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
			sFCU.sNavigation.sCS[2].u32XPosUncert = C_FCU__NAV_X_POS_UNCERTAINTY_OFFSET;
		}
		vFCU_FLIGHTCTL_NAV__ContrastSensor();
	}

}


void vFCU_FCTL_NAV__10MS_ISR(void)
{
	sFCU.sNavigation.u3210MSNavTimer++;
	sFCU.sNavigation.u3210MSLRFTimer++;
	sFCU.sNavigation.u3210MSDetectStripeTimer++;
	sFCU.sNavigation.u3210MSBetweenStripeTimer++;
	sFCU.sNavigation.u3210MSAccelHiValTimer++;
	sFCU.sNavigation.u3210MSAccelLoValTimer++;
}


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
	return u32FCU_FCTL_NAV__GetFrontPos() - C_FCU__NAV_POD_LENGTH;
}

Luint32 u32FCU_FCTL_NAV__Get_Accel_mmss(void)
{
	return round(sFCU.sNavigation.f32LongitudinalAcceleration);
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
