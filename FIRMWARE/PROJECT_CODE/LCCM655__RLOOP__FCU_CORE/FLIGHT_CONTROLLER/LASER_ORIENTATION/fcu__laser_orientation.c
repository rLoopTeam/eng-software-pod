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
	// sFCU.sLasers.sOptoLaser[] need consistency in laser/HE numbering convention between this file and optoncdt.c
	 	// My code here has forced that the optoncdt's are ordered as:
	 		// 0-4: Ground facing lasers
	 		// 5-6: I-beam facing lasers

	// If we are using anything involving floating point trig and that trig
		// is safety critical (i.e. pod distance or braking) then we must also do a
		// parallel equation in another data type to prevent the sorts of errors that
		// are commonly seen with floating point trig.

	 	// trig functions used in this code (search "trig" to find all cases)
	 		// f32NUMERICAL_Atan()
	 		// acos() (pi/2 - asin())
				// C_NUMERICAL__PI/2 - f32NUMERICAL_Asine
	 		// f32NUMERICAL_Cosine()


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U

//the structure
extern struct _strFCU sFCU;

//locals
static void vFCU_FLIGHTCTL_LASERORIENT__CalcRoll(void);
static void vFCU_FLIGHTCTL_LASERORIENT__CalcPitch(void);
static void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistRoll(void);
static void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistPitch(void);
static Lfloat32 f32FCU_FLIGHTCTL_LASERORIENT__PointToPlaneDistance(Lfloat32 f32Position[3]);
static void vFCU_FLIGHTCTL_LASERORIENT__CalculateGroundPlane(Luint8 u8A, Luint8 u8B, Luint8 u8C, Lfloat32 *pf32PlaneEqnCoeffs);
static void vFCU_FLIGHTCTL_LASERORIENT__CalcYaw(void);
static void vFCU_FLIGHTCTL_LASERORIENT__CalcLateral(void);



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
	// TODO: This data should be read in from EEPROM so a rebuild is not necessary to incorporate changes

	//Ground Facing Laser Positions
	 // Laser.f32Position[LASER_ORIENT__Z] is the reading when pod is sitting flat
  	   // (historic def: For the laser positions Z should be the reading when the HDK is sitting flat on the 4 hover engines)
	sFCU.sFlightControl.sOrient.sGroundLasers[0].f32Position[3] = {888, 888, 888}; // ground laser 1 position {x,y,z}
	sFCU.sFlightControl.sOrient.sGroundLasers[1].f32Position[3] = {-888, 888, 888}; // ground laser 2 position {x,y,z}
	sFCU.sFlightControl.sOrient.sGroundLasers[2].f32Position[3] = {888, -888, 888}; // ground laser 3 position {x,y,z}
	sFCU.sFlightControl.sOrient.sGroundLasers[3].f32Position[3] = {888,888,888}; // ground laser 4 position {x,y,z}

	// I-Beam laser positions

	//todo: following laser installation, need to measure the distance between the ibeam lasers and the pod centerline (mount should be orthogonal)
	//todo: change to a 2 dim array, but for now i'll leave as is to not get biebered

	sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[3] = {888, 888, 0};  // i-beam laser 1 position {x,y,z} //todo: first index of this array should have the x separation of the lasers - to be measured on pod
	sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[3] = {0, 888, 0};  // i-beam laser 2 position {x,y,z}

	//Hover Engine Positions {x,y,z} (from top view)
	sFCU.sFlightControl.sOrient.sHoverEngines[0].f32Position[3] = {888, 888, 888}; // Forward Top Left {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[1].f32Position[3] = {888, 888, 888}; // Forward Top Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[2].f32Position[3] = {888, 888, 888}; // Forward Bottom Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[3].f32Position[3] = {888, 888, 888}; // Forward Bottom Left {x,y,z}

	sFCU.sFlightControl.sOrient.sHoverEngines[4].f32Position[3] = {888, 888, 888}; // Rear Top Left {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[5].f32Position[3] = {888, 888, 888}; // Rear Top Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[6].f32Position[3] = {888, 888, 888}; // Rear Bottom Right {x,y,z}
	sFCU.sFlightControl.sOrient.sHoverEngines[7].f32Position[3] = {888, 888, 888}; // Rear Bottom Left {x,y,z}

	Luint8 u8Counter = 0U;
	// Init measurements and error states to zero
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_GROUND; u8Counter++)
	{
		sFCU.sFlightControl.sOrient.sGroundLasers[u8Counter].f32Measurement = 0.0F;
		sFCU.sFlightControl.sOrient.sGroundLasers[u8Counter].u8Error = 0U;
	} 

	for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_IBEAM; u8Counter++)
	{
		sFCU.sFlightControl.sOrient.sBeamLasers[u8Counter].f32Measurement = 0.0F;
		sFCU.sFlightControl.sOrient.sBeamLasers[u8Counter].u8Error = 0U;
	} 

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
			sFCU.sFlightControl.sOrient.eState = LASER_ORIENTATION_STATE__GET_LASER_DATA;
			break;

		case LASER_ORIENTATION_STATE__GET_LASER_DATA:
			/** store each laser's most recent distance measurement and error state to sOrient struct */

			for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_GROUND; u8Counter++)
			{
				sFCU.sFlightControl.sOrient.sGroundLasers[u8Counter].f32Measurement = f32FCU_LASEROPTO__Get_Distance(u8Counter);
				sFCU.sFlightControl.sOrient.sGroundLasers[u8Counter].u8Error = u8FCU_LASEROPTO__Get_Error(u8Counter);
			} 

			for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_IBEAM; u8Counter++)
			{
				sFCU.sFlightControl.sOrient.sBeamLasers[u8Counter].f32Measurement = f32FCU_LASEROPTO__Get_Distance(u8Counter + C_FCU__NUM_LASERS_GROUND); // kinda hacky; consistency in laser/HE numbering should help ground this
				sFCU.sFlightControl.sOrient.sBeamLasers[u8Counter].u8Error = u8FCU_LASEROPTO__Get_Error(u8Counter + C_FCU__NUM_LASERS_GROUND);
			} 

			sFCU.sFlightControl.sOrient.eState = LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST;
			break;

		case LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST:
			/** count which lasers are not in the error state and append them to array */

			for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_GROUND; u8Counter++)
			{
				if(sFCU.sFlightControl.sOrient.sGroundLasers[u8Counter].u8Error != 1U)
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
				if(sFCU.sFlightControl.sOrient.sBeamLasers[u8Counter].u8Error != 1U)
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
				vFCU_FLIGHTCTL_LASERORIENT__CalcYaw_and_Lateral();

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

	//Angle between two planes
	sFCU.sFlightControl.sOrient.s16Roll = (Lint16)(C_NUMERICAL__PI/2 - f32NUMERICAL_Asine((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
}


/** The angle between two planes that yields the pitch */
void vFCU_FLIGHTCTL_LASERORIENT__CalcPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes
	sFCU.sFlightControl.sOrient.s16Pitch = (Lint16)(C_NUMERICAL__PI/2 - f32NUMERICAL_Asine((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32PlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Roll Twisting */
void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistRoll(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 1, f32vec1y = 0, f32vec1z = 0;

	//Angle between two planes
	sFCU.sFlightControl.sOrient.s16TwistRoll = (Lint16)(C_NUMERICAL__PI/2 - f32NUMERICAL_Asine((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
	// the discrepancy in roll measured by two triplets of lasers gives the twisting of the pod structure // TODO: check signs
	sFCU.sFlightControl.sOrient.s16TwistRoll -= sFCU.sFlightControl.sOrient.s16Roll;
}


/** Calculate the pod's twisting due to the lack of perfect rigidity of the substructure: Bending */
void vFCU_FLIGHTCTL_LASERORIENT__CalcTwistPitch(void)
{
	//Normal vector of the other plane
	Lfloat32 f32vec1x = 0, f32vec1y = 1, f32vec1z = 0;

	//Angle between two planes
	sFCU.sFlightControl.sOrient.s16TwistPitch = (Lint16)(C_NUMERICAL__PI/2 - f32NUMERICAL_Asine((double)((f32vec1x * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + f32vec1y * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + f32vec1z * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C]) / sqrt((double)(sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__A] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__B] + sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C] * sFCU.sFlightControl.sOrient.f32TwistPlaneCoeffs[LASER_ORIENT__C])))) * 10000);  // TODO: Trig
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


/** Calculate the pod's yaw and lateral translation */

// see documentation: http://confluence.rloop.org/display/SD/2.1.+Determine+Pod+Yaw+and+Lateral+Position+in+Tube

void vFCU_FLIGHTCTL_LASERORIENT__CalcYaw_and_Lateral(void)
{

	Lfloat32 f32Y, f32Y0, f32Y1, f32BeamThickness, f32LaserSeparation_X;

	f32BeamThickness = 0; // todo: probably not proper to define here...

	f32Y0 = sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Measurement - sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[1];
	f32Y1 = sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Measurement - sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[1];
	f32Y = f32Y0 + f32Y1;

	f32LaserSeparation_X = sFCU.sFlightControl.sOrient.sBeamLasers[0].f32Position[0] - sFCU.sFlightControl.sOrient.sBeamLasers[1].f32Position[0];

	sFCU.sFlightControl.sOrient.s16Yaw = (Lint16)(2 * f32NUMERICAL_Atan((f32LaserSeparation_X - sqrt(f32LaserSeparation_X * f32LaserSeparation_X + f32Y * f32Y - f32BeamThickness * f32BeamThickness)) / (f32BeamThickness - f32Y))); //todo: why is there a *10000 in old code?

	sFCU.sFlightControl.sOrient.f32Lateral = (f32Y0 - f32Y1) * f32NUMERICAL_Cosine(sFCU.sFlightControl.sOrient.s16Yaw) / 2;

}




/****************************************************************************/
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
