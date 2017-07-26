/**
 * @file		RM4_I2C.H
 * @brief		Main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM215R0.FILE.002
 */
#ifndef _RM4_I2C_H_
#define _RM4_I2C_H_

	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE == 1U

		#include <RM4/LCCM215__RM4__I2C/rm4_i2c__private.h>
		#include <RM4/LCCM215__RM4__I2C/rm4_i2c__fault_flags.h>
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		//error
		#define C_RM4I2C__ERROR__NO_ERROR 							(0)

		//Timeout waiting for buffer empty
		#define C_RM4I2C__ERROR__TIMEOUT 							(-1)

		//NACK Received.
		#define C_RM4I2C__ERROR__NACK 								(-2)



		/** RM4 I2C Main Structure */
		struct _strRM4I2C
		{
			Luint32 u32Length;
			Luint8 *pu8Data;


			/** The fault flags for the module */
			FAULT_TREE__PUBLIC_T sFaultFlags;

			/** The timeout counter */
			Luint32 u32TimeoutCounter;


			/** Statistics Structure */
			struct
			{

				/**
				 * Number of bus timeouts that have occured
				 * This is a general counter related to the timeout module
				 */
				Luint32 u32General_Timeout;



			}sStats;

		};

		/** @enum i2cBitCount
		* @brief Alias names for i2c bit count
		* This enumeration is used to provide alias names for I2C bit count:
		*/

		enum i2cBitCount
		{
			I2C_2_BIT = 0x2U,
			I2C_3_BIT = 0x3U,
			I2C_4_BIT = 0x4U,
			I2C_5_BIT = 0x5U,
			I2C_6_BIT = 0x6U,
			I2C_7_BIT = 0x7U,
			I2C_8_BIT = 0x0U
		};




		/** @enum i2cStatFlags
		* @brief Interrupt Status Definitions
		*
		*/
		enum i2cStatFlags
		{
			I2C_AL		 = 0x0001U, /* arbitration lost		 */
			I2C_NACK	 = 0x0002U, /* no acknowledgement		*/
			I2C_ARDY	 = 0x0004U, /* access ready			 */
			I2C_RX		 = 0x0008U, /* receive data ready		*/
			I2C_TX		 = 0x0010U, /* transmit data ready	 */
			I2C_SCD		= 0x0020U, /* stop condition detect	 */
			I2C_AD0		= 0x0100U, /* address Zero Status	 */
			I2C_AAS		= 0x0200U, /* address as slave		 */
			I2C_XSMT	 = 0x0400U, /* Transmit shift empty not */
			I2C_RXFULL	 = 0x0800U, /* receive full			 */
			I2C_BUSBUSY	= 0x1000U, /* bus busy				 */
			I2C_NACKSNT	= 0x2000U, /* No Ack Sent			 */
			I2C_SDIR	 = 0x4000U /* Slave Direction		 */
		};


		/** @enum i2cDMA
		* @brief I2C DMA definitions
		*
		* Used before i2c transfer
		*/
		enum i2cDMA
		{
			I2C_TXDMA = 0x20U,
			I2C_RXDMA = 0x10U
		};



		//function prototypes
		//global private rm4_i2c.c
		void vRM4_I2C__Init(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Get_RegAddx(TE_RM4_I2C__CHANNEL eChannel, RM4_I2C__BASE_T **pReg);

		//global rm4_i2c__user.c
		void vRM4_I2C_USER__Init(TE_RM4_I2C__CHANNEL eChannel);
		Luint32 u32RM4_I2C_USER__Get_FaultFlags(TE_RM4_I2C__CHANNEL eChannel);
		Lint16 s16RM4_I2C_USER__Tx_U8(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 u8Byte);
		Lint16 s16RM4_I2C_USER__TxReg(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx);
		Lint16 s16RM4_I2C_USER__RxReg(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 *pu8Byte);
		Lint16 s16RM4_I2C_USER__Rx_U8(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 *pu8Byte);
		Lint16 s16RM4_I2C_USER__Tx_U8Array(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 *pu8Array, Luint8 u8ArrayLength);
		Lint16 s16RM4_I2C_USER__Tx_U8Array_Constant(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 u8Value, Luint16 u16ArrayLength);
		Lint16 s16RM4_I2C_USER__Rx_U8Array(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 *pu8Array, Luint8 u8ArrayLength);
		Lint16 s16RM4_I2C_USER__RxBit_U8(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 u8BitNumber, Luint8 *pu8Byte);
		Lint16 s16RM4_I2C_USER__RxBits_U8(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint8 u8RegisterAddx, Luint8 u8BitStart, Luint8 u8Length, Luint8 *pu8Byte);
		Lint16 s16RM4_I2C_USER__RxByte16(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint16 u16RegisterAddx, Luint8 *pu8Byte);
		Lint16 s16RM4_I2C_USER__TxByte16(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint16 u16RegisterAddx, Luint8 u8Byte);
		Lint16 s16RM4_I2C_USER__RxByteArray16(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8DeviceAddx, Luint16 u16RegisterAddx, Luint8 *pu8Array, Luint8 u8ArrayLength);

		//waits
		Luint8 u8RM4_I2C_WAIT__IsBusBusy(TE_RM4_I2C__CHANNEL eChannel);
		Luint8 u8RM4_I2C_WAIT__TxBufferEmpty(TE_RM4_I2C__CHANNEL eChannel);
		Luint8 u8RM4_I2C_WAIT__TxBufferEmpty_Or_NACK(TE_RM4_I2C__CHANNEL eChannel);
		Luint8 u8RM4_I2C_WAIT__RxBufferFull(TE_RM4_I2C__CHANNEL eChannel);

		//timeout
		void vRM4_I2C_TIMEOUT__Start(void);
		Luint8 u8RM4_I2C_TIMEOUT__Check(void);
		void vRM4_I2C_TIMEOUT__Stop(void);

		//local functions
		void vRM4_I2C__TransmiterEnable(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__ReceiverEnable(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Set_OwnAdd(TE_RM4_I2C__CHANNEL eChannel, Luint16 u16OwnAdd);
		void vRM4_I2C__Set_SlaveAdd(TE_RM4_I2C__CHANNEL eChannel, Luint16 u16SlaveAdd);
		void vRM4_I2C__Set_Stop(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Clear_Stop(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Set_MasterMode(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8MasterEnable);
		void vRM4_I2C__Set_TransactionLength(TE_RM4_I2C__CHANNEL eChannel, Luint16 u16Size);
		Luint8 u8RM4_I2C__IsBusBusy(TE_RM4_I2C__CHANNEL eChannel);

		//pins
		void vRM4_I2C_PINS__Set_SDA_Tris(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8Tris);
		void vRM4_I2C_PINS__Set_SCL_Tris(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8Tris);
		void vRM4_I2C_PINS__Set_SDA_Latch(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8Latch);
		void vRM4_I2C_PINS__Set_SCL_Latch(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8Latch);
		Luint8 u8RM4_I2C_PINS__Get_SDA(TE_RM4_I2C__CHANNEL eChannel);
		Luint8 u8RM4_I2C_PINS__Get_SCL(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C_PINS__Set_OutputLow(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C_PINS__Set_Functional(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C_PINS__Toggle_Clock(TE_RM4_I2C__CHANNEL eChannel);

		//interrupts
		#if C_LOCALDEF__LCCM215__USE_INTERRUPTS == 1U
			void vRM4_I2C_ISR__GeneralRoutine(void);
		#endif

	
		//private function prototypes
		//rm4_i2c.c
		void vRM4_I2C__SetUpTransaction(TE_RM4_I2C__CHANNEL eChannel, Luint16 u16Length, Luint8 u8GenerateStopCondition, Luint8 u8IsTransmission, Luint8 u8SlaveAddress);
		Luint8 u8RM4_I2C__Get_NACK(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Clear_NACK(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Set_Start(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__Master_Ignore_NACK(TE_RM4_I2C__CHANNEL eChannel);
		Luint16 u16RM4_I2C__IsTxBufferEmpty(TE_RM4_I2C__CHANNEL eChannel);
		Luint16 u16RM4_I2C__IsRxBufferFull(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__SendByte(TE_RM4_I2C__CHANNEL eChannel, Luint8 u8Byte);
		Luint8 u8RM4_I2C__ReceiveByte(TE_RM4_I2C__CHANNEL eChannel);
		void vRM4_I2C__SendArray(Luint32 u32Length, Luint8 *pu8Data);
		void vRM4_I2C__ReceiveArray(Luint32 u32Length, Luint8 *pu8Data);


	#endif //C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE


#endif //_RM4_I2C_H_
