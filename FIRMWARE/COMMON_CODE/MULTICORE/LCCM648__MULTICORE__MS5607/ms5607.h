/**
 * @file        ms5607.h
 * @brief       Barometric Pressure Sensor, with stainless steel cap
 * @author      Edward Chan (40Chans) [Sftw, HR], Mila Antonova (scrappymacgyver) [Ctrl]
 * @copyright   rLoop Inc.
 * @st_file     
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
		#define MS5607_NUM_OF_COEFFICIENTS		8U

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
            MS5607_CMD__PROM_READ_0 = 0xA0, //Manufacturer Reserved
            MS5607_CMD__PROM_READ_1 = 0xA2,
            MS5607_CMD__PROM_READ_2 = 0xA4,
            MS5607_CMD__PROM_READ_3 = 0xA6,
            MS5607_CMD__PROM_READ_4 = 0xA8,
            MS5607_CMD__PROM_READ_5 = 0xAA,
            MS5607_CMD__PROM_READ_6 = 0xAC,
            MS5607_CMD__PROM_READ_7 = 0xAE //CRC
        }E_MS5607_CMD_T;

        /** State types for the MS5607 state machine */
        typedef enum
        {
        	MS5607_STATE__IDLE = 0U,
        	MS5607_STATE__ERROR,
        	MS5607_STATE__INIT_DEVICE,
        	MS5607_STATE__READ_CALIBRATION,
        	MS5607_STATE__WAITING,
        	MS5607_STATE__BEGIN_SAMPLE,
        	MS5607_STATE__WAIT_LOOPS,
        	MS5607_STATE__READ_ADC,
        	MS5607_STATE__COMPUTE,
        	MS5607_STATE__INTERRUPT,
        }E_MS5607_STATE_T;
		/*******************************************************************************
		Structures
		*******************************************************************************/
		
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
			Luint16 u16Coefficients[MS5607_NUM_OF_COEFFICIENTS];
			/** counter the number of main program loops */
			Luint32 u32LoopCounter;


//MTODO: delete sCALIBRATION
//
//			struct
//			{
//				Luint16 u16Reserved = 0U;
//				Luint16 u16C1 = 0U;            // C1 - Pressure Sensitivity
//	            Luint16 u16C2 = 0U;            // C2 - Pressure Offset
//	            Luint16 u16C3 = 0U;            // C3 - Temperature coefficient of pressure sensitivity
//	            Luint16 u16C4 = 0U;            // C4 - Temperature coefficient of pressure offset
//	            Luint16 u16C5 = 0U;            // C5 - Reference temperature
//	            Luint16 u16C6 = 0U;            // C6 - Temperature coefficient of the temperature
//	            Luint16 u16CRC = 0U;
//	            //unsigned int 16, 16bit, 0-65535
//			}sCALIBRATION;

			struct
			{
				Lint32 s32dT = 0U;
				Lint32 s32TEMP = 0U;
				Luint32 u32D2 = 0U; //D2 Digital temperature value, type: unsigned int 32, size:24bit, 0-16777216 (min-max)
			}sTEMP;

			struct
			{
				Lint64 s64OFF = 0U;
				Lint64 s64SENS = 0U;
				Lint32 s32P = 0U;
				Luint32 u32D1 = 0U; //D1 Digital pressure value, type: unsigned int 32, size:24bit, 0-16777216 (min-max)
			}sPRESSURE;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
        void vMS5607__Init(void);
        void vMS5607__Process(void);

        void vMS5607__GetCalibrationData(void);

        void vMS5607__ReadTemperature(void);
        void vMS5607__ReadPressure(void);
        Luint32 sMS5607__GetTemperature(void);
        Luint32 sMS5607__GetPressure(void);
        void vMS5607__StartTemperatureConversion(void);
        void vMS5607__StartPressureConversion(void);
        void vMS5607__CalculateTemperature(void);
        void vMS5607__CalculateTempCompensatedPressure(void);
        void vMS5607__compensateSecondOrder(void);
        void vMS5607__Reset(void);
        Luint8 uMS5607__crc4(Luint32);


        Luint32 uMS5607__Read24(E_MS5607_CMD_T value);
        Luint16 vMS5607__Read16(E_MS5607_CMD_T value);
        void vMS5607__Write8(E_MS5607_CMD_T value);


        //I2C
		Lint16 s16MS5607_I2C__TxCommand(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister);
		Lint16 s16MS5607_I2C__TxU8(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint8 u8Byte);
		Lint16 s16MS5607_I2C__RxU16(Luint8 u8DeviceAddx, E_MS5607_CMD_T eRegister, Luint16 * pu16);

	#endif //#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_MS5607_H_

