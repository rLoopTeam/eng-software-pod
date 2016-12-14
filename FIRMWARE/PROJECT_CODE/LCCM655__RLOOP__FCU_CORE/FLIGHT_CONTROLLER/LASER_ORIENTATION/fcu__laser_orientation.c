 /**
 * @file		FCU__LASER_ORIENTATION.c
 * @brief		Orientation and Position from Distance Lasers
 * @author		David, Dean, acaratel
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

// coordinate system: +x in direction of travel; +z up wrt gravity

// Yaw value expressed accordingly the rloop system variable
// http://confluence.rloop.org/display/SD/System+Variables

// TODO:  
	// NEED TO ACCESS THE LASER STATES AND MEASUREMENTS FROM OPTONCDT CODE
 		// sFCU.sLasers.sOptoLaser[] need to know which lasers are ground v ibeam facing.

 	// Need to finish function that provides orientation parameters when called from other files

	// If we are using anything involving floating point trig and that trig
	  // is safety critical (i.e. pod distance or braking) then we must also do a
	  // parallel equation in another data type to prevent the sorts of errors that
	  // are commonly seen with floating point trig.

	 	// trig functions used in this code (search "trig" to find all cases)
	 		// f32NUMERICAL_Atan()
	 		// acos() - not yet implemented
	 		// f32NUMERICAL_Cosine()


#include "../../fcu_core.h"
//old
	//#include "../../../COMMON_CODE/MULTICORE/LCCMXXX__MULTICORE__OPTONCDT/optoncdt.c"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U

//the structure
extern struct _strFCU sFCU;

//locals
void vFCU_FLIGHTCTL_LASERORIENT__CalcRoll(void);
void vFCU_FLIGHTCTL_LASERORIENT__CalcPitch(void);
void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistRoll(void);
void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistPitch(void);
Lfloat32 f32FCU_FLIGHTCTL_LASERORIENT__PointToPlaneDistance(Lfloat32 f32Position[3]);
void vFCU_FLIGHTCTL_LASERORIENT__PrintPlane(void);
void vFCU_FLIGHTCTL_LASERORIENT__CalculateGroundPlane(Luint8 u8A, Luint8 u8B, Luint8 u8C, Lfloat32 *pf32PlaneEqnCoeffs);
void vFCU_FLIGHTCTL_LASERORIENT__CalcYaw(void);
void vFCU_FLIGHTCTL_LASERORIENT__CalcLateral(void);



/***************************************************************************//**
 * @brief
 * Init any brakes variables, etc.
 * 
 *
 */
