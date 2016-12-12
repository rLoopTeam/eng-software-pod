/* TODO:
 * doxygen compatible commenting
 */

 /**
 * @file		LaserOrientation.c
 * @brief		Orientation and Position from Distance Lasers
 * @author		David, Dean, acaratel
 * @copyright	rLoop Inc.
 * @st_fileID
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


#include "../fcu_core.h"
#include "fcu__laser_orientation.h"
//old
	//#include "../../../COMMON_CODE/MULTICORE/LCCMXXX__MULTICORE__OPTONCDT/optoncdt.c"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ORIENTATION == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init any brakes variables, etc.
 * 
 *
 */
void vFCU_LASER_ORIENTATION__Init(void)
{
	// TODO: All positions of components need their positions measured and assigned here.
		// blocked by installation of the components

	//Ground Facing Laser Positions
	 // Laser.f32Position[Z] is the reading when pod is sitting flat
  	   // (historic def: For the laser positions Z should be the reading when the HDK is sitting flat on the 4 hover engines)
	sFCU.sOrient.sGroundLasers[0].f32Position[3] = {8, 185, 35}; // ground laser 1 position {x,y,z}
	sFCU.sOrient.sGroundLasers[1].f32Position[3] = {-112, 18, 35}; // ground laser 2 position {x,y,z}
	sFCU.sOrient.sGroundLasers[2].f32Position[3] = {121, -53, 35}; // ground laser 3 position {x,y,z}
	sFCU.sOrient.sGroundLasers[3].f32Position[3] = {}; // ground laser 4 position {x,y,z}

	// I-Beam laser positions
	sFCU.sOrient.sBeamLasers[0].f32Position[3] = {25, 0, 35};  // i-beam laser 1 position {x,y,z}
	sFCU.sOrient.sBeamLasers[1].f32Position[3] = {25, 100, 35};  //i-beam laser 2 position {x,y,z}

	//Hover Engine Positions {x,y,z} (from top view)
	sFCU.sOrient.sHoverEngines[0].f32Position[3] = {61, 130, 0}; // Forward Top Left {x,y,z}
	sFCU.sOrient.sHoverEngines[1].f32Position[3] = {62, 129, 0}; // Forward Top Right {x,y,z}
	sFCU.sOrient.sHoverEngines[2].f32Position[3] = {62, 126, 0}; // Forward Bottom Right {x,y,z}
	sFCU.sOrient.sHoverEngines[3].f32Position[3] = {60, 128, 0}; // Forward Bottom Left {x,y,z}

	sFCU.sOrient.sHoverEngines[4].f32Position[3] = {0, 0, 0}; // Rear Top Left {x,y,z}
	sFCU.sOrient.sHoverEngines[5].f32Position[3] = {0, 0, 0}; // Rear Top Right {x,y,z}
	sFCU.sOrient.sHoverEngines[6].f32Position[3] = {0, 0, 0}; // Rear Bottom Right {x,y,z}
	sFCU.sOrient.sHoverEngines[7].f32Position[3] = {0, 0, 0}; // Rear Bottom Left {x,y,z}

	// Init PodOrientation values
	sFCU.sOrient.s16Roll = 0;
	sFCU.sOrient.s16Pitch = 0;
	sFCU.sOrient.s16Yaw = 0;
	sFCU.sOrient.f32Lateral = 0;
	sFCU.sOrient.s16TwistPitch = 0;
	sFCU.sOrient.s16TwistRoll = 0;

	sFCU.sOrient.f32PlaneCoeffs[4] = {0,0,0,0}; // ground plane coefficients
	sFCU.sOrient.f32TwistPlaneCoeffs[4] = {0,0,0,0}; // 2nd ground plane coefficients; compare to latter to get twist parameters

	sFCU.sOrient.eState = LASER_ORIENTATION_STATE__INIT;

	//vPrintPlane();
}


/***************************************************************************//**
 * @brief
 * Process the calculation of pod orientation and engine heights.
 * 
 */
