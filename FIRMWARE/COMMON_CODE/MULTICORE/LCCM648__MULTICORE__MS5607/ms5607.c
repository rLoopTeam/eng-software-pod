/**
 * @file        ms5607.c
 * @brief       Barometric Pressure Sensor, with stainless steel cap
 * @author      Edward Chan (40Chans) [Sftw, HR], Mila Antonova (scrappymacgyver) [Ctrl]
 * @copyright   rLoop Inc.
 * @st_file     
 *
 */

#include "ms5607.h"
#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U

struct _strMS5607 sMS5607;

//locals
Lint16 s16MS5607__GetCalibrationContants(Luint16 *pu16Values);

/** Init */
void vMS5607__Init(void)
{
	Luint8 u8Counter;

	//init structure
	sMS5607.eState = MS5607_STATE__INIT_DEVICE;
	sMS5607.u32LoopCounter = 0U;
	sMS5607.u32AverageResultTemperature = 0U;
	sMS5607.u32AverageResultPressure = 0U;
	sMS5607.u16AverageCounterTemperature = 0U;
	sMS5607.u16AverageCounterPressure = 0U;

	sMS5607.sTEMP.s32TEMP = 90.0F;    // MILA&ED: this needs to be confirmed
	sMS5607.sPRESSURE.s32P = 1300.0F; // MILA&ED: this needs to be confirmed

	//clear the average
	for(u8Counter = 0U; u8Counter < C_MS5607__MAX_FILTER_SAMPLES; u8Counter++)
	{
		sMS5607.u32AverageArrayTemperature[u8Counter] = 0U;
		sMS5607.u32AverageArrayPressure[u8Counter] = 0U;

	}




}