void vFCU_FLIGHTCTL_LASERORIENT__Init(void)
{
	// TODO: All positions of components need their positions measured and assigned here.
		// blocked by installation of the components

	//Ground Facing Laser Positions
	 // Laser.f32Position[LASER_ORIENT__Z] is the reading when pod is sitting flat
  	   // (historic def: For the laser positions Z should be the reading when the HDK is sitting flat on the 4 hover engines)
	sFCU.sFlightControl.sOrient.sGroundLasers[0].f32Position[3] = {8, 185, 35}; // ground laser 1 position {x,y,z}
	sFCU.sFlightControl.sOrient.sGroundLasers[1].f32Position[3] = {-112, 18, 35}; // ground laser 2 position {x,y,z}
	sFCU.sFlightControl.sOrient.sGroundLasers[2].f32Position[3] = {121, -53, 35}; // ground laser 3 position {x,y,z}
	sFCU.sFlightControl.sOrient.sGroundLasers[3].f32Position[3] = {}; // ground laser 4 position {x,y,z}

	// I-Beam laser positions
	sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[3] = {25, 0, 35};  // i-beam laser 1 position {x,y,z}
	sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[3] = {25, 100, 35};  //i-beam laser 2 position {x,y,z}

	//Hover Engine Positions {x,y,z} (from top view)
	sFCU.sFlightControl.sOrient.sHoverEngines[0].f32Position[3] = {61, 130, 0}; // Forward Top Left {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[1].f32Position[3] = {62, 129, 0}; // Forward Top Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[2].f32Position[3] = {62, 126, 0}; // Forward Bottom Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[3].f32Position[3] = {60, 128, 0}; // Forward Bottom Left {x,y,z}

	sFCU.sFlightControl.sOrient.sHoverEngines[4].f32Position[3] = {0, 0, 0}; // Rear Top Left {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[5].f32Position[3] = {0, 0, 0}; // Rear Top Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[6].f32Position[3] = {0, 0, 0}; // Rear Bottom Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[7].f32Position[3] = {0, 0, 0}; // Rear Bottom Left {x,y,z}

	// Init PodOrientation values
	sFCU.sFlightControl.sOrient.s16Roll = 0;
	sFCU.sFlightControl.sOrient.s16Pitch = 0;
	sFCU.sFlightControl.sOrient.s16Yaw = 0;
	sFCU.sFlightControl.sOrient.f32Lateral = 0.0F;
	sFCU.sFlightControl.sOrient.s16TwistPitch = 0;
	sFCU.sFlightControl.sOrient.s16TwistRoll = 0;

	sFCU.sFlightControl.sOrient.f32PlaneCoeffs[4] = {0,0,0,0}; // ground plane coefficients
	sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[4] = {0,0,0,0}; // 2nd ground plane coefficients; compare to latter to get twist parameters

	sFCU.sFlightControl.sOrient.eState = LASER_ORIENTATION_STATE__INIT;

}


/***************************************************************************//**
 * @brief
 * Process the calculation of pod orientation and engine heights.
 * 
 */
