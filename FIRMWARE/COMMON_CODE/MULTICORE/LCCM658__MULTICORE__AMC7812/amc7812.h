/**
 * @file		AMC7812.H
 * @brief		AMC7812 header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.001
 */

#ifndef _AMC7812_H_
#define _AMC7812_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/

		#define DAC_OUT_MAX_MVOLTS 		5000		// DAC output voltage limit
		#define DAC_OUT_MIN_MVOLTS 		0		// DAC output voltage limit
		#define NUM_DAC_CHANNELS		(12U)

		// AMC7812 external control pins driven by RM48 N2HET1 and GIOA pins

        #define RM48_N2HET1_PIN__AMC7812_HW_RESET      	(18U)

        #define RM48_N2HET1_PIN__AMC7812_CLR0      		(16U)
        #define RM48_N2HET1_PIN__AMC7812_CLR1      		(17U)
        #define RM48_N2HET1_PIN__AMC7812_CNVT      		(19U)
        #define RM48_GIOA_PIN__AMC7812_DAV      		(5U)

		// power-down register address; see AMC7812 datasheet, Table 10, p. 50

		#define AMC7812_REG_ADR__PWR_DWN				0x6B

		// GPIO pin address

		#define AMC7812_REG_ADR__GPIO 					0x4B

		// Device ID address

		#define AMC7812_REG_ADR__DEV_ID					0x6C

		#define NUM_GPIO_PINS							(8U)

		// Software reset register
		#define AMC7812_DAC_REG__SW_RESET				0x7C

		// Software clear register
		#define AMC7812_DAC_REG__SW_DAC_CLR				0x55

		// Hardware clear register
		#define AMC7812_DAC_REG__HW_DAC_CLR_EN_0		0x56
		#define AMC7812_DAC_REG__HW_DAC_CLR_EN_1		0x57

		// DAC configuration register, sets synchronous/asynchronous mode
		#define AMC7812_DAC_REG__CONFIG					0x58

		// DAC Gains register
		#define AMC7812_DAC_REG__GAINS					0x59

		// DAC Vref (millivolts)
		#define AMC7812_DAC_VREF						2500U

		// DAC gain flag: 0 for low gain (2*Vref), 1 for high gain (5*Vref)
		#define AMC7812_DAC_GAIN_FLAG					0U

		// DAC configuration mode flag: 0 for asynchronous, 1 for synchronous
		#define	AMC7812_DAC_CONFIG_MODE_FLAG			0U

		// enum type for  DAC 16-bit data registers
		typedef enum AMC7812_DAC_DATA_REG_ADDRESSES
		{
			AMC7812_REG_ADR__DAC_0_DATA = 0x33,		// address for AMC7812 DAC-0-OUT pin register (see Table 10, p. 60, AMC7812 Datasheet)
			AMC7812_REG_ADR__DAC_1_DATA = 0x34,
			AMC7812_REG_ADR__DAC_2_DATA = 0x35,
			AMC7812_REG_ADR__DAC_3_DATA = 0x36,
			AMC7812_REG_ADR__DAC_4_DATA = 0x37,
			AMC7812_REG_ADR__DAC_5_DATA = 0x38,
			AMC7812_REG_ADR__DAC_6_DATA = 0x39,
			AMC7812_REG_ADR__DAC_7_DATA = 0x3A,
			AMC7812_REG_ADR__DAC_8_DATA = 0x3B,
			AMC7812_REG_ADR__DAC_9_DATA = 0x3C,
			AMC7812_REG_ADR__DAC_10_DATA = 0x3D,
			AMC7812_REG_ADR__DAC_11_DATA = 0x3E,
		} E_AMC7812_DAC_DATA_REG_ADDRESSES;


		// States for the AMC7812 DAC state machine

		typedef enum
		{

			// do nothing
			AMC7812_DAC_STATE__IDLE = 0U,

			// We are in an error condition
			AMC7812_DAC_STATE__ERROR,

			// init the device, force a reset
			AMC7812_DAC_STATE__INIT_DEVICE,

			// Read the constants from the device
			AMC7812_DAC_STATE__START,

			// Waiting for the start of a conversion
			AMC7812_DAC_STATE__WAITING,

			// Issue the conversion command
			AMC7812_DAC_STATE__SET_VOLTAGE,

			// Wait for a number of processing loops to expire
			AMC7812_DAC_STATE__WAIT_LOOPS,


		} E_AMC7812_DAC_STATES_T;




		/*******************************************************************************
		Structures
		*******************************************************************************/

		struct _strAMC7812_DAC
		{

			// the current state

			E_AMC7812_DAC_STATES_T eState;

			// counter for the number of main program loops

			Luint32 u32LoopCounter;

			// DAC voltage limits - millivolts

			Luint16 u16MaxVoltage;
			Luint16 u16MinVoltage;

			// Input data to be set by function calling DAC:

			// Commanded value (e.g., RPMs)

			Luint16 u16Command;

			// Highest permissible value for the commanded quantity

			Luint16 u16MaxCommandValue;

			// Lowest permissible value for the commanded quantity

			Luint16 u16MinCommandValue;

			// Output channel data

			Luint8 u8DACRegAddr;

			// DAC gain flag

			Luint8 u8Gain;

			// DAC output scale factor

			Lfloat32 f32ScaleFactor;

		};



		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vAMC7812__Init(void);
		void vAMC7812__Process(void);
		
		//Lowlevel
		void vAMC7812_LOWLEVEL__Init(void);
		void vAMC7812_LOWLEVEL__Reset(void);

		//I2C
		void vAMC7812_I2C__Init(void);

		Lint16 s16AMC7812_I2C__TxCommand(Luint8 u8DeviceAddx, Luint8 u8RegisterAddx);
		Lint16 s16AMC7812_I2C__WriteU16(Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint16 u16Value);
		Lint16 s16AMC7812_I2C__TxCommand(Luint8 u8DeviceAddx, Luint8 u8RegisterAddx);
		Lint16 s16AMC7812_I2C__ReadU16(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint16 *pu16Value);

		
		//DAC
		void vAMC7812_DAC__Init(void);
		Luint16 vAMC7812_DAC__Process(void);
		Lint16 s16AMC7812_DAC__SetPinVoltage(void);

		
		//ADC
		void vAMC7812_ADC__Init(void);
		
		//setup the GPIO
		void vAMC7812_GPIO__Init(void);
		void vAMC7812_GPIO__Process(void);
		void vAMC7812_GPIO__Test(void);
		
	#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_AMC7812_H_

