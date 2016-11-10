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


		/*******************************************************************************
		Structures
		*******************************************************************************/
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

		//throttle layer
		void vFCU_THROTTLE__Init(void);


	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_FCU_CORE_H_