void vFCU_FLIGHTCTL_LASERORIENT__Process(void)
{
	Luint8 u8OperationalLasers[C_FCU__NUM_LASERS_GROUND];
	Luint8 u8OperationalCount = 0U;
	Luint8 u8Counter;


	//handle the state machine
	switch(sFCU.sFlightControl.sOrient.eState)
	{
		case LASER_ORIENTATION_STATE__IDLE:
			//do nothing
			break;

		case LASER_ORIENTATION_STATE__INIT:
			//do nothing?
			sFCU.sFlightControl.sOrient.eState = LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST;
			break;

		case LASER_ORIENTATION_STATE__GET_LASER_DATA:
			//get a lasers distance
				// relevant function from ../LASER_OPTO/fcu__laser_opto.c:
					// Lfloat32 f32FCU_LASEROPTO__Get_Distance(Luint8 u8LaserIndex)
				// or
					// sFCU.sLasers.sOptoLaser[].f32Distance

			// laser opto struct doesn't appear to have an error state
				// sFCU.sLasers.sOptoLaser[]
			break;

		case LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST:
			/** count which lasers are not in the error state and append them to array */

			for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_GROUND; u8Counter++)
			{
				if(sFCU.sFlightControl.sOrient.sGroundLasers[u8Counter].eState != OPTONCDT_STATE__ERROR)
				{
					// Laser works, store its index in the array
					u8OperationalLasers[u8OperationalCount] = u8Counter; 
					// increment count of operational lasers
					u8OperationalCount += 1U; 
				}
				else
				{
					// bad laser; dont append its index to array
				}
			}

			/** Calculate as many of the pods orientation parameters as possible based on the number of operational lasers */
			if(u8OperationalCount == 4U)
			{
				// calculate pitch, roll, and twist of the pod
				// 1st triplet of ground lasers
			    vFCU_FLIGHTCTL_LASERORIENT__CalculateGroundPlane(0U, 1U, 2U, &sFCU.sFlightControl.sOrient.f32PlaneCoeffs[0]);

			    // 2nd triplet of ground lasers
			    vFCU_FLIGHTCTL_LASERORIENT__CalculateGroundPlane(1U, 2U, 3U, &sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[0]);

			    for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
			    {
			    	// Calc the position of each hover engine
					sFCU.sFlightControl.sOrient.sHoverEngines[u8Counter].f32Measurement = f32FCU_FLIGHTCTL_LASERORIENT__PointToPlaneDistance(&sFCU.sFlightControl.sOrient.sHoverEngines[u8Counter].f32Position[0]);
				}

				vFCU_FLIGHTCTL_LASERORIENT__CalcRoll();
				vFCU_FLIGHTCTL_LASERORIENT__CalcPitch();

				vFCU_FLIGHTCTL_LASERORIENT__CalcTwistRoll();
				vFCU_FLIGHTCTL_LASERORIENT__CalcTwistPitch();
			}
			else if(u8OperationalCount == 3U)
			{ 
				// calculate pitch and roll. cannot calculate twist.
			    vFCU_FLIGHTCTL_LASERORIENT__CalculateGroundPlane(u8OperationalLasers[0], u8OperationalLasers[1], u8OperationalLasers[2], &sFCU.sFlightControl.sOrient.f32PlaneCoeffs[0]);

			    for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
			    {
			    	// Calc the position of each hover engine
					sFCU.sFlightControl.sOrient.sHoverEngines[u8Counter].f32Measurement = f32FCU_FLIGHTCTL_LASERORIENT__PointToPlaneDistance(&sFCU.sFlightControl.sOrient.sHoverEngines[u8Counter].f32Position[0]);
				}

				vFCU_FLIGHTCTL_LASERORIENT__CalcPitch();
				vFCU_FLIGHTCTL_LASERORIENT__CalcRoll();
			}
			else if(u8OperationalCount == 2U)
			{
				// there are 2 operable lasers; can't compute any of the orientation parameters directly, but can infer information from what we have.
				// TODO write code to infer orientation parameters
			}
			else
			{
				// there is 1 or fewer operable lasers; can't compute twist/pitch/roll/HE heights.
			}

			sFCU.sFlightControl.sOrient.eState = LASER_ORIENTATION_STATE__RECALCULATE_YAW_AND_LATERAL;
			break;

		case LASER_ORIENTATION_STATE__RECALCULATE_YAW_AND_LATERAL:

			/** count which lasers are not in the error state and append them to array. */
			Luint8 u8OperationalCount = 0U;
			Luint8 u8OperationalLasers[C_FCU__NUM_LASERS_IBEAM];

			for(Luint8 u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_IBEAM; u8Counter++)
			{
				if(sFCU.sFlightControl.sOrient.sBeamLasers[u8Counter].eState != OPTONCDT_STATE__ERROR)
				{
					// Laser works, store its index in the array
					u8OperationalLasers[u8OperationalCount] = u8Counter; 
					// increment count of operational lasers
					u8OperationalCount += 1U; 
				}
				else
				{
					// bad laser; dont append its index to array
				}
			}

			/** Calculate as many of the pods orientation parameters as possible based on the number of operational lasers */
			if(u8OperationalCount == 2U)
			{
				vFCU_FLIGHTCTL_LASERORIENT__RecalcYaw();

				vFCU_FLIGHTCTL_LASERORIENT__RecalcLateral();

			}
			else if(u8OperationalCount == 1U)
			{
				// At least one i-beam laser is down; can't explicitly compute yaw/translation.
				//TODO: assume yaw = 0 compute lateral translation?  or the opposite, depending on which parameter is more likely to deviate from its ideal value.
			}
			else 
			{
				// no i-beam lasers are working, no measurement can be made.
			}

			sFCU.sFlightControl.sOrient.eState = LASER_ORIENTATION_STATE__INIT;
			break;

		case LASER_ORIENTATION_STATE__WAIT_LOOPS:
			// do nothing
			break;

		case LASER_ORIENTATION_STATE__ERROR:
			//some error has happened 
			break;
	}
}


