/**
 * @file		LaserOrientation.h
 * @brief		Orientation and Position from Distance Lasers
 * @author		David, Alessandro
 * @copyright	rLoop Inc.
 * @st_fileID
 */

// TODO split this code into fcu_core.h and fcu_core__types.h
 	// quarantined for now until it gets approval


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
// /** Structure for laser and hover engine positions and measurements*/
// struct _strComponent
// {
// 	Lfloat32 f32Position[3]; // x,y,z
// 	Lfloat32 f32Measurement; // measurement returned from the distance lasers; height of hover engines above ground
// 	// TODO: need eState	
// };

// struct _strPodOrientation
// {
// 	Lint16 s16Roll;
// 	Lint16 s16Pitch;
// 	Lint16 s16Yaw;
// 	Lfloat32 f32Lateral;
// 	Lint16 s16TwistPitch; // TODO s8?
// 	Lint16 s16TwistRoll; // TODO s8?

// 	//Basically the vehicle is a static reference
// 	//and we recalculate the orientation of the
// 	//ground plane relative to the vehicle
// 	//and the hover engines
// 	Lfloat32 f32PlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms
// 	Lfloat32 f32TwistPlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms // to be built with CalculateGroundPlane using the second laser triplet
	
// 	_strComponent sHoverEngines[C_LOCALDEF__LCCM655__NUM_HOVER_ENGINES];
// 	_strComponent sGroundLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_GROUND];
// 	_strComponent sBeamLasers[C_LOCALDEF__LCCM655__LASER_OPTONCDT__NUM_BEAM];

// 	E_LaserOrientation_STATES_T eState

// }sOrient;

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
void vCalculateGroundPlane(struct sLaserA, struct sLaserB, struct sLaserC);
void vCalcYaw(void);
void vCalcLateral(void);
