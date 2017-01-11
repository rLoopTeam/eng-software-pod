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
		#include <LCCM655__RLOOP__FCU_CORE/PI_COMMS/fcu__pi_comms__types.h>

		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/BRAKES/fcu__brakes__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/ACCELEROMETERS/fcu__accel__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/LASER_OPTO/fcu__laser_opto__fault_flags.h>

		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi_defines.h>
		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi_types.h>

		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

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

			/** The main state machine for run mode */
			E_FCU__RUN_STATE_T eRunState;

			/** Auto sequence state machine */
			E_FCU__AUTO_SEQUENCE_STATE_T eAutoSeqState;

			/** The init statemachine */
			E_FCU__INIT_STATE_TYPES eInitStates;


			/** Fault handling subsystem */
			struct
			{
				/** top level fault tree subsystem for the flight controller */
				FAULT_TREE__PUBLIC_T sTopLevel;

				/** Accel subsystem faults */
				FAULT_TREE__PUBLIC_T sAccel;


			}sFaults;


			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

			/** Gloabl brakes system */
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
					Lint32 s32LinearVeloc;

					/** The required linear accel for the move */
					Lint32 s32LinearAccel;

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

				/** individual accel channels */
				struct
				{
					/** most recent recorded sample from the Accel in raw units */
					Lint16 s16LastSample[3];

					/** Last sample of the G-Force*/
					Lfloat32 f32LastG[3];

				}sChannels[C_LOCALDEF__LCCM418__NUM_DEVICES];

			}sAccel;
			#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL

			/** Pi Comms Layer */
			struct
			{

				//the current state
				E_FCU_PICOM__STATE_T eState;

				/** 100ms timer tick */
				Luint8 u8100MS_Timer;

			}sPiComms;

			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
			/** Pusher Interface Layer */
			struct
			{
				/** Guard variable 1*/
				Luint32 u32Guard1;

				/** The pusher subsystem state machine */
				E_FCU_PUSHER__STATES_T eState;

				/** Interlock switch status */
				Luint8 u8Pusher_Status;



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

			}sLaserOpto;
			#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT

			/** structure for the laser distance interface */
			struct
			{

				/** main state machine */
				E_FCU_LASERDIST__STATE_T eLaserState;

				/** RX byte state machine */
				E_LASERDIST__RX_STATE_T eRxState;

				/** A 100ms counter to wait until the lasers have powered up*/
				Luint32 u32LaserPOR_Counter;

				/** A new packet is available for distance processing */
				Luint8 u8NewPacket;

				/** Array to hold new bytes received */
				Luint8 u8NewByteArray[3];

				/** The most recent distance*/
				Lfloat32 f32DistanceRAW;

				/** The final filtered distance*/
				Lfloat32 f32DistanceFiltered;

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
					Lfloat32 f32Distance;

				}sEmu;

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

			}sFlightControl;


			

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
					Lint32 s32CurrentAccel_mmss;

				}sSensors[LASER_CONT__MAX];

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

				Luint32 u32Guard2;

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

				/** The next packet type to transmit */
				E_NET__PACKET_T eTxPacketType;

				/** If the user has enabled Tx streaming */
				E_NET__PACKET_T eTxStreamingType;


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
				/** the modbus state */
				E_FCU_MODBUS__STATE_T eMbState;

				/** a circular queue of modbus commands to ASI devices */
				struct _strASICmd cmdQueue[C_ASI__COMMAND_QUEUE];

				/** command queue head index*/
				Luint8 u8Queue_HeadIndex;

				/** command queue tail index*/
				Luint8 u8Queue_TailIndex;

				/** a set of timers to control tx timeouts */
				Luint32 u32ASI_turnaround_Counter;
				Luint32 u32ASI_replywait_Counter;

			}sASIComms;
			#endif

			/** Structure guard 2*/
			Luint32 u32Guard2;
			
			/** Input data for throttle layer */
			// (added by @gsweriduk on 23 NOV 2016)
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
			struct strThrottleInterfaceData
			{
				// Ground Station command
				E_GS_COMMANDS eGS_Command;

				// Flight Control Unit mode
				E_FCU_MODES eFCU_Mode;

				// throttle command units (0 for RPM*10, 1 for Percent), needs to be sent by GS
				Luint8 u8CommandUnits;

				// speeds of HE1 to HE8
				Luint16 u16HE_Speeds[8];

				// duration of ramp command *** ASSUMING throttleStartRampDuration IS IN UNITS of MILLISECONDS ***
				Luint16 u16throttleStartRampDuration;

				// maximum speed of HEs in RPM*10
				Luint16 u16HE_MAX_SPD;

				// minimum speed of HEs in RPM*10
				Luint16 u16HE_MIN_SPD;

				// HE speeds for static hover
				Luint16 u16rpmHEStaticHoveringSpeed;

				// HE speeds for standby mode
				Luint16 u16maxRunModeStandbySpeed;

				// Throttle command values:
				// use [0] to command all HEs, use [1] - [8] for commands to individual HEs
				Luint16 u16ThrottleCommands[9];

				// Number of the HE being given a command:
				// A value of 0 signifies all HEs, 1 - 8 indicates a specific HE
				Luint8 u8EngineNumber;

				// state variable
				E_THROTTLE_STATES_T eState;

				// timer state
				Luint8 u8100MS_Timer;

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
		void vFCU_FLIGHTCTL__Init(void);
		void vFCU_FLIGHTCTL__Process(void);

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
		Lfloat32 f32FCU_LASERDIST__Get_Distance(void);
		void vFCU_LASERDIST__100MS_ISR(void);

		DLL_DECLARATION void vFCU_LASERDIST_WIN32__Set_DistanceRaw(Lfloat32 f32Value);

			//eth
			void vFCU_LASERDIST_ETH__Init(void);
			void vFCU_LASERDIST_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_LASERDIST_ETH__Enable_EmulationMode(Luint32 u32Key, Luint32 u32Enable);
			void vFCU_LASERDIST_ETH__Emulation_Injection(Lfloat32 f32Value);

			//filtering
			void vFCU_LASERDIST_FILT__Init(void);
			void vFCU_LASERDIST_FILT__Process(void);

		//main state machine
		void vFCU_MAINSM__Init(void);
		void vFCU_MAINSM__Process(void);

			//auto sequence
			void vFCU_MAINSM_AUTO__Init(void);
			void vFCU_MAINSM_AUTO__Process(void);
			Luint8 u8FCU_MAINSM_AUTO__Is_Busy(void);
			Luint8 u8FCU_MAINSM_AUTO__Is_Abort(void);


		//lasers for OptoNCDT interface
		void vFCU_LASEROPTO__Init(void);
		void vFCU_LASEROPTO__Process(void);
		Lfloat32 f32FCU_LASEROPTO__Get_Distance(E_FCU__LASER_OPTO__INDEX_T eLaser);
		Luint8 u8FCU_LASEROPTO__Get_Error(E_FCU__LASER_OPTO__INDEX_T eLaser);
		void vFCU_LASEROPTO__100MS_ISR(void);
		DLL_DECLARATION void vFCU_LASEROPTO_WIN32__Set_DistanceRaw(Luint32 u32Index, Lfloat32 f32Value);

			//eth
			void vFCU_LASEROPTO_ETH__Transmit(E_NET__PACKET_T ePacketType);

			//filtering
			void vFCU_LASEROPTO_FILT__FilterPacket(E_FCU__LASER_OPTO__INDEX_T eLaser);


		//pi comms
		void vFCU_PICOMMS__Init(void);
		void vFCU_PICOMMS__Process(void);
		void vFCU_PICOMMS__100MS_ISR(void);

		//brakes
		void vFCU_BRAKES__Init(void);
		void vFCU_BRAKES__Process(void);
		void vFCU_BRAKES__Begin_Init(Luint32 u32Key);
		void vFCU_BRAKES__Move_IBeam_Distance_mm(Lfloat32 f32Distance);
		void vFCU_BRAKES__100MS_ISR(void);
		Lfloat32 f32FCU_BRAKES__Get_ScrewPos(E_FCU__BRAKE_INDEX_T eBrake);
		E_FCU__SWITCH_STATE_T eFCU_BRAKES__Get_SwtichState(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch);
		Luint16 u16FCU_BRAKES__Get_ADC_Raw(E_FCU__BRAKE_INDEX_T eBrake);
		Lfloat32 f32FCU_BRAKES__Get_IBeam_mm(E_FCU__BRAKE_INDEX_T eBrake);
		Lfloat32 f32FCU_BRAKES__Get_MLP_mm(E_FCU__BRAKE_INDEX_T eBrake);


			//stepper drive
			void vFCU_BRAKES_STEP__Init(void);
			void vFCU_BRAKES_STEP__Process(void);
			void vFCU_BRAKES_STEP__Move(Lint32 s32Brake0Pos, Lint32 s32Brake1Pos);
			Lint32 s32FCU_BRAKES__Get_CurrentPos(E_FCU__BRAKE_INDEX_T eBrake);

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
			void vFCU_BRAKES_ETH__MoveMotor_RAW(Luint32 u32Index, Luint32 u32Position);
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
		Lint16 s16FCU_ACCEL__Get_LastSample(Luint8 u8Index, Luint8 u8Axis);
		Lfloat32 f32FCU_ACCEL__Get_LastG(Luint8 u8Index, Luint8 u8Axis);
		void vFCU_ACCEL_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//Pusher interface
		void vFCU_PUSHER__Init(void);
		void vFCU_PUSHER__Process(void);
		void vFCU_PUSHER__InterlockA_ISR(void);
		void vFCU_PUSHER__InterlockB_ISR(void);
		Luint8 u8FCU_PUSHER__Get_InterlockA(void);
		Luint8 u8FCU_PUSHER__Get_InterlockB(void);
		void vFCU_PUSHER__10MS_ISR(void);
		Luint8 u8FCU_PUSHER__Get_Switch(Luint8 u8Switch);
		Luint8 u8FCU_PUSHER__Get_PusherState(void);


		//ASI interface
		void vFCU_ASI__Init(void);
		void vFCU_ASI__10MS_ISR(void);
		void vFCU_ASI__Process(void);
		Lint16 s16FCU_ASI__SendCommand(struct _strASICmd *sCmdParams);
		void vFCU_ASI__MemSet(Luint8 *pu8Buffer, Luint8 u8Value, Luint32 u32Count);
		void vFCU_ASI__SetVar(struct _strASICmd *pTail);

			//CRC
			void vFCU_ASI_CRC__AddCRC(Luint8 *pu8Data);
			Luint16 u16FCU_ASI_CRC__ComputeCRC(Luint8 *pu8Data, Luint16 u16DataLen);
			Lint16 s16FCU_ASI_CRC__CheckCRC(Luint8 *pu8Data, Luint8 u8DataLen);

			//controller layer
			Lint16 s16FCU_ASI_CTRL__Init(void);
			Lint16 s16FCU_ASI_CTRL__ReadMotorRpm(Luint8 u8ASIDevNum, Luint16 *pu16Rpm);
			Lint16 s16FCU_ASI_CTRL__ReadMotorCurrent(Luint8 u8ASIDevNum, Luint16 *pu16Current);
			Lint16 s16FCU_ASI_CTRL__ReadControllerTemperature(Luint8 u8ASIDevNum, Luint16 *pu16Temp);
			Lint16 s16FCU_ASI_CTRL__SaveSettings(Luint8 u8ASIDevNum);
			Lint16 s16FCU_ASI_CTRL__GetFaults(Luint8 u8ASIDevNum, Luint16 *pu16Faults);
			Lint16 s16FCU_ASI_CTRL__ProcessReply(struct _strASICmd *pTail);

			//mux
			void vFCU_ASI_MUX__Init(void);
			void vFCU_ASI_MUX__Process(void);
			void vFCU_ASI_MUX__SelectChannel(Luint8 u8ChannelIndex);

		//throttle layer
		void vFCU_THROTTLE__Init(void);
		void vFCU_THROTTLE__Process(void);
		Lint16 s16FCU_THROTTLE__Step_Command(void);
		Lint16 s16FCU_THROTTLE__Ramp_Command(void);
		Lint16 s16FCU_THROTTLE__Write_HEx_Throttle_Command_to_DAC(Luint16 u16ThrottleCommand, Luint8 u8EngineNumber);
		Lint16 s16FCU_THROTTLE__Write_All_HE_Throttle_Commands_to_DAC(Luint16 u16ThrottleCommand);
		Lint16 s16FCU_THROTTLE__Hold(void);
		void vFCU_THROTTLE__100MS_ISR(void);
		void vFCU_THROTTLE__GetGroundStationStructValues(void);

		// AMC7812 DAC

		void vAMC7812__Process(void);
		void vAMC7812__Init(void);


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

