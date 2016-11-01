/* TODO:
 * doxygen compatible commenting
 */


/**
 * @file		tsys01.C
 * @brief		Pressure Vessel Temperature Sensor
 * @author		Dean & Lachlan
 * @copyright	rLoop Inc.
 * @st_fileID	
 */


#include "tsys01.h"
#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U


//structure
struct _strTSYS01 sTSYS;

//locals
Lint16 s16TSYS01__Read_K_Values(Luint16 *pu16Values);

/** Read calibration constants, compute conversion eqn coefficients */
void vTSYS01__Init(void)
{
	Luint8 u8Counter;

	//structure init
	sTSYS.eState = TSYS01_STATE__INIT_DEVICE;
	sTSYS.u32LoopCounter = 0U;
	sTSYS.u16AverageResult = 0U;
	sTSYS.u16AverageCounter = 0U;

	//set to some out there value
	sTSYS.f32TempDegC = 127.0F;

	//clear the average
	for(u8Counter = 0U; u8Counter < C_TSYS01__MAX_FILTER_SAMPLES; u8Counter++)
	{
		sTSYS.u16AverageArray[u8Counter] = 0U;
	}

}


/** Read 16-bit temperature measurement, convert units to Celsius using eqn from datasheet */
void vTSYS01__Process(void)
{
	Luint16 u16KValues[5];
	Lfloat32 f32Term[5];
	Lint16 s16Return;

	//handle the state machine
	switch(sTSYS.eState)
	{
		case TSYS01_STATE__IDLE:
			//do nothing,
			break;

		case TSYS01_STATE__INIT_DEVICE:
			//reset the device
			//TSYS01 must be reset after power up
			s16Return = s16TSYS01_I2C__TxCommand(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__RESET);
			if(s16Return >= 0)
			{
				//success
				//change state
				sTSYS.eState = TSYS01_STATE__READ_CONSTANTS;
			}
			else
			{
				//read error, handle state.
				sTSYS.eState = TSYS01_STATE__ERROR;
			}
			break;

		case TSYS01_STATE__READ_CONSTANTS:

			//issue the read command and read all 5 values
			s16Return = s16TSYS01__Read_K_Values(&u16KValues[0]);
			if(s16Return >= 0)
			{
				//process
				// Use K values to compute the full coefficient for each polynomial term,
				// these coeffs are static, so this doesn't have to be done in __Process()
				sTSYS.f32Coeffs[4] = (-2.0F) * (Lfloat32)u16KValues[4] * f32NUMERICAL__Power(10, -21);
				sTSYS.f32Coeffs[3] = 4.0F * (Lfloat32)u16KValues[3] * f32NUMERICAL__Power(10, -16);
				sTSYS.f32Coeffs[2] = -2.0F * (Lfloat32)u16KValues[2] * f32NUMERICAL__Power(10, -11);
				sTSYS.f32Coeffs[1] = 1.0F * (Lfloat32)u16KValues[1] * f32NUMERICAL__Power(10, -6);
				sTSYS.f32Coeffs[0] = -1.5F * (Lfloat32)u16KValues[0] * f32NUMERICAL__Power(10, -2);

				//todo: range checks on constants.

				//move to ready state waiting for a conversion start
				sTSYS.eState = TSYS01_STATE__WAITING;

			}
			else
			{
				//Change to error state
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

			break;

		case TSYS01_STATE__WAITING:
			//here we are waiting, we can use a function to trigger a start conversion as we don't want to
			//just start processing if the rest of the system is not operational..
			break;


		case TSYS01_STATE__BEGIN_SAMPLE:
			//issue the request
			s16Return = s16TSYS01_I2C__TxCommand(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__START_ADC_TEMPERATURE_CONVERSION);
			if(s16Return >= 0)
			{
				//sample started, wait for some processing loops to expire

				//clear the counter
				sTSYS.u32LoopCounter = 0U;

				//change states
				sTSYS.eState = TSYS01_STATE__WAIT_LOOPS;

			}
			else
			{
				//error has occurred
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

			break;

		case TSYS01_STATE__WAIT_LOOPS:

			//todo, change to constant
			if(sTSYS.u32LoopCounter > 1000)
			{
				//move on to read the ADC
				sTSYS.eState = TSYS01_STATE__READ_ADC;

			}
			else
			{
				//stay in state
			}
			break;


		case TSYS01_STATE__READ_ADC:
			//do the ADC read
			s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__READ_ADC_TEMPERATURE_RESULT, &sTSYS.u16LastResult);
			if(s16Return >= 0)
			{
				//add to filter
				sTSYS.u16AverageResult = u16NUMERICAL_FILTERING__Add_U16(sTSYS.u16LastResult,
																		&sTSYS.u16AverageCounter,
																		C_TSYS01__MAX_FILTER_SAMPLES,
																		&sTSYS.u16AverageArray[0]);
				//change state
				sTSYS.eState = TSYS01_STATE__COMPUTE;
			}
			else
			{
				//error has occurred
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

			break;

		case TSYS01_STATE__COMPUTE:
			// Compute temperature polynomial terms individually then sum
			f32Term[4] = sTSYS.f32Coeffs[4] * f32NUMERICAL__Power(sTSYS.u16AverageResult, 4);
			f32Term[3] = sTSYS.f32Coeffs[3] * f32NUMERICAL__Power(sTSYS.u16AverageResult, 3);
			f32Term[2] = sTSYS.f32Coeffs[2] * f32NUMERICAL__Power(sTSYS.u16AverageResult, 2);
			f32Term[1] = sTSYS.f32Coeffs[1] * (Lfloat32)sTSYS.u16AverageResult;
			f32Term[0] = sTSYS.f32Coeffs[0];

			// Celsius units
			sTSYS.f32TempDegC = f32Term[4] + f32Term[3] + f32Term[2] + f32Term[1] + f32Term[0];

			//go back and re-sample
			sTSYS.eState = TSYS01_STATE__BEGIN_SAMPLE;

			break;

		case TSYS01_STATE__ERROR:
			//some error has happened
			break;

	}

}


//call this when you are ready to start getting data from the TSYS01
void vTSYS01__Enable(void)
{
	if(sTSYS.eState == TSYS01_STATE__WAITING)
	{
		//change to being sampling.
		sTSYS.eState = TSYS01_STATE__BEGIN_SAMPLE;
	}
	else
	{
		//error, not allowed to change state until we are waiting.
	}

}


/** Read each of the 5 K calibration constants over i2c */
Lint16 s16TSYS01__Read_K_Values(Luint16 *pu16Values)
{
	Lint16 s16Return;
	Luint16 * pu16Temp;

	pu16Temp = &pu16Values[0];
	s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k0_ADR, pu16Temp);
	if(s16Return >= 0)
	{
		pu16Temp = &pu16Values[1];
		s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k1_ADR, pu16Temp);
		if(s16Return >= 0)
		{
			pu16Temp = &pu16Values[2];
			s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k2_ADR, pu16Temp);
			if(s16Return >= 0)
			{
				pu16Temp = &pu16Values[3];
				s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k3_ADR, pu16Temp);
				if(s16Return >= 0)
				{
					pu16Temp = &pu16Values[4];
					s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k4_ADR, pu16Temp);

					//fall on
				}
				else
				{
					//fall on
				}

			}
			else
			{
				//fall on with error code
			}

		}
		else
		{
			//fall on with error code
		}
	}
	else
	{
		//fall on
	}

	//return with the status of the I2C read
	return s16Return;
}


/** Most recent measurement, made global for external use */
Lfloat32 f32TSYS01__Get_TempDegC(void)
{
	return sTSYS.f32TempDegC;
}

#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
	#error
#endif

