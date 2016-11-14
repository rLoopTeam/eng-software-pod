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


		// enum type for THROTTLE DAC 16-bit data registers
		typedef enum ACM7812_DAC_DATA_REG_ADDRESSES
		{
			ACM7812_DAC_DATA_REG_ADR__HE1 = 0x33,		// address for AMC7812 DAC-0-OUT pin register, DAC-1- to DAC-7-OUT pins follow in order (see Table 10 in AMC7812 Datasheet)
			ACM7812_DAC_DATA_REG_ADR__HE2 = 0x34,
			ACM7812_DAC_DATA_REG_ADR__HE3 = 0x35,
			ACM7812_DAC_DATA_REG_ADR__HE4 = 0x36,
			ACM7812_DAC_DATA_REG_ADR__HE5 = 0x37,
			ACM7812_DAC_DATA_REG_ADR__HE6 = 0x38,
			ACM7812_DAC_DATA_REG_ADR__HE7 = 0x39,
			ACM7812_DAC_DATA_REG_ADR__HE8 = 0x3A
		} E_AMC7812_DAC_DATA_REG_ADDRESSES;

		typedef enum
		{
			ACM7812_DAC_REG__RESET = 0x7C
		} E_AMC7812_DAC_CONTROL_REG_ADDRESSES;

		/** State types for the TSYS01 state machine */
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
			AMC7812_DAC_STATE__WRITE,

			// Wait for a number of processing loops to expire
			AMC7812_DAC_STATE__WAIT_LOOPS,


		} E_AMC7812_DAC_STATES_T;



		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strAMC7812
		{

			/** the current state */
			E_AMC7812_DAC_STATES_T eState;

			/** counter the number of main program loops */
			Luint32 u32LoopCounter;

			E_AMC7812_DAC_DATA_REG_ADDRESSES eDAC_Data_Addx;

			Luint16 u16ThrottleCommand;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vAMC7812__Init(void);
		void vAMC7812__Process(void);
		
		//Lowlevel
		void vAMC7812_LOWLEVEL__Init(void);

		//I2C
		void vAMC7812_I2C__Init(void);
		
		//DAC
		void vAMC7812_DAC__Init(void);
		
		//ADC
		void vAMC7812_ADC__Init(void);
		
		//setup the GPIO
		void vAMC7812_GPIO__Init(void);
		
	#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_AMC7812_H_

