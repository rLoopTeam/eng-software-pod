 /**
 * @file		FCU__NAVIGATION.c
 * @brief		Determine Pod Front and Rear x Position, Speed and Acceleration in tube
 * @author		Paul Le Henaff, Nazneen Khan
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

#define ACCELERATION_ARRAY_SIZE = 10
#define MAX_LONGETIUDENAL_POSITION_USE_ACCELEROMETER = 

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U

//the structure
extern struct _strFCU sFCU;

////locals
//static void vFCU_FLIGHTCTL_NAVIGATION__CalcLongitudenalPosition(void);
//static void vFCU_FLIGHTCTL_NAVIGATION__CalcLongitudenalSpeed(void);
//static void vFCU_FLIGHTCTL_NAVIGATION__CalcLongitudenalAcceleration(void);
//
//// TODO: need values for following constants and move to fcu_core_defines.h
//#define C_FCU__NAVIGATION_NUM_CONTRAST_SENSORS 	3U
//#define C_FCU__NAVIGATION_
//#define C_FCU__NAVIGATION_STARTING_XPOS_LC_FWD
//#define C_FCU__NAVIGATION_STARTING_XPOS_LC_MID
//#define C_FCU__NAVIGATION_STARTING_XPOS_LC_AFT
//#define C_FCU__NAVIGATION_STARTING_XPOSUNCERT
//#define C_FCU__NAVIGATION_STRIPE_DETECTION_NAVIGATION_DELAY
//#define C_FCU__NAVIGATION_X_POS_UNCERTAINTY_OFFSET
//
//// TODO: add struct to fcu_core.h inside of _strFCU:
//#if C_LOCALDEF__LCCM655__ENABLE_PODDRIVE_CONTROL == 1U
//
//struct
//{
//	Luint32 u32StripeCount;
//	Luint32 u32Xpos;
//	Luint32 u32XPosUncert;
//	Luint32 u32Score;
//	Luint8 u8Valid;
//}sContrastSensor;
//
//struct
//{
//	Lfloat32 f32LongitudenalPosition;
//	Lfloat32 f32PositionValidity;
//	Lfloat32 f32LongitudenalAcceleration;
//	Lfloat32 f32LongitudenalAcceleration;
//
//	Luint8 u8LRFAvailable;
//	Luint8 u8masterSensor;
//	sContrastSensor sCS[C_FCU__NAVIGATION_NUM_CONTRAST_SENSORS];
//
//}sNavigation;
//#endif
//
//
//E_FCU__LASER_CONT_INDEX_T Get_LC_Enum(Luint8 u8LCIndex)
//{
//	switch(u8LCIndex)
//	{
//		case 0:
//			return LASER_CONT__FWD;
//		case 1:
//			return LASER_CONT__MID;
//		case 2:
//			return LASER_CONT__AFT;
//	}
//
//}
//
//
///***************************************************************************//**
// * @brief
// * Init any navigation variables, etc.
// *
// *
// */
//void vFCU_FLIGHTCTL_NAVIGATION__Init(void)
//{
//	Luint8 u8LCIndex;
//
//	sFCU.sNavigation.f32LongitudenalPosition = 0; // distance along tube
//	sFCU.sNavigation.f32LongitudenalAcceleration = 0; // acceleration
//	sFCU.sNavigation.f32LongitudenalVelocity = 0; // velocity
//
//	// TODO check if accelerometers are working?
//
//
//	sFCU.sNavigation.u8masterSensor = 0;
//	sFCU.sNavigation.f32PositionValidity = 1;
//	sFCU.sNavigation.u8LRFAvailable = 0;
//
//	// initialize each LC
//	for (u8LCIndex = 0; u8LCIndex < C_FCU__NAVIGATION_NUM_CONTRAST_SENSORS; u8LCIndex++)
//	{
//		if (sFCU.sNavigation.sLC[u8LCIndex] is in no stripe detection range )	// TODO
//		{
//			sFCU.sNavigation.sLC[u8LCIndex].u8Valid = 0;
//			// send alarm to GS;
//		}
//		else
//		{
//			sFCU.sNavigation.sLC[u8LCIndex].u8Valid = 1;
//		}
//		sFCU.sNavigation.sLC[u8LCIndex].u32StripeCount = 0;
//		sFCU.sNavigation.sLC[u8LCIndex].u32Score = 0;
//		sFCU.sNavigation.sLC[u8LCIndex].u32XPosUncert = C_FCU__NAVIGATION_STARTING_XPOSUNCERT;
//	}
//	sFCU.sNavigation.sLC[0].u32Xpos = C_FCU__NAVIGATION_STARTING_XPOS_LC_FWD;
//	sFCU.sNavigation.sLC[1].u32Xpos = C_FCU__NAVIGATION_STARTING_XPOS_LC_MID;
//	sFCU.sNavigation.sLC[2].u32Xpos = C_FCU__NAVIGATION_STARTING_XPOS_LC_AFT;
//
//
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
//void vFCU_FLIGHTCTL_NAVIGATION__Process(void)
//{
//	vFCU_FLIGHTCTL_NAVIGATION__CalcLongitudenalPosition();
//	vFCU_FLIGHTCTL_NAVIGATION__CalcSpeed();
//	vFCU_FLIGHTCTL_NAVIGATION__CalcAcceleration();
//
//}
//
///** The longitudenal position down the tube */
///*
//input
//=====
//contrast sensor 1 value
//contrast sensor 2 value
//contrast sensor 3 value
//laser range finder value
//speed
//speed uncertainty
//speed validity
//*/
//
///*
//output
//======
//front x position (x position of pod nose in the tube)
//rear x position (x position of pod pusher plate in the tube)
//x position validity
//*/
//
//void vFCU_FLIGHTCTL_NAVIGATION__CalcLongitudenalPosition(void)
//{
//	Luint8 u8LCIndex;
//	Luint32 u32xPosIndex;
//	Luint32 u32xPosStart;
//	Luint32 u32xPosEnd;
//
//	if (sFCU.sNavigation.u8LRFAvailable == 1U)
//	{
//		// laser range finder available
//
//	}
//	else
//	{
//		for (u8LCIndex = 0; u8LCIndex < C_FCU__NAVIGATION_NUM_CONTRAST_SENSORS; u8LCIndex++)
//		{
//			E_FCU__LASER_CONT_INDEX_T u8LC = Get_LC_Enum(u8LCIndex);
//			u32xPosStart=sFCU.sNavigation.sCS[u8LCIndex].u32Xpos - sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert;
//			u32xPosEnd=sFCU.sNavigation.sCS[u8LCIndex].u32Xpos + sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert;
//			for (u32xPosIndex=u32xPosStart; u32xPosIndex < u32xPosEnd; u32xPosEnd++)
//			{
//				if (stripesLocTable[u32xPosIndex].nStripes)
//				{
//					// expected a stripe at this position
//					// TODO:  not sure how this table is organized so difficult to tell
//					//        how to get values
//					sFCU.sNavigation.sCS[u8LCIndex].u32Xpos = stripesLocTable[u32xPosIndex].stripePos;
//					sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert = C_FCU__NAVIGATION_X_POS_UNCERTAINTY_OFFSET;
//				}
//			}
//			if (stripe detection mode)	//TODO
//			{
//				// detected stripe
//				if (stripe expected)	//TODO
//				{
//					sFCU.sNavigation.sCS[u8LCIndex].u32StripeCount++;
//					sFCU.sNavigation.sCS[u8LCIndex].u32Xpos = stripe pos in DB; //TODO
//					sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert = 0;
//				}
//				else
//				{
//					sFCU.sNavigation.sCS[u8LCIndex].u32Xpos increment; //TODO from speed
//					sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert increment; //TODO from speed
//					sFCU.sNavigation.sCS[u8LCIndex].u32Score--;
//				}
//			}
//			else if (stripe expected)	//TODO
//			{
//				// expected but not detected
//				sFCU.sNavigation.sCS[u8LCIndex].u32Xpos increment; //TODO from speed
//				sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert increment; //TODO from speed
//				sFCU.sNavigation.sCS[u8LCIndex].u32Score--;
//			}
//			if (detected signal too long || sCS[u8LCIndex].u32XPosUncert > 100ft ) //TODO
//			{
//				sFCU.sNavigation.sCS[u8LCIndex].u8Valid = 0;
//			}
//			else
//			{
//				sFCU.sNavigation.sCS[u8LCIndex].u8Valid = 1;
//			}
//		}
//
//		// set x pos based on current master sensor
//		sFCU.sNavigation.f32LongitudenalPosition = sFCU.sNavigation.sCS[sFCU.sNavigation.u8masterSensor].u32Xpos;
//
//		// determine new master sensor
//		Luint32 maxScore=sFCU.sNavigation.sCS[0].u32Score;
//		Luint32 same = 0;
//		sFCU.sNavigation.u8masterSensor = 0;
//		for (u8LCIndex = 1; u8LCIndex < C_FCU__NAVIGATION_NUM_CONTRAST_SENSORS; u8LCIndex++)
//		{
//			// figure out sensor with highest score
//			if (sFCU.sNavigation.sCS[u8LCIndex].u32Score > maxScore)
//			{
//				maxScore = sFCU.sNavigation.sCS[u8LCIndex].u32Score;
//				sFCU.sNavigation.u8masterSensor = u8LCIndex;
//				same = 0;
//			}
//			else if (sFCU.sNavigation.sCS[u8LCIndex].u32Score == maxScore)
//			{
//				same = 1;
//			}
//			else
//			{
//				same = 0;
//			}
//		}
//		if (same = 0)
//		{
//			// figure out sensor with least uncertainty
//			Luint32 minUncert=sFCU.sNavigation.sCS[0].u32XPosUncert;
//			for (u8LCIndex = 1; u8LCIndex < C_FCU__NAVIGATION_NUM_CONTRAST_SENSORS; u8LCIndex++)
//			{
//				if (sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert < minUncert)
//				{
//					minUncert = sFCU.sNavigation.sCS[u8LCIndex].u32XPosUncert
//					sFCU.sNavigation.u8masterSensor = u8LCIndex;
//				}
//			}
//		}
//
//	}
//
//}

