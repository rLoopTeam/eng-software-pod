/**
 * @file		rm4_mibspi135.h
 * @brief		Main header file for SPI135
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM280R0.FILE.002
 */



 
#ifndef _MIBSPI135_H_
#define _MIBSPI135_H_

	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE == 1U

		#include <RM4/LCCM280__RM4__MIBSPI_135/rm4_mibspi135__private.h>

		//Types

		//channels
		typedef enum
		{
			MIBSPI135_CHANNEL__1 = 1U,
			/*channel 2 is not MIB*/
			SPI135_CHANNEL__2 = 2U,
			MIBSPI135_CHANNEL__3 = 3U,
			MIBSPI135_CHANNEL__5 = 5U

		}RM4_MIBSPI135__CHANNELS_T;

		//the clock phase
		typedef enum
		{
			//Valid on Leading Edge
			MIBSPI135_CPHA__0 = 0U,

			//Valid on trailing edge
			MIBSPI135_CPHA__1 = 1U

		}RM4_MIBSPI135__CPHA_T;

		//the clock polarity
		typedef enum
		{
			//Clock Idle Low
			MIBSPI135_CPOL__0 = 0U,

			//Clock Idle High
			MIBSPI135_CPOL__1 = 1U

		}RM4_MIBSPI135__CPOL_T;


		//the data formats
		typedef enum
		{
			MIBSPI135_DATA_FORMAT__0 = 0U,
			MIBSPI135_DATA_FORMAT__1 = 1U,
			MIBSPI135_DATA_FORMAT__2 = 2U,
			MIBSPI135_DATA_FORMAT__3 = 3U
		}RM4_MIBSPI135__DATA_FORMAT_T;

		//available speeds that we can set the device to
		//only with VCLK1 = 100MHZ
		//These actually form the Prescaler Values at 100MHZ
		typedef enum
		{
			//Minimum speed at 100MHZ
			MIBSPI135_SPEED__392K = 254U,
			MIBSPI135_SPEED__400K = 249U,
			MIBSPI135_SPEED__3MHZ = 33U,
			MIBSPI135_SPEED__4MHZ = 24U,
			MIBSPI135_SPEED__5MHZ = 19U,
			MIBSPI135_SPEED__8MHZ = 12U,
			MIBSPI135_SPEED__10MHZ = 9U,
			MIBSPI135_SPEED__20MHZ = 4U

		}RM4_MIBSPI135__SPEEDS_T;

		//data format tx lengths in bits
		typedef enum
		{
			MIBSPI135_DATAFORMAT__8BITS = 8U,
			MIBSPI135_DATAFORMAT__16BITS = 16U

		}RM4_MIBSPI135__DATAFORMAT_BITS_T;

		//loopback types
		typedef enum
		{
			MIBSPI135_LOOPBACK__DIGITAL = 0U,
			MIBSPI135_LOOPBACK__ANALOG = 1U
		}RM4_MIBSPI135__LOOPBACK_T;

		//parallel u32Mode
		typedef enum
		{
			MIBSPI135_PMODE_NORMAL	= 0x0U,
			MIBSPI135_PMODE_2_DATALINE = 0x1U,
			MIBSPI135_PMODE_4_DATALINE = 0x2U,
			MIBSPI135_PMODE_8_DATALINE = 0x3U
		}RM4_MIBSPI135__PARALLEL_MODE_T;

		/** @enum chipSelect
		* @brief Transfer Group Chip Select
		*/
		typedef enum
		{
			MIBSPI135_CS__NONE = 0xFFU,
			MIBSPI135_CS__0 = 0xFEU,
			MIBSPI135_CS__1 = 0xFDU,
			MIBSPI135_CS__2 = 0xFBU,
			MIBSPI135_CS__3 = 0xF7U,
			MIBSPI135_CS__4 = 0xEFU,
			MIBSPI135_CS__5 = 0xDFU,
			MIBSPI135_CS__6 = 0xBFU,
			MIBSPI135_CS__7 = 0x7FU
		}RM4_MIBSPI135__CHIP_SELECT_T;

		/** @enum mibspiPinSelect
		* @brief mibspi Pin Select
		*/
		typedef enum
		{
			MIBSPI135_PIN__CS0 = 0U,
			MIBSPI135_PIN__CS1 = 1U,
			MIBSPI135_PIN__CS2 = 2U,
			MIBSPI135_PIN__CS3 = 3U,
			MIBSPI135_PIN__CS4 = 4U,
			MIBSPI135_PIN__CS5 = 5U,
			MIBSPI135_PIN__CS6 = 6U,
			MIBSPI135_PIN__CS7 = 7U,
			MIBSPI135_PIN__ENA = 8U,
			MIBSPI135_PIN__CLK = 9U,
			MIBSPI135_PIN__SIMO = 10U,
			MIBSPI135_PIN__SOMI = 11U,
			MIBSPI135_PIN__SIMO1 = 17U,
			MIBSPI135_PIN__SIMO2 = 18U,
			MIBSPI135_PIN__SIMO3 = 19U,
			MIBSPI135_PIN__SIMO4 = 20U,
			MIBSPI135_PIN__SIMO5 = 21U,
			MIBSPI135_PIN__SIMO6 = 22U,
			MIBSPI135_PIN__SIMO7 = 23U,
			MIBSPI135_PIN__SOMI1 = 25U,
			MIBSPI135_PIN__SOMI2 = 26U,
			MIBSPI135_PIN__SOMI3 = 27U,
			MIBSPI135_PIN__SOMI4 = 28U,
			MIBSPI135_PIN__SOMI5 = 29U,
			MIBSPI135_PIN__SOMI6 = 30U,
			MIBSPI135_PIN__SOMI7 = 31U
		}RM4_MIBSPI135__PIN_SELECT_T;


		/** @enum triggerSource
				* @brief Transfer Group Trigger Source
				*/
		typedef enum
		{
			MIBSPI135_TRG__DISABLED,
			MIBSPI135_TRG__GIOA0,
			MIBSPI135_TRG__GIOA1,
			MIBSPI135_TRG__GIOA2,
			MIBSPI135_TRG__GIOA3,
			MIBSPI135_TRG__GIOA4,
			MIBSPI135_TRG__GIOA5,
			MIBSPI135_TRG__GIOA6,
			MIBSPI135_TRG__GIOA7,
			MIBSPI135_TRG__HET1_8,
			MIBSPI135_TRG__HET1_10,
			MIBSPI135_TRG__HET1_12,
			MIBSPI135_TRG__HET1_14,
			MIBSPI135_TRG__HET1_16,
			MIBSPI135_TRG__HET1_18,
			MIBSPI135_TRG__TICK
		}RM4_MIBSPI135__TRIGGER_SOURCE_T;


		//function prots
		void vRM4_MIBSPI135__Init(RM4_MIBSPI135__CHANNELS_T eChannel);

		//tx
		Luint16 u16RM4_MIBSPI135__Tx_U16_2(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__DATA_FORMAT_T eDataFormat, RM4_MIBSPI135__CHIP_SELECT_T eChipSelectNum, Luint8 u8DataL, Luint8 u8DataH);
		Luint8 u8RM4_MIBSPI135__Tx_U16_2_LSB(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__DATA_FORMAT_T eDataFormat, RM4_MIBSPI135__CHIP_SELECT_T eChipSelectNum, Luint8 u8DataL, Luint8 u8DataH);
		Luint16 u16RM4_MIBSPI135__Tx_U16(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__DATA_FORMAT_T eDataFormat, RM4_MIBSPI135__CHIP_SELECT_T eChipSelectNum, Luint16 u16Data);
		Luint8 u8RM4_MIBSPI135__Tx_U8(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__DATA_FORMAT_T eDataFormat, RM4_MIBSPI135__CHIP_SELECT_T eChipSelectNum, Luint8 u8Data);

		//pins
		void vRM4_MIBSPI135_PINS__Set_OutputDirection(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__PIN_SELECT_T ePin);
		void vRM4_MIBSPI135_PINS__Set(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__PIN_SELECT_T ePin, Luint32 u32Value);
		void vRM4_MIBSPI135_PINS__Set_Low(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__PIN_SELECT_T ePin);
		void vRM4_MIBSPI135_PINS__Set_High(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__PIN_SELECT_T ePin);
		void vRM4_MIBSPI135_PINS__Set_Defaults(RM4_MIBSPI135__CHANNELS_T eChannel);

		//speed
		void vRM4_MIBSPI135__Set_Speed(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__DATA_FORMAT_T eDataFormat, RM4_MIBSPI135__SPEEDS_T eSpeed);

		//loopback
		void vRM4_MIBSPI135__Enable_Loopback(RM4_MIBSPI135__CHANNELS_T eChannel, RM4_MIBSPI135__LOOPBACK_T Loopbacktype);
		void vRM4_MIBSPI135__Disable_Loopback(RM4_MIBSPI135__CHANNELS_T eChannel);

		//interrupts
		#if C_LOCALDEF__LCCM280__ENABLE_INTERRUPTS == 1U
			void vRM4_MIBSPI135__Setup_Interrupts(RM4_MIBSPI135__CHANNELS_T eChannel);
			void vRM4_MIBSPI135_ISR1__High(void);
			void vRM4_MIBSPI135_ISR1__Low(void);
			void vRM4_MIBSPI135_ISR3__High(void);
			void vRM4_MIBSPI135_ISR3__Low(void);
			void vRM4_MIBSPI135_ISR5__High(void);
			void vRM4_MIBSPI135_ISR5__Low(void);
		#endif

		//errors
		void vRM4_MIBSPI135_PINS__CheckErrors(RM4_MIBSPI135__CHANNELS_T eChannel);

	#endif //C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE



#endif //MIBSPI135_H
