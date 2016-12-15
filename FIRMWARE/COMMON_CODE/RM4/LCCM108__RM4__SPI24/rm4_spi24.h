/**
 * @file		RM4_SPI24.H
 * @brief		SPI2,4 main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM108R0.FILE.002
 */



#ifndef _RM4_SPI2_H_
#define _RM4_SPI2_H_

	/*lint -e537*/
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE == 1U

		/*****************************************************************************
		Includes
		*****************************************************************************/
		#include <rm4/lccm108__rm4__spi24/rm4_spi24__private.h>
		#include <rm4/lccm108__rm4__spi24/rm4_spi24__semistaticdef.h>


		/*****************************************************************************
		Defines
		*****************************************************************************/
		#define CS0_MSK  0x00000001
		#define CS1_MSK  0x00000002
		#define ENA_MSK  0x00000100
		#define CLK_MSK  0x00000200
		#define SIMO_MSK 0x00000400
		#define SOMI_MSK 0x00000800


		//channels
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			SPI24_CHANNEL__2 = 2U,
			SPI24_CHANNEL__4 = 4U

		}RM4_SPI24__CHANNELS_T;

		//the clock phase
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			//Valid on Leading Edge
			SPI24_CPHA__0 = 0U,

			//Valid on trailing edge
			SPI24_CPHA__1 = 1U

		}RM4_SPI24__CPHA_T;

		//available speeds that we can set the device to
		//only with VCLK1 = 100MHZ
		//These actually form the Prescaler Values at 100MHZ
		//BRFormatx = VBUSPCLK / (PRESCALEx + 1)
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			SPI24_SPEED__400K = 249U,
			SPI24_SPEED__3MHZ = 33U,
			SPI24_SPEED__4MHZ = 24U,
			SPI24_SPEED__5MHZ = 19U,
			SPI24_SPEED__8MHZ = 12U,
			SPI24_SPEED__10MHZ = 9U,
			SPI24_SPEED__20MHZ = 4U
		}RM4_SPI24__SPEEDS_T;


		/** @enum chipSelect
		*   @brief Transfer Group Chip Select
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			SPI24_CS__NONE = 0xFF,
			SPI24_CS__0    = 0xFE,
			SPI24_CS__1    = 0xFD,
			SPI24_CS__2    = 0xFB,
			SPI24_CS__3    = 0xF7,
			SPI24_CS__4    = 0xEF,
			SPI24_CS__5    = 0xDF,
			SPI24_CS__6    = 0xBF,
			SPI24_CS__7    = 0x7F
		}RM4_SPI24__CHIP_SELECT_T;

		/** @enum spiPinSelect
		*   @brief spi Pin Select
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			SPI24_PIN__CS0    = 0,
			SPI24_PIN__CS1    = 1,
			SPI24_PIN__CS2    = 2,
			SPI24_PIN__CS3    = 3,
			SPI24_PIN__CS4    = 4,
			SPI24_PIN__CS5    = 5,
			SPI24_PIN__CS6    = 6,
			SPI24_PIN__CS7    = 7,
			SPI24_PIN__ENA    = 8,
			SPI24_PIN__CLK    = 9,
			SPI24_PIN__SIMO   = 10,
			SPI24_PIN__SOMI   = 11,
			SPI24_PIN__SIMO1 = 17,
			SPI24_PIN__SIMO2 = 18,
			SPI24_PIN__SIMO3 = 19,
			SPI24_PIN__SIMO4 = 20,
			SPI24_PIN__SIMO5 = 21,
			SPI24_PIN__SIMO6 = 22,
			SPI24_PIN__SIMO7 = 23,
			SPI24_PIN__SOMI1 = 25,
			SPI24_PIN__SOMI2 = 26,
			SPI24_PIN__SOMI3 = 27,
			SPI24_PIN__SOMI4 = 28,
			SPI24_PIN__SOMI5 = 29,
			SPI24_PIN__SOMI6 = 30,
			SPI24_PIN__SOMI7 = 31

		}RM4_SPI24__PIN_T;

		//pin fuctionality
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			SPI24_PINFUNC__GPIO = 0U,
			SPI24_PINFUNC__SPI = 1U
		}RM4_SPI24__PIN_FUNC_T;

		/** @enum dataformat
		*   @brief SPI dataformat register select
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum dataformat
		{
			SPI24_DATA_FORMAT__0 = 0,
			SPI24_DATA_FORMAT__1 = 1,
			SPI24_DATA_FORMAT__2 = 2,
			SPI24_DATA_FORMAT__3 = 3
		}RM4_SPI24__DATA_FORMAT_T;


		/*****************************************************************************
		*****************************************************************************/
		typedef struct spiDAT1RegConfig
		{
			Luint32 CS_HOLD;
			Luint32 WDEL;
			Luint32 DFSEL;
			Luint32 CSNR;
			Luint32 u32UpperDAT1;
			Luint8 OperationMode;
		}RM4_SPI24__DATA_REG__T;

		extern RM4_SPI24__DATA_REG__T m_SPI24DataFormat;

		/*****************************************************************************
		Function Prototypes
		*****************************************************************************/
		void vRM4_SPI24__Init(RM4_SPI24__CHANNELS_T eChannel);
		void vRM4_SPI24__Set_Speed(RM4_SPI24__CHANNELS_T eChannel, RM4_SPI24__DATA_FORMAT_T eDataFormat, RM4_SPI24__SPEEDS_T eSpeed);
		void vRM4_SPI24__Setup_Interrupts(RM4_SPI24__CHANNELS_T eChannel);
		void vRM4_SPI24_PINS__Set_Defaults(RM4_SPI24__CHANNELS_T eChannel);

		Luint32 u32RM4_SPI2__SendData(Luint32 u32DataOut);
		Luint8 u8RM4_SPI24__SendU8(RM4_SPI24__CHANNELS_T eChannel, RM4_SPI24__DATA_FORMAT_T eDataFormat, RM4_SPI24__CHIP_SELECT_T eChipSelectNum, Luint8 u8Data);
		Luint16 u16RM4_SPI24__SendU16(RM4_SPI24__CHANNELS_T eChannel,RM4_SPI24__DATA_FORMAT_T eDataFormat, RM4_SPI24__CHIP_SELECT_T eChipSelectNum, Luint16 u16Data);
		Luint16 u16RM4_SPI24__SendU16_2(RM4_SPI24__CHANNELS_T eChannel,RM4_SPI24__DATA_FORMAT_T eDataFormat, RM4_SPI24__CHIP_SELECT_T eChipSelectNum, Luint8 u8DataL, Luint8 u8DataH);

		//pins
		void vRM4_SPI24_PINS__Set_DirectionOutput(RM4_SPI24__CHANNELS_T eChannel, RM4_SPI24__PIN_T ePin);
		void vRM4_SPI24_PINS__Set_DirectionInput(RM4_SPI24__CHANNELS_T eChannel, RM4_SPI24__PIN_T ePin);
		void vRM4_SPI24_PINS__Set_Pin(RM4_SPI24__CHANNELS_T eChannel, RM4_SPI24__PIN_T ePin, Luint8 u8Value);
		void vRM4_SPI24_PINS__Off(RM4_SPI24__CHANNELS_T eChannel, RM4_SPI24__PIN_T ePin);

		//Declarations without and with interrupts enabled
		#if C_LOCALDEF__LCCM108__ENABLE_INTERRUPTS == 0U
			Luint32 u32RM4_SPI2__TransmitData(RM4_SPI24__DATA_REG__T * pDataconfig_t, Luint32 u32Blocksize, Luint16 * pSrcbuff);
			Luint32 u32RM4_SPI2__ReceiveData(RM4_SPI24__DATA_REG__T * pDataconfig_t, Luint32 u32Blocksize, Luint16 * pDestbuff);
		#else //C_LOCALDEF__LCCM108__ENABLE_INTERRUPTS == 0

		/** @struct spiDAT1RegConfig
		*   @brief SPI data register configuration
		*/
		typedef struct spiPacket
		{
			Luint32  u32Mode;
			Luint32  u32Length;
			Luint16  * pData;
		} _spiPacket;

		extern  _spiPacket  g_spiPacket[2];

		//Declaration of functions for interrupts
		void vRM4_SPI24__Enable_Notification(Luint32 u32Flags);
		void vRM4_SPI24__Disable_Notification(Luint32 u32Flags);
		void vSPISendData(RM4_SPI24__DATA_REG__T * pDataconfig_t, Luint32 u32Blocksize, Luint16 * pSrcbuff);
		void vSPIGetData(RM4_SPI24__DATA_REG__T * pDataconfig_t, Luint32 u32Blocksize, Luint16 * pDestbuff);
		void vRM4_SPI24_ISR__Notification(Luint32 u32Flags);

	#endif //C_LOCALDEF__LCCM108__ENABLE_INTERRUPTS == 0

	#endif //C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE
#endif /* RM48_SPI_H_ */
