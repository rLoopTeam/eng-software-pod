/**
 * @file		CELL_MODEL__CELL.C
 * @brief		Simulates a physical cell
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM723R0.FILE.005
 */

/**
 * @addtogroup MULTICORE
 * @{
*/
/**
 * @addtogroup LIPO_CELL_MODEL
 * @ingroup MULTICORE
 * @{
*/
/**
 * @addtogroup LIPO_CELL_MODEL__CELL
 * @ingroup LIPO_CELL_MODEL
 * @{
*/
#include <MULTICORE/LCCM723__MULTICORE__LIPO_CELL_MODEL/cell_model.h>
#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

#include <math.h>

extern TS_LIPO_CELL_MODEL sLiPo;
#ifdef WIN32
	extern Lfloat32 f32CELLMODEL_TABLES__OCV[];
	extern TS_CELL_MODEL__POINT_2D f322DCELLMODEL_TABLES__Entropy[];
	extern Lfloat32 f32CELLMODEL_TABLES__Entropy[];
#else
	extern const Lfloat32 f32CELLMODEL_TABLES__OCV[];
	extern const TS_CELL_MODEL__POINT_2D f322DCELLMODEL_TABLES__Entropy[];
	extern const Lfloat32 f32CELLMODEL_TABLES__Entropy[];
#endif


/***************************************************************************//**
 * @brief
 * Init the cell
 * 
 * @param[in]		u16CellIndex			Index of the cell in the pack
 * @param[in]		u16PackIndex			The battery pack index
 * @st_funcMD5		7B53EDE734DBB4C2AA21C8AC2DF24059
 * @st_funcID		LCCM723R0.FILE.005.FUNC.001
 */
void vLIPOMODEL_CELL__Init(Luint16 u16PackIndex, Luint16 u16CellIndex)
{
	Luint32 u32Counter;
	
	if(u16CellIndex < C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK)
	{
		//clear the timer flag and the actual counter
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u8CellTimer_1S_Flag = 0U;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u32CellTimer_Counter = 0U;
		
		//physical params
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32CellCapacity_As = 5.0F * 3600.0F;
		
		//make the capacity the size of the number of parallel cells
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32CellCapacity_As *= (Lfloat32)C_LOCALDEF__LCCM723__NUM_PARALLEL;
		
		
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32CellMass_g = 138.0F;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32PCMMass_g = 12.0F;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32SpecificHeatCapacity_Cell_ = 1.0F;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32SpecificHeatCapacity_PCM_ = 2.1F;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32ResistanceTH_Ambient_ = 1.0e10;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32ResistanceTH_PCM_ = 1.0;
		sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32PCM_MeltTemp = 46.8F;
			
		//clear the variables to zero
		for(u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM723__MAX_TIME_SIZE; u32Counter++)
		{
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32Counter] = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32Counter] = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32Counter] = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellPower_W[u32Counter] = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellHeatCapacity_[u32Counter] = 0.0F;
			
			//temperature conditions
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32Counter] = 20.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32SensorTemperature_degC[u32Counter] = 20.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32PCMTemperature_degC[u32Counter] = 20.0F;
			
			//depth of discharge
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32Cell_DOD[u32Counter] = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellResistance_R[u32Counter] = 0.0F;
			
			//thermal model (just iinit some of these non array stuff too)
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.intIrrHeat = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.intRevHeat = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.ambCool = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.pcmHeat = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRate = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.meltFunc = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRatePCM = 0.0F;
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRateSense = 0.0F;
			
			
			
		}
	}
	else
	{
		//error
	}

	
}
/***************************************************************************//**
 * @brief
 * Call as qucik as possible
 * 
 * @param[in]		u16CellIndex			Index of the cell in teh pack
 * @param[in]		u16PackIndex			Index of the pack
 * @st_funcMD5		33D0C8F7E87FF6FDCDC21ADCE9D5162C
 * @st_funcID		LCCM723R0.FILE.005.FUNC.002
 */
