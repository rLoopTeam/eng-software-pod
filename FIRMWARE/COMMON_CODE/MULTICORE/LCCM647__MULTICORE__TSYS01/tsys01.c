/**
 * @file		TSYS01.C
 * @brief		TSYS01 Temp Sensor Driver
 * @author		Dean, Lachlan Grogan
 * @st_fileID	LCCM647R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup TSYS01
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup TSYS01__CORE
 * @ingroup TSYS01
 * @{ */
 
#include "tsys01.h"
#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U


//structure
struct _strTSYS01 sTSYS;

//locals
Lint16 s16TSYS01__Read_K_Values(Luint16 *pu16Values);

/***************************************************************************//**
 * @brief
 * Init any variables as needed
 * 
 * @st_funcMD5		550AC09EA4072FFD84D5440F4046F601
 * @st_funcID		LCCM647R0.FILE.000.FUNC.001
 */
void vTSYS01__Init(void)
{
	Luint8 u8Counter;

	//structure init
	sTSYS.eState = TSYS01_STATE__INIT_DEVICE;
	sTSYS.u32LoopCounter = 0U;
	sTSYS.u32AverageResult = 0U;
	sTSYS.u32AverageResult_Div256 = 0U;
	sTSYS.u16AverageCounter = 0U;

	//set to some out there value
	sTSYS.f32TempDegC = 127.0F;

	//clear the average
	for(u8Counter = 0U; u8Counter < C_TSYS01__MAX_FILTER_SAMPLES; u8Counter++)
	{
		sTSYS.u32AverageArray[u8Counter] = 0U;
	}

}


/***************************************************************************//**
 * @brief
 * Main processing state machine.
 * 
 * @st_funcMD5		8C7BCC3EE06496D86D8B401AE97E08C5
 * @st_funcID		LCCM647R0.FILE.000.FUNC.002
 */
void vTSYS01__Process(void)
{
	Luint16 u16KValues[5];
	Lfloat32 f32Term[5];
	Lfloat32 f32Pow;
	Lint16 s16Return;

	//handle the state machine
	switch(sTSYS.eState)
	{
		case TSYS01_STATE__IDLE:
			//do nothing,
			break;

		case TSYS01_STATE__INIT_DEVICE:
			//reset the device

			//wait a little bit incase we came in from clocking out bad I2C data.
			vRM4_DELAYS__Delay_mS(10U);

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

				#if C_LOCALDEF__LCCM647__ENABLE_DS_VALUES == 1U
					u16KValues[4] = 28446;
					u16KValues[3] = 24926;
					u16KValues[2] = 36016;
					u16KValues[1] = 32791;
					u16KValues[0] = 40781;
				#endif

				//process
				// Use K values to compute the full coefficient for each polynomial term,
				// these coeffs are static, so this doesn't have to be done in __Process()
				f32Pow = f32NUMERICAL__Power(10.0F, -21.0F);
				sTSYS.f32Coeffs[4] = (-2.0F) * (Lfloat32)u16KValues[4] * f32Pow;

				sTSYS.f32Coeffs[3] = 4.0F * (Lfloat32)u16KValues[3] * f32NUMERICAL__Power(10.0F, -16.0F);
				sTSYS.f32Coeffs[2] = -2.0F * (Lfloat32)u16KValues[2] * f32NUMERICAL__Power(10.0F, -11.0F);
				sTSYS.f32Coeffs[1] = 1.0F * (Lfloat32)u16KValues[1] * f32NUMERICAL__Power(10.0F, -6.0F);
				sTSYS.f32Coeffs[0] = -1.5F * (Lfloat32)u16KValues[0] * f32NUMERICAL__Power(10.0F, -2.0F);

				//todo: range checks on constants.

				//move to ready state waiting for a conversion start
				sTSYS.eState = TSYS01_STATE__BEGIN_SAMPLE;

			}
			else
			{
				//Change to error state
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

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
			if(sTSYS.u32LoopCounter > C_LOCALDEF__LCCM647__NUM_CONVERSION_LOOPS)
			{
				//move on to read the ADC
				sTSYS.eState = TSYS01_STATE__READ_ADC;

			}
			else
			{
				//increment the loop counter;
				sTSYS.u32LoopCounter += 1;
				//stay in state
			}
			break;

		case TSYS01_STATE__READ_ADC:
			//do the ADC read
			s16Return = s16TSYS01_I2C__RxU24(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__READ_ADC_TEMPERATURE_RESULT, &sTSYS.u32LastResult);
			if(s16Return >= 0)
			{

				#if C_LOCALDEF__LCCM647__ENABLE_DS_VALUES == 1U
					sTSYS.u32LastResult = 9378708;
				#endif
				//add to filter
				sTSYS.u32AverageResult = u32NUMERICAL_FILTERING__Add_U32(sTSYS.u32LastResult,
																		&sTSYS.u16AverageCounter,
																		C_TSYS01__MAX_FILTER_SAMPLES,
																		&sTSYS.u32AverageArray[0]);
				#if C_LOCALDEF__LCCM647__ENABLE_DS_VALUES == 1U
					sTSYS.u32AverageResult = 9378708;
				#endif

				//generate the DIV256 option
				sTSYS.u32AverageResult_Div256 = sTSYS.u32AverageResult >> 8U;

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
			f32Term[4] = sTSYS.f32Coeffs[4] * f32NUMERICAL__Power(sTSYS.u32AverageResult_Div256, 4);
			f32Term[3] = sTSYS.f32Coeffs[3] * f32NUMERICAL__Power(sTSYS.u32AverageResult_Div256, 3);
			f32Term[2] = sTSYS.f32Coeffs[2] * f32NUMERICAL__Power(sTSYS.u32AverageResult_Div256, 2);
			f32Term[1] = sTSYS.f32Coeffs[1] * (Lfloat32)sTSYS.u32AverageResult_Div256;
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

/***************************************************************************//**
 * @brief
 * Read each of the 5 K calibration constants over i2c
 * 
 * @param[in]		*pu16Values				Pointer to returned values
 * @st_funcMD5		CAF68263EFC16BA4861833E1AB48F59A
 * @st_funcID		LCCM647R0.FILE.000.FUNC.003
 */
Lint16 s16TSYS01__Read_K_Values(Luint16 *pu16Values)
{
	Lint16 s16Return;
	Luint16 * pu16Temp;

	vRM4_DELAYS__Delay_mS(10U);
	pu16Temp = &pu16Values[0];
	s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k0_ADR, pu16Temp);
	if(s16Return >= 0)
	{
		vRM4_DELAYS__Delay_mS(10U);
		pu16Temp = &pu16Values[1];
		s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k1_ADR, pu16Temp);
		if(s16Return >= 0)
		{
			vRM4_DELAYS__Delay_mS(10U);
			pu16Temp = &pu16Values[2];
			s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k2_ADR, pu16Temp);
			if(s16Return >= 0)
			{
				vRM4_DELAYS__Delay_mS(10U);
				pu16Temp = &pu16Values[3];
				s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k3_ADR, pu16Temp);
				if(s16Return >= 0)
				{
					vRM4_DELAYS__Delay_mS(10U);
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

/***************************************************************************//**
 * @brief
 * Most recent measurement, made global for external use
 * 
 * @return			Temperature in DegC
 * @st_funcMD5		8659D658713AB1BA9D1CC17CFF9FDCB4
 * @st_funcID		LCCM647R0.FILE.000.FUNC.004
 */
Lfloat32 f32TSYS01__Get_TempDegC(void)
{
	return sTSYS.f32TempDegC;
}

#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