void vFCU_LASER_ORIENTATION__Process(void)
{
	//handle the state machine
	switch(sFCU.sOrient.eState)
	{
		case LASER_ORIENTATION_STATE__IDLE:
			//do nothing
			break;

		case LASER_ORIENTATION_STATE__INIT:
			//do nothing?
			sFCU.sOrient.eState = LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST;
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
			Luint8 u8OperationalCount = 0U;
			Luint8 u8OperationalLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_GROUND];

			for(Luint8 u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_GROUND; u8Counter++)
			{
				if(sFCU.sOrient.sGroundLasers[u8Counter].eState != OPTONCDT_STATE__ERROR)
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
			    vCalculateGroundPlane(0U, 1U, 2U, &sFCU.sOrient.f32PlaneCoeffs[0]);
			    // 2nd triplet of ground lasers
			    vCalculateGroundPlane(1U, 2U, 3U, &sFCU.sOrient.f32TwistPlaneCoeffs[0]); 

			    for(Luint u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES; u8Counter++)
			    {
			    	// Calc the position of each hover engine
					sFCU.sOrient.sHoverEngines[u8Counter].f32Measurement = f32PointToPlaneDistance(sHE1.f32Position);
				}

				vCalcRoll();
				vCalcPitch();

				vCalcTwistRoll();
				vCalcTwistPitch();
			}
			else if(u8OperationalCount == 3U)
			{ 
				// calculate pitch and roll. cannot calculate twist.
			    vCalculateGroundPlane(u8OperationalLasers[0], u8OperationalLasers[1], u8OperationalLasers[2], &sFCU.sOrient.f32PlaneCoeffs[0]);

			    for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES; u8Counter++)
			    {
			    	// Calc the position of each hover engine
					sFCU.sOrient.sHoverEngines[u8Counter].f32Measurement = f32PointToPlaneDistance(sHE1.f32Position);
				}

				vCalcPitch();
				vCalcRoll();
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

			sFCU.sOrient.eState = LASER_ORIENTATION_STATE__RECALCULATE_YAW_AND_LATERAL;
			break;

		case LASER_ORIENTATION_STATE__RECALCULATE_YAW_AND_LATERAL:

			/** count which lasers are not in the error state and append them to array. */
			Luint8 u8OperationalCount = 0U;
			Luint8 u8OperationalLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_BEAM];

			for(Luint8 u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_BEAM; u8Counter++)
			{
				if(sFCU.sOrient.sBeamLasers[u8Counter].eState != OPTONCDT_STATE__ERROR)
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
				vRecalcYaw();
				vRecalcLateral();
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

			sFCU.sOrient.eState = LASER_ORIENTATION_STATE__INIT;
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
Lfloat32 f32PointToPlaneDistance(Lfloat32 f32Position[3])
{
	return 
	(
		(sFCU.sOrient.f32PlaneCoeffs[A] * f32Position[X] + sFCU.sOrient.f32PlaneCoeffs[B] * f32Position[Y] + sFCU.sOrient.f32PlaneCoeffs[C] * f32Position[Z] + sFCU.sOrient.f32PlaneCoeffs[D]) / 
		sqrt((double)(sFCU.sOrient.f32PlaneCoeffs[A] * sFCU.sOrient.f32PlaneCoeffs[A] + sFCU.sOrient.f32PlaneCoeffs[B] * sFCU.sOrient.f32PlaneCoeffs[B] + sFCU.sOrient.f32PlaneCoeffs[C] * sFCU.sOrient.f32PlaneCoeffs[C]))
	);
}


/** The angle between two planes that yield the roll */
void vCalcRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this and account for floating point errors 
	sFCU.sOrient.s16Roll = (Lint16)(acos((double)((f32vec1x * sFCU.sOrient.f32PlaneCoeffs[A] + f32vec1y * sFCU.sOrient.f32PlaneCoeffs[B] + f32vec1z * sFCU.sOrient.f32PlaneCoeffs[C]) / sqrt((double)(sFCU.sOrient.f32PlaneCoeffs[A] * sFCU.sOrient.f32PlaneCoeffs[A] + sFCU.sOrient.f32PlaneCoeffs[B] * sFCU.sOrient.f32PlaneCoeffs[B] + sFCU.sOrient.f32PlaneCoeffs[C] * sFCU.sOrient.f32PlaneCoeffs[C])))) * 10000);  // TODO: Trig
}


