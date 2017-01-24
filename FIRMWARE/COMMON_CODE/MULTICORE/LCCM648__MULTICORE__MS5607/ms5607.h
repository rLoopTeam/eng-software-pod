/**
 * @file        ms5607.h
 * @brief       Barometric Pressure Sensor, with stainless steel cap
 * @author      Edward Chan (40Chans) [Sftw, HR], Mila Antonova (scrappymacgyver) [Ctrl]
 * @copyright   rLoop Inc.
 *
 */

/** Datasheet: 	MS5607 https://goo.gl/JNkGxE (version: 09/2015) 
 *  Milestone:  CTRL-44 MS5607 Pressure Sensor	 		
*/

#ifndef _MS5607_H_
#define _MS5607_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define MS5607_TEMPERATURE_OSR			MS5607_CMD__CONVERT_D2_OSR_4096
		#define MS5607_PRESSURE_OSR				MS5607_CMD__CONVERT_D1_OSR_4096
		#define C_MS5607__NUM_OF_COEFFICIENTS	(8U)
		#define C_MS5607__MAX_FILTER_SAMPLES    (1U)

		/** COMMANDS */
        typedef enum
        {
            MS5607_CMD__RESET = 0x1E,
			//D1 Digital Pressure Value
            MS5607_CMD__CONVERT_D1_OSR_256 = 0x40,
            MS5607_CMD__CONVERT_D1_OSR_512 = 0x42,
            MS5607_CMD__CONVERT_D1_OSR_1024 = 0x44,
            MS5607_CMD__CONVERT_D1_OSR_2048 = 0x46,
            MS5607_CMD__CONVERT_D1_OSR_4096 = 0x48,
			//D2 Digital Temp Value
            MS5607_CMD__CONVERT_D2_OSR_256 = 0x50,
            MS5607_CMD__CONVERT_D2_OSR_512 = 0x52,
            MS5607_CMD__CONVERT_D2_OSR_1024 = 0x54,
            MS5607_CMD__CONVERT_D2_OSR_2048 = 0x56,
            MS5607_CMD__CONVERT_D2_OSR_4096 = 0x58,
            MS5607_CMD__ADC_READ = 0x00,
            MS5607_CMD__PROM_READ = 0xA0, // Calibration data (from 0xA0 to 0xAE)
        }E_MS5607_CMD_T;

        /** State types for the MS5607 state machine */
        typedef enum
        {
        	MS5607_STATE__IDLE = 0U,
        	MS5607_STATE__ERROR,
        	MS5607_STATE__INIT_DEVICE,
        	MS5607_STATE__READ_CALIBRATION,
        	MS5607_STATE__WAITING,
			MS5607_STATE__BEGIN_SAMPLE_TEMPERATURE,
			MS5607_STATE__BEGIN_SAMPLE_PRESSURE,
			MS5607_STATE__WAIT_LOOPS_TEMPERATURE,
			MS5607_STATE__WAIT_LOOPS_PRESSURE,
        	MS5607_STATE__READ_ADC_TEMPERATURE,
			MS5607_STATE__READ_ADC_PRESSURE,
        	MS5607_STATE__COMPUTE,
        	MS5607_STATE__INTERRUPT,
        }E_MS5607_STATE_T;

		/*******************************************************************************
		Structures
		*******************************************************************************/

        /*** The temperature compensation values ***/
		struct _strTemperature
		{
			Lint32 s32dT;
			Lint32 s32TEMP;
		};

		/*** The pressure values ***/
		struct _strPressure
		{
			Lint64 s64OFF;
			Lint64 s64SENS;
			Lint32 s32P;
		};

		/*** The second order temperature compensation ***/
		struct _strSecondOrderCompensation
		{
			Lint32 s32OFF2;
			Lint64 s64SENS2;
		};

		/** Main MS5607 Structure */
		struct _strMS5607
		{
			E_MS5607_STATE_T eState;
			/**
			 *		C0 - Manufacturer Reserved
			 *		C1 - Pressure Sensitivity
			 *		C2 - Pressure Offset
			 *		C3 - Temperature coefficient of pressure sensitivity
			 *		C4 - Temperature coefficient of pressure offset
			 *		C5 - Reference temperature
			 *		C6 - Temperature coefficient of the temperature
			 *		C7 - CRC
			 * */
			Luint16 u16Coefficients[C_MS5607__NUM_OF_COEFFICIENTS];

			/** counter the number of main program loops */
			Luint32 u32LoopCounter;

			/** Last sampled temperature ADC result*/
			Luint32 u32LastResultTemperature;

			/** Last average temperature  result */
			Luint32 u32AverageResultTemperature;

			/** Count the averages */
			Luint16 u16AverageCounterTemperature;

			/** The averages */
			Luint32 u32AverageArrayTemperature[C_MS5607__MAX_FILTER_SAMPLES];

			/** Last sampled pressure ADC result*/
			Luint32 u32LastResultPressure;

			/** Last average pressure  result */
			Luint32 u32AverageResultPressure;

			/** Count the averages */
			Luint16 u16AverageCounterPressure;

			/** The averages */
			Luint32 u32AverageArrayPressure[C_MS5607__MAX_FILTER_SAMPLES];

			/** temperature values **/
			struct _strTemperature sTEMP;

			/** pressure values **/
			struct _strPressure sPRESSURE;

			/** second order temperature compensation **/
			struct _strSecondOrderCompensation sSECONDORDER;
		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
        void vMS5607__Init(void);
        void vMS5607__Process(void);
        Luint8 u8MS5607__Get_IsFault(void);

        void vMS5607__GetCalibrationData(void);

        void vMS5607__ReadTemperature(void);
        void vMS5607__ReadPressure(void);
        Lint32 sMS5607__GetTemperature(void);
        Lint32 sMS5607__GetPressure(void);
        Lint16 s16MS5607__StartTemperatureConversion(void);
        Lint16 s16MS5607__StartPressureConversion(void);
        void vMS5607__CalculateTemperature(void);
        void vMS5607__CalculateTempCompensatedPressure(void);
        void vMS5607__compensateSecondOrder(void);
        Luint8 u8MS5607__CRC4(Luint16 * pu16Coefficients);
        Luint8 uMS5607__getLSB4Bits(Luint32 u32LastCoefficient);


        //I2C
		Lint16 s16MS5607_I2C__TxCommand(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister);
		Lint16 s16MS5607_I2C__TxU8(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint8 u8Byte);
		Lint16 s16MS5607_I2C__RxU16(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint16 *pu16);
		Lint16 s16MS5607_I2C__RxU24(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint32 *pu32);

	#endif //#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_MS5607_H_
