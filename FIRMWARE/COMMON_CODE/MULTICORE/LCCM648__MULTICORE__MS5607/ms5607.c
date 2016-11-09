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

extern struct _strMS5607 sMS5607;

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
	sMS5607.u32AverageResult_Div256Temperature = 0U;
	sMS5607.u32AverageResult_Div256Pressure = 0U;
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
	Luint8 u8crc4read;


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
				u8crc4read = uMS5607__getLSB4Bits(sMS5607.u16Coefficients[7]);

				if (u8crc4Result == u8crc4read)
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

			break;
		case MS5607_STATE__WAITING:
			//Nothing

			break;

	    case MS5607_STATE__BEGIN_SAMPLE_TEMPERATURE:
			//Start conversion here
	    	s16Return = s16MS5607__StartTemperatureConversion();

	    	if(s16Return >= 0)
			{
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
					sMS5607.u32LastResultTemperature = 8077636;
				#endif
				//add to filter
				sMS5607.u32AverageResultTemperature = u32NUMERICAL_FILTERING__Add_U32(sMS5607.u32LastResultTemperature,
																		&sMS5607.u16AverageCounterTemperature,
																		C_MS5607__MAX_FILTER_SAMPLES,
																		&sMS5607.u32AverageArrayTemperature[0]);
				#if C_LOCALDEF__LCCM648__ENABLE_DS_VALUES == 1U
					sMS5607.u32AverageResultTemperature = 8077636;
				#endif

				//generate the DIV256 option
				sMS5607.u32AverageResult_Div256Temperature = sMS5607.u32AverageResultTemperature >> 8U;

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
			// Read ADC Preassure
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

				//generate the DIV256 option
				sMS5607.u32AverageResult_Div256Pressure = sMS5607.u32AverageResultPressure >> 8U;

				//change state
				sMS5607.eState = MS5607_STATE__COMPUTE;
			}
			else
			{
				//error has occurred
				sMS5607.eState = MS5607_STATE__ERROR;
			}


<<<<<<< HEAD
=======
			sMS5607.eState = MS5607_STATE__COMPUTE;
>>>>>>> Fix some syntax errors
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

/** Read each of coefficients over i2c */
Lint16 s16MS5607__GetCalibrationContants(Luint16 *pu16Values)
{
	Lint16 s16Return;
	Luint16 * pu16Temp;

	pu16Temp = &pu16Values[0];
	s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_0, pu16Temp);
	if(s16Return >= 0)
	{
		pu16Temp = &pu16Values[1];
		s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_1, pu16Temp);
		if(s16Return >= 0)
		{
			pu16Temp = &pu16Values[2];
			s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_2, pu16Temp);
			if(s16Return >= 0)
			{
				pu16Temp = &pu16Values[3];
				s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_3, pu16Temp);
				if(s16Return >= 0)
				{
					pu16Temp = &pu16Values[4];
					s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_4, pu16Temp);
					if(s16Return >= 0)
					{
						pu16Temp = &pu16Values[5];
						s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_5, pu16Temp);
						if(s16Return >= 0)
						{
							pu16Temp = &pu16Values[6];
							s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_6, pu16Temp);
							if(s16Return >= 0)
							{
								pu16Temp = &pu16Values[7];
								s16Return = s16MS5607_I2C__RxU16(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__PROM_READ_7, pu16Temp);


								//fall on
							}
							else
							{
								//fall on
							}

							//fall on
						}
						else
						{
							//fall on
						}

						//fall on
					}
					else
					{
						//fall on
					}

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
	return s16MS5607_I2C__TxCommand(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_TEMPERATURE_OSR);
}

/** Calculate Compensated Temperature */
void vMS5607__CalculateTemperature(void)
{
	// Difference between actual and reference temperature
	sMS5607.sTEMP.s32dT = (Lint32)sMS5607.u32AverageResult_Div256Temperature - ((Lint32)sMS5607.u16Coefficients[5] * f32NUMERICAL__Power(2, 8));
	// Actual temperature (-40 unsigned long long 85°C with 0.01°C resolution)
	sMS5607.sTEMP.s32TEMP = 2000 + ((sMS5607.sTEMP.s32dT * (Lint64)sMS5607.u16Coefficients[6]) / f32NUMERICAL__Power(2, 23));
}

