/**
 * @file		STEPPER_DRIVE.H
 * @brief		Main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571). This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM231R0.FILE.002
 */


#ifndef _STEP_MOTOR_DRIVER_H_
#define _STEP_MOTOR_DRIVER_H_

	#include <localdef.h>

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical__structs.h>

		#if C_LOCALDEF__LCCM231__ENABLE_ETH_FUNCTIONS == 1U
			#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp__types.h>
			#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp__packet_types.h>
		#endif

		/*******************************************************************************
		Defines
		*******************************************************************************/
		//Absolute maximum number of motors supported here, change this and lots of things
		//in addition will need to change.
		#define C_STEPDRIVE__ABS_MAX_NUM_MOTORS										(6U)


		//the floating point type
		#ifndef C_LOCALDEF__LCCM231__USE_F64
			#error
		#endif

		#if C_LOCALDEF__LCCM231__USE_F64 == 1U
			#define C_STEPDRIVE__FLOAT	Lfloat64
		#else
			#define C_STEPDRIVE__FLOAT	Lfloat32
		#endif


		#define C_STEPDRIVE__MOTOR_DRIVER_DIRECTION_CLOCKWISE 						(0U)
		#define C_STEPDRIVE__MOTOR_DRIVER_DIRECTION_COUNTER_CLOCKWISE 				(1U)

		//percentage, pasive + active must be equal to 1
		#define C_STEPDRIVE__MOTOR_DRIVER_ACTIVE_DUTY_CYCLE 						(0.2F)
		//percentage, pasive + active must be equal to 1
		#define C_STEPDRIVE__MOTOR_DRIVER_PASIVE_DUCY_CYCLE 						(0.8F)


		//Map the axis to the motors. In this case only 3 axis are used
		#define C_STEPDRIVE__MOTOR_INDEX__X											(0U)
		#define C_STEPDRIVE__MOTOR_INDEX__Y											(1U)
		#define C_STEPDRIVE__MOTOR_INDEX__Z											(2U)
		#define C_STEPDRIVE__MOTOR_INDEX__A											(3U)
		#define C_STEPDRIVE__MOTOR_INDEX__B											(4U)
		#define C_STEPDRIVE__MOTOR_INDEX__C											(5U)

		//MICROSTEP RESOLUTION (This is just an index)
		#define C_STEPDRIVE__FULL_STEP												1
		#define C_STEPDRIVE__HALF_STEP												2
		#define C_STEPDRIVE__QUARTER_STEP											4 
		#define C_STEPDRIVE__EIGHTH_STEP											8
		#define C_STEPDRIVE__TENTH_STEP												10
		#define C_STEPDRIVE__SIXTEENTH_STEP											16

		//Error Flags
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED 0x01
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED 0x02
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED_AX_X 0x0001
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED_AX_X 0x0002
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED_AX_Y 0x0004
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED_AX_Y 0x0008
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED_AX_Z 0x0010
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED_AX_Z 0x0020
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED_AX_4 0x0040
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED_AX_4 0x0080
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED_AX_5 0x0100
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED_AX_5 0x0200
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_VEL_EXCEEDED_AX_6 0x0400
		#define	C_STEPDRIVE__MOVEMENT_FLAGS_ACC_EXCEEDED_AX_6 0x0800

		/** Internal states of the Step machine */
		typedef enum
		{
			/** We are not stepping */
			STEP_STATE__IDLE = 0U,

			/** We are armed, waiting for the first interrupt from the timer */
			STEP_STATE__ARMED,

			STEP_STATE__ON,
			STEP_STATE__WAIT_ON,
			STEP_STATE__OFF,
			STEP_STATE__WAIT_OFF
		}STEP_DRIVE__STEP_STATES_T;

		//Internal states of the Motor machine
		typedef enum
		{
			MOTOR_STATE__IDLE,
			
			/** We are transitioning from IDLE to ACCEL ARMED and
			 * will wait for the ISR to give us the first pulse.
			 */
			MOTOR_STATE__ACCEL_ARMED,

			/** The main SM is waiting for the ISR to do its pulse */
			MOTOR_STATE__ACCEL_ARMED_WAIT,

			MOTOR_STATE__ACCEL_ON,

			MOTOR_STATE__CONST_ARMED,
			MOTOR_STATE__CONST_ARMED_WAIT,
			MOTOR_STATE__CONST_ON,


			MOTOR_STATE__DECEL_ARMED,
			MOTOR_STATE__DECEL_ARMED_WAIT,
			MOTOR_STATE__DECEL_ON

		}STEP_DRIVE__MOTOR_STATE_T;

		#ifdef WIN32	
			typedef void (__cdecl * pSTEPDRIVE_WIN32__UpdatePosCallback_FuncType)(Luint8 u8MotorIndex, Luint8 u8Step, Luint8 u8Dir, Lint32 s32Position_um);
		#endif
		
		/*******************************************************************************
		Structures
		*******************************************************************************/
		typedef struct
		{
			//our two important positions
			struct
			{
				struct
				{
					/** the position relative to home */
					Lint32 s32Home_PicoMeters;

					/** The starting point before the move begins */
					Lint32 s32StartWorkPoint_pm;

					/** Holds the current position (working position) in um*10 */
					Lint32 s32WorkPoint_pm;

				}sAxis[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];

			}sWorkingPoints;
		

			/** Axis limit control switches */
			struct
			{
				struct
				{
					//stopped on MinX
					Luint8 u8Min;
					Luint8 u8Max;

					/** an interrupt has occurred, we don't know the source yet, but all motors
					 * must be aware of it. */
					Luint8 u8InterruptFlag;

				}sAxis[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];

				/** Global all motors stop limit */
				Luint8 u8InterruptFlag;

			}sLimits;

			struct _strTIME_BASE
			{

				//used when calculating the value for registers
				//stored to read them if required during run time
				Lfloat32 f32RequestedFreqHZ;

				Lfloat32 f32Temp;

				Luint32 u32Counts;

				//Number of ticks 
				Luint32 u32Ticks;

			}sTIME_BASE;

			
			/** Current Requested move
			 *  This structure is set when the upper layer requests a move.
			 *  There are two move requests, in a double buffer format so as the next
			 *  request can be queued up and the state machine can just flow onto the next move.
			 */
			struct
			{
				
				struct
				{
					/** the target linear position absolute */
					Lint32 s32TargetAbsolutePosition_um;

					/** holds the displacement vector
					 * Displacement is from current position to new position*/
					Lint32 s32TargetDisplacementVector_um;

					/** Computed dispacement vector in pm*/
					Lint32 s32TargetDisplacementVector_pm;

					/** holds the velocity relative to each component or axis
					 * POSITIVE ONLY */
					Lint32 s32TargetVeloc_um_s;

					/** holds the acceleration relative to each component or axis
					 * POSITIVE ONLY */
					Lint32 s32TargetAccel_um_s2;

					/** Can the Axis move in this move request */
					Luint8 u8AxisCanMove;

					/** The computed sign of the movement */
					Lint32 s32SignOfMovement;

				}sAxis[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];

				/** A task ID assigned to this move, allowing us to report the end of a task */
				Luint32 u32TaskID;

			}sMoveRequest;
			
			//the movement planner, just before rotating motors
			struct
			{

				struct
				{

					/** Are we to stop an axis? */
					Luint8 u8Stop;

					/** CW or CCW */
					Lint32 s32SignOfMovement;

					Lint32 s32PrevSignOfMovement;

					/** Microns per step
					 * Needs to be pm not um because on a 5mm lead screw we have 2.5um/pulse.
					 */
					Lint32 s32Picometers_Per_Step;

					/** Number of pulses for the entire movement */
					Luint32 u32NumPulses_Entire_Movement;
				
					/** the angular veloc required. */
					Lint32 s32AngularVelocity_rev_s;

					Lint32 s32AngularAccel_rev_s2;

					Luint32 u32MicroStepsPerRevolution;

					/** Stats on the movement */
					struct
					{

						/** Has the velocity been limited by the movement request */
						Luint8 u8LinearVelocLimit;

						/** Has the linear accel been limited by the movement request */
						Luint8 u8LinearAccelLimit;

						/** Has the RPM been limited by the motor settings */
						Luint8 u8AngularVelocLimit;

						/** Has the angular accel been limited by the move */
						Luint8 u8AngularAccelLimit;


					}sStats;


				}sAxis[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];

				/** The task ID associated with this movement plan */
				Luint32 u32TaskID;
				
			}sMovePlan;
			
			
			//Variables that link rotation with axis
			struct 
			{
				//This value hold the number of microsteps per step
				Luint8 u8MicrostepResolution;
				
			}sAxis[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];

			//Acceleration profile struct
			struct _strACCELERATION_PROFILE
			{

				struct
				{

					//Stores the number of steps already rotated
					Luint32 u32Current_PulsesAccel;
					Luint32 u32Current_PulsesConstant;
					Luint32 u32Current_PulsesDecel;

					//store the values for the current movement
					Lint32 s32AngularVelocity_rev_s;
					Lint32 s32AngularAcceleration_rev_s2;
					Luint32 u32MicroStepsPerRevolution;
			
					//Stores the number of steps that must be rotated in the current instruction
					//Total number of pulses to rotate
					Luint32 u32Total_PulsesToRotate;
		

					//State in which the motor is. This variable determines the state of the state machine.
					STEP_DRIVE__MOTOR_STATE_T eMotorCurrentState;

					struct
					{

						/** A step has several states. This variable represents the current state in which the step is */
						//STEP_DRIVE__STEP_STATES_T eCurrentState;

						/** Sotres the number of ticks for the current step */
						Luint32 u32Ticks;

						/** Once step state is changed to on, the pre computed ticks on and ticks off are transferred
						 * into the working variables for use in the state machine. this means the upper layer can process
						 * new ticks for us.
						 */
						struct
						{
							/** Variable to store the number of ticks and use it as reference for the intervals (moving the pins on and off) */
							Luint32 u32TickInterval;

							/** Sotres the number of ticks for the current step */
							Luint32 u32Ticks;


						}sWorking;

						struct
						{
							/** The interrupt is armed for the next interrupt to pulse us */
							Luint8 u8AccelArmed;
							Luint8 u8ConstArmed;
							Luint8 u8DecelArmed;

						}sISR;

						/** Signal to the interrupt controller that we need a falling edge */
						Luint8 u8NeedFallingEdge;

					}sStepState;

					//we can pre-plan 3 types of plans
					//if we get a new buffer input then we can switch plans.
					//1 = Accel, Constant, Decl
					//2 = Accel, Constant
					//3 = Constant, Decel
					//4 = Constant

					struct
					{

						Luint32 u32Total_PulsesAccel;
						Luint32 u32Total_PulsesConstant;
						Luint32 u32Total_PulsesDecel;

					}sPlan;


					//the current profile plan that we are using.
					//Luint8 u8CurrentPlan;

				}sAxis[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];

				Luint32 u32TaskID;

			}sAccelProfile; //[2];
		
					
			//The parameters loaded from the EEPROM layer
			struct
			{
							
				//Maximum Angular Acceleration
				Lint32 s32Max_AngularAccel_rev_s2;
				
				/** The number of picometers per step of the motor.
				 * We need pm as opposed to um because with a 5mm lead screw we can have 2.5um/step and this causes
				 * us to need floating point.
				 *
				 * 2^31pm = 2,147mm = 2.1 meters.
				 *  */
				Lint32 s32PicoMeters_PerRevolution;
				
				/** Steps per revolution (usually 200) */
				Luint32 u32Steps_Rev;
				
				/** The maximum angular velocity, should be about 400 */
				Lint32 s32Max_AngularVeloc_rev_min;
				

			}sParams[C_LOCALDEF__LCCM231__NUMBER_OF_MOTORS];
			
			/** Struct to hold move complete details */
			struct
			{
				Luint32 u32TaskID;
				Luint8 u8Complete;
			}sMoveComplete;

			
			#ifdef WIN32
			struct
			{
				pSTEPDRIVE_WIN32__UpdatePosCallback_FuncType pCallback;
			}sWIN32;
			#endif
			
		}TS_STEPDRIVE_MAIN;

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vSIL3_STEPDRIVE__Init(void);
		void vSIL3_STEPDRIVE__Process(void);
		Lint16 s16SIL3_STEPDRIVE_POSITION__Set_Position(Lint32 * ps32XYZABC_microns, Lint32 * ps32Velocity_microns_sec, Lint32 * ps32Accel_microns_ss, Luint32 u32TaskID);
		Lint32 s32SIL3_STEPDRIVE_POSITION__Get_PositionPicometers(Luint8 u8AxisIndex);
		Luint8 u8SIL3_STEPDRIVE__Get_TaskComplete(void);
		void vSIL3_STEPDRIVE__Set_TaskComplete(void);
		void vSIL3_STEPDRIVE__Clear_TaskComplete(void);
		Luint32 u32SIL3_STEPDRIVE__Get_TaskID(void);

		void vSIL3_STEPDRIVE_POSITION__Stop_Minimum(Luint8 u8Axis);
		void vSIL3_STEPDRIVE_POSITION__Release_Minimum(Luint8 u8Axis);


		//time_base.c
		void vSIL3_STEPDRIVE_TIMEBASE__Init(void);
		void vSIL3_STEPDRIVE_TIMEBASE__Process(void);
		void vSIL3_STEPDRIVE_TIMEBASE__Clear_Ticks(void);
		#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U) || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U ||C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
			DLL_DECLARATION void vSIL3_STEPDRIVE_TIMEBASE__ISR(void);
		#endif
		
		//limits
		void vSIL3_STEPDRIVE_LIMIT__Init(void);
		void vSIL3_STEPDRIVE_LIMIT__Limit_ISR(Luint8 u8MotorIndex);
		void vSIL3_STEPDRIVE_LIMIT__GlobalLimit(void);

		//memory
		void vSIL3_STEPDRIVE_MEM__Init(void);
		Lint32 s32SIL3_STEPDRIVE_MEM__Get_PicoMeters_PerRev(Luint8 u8MotorIndex);
		Lint32 s32SIL3_STEPDRIVE_MEM__Get_MicronsPerRev(Luint8 u8MotorIndex);
		Luint32 u32SIL3_STEPDRIVE_MEM__Get_StepsPerRevolution(Luint8 u8MotorIndex);
		Luint8 u8SIL3_STEPDRIVE_MEM__Get_MicroStepResolution(Luint8 u8MotorIndex);
		Lint32 s32SIL3_STEPDRIVE_MEM__Get_MaxAngularAcceleration(Luint8 u8MotorIndex);
		Lint32 s32SIL3_STEPDRIVE_MEM__Get_MaxAngularVelocity(Luint8 u8MotorIndex);

		void vSIL3_STEPDRIVE_MEM__Set_MicroStepResolution(Luint8 u8MotorIndex, Luint8 u8Value);
		void vSIL3_STEPDRIVE_MEM__Set_MaxAngularAccel(Luint8 u8MotorIndex, Lint32 s32Value);
		void vSIL3_STEPDRIVE_MEM__Set_MicronsPerRev(Luint8 u8MotorIndex, Lint32 s32Value);
		void vSIL3_STEPDRIVE_MEM__Set_MaxRPM(Luint8 u8MotorIndex, Lint32 s32Value);

		//home position
		void vSIL3_STEPDRIVE_HOME__Init(void);

		//buffer
		void vSIL3_STEPDRIVE_BUFFER__Init(void);
		void vSIL3_STEPDRIVE_BUFFER__Swap(void);

		Luint8 u8SIL3_STEPDRIVE_BUFFER__Alternate__Get_IsFree(void);
		Luint8 u8SIL3_STEPDRIVE_BUFFER__Alternate__Get_Index(void);
		Luint8 u8SIL3_STEPDRIVE_BUFFER__Alternate__Get_IsValid(void);
		void vSIL3_STEPDRIVE_BUFFER__Alternate__Set_IsValid(void);
		void vSIL3_STEPDRIVE_BUFFER__Alternate__Clear_IsValid(void);
		Luint8 u8SIL3_STEPDRIVE_BUFFER__Alternate__Get_IsReady(void);
		void vSIL3_STEPDRIVE_BUFFER__Alternate__Set_IsReady(void);

		Luint8 u8SIL3_STEPDRIVE_BUFFER__Current__Get_Index(void);
		Luint8 u8SIL3_STEPDRIVE_BUFFER__Current__Get_InProgress(void);
		void vSIL3_STEPDRIVE_BUFFER__Current__Clear_InProgress(void);
		void vSIL3_STEPDRIVE_BUFFER__Current__Set_InProgress(void);

		//axis_system.c
		void vSIL3_STEPDRIVE_AXIS__Init(void);
		void vSIL3_STEPDRIVE_AXIS__Set_AxisToMove(Luint8 u8AxisIndex);
		Luint8 u8SIL3_STEPDRIVE_AXIS__Get_AxisDirection(Luint8 u8AxisIndex);
		Luint8 u8SIL3_STEPDRIVE_AXIS__Get_LimitFlags(Luint8 u8AxisIndex);
		void vSIL3_STEPDRIVE_AXIS__Process(void);

		//acceleration_profile.c
		void vSIL3_STEPDRIVE_ACCEL__Init(void);
		void vSIL3_STEPDRIVE_ACCEL__Process(void);
		Lint16 s16SIL3_STEPDRIVE_ACCEL__StartRotation(Luint8 u8MotorIndex, Luint32 u32TaskID);
		Luint8 u8SIL3_STEPDRIVE_ACCEL__Get_Busy(Luint8 u8AxisIndex);
		Luint8 u8SIL3_STEPDRIVE_ACCEL__Get_CurrentState(Luint8 u8AxisIndex);
		Luint32 u32SIL3_STEPDRIVE_ACCEL__Get_NumPulsesToRotate(Luint8 u8AxisIndex);
		void vSIL3_STEPDRIVE_ACCEL__Update_Ticks__Accel(Luint8 u8AxisIndex);
		void vSIL3_STEPDRIVE_ACCEL__Update_Ticks__Decel(Luint8 u8AxisIndex);

		//local functions
		Lint32 u32SIL3_STEPDRIVE_ACCEL__Get_NumPulsesForSpeedUpdate(Luint8 u8MotorIndex);
		Luint8 u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle(void);
		void vSIL3_STEPDRIVE_ACCELL_Inc_Position(Luint8 u8AxisIndex);


		//single_step_sm.c
		void vSIL3_STEPDRIVE_SINGLESTEP__Init(void);	
		void vSIL3_STEPDRIVE_SINGLESTEP__Process(Luint8 u8MotorIndex);
		void vSIL3_STEPDRIVE_SINGLESTEP__ChangeState(Luint8 u8AxisIndex, STEP_DRIVE__STEP_STATES_T eState);
		STEP_DRIVE__STEP_STATES_T eSTEPDRIVE_SINGLESTEP__Get_State(Luint8 u8AxisIndex);
		void vSIL3_STEPDRIVE_SINGLESTEP__ReArm_NextStep(Luint8 u8AxisIndex);
		
		//eth interface
		#if C_LOCALDEF__LCCM231__ENABLE_ETH_FUNCTIONS == 1U
			void vSIL3_STEPDRIVE_ETH__Init(void);
			void vSIL3_STEPDRIVE_ETH__Process(void);
			void vSIL3_STEPDRIVE_ETH__RxUDPSafe(Luint8 *pu8Payload, Luint16 u16PayloadLength, SAFE_UDP__PACKET_T ePayloadType, Luint16 u16DestPort, SAFE_UDP__FAULTS_T ePayloadFault);
			void vSIL3_STEPDRIVE_ETH__Transmit(SAFE_UDP__PACKET_T ePacketType, Luint32 u32UserValue, Lint32 s32UserValue);
		#endif

		//low_level.c
		#if C_LOCALDEF__LCCM231__STEP_VIA_A4988 == 1U
			void vSIL3_STEPDRIVE_A4988__Init(void);
			Lint16 s16SIL3_STEPDRIVE_A4988__Set_PulseLow(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__Set_PulseHigh(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__Set_RotationClockwise(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__Set_RotationCounterClockwise(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__SleepDriver(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__WakeDriver(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__ResetDriver(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__DisableOutputs(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__EnableOutputs(Luint8 u8MotorIndex);
			Lint16 s16SIL3_STEPDRIVE_A4988__Set_MicroStepResolution(Luint8 u8MotorIndex, Luint8 u8MicrostepResolution);
		#elif C_LOCALDEF__LCCM231__STEP_VIA_GEKO == 1U
			void vSIL3_STEPDRIVE_GEKO__Init(void);
			void vSIL3_STEPDRIVE_GEKO__Set_PulseHigh(Luint8 u8MotorIndex);
			void vSIL3_STEPDRIVE_GEKO__Set_PulseLow(Luint8 u8MotorIndex);
			void vSIL3_STEPDRIVE_GEKO__Set_RotationClockwise(Luint8 u8MotorIndex);
			void vSIL3_STEPDRIVE_GEKO__Set_RotationCounterClockwise(Luint8 u8MotorIndex);
		#elif C_LOCALDEF__LCCM231__STEP_VIA_DRV8711 == 1U
			void vSIL3_STEPDRIVE_DRV8711__Init(void);
			void vSIL3_STEPDRIVE_DRV8711__Set_PulseHigh(Luint8 u8MotorIndex);
			void vSIL3_STEPDRIVE_DRV8711__Set_PulseLow(Luint8 u8MotorIndex);
			void vSIL3_STEPDRIVE_DRV8711__Set_RotationClockwise(Luint8 u8MotorIndex);
			void vSIL3_STEPDRIVE_DRV8711__Set_RotationCounterClockwise(Luint8 u8MotorIndex);
		#elif C_LOCALDEF__LCCM231__STEP_VIA_WIN32 == 1U
			//do nothing.
		#else
			#error
		#endif


		//zero
		void vSIL3_STEPDRIVE_ZERO__Set_Zero(Luint8 u8Axis);
		void vSIL3_STEPDRIVE_ZERO__Set_Zero_Defined(Luint8 u8AxisIndex, Lint32 s32Value);
		void vSIL3_STEPDRIVE_ZERO__ZeroAll(void);

		//usb
		#if C_LOCALDEF__LCCM231__ENABLE_USB == 1U
			void vSIL3_STEPDRIVE_USB__Init(void);
			void vSIL3_STEPDRIVE_USB__Process(void);
		#endif
		#if C_LOCALDEF__LCCM231__ENABLE_USB_FUNCTIONS == 1U
			void vSIL3_STEPDRIVE_USB__User_Process(sLockieStandardUSBEndpoints * pEP);
			void vSIL3_STEPDRIVE_USB__User_ProcessControlPacket(Luint16 u16PacketType, Luint32 * pu32Blocks, sLockieStandardUSBEndpoints * pEP);
			void vSIL3_STEPDRIVE_USB__Send_Paramters(Luint32 u32MotorIndex, sLockieStandardUSBEndpoints * pEP);
		#endif //C_LOCALDEF__LCCM231__ENABLE_USB_FUNCTIONS

		#if C_LOCALDEF__LCCM231__ENABLE_TEST_SPEC == 1U
			void vLCCM231_TS_001(void);

		#endif
		
		#ifdef WIN32
			#ifndef DLL_DECLARATION
				#error
			#endif
			DLL_DECLARATION void vSIL3_STEPDRIVE_WIN32__Set_UpdatePositionCallback(pSTEPDRIVE_WIN32__UpdatePosCallback_FuncType pFunc);
			void vSIL3_STEPDRIVE_WIN32__UpdatePostion(Luint8 u8MotorIndex, Luint8 u8Step, Luint8 u8Dir, Lint32 s32Position);
			DLL_DECLARATION void vSIL3_STEPDRIVE_WIN32__ForcePosition(Luint8 u8MotorIndex, Lint32 s32Position);
		#endif

		//safetys
		#ifndef C_LOCALDEF__LCCM231__ENABLE_USB
			#error
		#endif
		#ifndef C_LOCALDEF__LCCM231__ENABLE_USB_FUNCTIONS
			#error
		#endif

#endif //step_motor_driver.h
