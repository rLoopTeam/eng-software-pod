/* TODO:
 * doxygen compatible commenting
 */

 /**
 * @file		LaserOrientation.c
 * @brief		Orientation and Position from Distance Lasers
 * @author		David, acaratel
 * @copyright	rLoop Inc.
 * @st_fileID
 */

// All units in mm, but the math doesn't care as long as you're consistent

// Yaw value expressed accordingly the rloop system variable
// http://confluence.rloop.org/display/SD/System+Variables

// TODO:  
	// If we are using anything involving floating point trig and that trig
	  // is safety critical (i.e. pod distance or braking) then we must also do a
	  // parallel equation in another data type to prevent the sorts of errors that
	  // are commonly seen with floating point trig.

	 	// trig functions used in this code (search "trig" to find all cases)
	 		// f32NUMERICAL_Atan()
	 		// acos() - not yet implemented
	 		// f32NUMERICAL_Cosine()

	// Need to access the laser states from optoncdt code

#include "../fcu_core.h"
#include "LaserOrientation.h"
#include "../../../COMMON_CODE/MULTICORE/LCCMXXX__MULTICORE__OPTONCDT/optoncdt.c" // TODO: check this

#define PI 3.14159265359
#define X 0U
#define Y 1U
#define Z 2U
#define A 0U
#define B 1U
#define C 2U
#define D 3U

/** set laser structs */
//_strComponent sHoverEngines[C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES]; // todo: this isn't declared in LOCALDEF yet; wait on Throttle work?
_strComponent sHoverEngines[8]; 
_strComponent sGroundLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_GROUND];
_strComponent sBeamLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_BEAM];

// coordinate system: +x in direction of travel; +z up wrt gravity
void vLaserOrientation__Init(void)
{
	// TODO: All positions of components need their positions measured and assigned here.
		// blocked by installation of the components

	//Ground Facing Laser Positions
	 // Laser.f32Position[Z] is the reading when pod is sitting flat
  	   // (historic def: For the laser positions Z should be the reading when the HDK is sitting flat on the 4 hover engines)
	sGroundLasers[0].f32Position[3] = {8, 185, 35}; // ground laser 1 position {x,y,z}
	sGroundLasers[1].f32Position[3] = {-112, 18, 35}; // ground laser 2 position {x,y,z}
	sGroundLasers[2].f32Position[3] = {121, -53, 35}; // ground laser 3 position {x,y,z}
	sGroundLasers[3].f32Position[3] = {}; // ground laser 4 position {x,y,z}

	// I-Beam laser positions
	sBeamLasers[0].f32Position[3] = {25, 0, 35};  // i-beam laser 1 position {x,y,z}
	sBeamLasers[1].f32Position[3] = {25, 100, 35};  //i-beam laser 2 position {x,y,z}

	//Hover Engine Positions {x,y,z} (from top view)
	sHoverEngines[0].f32Position[3] = {61, 130, 0}; // Top Left {x,y,z}
	sHoverEngines[1].f32Position[3] = {62, 129, 0}; // Top Right {x,y,z}
	sHoverEngines[2].f32Position[3] = {62, 126, 0}; // Bottom Right {x,y,z}
	sHoverEngines[3].f32Position[3] = {60, 128, 0}; // Bottom Left {x,y,z}

	sHoverEngines[4].f32Position[3] = {0, 0, 0}; // Top Left {x,y,z}
	sHoverEngines[5].f32Position[3] = {0, 0, 0}; // Top Right {x,y,z}
	sHoverEngines[6].f32Position[3] = {0, 0, 0}; // Bottom Right {x,y,z}
	sHoverEngines[7].f32Position[3] = {0, 0, 0}; // Bottom Left {x,y,z}

	// Init PodOrientation values
	sOrient.s16Roll = 0;
	sOrient.s16Pitch = 0;
	sOrient.s16Yaw = 0;
	sOrient.f32Lateral = 0;
	sOrient.s16TwistPitch = 0;
	sOrient.s16TwistRoll = 0;

	sOrient.f32PlaneCoeffs[4] = {0,0,0,0}; // ground plane coefficients
	sOrient.f32TwistPlaneCoeffs[4] = {0,0,0,0}; // 2nd ground plane coefficients; compare to latter to get twist parameters

	sOrient.eState = LaserOrientation_STATE__INIT;

	//vPrintPlane();
}