void vLIPOMODEL_CELL__Process(Luint16 u16PackIndex, Luint16 u16CellIndex)
{
	Lfloat32 f32Temp;
	Lfloat32 f32R1, f32R2;
	
	Lint32 s32SoC;
	Lfloat32 f32SoC;
	Lfloat32 f32dV_dT;
	Lfloat32 f32NegTemp;
	Luint32 u32CurrentIndex;
	
	if(u16CellIndex < C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK)
	{
		//check for the flag
		if(sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u8CellTimer_1S_Flag == 1U)
		{
			//process the cell model
			if(sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u32CellTimer_Counter < C_LOCALDEF__LCCM723__MAX_TIME_SIZE)
			{
				
				u32CurrentIndex = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u32CellTimer_Counter;
				
				//compute the satate of charge at the current counter point.
				f32SoC = 1.0F - sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32Cell_DOD[u32CurrentIndex];
				
				f32Temp = f32SoC;
				f32Temp *= 100.0F;
				
				//convert to integer percentage and limit 0 to 100%
				s32SoC = (Lint32)f32Temp;

				//Limit
				if(s32SoC < 0)
				{
					s32SoC = 0;
				}
				else
				{
					if(s32SoC > 100)
					{
						s32SoC = 100;
					}
					else
					{
						//all good
					}
				}
				
				//compute the open circuit voltage at this point.
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32CurrentIndex] = f32SIL3_NUM_POLY__PolyVal((Lfloat32 *)&f32CELLMODEL_TABLES__OCV[0], 11U, f32SoC);
				
				//lookup the entropy curve at the current State Of Charge point
				f32dV_dT = -1.0F * f32CELLMODEL_TABLES__Entropy[s32SoC];
				
				//Resistance calculation - Equation 5
				f32NegTemp = -1.0F * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex];
				f32R1 = 0.0020495F * exp(f32NegTemp / 41.9763F);
				f32R2 = 0.00058736F * exp(f32NegTemp / 14.3779F);
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellResistance_R[u32CurrentIndex] = (f32R1 + f32R2) * 1.5F;
				
				
				if(sLiPo.sLoads.u8Current == 1U)
				{
					//constant current case % Equation 1
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32CurrentIndex] - sLiPo.sLoads.f32Current_A * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellResistance_R[u32CurrentIndex];
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex] = sLiPo.sLoads.f32Current_A;
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellPower_W[u32CurrentIndex] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex] * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex];
				}
				else if(sLiPo.sLoads.u8Power == 1U)
				{
					
					//Constant power case - Equation 2
					f32Temp = (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32CurrentIndex] * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32CurrentIndex]) - (4.0F * sLiPo.sLoads.f32Power_W * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellResistance_R[u32CurrentIndex]);
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex] = /*1.0F / 2.0F*/ 0.5 * (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32CurrentIndex] + sqrt(f32Temp));
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex] = sLiPo.sLoads.f32Power_W / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex];
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellPower_W[u32CurrentIndex] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex]*sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex];
				}
				else
				{
					//constant resistance load % Equation 3
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex] = sLiPo.sLoads.f32Resistance_R/(sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellResistance_R[u32CurrentIndex] + sLiPo.sLoads.f32Resistance_R) * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32OpenCircuitVoltage_V[u32CurrentIndex];
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex] / sLiPo.sLoads.f32Resistance_R;
					sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellPower_W[u32CurrentIndex] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellVoltage_V[u32CurrentIndex] * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex];
				}
				
				//% Cell thermal caculation - Equation 6
				//% Irreversible resistive heat generation
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.intIrrHeat = (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex] * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex]) * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellResistance_R[u32CurrentIndex];

				//% Reversible entropic heat generation
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.intRevHeat = f32dV_dT / 1000.0F * (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex] + 273.15F) * sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex];

				//% Cooling due to ambient
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.ambCool = 1.0F / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32ResistanceTH_Ambient_ * (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex] - sLiPo.sSim.f32TempAmbient_degC);
				//% Cooling due to PCM
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.pcmHeat = 1.0F / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32ResistanceTH_PCM_ * (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex] - sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32PCMTemperature_degC[u32CurrentIndex]);
				//% Temperature rate of change
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRate = 1.0F / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32CellMass_g / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32SpecificHeatCapacity_Cell_ *(sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.intIrrHeat + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.intRevHeat - sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.ambCool - sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.pcmHeat);


				//% PCM thermal calculation
				//% PCM specific heat capacity calculation - Equation 8
				f32Temp = (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32PCMTemperature_degC[u32CurrentIndex] - sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32PCM_MeltTemp);
				f32Temp *= f32Temp;

				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.meltFunc = 1.0F / sqrt(3.14159F * (2.5 * 2.5)) * exp(-1.0F * (f32Temp) / (2.5 * 2.5));
				//sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.meltFunc = 1.0F / sqrt(3.14159F * (2.5 * 2.5)) * exp(-1.0F * (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32PCMTemperature_degC[u32CurrentIndex] - sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.f32PCM_MeltTemp)^2/ (2.5 * 2.5));
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellHeatCapacity_[u32CurrentIndex] = (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32SpecificHeatCapacity_PCM_ + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.meltFunc * 242.0F /*heatMelt*/);

				//% Temperature rate of change - Equation 7
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRatePCM = 1.0F / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32PCMMass_g / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellHeatCapacity_[u32CurrentIndex] * (sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.pcmHeat);

				//% Sensor calculation - Equation 9
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRateSense = 1.0F / 50.0F /*timeConstSense*/ * (-sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32SensorTemperature_degC[u32CurrentIndex] + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex]);

				//% Integrate to next time step
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32Cell_DOD[u32CurrentIndex + 1U] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32Cell_DOD[u32CurrentIndex] + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellCurrent_A[u32CurrentIndex] * sLiPo.sSim.f32SimTimeStep / sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32CellCapacity_As;
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex + 1U] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32CellTemperature_degC[u32CurrentIndex] + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRate * sLiPo.sSim.f32SimTimeStep;
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32PCMTemperature_degC[u32CurrentIndex + 1U] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32PCMTemperature_degC[u32CurrentIndex] + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRatePCM * sLiPo.sSim.f32SimTimeStep;
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32SensorTemperature_degC[u32CurrentIndex + 1U] = sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].f32SensorTemperature_degC[u32CurrentIndex] + sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sTherm.tempRateSense * sLiPo.sSim.f32SimTimeStep;


				//inc the counter
				sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u32CellTimer_Counter++;
			}
			else
			{
				//we are at the limit, do nothing.
			}
			
			
			
			//clear the flag
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].u8CellTimer_1S_Flag = 0U;
		}
		else
		{
			//not ready yet
		}
	}
	else
	{
		//error
	}
	
	
}

