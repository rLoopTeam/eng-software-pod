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

		//state machine types
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__types.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__defines.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__enums.h>
		#include <LCCM655__RLOOP__FCU_CORE/PI_COMMS/fcu__pi_comms__types.h>

		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/BRAKES/fcu__brakes__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/ACCELEROMETERS/fcu__accel__fault_flags.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define C_MLP__MAX_AVERAGE_SIZE				(8U)
		// number of ASI commands waiting in queue
		#define C_ASI__COMMAND_QUEUE				(8)
 	 	// modbus frame size for read/write register commands
		#define C_ASI__RW_FRAME_SIZE				(8)
		// max modbus frame size
		#define C_ASI__MAX_FRAME_SIZE				(256)
		// modbus function codes
		#define C_ASI__READ_INPUT_REGISTER			(0x04)
		#define C_ASI__WRITE_SINGLE_REGISTER		(0x06)

		/** Brakes states */
		typedef enum
		{

			/** We are in idle state */
			BRAKE_STATE__IDLE = 0U,

			/** Beginning to move the brakes */
			BRAKE_STATE__BEGIN_MOVE,

			/** The brakes are moving */
			BRAKE_STATE__MOVING,

			/** The brakes were moving, and now they have stopped, cleanup any necessary stuff */
			BRAKE_STATE__MOVE_STOPPED,

			/** A fault has occurred with the brake system */
			BRAKE_STATE__FAULT,

			BRAKE_STATE__TEST

		}E_FCU_BRAKES__STATES_T;

		/** ASI communication (modbus client) states */
		typedef enum
		{
			/** Initial state */
			ASI_COMM_STATE__INITIAL = 0u,

			/** Idle state */
			ASI_COMM_STATE__IDLE = 1u,

			/** Transmit to all slaves */
			ASI_COMM_STATE__BROADCAST_EMISSION = 2u,

			/** Transmit to a specific slave */
			ASI_COMM_STATE__UNICAST_EMISSION = 3u,

			/** Receive state */
			ASI_COMM_STATE__RECEPTION = 4u,

			/** Process reply or error */
			ASI_COMM_STATE__CONTROL_AND_WAIT = 5u

		} E_FCU_MODBUS__STATE_T;

		/** variable type to set requested variable to ASI response */
		typedef enum
		{
			E_INT8 = 0X11,
			E_UINT8 = 0X12,
			E_INT16 = 0X21,
			E_UINT16 = 0X22,
			E_INT32 = 0X41,
			E_UINT32 = 0X42,
			E_INT64 = 0X81,
			E_UINT64 = 0X82
		} E_VAR_TYPE;


		/*******************************************************************************
		Structures
		*******************************************************************************/

		/** ASI controller modbus read/write register command structure */
		struct _strASICmd {
			Luint8 slaveAddress;
			Luint8 fncCode;			// C_ASI__READ_INPUT_REGISTER or C_ASI__WRITE_SINGLE_REGISTER
			Luint16 paramAddress;
			Luint16 paramValue;		// for reading, this is num of registers to read, set to 1
			Luint8 framedCmd[C_ASI__RW_FRAME_SIZE];
			Luint8 response[C_ASI__RW_FRAME_SIZE];	// assuming we always read only one register
			void* destVar;
			E_VAR_TYPE eDestVarType;
		};

		/** ASI controller modbus read register response structure */
		struct _strASIReply {
			Luint8 fncCode;
			Luint8 byteCount;
			Luint8 inRegHi;
			Luint8 inRegLo;
		};

		/** main flight control structure */
		struct _strFCU
		{
			/** Structure guard 1*/
			Luint32 u32Guard1;


			/** The init statemachine */
			E_FCU__INIT_STATE_TYPES eInitStates;

			/** The brakes state machine */
			E_FCU_BRAKES__STATES_T eBrakeStates;

			/** Fault handling subsystem */
			struct
			{
				/** top level fault tree subsystem for the flight controller */
				FAULT_TREE__PUBLIC_T sTopLevel;

				/** Accel subsystem faults */
				FAULT_TREE__PUBLIC_T sAccel;


			}sFaults;


			/** Brake Substructure */
			struct
			{

				/** Linear position sensor detail */
				struct
				{
					/** This is the sample from the ADC converter */
					Luint16 u16ADC_Sample;

					/** The zero value when the brakes are fully retracted */
					Luint16 u16ADC_Zero;

					/** Current ADC span to convert ADC units into engineering units */
					Lfloat32 f32SystemSpan;

					/** ADC value - Zero Value */
					Lint32 s32ADC_Minus_Zero;

					/** Percent of braking from 0.0 to 100.0*/
					Lfloat32 f32BrakePosition_Percent;

					/** Average Counter	for MLP filter function				 */
					Luint16 u16AverageCounter;

					/** Average Array for MLP filter function				 */
					Luint16 u16AverageArray[C_MLP__MAX_AVERAGE_SIZE];

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


				/** individual brake fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

			}sBrakes[C_FCU__NUM_BRAKES];


			/** Accel subsystem */
			struct
			{

				/** individual accel channels */
				struct
				{
					/** most recent recorded sample from the Accel */
					Lint16 s16LastSample;

				}sChannels[C_LOCALDEF__LCCM418__NUM_DEVICES];

			}sAccel;

			/** Pi Comms Layer */
			struct
			{

				//the current state
				E_FCU_PICOM__STATE_T eState;

			}sPiComms;

			/** ASI Comms Layer */
			struct
			{
				/** the modbus state */
				E_FCU_MODBUS__STATE_T eMbState;
				/** a circular queue of modbus commands to ASI devices */
				struct _strASICmd cmdQueue[C_ASI__COMMAND_QUEUE];
				/** command queue head index*/
				Lint8 qHead;
				/** command queue tail index*/
				Lint8 qTail;
				/** a set of timers to control tx timeouts */
				Luint64 timeout_3_5_char;
				Luint64 timeout_1_5_char;
				Luint64 timeout_response;
				Luint64 timeout_turnaround;
				Luint64 timer_3_5_char_start;
				Luint64 timer_1_5_char_start;
				Luint64 timer_response_start;
				Luint64 timer_turnaround_start;

			}sASIComms;

			/** Structure guard 2*/
			Luint32 u32Guard2;
			
		};




		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		//core
		DLL_DECLARATION void vFCU__Init(void);
		DLL_DECLARATION void vFCU__Process(void);
		void vFCU__RTI_100MS_ISR(void);
		void vFCU__RTI_10MS_ISR(void);

		//fault handling layer
		void vFCU_FAULTS__Init(void);
		void vFCU_FAULTS__Process(void);
		Luint8 u8FCU_FAULTS__Get_IsFault(void);
		Luint32 u32FCU_FAULTS__Get_FaultFlags(void);

		//pi comms
		void vFCU_PICOMMS__Init(void);
		void vFCU_PICOMMS__Process(void);

		//brakes
		void vFCU_BRAKES__Init(void);
		void vFCU_BRAKES__Process(void);
		void vFCU_BRAKES__Move_IBeam_Distance_Microns(Luint32 u32Distance);
		
			//stepper drive
			void vFCU_BRAKES_STEP__Init(void);
			void vFCU_BRAKES_STEP__Process(void);
			void vFCU_BRAKES_STEP__Move(Lint32 s32Brake0Pos, Lint32 s32Brake1Pos);
			Lint32 s32FCU_BRAKES__Get_CurrentPos(E_FCU__BRAKE_INDEX_T eBrake);

			//brake switches
			void vFCU_BRAKES_SW__Init(void);
			void vFCU_BRAKES_SW__B0_SwitchExtend_ISR(void);
			void vFCU_BRAKES_SW__B0_SwitchRetract_ISR(void);
			void vFCU_BRAKES_SW__B1_SwitchExtend_ISR(void);
			void vFCU_BRAKES_SW__B1_SwitchRetract_ISR(void);
			Luint8 u8FCU_BRAKES_SW__Get_B0_Extend(void);
			Luint8 u8FCU_BRAKES_SW__Get_B0_Retract(void);
			Luint8 u8FCU_BRAKES_SW__Get_B1_Extend(void);
			Luint8 u8FCU_BRAKES_SW__Get_B1_Retract(void);

			//brakes MLP sensor
			void vFCU_BRAKES_MLP__Init(void);
			void vFCU_BRAKES_MLP__Process(void);

		//accelerometer layer
		void vFCU_ACCEL__Init(void);
		void vFCU_ACCEL__Process(void);

		//ASI interface
		void vFCU_ASI__Init(void);
		void vFCU_ASI__Process(void);
		Lint16 vFCU_ASI__Controller_Init(void);
		Lint16 vFCU_ASI__ReadMotorRpm(Luint8 u8ASIDevNum, Luint16* u16Rpm);
		Lint16 vFCU_ASI__ReadControllerTemperature(Luint8 u8ASIDevNum, Luint16* u16Temp);
		Lint16 vFCU_ASI__SaveSettings(Luint8 u8ASIDevNum);
		Luint16 vFCU_ASI__GetFaults(Luint8 u8ASIDevNum, Luint16* u16Faults);
		// lower level
		Lint8 vFCU_ASI__SendCommand(struct _strASICmd *sCmdParams);
		void vFCU_ASI__BuildCmdFrame(struct _strASICmd *sCmdParams);
		Luint16 vFCU_ASI__ComputeCRC(Luint8* data, Luint16 dataLen);
		void vFCU_ASI__AddCRC(Luint8* data);
		Lint8 vFCU_ASI__ProcessReply(void);
		Lint8 vFCU_ASI__CheckCRC(Luint8* rData, Luint8 dataLen);
		void vFCU_ASI__SetVar(struct _strASICmd *pTail);
		void vFCU_ASI__ProcessError(struct _strASICmd *pTail);
		void vFCU_ASI__RTU_Tx_Byte(Luint8* pByte);
		void vFCU_ASI__RTU_Rx_Byte(Luint8* pByte);
		Luint8 vFCU_ASI__RTU_RxIsReady(void);

		//throttle layer
		void vFCU_THROTTLE__Init(void);


	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_FCU_CORE_H_

