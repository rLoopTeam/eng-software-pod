/**
 * @file		MMA8451.H
 * @brief		Main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM418R0.FILE.014
 */

#ifndef _MMA8451_H_
#define _MMA8451_H_

	/*lint -e537*/
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM418__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM418__ENABLE_THIS_MODULE == 1U
	
	/*****************************************************************************
	Includes
	*****************************************************************************/
	#include <MULTICORE/LCCM418__MULTICORE__MMA8451/mma8451__register_defs.h>
	#include <MULTICORE/LCCM418__MULTICORE__MMA8451/mma8541__fault_flags.h>
	#include <MULTICORE/LCCM418__MULTICORE__MMA8451/mma8451__types.h>
	#include <multicore/lccm284__multicore__fault_tree/fault_tree__public.h>



	//in 14 bit, 8g mode we have 1G = 
	//2^14 = 16K/16 = 1024
	#if C_LOCALDEF__LCCM418__G_FORCE_RANGE == 8U
		#define C_MMA8451__ONE_G_VALUE	1024U
	#elif C_LOCALDEF__LCCM418__G_FORCE_RANGE == 4U
		#define C_MMA8451__ONE_G_VALUE	2048U
	#elif C_LOCALDEF__LCCM418__G_FORCE_RANGE == 2U
			#define C_MMA8451__ONE_G_VALUE	4096U
	#else
		#error
	#endif
	
	//The minimum +/- value for next cal state transition
	#define C_MMA8451__MIN_CAL_WINDOW		2U


	#define C_MMA8451__MAGIC_HEADER_VALUE		0xABCD0123U

	/** Main MMA8451 structure */
	struct strMMA8451
	{
		/** The fault tree for each channel */
		FAULT_TREE__PUBLIC_T sFaultFlags;

		/** New sample avail for the top level to process */
		Luint8 u8NewSampleReady;

		/** IO Port Flags */
		struct
		{
			/** Data ready due to sample from IO Pin */
			Luint8 u8DataReady;

			/** Data ready due to interrupt called */
			Luint8 u8Interrupt;

			/** Set to 1 to inhibit the interrupt during a read */
			Luint8 u8InterruptInhibit;

			/** The count of interrupts last seen */
			Luint32 u32InterruptLastSeen;

		}sPortFlags;

		/** The first X,Y,Z read */
		struct
		{
			Lint16 s16;
		}sFirstRead[MMA8451_AXIS__MAX];
		
		/** These are the sensor offsets which are the calibrated parameters to offset each sensors channel correctly. */
		struct
		{
			/** mma8450 only supports 8 bit offsets but we need to store the data as twos complement*/
			/*lint -e960*/
			//Note 960: Violates MISRA 2004 Required Rule 18.4, unions
			union
			{
				Lint8 s8;
				Luint8 u8;
			}unT;
			/*lint +e960*/
			
		}sSensorOffset[MMA8451_AXIS__MAX];
		
		/** When we have calibration in progress, we need to have theses states */
		struct
		{
			
			#define C_MMA8451__CALSTATE__NONE		0
			#define C_MMA8451__CALSTATE__X			1
			#define C_MMA8451__CALSTATE__Y			2
			#define C_MMA8451__CALSTATE__Z			3
			//#define C_MMA8451__CALSTATE__SAVE_VALUES	4
			Luint8 u8State;

			/** Is a fine zero required of the system */
			Luint8 u8FineZeroRequired;
			
			/** If a fine zero is needed, this is the current axis that is being zeroed */
			MMA8451__AXIS_E eFineZeroAxis;

			Luint8 u8CalEntryCounter;

		}sCalibration;
	
		/** Mathematic calculations */
		struct
		{
			/** The x,y incline */
			Lfloat32 f32PitchXY;
			
			/** The Roll based on the Z axis */
			Lfloat32 f32RollZ;

			/** The sum of accelerations in each of the sensors 
			*(should be 1.0, else sensor has linear accel influence) */
			Lfloat32 f32AccelSum;
			
		}sMath;
		
		/** The current instant sample for each channel 
		* This value is updated each interrupt or data ready call */
		struct
		{
			#if C_LOCALDEF__LCCM418__USER_AVERAGE_MAX_SAMPLES > 0U
				/** This is the averaging system, used to filter the data for each channel */
				struct
				{
					/** The current position in the averag buffer */
					Luint16 u16AverageCounter;

					/** The average samples */
					Lint16 s16AverageSamples[C_LOCALDEF__LCCM418__USER_AVERAGE_MAX_SAMPLES];

					/** the actual average value. */
					Lint16 s16Average;

				}sAverage[3U];
			#else
				struct
				{
					/** the actual average value, in this mode just used as raw sample. */
					Lint16 s16Average;

				}sAverage[MMA8451_AXIS__MAX];
			#endif
			/** The computed G-Forces */
			struct
			{
				Lfloat32 f32;

			}sGForce[3];
					
		}sCurrentSample;
		
		#if C_LOCALDEF__LCCM418__ENABLE_ROC == 1U
			/** Handles rate of change data storage */
			struct
			{
				/** The previous angle for ROC calculation */
				Lfloat32 f32PrevAngle;

				/** The calculated ROC*/
				Lfloat32 f32ROC;

				#if C_LOCALDEF__LCCM418__ROC_AVERAGE_MAX_SAMPLES > 0U
					/** Buffer for ROC */
					Lfloat32 f32ROC_Filter[C_LOCALDEF__LCCM418__ROC_AVERAGE_MAX_SAMPLES];

					/** Current average ROC value */
					Lfloat32 f32ROC_Average_Value;

					/** ROC average counter */
					Luint16 u16AverageCounter;
				#endif
			}sROC;
				
		#endif
		
		//the number of average samples the user wants.
		Luint16 u16UserAverageValue;
		Luint16 u16Prev_UserAverageValue;
	};

	/*****************************************************************************
	Function Prototypes
	*****************************************************************************/
	void vMMA8451__Init(Luint8 u8DeviceIndex);
	void vMMA8451__Process(Luint8 u8DeviceIndex);
	Luint8 u8MMA8451_PROCESS__Get_CalibrationState(Luint8 u8DeviceIndex);
	void vMMA8451_PROCESS__Calibration(Luint8 u8DeviceIndex);
	void vMMA8451__ISR(Luint8 u8DeviceIndex);
	Luint32 u32MMA8451__Get_FaultFlags(Luint8 u8DeviceIndex);
	Luint8 u8MMA8451__Get_IsFault(Luint8 u8DeviceIndex);
	Luint8 u8MMA8451__Get_NewSampleReady(Luint8 u8DeviceIndex);
	void vMMA8451__Clear_NewSampleReady(Luint8 u8DeviceIndex);

	//ROC
	void vMMA8451_ROC__Process_ROC(Luint8 u8DeviceIndex, Lfloat32 f32DifferenceTime);
	Lfloat32 f32MMA8451_ROC__Get_ROC(Luint8 u8DeviceIndex);

	//filtering
	#if C_LOCALDEF__LCCM418__USER_AVERAGE_MAX_SAMPLES > 0U
		void vMMA8451_FILTERING__Init(Luint8 u8DeviceIndex);
		void vMMA8451_FILTERING__Add(Luint8 u8DeviceIndex, MMA8451__AXIS_E eAxis, Lint16 s16Value);
	#endif
	DLL_DECLARATION Lint16 s16MMA8451_FILTERING__Get_Average(Luint8 u8DeviceIndex, MMA8451__AXIS_E eAxis);

	//read	
	Lint16 s16MMA8451_READ__ReadXYZ(Luint8 u8DeviceIndex);
	Lint16 s16MMA8451_LOWLEVEL__ReadByte(Luint8 u8DeviceIndex, Luint8 u8AddxOffset, Luint8 * pu8Value);
	Lint16 s16MMA8451_LOWLEVEL__ReadMultiple(Luint8 u8DeviceIndex, Luint8 u8AddxOffset, Luint8 * pu8Array, Luint8 u8Length);
	Lint16 s16MMA8451_LOWLEVEL__WriteByte(Luint8 u8DeviceIndex, Luint8 u8AddxOffset, Luint8 u8Value);
	Lint16 s16MMA8451_READ__StatusRegister(Luint8 u8DeviceIndex, Luint8 * pReg);

	//math
	void vMMA8451_MATH__Sum_Acceleration(Luint8 u8DeviceIndex);
	Lfloat32 f32MMA8451_MATH__Get_AccelSum(Luint8 u8DeviceIndex);

	//only some functions avail with gforce options.
	#if C_LOCALDEF__LCCM418__ENABLE_G_FORCE == 1U
		void vMMA8451_MATH__Process_GForce(Luint8 u8DeviceIndex);
		Lfloat32 f32MMA8451_MATH__Get_GForce(Luint8 u8DeviceIndex, MMA8451__AXIS_E eAxis);
		void vMMA8451_MATH__Calculate_Roll_Z(Luint8 u8DeviceIndex);
		void vMMA8451_MATH__Calculate_InclineXY(Luint8 u8DeviceIndex);
		Lfloat32 f32MMA8451_MATH__Get_PitchAngle(Luint8 u8DeviceIndex);
		Lfloat32 f32MMA8451_MATH__Get_RollAngle(Luint8 u8DeviceIndex);
	#endif

	//zero
	void vMMA8451_ZERO__AutoZero(Luint8 u8DeviceIndex);
	void vMMA8451_ZERO__Set_FineZero(Luint8 u8SensorIndex, MMA8451__AXIS_E eAxis);
	void vMMA8451_ZERO__ClearAll(void);
	void vMMA8451_ZERO__RestoreZero(Luint8 u8DeviceIndex);
	void vMMA8451_ZERO__SetX_SensorZero_FineZero(Luint8 u8DeviceIndex);
	void vMMA8451_ZERO__SetY_SensorZero_FineZero(Luint8 u8DeviceIndex);
	void vMMA8451_ZERO__SetZ_SensorZero_FineZero(Luint8 u8DeviceIndex);
	Lint16 s16MMA8451_ZERO__Get_SensorOffset(Luint8 u8DeviceIndex, MMA8451__AXIS_E eAxis);

	//FIFO functions
	void vMMA8451_FIFO__Init(void);
	void vMMA8451_FIFO__Read(void);
	
	#ifdef WIN32
		DLL_DECLARATION void vMMA8451_WIN32__TriggerInterrupt(Luint8 u8DeviceIndex);
		typedef void (__cdecl * pMMA8451_WIN32__ReadDataCallback_FuncType)(Luint8 u8DeviceIndex, Lint16 *ps16X, Lint16 *ps16Y, Lint16 *ps16Z);
		DLL_DECLARATION void vMMA8451_WIN32__Set_ReadDataCallback(pMMA8451_WIN32__ReadDataCallback_FuncType pFunc);
		void vMMA8451_WIN32__ReadData(Luint8 u8DeviceIndex, Lint16 *ps16X, Lint16 *ps16Y, Lint16 *ps16Z);

	#endif
	
	#if C_LOCALDEF__LCCM418__ENABLE_TEST_SPEC == 1U
		void vLCCM418_TS_001(void);
	#endif

	#endif //C_LOCALDEF__LCCM418__ENABLE_THIS_MODULE
#endif //MMA8451