//Recalculate the orientation and engine heights
void vLaserOrientation__Process(void)
{
	//handle the state machine
	switch(sOrient.eState)
	{
		case LaserOrientation_STATE__IDLE:
			//do nothing
			break;

		case LaserOrientation_STATE__INIT:
			//do nothing?
			sOrient.eState = LaserOrientation_STATE__RECALCULATE_PITCH_ROLL_TWIST;
			break;

		case LaserOrientation_STATE__RECALCULATE_PITCH_ROLL_TWIST:
			/** count which lasers are not in the error state and append them to array */
			Luint8 u8OperationalCount = 0U;
			Luint8 u8OperationalLasers[4]; // TODO: array of struct types? {sLaserGround1, sLaserGround2, ...}

			if(sGroundLasers[0].eState != OPTONCDT_STATE__ERROR)
			{
				u8OperationalLasers[u8OperationalCount] = 1U; // Laser 1 works, store a 1 in the array to denote this
				u8OperationalCount += 1U; // increment count of operational lasers
			}
			else
			{
				// laser 1 bad
			}

			if(sGroundLasers[1].eState != OPTONCDT_STATE__ERROR)
			{
				u8OperationalLasers[u8OperationalCount] = 2U; // Laser 2 works, store a 2 in the array to denote this
				u8OperationalCount += 1U; // increment count of operational lasers
			}
			else
			{
				// laser 2 bad
			}

			if(sGroundLasers[2].eState != OPTONCDT_STATE__ERROR)
			{
				u8OperationalLasers[u8OperationalCount] = 3U; // Laser 3 works, store a 3 in the array to denote this
				u8OperationalCount += 1U; // increment count of operational lasers
			}
			else
			{
				// laser 3 bad
			}

			if(sGroundLasers[3].eState != OPTONCDT_STATE__ERROR)
			{
				u8OperationalLasers[u8OperationalCount] = 4U; // Laser 4 works, store a 4 in the array to denote this
				u8OperationalCount += 1U; // increment count of operational lasers 
			}
			else
			{
				// laser 4 bad
			}


			/** Calculate as many of the pods orientation parameters as possible based on the number of operational lasers */
			if(u8OperationalCount == 4U)
			{
				// calculate pitch, roll, and twist of the pod
				// 1st triplet of ground lasers
			    vCalculateGroundPlane(sGroundLasers[0], sGroundLasers[1], sGroundLasers[2], &sOrient.f32PlaneCoeffs[0]);
			    // 2nd triplet of ground lasers
			    vCalculateGroundPlane(sGroundLasers[1], sGroundLasers[2], sGroundLasers[3], &sOrient.f32TwistPlaneCoeffs[0]); 

			    for (u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES; u8Counter++)
			    {
			    	// Calc the position of each hover engine
					sHoverEngines[u8Counter].f32Measurement = f32PointToPlaneDistance(sHE1.f32Position);
				}

				vCalcRoll();
				vCalcPitch();

				vCalcTwistRoll();
				vCalcTwistPitch();
			}
			else if(u8OperationalCount == 3U)
			{ 
				// calculate pitch and roll. cannot calculate twist.
			    vCalculateGroundPlane(sGroundLasers[u8OperationalLasers[0]], sGroundLasers[u8OperationalLasers[1]], sGroundLasers[u8OperationalLasers[2]]);

			    for (u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES; u8Counter++)
			    {
			    	// Calc the position of each hover engine
					sHoverEngines[u8Counter].f32Measurement = f32PointToPlaneDistance(sHE1.f32Position);
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

			sOrient.eState = LaserOrientation_STATE__RECALCULATE_YAW_AND_LATERAL;
			break;

		case LaserOrientation_STATE__RECALCULATE_YAW_AND_LATERAL:

			/** count which lasers are not in the error state and append them to array. */
			Luint8 u8OperationalCount = 0U;
			Luint8 u8OperationalLasers[2];

			if(sBeamLasers[0].eState != OPTONCDT_STATE__ERROR)
			{
				u8OperationalLasers[u8OperationalCount] = 1U; // Laser 1 works, store a 1 in the array to denote this
				u8OperationalCount += 1U; // increment count of operational lasers
			}
			else
			{
				// Laser 1 is down
			}

			if(sBeamLasers[1].eState != OPTONCDT_STATE__ERROR)
			{
				u8OperationalLasers[u8OperationalCount] = 2U; // Laser 2 works, store a 2 in the array to denote this
				u8OperationalCount += 1U; // increment count of operational lasers
			}
			else
			{
				// Laser 2 is down
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

			sOrient.eState = LaserOrientation_STATE__INIT;
			break;

		case LaserOrientation_STATE__WAIT_LOOPS:
			// do nothing
			break;

		case LaserOrientation_STATE__ERROR:
			//some error has happened 
			break;
	}
}


/** Return the least distance between a point and the plane */
Lfloat32 f32PointToPlaneDistance(Lfloat32 f32Position[3])
{
	return 
	(
		(sOrient.f32PlaneCoeffs[A] * f32Position[X] + sOrient.f32PlaneCoeffs[B] * f32Position[Y] + sOrient.f32PlaneCoeffs[C] * f32Position[Z] + sOrient.f32PlaneCoeffs[D]) / 
		sqrt((double)(sOrient.f32PlaneCoeffs[A] * sOrient.f32PlaneCoeffs[A] + sOrient.f32PlaneCoeffs[B] * sOrient.f32PlaneCoeffs[B] + sOrient.f32PlaneCoeffs[C] * sOrient.f32PlaneCoeffs[C]))
	);
}


/** The angle between two planes that yield the roll */
void vCalcRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this and account for floating point errors 
	sOrient.s16Roll = (Lint16)(acos((double)((f32vec1x * sOrient.f32PlaneCoeffs[A] + f32vec1y * sOrient.f32PlaneCoeffs[B] + f32vec1z * sOrient.f32PlaneCoeffs[C]) / sqrt((double)(sOrient.f32PlaneCoeffs[A] * sOrient.f32PlaneCoeffs[A] + sOrient.f32PlaneCoeffs[B] * sOrient.f32PlaneCoeffs[B] + sOrient.f32PlaneCoeffs[C] * sOrient.f32PlaneCoeffs[C])))) * 10000);  // TODO: Trig
}


/** The angle between two planes that yields the pitch */
void vCalcPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this
	sOrient.s16Pitch = (Lint16)(acos((double)((f32vec1x * sOrient.f32PlaneCoeffs[A] + f32vec1y * sOrient.f32PlaneCoeffs[B] + f32vec1z * sOrient.f32PlaneCoeffs[C]) / sqrt((double)(sOrient.f32PlaneCoeffs[A] * sOrient.f32PlaneCoeffs[A] + sOrient.f32PlaneCoeffs[B] * sOrient.f32PlaneCoeffs[B] + sOrient.f32PlaneCoeffs[C] * sOrient.f32PlaneCoeffs[C])))) * 10000);  // TODO: Trig
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Roll Twisting */
void vCalcTwistRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this and account for floating point errors 
	sOrient.s16TwistRoll = (Lint16)(acos((double)((f32vec1x * sOrient.f32TwistPlaneCoeffs[A] + f32vec1y * sOrient.f32TwistPlaneCoeffs[B] + f32vec1z * sOrient.f32TwistPlaneCoeffs[C]) / sqrt((double)(sOrient.f32TwistPlaneCoeffs[A] * sOrient.f32TwistPlaneCoeffs[A] + sOrient.f32TwistPlaneCoeffs[B] * sOrient.f32TwistPlaneCoeffs[B] + sOrient.f32TwistPlaneCoeffs[C] * sOrient.f32TwistPlaneCoeffs[C])))) * 10000);  // TODO: Trig
	// the discrepancy in roll measured by two triplets of lasers gives the twisting of the pod structure // TODO: check signs
	sOrient.s16TwistRoll -= sOrient.s16Roll;
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Bending */
void vCalcTwistPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes // TODO: Need to find a Lachlan func for this
	sOrient.s16TwistPitch = (Lint16)(acos((double)((f32vec1x * sOrient.f32TwistPlaneCoeffs[A] + f32vec1y * sOrient.f32TwistPlaneCoeffs[B] + f32vec1z * sOrient.f32TwistPlaneCoeffs[C]) / sqrt((double)(sOrient.f32TwistPlaneCoeffs[A] * sOrient.f32TwistPlaneCoeffs[A] + sOrient.f32TwistPlaneCoeffs[B] * sOrient.f32TwistPlaneCoeffs[B] + sOrient.f32TwistPlaneCoeffs[C] * sOrient.f32TwistPlaneCoeffs[C])))) * 10000);  // TODO: Trig
	// the discrepancy in pitch measured by two triplets of lasers gives the bending of the pod structure // TODO: check signs
	sOrient.s16TwistPitch -= sOrient.s16Pitch;
}


//historic
void vPrintPlane(void)
{
	// printf("A:%f B:%f C:%f D:%f\n", sOrient.f32PlaneCoeffs[0], sOrient.f32PlaneCoeffs[1], sOrient.f32PlaneCoeffs[2], sOrient.f32PlaneCoeffs[3]);
}


/** Calculate the ground plane given three points */
//Ax + By + Cz + D = 0
void vCalculateGroundPlane(struct sLaserA, struct sLaserB, struct sLaserC, Lfloat32[4] *f32PlaneEqnCoeffs) // TODO: check implementation of the pointer input
{
	Lfloat32 f32Vec1X, f32Vec1Y, f32Vec1Z;
	Lfloat32 f32Vec2X, f32Vec2Y, f32f32Vec2Z;
	Lfloat32 f32XProductX, f32XProductY, f32XProductZ;

	//Calculate two vectors in the plane
	f32Vec1X = sGroundLasers[0].f32Position[X] - sGroundLasers[1].f32Position[X];
	f32Vec1Y = sGroundLasers[0].f32Position[Y] - sGroundLasers[1].f32Position[Y];
	f32Vec1Z = (sGroundLasers[0].f32Position[Z] - sGroundLasers[0].f32Measurement) - (sGroundLasers[1].f32Position[Z] - sGroundLasers[1].f32Measurement);
	f32Vec2X = sGroundLasers[1].f32Position[X] - sGroundLasers[2].f32Position[X];
	f32Vec2Y = sGroundLasers[1].f32Position[Y] - sGroundLasers[2].f32Position[Y];
	f32Vec2Z = (sGroundLasers[1].f32Position[Z] - sGroundLasers[1].f32Measurement) - (sGroundLasers[2].f32Position[Z] - sGroundLasers[2].f32Measurement);

	//Calculate the cross product of the vectors
	//to get a vector normal to the plane
	f32XProductX = f32Vec1Y*f32Vec2Z - f32Vec1Z*f32Vec2Y;
	f32XProductY = f32Vec1Z*f32Vec2X - f32Vec1X*f32Vec2Z;
	f32XProductZ = f32Vec1X*f32Vec2Y - f32Vec1Y*f32Vec2X;

	//The normal vector should be pointed in the +Z direction
	//It affects which side of the plane has negative distances
	if (f32XProductZ < 0){
		f32XProductX *= -1;
		f32XProductY *= -1;
		f32XProductZ *= -1;
	}

	//Plane in 3D: Ax + By + Cz + D = 0
	//A, B, C is the vector normal to the plane
	//Use one of our original points to calculate D
	f32PlaneEqnCoeffs[A] = f32XProductX;
	f32PlaneEqnCoeffs[B] = f32XProductY;
	f32PlaneEqnCoeffs[C] = f32XProductZ;

	f32PlaneEqnCoeffs[D] = -1 * (sOrient.f32PlaneCoeffs[A] * sGroundLasers[0].f32Position[X] + sOrient.f32PlaneCoeffs[B] * sGroundLasers[0].f32Position[Y] + sOrient.f32PlaneCoeffs[C] * sGroundLasers[0].f32Position[Z]);

}


/** Calculate the pod's yaw */
void vCalcYaw(void)
{
  Lfloat32 f32SDif = (Lfloat32)(sBeamLasers[0].f32Measurement - sBeamLasers[1].f32Measurement);
  Lfloat32 f32DTan = f32SDif / ((Lfloat32)(sBeamLasers[0].f32Position[Z] - sBeamLasers[1].f32Position[Z]));
  sOrient.s16Yaw = (Lint16)(f32NUMERICAL_Atan(f32DTan) * 10000);  // TODO: Trig
  // value expressed according to the rloop system variable
  // http://confluence.rloop.org/display/SD/System+Variables
}


/** Calculate the pod's lateral translation */
void vCalcLateral(void) 
{
  Lfloat32 f32XDif = (Lfloat32)(sBeamLasers[0].f32Position[Z] - sBeamLasers[1].f32Position[Z]);
  Lfloat32 f32Coef =
      ((Lfloat32)(sBeamLasers[1].f32Position[Z]) / f32XDif * sBeamLasers[0].f32Measurement) -
      ((Lfloat32)(sBeamLasers[0].f32Position[Z]) / f32XDif * sBeamLasers[1].f32Measurement);
  sOrient.f32Lateral = f32Coef* f32NUMERICAL_Cosine((Lfloat32)(s16Yaw) / 10000.0);  // TODO: Trig
}