/** Calculate Temperature Compensated Pressure */
void vMS5607__CalculateTempCompensatedPressure(void)
{
	// Offset at actual temperature
	sMS5607.sPRESSURE.s64OFF = ((Lint64)sMS5607.u16Coefficients[2] * f32NUMERICAL__Power(2, 17)) + (((Lint64)sMS5607.u16Coefficients[4] * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 6));
	// Sensitivity at actual temperature
	sMS5607.sPRESSURE.s64SENS = ((Lint64)sMS5607.u16Coefficients[1] * f32NUMERICAL__Power(2, 16)) + (((Lint64)sMS5607.u16Coefficients[3] * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 7));
	// Temperature compensated pressure (10 to 1200mbar with 0.01mbar resolution)
	sMS5607.sPRESSURE.s32P = (Lint32)(((sMS5607.u32AverageResult_Div256Pressure * sMS5607.sPRESSURE.s64SENS) / f32NUMERICAL__Power(2, 21)) - sMS5607.sPRESSURE.s64OFF) / f32NUMERICAL__Power(2, 15);
}

/** Second Order Temperature Compensation */
void vMS5607__compensateSecondOrder(void)
{
    Lint32 s32T2 = 0;
    Lint64 s32OFF2 = 0;
    Lint64 s64SENS2 = 0;

    // Low Temperature
    if (sMS5607.sTEMP.s32TEMP < 2000){
        s32T2 = (Lint32) ((sMS5607.sTEMP.s32dT * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 31));                       // T2 = dT^2 / 2^31
        s32OFF2 = 61 * (Lint64) ((sMS5607.sTEMP.s32TEMP - 2000)*(sMS5607.sTEMP.s32TEMP - 2000)) / f32NUMERICAL__Power(2, 4);       // OFF2 = 61 * (TEMP-2000)^2 / 2^4
        s64SENS2 = 2 * (Lint64) ((sMS5607.sTEMP.s32TEMP - 2000)*(sMS5607.sTEMP.s32TEMP - 2000));            // SENS2 = 2 * (TEMP-2000)^2

        // Very Low Temperature
        if (sMS5607.sTEMP.s32TEMP < -1500) {
            s32OFF2 += 15 * (sMS5607.sTEMP.s32TEMP + 1500)*(sMS5607.sTEMP.s32TEMP + 1500);       // OFF2 = OFF2 + 15 * (TEMP + 1500)^2
            s64SENS2 += 8 * (sMS5607.sTEMP.s32TEMP + 1500)*(sMS5607.sTEMP.s32TEMP + 1500);       // SENS2 = SENS2 + 8 * (TEMP + 1500)^2
        }
        sMS5607.sTEMP.s32TEMP = sMS5607.sTEMP.s32TEMP - s32T2;
        sMS5607.sPRESSURE.s64OFF = sMS5607.sPRESSURE.s64OFF - s32OFF2;
        sMS5607.sPRESSURE.s64SENS = sMS5607.sPRESSURE.s64SENS - s64SENS2;
    }
}

//********************************************************
//! @brief calculate the CRC code for details look into CRC CODE NOTES
//!
//! @return crc code
// http://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=AN520_C-code_example_for_MS56xx&DocType=SS&DocLang=EN
// Code from TE AN520
//********************************************************
Luint8 u8MS5607__CRC4(Luint32 * pu32Coefficients)
{
	Luint32 u32count; // simple counter
	Luint32 u32n_rem; // crc reminder
	Luint32 u32crc_read; // original value of the crc
	Luint8 u8n_bit;

	u32n_rem = 0x00;

	//save read CRC
	u32crc_read = pu32Coefficients[7];

	//CRC byte is replaced by 0
	u32Coefficients[7] = (0xFF00 & (pu32Coefficients[7]));

	// operation is performed on bytes
	for(u32count = 0; u32count < 16; u32count++)
	{
		// choose LSB or MSB
		if((u32count % 2U) == 1U)
		{
			u32n_rem ^= (Luint16) ((pu32Coefficients[u32count>>1]) & 0x00FF);
		}
		else
		{
			u32n_rem ^= (Luint16) (pu32Coefficients[u32count>>1]>>8);
		}
		for (u8n_bit = 8; u8n_bit > 0; u8n_bit--)
		{
			if (u32n_rem & (0x8000))
			{
				u32n_rem = (u32n_rem << 1) ^ 0x3000;
			}
			else
			{
				u32n_rem = (u32n_rem << 1);
			}
		}
	}
	u32n_rem= (0x000F & (u32n_rem >> 12)); // // final 4-bit reminder is CRC code
	u32Coefficients[7]=u32crc_read; // restore the crc_read to its original place
	return (u32n_rem ^ 0x00);
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

