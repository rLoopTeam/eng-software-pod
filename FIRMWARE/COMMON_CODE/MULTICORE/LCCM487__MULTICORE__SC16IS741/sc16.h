/**
 * @file		SC16.H
 * @brief		Main Header File
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM487R0.FILE.002
 */

#ifndef _SC16_H_
#define _SC16_H_
	#include <localdef.h>

	#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U

		//required for software fifo public types
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo__public.h>

		//required for fault tree
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		//required so as we can get access to the flags.
		#include <MULTICORE/LCCM487__MULTICORE__SC16IS741/sc16__fault_flags.h>


		/*******************************************************************************
		Defines
		*******************************************************************************/
		/** Max Raw SPI FIFO depth */
		#define C_SC16__MAX_RAW_SPI_FIFO_DEPTH									(128U)

		#define C_SC16__MAX_SPI_TXFIFO_DEPTH									(4U)

		#define C_SC16__MAX_SPI_TXFIFO_BYTE_SIZE								(64U)

		#define C_SC16__MAX_RX_ARRAY_SIZE										(64U)


		typedef enum
		{

			SC16_REG__THR = 0x00U,


			SC16_REG__LCR = 0x03U,

			SC16_REG__MCR = 0x04U,

			SC16_REG__TCR = 0x06U,

			/*
			8.13 Trigger Level Register (TLR)
				This 8-bit register is used to store the transmit and received FIFO trigger levels used for
				interrupt generation. Trigger levels from 4 to 60 can be programmed with a granularity
				of 4. Table 24 shows trigger level register bit settings.
				Remark: TLR can only be written to when EFR[4] = 1 and MCR[2] = 1. If TLR[3:0] or
				TLR[7U:4] are logical 0, the selectable trigger levels via the FIFO Control Register (FCR)
				are used for the transmit and receive FIFO trigger levels. Trigger levels from 4 characters
				to 60 characters are available with a granularity of four. The TLR should be programmed
				for N4, where N is the desired trigger level.
				When the trigger level setting in TLR is zero, the SC16IS741 uses the trigger level setting
				defined in FCR. If TLR has non-zero trigger level value, the trigger level defined in FCR is
				discarded. This applies to both transmit FIFO and receive FIFO trigger level setting.
				When TLR is used for RX trigger level control, FCR[7U:6] should be left at the default state,
				that is
			 */
			SC16_REG__TLR = 0x07U


		}SC16__REGS__T;

		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strSC16
		{

			/** the multiple devices */
			struct
			{
				//the fault flags for this module
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** Received array */
				Luint8 u8RxDataArray[C_SC16__MAX_RX_ARRAY_SIZE];

				/** Number of bytes in the Rx*/
				Luint8 u8NumofRxBytes;

				/** count of bytes being sent */
				Luint8 u8TxCounter;

				Luint8 u8TxSwitchCounter;

				Luint32 u32baud;

				//Flags
				Luint8 u8Interrupt;

				Luint8 u8ISRFlag;

				Luint8 u8NewDataAvalible;

				Luint8 u8ErrorFlag;

				// 0 = no error
				// 1 = FIFO read count is great than 65 characters (max should only be 64)
				// 2 = Unknown Interrupt status
				// 3 = Handle_Interrupt was called but no interrput was received
				// 4 = there was an overrun error flag in the Rx FIFO
				// 5 = there was an Parity error flag in the Rx FIFO
				// 6 = there was an framing error flag in the Rx FIFO
				// 7 = there was an break interrput flag in the Rx FIFO

				//test varible
				Luint16 u16test;


				struct
				{

					//the FIFO
					SOFTWARE_FIFO__USER_T	sSPIFIFO;

					Luint8 u8Character[C_SC16__MAX_RAW_SPI_FIFO_DEPTH];


				}sRawSPI_FIFO;


				/** Transmit FIFO size */
				struct
				{

					//the FIFO
					SOFTWARE_FIFO__USER_T	sSPITXFIFO;

					/** Save the pack of data for each TX fifo entry with a maximum byte size */
					Luint8 u8Packet[C_SC16__MAX_SPI_TXFIFO_DEPTH][C_SC16__MAX_SPI_TXFIFO_BYTE_SIZE];

					/** save the packe length for each transmit FIFO entry */
					Luint8 u8PacketLength[C_SC16__MAX_SPI_TXFIFO_DEPTH];


				}sSPI_TxFIFO;

				/** keep track of hardware items */
				struct
				{

					/** Have we performed a device reset? */
					Luint8 u8IsReset;


					/** A hardware interrupt has occurred */
					Luint8 u8HW_Interrupt;

				}sHardware;

			}sDevice[C_LOCALDEF__LCCM487__NUM_DEVICES];

		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/

		//sc16.c
		void vSC16__Init(Luint8 u8DeviceIndex);
		void vSC16__Process(Luint8 u8DeviceIndex);
		Luint8 u8SC16__Get_NewDataAvalible(Luint8 u8DeviceIndex);
		Luint8 u8SC16__Get_ErrorFlagStatus(Luint8 u8DeviceIndex);
		void vSC16__Clear_ErrorFlagStatus(Luint8 u8DeviceIndex);
		void vSC16__Clear_NewDataAvalible(Luint8 u8DeviceIndex);
		void vSC16__Clear_Rx_Byetes(Luint8 u8DeviceIndex);
		Luint8 u8SC16_USER__Is_TxAvail(Luint8 u8DeviceIndex);
		void vSC16_USER__Tx_Byte(Luint8 u8DeviceIndex);
		Luint8 u8SC16_USER__Get_ByteAvail(Luint8 u8DeviceIndex);
		Luint8 u8SC16_USER__Get_Byte(Luint8 u8DeviceIndex);
		void vSC16__Command_Write(Luint8 u8DeviceIndex, Luint8 *u8Data, Luint8 u8StringLength);


		//Interrupt
		void vSC16_INT__Init(Luint8 u8DeviceIndex);
		void vSC16_INT__Process(Luint8 u8DeviceIndex);
		void vSC16_INT__Handle_ISR(Luint8 u8DeviceIndex);
		void vSC16_INT__Enable_Xoff_Interrupt(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_INT__Enable_Rx_DataAvalibleInterupt(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_INT__Capture_ISR(Luint8 u8DeviceIndex);
		Luint8 u8SC16_INT__Read_Interupt_Status(Luint8 u8DeviceIndex);
		Luint8 u8SC16_INT__Read_Line_StatusReg(Luint8 u8DeviceIndex);
		Luint8 u8SC16_INT__Read_Line_Status(Luint8 u8DeviceIndex);


		//Registers
		void vSC16_REGISTERS__Edit_Register(Luint8 u8DeviceIndex, Luint8 u8MasterRegisterAddress, Luint8 u8SlaveRegisterAddress,Luint8 u8BitPosMasterReg ,Luint8 u8BitPosSlaveReg, Luint8 u8MasterBitStatus, Luint8 u8SlaveBitStatus);
		Luint8 u8SC16_REGISTERS__Read_Register(Luint8 u8DeviceIndex, Luint8 u8MasterRegisterAddress, Luint8 u8BitPosMasterReg, Luint8 u8MasterBitStatus, Luint8 u8SlaveRegisterAddress);

		//Fifo
		void vSC16_FIFO___Enable_FIFOs(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_FIFO__Reset_Rx_FIFO(Luint8 u8DeviceIndex, Luint8 u8Reset);
		void vSC16_FIFO__Reset_Tx_FIFO(Luint8 u8DeviceIndex, Luint8 u8Reset);

		//Flowcontrol
		void vSC16_FLOWCONTROL__Enable_EnhancedFeatures(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_FLOWCONTROL__Enable_SpecialCharacterDetect(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_FLOWCONTROL__Enable_ProgTriggerLvlRegister(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_FLOWCONTROL__Enable_Parity(Luint8 u8DeviceIndex, Luint8 u8Enable);
		void vSC16_FLOWCONTROL__Set_ProgTriggerlvlRegister(Luint8 u8DeviceIndex, Luint8 u8Triglevels);
		void vSC16_FLOWCONTROL__Set_RxTriggerlvl(Luint8 u8DeviceIndex, Luint8 u8Rxlevel);
		void vSC16_FLOWCONTROL__Set_SpecialCharacter(Luint8 u8DeviceIndex, Luint8 u8Character);

		Luint8 u8SC16_FLOWCONTROL__Read_Rx_FillLevel(Luint8 u8DeviceIndex);
		Luint8 u8SC16_FLOWCONTROL__Read_Tx_FillLevel(Luint8 u8DeviceIndex);

		//Loopback
		void vSC16_LOOPBACK__Enable_Rx_Loopback(Luint8 u8DeviceIndex, Luint8 u8Enable);

		//Baud
		void vSC16_BAUD__Set_BaudRate(Luint8 u8DeviceIndex, Luint8 u8InputClockFreq, Luint16 u16Baudrate, Luint8 u8Prescalar);
		void vSC16_BAUD__Set_Stopbits(Luint8 u8DeviceIndex, Luint8 u8StopBit);
		void vSC16_BAUD__Set_Wordlength(Luint8 u8DeviceIndex, Luint8 u8Wordlength);

		//low level.c
		void vSC16_LOWLEVEL__Init(Luint8 u8DeviceIndex);
		void vSC16_LOWLEVEL__Reg_Write(Luint8 u8DeviceIndex, Luint8 u8RegAddress,Luint8 u8RegData);
		Luint8 u8SC16_LOWLEVEL__Reg_Read(Luint8 u8DeviceIndex, Luint8 u8RegAddress);
		void vSC16_LOWLEVEL__FIFO_Write(Luint8 u8DeviceIndex, Luint8 *u8Data, Luint8 u8DataLength);
		void vSC16_LOWLEVEL__FIFO_Read(Luint8 u8DeviceIndex);



		//testing
		#if C_LOCALDEF__LCCM487__ENABLE_TEST_SPEC == 1U
			void vLCCM487_TS_002(void);
			void vLCCM487_TS_003(void);
			void vLCCM487_TS_004(void);
			void vLCCM487_TS_005(void);
			void vLCCM487_TS_006(void);
			void vLCCM487_TS_007(void);
			void vLCCM487_TS_008(void);
			void vLCCM487_TS_009(void);
			void vLCCM487_TS_010(void);
			void vLCCM487_TS_011(void);
			void vLCCM487_TS_012(void);
			void vLCCM487_TS_013(void);
			void vLCCM487_TS_014(void);
			void vLCCM487_TS_015(void);
			void vLCCM487_TS_016(void);
			void vLCCM487_TS_017(void);
			void vLCCM487_TS_019(void);
			void vLCCM487_TS_020(void);
			void vLCCM487_TS_021(void);
			void vLCCM487_TS_022(void);
			void vLCCM487_TS_023(void);
			void vLCCM487_TS_024(void);
			void vLCCM487_TS_025(void);
			void vLCCM487_TS_026(void);
			void vLCCM487_TS_027(void);
			void vLCCM487_TS_028(void);
			void vLCCM487_TS_029(void);
			void vLCCM487_TS_030(void);
			void vLCCM487_TS_031(void);
			void vLCCM487_TS_032(void);
			void vLCCM487_TS_033(void);
			void vLCCM487_TS_034(void);
			void vLCCM487_TS_035(void);
		#endif


		//safetys
		#ifndef C_LOCALDEF__LCCM487__NUM_DEVICES
			#error
		#endif

	#endif //#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_SC16_H_