/** The angle between two planes that yields the pitch */
void vCalcPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this
	sFCU.sOrient.s16Pitch = (Lint16)(acos((double)((f32vec1x * sFCU.sOrient.f32PlaneCoeffs[A] + f32vec1y * sFCU.sOrient.f32PlaneCoeffs[B] + f32vec1z * sFCU.sOrient.f32PlaneCoeffs[C]) / sqrt((double)(sFCU.sOrient.f32PlaneCoeffs[A] * sFCU.sOrient.f32PlaneCoeffs[A] + sFCU.sOrient.f32PlaneCoeffs[B] * sFCU.sOrient.f32PlaneCoeffs[B] + sFCU.sOrient.f32PlaneCoeffs[C] * sFCU.sOrient.f32PlaneCoeffs[C])))) * 10000);  // TODO: Trig
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Roll Twisting */
void vCalcTwistRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this and account for floating point errors 
	sFCU.sOrient.s16TwistRoll = (Lint16)(acos((double)((f32vec1x * sFCU.sOrient.f32TwistPlaneCoeffs[A] + f32vec1y * sFCU.sOrient.f32TwistPlaneCoeffs[B] + f32vec1z * sFCU.sOrient.f32TwistPlaneCoeffs[C]) / sqrt((double)(sFCU.sOrient.f32TwistPlaneCoeffs[A] * sFCU.sOrient.f32TwistPlaneCoeffs[A] + sFCU.sOrient.f32TwistPlaneCoeffs[B] * sFCU.sOrient.f32TwistPlaneCoeffs[B] + sFCU.sOrient.f32TwistPlaneCoeffs[C] * sFCU.sOrient.f32TwistPlaneCoeffs[C])))) * 10000);  // TODO: Trig
	// the discrepancy in roll measured by two triplets of lasers gives the twisting of the pod structure // TODO: check signs
	sFCU.sOrient.s16TwistRoll -= sFCU.sOrient.s16Roll;
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Bending */
void vCalcTwistPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this
	sFCU.sOrient.s16TwistPitch = (Lint16)(acos((double)((f32vec1x * sFCU.sOrient.f32TwistPlaneCoeffs[A] + f32vec1y * sFCU.sOrient.f32TwistPlaneCoeffs[B] + f32vec1z * sFCU.sOrient.f32TwistPlaneCoeffs[C]) / sqrt((double)(sFCU.sOrient.f32TwistPlaneCoeffs[A] * sFCU.sOrient.f32TwistPlaneCoeffs[A] + sFCU.sOrient.f32TwistPlaneCoeffs[B] * sFCU.sOrient.f32TwistPlaneCoeffs[B] + sFCU.sOrient.f32TwistPlaneCoeffs[C] * sFCU.sOrient.f32TwistPlaneCoeffs[C])))) * 10000);  // TODO: Trig
	// the discrepancy in pitch measured by two triplets of lasers gives the bending of the pod structure // TODO: check signs
	sFCU.sOrient.s16TwistPitch -= sFCU.sOrient.s16Pitch;
}