/** The longitudenal position down the tube */
/*
input
=====
contrast sensor 1 value
contrast sensor 2 value
contrast sensor 3 value
laser range finder value
acceleration
acceleration uncertainty
acceleration validity
*/

/*
output
======
speed
speed uncertainty
speed validity
*/
void vFCU_FLIGHTCTL_NAVIGATION__CalcSpeed(void)
{
	
}

/** The longitudenal position down the tube */
/*
input
=====
accelerometer 1 value
accelerometer 2 value
pitch
roll
yaw
*/

/*
output
======
acceleration
acceleration uncertainty
acceleration validity
*/
//void vFCU_FLIGHTCTL_NAVIGATION__CalcAcceleration(void)
//{
//	// use pitch, yaw and roll along with accelerometer data to get corrected acceleration
//	Lfloat32 f32LongitudenalAcceleration;
//	if (sFCU.sNavigation.f32LongitudenalPosition < MAX_LONGETIUDENAL_POSITION_USE_ACCELEROMETER)
//	{
//		// get filtered accelerometer value. need to confirm how we get the data
//		Lfloat32 f32Accel1 = sFCU.sFlightControl.sAccelerometer[0].getAccelerationFiltered();
//		Lfloat32 f32Accel2 = sFCU.sFlightControl.sAccelerometer[1].getAccelerationFiltered();
//
//		// compute final longitudenal acceleration as the mean of the acceleration from valid accelerometers
//		f32LongitudenalAcceleration = (f32Accel1[0] + f32Accel2[0] + f32Accel1[1] + f32Accel2[1] + f32Accel1[2] + f32Accel2[2]) / 6;
//	}
//	else
//	{
//		// depending on position down the tube, use laser range finder to compute acceleration
//		f32LongitudenalAcceleration = getAccelerationFromLaserRangeFinder();
//	}
//
//	// TODO compensate for thermal drift?
//}

Luint8 u8FCU_FCTL_NAV__GetPodSpeedTooHigh(void)
{
	Luint8 u8Test;
	return u8Test;
}

Luint32 u32FCU_FCTL_NAV__PodSpeed(void)
{
//do something with it
}

Luint32 u32FCU_FCTL_NAV__GetRearPos(void)
{
//do something with it
}

Luint32 u32FCU_FCTL_NAV__GetFrontPos(void)
{
//do something with it
}

Luint32 u32FCU_FCTL_NAV__Get_Accel_mmss(void)
{
//do something with it
}

Luint32 u32FCU_FCTL_LASERORIENT__Get_Z_Pos()
{
	//TODO: WRITE THIS ONE
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
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
