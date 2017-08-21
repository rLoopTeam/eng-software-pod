/**
 * @file		FCU_CORE.H
 * @brief		Main header for the FCU
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.001
 */

#ifndef _FCU_CORE_H_
#define _FCU_CORE_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__types.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__defines.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__enums.h>

		#include <LCCM655__RLOOP__FCU_CORE/FAULTS/fcu__faults__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/BRAKES/fcu__brakes__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/ACCELEROMETERS/fcu__accel__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/LASER_OPTO/fcu__laser_opto__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/LASER_OPTO/fcu__laser_opto__laser_fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/THROTTLES/fcu__throttles__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/LASER_DISTANCE/fcu__laser_distance__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi__fault_flags.h>

		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi_defines.h>
		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi_types.h>

		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>
		#include <MULTICORE/LCCM418__MULTICORE__MMA8451/mma8451__types.h>

		//flight controller states
		#include <LCCM655__RLOOP__FCU_CORE/FLIGHT_CONTROLLER/fcu__flight_controller__state_types.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define C_MLP__MAX_AVERAGE_SIZE				(8U)

		/*******************************************************************************
		Structures
		*******************************************************************************/
		/** main flight control structure */
		struct _strFCU
		{
			/** Structure guard 1*/
			Luint32 u32Guard1;


			/** Navigation System */
			struct
			{

				/** The navigation state machine */
				TE_NAV_SM__TYPES sStateMachine;

				/** Is there a new navigation value available */
				Luint8 u8NewSampleAvail;

				/** Calculated Values */
				struct
				{
					/** What is our valid accel? */
					Lint32 s32Accel_mm_ss;

					/** The computed current velocity in mm/sec*/
					Lint32 s32Veloc_mm_s;

					/** Current displacement from some point */
					Lint32 s32Displacement_mm;

					/** Track position, which may be different from displacement */
					Lint32 s32Position_mm;

				}sCalc;

			}sNavigation;


            #if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U
			/** Navigation */
			struct
			{
				Lfloat32 f32LongitudinalPosition;
				Lfloat32 f32PositionValidity;
				Lfloat32 f32LongitudinalSpeed;
				Lfloat32 f32LongitudinalSpeedUncertainty;
				Luint8 u8LongitudinalSpeedValidity;
				Lfloat32 f32LongitudinalAcceleration;
				Luint8 u8LongitudinalAccelerationValidity;
				Luint8 u8LRFAvailable;
				Luint8 u8masterSensor;
				Luint8 u8GeneralStripeCount;
				Luint32 u3210MSNavTimer;
				Luint32 u3210MSLRFTimer;
				Luint32 u3210MSAccelHiValTimer;
				Luint32 u3210MSAccelLoValTimer;
				Luint32 u3210MSDetectStripeTimer;
				Luint32 u3210MSBetweenStripeTimer;

					struct
					{
						Luint32 u32StripeCount;
						Luint32 u32Xpos;
						Luint32 u32XPosUncert;
						Luint32 u32NoseToSensorDist;
						Luint32 u32Score;
						Luint8 u8Valid;
					}sCS[C_FCU__NAV_NUM_CONTRAST_SENSORS];

					struct
					{
						Lfloat32 f32Accel;
						Luint8 u8Valid;
					}sAccel[C_LOCALDEF__LCCM418__NUM_DEVICES];

			}sNavigation;
            #endif

#if 0
			/** Hover Engines Control Structure */
			struct
			{
				/** The hover engines state machine */
				E_FCU__HOVERENGINES_STATES_T eState;

				/** The hover engines input commands from GS */
				Luint32 eGSCommands;

				/** The hover engines command values from GS */
				Luint32 u32CommandValues;


				/** Internal parameters */
				struct
				{
					Luint8  u8Enable;
					Luint8  u8RunAuto;
					Luint8  u8SpeedState;
					Luint32 u32CurrentRPMValue[8];
					Luint8  u8TempVar;

				}sIntParams;

			}sHoverEngines;
#endif //0

			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
			#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
			/** State Machine Structure **/
			struct
			{
                /** Main pod state machine structure. @see TE_POD_STATE_T */
				TS_FCTL__STATE_MACHINE_T sm;

				/** Main pod command holder. @see TE_POD_COMMAND_T */
				strPodCmd command;
	
				/** Enum for Pod Status for SpaceX telemetry */
				// @todo: Update code to change this as needed when states change
				E_FCU__POD_STATUS ePodStatus;
				
				// Timers and timeouts:
				struct
				{
					/** Accel to Coast Interlock backup timeout */
					TS_FCTL__TIMEOUT_T pAccel_To_Coast_Max;

					/** Coast interlock timeout */
					TS_FCTL__TIMEOUT_T pCoast_To_Brake;

					/** Brake to Spindown backup timeout */
					TS_FCTL__TIMEOUT_T BrakeToSpindownBackupTimeout;

					/** Spindown to Idle backup timeout */
					TS_FCTL__TIMEOUT_T SpindownToIdleBackupTimeout;

				}sTimers;
				
				/** Interlock command timeouts */
				strInterlockCommand command_interlocks[POD_COMMAND__NUM_COMMANDS];
				
			}sStateMachine;
			#endif//C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
			#endif//C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL

			/** Auto sequence state machine */
			E_FCU__AUTO_SEQUENCE_STATE_T eAutoSeqState;

			/** The init statemachine */
			E_FCU__INIT_STATE_TYPES eInitStates;


			/** Fault handling subsystem */
			struct
			{
				/** top level fault tree subsystem for the flight controller */
				FAULT_TREE__PUBLIC_T sTopLevel;

			}sFaults;


			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

			/** Global brakes system */
			struct
			{
				/** individual brake fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The brakes state machine */
				E_FCU_BRAKES__STATES_T eBrakeStates;


				/** Brake Development mode */
				struct
				{

					/** Are we in develompent mode? */
					Luint8 u8DevMode;

					/** Key to enable develompent mode checks */
					Luint32 u32DevKey;

				}sBrakesDev;

				/** just a global movement planner ID */
				Luint32 u32MoveTaskID;

				/** Claibration Systems */
				struct
				{
					//Cal State
					E_FCU_CAL_BRAKES__STATES_T eState;

				}sCalibration;

				/** 100ms tick */
				Luint8 u8Timer_100ms;

			}sBrakesGlobal;


			/** Brake(S) Substructure */
			struct
			{

				/** Limit switch structure
				 * There are two limit switches per brake assy
				 */
				struct
				{

					/** An edge was captured on the interrupt subsystem
					 * Its up to some other layer to clear the flag once its used.
					 */
					Luint8 u8EdgeSeen;

					#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
						/** Debugs how many interrupts have been received
						 */
						Luint32 u8EdgeSeenCnt;
					#endif

					/** The program index for N2HET, even if not used on both channels */
					Luint16 u16N2HET_Prog;

					/** The current state of the switch */
					E_FCU__SWITCH_STATE_T eSwitchState;

					#ifdef WIN32
						/** Allow us to inject swiches on WIN32 */
						Luint8 u8InjectedValue;
					#endif

				}sLimits[BRAKE_SW__MAX_SWITCHES];

				/** Linear position sensor detail */
				struct
				{
					/** This is the sample from the ADC converter */
					Luint16 u16ADC_Sample;

					/** This is the filtered result from the raw sample */
					Luint16 u16ADC_FilteredSample;

					/** The zero value when the brakes are fully retracted */
					Luint16 u16ADC_Zero;

					/** Current ADC span to convert ADC units into engineering units */
					Lfloat32 f32SystemSpan;

					/** ADC value - Zero Value */
					Lint32 s32ADC_Minus_Zero;

					/** Brake linear pos feedback*/
					Lfloat32 f32BrakePosition_mm;

					/** Average Counter	for MLP filter function */
					Luint16 u16AverageCounter;

					/** Average Array for MLP filter function */
					Luint16 u16AverageArray[C_MLP__MAX_AVERAGE_SIZE];

					/** Lowest MLP Value*/
					Luint16 lowest_value;

					/** Highest MLP Value */
					Luint16 highest_value;

					#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
						/** Debug how many times we get a zero */
						Luint32 zero_count;
					#endif


					#ifdef WIN32
					struct
					{
						/** The ADC sample for WIN32 emulation */
						Luint16 u16ADC_Sample;

					}sWin32;
					#endif

					/** Temporary use; identify when startup sequence has ended and mlp won't return 0. */
					Luint8 u8Running;
				}sMLP;


				/** Movement Planner */
				struct
				{

					/** The required linear veloc for the move */
					Lint32 s32LinearVeloc_um_s;

					/** The required linear accel for the move */
					Lint32 s32LinearAccel_um_ss;

					/** The position that we have requested the brake to move to */
					Lint32 s32MoveToPos;

					/** The current position of the lead screw */
					Lint32 s32currentPos;

				}sMove;


				/** Current Details */
				struct
				{

					/** the screw position in mm */
					Lfloat32 f32ScrewPos_mm;

					/** I-Beam distance in mm */
					Lfloat32 f32IBeam_mm;

					/** I-Beam distance in mm */
					Lfloat32 f32MLP_mm;


				}sCurrent;


				/** The target move position */
				struct
				{
					/** The current targeted IBeam brake distance */
					Lfloat32 f32IBeam_mm;

					/** target lead screw position */
					Lfloat32 f32LeadScrew_mm;

					/** Microns for the planner */
					Luint32 u32LeadScrew_um;

				}sTarget;

				Luint8 u8BrakeSWErr;

			}sBrakes[C_FCU__NUM_BRAKES];
			#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES

			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
			/** Accel subsystem */
			struct
			{
				/** Accel subsystem faults */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** Thresholding system */
				struct
				{

					/** Set to 1 when the threshold has been reached*/
					Luint8 u8ThresholdTrue;

					/** The threshold time in count of 10ms increments */
					Luint32 u32ThreshTime_x10ms;

					/** The threshold acceleration in mm_ss*/
					Lint32 s32Thresh_Accel_mm_ss;

					/** Count of the number of 10ms interrupts */
					Luint32 u3210MS_Counter;

				}sThresh;

				/** Data validity checks */
				struct
				{

					/** Is a new sample of data ready */
					Luint8 u8NewDataAvail;

					/** Is the accel module enabled? */
					Luint8 u8Enabled;

					/** Is our data source valid, if we loose accel, we loose all data */
					Luint8 u8IsValid;

					/** What is our valid accel? */
					Lint32 s32ValidAccel_mm_ss;

					/** The computed current velocity in mm/sec*/
					Lint32 s32ValidVeloc_mm_s;

					/** Current displacement */
					Luint32 s32ValidDisplacement_mm;

				}sValid;


				/** individual accel channels */
				struct
				{

					/** A new update for this channel is available */
					Luint8 u8NewSampleAvail;

					/** most recent recorded sample from the Accel in raw units */
					Lint16 s16LastSample[MMA8451_AXIS__MAX];

					/** do some filtering on our target axis */
					Luint16 u16FilterCounter;
					Lint16 s16FilterValues[C_FCU__ACCEL_FILTER_WINDOW];
					Lint16 s16FilteredResult;

					#if C_LOCALDEF__LCCM418__ENABLE_G_FORCE == 1U
						/** Last sample of the G-Force*/
						Lfloat32 f32LastG[MMA8451_AXIS__MAX];
					#endif

					/** The current acceleration in mm/sec^2 based on the last sample */
					Lint32 s32CurrentAccel_mm_ss;

					/** The computed current velocity in mm/sec*/
					Lint32 s32CurrentVeloc_mm_s;

					/** The previous veloc has just been calculated in the last time period */
					Lint32 s32PrevVeloc_mm_s;

					/** Current displacement */
					Luint32 s32CurrentDisplacement_mm;

					/** Previous displacement */
					Luint32 s32PrevDisplacement_mm;



				}sChannels[C_LOCALDEF__LCCM418__NUM_DEVICES];

			}sAccel;
			#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL

			
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
			/** Pusher Interface Layer */
			struct
			{
				/** Guard variable 1*/
				Luint32 u32Guard1;

				/** Pusher Fault Flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The pusher subsystem state machine */
				E_FCU_PUSHER__STATES_T eState;

				/** Interlock switch status */
				E_FCU_PUSHPIN_STATE_T ePusher_Status;



				/** Timer of 10ms ticks used for switch state timing */
				Luint32 u32SwtichTimer;

				/** Switch interfaces */
				struct
				{
					/** N2HET Program index for edge interrupts*/
					Luint16 u16N2HET_Prog;

					/** The state of the switch based on the last sample */
					Luint8 u8SwitchState;

					/** Edge interrupt has occurred, meaning there has been a switch transition */
					Luint8 u8EdgeFlag;

				}sSwitches[2];

				/** Guard variable 2*/
				Luint32 u32Guard2;

			}sPusher;
			#endif //C_LOCALDEF__LCCM655__ENABLE_PUSHER


			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
			/** Overall structure for the OPTONCDT laser interfaces */
			struct
			{

				/** Upper guard */
				Luint32 u32Guard1;

				/** Global laser fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** state machine for processing the OptoNCDT systems */
				E_FCU_OPTOLASER__STATE_T eOptoNCDTState;

				/** A 100ms counter to wait until the lasers have powered up*/
				Luint32 u32LaserPOR_Counter;

				/** The opto NCDT laser interfaces */
				struct
				{
					/** Individual laser fault flags */
					FAULT_TREE__PUBLIC_T sFaultFlags;

					/** RX byte state machine */
					E_OPTONCDT__RX_STATE_T eRxState;

					/** A new packet is available for distance processing */
					Luint8 u8NewPacket;

					/** A new packet is available and ready to be filtered */
					Luint8 u8ReadyForFiltering;

					/** Array to hold new bytes received */
					Luint8 u8NewByteArray[3U];

					/** The most recent distance*/
					Lfloat32 f32DistanceRAW;

					/** New distance has been measured, other layer to clear it */
					Luint8 u8NewDistanceAvail;

					/** is f32Distance equal to error value? */
					Luint8 u8Error;


					/** Diagnostic Counters */
					struct
					{

						/** We have received an error code from the laser */
						Luint32 u32ErrorCode;

						/** First packet byte was not in the correct place */
						Luint32 u32Byte1Wrong;

						/** Successful packet count */
						Luint32 u32Success;

						/** Keep track of how long its takes between bytes being seen */
						Luint32 u32ByteSeenTimeOut;

					}sCounters;

					/** Filtered data structure */
					struct
					{

						/** The filtered height */
						Lfloat32 f32FilteredValue;

						/** The previous value */
						Lfloat32 f32PreviousValue;

					}sFiltered;

				}sOptoLaser[C_FCU__NUM_LASERS_OPTONCDT];

				/** Calibration storage offset */
				struct
				{
					/** The offset value */
					Lfloat32 f32Offset;

				}sCalibration[C_FCU__NUM_LASERS_OPTONCDT];

				/** Ethernet Injection values */
				struct
				{

					/** Is eth inj enabled? */
					Luint8 u8InjectionEnabled;

					/** What is the eth injection key, check this against enabled value */
					Luint32 u32InjectionKey;

					/** The actual injected values */
					Lfloat32 f32InjValues[C_FCU__NUM_LASERS_OPTONCDT];

				}sInjection;


				/** Lower guard */
				Luint32 u32Guard2;


			}sLaserOpto;
			#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT

			/** structure for the laser distance interface */
			struct
			{

				/** Data valid structure */
				struct
				{

					/** Do we want to enable this data source */
					Luint8 u8Enable;

					/** Is this data source valid?*/
					Luint8 u8Valid;

					/** What is our valid accel? */
					Lint32 s32ValidAccel_mm_ss;

					/** The computed current velocity in mm/sec*/
					Lint32 s32ValidVeloc_mm_s;

					/** Current displacement */
					Luint32 s32ValidDistance_mm;

				}sValid;


				/** Individual laser fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** main state machine */
				E_FCU_LASERDIST__STATE_T eLaserState;

				/** RX byte state machine */
				E_LASERDIST__RX_STATE_T eRxState;

				/** A 100ms counter to wait until the lasers have powered up*/
				Luint32 u32LaserPOR_Counter;

				/** Number of 100ms increments the new bytes have been seen */
				Luint32 u32BytesSeen_Counter;

				/** Number of 100ms increments the new packets have been seen */
				Luint32 u32PacketsSeen_Counter;


				/** A new packet is available for distance processing */
				Luint8 u8NewPacket;

				/** Array to hold new bytes received */
				Luint8 u8NewByteArray[5];

				/** The most recent distance in mm*/
				Lint32 s32Distance_mm;

				/** Previous distance of last sample */
				Lint32 s32PrevDistance_mm;

				Lint32 s32Velocity_mm_s;
				Lint32 s32PrevVelocity_mm_s;

				Lint32 s32Accel_mm_ss;
				Lint32 s32PrevAccel_mm_ss;

				/** The final filtered distance*/
				//Lfloat32 f32DistanceFiltered;

				/** New distance has been measured, other layer to clear it */
				Luint8 u8NewDistanceAvail;

				/** For emulation over UDP */
				struct
				{

					/** Is the EMU enabled ?*/
					Luint8 u8EmulationEnabled;

					/** Special Key = 0x98984343 to prevent above flag being 1 */
					Luint32 u32EmuKey;

					/** Emulated Distance */
					Lint32 s32Distance;

				}sEmu;



				/** binary mode data */
				struct
				{

					/** Hold the Rx data in binary millimeter mode */
					union
					{

						Luint8 u8[4];
						Luint32 u32;

					}unRx;

					/** Count of missed start packets */
					Luint32 u32Counter__MissedStart;

					/** Bad distance measurement */
					Luint32 u32Counter__BadDistance;

					/** Error code value counter */
					Luint32 u32Counter__ErrorCode;

				}sBinary;

			}sLaserDist;


			/** Flight Controller */
			struct
			{
				#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
				/** Orientation structure */

				/** Main orientation parameter structure */
				struct
				{
					Lint16 s16Roll;
					Lint16 s16Pitch;
					Lint16 s16Yaw;
					Lfloat32 f32Lateral;
					Lint16 s16TwistPitch; // TODO s8?
					Lint16 s16TwistRoll; // TODO s8?

					//Basically the vehicle is a static reference and we recalculate the orientation
					//of the ground plane relative to the vehicle and the hover engines
					Lfloat32 f32PlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms
					Lfloat32 f32TwistPlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms // to be built with vCalculateGroundPlane() using the second laser triplet

					/** sub-structure for ground lasers and their measurements*/
					struct
					{
						Lfloat32 f32Position[3]; // x,y,z
						Lfloat32 f32Measurement; // measurement returned from the distance laser
						Luint8 u8Error; //Error value as read from fcu__laser_opto.c 
					}sGroundLasers[C_FCU__NUM_LASERS_GROUND];

					/** sub-structure for beam lasers and their measurements*/
					struct
					{
						Lfloat32 f32Position[3]; // x,y,z
						Lfloat32 f32Measurement; // measurement returned from the distance laser
						Luint8 u8Error; //Error value as read from fcu__laser_opto.c 
					}sBeamLasers[C_FCU__NUM_LASERS_IBEAM];

					/** sub-structure for hover engine positions and their hover heights*/
					struct
					{
						Lfloat32 f32Position[3]; // x,y,z
						Lfloat32 f32Measurement; // height of hover engine above ground
					}sHoverEngines[C_FCU__NUM_HOVER_ENGINES];

					E_LASER_ORIENTATION__STATE_T eState;

				}sOrient;
				
				#else
					//Needed for compatibiltiy
					Luint8 u8Dummy;
				#endif


				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
				/** Track database structure */
				struct
				{
					/** Track DB fault flags system */
					FAULT_TREE__PUBLIC_T sFaultFlags;

					/** The current selected track DB, defaults to 0 and user
					 * must set from GS
					 */
					Luint32 u32CurrentDB;

				}sTrackDB;
				#endif //#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U

				#if C_LOCALDEF__LCCM655__ENABLE_GEOM == 1U
				/** Geometry */
				struct
				{
					/** F32 Geom Items */
					struct tsNUM_f32Vector_3D vf32Geom[C_FCU__GEOM__NUM_ITEMS_F32];

					/** S32 Geom Items */
					struct tsNUM_s32Vector_3D vs32Geom[C_FCU__GEOM__NUM_ITEMS_S32];

				}sGeom;
				#endif //C_LOCALDEF__LCCM655__ENABLE_GEOM

				/** Accel, Veloc and Displacement blender system */
				struct
				{

					/** The current working values we are using for flight */
					struct
					{
						/** Current computed accel in ms ss*/
						Lint32 s32Accel_mm_ss;

						/** Computed velocity */
						Lint32 s32Veloc_mm_s;

						/** The actual measured distance to the target infront of the pod */
						Lint32 s32Distance_mm;

					}sWorking;

				}sBlender;


			}sFlightControl;


			#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U
			struct
			{

				/** The flags indicating pod health */
				FAULT_TREE__PUBLIC_T sHealthFlags;

			}sPodHealth;
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
			/** Contrast sensor structure */
			struct
			{

				/** Upper guard */
				Luint32 u32Guard1;

				/** Top level fault system */
				FAULT_TREE__PUBLIC_T sFaultFlags;


				/** The final computed values taking into account fault tolerance and
				 * laser processing techiques */
				struct
				{

					/** The current velocity in mm/sec */
					Luint32 u32CurrentVeloc_mms;

				}sComputed;

				/** Individual contrast senors */
				struct
				{

					/** The N2HET program index */
					Luint16 u16N2HET_Index;

					/** Individual fault flags */
					FAULT_TREE__PUBLIC_T sFaultFlags;

					/** Top level distance remaining in the run in mm */
					Luint32 u32DistElapsed_mm;

					/** Distance elapsed between last stripe */
					Luint32 u32DistLastStripe_mm;

					/** Current velocity in mm/sec */
					Luint32 u32CurrentVeloc_mms;

					/** Current velocity in mm/sec */
					Luint32 u32PreviousVeloc_mms;

					/** Current acceleration */
					Lint32 s32CurrentAccel_mm_ss;

				}sSensors[LASER_CONT__MAX];


				Luint32 u32Guard2;

				/** a timing based list to store the rising and falling edges of each laser */
				struct
				{

					/** Rising edge time stamp */
					Luint64 u64RisingList[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** Falling edge time stamp */
					Luint64 u64FallingList[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** list of time that has elapsed between sensor marks */
					Luint64 u64ElapsedList_Rising[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** Rising edge count */
					Luint16 u16RisingCount;

					/** Can maintan a list of prev processed counts */
					Luint16 u16PrevRisingCount;

					/** Falling edge count */
					Luint16 u16FallingCount;

					/** signalled by the rising edge that a new item is avail */
					Luint8 u8NewRisingAvail;

				}sTimingList[LASER_CONT__MAX];

				Luint32 u32Guard3;

				/** The track database for each sensor */
				struct
				{
					/** The distance elapsed in the tube */
					Luint32 u32DistanceElapsed_mm[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** The current optical marker */
					Luint8 u8ElapsedCount;

					/** Distance Remaining - computed*/
					Luint32 u32DistElapsed;

					/** Last Increment */
					Luint32 u32LastIncrement;

				}sTrackDatabase[LASER_CONT__MAX];

				Luint32 u32Guard4;

			}sContrast;
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
			/** Ethernet comms structure */
			struct
			{
				/** our hardware MAC */
				Luint8 u8MACAddx[6];

				/** our locally assigned IP*/
				Luint8 u8IPAddx[4];

			}sEthernet;


			/** UDP diagnostics system */
			struct
			{

				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u810MS_Flag;

				/** 250ms timer for our fault data */
				Luint8 u8250MS_Flag;

				/** The next packet type to transmit */
				E_NET__PACKET_T eTxPacketType;

				/** If the user has enabled Tx streaming */
				E_NET__PACKET_T eTxStreamingType;

				/** Timer for the Drive Pod comms watchdog */
				Luint32 u32_10MS_GS_COMM_Timer;

			}sUDPDiag;

			/** SpaceX required transmission */
			struct
			{
				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u8100MS_Flag;

				/** Test counter for telemetry */
				Luint32 u32TestCounter;

			}sSpaceX;

			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
			/** ASI Comms Layer */
			struct
			{
				Luint32 u32Guard1;

				/** the real time scan holding values */
				struct
				{
					/** fault flags */
					Luint16 u16Faults;

					/** Temp in deg C*/
					Lfloat32 f32TempC;

					/** Motor Current */
					Lfloat32 f32MotorCurrentA;

					/** Throttle Voltage*/
					Lfloat32 f32ThrottleV;

					/** Current RPM */
					Luint16 u16RPM;

				}sHolding[C_FCU__NUM_HOVER_ENGINES];

				/** The main state machine */
				E_FCU__ASI_STATE_T eMainState;

				/** When scanning our HE's, maintain the scan index */
				Luint8 u8ScanIndex;

				/** 10ms timer used for scanning */
				Luint8 u810MS_Timer;

				/** ASI Subsystemfaults */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The Rx Counter Position */
				Luint8 u8RxCount;

				#ifdef WIN32
					/** On win32 generate save the mux */
					Luint8 u8MuxChannel;
				#endif

				/** List of commands to send in round robbin*/
				E_FCU_ASI_BAC_OBJECT_TYPES__T eCommandList[C_FCU__ASI_COMMAND_LIST_MAX];

				/** Keep track of the command */
				Luint8 u8CommandListIndex;

				/** Do we need to issue a throttle command? */
				Luint8 u8ThrottleCommand[C_FCU__NUM_HOVER_ENGINES];

				/** Command issued to change ASI's into serial throttle mode */
				Luint8 u8SerialNetworkCommand[C_FCU__NUM_HOVER_ENGINES];

				/** The throttle value to change to */
				Luint16 u16Throttle[C_FCU__NUM_HOVER_ENGINES];


				/** The lower guard */
				Luint32 u32Guard2;

			}sASI;
			#endif

			/** Input data for throttle layer */
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
			struct strThrottleInterfaceData
			{

				/* State Variable*/
				E_THROTTLE_STATES_T eState;

				/** Throttle fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The requested RPM of each HE */
				Luint16 u16RequestedRPM[C_FCU__NUM_HOVER_ENGINES];

				/** The requested ramp or step mode */
				E_THROTTLE_CTRL_T eRequestedMode[C_FCU__NUM_HOVER_ENGINES];

				/** The current (actually set RPM) */
				Luint16 u16CurrentRPM[C_FCU__NUM_HOVER_ENGINES];

				/** A 100ms timer for each ramp increment */
				Luint8 u8100ms_Timer[C_FCU__NUM_HOVER_ENGINES];

				/** During run keep an index of the last servied HE */
				Luint8 u8RunIndex;

				/** For development mode */
				struct
				{

					/** Dev mode enabled */
					Luint8 u8Enabled;

					/** Dev mode security key, 0x77558833U */
					Luint32 u32SecurityKey;

				}sDevMode;

			} sThrottle;
			#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLE


			
			/** Critical info from the BMS */
			struct
			{
				/** Highest cell temp */
				Lfloat32 f32HighestTemp;

				/** Average Temp cell (battery temp) */
				Lfloat32 f32AverageTemp;

				/** Total pack voltage */
				Lfloat32 f32PackVoltage;

				/** Highest cell voltage */
				Lfloat32 f32HighestCellVoltage;

				/** Lowest cell voltage */
				Lfloat32 f32LowestCellVoltage;

				/** PV Temp */
				Lfloat32 f32PV_Temp;

				/** PV Press */
				Lfloat32 f32PV_Press;


			}sBMS[2];

			/** Structure guard 2*/
			Luint32 u32Guard2;


		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		//core
		DLL_DECLARATION void vFCU__Init(void);
		DLL_DECLARATION void vFCU__Process(void);
		DLL_DECLARATION void vFCU__RTI_100MS_ISR(void);
		DLL_DECLARATION void vFCU__RTI_10MS_ISR(void);


		//flight controller
		void vFCU_FCTL__Init(void);
		void vFCU_FCTL__Process(void);
		void vFCU_FCTL__Config_From_Database(void);

			// General Timer and timeouts
			void vFCU_FCTL__TIMEOUT__Init(TS_FCTL__TIMEOUT_T *pTimeout, Luint32 u32Duration_x10ms);
			void vFCU_FCTL__TIMEOUT__Restart(TS_FCTL__TIMEOUT_T *pTimeout);
			void vFCU_FCTL__TIMEOUT__Reset(TS_FCTL__TIMEOUT_T *pTimeout);
			void vFCU_FCTL__TIMEOUT__Ensure_Started(TS_FCTL__TIMEOUT_T *pTimeout);
			Luint8 u8FCU_FCTL__TIMEOUT__Is_Expired(TS_FCTL__TIMEOUT_T *pTimeout);
			void vFCU_FCTL__TIMEOUT__Update_x10ms(TS_FCTL__TIMEOUT_T *pTimeout);

			// Flight Control interlock guards
			void vFCU_FCTL__InterlockGuard__Init(strInterlockCommand *pInterlockGuard, Luint32 u32Duration_x10ms);
			void vFCU_FCTL__InterlockGuard__Unlock(strInterlockCommand *pInterlockGuard);
			Luint8 u8FCU_FCTL__InterlockGuard__IsUnlocked(strInterlockCommand *pInterlockGuard);
			void vFCU_FCTL__InterlockGuard__Reset(strInterlockCommand *pInterlockGuard);
			void vFCU_FCTL__InterlockGuard__UpdateTimeout_x10ms(strInterlockCommand *pInterlockGuard);

			// Helper functions for executing interlock commands
			void vFCU_FCTL__NetCommand_Unlock(TE_POD_COMMAND_T command);
			Luint8 vFCU_FCTL__NetCommand_IsEnabled(TE_POD_COMMAND_T command);
			// @todo: change this to take a pointer (or a copy) of a pod command struct
			// @todo: is this only for the state machine? I suppose commands could do things unrelated to the SM...
			void vFCU_FCTL__PushCommand(TE_POD_COMMAND_T command);

			//main state machine
			void vFCU_FCTL_MAINSM__Init(void);
			void vFCU_FCTL_MAINSM__Process(void);
			void vFCU_FCTL_MAINSM__10MS_ISR(void);
			void vFCU_FCTL_MAINSM__100MS_ISR(void);

				void vFCU_FCTL_MAINSM__Step(TS_FCTL__STATE_MACHINE_T* p_sm);

				Luint8 u8FCU_FCTL_MAINSM__Check_IsEntering(const TS_FCTL__STATE_MACHINE_T *cpSM, TE_POD_STATE_T eTestState);
				Luint8 u8FCU_FCTL_MAINSM__Check_IsExiting(const TS_FCTL__STATE_MACHINE_T *cpSM, TE_POD_STATE_T eTestState);
				Luint8 u8FCU_FCTL_MAINSM__Check_IsTransitioning(const TS_FCTL__STATE_MACHINE_T *cpSM);


                //  Pod guard/check functions 
                Luint8 pod_init_complete();
                Luint8 armed_wait_checks_ok();
                Luint8 drive_checks_ok();
                Luint8 flight_prep_checks_ok();
                Luint8 flight_readiness_checks_ok();
                Luint8 accel_confirmed();
                Luint8 pusher_separation_confirmed();
                Luint8 pod_stop_confirmed();
                Luint8 spindown_complete_confirmed();

                //  Pod state transition functions
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__INIT();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__IDLE();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__TEST_MODE();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__DRIVE();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__ARMED_WAIT();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__FLIGHT_PREP();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__READY();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__ACCEL();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__COAST_INTERLOCK();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__BRAKE();
                void vFCU_FCTL_MAINSM_XSN__POD_STATE__SPINDOWN();

                //  Pod command functions
                void cmd_POD_COMMAND__IDLE();
                void cmd_POD_COMMAND__TEST_MODE();
                void cmd_POD_COMMAND__DRIVE();
                void cmd_POD_COMMAND__FLIGHT_PREP();
                void cmd_POD_COMMAND__ARMED_WAIT();
                void cmd_POD_COMMAND__READY();

			//navigation
			void vFCU_FCTL_NAV__Init(void);
			void vFCU_FCTL_NAV__Process(void);
			void vFCU_FCTL_NAV__Reset(Luint32 u32Key);
			void vFCU_FCTL_NAV__Run(void);
			Lint32 s32FCU_FCTL_NAV__Get_Accel_mm_ss(void);
			Lint32 s32FCU_FCTL_NAV__Get_Veloc_mm_s(void);
			Lint32 s32FCU_FCTL_NAV__Get_Displacement_mm(void);
			Lint32 s32FCU_FCTL_NAV__Get_Track_Position_mm(void);



			//drive pod
			Luint32 u32FCU_NET_RX__GetGsCommTimer(void);

#if 0
			//blender
			void vFCU_FCTL_BLENDER__Init(void);
			void vFCU_FCTL_BLENDER__Process(void);
			Lint32 s32FCU_FCTL_BLENDER__Get_Accel_mmss(void);
			Lint32 s32FCU_FCTL_BLENDER__Get_Veloc_mms(void);
			Lint32 s32FCU_FCTL_BLENDER__Get_Displacement_mm(void);
			void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Veloc_mms);
			void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Veloc_mms);
			void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Veloc_mms);
			void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Accel_mmss);
			void vFCU_FCTL_BLENDER__Accel_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Accel_mmss);
			void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Accel_mmss);
			void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Disp_mm);
			void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Disp_mm);
			void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Disp_mm);