void vMS5607__Process(void)
{
	Lint16 s16Return;
	Luint8 u8crc4Result;
	Luint8 u8crc4Read;

	switch(sMS5607.eState)
	{
		case MS5607_STATE__IDLE:
			//do nothing,
			break;

		case MS5607_STATE__INIT_DEVICE:
			//reset the device
			s16Return = s16MS5607_I2C__TxCommand(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__RESET);
			//The Reset sequence shall be be sent once after power-on to make sure theat the calibration PROM gets loaded into the internal register

			if(s16Return >= 0)
			{
				//success
				sMS5607.eState = MS5607_STATE__READ_CALIBRATION;
			}
			else 
			{
				//read error, handle state.
				sMS5607.eState = MS5607_STATE__ERROR;
			}

			break;

		case MS5607_STATE__READ_CALIBRATION:
			s16Return = s16MS5607__GetCalibrationContants(&sMS5607.u16Coefficients[0]);

			if(s16Return >= 0)
			{
				//crc check
				u8crc4Result = uMS5607__getLSB4Bits(u8MS5607__CRC4(sMS5607.u16Coefficients));
				u8crc4Read = uMS5607__getLSB4Bits(sMS5607.u16Coefficients[7]);

				if (u8crc4Result == u8crc4Read)
				{
					// success
					sMS5607.eState = MS5607_STATE__BEGIN_SAMPLE_TEMPERATURE; //QUESTION: DO WE NEED MS5607_STATE__WAITING?
				}
				else
				{
					// handle error
					sMS5607.eState = MS5607_STATE__ERROR;
				}
			}
			else
			{
				//read error, handle state.
				sMS5607.eState = MS5607_STATE__ERROR;
			}

			#if C_LOCALDEF__LCCM648__ENABLE_DS_VALUES == 1U
				// Coefficient values copied from the MS5607 data sheet (ENG_DS_MS5607-02BA03_B.pdf; page 8)
				sMS5607.u16Coefficients[1] = 46372;
				sMS5607.u16Coefficients[2] = 43981;
				sMS5607.u16Coefficients[3] = 29059;
				sMS5607.u16Coefficients[4] = 27842;
				sMS5607.u16Coefficients[5] = 31553;
				sMS5607.u16Coefficients[6] = 28165;
			#endif

			break;
		case MS5607_STATE__WAITING:
			//Nothing

			break;

	    case MS5607_STATE__BEGIN_SAMPLE_TEMPERATURE:
			//Start conversion here
	    	s16Return = s16MS5607__StartTemperatureConversion();

	    	if(s16Return >= 0)
			{
	    		//clear the counter
	    		sMS5607.u32LoopCounter = 0U;

				//success
				sMS5607.eState = MS5607_STATE__WAIT_LOOPS_TEMPERATURE;
			}
			else
			{
				//read error, handle state.
				sMS5607.eState = MS5607_STATE__ERROR;
			}
			break;

		case MS5607_STATE__WAIT_LOOPS_TEMPERATURE:
			//TODO add delay here for conversion then
			//After the conversion is over, move to next stage to read ADC
			//todo, change to constant
			if(sMS5607.u32LoopCounter > C_LOCALDEF__LCCM648__NUM_CONVERSION_LOOPS)
			{
				//move on to read the ADC
				sMS5607.eState = MS5607_STATE__READ_ADC_TEMPERATURE;

			}
			else
			{
				sMS5607.u32LoopCounter += 1;
				//stay in state
			}
			break;

		case MS5607_STATE__READ_ADC_TEMPERATURE:
			//Read ADC Temperature
			s16Return = s16MS5607_I2C__RxU24(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__ADC_READ, &sMS5607.u32LastResultTemperature);
			if(s16Return >= 0)
			{

				#if C_LOCALDEF__LCCM648__ENABLE_DS_VALUES == 1U
					//sMS5607.u32LastResultTemperature = 8077636;
					//sMS5607.u32LastResultTemperature = 8077036; //Below 20 (at 19C)
					sMS5607.u32LastResultTemperature = 7000000; //Below -15 (at -16C)
				#endif
				//add to filter
				sMS5607.u32AverageResultTemperature = u32NUMERICAL_FILTERING__Add_U32(sMS5607.u32LastResultTemperature,
																		&sMS5607.u16AverageCounterTemperature,
																		C_MS5607__MAX_FILTER_SAMPLES,
																		&sMS5607.u32AverageArrayTemperature[0]);
				#if C_LOCALDEF__LCCM648__ENABLE_DS_VALUES == 1U
					//sMS5607.u32AverageResultTemperature = 8077636;
					//sMS5607.u32AverageResultTemperature = 8077036; //Below 20 (at 19C)
					sMS5607.u32AverageResultTemperature = 7000000; //Below -15 (at -16C)
				#endif

				//change state
				sMS5607.eState = MS5607_STATE__BEGIN_SAMPLE_PRESSURE;
			}
			else
			{
				//error has occurred
				sMS5607.eState = MS5607_STATE__ERROR;
			}
			break;

		case MS5607_STATE__BEGIN_SAMPLE_PRESSURE:
			//Start conversion here
			s16Return = s16MS5607__StartPressureConversion();

			if(s16Return >= 0)
			{
				//clear the counter
				sMS5607.u32LoopCounter = 0U;

				//success
				sMS5607.eState = MS5607_STATE__WAIT_LOOPS_PRESSURE;
			}
			else
			{
				//read error, handle state.
				sMS5607.eState = MS5607_STATE__ERROR;
			}
			break;

		case MS5607_STATE__WAIT_LOOPS_PRESSURE:
				//After the conversion is over, move to next stage to read ADC
				if(sMS5607.u32LoopCounter > C_LOCALDEF__LCCM648__NUM_CONVERSION_LOOPS)
				{
					//move on to read the ADC
					sMS5607.eState = MS5607_STATE__READ_ADC_PRESSURE;

				}
				else
				{
					sMS5607.u32LoopCounter += 1;
					//stay in state
				}
			break;

		case MS5607_STATE__READ_ADC_PRESSURE:
			// Read ADC Preassure (reading the D2 value from the MS5607).
			s16Return = s16MS5607_I2C__RxU24(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__ADC_READ, &sMS5607.u32LastResultPressure);

			if(s16Return >= 0)
			{

				#if C_LOCALDEF__LCCM648__ENABLE_DS_VALUES == 1U
					sMS5607.u32LastResultPressure = 6465444;
				#endif
				//add to filter
				sMS5607.u32AverageResultPressure = u32NUMERICAL_FILTERING__Add_U32(sMS5607.u32LastResultPressure,
																		&sMS5607.u16AverageCounterPressure,
																		C_MS5607__MAX_FILTER_SAMPLES,
																		&sMS5607.u32AverageArrayPressure[0]);
				#if C_LOCALDEF__LCCM648__ENABLE_DS_VALUES == 1U
					sMS5607.u32AverageResultPressure = 6465444;
				#endif

				//change state
				sMS5607.eState = MS5607_STATE__COMPUTE;
			}
			else
			{
				//error has occurred
				sMS5607.eState = MS5607_STATE__ERROR;
			}
			break;

		case MS5607_STATE__COMPUTE:
            // Compute temperature first
			vMS5607__CalculateTemperature();

			if(sMS5607.sTEMP.s32TEMP < 2000)
			{
				vMS5607__compensateSecondOrder();
			}

			vMS5607__CalculateTempCompensatedPressure();

			sMS5607.eState = MS5607_STATE__BEGIN_SAMPLE_TEMPERATURE; //MILA&ED: SHOULD THS BE ..._STATE_IDLE
			break;

		case MS5607_STATE__INTERRUPT:

			break;

		case MS5607_STATE__ERROR:

			break;
	}

}

