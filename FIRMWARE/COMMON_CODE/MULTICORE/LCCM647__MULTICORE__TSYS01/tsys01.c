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

		// vars for filtering
		Luint16[64] u16Averages = {}; // TODO: too big? probably too big...
		Luint8 * pu8AverageCounter1 = 0; // for use in u16NUMERICAL_FILTERING__Add_U16
		Luint8 * pu8AverageCounter2 = 0; // for use in my simple moving average 
		Luint8 C_LCCM436__MAX_FILTERING_SIZE = 64;

		// vars for converting to Celsius
		Lfloat32 f32Coeffs[5];
		Lfloat32 f32TemperatureResult=0;
		Lfloat32[10] f32Last10Values = {0,0,0,0,0,0,0,0,0,0};

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
			u16NUMERICAL_FILTERING__Add_U16(u16ADCTemperatureResult, pu8AverageCounter1, C_LCCM436__MAX_FILTERING_SIZE, u16Averages[64]); //TODO: not sure what number should be in the [] for the final paramter, example has 0

			// Compute temperature polynomial terms individually then sum
			Lfloat32 Term4 = f32Coeffs[4] * pow(u16ADCTemperatureResult, 4);
			Lfloat32 Term3 = f32Coeffs[3] * pow(u16ADCTemperatureResult, 3);
			Lfloat32 Term2 = f32Coeffs[2] * pow(u16ADCTemperatureResult, 2);
			Lfloat32 Term1 = f32Coeffs[1] * u16ADCTemperatureResult;
			Lfloat32 Term0 = f32Coeffs[0];
			
			f32TemperatureResult = Term4 + Term3 + Term2 + Term1 + Term0; // Celsius units

			// Is new data point reasonable?
			vFilterTemperatureData();

		}

	}// end vTSYS01__Process()


	/** Most recent measurement, made global for external use */
	Lfloat32 f32TSYS01__Read_Temperature_Result(void)
	{
		return f32TemperatureResult;
	}


	/*******************************************************************************
	My Simple Moving Average Functions
	*******************************************************************************/

	/** Compare the new data point to the average of the previous 5 points, if it deviates by X degrees C don't save the value */
	void vFilterTemperatureData(void)
	{
		Lfloat32 f32RecentTemperatureAverage = f32NUMERICAL_FLOAT_AVERAGE(); 

		// if the measurement is within acceptable range
		if(abs(f32TemperatureResult - f32RecentTemperatureAverage) < X.0F) // TODO: Define acceptable devation from recent average
		{
			// update the recent history array to save this measurement
			vUpdateMeasurementHistory();
		}
		// if the measurement has deviated too greatly from the recent average
		else
		{
			// TODO: undecided on action

			// f32TemperatureResult = f32RecentTemperatureAverage; // TODO: pretty dangerous.
			// vUpdateMeasurementHistory();
			// TODO: instead, append real val to an outlier array? or do nothing
				// if there are multiple in a row within the same range (what looks like an outlier is actually physical) we'll want to end up accepting them
	 			// loss of vacuum --> dramatic temperature change?	
		}

	}


	/** Compute the average of temperature measurements */
	Lfloat32 f32NUMERICAL_FLOAT_AVERAGE(void)
	{
		Lfloat32 f32TemperatureSum = 0;
		// sum the nums of the array
		for(Luint8 u8Counter; u8Counter < 10; u8Counter++)
		{
			Lfloat32 f32TemperatureSum += f32Last10Values[u8Counter];
		}

		// divide by array size (might be considered a magic number..) 
		Lfloat32 f32AverageTemperature = f32TemperatureSum / 10.0F; 
		f32Averages[pu8AverageCounter2] = f32AverageTemperature;
		
		pu8AverageCounter2 += 1;
		if(pu8AverageCounter2==64U)
		{
			pu8AverageCounter2 = 0;
		}		

		return f32AverageTemperature
	}


	/** Delete oldest measurement in the recent history array, add new. */
	void vUpdateMeasurementHistory(void)
	{
		// shift all data points down one index
		f32Last10Values[9] = f32Last10Values[8];
		f32Last10Values[8] = f32Last10Values[7];
		f32Last10Values[7] = f32Last10Values[6];
		f32Last10Values[6] = f32Last10Values[5];
		f32Last10Values[5] = f32Last10Values[4];
		f32Last10Values[4] = f32Last10Values[3];
		f32Last10Values[3] = f32Last10Values[2];
		f32Last10Values[2] = f32Last10Values[1];
		f32Last10Values[1] = f32Last10Values[0];
		// write the new data point to the first index
		f32Last10Values[0] = f32TemperatureResult;

	}


	/*******************************************************************************
	Unwritten Functions
	*******************************************************************************/

   	/** Read each of the 5 K calibration constants over i2c */
    Luint16[] u16TSYS01__Read_K_Values(void)
    {
    	// TODO: write to align with i2c code

    	Luint16 u16K[5];
    	u16K[0] = i2cRead(k0_ADR); // TODO: fake function
    	u16K[1] = i2cRead(k1_ADR);
    	u16K[2] = i2cRead(k2_ADR);
    	u16K[3] = i2cRead(k3_ADR);
    	u16K[4] = i2cRead(k4_ADR);

    	return u16K[5];
    }


   	/** to [ideally] be used for: read 16-bit k values, read 16-bit temperature result over i2c */
    Luint16 I2CRead(char ADR)
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

