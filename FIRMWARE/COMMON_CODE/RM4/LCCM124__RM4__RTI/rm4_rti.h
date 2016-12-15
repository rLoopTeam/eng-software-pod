/**
 * @file		rm4_rti.h
 * @brief		Main RTI header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571). This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM124R0.FILE.002
 */

#ifndef __RM48_RTI_H__
#define __RM48_RTI_H__
	
	/*lint -e537*/
	#include <localdef.h>

	#ifndef C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE
		#error
	#endif

	#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U
		/*****************************************************************************
		Includes
		*****************************************************************************/
		#include <RM4/LCCM124__RM4__RTI/rm4_rti__private.h>
		#include <RM4/LCCM124__RM4__RTI/rm4_rti__semistaticdef.h>


		//Structure to hold details about the counters
		struct _strCounter
		{
			Luint32 u32FRCValue; //Free Running Counter Current Value or Preset
			Luint32 u32CUValue; //Counter Up Current Value or Preset
			Luint32 u32CUCompareValuePrescale; //Value to generate pulse and restart the counter
			Luint32 u32FRCCaptureOnEvent; //Holds the value of the Free Running Counter on External Event (Just read)
			Luint32 u32CUCaptureOnEvent; //Holds the value of the Counter Up on External Event (Just read)
		};

		//Structure to hold details about the compare modules
		/*****************************************************************************
		*****************************************************************************/
		struct _strCompare
		{
			Luint8 u8CounterToCompareWith;
			Luint32 u32Compare;
			Luint32 u32UpdateCompare;
		};

		//Structure to hold details about the RTI Module
		/*****************************************************************************
		*****************************************************************************/
		struct _strRTI
		{
			Luint8 u8NTUsignalforTimeBase;
			Luint8 u8CountersRunInHaltDebug;
			Luint8 u8Counter0_Running;
			Luint8 u8Counter1_Running;
			Luint8 u8FRC0_IncrementsOnFailingExternalClock;
			Luint8 u8TimebaseForFRC0;
			Luint8 u8SourceCaptureEventCounter1;
			Luint8 u8SourceCaptureEventCounter0;
			struct _strCounter sCounter[RM48L950_RTI_NUMBER_OF_COUNTERS];
			struct _strCompare sCompare[RM48L950_RTI_NUMBER_OF_COMPARE_MODULES];
			Luint32 u32ValueToActivateTheEdgeDetectionCircuit;
			Luint32 u32ValueToDeactivateTheEdgeDetectionCircuit;

			Luint32 u32FRC1_OverflowInterruptEnabled;
			Luint32 u32FRC0_OverflowInterruptEnabled;
			Luint32 u32TimebaseInterruptEnabled;
			Luint32 u32DMA3_RequestEnabled;
			Luint32 u32DMA2_RequestEnabled;
			Luint32 u32DMA1_RequestEnabled;
			Luint32 u32DMA0_RequestEnabled;
			Luint32 u32Compare3_InterruptEnabled;
			Luint32 u32Compare2_InterruptEnabled;
			Luint32 u32Compare1_InterruptEnabled;
			Luint32 u32Compare0_InterruptEnabled;

			//Interrupt Flag register does not provide value to the structure.
			//WatchDog Registers not defined as it is not the intended use of the driver
			//Rest of the registers starting at offset ACh should not be used to avoid clearing pending RTI interrupts as per datasheet indication.
		};

		//Counter clock struct
		/*****************************************************************************
		*****************************************************************************/
		typedef struct
		{
			 Lfloat32 f32SrcFrequency;

			 Luint8 u8Div;

			 Lfloat32 f32OutFreq;

		}RM4_RTI__COUNTER_CLOCK_T;

		//RTI Internal clock structure
		typedef struct
		{
			 RM4_RTI__COUNTER_CLOCK_T sCounters[2];

		}RM4_RTI__INTERNAL_CLOCK_T;



		/*****************************************************************************
		//function prototypes
		*****************************************************************************/
		void vRM4_RTI__Init(void);
		void vRM4_RTI__Clear_Flags(Luint32 u32FlagsToClear);
		void vRM4_RTI__Update_Period(Luint8 u8Counter, Luint32 u32Period_US);
		void vRM4_RTI__SystemReset(void);

		Luint64 u64RM4_RTI__Get_Counter1(void);

		void vRM4_RTI__Start_Counter(Luint32 u32Counter);
		Lint16 s16RM4_RTI__Stop_Counter(Luint32 u32Counter);
		Lint16 s16RM4_RTI__ResetCounter(Luint32 u32Counter);
		Luint64 u64RM4_RTI__Get_Counter1(void);
		void vRM4_RTI__Start_Interrupts(void);

		void vRM4_RTI__Struct_Init(void);
		void vRTI_COMPARE__Disable_CompareInterrupt(Luint8 u8Index);
		void vRTI_COMPARE__Enable_CompareInterrupt(Luint8 u8Index);

		//interrupts
		void vRM4_RTI_ISR__Disable_Interrupts(void);
		void vRM4_RTI_ISR__Enable_Interrupts(void);
		void vRM4_RTI_ISR__Compare0(void);
		void vRM4_RTI_ISR__Compare1(void);
		void vRM4_RTI_ISR__Compare2(void);
		void vRM4_RTI_ISR__Compare3(void);
		void vRM4_RTI_ISR__Overflow0(void);
		void vRM4_RTI_ISR__Overflow1(void);
		void vRM4_RTI_ISR__Timebase(void);
		void vRM4_RTI_INTERRUPTS__DefaultCallbackHandler(void);

		//watchdog
		#if C_LOCALDEF__LCCM124__ENABLE_WDT == 1U
			void vRM4_RTI_WDT__Init(RM4_RTI_DWD__REACTION_T eReaction, Luint32 u32Preload, RM4_RTI_DWD__WINDOW_SIZE_T eWindowSize);
			Luint32 u32RM4_RTI_WDT__Get_DownCounter(void);
			void vRM4_RTI_WDT__Counter_Enable(void);
			void vRM4_RTI_WDT__Set_Preload(Luint32 u32Preload);
			void vRM4_RTI_WDT__Reset(void);
			void vRM4_RTI_WDT__Reset_If_Enabled(void);
			void vRM4_RTI_WDT__Generate_SysReset(void);
			Luint8 u8RM4_RTI_WDT__Get_IsKeySeq_Correct(void);
			RM4_RTI_DWD__RESET_STATUS_T tRM4_RTI_WDT__Get_Status(void);
			RM4_RTI_DWD__VIOLATION_T tRM4_RTI_WDT__Get_ViolationStatus(void);
			void vRM4_RTI_WDT__Clear_Flag(void);
		#endif
		
		/*Declarations fot the Test Unit*/
		#if C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC == 1U

			void vLCCM124_TS_001(void);

			//Manage IO on the test
			#define RM48L950_GIO_SET_LOW 0
			#define RM48L950_GIO_SET_HIGH 1
		#endif//#define C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC

	#endif //#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1
#endif //#ifndef __RM48_RTI_H__