Luint8 u8MS5607__Get_IsFault(void)
{
	Luint8 u8Return;

	if(sMS5607.eState == MS5607_STATE__ERROR)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;

}

/** Read each of coefficients over i2c */
Lint16 s16MS5607__GetCalibrationContants(Luint16 *pu16Values)
{
	Lint16 s16Return; // I2C read return status
	Luint8 u8CoefficientIndex; // Factor used to move the address ahead in the loop.
	Luint8 u8CoefficientStartingAddress = MS5607_CMD__PROM_READ;

	// Loop through the coefficients from 0 to 8.
	for (u8CoefficientIndex = 0; u8CoefficientIndex < 8; u8CoefficientIndex++)
	{
		vRM4_DELAYS__Delay_mS(10U);
		// We have to make sure we're increasing the address by 2,
		// since we're reading two bytes at a time (16-bit words).
		s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, (E_MS5607_CMD_T)(u8CoefficientStartingAddress + (2 * u8CoefficientIndex)), &pu16Values[u8CoefficientIndex]);
		if (s16Return != 0)
		{
			// Failed reading.
			break;
		}
	}

	// Return with the status of the I2C read.
	return s16Return;
}

/** Read Digital Temperature Value D2 */
//void vMS5607__ReadTemperature(void)
//{
//	//TODO need a read24 from ms5607_i2c.c
//	sMS5607.sTEMP.u32D2 = uMS5607__Read24(MS5607_CMD__ADC_READ);
//}

/** Read Digital Pressure Value D1 */
//void vMS5607__ReadPressure(void)
//{
//	//TODO need a read24 from ms5607_i2c.c
//	sMS5607.sPRESSURE.u32D1 = uMS5607__Read24(MS5607_CMD__ADC_READ);
//}

/** Return the compensated temperature as a floating point value in C */
Lint32 sMS5607__GetTemperature(void)
{
	return sMS5607.sTEMP.s32TEMP;
}

/** Return the compensated pressure as a floating point value, in mbar */
Lint32 sMS5607__GetPressure(void)
{
	return sMS5607.sPRESSURE.s32P;
}

/** Start a temperature conversion with the defined OSR */
Lint16 s16MS5607__StartTemperatureConversion(void)
{
	//return with the status of the I2C read
	return s16MS5607_I2C__TxCommand(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_TEMPERATURE_OSR);
}

/** Start a pressure conversion with the defined OSR */
Lint16 s16MS5607__StartPressureConversion(void)
{
	//return with the status of the I2C read
	return s16MS5607_I2C__TxCommand(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_PRESSURE_OSR);
}

/** Calculate Compensated Temperature */
void vMS5607__CalculateTemperature(void)
{
	// Difference between actual and reference temperature
	sMS5607.sTEMP.s32dT = (Lint32)sMS5607.u32AverageResultTemperature - ((Lint32)sMS5607.u16Coefficients[5] * f32NUMERICAL__Power(2, 8));

	// Actual temperature (-40 unsigned long long 85C with 0.01C resolution)
	sMS5607.sTEMP.s32TEMP = 2000 + ((sMS5607.sTEMP.s32dT * (Lint64)sMS5607.u16Coefficients[6]) / f32NUMERICAL__Power(2, 23));
}

/** Calculate Temperature Compensated Pressure */
void vMS5607__CalculateTempCompensatedPressure(void)
{
	Lfloat64 f64TempD1Sens = 0;
	Lfloat64 f64TempD1SensDiv2p21 = 0;
	Lfloat64 f64TempD1SensDiv2p21MinusOffset = 0;
	Lfloat64 f64TempD1SensDiv2p21MinusOffsetDiv2p15 = 0;
	// Offset at actual temperature
	sMS5607.sPRESSURE.s64OFF = ((Lint64)sMS5607.u16Coefficients[2] * f32NUMERICAL__Power(2, 17)) + (((Lint64)sMS5607.u16Coefficients[4] * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 6));
	// Sensitivity at actual temperature
	sMS5607.sPRESSURE.s64SENS = ((Lint64)sMS5607.u16Coefficients[1] * f32NUMERICAL__Power(2, 16)) + (((Lint64)sMS5607.u16Coefficients[3] * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 7));

	// Second Order Temperature Compensation
	sMS5607.sPRESSURE.s64OFF = sMS5607.sPRESSURE.s64OFF - (Lint64) sMS5607.sSECONDORDER.s32OFF2;
	sMS5607.sPRESSURE.s64SENS = sMS5607.sPRESSURE.s64SENS - sMS5607.sSECONDORDER.s64SENS2;

	// Temperature compensated pressure (10 to 1200mbar with 0.01mbar resolution)
	f64TempD1Sens = sMS5607.u32AverageResultPressure * sMS5607.sPRESSURE.s64SENS;
	f64TempD1SensDiv2p21 = f64TempD1Sens / f64NUMERICAL__Power(2, 21);
	f64TempD1SensDiv2p21MinusOffset = f64TempD1SensDiv2p21 - sMS5607.sPRESSURE.s64OFF;
	f64TempD1SensDiv2p21MinusOffsetDiv2p15 =  f64TempD1SensDiv2p21MinusOffset / f64NUMERICAL__Power(2, 15);
	sMS5607.sPRESSURE.s32P = (Lint32)f64TempD1SensDiv2p21MinusOffsetDiv2p15;
}

