/**
 * @file		LaserOrientation.h
 * @brief		Orientation and Position from Distance Lasers
 * @author		David, Alessandro
 * @copyright	rLoop Inc.
 * @st_fileID
 */

/*******************************************************************************
Defines
*******************************************************************************/
#define PI 3.14159265359
//TODO this is probably not a great idea, 
//	intended for readability of plane eqn constants and coordinates...
#define X 0U
#define Y 1U
#define Z 2U
#define A 0U
#define B 1U
#define C 2U
#define D 3U


/** State types for the LaserOrientation state machine */
	/** ADDED TO FCU_CORE__TYPES.H */

// typedef enum
// {

// 	/** do nothing*/
// 	LASER_ORIENTATION_STATE__IDLE = 0U,

// 	/** We are in an error condition */
// 	LASER_ORIENTATION_STATE__ERROR,

// 	/** init the device, force a reset */
// 	LASER_ORIENTATION_STATE__INIT,

// 	/** Wait for a number of processing loops to expire */
// 	LASER_ORIENTATION_STATE__WAIT_LOOPS,

// 	/** Get laser measurements and states from optoncdt code */
// 	LASER_ORIENTATION_STATE__GET_LASER_DATA,

// 	LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST,

// 	LASER_ORIENTATION_STATE__RECALCULATE_YAW_AND_LATERAL,


// }E_LASER_ORIENTATION__STATE_T;


/*******************************************************************************
Structures - ADDED TO FCU_CORE.H
*******************************************************************************/
//	/** Main orientation parameter structure */
//	struct
//	{
//		Lint16 s16Roll;
//		Lint16 s16Pitch;
//		Lint16 s16Yaw;
//		Lfloat32 f32Lateral;
//		Lint16 s16TwistPitch; // TODO s8?
//		Lint16 s16TwistRoll; // TODO s8?
//
//		//Basically the vehicle is a static reference and we recalculate the orientation
//		//of the ground plane relative to the vehicle and the hover engines
//		Lfloat32 f32PlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms
//		Lfloat32 f32TwistPlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms // to be built with vCalculateGroundPlane() using the second laser triplet
//
//		/** sub-structure for ground lasers and their measurements*/
//		struct
//		{
//			Lfloat32 f32Position[3]; // x,y,z
//			Lfloat32 f32Measurement; // measurement returned from the distance laser
//			// TODO: need eState
//		}sGroundLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_GROUND];
//
//		/** sub-structure for beam lasers and their measurements*/
//		struct
//		{
//			Lfloat32 f32Position[3]; // x,y,z
//			Lfloat32 f32Measurement; // measurement returned from the distance laser
//			// TODO: need eState
//		}sBeamLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_BEAM];
//
//		/** sub-structure for hover engine positions and their hover heights*/
//		struct
//		{
//			Lfloat32 f32Position[3]; // x,y,z
//			Lfloat32 f32Measurement; // height of hover engine above ground
//		}sHoverEngines[C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES];
//
//		E_LaserOrientation_STATES_T eState
//
//	}sOrient;

/*******************************************************************************
Function Prototypes
*******************************************************************************/

// Prototyped in fcu_core.h
	// void vFCU_LASER_ORIENTATION__Init(void);
	// void vFCU_LASER_ORIENTATION__Process(void);

// needs to be prototyped in fcu_core.h once finished
	// type(?) sFCU_ORIENTATION__Get_Params(void);

void vCalcRoll(void);
void vCalcPitch(void);
void vCalcTwistRoll(void);
void vCalcTwistPitch(void);
Lfloat32 f32PointToPlaneDistance(Lfloat32 f32Position[3]);
void vPrintPlane(void);
void vCalculateGroundPlane(Luint8 u8A, Luint8 u8B, Luint8 u8C, Lfloat32 *pf32PlaneEqnCoeffs[4]);
void vCalcYaw(void);
void vCalcLateral(void);
