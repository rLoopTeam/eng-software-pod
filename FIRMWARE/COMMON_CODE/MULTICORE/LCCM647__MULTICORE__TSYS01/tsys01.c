/* TODO:
 * i2c implementation
 * how to handle 10ms delay between ADC conversion and reading measurement
 * 	timer...
 * doxygen compatible commenting
 * 
 * Simple Moving Average
 * 	sHANDSENSOR.u16AverageValue = u16NUMERICAL_FILTERING__Add_U16(u16Measurement, &sHANDSENSOR.u16AverageCounter, C_LCCM436__MAX_FILTERING_SIZE, &sHANDSENSOR.u16Averages[0]);
 * 	You need to store in your later, 
 * 	a counter for the average position (i.e. where the sample is last written to in the array, the max size of the array and an array of all the previous samples up to max array size.
 */


/**
 * @file		tsys01.C
 * @brief		Pressure Vessel Temperature Sensor
 * @author		Dean
 * @copyright	rLoop Inc.
 * @st_fileID	
 */


#include "tsys01.h"
#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

	/** Read calibration constants, compute conversion eqn coefficients */
	void vTSYS01__Init(void)
	{
		Luint8 u8ADCConvertingFlag = 0U;

		// raw temp ADC value
		Luint16 u16ADCTemperatureResult=0;

		// vars for filtering via u16NUMERICAL_FILTERING__Add_U16()
		Luint8 C_LCCM436__MAX_FILTERING_SIZE = 32; // 32 values will be kept in history
		Luint16 u16Averages[C_LCCM436__MAX_FILTERING_SIZE] = {}; // array containing filtered measurement history; NOTE UNITS ARE BITS
		Luint8 * pu8AverageCounter1 = 0; // index counter to remember where to put next data point
		
		// vars for converting to Celsius
		Lfloat32 f32Coeffs[5];
		Lfloat32 f32TemperatureResult=0;
		Lfloat32[10] f32Last10Values = {0,0,0,0,0,0,0,0,0,0};

		// TSYS01 must be reset after power up
		vI2CWrite(RESET); // TODO: unwritten function

	    u16KValues = u16TSYS01__Read_K_Values()

		// Use K values to compute the full coefficient for each polynomial term,   
	    // 	these coeffs are static, so this doesn't have to be done in __Process()
		f32Coeffs[4] = (-2.0F) * u16KValues[4] * pow(10, -21);
		f32Coeffs[3] = 4.0F * u16KValues[3] * pow(10, -16);
		f32Coeffs[2] = -2.0F * u16KValues[2] * pow(10, -11);
		f32Coeffs[1] = 1.0F * u16KValues[1] * pow(10, -6);
		f32Coeffs[0] = -1.5F * u16KValues[0] * pow(10, -2);

	}// end vTSYS01__Init()


	/** Read 16-bit temperature measurement, convert units to Celsius using eqn from datasheet */
	void vTSYS01__Process(void)
	{
		// if not already converting
		if(u8ADCConvertingFlag == OU)
		{
			// Tell TSYS01 to begin analog to digital conversion (10ms max duration)
			// vI2CWrite(START_ADC_TEMPERATURE_CONVERSION); // TODO: use a real function! 

			// TODO: is any return sent as acknowledgment of the command?

			// Set flag to show conversion has begun
			u8ADCConvertingFlag = 1U;

		}
		// conversion is already in progress
		//		assume the process is done? should return a 0 if conversion underway
		else 
		{
			u16ADCTemperatureResult = F_TSYS01_Read_ADC_Temperature_Result();

			// Reset flag now that measurement has been read
			u8ADCConvertingFlag = 0U;

			//log and filter, build array of averages
			Luint16 u16ADCFilteredTemperatureResult = u16NUMERICAL_FILTERING__Add_U16(u16ADCTemperatureResult, pu8AverageCounter1, C_LCCM436__MAX_FILTERING_SIZE, u16Averages[64]); //TODO: not sure what number should be in the [] for the final paramter, example has 0

			// TODO: write to u16Averages array here?

			// Compute temperature polynomial terms individually then sum
			Lfloat32 Term4 = f32Coeffs[4] * pow(u16ADCFilteredTemperatureResult, 4);
			Lfloat32 Term3 = f32Coeffs[3] * pow(u16ADCFilteredTemperatureResult, 3);
			Lfloat32 Term2 = f32Coeffs[2] * pow(u16ADCFilteredTemperatureResult, 2);
			Lfloat32 Term1 = f32Coeffs[1] * u16ADCFilteredTemperatureResult;
			Lfloat32 Term0 = f32Coeffs[0];
			
			f32TemperatureResult = Term4 + Term3 + Term2 + Term1 + Term0; // Celsius units


			u8FaultCheck();
		}

	}// end vTSYS01__Process()


	/** Most recent measurement, made global for external use */
	Lfloat32 f32TSYS01__Read_Temperature_Result(void)
	{
		return f32TemperatureResult;
	}


	/*******************************************************************************
	Unwritten Functions
	*******************************************************************************/
	
	// Check for failures of the TSYS01
	Luint8 u8FaultCheck()
	{
		// TODO: write this	

		// DATASHEET INFO:
		//	if the sensor is busy with ADC conversion, attempting to read Temp will return 0
		// 	others...?
	}

   	/** Read each of the 5 K calibration constants over i2c */
    Luint16[] u16TSYS01__Read_K_Values(void)
    {
    	// TODO: write to align with i2c code

    	Luint16 u16K[5];
    	u16K[0] = u16I2CRead(k0_ADR); // TODO: unwritten function
    	u16K[1] = u16I2CRead(k1_ADR);
    	u16K[2] = u16I2CRead(k2_ADR);
    	u16K[3] = u16I2CRead(k3_ADR);
    	u16K[4] = u16I2CRead(k4_ADR);

    	return u16K[5];
    }


   	/** to [ideally] be used for: read 16-bit k values, read 16-bit temperature result over i2c */
    Luint16 u16I2CRead(char ADR)
    {
    	// TODO: write to align with i2c code	
    }


    void vI2CWrite(char ADR)
    {
    	// TODO: write to align with i2c code
    }


	Lfloat16 f16TSYS01__Read_ADC_Temperature_Result(void)
	{
		// TODO: write to align with i2c code
		return u16ADCTemperatureResult;
	}


#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
	#error
#endif