/***************************************************************************//**
 * @brief
 * Provide a 1 second ISR for timing
 * 
 * @st_funcMD5		2637B33E0143B26514CBE46D2F2AF7CD
 * @st_funcID		LCCM723R0.FILE.005.FUNC.003
 */
void vLIPOMODEL_CELL__1S_ISR(void)
{
	Luint32 u32Counter;
	Luint32 u32Pack;
	
	for (u32Pack = 0U; u32Pack < C_LOCALDEF__LCCM723__NUM_PACKS; u32Pack++)
	{
		for (u32Counter = 0U; u32Counter < C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK; u32Counter++)
		{
			//set the flag to alert the proces loop that we have a new 1second interrupt.
			sLiPo.sPack[u32Pack].sCell[u32Counter].u8CellTimer_1S_Flag = 1U;
		}
	}
	
}

/***************************************************************************//**
 * @brief
 * Set cell capacity in Amp Seconds (Coloumbs)
 * 
 * @param[in]		f32Value			New cell capacity in As
 * @st_funcMD5		96DD81631075BDC917F9D62A66138747
 * @st_funcID		LCCM723R0.FILE.005.FUNC.004
 */
void vLIPOMODEL_CELL__Set_Capaciity_As(Luint16 u16PackIndex, Luint16 u16CellIndex, Lfloat32 f32Value)
{
	if(u16PackIndex < C_LOCALDEF__LCCM723__NUM_PACKS)
	{
		if(u16CellIndex < C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK)
		{
			sLiPo.sPack[u16PackIndex].sCell[u16CellIndex].sPhysical.f32CellCapacity_As = f32Value;
		}
		else
		{
			//error
		}
	}
	else
	{
		//error
	}
}


#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

