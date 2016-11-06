/**
 * @file		TSYS01.H
 * @brief		TSYS01 Temp sensor driver
 * @author		Dean, Lachlan Grogan
 * @st_fileID	LCCM647R0.FILE.001
 */
#ifndef _TSYS01_H_
#define _TSYS01_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define C_TSYS01__MAX_FILTER_SAMPLES					(8U)


		/** enum type for tsys01 PROM addresses */
		typedef enum
		{
			TSYS01_REG__RESET = 0x1E,
			TSYS01_REG__START_ADC_TEMPERATURE_CONVERSION = 0x48,
			TSYS01_REG__READ_ADC_TEMPERATURE_RESULT = 0x00,
			TSYS01_REG__PROM_READ_ADDRESS_0 = 0xA0,
			TSYS01_REG__PROM_READ_ADDRESS_6 = 0xAC,
			TSYS01_REG__PROM_READ_ADDRESS_7 = 0xAE,

			TSYS01_REG__k4_ADR = 0xA2,
			TSYS01_REG__k3_ADR = 0xA4,
			TSYS01_REG__k2_ADR = 0xA6,
			TSYS01_REG__k1_ADR = 0xA8,
			TSYS01_REG__k0_ADR = 0xAA


		}E_TSYS01_REGS_T;


		/** State types for the TSYS01 state machine */
		typedef enum
		{

			/** do nothing*/
			TSYS01_STATE__IDLE = 0U,

			/** We are in an error condition */
			TSYS01_STATE__ERROR,

			/** init the device, force a reset */
			TSYS01_STATE__INIT_DEVICE,

			/** Read the constants from the device */
			TSYS01_STATE__READ_CONSTANTS,

			/** Issue the conversion command*/
			TSYS01_STATE__BEGIN_SAMPLE,

			/** Wait for a number of processing loops to expire */
			TSYS01_STATE__WAIT_LOOPS,

			/** Read the ADC */
			TSYS01_STATE__READ_ADC,

			/** Compute the result */
			TSYS01_STATE__COMPUTE,


		}E_TSYS01_STATES_T;


		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strTSYS01
		{

			/** the current state */
			E_TSYS01_STATES_T eState;

			/** the coeffs from the device */
			Lfloat32 f32Coeffs[5];

			/** counter the number of main program loops */
			Luint32 u32LoopCounter;

			/** Last sampled ADC result*/
			Luint32 u32LastResult;

			/** Last average result */
			Luint32 u32AverageResult;

			/** some reason the math requires div256 */
			Luint32 u32AverageResult_Div256;

			/** Count the averages */
			Luint16 u16AverageCounter;

			/** The averages */
			Luint32 u32AverageArray[C_TSYS01__MAX_FILTER_SAMPLES];

			/** The computed temp in deg C*/
			Lfloat32 f32TempDegC;

		};



		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vTSYS01__Init(void);
		void vTSYS01__Process(void);
		void vTSYS01__Enable(void);
		Lfloat32 f32TSYS01__Get_TempDegC(void);
		
		
		//I2C
		Lint16 s16TSYS01_I2C__TxCommand(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister);
		Lint16 s16TSYS01_I2C__TxU8(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint8 u8Byte);
		Lint16 s16TSYS01_I2C__RxU16(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint16 * pu16);
		Lint16 s16TSYS01_I2C__RxU24(Luint8 u8DeviceAddx, E_TSYS01_REGS_T eRegister, Luint32 *pu32);

	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_TSYS01_H_

