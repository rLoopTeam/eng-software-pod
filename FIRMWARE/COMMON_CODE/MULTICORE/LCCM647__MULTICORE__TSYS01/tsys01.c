/* TODO:
 * i2c implementation
 * how to handle 10ms delay between ADC conversion and reading measurement
 * globals demand too much space?
 * doxygen compatible commenting
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
	Lfloat32 f32TemperatureResult=0;
	Lfloat32 f32ADCTemperatureResult=0;
	Lfloat32 f32Coeffs[5];
	Luint8 u8ConvertingFlag;

	/** Read calibration constants, compute conversion eqn coefficients */
	void vTSYS01__Init(void)
	{
	    u16KValues = u16TSYS01__Read_K_Values()

		// Use K values to compute the full coefficient for each polynomial term,   
	    // 	these coeffs are static, so this doesn't have to be done in __Process()
		f32Coeffs[4] = (-2) * u16KValues[4] * pow(10, -21), //TODO: fix syntax
		f32Coeffs[3] = 4 * u16KValues[3] * pow(10, -16),
		f32Coeffs[2] = -2 * u16KValues[2] * pow(10, -11),
		f32Coeffs[1] = 1 * u16KValues[1] * pow(10, -6),
		f32Coeffs[0] = -1.5 * u16KValues[0] * pow(10, -2)

	}// end vTSYS01__Init()


	/** Read 16-bit temperature measurement, convert units to Celsius using eqn from datasheet */
	void vTSYS01__Process(void)
	{
		// Tell TSYS01 to begin analog to digital conversion (10ms max duration)
		// vI2CWrite(START_ADC_TEMPERATURE_CONVERSION); // TODO: use a real function! 
			// is any return sent as acknowledgment of the command?

		// Set flag to show conversion has begun
		u8ConvertingFlag = 1;

		f32ADCTemperatureResult = F_TSYS01_Read_ADC_Temperature_Result();

		// Reset flag now that measurement has been read
		u8ConvertingFlag = 0;

		// Compute temperature polynomial terms individually then sum
		Lfloat32 Term4 = f32Coeffs[4] * pow(f32ADCTemperatureResult, 4);
		Lfloat32 Term3 = f32Coeffs[3] * pow(f32ADCTemperatureResult, 3);
		Lfloat32 Term2 = f32Coeffs[2] * pow(f32ADCTemperatureResult, 2);
		Lfloat32 Term1 = f32Coeffs[1] * f32ADCTemperatureResult;
		Lfloat32 Term0 = f32Coeffs[0];
		f32TemperatureResult = Term4 + Term3 + Term2 + Term1 + Term0; // Celius

	}// end vTSYS01__Process()


	/** Most recent measurement made global for external use */
	Lfloat32 f32TSYS01__Read_Temperature_Result(void)
	{
		return f32TemperatureResult;
	}


	/*******************************************************************************
	Unwritten Functions
	*******************************************************************************/


   	// Read each of the 5 K calibration constants over i2c
    Luint16[] u16TSYS01__Read_K_Values(void)
    {
    	// write to align with i2c code

    	Luint16 u16K[5];
    	u16K[0] = i2cRead(k0_ADR);
    	u16K[1] = i2cRead(k1_ADR);
    	u16K[2] = i2cRead(k2_ADR);
    	u16K[3] = i2cRead(k3_ADR);
    	u16K[4] = i2cRead(k4_ADR);

    	return u16K[5];
    }


    type? I2CRead(char ADR)
    {
    	// write to align with i2c code	

    	//to [ideally] be used for: 16-bit k values, 32-bit temperature result

    }


    void vI2CWrite(char ADR)
    {
    	// write to align with i2c code

    }


	Lfloat32 f32TSYS01__Read_ADC_Temperature_Result(void)
	{
		// write to align with i2c code
		return f32ADCTemperatureResult;
	}


#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
	#error
#endif