/** Calculate the ground plane given three points */
// uses plane eqn: Ax + By + Cz + D = 0
void vCalculateGroundPlane(Luint8 u8A, Luint8 u8B, Luint8 u8C, Lfloat32 *pf32PlaneEqnCoeffs[4])
{
	Lfloat32 f32Vec1X, f32Vec1Y, f32Vec1Z;
	Lfloat32 f32Vec2X, f32Vec2Y, f32f32Vec2Z;
	Lfloat32 f32XProductX, f32XProductY, f32XProductZ;

	//Calculate two vectors in the plane
	f32Vec1X = sFCU.sOrient.sGroundLasers[u8A].f32Position[X] - sFCU.sOrient.sGroundLasers[u8B].f32Position[X];
	f32Vec1Y = sFCU.sOrient.sGroundLasers[u8A].f32Position[Y] - sFCU.sOrient.sGroundLasers[u8B].f32Position[Y];
	f32Vec1Z = (sFCU.sOrient.sGroundLasers[u8A].f32Position[Z] - sFCU.sOrient.sGroundLasers[u8A].f32Measurement) - (sFCU.sOrient.sGroundLasers[u8B].f32Position[Z] - sFCU.sOrient.sGroundLasers[u8B].f32Measurement);
	f32Vec2X = sFCU.sOrient.sGroundLasers[u8B].f32Position[X] - sFCU.sOrient.sGroundLasers[u8C].f32Position[X];
	f32Vec2Y = sFCU.sOrient.sGroundLasers[u8B].f32Position[Y] - sFCU.sOrient.sGroundLasers[u8C].f32Position[Y];
	f32Vec2Z = (sFCU.sOrient.sGroundLasers[u8B].f32Position[Z] - sFCU.sOrient.sGroundLasers[u8B].f32Measurement) - (sFCU.sOrient.sGroundLasers[u8C].f32Position[Z] - sFCU.sOrient.sGroundLasers[u8C].f32Measurement);

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
	pf32PlaneEqnCoeffs[A] = f32XProductX;
	pf32PlaneEqnCoeffs[B] = f32XProductY;
	pf32PlaneEqnCoeffs[C] = f32XProductZ;

	pf32PlaneEqnCoeffs[D] = -1 * (pf32PlaneEqnCoeffs[A] * sFCU.sOrient.sGroundLasers[u8A].f32Position[X] + pf32PlaneEqnCoeffs[B] * sFCU.sOrient.sGroundLasers[u8A].f32Position[Y] + pf32PlaneEqnCoeffs[C] * sFCU.sOrient.sGroundLasers[u8A].f32Position[Z]);

}


/** Calculate the pod's yaw */
void vCalcYaw(void)
{
  Lfloat32 f32SDif = (Lfloat32)(sFCU.sOrient.sBeamLasers[0].f32Measurement - sFCU.sOrient.sBeamLasers[1].f32Measurement);
  Lfloat32 f32DTan = f32SDif / ((Lfloat32)(sFCU.sOrient.sBeamLasers[0].f32Position[Z] - sFCU.sOrient.sBeamLasers[1].f32Position[Z]));
  sFCU.sOrient.s16Yaw = (Lint16)(f32NUMERICAL_Atan(f32DTan) * 10000);  // TODO: Trig
  // value expressed according to the rloop system variable
  // http://confluence.rloop.org/display/SD/System+Variables
}


/** Calculate the pod's lateral translation */
void vCalcLateral(void) 
{
  Lfloat32 f32XDif = (Lfloat32)(sFCU.sOrient.sBeamLasers[0].f32Position[Z] - sFCU.sOrient.sBeamLasers[1].f32Position[Z]);
  Lfloat32 f32Coef =
      ((Lfloat32)(sFCU.sOrient.sBeamLasers[1].f32Position[Z]) / f32XDif * sFCU.sOrient.sBeamLasers[0].f32Measurement) -
      ((Lfloat32)(sFCU.sOrient.sBeamLasers[0].f32Position[Z]) / f32XDif * sFCU.sOrient.sBeamLasers[1].f32Measurement);
  sFCU.sOrient.f32Lateral = f32Coef* f32NUMERICAL_Cosine((Lfloat32)(s16Yaw) / 10000.0);  // TODO: Trig
}


//historic
void vPrintPlane(void)
{
	// printf("A:%f B:%f C:%f D:%f\n", sFCU.sOrient.f32PlaneCoeffs[0], sFCU.sOrient.f32PlaneCoeffs[1], sFCU.sOrient.f32PlaneCoeffs[2], sFCU.sOrient.f32PlaneCoeffs[3]);
}

// TODO: Finish this!!!
/** get orientation parameters, for use by other files */
//  sFCU_ORIENTATION__Get_Params(void)
// {
// 	return sFCU.sOrient;
// }



#endif //C_LOCALDEF__LCCM655__ENABLE_ORIENTATION
#ifndef C_LOCALDEF__LCCM655__ENABLE_ORIENTATION
	#error
#endif
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif


