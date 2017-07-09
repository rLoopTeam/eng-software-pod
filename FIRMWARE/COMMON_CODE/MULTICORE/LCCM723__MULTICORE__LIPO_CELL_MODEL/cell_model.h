/**
 * @file		CELL_MODEL.H
 * @brief		Main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM723R0.FILE.001
 */

#ifndef _CELL_MODEL_H_
#define _CELL_MODEL_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/

		/*******************************************************************************
		Defines
		*******************************************************************************/
		/** Strucuture for a 2D lookup table */
		typedef struct
		{
			Lfloat32 f32X;
			Lfloat32 f32Y;

		}TS_CELL_MODEL__POINT_2D;

		/*******************************************************************************
		Structures
		*******************************************************************************/
		typedef struct
		{
			
			/** we need to apply a load to the cells, battery or packs*/
			struct
			{
				
				/** Current load */
				Luint8 u8Current;
				
				/** Power Load */
				Luint8 u8Power;
				
				/** Resistance Load */
				Luint8 u8Resistance;
				
				/** The load in Amps*/
				Lfloat32 f32Current_A;
				
				/** The power load in watts*/
				Lfloat32 f32Power_W;
				
				/** The resistance load in R */
				Lfloat32 f32Resistance_R;
				
			}sLoads;
			
			/** Simulation Items */
			struct
			{
				/** Simulation Time Step */
				Lfloat32 f32SimTimeStep;
				
				/** Ambient Temperature */
				Lfloat32 f32TempAmbient_degC;
				
			}sSim;
			
			/** Battery packs */
			struct
			{
				/** The total pack voltage */
				Lfloat32 f32PackVoltage_V;
			
				/** The individual cell model */
				struct
				{
					/** Physical Parameters */
					struct
					{
						/** Cell capacity in Amp Seconds
						i.e. 5Ah * 3600 = 18K*/
						Lfloat32 f32CellCapacity_As;
						
						/** Cell Mass in gramms */
						Lfloat32 f32CellMass_g;
						
						/** PCM Mass in gramms */
						Lfloat32 f32PCMMass_g;
						
						/** Specific Heat for the cell */
						Lfloat32 f32SpecificHeatCapacity_Cell_;
						
						/** Specific Heat for the PCM */
						Lfloat32 f32SpecificHeatCapacity_PCM_;
						
						Lfloat32 f32ResistanceTH_Ambient_;
						Lfloat32 f32ResistanceTH_PCM_;
						
						/** PCM Melt Temperature */
						Lfloat32 f32PCM_MeltTemp;
						
					}sPhysical;
					
					/** Cell 1 second timer increment flag */
					Luint8 u8CellTimer_1S_Flag;
					Luint32 u32CellTimer_Counter;
					
					/** Open circuit voltage vector, units are volts */
					Lfloat32 f32OpenCircuitVoltage_V[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Cell voltage in volts */
					Lfloat32 f32CellVoltage_V[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Cell Current, in Amps */
					Lfloat32 f32CellCurrent_A[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Cell Power, in Watts*/
					Lfloat32 f32CellPower_W[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Cell Heat Capacity*/
					Lfloat32 f32CellHeatCapacity_[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Cell Temperature, deg C */
					Lfloat32 f32CellTemperature_degC[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Sensor Temperature, deg C */
					Lfloat32 f32SensorTemperature_degC[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];

					/** PCM Temperature, deg C*/
					Lfloat32 f32PCMTemperature_degC[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
					
					/** Depth of Discharge, unitless */
					Lfloat32 f32Cell_DOD[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
				
					/** Cell Resistance, R*/
					Lfloat32 f32CellResistance_R[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
				
					/** Thermal Model */
					struct
					{
						
						/** Irreversible resistive heat generation */
						Lfloat32 intIrrHeat;
						
						/** Reversible entropic heat generation*/
						Lfloat32 intRevHeat;
						
						/** Cooling due to ambient */
						Lfloat32 ambCool;
						
						/** Cooling due to PCM */
						Lfloat32 pcmHeat;
						
						/** Temperature rate of change */
						Lfloat32 tempRate;
						
						/** PCM specific heat capacity calculation - Equation 8 */
						Lfloat32 meltFunc;
						Lfloat32 effHeatCap[C_LOCALDEF__LCCM723__MAX_TIME_SIZE];
						
						/** Temperature rate of change - Equation 7*/
						Lfloat32 tempRatePCM;

						/**  Sensor calculation - Equation 9 */
						Lfloat32 tempRateSense;
						
						
					}sTherm;
				
				
				}sCell[C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK];
			}sPack[C_LOCALDEF__LCCM723__NUM_PACKS];
			
		}TS_LIPO_CELL_MODEL;
		

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		//main
		DLL_DECLARATION void vLIPOMODEL__Init(void);
		DLL_DECLARATION void vLIPOMODEL__Process(void);
		DLL_DECLARATION void vLIPOMODEL__1S_ISR(void);

		//cell functions
		void vLIPOMODEL_CELL__Init(Luint16 u16PackIndex, Luint16 u16CellIndex);
		void vLIPOMODEL_CELL__Process(Luint16 u16PackIndex, Luint16 u16CellIndex);
		void vLIPOMODEL_CELL__1S_ISR(void);
		
		//battery
		void vLIPOMODEL_BATTERY__Init(Luint16 u16BattIndex);
		void vLIPOMODEL_BATTERY__Process(Luint16 u16BattIndex);
		
		//win32 simulation
		#ifdef WIN32
			DLL_DECLARATION Lfloat32 f32LIPOMODEL_WIN32__Get_PackVoltage(Luint16 u16PackIndex);
			DLL_DECLARATION void vLIPOMODEL_WIN32__Update_LoadPower(Lfloat32 f32Value);
			DLL_DECLARATION void vLIPOMODEL_WIN32__Update_LoadCurrent(Lfloat32 f32Value);
		#endif

		//safetys
		#ifndef C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK
			#error
		#endif
		#ifndef C_LOCALDEF__LCCM723__MAX_TIME_SIZE
			#error
		#endif
		#ifndef C_LOCALDEF__LCCM723__NUM_PACKS
			#error
		#endif	
		
	#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_CELL_MODEL_H_

