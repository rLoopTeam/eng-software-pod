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

/** State types for the LaserOrientation state machine */
typedef enum
{

	/** do nothing*/
	LaserOrientation_STATE__IDLE = 0U,

	/** We are in an error condition */
	LaserOrientation_STATE__ERROR,

	/** init the device, force a reset */
	LaserOrientation_STATE__INIT,

	/** Wait for a number of processing loops to expire */
	LaserOrientation_STATE__WAIT_LOOPS,

	/** Read the ADC */
	LaserOrientation_STATE__RECALCULATE_ORIENTATION,


}E_LaserOrientation_STATES_T;


/*******************************************************************************
Structures
*******************************************************************************/
struct _strComponent // TODO: might want to make a separate one for HE/laser, so that laser readings can be appended. or should hover height be set there similarly
{
	Lfloat32 f32Position[3]; // x,y,z
	Lfloat32 f32Measurement; // measurement returned from the distance lasers; height of hover engines above ground
};

struct _strPodOrientation
{
	Lint16 s16Roll;
	Lint16 s16Pitch;
	Lint16 s16Yaw;
	Lfloat32 f32Lateral;
	Lint16 s16TwistPitch; // TODO s8?
	Lint16 s16TwistRoll; // TODO s8?

	//Basically the vehicle is a static reference
	//and we recalculate the orientation of the
	//ground plane relative to the vehicle
	//and the hover engines
	Lfloat32 f32PlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms
	Lfloat32 f32TwistPlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms // to be built with CalculateGroundPlane using the second laser triplet
	
	E_LaserOrientation_STATES_T eState

}sOrient;

/*******************************************************************************
Function Prototypes
*******************************************************************************/

void vLaserOrientation__Init(void);
void vLaserOrientation__Process(void);
void vCalcRoll(void);
void vCalcPitch(void);
void vCalcTwistRoll(void);
void vCalcTwistPitch(void);
Lfloat32 f32PointToPlaneDistance(Lfloat32 f32Position[3]);
void vPrintPlane(void);
void vCalculateGroundPlane(struct sLaserA, struct sLaserB, struct sLaserC);
void vCalcYaw(void);
void vCalcLateral(void);