#endif //

			//track DB
			void vFCU_FCTL_TRACKDB__Init(void);
			void vFCU_FCTL_TRACKDB__Process(void);
			void vFCU_FCTL_TRACKDB__Set_CurrentDB(Luint32 u32Key, Luint32 u32TrackID);


				//get functions
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_CurrentDB(void);

				//accel system
				Luint8 u8FCU_FCTL_TRACKDB__Accel__Get_Use(void);
				Lint32 s32FCU_FCTL_TRACKDB__Accel__Get_Threshold_mm_ss(void);
				Lint32 s32FCU_FCTL_TRACKDB__Accel__Get_ThresholdTime_x10ms(void);
				Luint8 u8FCU_FCTL_TRACKDB__Accel__Get_UsePusherSeparaation(void);
				Luint32 u32FCU_FCTL_TRACKDB__Time__Get_Accel_to_Coast_Max(void);
				Luint32 u32FCU_FCTL_TRACKDB__Time__Get_Coast_to_Brake(void);

				//mem
				void vFCU_FCTL_TRACKDB_MEM__Init(void);
				void vFCU_FCTL_TRACKDB_MEM__Process(void);
				void vFCU_FCTL_TRACKDB_MEM__UploadChunk(Luint32 u32ChunkIndex, Luint32 u32Length, Luint8 *pu8Buffer);

				//win32
				void vFCU_FCTL_TRACKDB_WIN32__Init(void);
				void vFCU_FCTL_TRACKDB_WIN32__Process(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Clear_Array(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Get_Array(Luint8 *pu8ByteArray);
				DLL_DECLARATION Luint16 u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Array(Luint8 *pu8ByteArray);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Header(Luint32 u32Value);

				//accel system
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Use(Luint8 u8TrackIndex, Luint8 u8Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_mm_ss(Luint8 u8TrackIndex, Lint32 s32Thresh_mm_ss);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_x10ms(Luint8 u8TrackIndex, Luint32 u32Thresh_x10ms);

				//track system
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackStart_mm(Luint8 u8TrackIndex, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackEnd_mm(Luint8 u8TrackIndex, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackLength_mm(Luint8 u8TrackIndex, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Time__Accel_Coast_x10ms(Luint8 u8TrackIndex, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Time__Coast_Brake_x10ms(Luint8 u8TrackIndex, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_UsePusherSeparation(Luint8 u8TrackIndex, Luint8 u8Value);

				//CRC control
				DLL_DECLARATION Luint16 u16FCTL_TRAKDB_WIN32__ComputeCRC(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_CRC(Luint16 u16Value);


			//auto sequence
			void vFCU_MAINSM_AUTO__Init(void);
			void vFCU_MAINSM_AUTO__Process(void);
			Luint8 u8FCU_MAINSM_AUTO__Is_Busy(void);
			Luint8 u8FCU_MAINSM_AUTO__Is_Abort(void);

			//ethernet
			void vFCU_FCTL_ETH__Init(void);
			void vFCU_FCTL_ETH__Transmit(E_NET__PACKET_T ePacketType);

			//pod health
			void vFCU_PODHEALTH__Init(void);
			void vFCU_PODHEALTH__Process(void);

			// Laser Orientation
			void vFCU_FLIGHTCTL_LASERORIENT__Init(void);
			void vFCU_FLIGHTCTL_LASERORIENT__Process(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Roll(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Pitch(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Yaw(void);
			Lfloat32 f32FCU_FLIGHTCTL_LASERORIENT__Get_Lateral(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_TwistRoll(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_TwistPitch(void);

			//contrast sensor nav
			void vFCU_FLIGHTCTL_CONTRASTNAV__Init(void);
			void vFCU_FLIGHTCTL_CONTRASTNAV__Process(void);
			Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_Position_mm(void);
			Luint8 u8FCU_FLIGHTCTL_CONTRASTNAV__Get_IsFault(void);
			Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_FaultFlags(void);

			//brake profiler
			Lint16 s16FCU_FLIGHTCTL_BRAKES__Brake_Lookup(Luint32 u32Veloc_mms, Luint32 u32DragForce_n, Luint32 *pu32IBDistance_um);




		//network
		void vFCU_NET__Init(void);
		void vFCU_NET__Process(void);
		void vFCU_NET_RX__Init(void);
		Luint8 u8FCU_NET__Is_LinkUp(void);
		void vFCU_NET_RX__RxUDP(Luint8 * pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vFCU_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);

			//transmit
			void vFCU_NET_TX__Init(void);
			void vFCU_NET_TX__Process(void);
			void vFCU_NET_TX__10MS_ISR(void);
			void vFCU_NET_TX__100MS_ISR(void);

			//spaceX specific
			void vFCU_NET_SPACEX_TX__Init(void);
			void vFCU_NET_SPACEX_TX__Process(void);
			void vFCU_NET_SPACEX_TX__100MS_ISR(void);

		//fault handling layer
		void vFCU_FAULTS__Init(void);
		void vFCU_FAULTS__Process(void);
		Luint8 u8FCU_FAULTS__Get_IsFault(void);
		Luint32 u32FCU_FAULTS__Get_FaultFlags(void);

			//ethernet
			void vFCU_FAULTS_ETH__Init(void);
			void vFCU_FAULTS_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//laser contrast sensors
		void vFCU_LASERCONT__Init(void);
		void vFCU_LASERCONT__Process(void);
		void vFCU_LASERCONT__Reset(Luint32 u32Key);
		void vFCU_LASERCONT__ISR(E_FCU__LASER_CONT_INDEX_T eLaser, Luint32 u32Register);

			//timing list
			void vFCU_LASERCONT_TL__Init(void);
			void vFCU_LASERCONT_TL__Process(void);
			DLL_DECLARATION void vFCU_LASERCONT_TL__ISR(E_FCU__LASER_CONT_INDEX_T eLaser, Luint32 u32Register);
			Luint8 u8FCU_LASERCONT_TL__Get_NewRisingAvail(E_FCU__LASER_CONT_INDEX_T eLaser);
			void vFCU_LASERCONT_TL__Clear_NewRisingAvail(E_FCU__LASER_CONT_INDEX_T eLaser);
			Luint64 u64FCU_LASERCONT_TL__Get_TimeDelta(E_FCU__LASER_CONT_INDEX_T eLaser, Luint16 u16CurrentIndex);

			//velocity
			void vFCU_LASERCONT_VELOC__Init(void);
			void vFCU_LASERCONT_VELOC__Process(void);
			Luint32 u32FCU_LASERCONT_VELOC__Get_CurrentVeloc_mms(void);
			Luint32 u32FCU_LASERCONT_VELOC__Compute(Luint32 u32Distance, Luint64 u64TimeDelta);

			//track database
			void vFCU_LASERCONT_TRKDB__Init(void);
			void vFCU_LASERCONT_TRKDB__Process(void);
			void vFCU_LASERCONT_TRKDB__Inc_Marker(E_FCU__LASER_CONT_INDEX_T eLaser);
			void vFCU_LASERCONT_TRKDB__Compute(E_FCU__LASER_CONT_INDEX_T eLaser);
			Luint32 u32FCU_LASERCONT_TRKDB__Get_DistanceElapsed_mm(E_FCU__LASER_CONT_INDEX_T eLaser);
			Luint32 u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm(E_FCU__LASER_CONT_INDEX_T eLaser);

			//ethernet
			void vFCU_LASERCONT_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//Laser distance
		void vFCU_LASERDIST__Init(void);
		void vFCU_LASERDIST__Process(void);
		Lint32 s32FCU_LASERDIST__Get_Distance_mm(void);
		Lint32 s32FCU_LASERDIST__Get_Velocity_mms(void);
		void vFCU_LASERDIST__100MS_ISR(void);
		DLL_DECLARATION void vFCU_LASERDIST_WIN32__Set_DistanceRaw(Lint32 s32Value);

			//valid checks
			void vFCU_LASERDIST_VALID__Init(void);
			void vFCU_LASERDIST_VALID__Process(void);
			void vFCU_LASERDIST_VALID__Enable(Luint8 u8Enable);
			Luint8 vFCU_LASERDIST_VALID__Get_IsValid(void);
			Lint32 s32FCU_LASERDIST_VALID__Get_Accel_mm_ss(void);
			Lint32 s32FCU_LASERDIST_VALID__Get_Velocity_mm_s(void);
			Lint32 s32FCU_LASERDIST_VALID__Get_Distance_mm(void);



			//eth
			void vFCU_LASERDIST_ETH__Init(void);
			void vFCU_LASERDIST_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_LASERDIST_ETH__Enable_EmulationMode(Luint32 u32Key, Luint32 u32Enable);
			void vFCU_LASERDIST_ETH__Emulation_Injection(Lint32 s32Value);

			//filtering
			void vFCU_LASERDIST_FILT__Init(void);
			void vFCU_LASERDIST_FILT__Process(void);




		//lasers for OptoNCDT interface
		void vFCU_LASEROPTO__Init(void);
		void vFCU_LASEROPTO__Process(void);
		void vFCU_LASEROPTO__Set_CalValue(Luint32 u32Key, Lfloat32 f32Offset);
		Lfloat32 f32FCU_LASEROPTO__Get_Distance(E_FCU__LASER_OPTO__INDEX_T eLaser);
		DLL_DECLARATION void vFCU_LASEROPTO__Enable_Ethernet_Injection(Luint32 u32Key1, Luint32 u32Key2, Luint8 u8Enable);
		DLL_DECLARATION void vFCU_LASEROPTO__Inject_Value(Luint8 u8LaserIndex, Lfloat32 f32Value);
		Luint8 u8FCU_LASEROPTO__Get_Error(E_FCU__LASER_OPTO__INDEX_T eLaser);
		void vFCU_LASEROPTO__100MS_ISR(void);
		DLL_DECLARATION void vFCU_LASEROPTO_WIN32__Set_DistanceRaw(Luint32 u32Index, Lfloat32 f32Value);

			//eth
			void vFCU_LASEROPTO_ETH__Transmit(E_NET__PACKET_T ePacketType);

			//filtering
			void vFCU_LASEROPTO_FILT__FilterPacket(E_FCU__LASER_OPTO__INDEX_T eLaser);


		
		//brakes
		void vFCU_BRAKES__Init(void);
		void vFCU_BRAKES__Process(void);
		void vFCU_BRAKES__Begin_Init(Luint32 u32Key);
		void vFCU_BRAKES__Move_IBeam_Distance_mm(Lfloat32 f32Distance);
		void vFCU_BRAKES__100MS_ISR(void);
		void vFCU_BRAKES__10MS_ISR(void);
		Lfloat32 f32FCU_BRAKES__Get_ScrewPos(E_FCU__BRAKE_INDEX_T eBrake);
		E_FCU__SWITCH_STATE_T eFCU_BRAKES__Get_SwtichState(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch);
		Luint16 u16FCU_BRAKES__Get_ADC_Raw(E_FCU__BRAKE_INDEX_T eBrake);
		Lfloat32 f32FCU_BRAKES__Get_IBeam_mm(E_FCU__BRAKE_INDEX_T eBrake);
		Lfloat32 f32FCU_BRAKES__Get_MLP_mm(E_FCU__BRAKE_INDEX_T eBrake);


			//stepper drive
			void vFCU_BRAKES_STEP__Init(void);
			void vFCU_BRAKES_STEP__Process(void);
			void vFCU_BRAKES_STEP__Move(Lint32 s32Brake0Pos, Lint32 s32Brake1Pos);
			Lint32 s32FCU_BRAKES__Get_CurrentPos_um(E_FCU__BRAKE_INDEX_T eBrake);
			void vFCU_BRAKES_STEP__UpdateValues(Luint32 u32Brake, Luint32 u32Type, Lint32 s32Value);

			//brake switches
			void vFCU_BRAKES_SW__Init(void);
			void vFCU_BRAKES_SW__Process(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Left_SwitchExtend_ISR(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Left_SwitchRetract_ISR(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Right_SwitchExtend_ISR(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Right_SwitchRetract_ISR(void);
			E_FCU__SWITCH_STATE_T eFCU_BRAKES_SW__Get_Switch(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch);
			Luint8 u8FCU_BRAKES_SW__Get_FaultFlag(E_FCU__BRAKE_INDEX_T eBrake);
			#ifdef WIN32
				DLL_DECLARATION void vFCU_BRAKES_SW_WIN32__Inject_SwitchState(Luint8 u8Brake, Luint8 u8ExtendRetract, Luint8 u8Value);
			#endif

			//brakes MLP sensor
			void vFCU_BRAKES_MLP__Init(void);
			void vFCU_BRAKES_MLP__Process(void);
			#ifdef WIN32
				DLL_DECLARATION void vFCU_BRAKES_MLP_WIN32__ForceADC(Luint8 u8Brake, Luint16 u16Value);
			#endif
			void vFCU_BRAKES_MLP__ComputeCalibration_Zero(Luint32 u32Key, E_FCU__BRAKE_INDEX_T eBrake);
			void vFCU_BRAKES_MLP__ComputeCalibration_Span(Luint32 u32Key, E_FCU__BRAKE_INDEX_T eBrake);

			//eth
			void vFCU_BRAKES_ETH__Init(void);
			void vFCU_BRAKES_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_BRAKES_ETH__MoveMotor_RAW(Luint32 u32Index, Lint32 s32Position);
			void vFCU_BRAKES_ETH__MoveMotor_IBeam(Lfloat32 f32Value);
			void vFCU_BRAKES_ETH__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1);
			void vFCU_BRAKES_ETH__MLP_ZeroSpan(Luint32 u32Key0, Luint32 u32Brake, Luint32 u32Function);

			//calibration
			void vFCU_BRAKES_CAL__Init(void);
			void vFCU_BRAKES_CAL__Process(void);
			void vFCU_BRAKES_CAL__BeginCal(Luint32 u32Key);
			Luint8 u8FCU_BRAKES_CAL__Is_Busy(void);

			//WDT
			void vFCU_BRAKES_WDT__Init(void);
			void vFCU_BRAKES_WDT__Pet_Start(void);
			void vFCU_BRAKES_WDT__Pet_End(void);

		//accelerometer layer
		void vFCU_ACCEL__Init(void);
		void vFCU_ACCEL__Process(void);
		void vFCU_ACCEL__10MS_ISR(void);
		Luint8 u8FCU_ACCEL__Get_New_Sample_Avail(Luint8 u8Channel);
		void vFCU_ACCEL__Clear_New_Sample_Avail(Luint8 u8Channel);
		Lint16 s16FCU_ACCEL__Get_LastSample(Luint8 u8Index, Luint8 u8Axis);
		Lfloat32 f32FCU_ACCEL__Get_LastG(Luint8 u8Index, Luint8 u8Axis);
		DLL_DECLARATION Lint32 s32FCU_ACCELL__Get_CurrentAccel_mmss(Luint8 u8Channel);
		DLL_DECLARATION Lint32 s32FCU_ACCELL__Get_CurrentVeloc_mms(Luint8 u8Channel);
		DLL_DECLARATION Lint32 s32FCU_ACCELL__Get_CurrentDisplacement_mm(Luint8 u8Channel);

			//thresholding
			void vFCU_ACCEL_THRESH__Init(void);
			void vFCU_ACCEL_THRESH__Process(void);
			Luint8 u8FCU_ACCEL_THRES__Is_Threshold_Met(void);
			void vFCU_ACCEL_THRESH__Set_Threshold(Lint32 s32Accel_mm_ss, Luint32 u32Time_x10ms);
			void vFCU_ACCEL_THRESH__10MS_ISR(void);

			//eth
			void vFCU_ACCEL_ETH__Init(void);
			void vFCU_ACCEL_ETH__Transmit(E_NET__PACKET_T ePacketType);

			//valid checks
			void vFCU_ACCEL_VALID__Init(void);
			void vFCU_ACCEL_VALID__Process(void);
			Luint8 u8FCU_ACCEL_VALID__Get_IsValid(void);
			Lint32 sFCU_ACCEL_VALID__Get_Accel_mm_ss(void);
			Lint32 sFCU_ACCEL_VALID__Get_Velocity_mm_s(void);
			Lint32 sFCU_ACCEL_VALID__Get_Displacement_mm(void);
			void vFCU_ACCEL_VALID__Enable(Luint8 u8Enable);
			Luint8 u8FCU_ACCEL_VALID__Get_New_Sample_Avail(void);
			void vFCU_ACCEL_VALID__Clear_NewSample_Avail(void);


			//win32
			void vFCU_ACCEL_WIN32__Set_Raw(Luint8 u8DeviceIndex, Luint8 u8ChannelIndex, Lint32 s32Value);

		//Pusher interface
		void vFCU_PUSHER__Init(void);
		void vFCU_PUSHER__Process(void);
		void vFCU_PUSHER__InterlockA_ISR(void);
		void vFCU_PUSHER__InterlockB_ISR(void);
		Luint8 u8FCU_PUSHER__Get_InterlockA(void);
		Luint8 u8FCU_PUSHER__Get_InterlockB(void);
		void vFCU_PUSHER__10MS_ISR(void);
		Luint8 u8FCU_PUSHER__Get_Switch(Luint8 u8Switch);
		E_FCU_PUSHPIN_STATE_T eFCU_PUSHER__Get_PusherState(void);

			//eth
			void vFCU_PUSHER_ETH__Init(void);
			void vFCU_PUSHER_ETH__Transmit(E_NET__PACKET_T ePacketType);


		//ASI interface
		void vFCU_ASI__Init(void);
		void vFCU_ASI__10MS_ISR(void);
		void vFCU_ASI__Process(void);
		void vFCU_ASI__MemSet(Luint8 *pu8Buffer, Luint8 u8Value, Luint32 u32Count);
		void vFCU_ASI__Set_Throttle(Luint8 u8Index, Luint16 u16RPM);


			//mux
			void vFCU_ASI_MUX__Init(void);
			void vFCU_ASI_MUX__Process(void);
			void vFCU_ASI_MUX__SelectChannel_DE(Luint8 u8ChannelIndex, Luint8 u8DeValue);
			DLL_DECLARATION Luint8 u8FCU_ASI_MUX_WIN32__Get(void);

			//eth
			void vFCU_ASI_ETH__Init(void);
			void vFCU_ASI_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//throttle layer
		void vFCU_THROTTLE__Init(void);
		void vFCU_THROTTLE__Process(void);
		void vFCU_THROTTLE__100MS_ISR(void);
		void vFCU_THROTTLE__Enable_Run(void);
		void vFCU_THROTTLE__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, E_THROTTLE_CTRL_T eRampType);

			//eth
			void vFCU_THROTTLE_ETH__Init(void);
			void vFCU_THROTTLE_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_THROTTLE_ETH__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1);
			void vFCU_THROTTLE_ETH__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, E_THROTTLE_CTRL_T eRampType);

			//geometry
		void vFCU_GEOM__Init(void);
		void vFCU_GEOM__Process(void);

			//eth
			void vFCU_GEOM_ETH__Init(void);
			void vFCU_GEOM_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//hover engines
		E_FCU__HOVERENGINES_STATES_T eFCU_FCTL_HOVERENGINES__Get_State(void);
		void vFCU_FCTL_HOVERENGINES__ManualCommandsHandle(void);
		void vFCU_FCTL_HOVERENGINES__Process(void);
		void vFCU_FCTL_HOVERENGINES__Start(void);
		void vFCU_FCTL_HOVERENGINES__Stop(void);

		//ASI
		Luint16 u16FCU_ASI__ReadMotorRpm(Luint8 u8EngineIndex);
		Lfloat32 f32FCU_ASI__ReadMotorCurrent(Luint8 u8EngineIndex);
		Lfloat32 f32FCU_ASI__ReadControllerTemperature(Luint8 u8EngineIndex);

		//drive pod
		void vFCU_FCTL_DRIVEPOD__10MS_ISR(void);
		void vFCU_FCTL_DRIVEPOD__SetPodStopCmd(void);

		//aux propulsion
		void vFCU_FCTL_AUX_PROP__Stop(void);
		void vFCU_FCTL_AUX_PROP__Disable(void);

		//flight controller cooling
		void vFCU_FCTL_COOLING__ManualCommandsHandle();
		void vFCU_FCTL_COOLING__Disable(void);
		void vFCU_FCTL_COOLING__Enable(void);

		//hover engine cooling
		void vFCU_COOLING__Set_Valve(Luint8 ValveNumber, Lfloat32 TimeOn, Lfloat32 TimeOff);

		//lift mechanism
		void vFCU_FCTL_LIFTMECH_Dir(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir);
		void vFCU_FCTL_LIFTMECH__SetDirAll(E_FCU__LIFTMECH_DIRECTION dir);
		void vFCU_FCTL_LIFTMECH__SetSpeedAll(Luint32 u32speed);
		void vFCU_FCTL_LIFTMECH__Extend(void);
		//void vFCU_FCTL_LIFTMECH_Speed(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir);
		//void vFCU_FCTL_LIFTMECH__Get_State(void);

		//brakes
		void vFCU_FCTL_EDDYBRAKES_Speed(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator, Luint32 u32speed);
		void vFCU_FCTL_EDDYBRAKES__SetSpeedAll(Luint32 u32speed);
		void vFCU_FCTL_EDDYBRAKES__SetDirAll(E_FCU__FCTL_EDDYBRAKES_DIRECTION dir);
		void vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake();
		void vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes(void);
		void vFCU_FCTL_EDDY_BRAKES__Release(void);
		void vFCU_FCTL_EDDY_BRAKES__GainScheduleController(Luint32 u32speed);
		void vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController(void);

		//main state machine
		Luint8 u8FCU_FCTL_MAINSM__CheckIfUnlifted(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfLifted(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfHoveringStatically(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfReadyForPush(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfPushing(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfCoasting(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfBraking(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfControlledBraking(void);
		void vFCU_FCTL_MAINSM__100MS_ISR(void);
		void vFCU_FCTL_MAINSM__EnterPreRun_Phase();

		//navigation
		Luint32 u32FCU_FCTL_NAV__PodSpeed(void);
		Luint8 u8FCU_FCTL_NAV__GetPodSpeedTooHigh(void);
		Luint32 u32FCU_FCTL_NAV__GetFrontPos(void);
		Luint32 u32FCU_FCTL_NAV__GetRearPos(void);
		Luint32 u32FCU_FCTL_NAV__Get_Accel_mmss(void);

		// Laser Orientation
		Luint32 u32FCU_FCTL_LASERORIENT__Get_Z_Pos();

		//brake pid
		void vFCU_FLIGHTCTL_BRAKEPID__Init(void);

		//cooling
		void vFCU_FCTL_COOLING__Enable(void);

		#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U

			//only for testing
			extern struct _strFCU sFCU;

			DLL_DECLARATION void vLCCM655R0_TS_000(void);
			DLL_DECLARATION void vLCCM655R0_TS_001(void);
			DLL_DECLARATION void vLCCM655R0_TS_002(void);
			DLL_DECLARATION void vLCCM655R0_TS_003(void);
			DLL_DECLARATION void vLCCM655R0_TS_004(void);
			DLL_DECLARATION void vLCCM655R0_TS_005(void);
			DLL_DECLARATION void vLCCM655R0_TS_006(void);


			#endif


	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_FCU_CORE_H_

