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

/** Init */
void vMS5607__Init(void)
{
	//init structure
	sMS5607.eState = MS5607_STATE__INIT_DEVICE;
}

void vMS5607__Process(void)
{

	Lint16 s16Return;


    //TODO State Machines

	switch(sMS5607.eState)
	{
		case MS5607_STATE__IDLE:
			//do nothing,
			break;
		case MS5607_STATE__INIT_DEVICE:

			//TODO set I2C Address??
			//reset the device
			//vMS5607__Reset();
			s16Return = s16MS5607_I2C__TxCommand(C_LOCALDEF__LCCM648__BUS_ADDX, MS5607_CMD__RESET); 
    		//TODO define C_LOCALDEF__LCCM648__BUS_ADDX under FIRMWARE/LFW513__RLOOP__POWER_NODE/SOURCE/MAIN/localdef.h
			//The Reset sequence shall be be sent once after power-on to make sure theat the calibration PROM gets loaded into the internal register
			
			//TODO error check
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
			vMS5607__GetCalibrationData();
			//TODO error check

			sMS5607.eState = MS5607_STATE__WAITING;
			//TODO error check

			break;
		case MS5607_STATE__WAITING:
			//TODO start conversion

			break;

		case MS5607_STATE__BEGIN_SAMPLE:

			break;

		case MS5607_STATE__WAIT_LOOPS:

			break;

		case MS5607_STATE__READ_ADC:

			break;

		case MS5607_STATE__COMPUTE:

			break;

		case MS5607_STATE__INTERRUPT:

			break;

		case MS5607_STATE__ERROR:

			break;
	}

}

/** Issue#22: Read calibration data off the device */
void vMS5607__GetCalibrationData(void)
{
    sMS5607.sCALIBRATION.u16C1 = uMS5607__Read16(MS5607_CMD__PROM_READ_1);
    sMS5607.sCALIBRATION.u16C2 = uMS5607__Read16(MS5607_CMD__PROM_READ_2);
    sMS5607.sCALIBRATION.u16C3 = uMS5607__Read16(MS5607_CMD__PROM_READ_3);
    sMS5607.sCALIBRATION.u16C4 = uMS5607__Read16(MS5607_CMD__PROM_READ_4);
    sMS5607.sCALIBRATION.u16C5 = uMS5607__Read16(MS5607_CMD__PROM_READ_5);
    sMS5607.sCALIBRATION.u16C6 = uMS5607__Read16(MS5607_CMD__PROM_READ_6);
    //TODO Check CRC is valid?
}

/** Read Digital Temperature Value D2 */
void vMS5607__ReadTemperature(void)
{
	sMS5607.sTEMP.u32D2 = uMS5607__Read24(MS5607_CMD__ADC_READ);
}

/** Read Digital Pressure Value D1 */
void vMS5607__ReadPressure(void)
{
	sMS5607.sPRESSURE.u32D1 = uMS5607__Read24(MS5607_CMD__ADC_READ);
}

/** Return the compensated temperature as a floating point value in °C */
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
void vMS5607__StartTemperatureConversion(void)
{
    vMS5607__Write8(MS5607_TEMPERATURE_OSR);
}

/** Start a pressure conversion with the defined OSR */
void vMS5607__StartPressureConversion(void)
{
    vMS5607__Write8(MS5607_PRESSURE_OSR);
}

/** Calculate Temperature */
void vMS5607__CalculateTemperature(void)
{
	// Difference between actual and reference temperature
	sMS5607.sTEMP.s32dT = (Lint32)sMS5607.sTEMP.u32D2 - ((Lint32)sMS5607.sCALIBRATION.u16C5 * f32NUMERICAL__Power(2, 8));
	// Actual temperature (-40 unsigned long long 85°C with 0.01°C resolution)
	sMS5607.sTEMP.s32TEMP = 2000 + ((sMS5607.sTEMP.s32dT * (Lint64)sMS5607.sCALIBRATION.u16C6) / f32NUMERICAL__Power(2, 23));
}

