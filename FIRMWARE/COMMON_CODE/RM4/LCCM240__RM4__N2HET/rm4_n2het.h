/**
 * @file		rm4_n2het.h
 * @brief		N2HET1 header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @st_fileID	LCCM240R0.FILE.002
 */
 
#ifndef _RM4_HET_H_
#define _RM4_HET_H_

	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U

		#include <RM4/LCCM240__RM4__N2HET/rm4_n2het__private.h>
		#include <RM4/LCCM219__RM4__SYSTEM/rm4_system.h>

		/** N2HET Pin Defs */
		typedef enum
		{
			PIN_HET_0 = 0U,
			PIN_HET_1 = 1U,
			PIN_HET_2 = 2U,
			PIN_HET_3 = 3U,
			PIN_HET_4 = 4U,
			PIN_HET_5 = 5U,
			PIN_HET_6 = 6U,
			PIN_HET_7 = 7U,
			PIN_HET_8 = 8U,
			PIN_HET_9 = 9U,
			PIN_HET_10 = 10U,
			PIN_HET_11 = 11U,
			PIN_HET_12 = 12U,
			PIN_HET_13 = 13U,
			PIN_HET_14 = 14U,
			PIN_HET_15 = 15U,
			PIN_HET_16 = 16U,
			PIN_HET_17 = 17U,
			PIN_HET_18 = 18U,
			PIN_HET_19 = 19U,
			PIN_HET_20 = 20U,
			PIN_HET_21 = 21U,
			PIN_HET_22 = 22U,
			PIN_HET_23 = 23U,
			PIN_HET_24 = 24U,
			PIN_HET_25 = 25U,
			PIN_HET_26 = 26U,
			PIN_HET_27 = 27U,
			PIN_HET_28 = 28U,
			PIN_HET_29 = 29U,
			PIN_HET_30 = 30U,
			PIN_HET_31 = 31U
		}RM4_HET__PIN_SELECT__T;


		/** N2HET Channels */
		typedef enum
		{
			N2HET_CHANNEL__1 = 0U,
			#if C_LOCALDEF__LCCM240__ENABLE_N2HET2 == 1U
				N2HET_CHANNEL__2,
			#endif

			N2HET_CHANNEL__NUM_CHANNELS

		}RM4_N2HET__CHANNEL_T;


		/** N2HET Prescaler values for Loop Resolution */
		typedef enum
		{
			LR_PRESCALE__1 = 0U,
			LR_PRESCALE__2 = 1U,
			LR_PRESCALE__4 = 2U,
			LR_PRESCALE__8 = 3U,
			LR_PRESCALE__16 = 4U,
			LR_PRESCALE__32 = 5U,
			LR_PRESCALE__64 = 6U,
			LR_PRESCALE__128 = 7U

		}RM4_N2HET__LR_PRESCALE_T;

		/** High Resolution Prescaler Values */
		typedef enum
		{
			HR_PRESCALE__1 = 0U,
			HR_PRESCALE__2 = 1U,
			HR_PRESCALE__4 = 2U,
			HR_PRESCALE__8 = 3U,
			HR_PRESCALE__16 = 4U,
			HR_PRESCALE__32 = 5U,
			HR_PRESCALE__64 = 6U

		}RM4_N2HET__HR_PRESCALE_T;
		
		/** This type is used to access a HET Instruction.*/
		typedef volatile struct hetInstructionBase
		{
			Luint32 u32Program;
			Luint32 u32Control;
			Luint32 u32Data;
			Luint32 u32Reserved;

		} RM4_HET__INSTRUCTION_T;


		/** @struct hetRamBase
		* @brief HET RAM Definition
		*
		* This structure is used to access the HET RAM.
		*/
		/** @typedef RM4_HET__RAMBASE_T
		* @brief HET RAM Type Definition
		*
		* This type is used to access the HET RAM.
		*/
		#define C_RM4_N2HET__MAX_HET_INSTRUCTIONS		160U

		typedef volatile struct het1RamBase
		{
			RM4_HET__INSTRUCTION_T Instruction[C_RM4_N2HET__MAX_HET_INSTRUCTIONS];
		} RM4_HET__RAMBASE_T;


		/** @struct hetSignal
		* @brief HET Signal Definition
		*
		* This structure is used to define a u32PWM signal.
		*/
		/** @typedef RM4_HET__SIGNAL_T
		* @brief HET Signal Type Definition
		*
		* This type is used to access HET Signal Information.
		*/
		typedef struct hetSignal
		{

			 /** Duty cycle in % of the period */
			Luint32 u32DutyCycle;

			/**Period in us */
			Lfloat32 f32PeriodUS;

		} RM4_HET__SIGNAL_T;


		/* Configuration registers */
		typedef struct het_config_reg
		{
			Luint32 CONFIG_GCR;
			Luint32 CONFIG_PFR;
			Luint32 CONFIG_INTENAS;
			Luint32 CONFIG_INTENAC;
			Luint32 CONFIG_PRY;
			Luint32 CONFIG_AND;
			Luint32 CONFIG_HRSH;
			Luint32 CONFIG_XOR;
			Luint32 CONFIG_DIR;
			Luint32 CONFIG_PDR;
			Luint32 CONFIG_PULDIS;
			Luint32 CONFIG_PSL;
			Luint32 CONFIG_PCR;
		}RM4_HET__CONFIG_REG_T;


		#define C_N2HET__MAX__PROGRAMS		16

		//the program types
		typedef enum
		{
			/** A basic timebase counter to register T */
			DYN_TYPE__TIMEBASE,

			/** A 50 bit timer using the 25bit timebase and then on each rollover
			* generate an interrupt and inc a new counter. Reading time base
			* requires reading two values */
			DYN_TYPE__TIMEBASE_50BIT,
			
			/** Pulse Width Capture, determined by rising / falling edge types */
			DYN_TYPE__PULSE_CAPTURE,

			/** Get interrupt on an edge
			 * If interrupts are off you can also use is as a edge counter*/
			DYN_TYPE__EDGE_DETECT,

			/** Get interrupt after 'n' edges*/
			DYN_TYPE__EDGE_COUNTER,

			/** PWM Program Type, specify duty cycle and period */
			DYN_TYPE__PWM,

			/** PWM Program with a counter, specify duty cycle and period and max counts */
			DYN_TYPE__PWM_WITH_COUNTER

		}RM4_N2HET__DYN_PROG__TYPES_T;


		/** main structure for N2HET program control
		 * Keeps track of our programs running in memory.
		 */
		struct _strRM4_N2HET
		{
			/** dynamic program control */
			struct
			{

				//the count of instructions used;
				Luint32 u32InstructionCount;

				/** The count of programs added */
				Luint32 u32ProgramCount;

				/** the programs */
				struct
				{
					/** which instruction in memory do we start on */
					Luint32 u32StartInstruction;

					/** The type of program we have added */
					RM4_N2HET__DYN_PROG__TYPES_T eProgramType;

				}sProgram[C_N2HET__MAX__PROGRAMS];


			}sDynamicProgram[N2HET_CHANNEL__NUM_CHANNELS];

		};


		//Function Protos
		void vRM4_N2HET__Init(RM4_N2HET__CHANNEL_T eChannel, Luint8 u8DontUpdateRAM, RM4_N2HET__HR_PRESCALE_T eHR_Prescale, RM4_N2HET__LR_PRESCALE_T eLR_Prescale);
		void vRM4_N2HET__Disable(RM4_N2HET__CHANNEL_T eChannel);
		void vRM4_N2HET__Enable(RM4_N2HET__CHANNEL_T eChannel);

		/* PWM Interface Functions */
		void vRM4_N2HET_PWM__Dyanmic_Start(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);
		void vRM4_N2HET_PWM__Dyanmic_Stop(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);
		void vRM4_N2HET_PWM__Dyanmic_SetDutyCycle(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex, Lfloat32 f32DutyCycle);
		void vRM4_N2HET_PWM__Dyanmic_SetPeriod(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex, Lfloat32 f32PeriodUS);
		void vRM4_N2HET_PWM__Dyanmic_SetCounts(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex, Luint32 u32Counter);

		/* Edge Interface Functions */
		void vRM4_N2HET_EDGE__ResetCounter(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);
		void vRM4_N2HET_EDGE__Set_MaxCount(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex, Luint32 u32Value);
		Luint32 u32RM4_N2HET_EDGE__Get_Counter(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);

		//Captured Signal Interface Functions
		Lfloat32 f32RM4_N2HET_CAPTURE__Get_Dyn_PulseWidth(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);

		/* Timestamp Interface Functions */
		void vRM4_N2HET1_TIMESTAMP__Reset_Timestamp(RM4_HET__RAMBASE_T * hetRAM);
		Luint32 u32RM4_N2HET1_TIMESTAMP__Get_Timestamp(RM4_HET__RAMBASE_T * hetRAM);

		//Pins.C
		void vRM4_N2HET_PINS__Init(RM4_N2HET__CHANNEL_T eChannel);
		void vRM4_N2HET_PINS__Set_PinDirection_Output(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinNumber);
		void vRM4_N2HET_PINS__Set_PinDirection_Input(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinNumber);
		void vRM4_N2HET_PINS__Set_PinHigh(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Bit);
		void vRM4_N2HET_PINS__Set_PinLow(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Bit);
		void vRM4_N2HET_PINS__Set_Pin(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Bit, Luint32 u32Value);
		Luint8 u8RM4_N2HET_PINS__Get_Pin(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinNumber);

		void vRM4_N2HET_PINS__Set_PortData(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Value);
		void vRM4_N2HET_PINS__Set_PortData_LSR(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Value, Luint32 u32LSRValue, Luint32 u32DataMask);
		Luint32 u32RM4_N2HET_PINS__Get_DIN_HET1(void);
		Luint32 u32RM4_N2HET_PINS__Get_DIN_HET2(void);
		void vRM4_N2HET_PINS__AND_ShareControl(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinNumber, Luint8 u8Enable);

		//interrupts
		void vRM4_N2HET_CHANNEL1_ISR__High(void);
		void vRM4_N2HET_CHANNEL1_ISR__Low(void);

		//user template
		void vRM4_N2HET_EDGE__Notification(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Edge);
		void vRM4_N2HET_PWM__Notification(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PWM, Luint32 notification);
		void vRM4_N2HET_DYNAMIC__Notification(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32ProgramIndex, Luint32 u32Register);

		//program
		void vN2HET_PROG_DYNAMIC__Clear(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Key);
		Luint16 u16N2HET_PROG_DYNAMIC__Add_Capture(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinIndex, RM4_N2HET__CAPTURE_T eType, Luint8 u8EnableInterrupt);
		Luint16 u16N2HET_PROG_DYNAMIC__Add_Edge(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinIndex, RM4_N2HET__EDGE_EDGE_T eType, Luint8 u8EnableInterrupt);
		Luint16 u16N2HET_PROG_DYNAMIC__Add_Edge_Counter(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinIndex, RM4_N2HET__EDGE_EDGE_T eType, Luint8 u8EnableInterrupt, Luint32 u32MaxCount);
		Luint16 u16N2HET_PROG_DYNAMIC__Add_PWM(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinIndex, Luint8 u8EnableInterrupt);
		Luint16 u16N2HET_PROG_DYNAMIC__Add_PWM_Counter(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinIndex, Luint8 u8EnableInterrupt, Luint32 u32MaxCounts);
		Luint16 u16N2HET_PROG_DYNAMIC__Add_QEP(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32PinCW_Index, Luint32 u32PinCCW_Index);

		//QEP
		Lint32 s32RM4_N2HET_QEP__Get_Counter(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);
		void vRM4_N2HET_QEP__Zero_Index(RM4_N2HET__CHANNEL_T eChannel, Luint16 u16ProgramIndex);

		//non user functions
		void vN2HET_PROG__BR__Make(RM4_HET__INSTRUCTION_T * pReturn, Luint8 u8Request, Luint8 u8Break, Luint16 u16NextProgAddx, Luint16 u16ConditionalAddx);
		void vN2HET_PROG__Update_RAM(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32Program, Luint32 u32Control, Luint32 u32Data);
		Lfloat32 f32RM4_N2HET_PROG_LR__Get_LoopTimeNS(RM4_N2HET__CHANNEL_T eChannel);

		//testing
		#if C_LOCALDEF__LCCM240__ENABLE_TEST_SPEC == 1U
			void vLCCM240_TS_001(void);
			void vLCCM240_TS_002(void);
			void vLCCM240_TS_003(void);
			void vLCCM240_TS_004(void);
			void vLCCM240_TS_005(void);
			void vLCCM240_TS_006(void);
			void vLCCM240_TS_007(void);
			void vLCCM240_TS_008(void);
			void vLCCM240_TS_009(void);
			void vLCCM240_TS_010(void);
			void vLCCM240_TS_011(void);
			void vLCCM240_TS_012(void);
			void vLCCM240_TS_013(void);
			void vLCCM240_TS_014(void);
			void vLCCM240_TS_015(void);
			void vLCCM240_TS_016(void);
			void vLCCM240_TS_017(void);
			void vLCCM240_TS_018(void);
			void vLCCM240_TS_019(void);
			void vLCCM240_TS_020(void);
		#endif

		//safetys

	#endif //C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE

#endif //RM4_HET