/** Second Order Temperature Compensation */
void vMS5607__compensateSecondOrder(void)
{
    Lint32 s32T2 = 0;
    Lint64 s32OFF2 = 0;
    Lint64 s64SENS2 = 0;

    // Low Temperature
    if (sMS5607.sTEMP.s32TEMP < 2000)
    {
    	// T2 = dT^2 / 2^31
    	Lint64 s64Temp = (Lint64) sMS5607.sTEMP.s32dT * sMS5607.sTEMP.s32dT;
        s32T2 = (Lint32) ( s64Temp / f64NUMERICAL__Power(2, 31));

        // OFF2 = 61 * (TEMP-2000)^2 / 2^4
        s32OFF2 = 61 * (Lint64) ((sMS5607.sTEMP.s32TEMP - 2000)*(sMS5607.sTEMP.s32TEMP - 2000)) / f32NUMERICAL__Power(2, 4);

        // SENS2 = 2 * (TEMP-2000)^2
        s64SENS2 = 2 * (Lint64) ((sMS5607.sTEMP.s32TEMP - 2000)*(sMS5607.sTEMP.s32TEMP - 2000));

        // Very Low Temperature
        if (sMS5607.sTEMP.s32TEMP < -1500)
        {
        	// OFF2 = OFF2 + 15 * (TEMP + 1500)^2
            s32OFF2 += 15 * (sMS5607.sTEMP.s32TEMP + 1500)*(sMS5607.sTEMP.s32TEMP + 1500);
            // SENS2 = SENS2 + 8 * (TEMP + 1500)^2
            s64SENS2 += 8 * (sMS5607.sTEMP.s32TEMP + 1500)*(sMS5607.sTEMP.s32TEMP + 1500);
        }
        sMS5607.sTEMP.s32TEMP = sMS5607.sTEMP.s32TEMP - s32T2;
        sMS5607.sSECONDORDER.s32OFF2 =  s32OFF2;
        sMS5607.sSECONDORDER.s64SENS2 = s64SENS2;
    }
}

//********************************************************
//! @brief calculate the CRC code for details look into CRC CODE NOTES
//!
//! @return crc code
// http://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=AN520_C-code_example_for_MS56xx&DocType=SS&DocLang=EN
// Code from TE AN520
//********************************************************
Luint8 u8MS5607__CRC4(Luint16 * pu16Coefficients)
{
	// simple counter
	Luint16 u16Count;
	 // crc reminder
	Luint16 u16Num_rem;
	// original value of the crc
	Luint16 u16CRC_Read;
	Luint8 u8n_bit;

	u16Num_rem = 0x00;

	//save read CRC
	u16CRC_Read = pu16Coefficients[7];

	//CRC byte is replaced by 0
	pu16Coefficients[7] = (0xFF00U & (pu16Coefficients[7]));

	// operation is performed on bytes
	for(u16Count = 0; u16Count < 16U; u16Count++)
	{
		// choose LSB or MSB
		if((u16Count % 2U) == 1U)
		{
			u16Num_rem ^= (Luint16) ((pu16Coefficients[u16Count>>1]) & 0x00FFU);
		}
		else
		{
			u16Num_rem ^= (Luint16) (pu16Coefficients[u16Count>>1]>>8);
		}
		for (u8n_bit = 8; u8n_bit > 0; u8n_bit--)
		{
			if (u16Num_rem & (0x8000U))
			{
				u16Num_rem = (u16Num_rem << 1) ^ 0x3000U;
			}
			else
			{
				u16Num_rem = (u16Num_rem << 1);
			}
		}
	}

	// final 4-bit reminder is CRC code
	u16Num_rem = (0x000F & (u16Num_rem >> 12));

	// restore the crc_read to its original place
	pu16Coefficients[7]=u16CRC_Read;

	//
	return (u16Num_rem ^ 0x00);
} 

Luint8 uMS5607__getLSB4Bits(Luint32 u32LastCoefficient)
{
	return u32LastCoefficient & 0x000F;
}

#endif //#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE
	#error
#endif