/** Return the least distance between a point and the plane */
Lfloat32 f32FCU_FLIGHTCTL_LASERORIENT__PointToPlaneDistance(Lfloat32 f32Position[3]) // TODO add a * since it's now called with ref &?
{
	return 
	(
		(sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] * f32Position[LASER_ORIENT__X] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] * f32Position[LASER_ORIENT__Y] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C] * f32Position[LASER_ORIENT__Z] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__D]) /
		sqrt((double)(sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C]))
	);
}


/** The angle between two planes that yield the roll */
void vFCU_FLIGHTCTL_LASERORIENT__CalcRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this and account for floating point errors 
	sFCU.sFlightControl.sOrient.s16Roll = (Lint16)(acos((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
}


/** The angle between two planes that yields the pitch */
void vFCU_FLIGHTCTL_LASERORIENT__CalcPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this
	sFCU.sFlightControl.sOrient.s16Pitch = (Lint16)(acos((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Roll Twisting */
void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this and account for floating point errors 
	sFCU.sFlightControl.sOrient.s16TwistRoll = (Lint16)(acos((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
	// the discrepancy in roll measured by two triplets of lasers gives the twisting of the pod structure // TODO: check signs
	sFCU.sFlightControl.sOrient.s16TwistRoll -= sFCU.sFlightControl.sOrient.s16Roll;
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Bending */
void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this
	sFCU.sFlightControl.sOrient.s16TwistPitch = (Lint16)(acos((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
	// the discrepancy in pitch measured by two triplets of lasers gives the bending of the pod structure // TODO: check signs
	sFCU.sFlightControl.sOrient.s16TwistPitch -= sFCU.sFlightControl.sOrient.s16Pitch;
}


/** Calculate the ground plane given three points */
// uses plane eqn: Ax + By + Cz + D = 0
void vFCU_FLIGHTCTL_LASERORIENT__CalculateGroundPlane(Luint8 u8A, Luint8 u8B, Luint8 u8C, Lfloat32 *pf32PlaneEqnCoeffs)
{
	Lfloat32 f32Vec1X, f32Vec1Y, f32Vec1Z;
	Lfloat32 f32Vec2X, f32Vec2Y, f32Vec2Z;
	Lfloat32 f32XProductX, f32XProductY, f32XProductZ;

	//Calculate two vectors in the plane
	f32Vec1X = sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Position[LASER_ORIENT__X] - sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Position[LASER_ORIENT__X];
	f32Vec1Y = sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Position[LASER_ORIENT__Y] - sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Position[LASER_ORIENT__Y];
	f32Vec1Z = (sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Position[LASER_ORIENT__Z] - sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Measurement) - (sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Position[LASER_ORIENT__Z] - sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Measurement);
	f32Vec2X = sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Position[LASER_ORIENT__X] - sFCU.sFlightControl.sOrient.sGroundLasers[u8C].f32Position[LASER_ORIENT__X];
	f32Vec2Y = sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Position[LASER_ORIENT__Y] - sFCU.sFlightControl.sOrient.sGroundLasers[u8C].f32Position[LASER_ORIENT__Y];
	f32Vec2Z = (sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Position[LASER_ORIENT__Z] - sFCU.sFlightControl.sOrient.sGroundLasers[u8B].f32Measurement) - (sFCU.sFlightControl.sOrient.sGroundLasers[u8C].f32Position[LASER_ORIENT__Z] - sFCU.sFlightControl.sOrient.sGroundLasers[u8C].f32Measurement);

	//Calculate the cross product of the vectors
	//to get a vector normal to the plane
	f32XProductX = f32Vec1Y*f32Vec2Z - f32Vec1Z*f32Vec2Y;
	f32XProductY = f32Vec1Z*f32Vec2X - f32Vec1X*f32Vec2Z;
	f32XProductZ = f32Vec1X*f32Vec2Y - f32Vec1Y*f32Vec2X;

	//The normal vector should be pointed in the +Z direction
	//It affects which side of the plane has negative distances
	if(f32XProductZ < 0)
	{
		f32XProductX *= -1;
		f32XProductY *= -1;
		f32XProductZ *= -1;
	}

	//Plane in 3D: Ax + By + Cz + D = 0
	//A, B, C is the vector normal to the plane
	//Use one of our original points to calculate D
	pf32PlaneEqnCoeffs[LASER_ORIENT__A] = f32XProductX;
	pf32PlaneEqnCoeffs[LASER_ORIENT__B] = f32XProductY;
	pf32PlaneEqnCoeffs[LASER_ORIENT__C] = f32XProductZ;

	pf32PlaneEqnCoeffs[LASER_ORIENT__D] = -1 * (pf32PlaneEqnCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Position[LASER_ORIENT__X] + pf32PlaneEqnCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Position[LASER_ORIENT__Y] + pf32PlaneEqnCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.sGroundLasers[u8A].f32Position[LASER_ORIENT__Z]);

}


/** Calculate the pod's yaw */
void vFCU_FLIGHTCTL_LASERORIENT__CalcYaw(void)
{
  Lfloat32 f32SDif = (Lfloat32)(sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Measurement - sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Measurement);

  Lfloat32 f32DTan = f32SDif / ((Lfloat32)(sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[LASER_ORIENT__Z] - sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[LASER_ORIENT__Z]));

  sFCU.sFlightControl.sOrient.s16Yaw = (Lint16)(f32NUMERICAL_Atan(f32DTan) * 10000);  // TODO: Trig
  // value expressed according to the rloop system variable
  // http://confluence.rloop.org/display/SD/System+Variables
}


/** Calculate the pod's lateral translation */
void vFCU_FLIGHTCTL_LASERORIENT__CalcLateral(void) 
{
  Lfloat32 f32XDif = (Lfloat32)(sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[LASER_ORIENT__Z] - sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[LASER_ORIENT__Z]);

  Lfloat32 f32Coef =
      ((Lfloat32)(sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[LASER_ORIENT__Z]) / f32XDif * sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Measurement) -
      ((Lfloat32)(sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[LASER_ORIENT__Z]) / f32XDif * sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Measurement);

  sFCU.sFlightControl.sOrient.f32Lateral = f32Coef* f32NUMERICAL_Cosine((Lfloat32)(sFCU.sFlightControl.sOrient.s16Yaw) / 10000.0);  // TODO: Trig
}


//historic
void vFCU_FLIGHTCTL_LASERORIENT__PrintPlane(void)
{
	// printf("A:%f B:%f C:%f D:%f\n", sFCU.sFlightControl.sOrient.f32PlaneCoeffs[0], sFCU.sFlightControl.sOrient.f32PlaneCoeffs[1], sFCU.sFlightControl.sOrient.f32PlaneCoeffs[2], sFCU.sFlightControl.sOrient.f32PlaneCoeffs[3]);
}


/***************************************************************************//**
/** Functions to retrieve orientation parameters, to be called from other files */

/** Get pod's current Roll */
Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Roll()
{
	return sFCU.sFlightControl.sOrient.s16Roll
}

/** Get pod's current Pitch */
Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Pitch()
{
	return sFCU.sFlightControl.sOrient.s16Pitch
}

/** Get pod's current Yaw */
Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Yaw()
{
	return sFCU.sFlightControl.sOrient.s16Yaw
}

/** Get Lateral translation parameter */
Lfloat32 f32FCU_FLIGHTCTL_LASERORIENT__Get_Lateral()
{
	return sFCU.sFlightControl.sOrient.f32Lateral
}

/** Get pitch due to lack of perfect structural rigidity */
Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_TwistPitch()
{
	return sFCU.sFlightControl.sOrient.s16TwistPitch
}

/** Get roll due to lack of perfect structural rigidity */
Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_TwistRoll()
{
	return sFCU.sFlightControl.sOrient.s16TwistRoll
}


#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION
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