/** Calculate Temperature Compensated Pressure */
void vMS5607__CalculateTempCompensatedPressure(void)
{
	// Offset at actual temperature
	sMS5607.sPRESSURE.s64OFF = ((Lint64)sMS5607.sCALIBRATION.u16C2 * f32NUMERICAL__Power(2, 17)) + (((Lint64)sMS5607.sCALIBRATION.u16C4 * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 6));
	// Sensitivity at actual temperature
	sMS5607.sPRESSURE.s64SENS = ((Lint64)sMS5607.sCALIBRATION.u16C1 * f32NUMERICAL__Power(2, 16)) + (((Lint64)sMS5607.sCALIBRATION.u16C3 * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 7));
	// Temperature compensated pressure (10 to 1200mbar with 0.01mbar resolution)
	sMS5607.sPRESSURE.s32P = (Lint32)(((sMS5607.sPRESSURE.u32D1 * sMS5607.sPRESSURE.s64SENS) / f32NUMERICAL__Power(2, 21)) - sMS5607.sPRESSURE.s64OFF) / f32NUMERICAL__Power(2, 15);
}

/** Second Order Temperature Compensation */
void vMS5607__compensateSecondOrder(void)
{
    Lint32 T2 = 0;
    Lint64 OFF2 = 0;
    Lint64 SENS2 = 0;

    // Low Temperature
    if (sMS5607.sTEMP.s32TEMP < 2000){
        T2 = (Lint32) ((sMS5607.sTEMP.s32dT * sMS5607.sTEMP.s32dT) / f32NUMERICAL__Power(2, 31));                       // T2 = dT^2 / 2^31
        OFF2 = 61 * (Lint64) ((sMS5607.sTEMP.s32TEMP - 2000)*(sMS5607.sTEMP.s32TEMP - 2000)) / f32NUMERICAL__Power(2, 4);       // OFF2 = 61 * (TEMP-2000)^2 / 2^4
        SENS2 = 2 * (Lint64) ((sMS5607.sTEMP.s32TEMP - 2000)*(sMS5607.sTEMP.s32TEMP - 2000));            // SENS2 = 2 * (TEMP-2000)^2

        // Very Low Temperature
        if (sMS5607.sTEMP.s32TEMP < -1500) {
            OFF2 += 15 * (sMS5607.sTEMP.s32TEMP + 1500)*(sMS5607.sTEMP.s32TEMP + 1500);       // OFF2 = OFF2 + 15 * (TEMP + 1500)^2
            SENS2 += 8 * (sMS5607.sTEMP.s32TEMP + 1500)*(sMS5607.sTEMP.s32TEMP + 1500);       // SENS2 = SENS2 + 8 * (TEMP + 1500)^2
        }
        sMS5607.sTEMP.s32TEMP = sMS5607.sTEMP.s32TEMP - T2;
        sMS5607.sPRESSURE.s64OFF = sMS5607.sPRESSURE.s64OFF - OFF2;
        sMS5607.sPRESSURE.s64SENS = sMS5607.sPRESSURE.s64SENS - SENS2;
    }
}

/* Write reset cmd to the MS5607 pressure sensor*/
void vMS5607__Reset(void)
{
    vMS5607__Write8(MS5607_CMD__RESET);
}


//TODO delete I2C functions below
/***************************************************************************
* i2c Communcation Functions
***************************************************************************/
/** Read an 24-bit value from the device*/
Luint32 uMS5607__Read24(Luint8 value)
{
    //TODO Reference rm4_i2c__user.c or rm4_i2c.c
    return; //something
}

/** Read an 16-bit value from the device*/
Luint16 uMS5607__Read16(Luint8 value)
{
    //TODO Reference rm4_i2c__user.c or rm4_i2c.c
    return; //something
}

/** Write an 8-bit value to the device */
void vMS5607__Write8(Luint8 value)
{
    //TODO Reference rm4_i2c__user.c or rm4_i2c.c
}

#endif //#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE
	#error
#endif

