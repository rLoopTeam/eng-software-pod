/**
 * @file		rm4_emif.h
 * @brief		Main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM107R0.FILE.002
 */
#ifndef __RM4_EMIF_H__
#define __RM4_EMIF_H__

	/*lint -e537*/
	#include <localdef.h>
	#if C_LOCALDEF__LCCM107__ENABLE_THIS_MODULE == 1U
		
		#include <rm4/lccm107__rm4__emif/rm4_emif__private.h>
		#include <rm4/lccm229__rm4__dma/rm4_dma__private.h>

		typedef volatile struct emifDATA
		{
			//Simply the data, a read or write to this will trigger
			//a CS2 write
			Luint32 u32Data;

		} RM4_EMIF__DATA_T;

		//when using our "SPECIAL" features, determine the region.
		typedef enum
		{
			CS_REGION__CS0 = 0x80000000,
			CS_REGION__CS2 = 0x60000000,
			CS_REGION__CS3 = 0x64000000,
			CS_REGION__CS4 = 0x68000000


		}RM4_EMIF__SPECIAL_CS_REGION_T;

		#define emifDATA_CS2   ((RM4_EMIF__DATA_T *)0x60000000)
		#define emifDATA_CS3   ((RM4_EMIF__DATA_T *)0x64000000)
		#define emifDATA_CS4   ((RM4_EMIF__DATA_T *)0x68000000)


		struct _strEMIF
		{

			struct
			{
				/** Is flow control enabled? */
				Luint8 u8FlowControl;

				/** are we a constant (i.e. non source inc) transfer? */
				Luint8 u8ConstantTx;

				/** The total transfer size of pixels */
				Luint32 u32TotalTransferSize;

				/** The number of full frame transfers */
				Luint32 u32FullFrameTransfers;

				/** The size of the number of full elements to transfer */
				Luint32 u32FullElemntTransfers;

				/** Do we have a delta packet */
				Luint8 u8DeltaPacket;

				/** Delta Packet Size */
				Luint32 u32DeltaSize;

				/** The Control Packet Used For Transfers */
				RM4_DMA__CONTROL_T pControl;

				RM4_EMIF__SPECIAL_CS_REGION_T eRegion;

				/** Next packet queued and ready for Tx */
				Luint8 u8NextPacketQueued;

			}sSpecial;


		};



		#if C_LOCALDEF__LCCM107__ENABLE_ENCAP == 1U

		typedef union _unCAN_ENCAP
		{
			struct _strCAN_ENCAP
			{
				//the packet type, 1 byte :0
				Luint8 u8PacketType;
				//the sub type (typically 0) 1 byte :1
				Luint8 u8SubType;
				//the packet sequence number, 4 bytes :5
				Luint32 u32Sequence;
				//the time stamp, 4 bytes :9
				Luint32 u32TimeStamp;
				//The source Node ID on the network, 1 byte :10
				Luint8 u8NodeID;
				//The message ID, 2 bytes :12
				Luint16 u16MessageID;
				//The CAN maximum payload data, 8 bytes :20
				Luint8 u8PayloadData[8];
				//the reserved data to bring up to 32-2 bytes
				Luint8 u8Reserved[32-1-1-4-4-1-2-8 -2];

				//The 16bit CRC
				Luint16 u16CRC;
			}sENC;

			Luint16 u16Buffer[16];
		}unCAN_ENCAP;

		 //__attribute__ ((packed))
		#endif //C_LOCALDEF__LCCM107__ENABLE_ENCAP

		//function protos
		void vRM4_EMIF__Init(void);
		void vRM4_EMIF__CS2_WriteU32(Luint32 u32Data);
		void vRM4_EMIF__CS3_WriteU32(Luint32 u32Data);
		void vRM4_EMIF__CS4_WriteU32(Luint32 u32Data);
		void vRM4_EMIF__CS2_WriteU16_Addx(Luint32 u32Addx, Luint16 u16Data);
		void vRM4_EMIF__CS3_WriteU16_Addx(Luint32 u32Addx, Luint16 u16Data);
		void vRM4_EMIF__CS4_WriteU16_Addx(Luint32 u32Addx, Luint16 u16Data);

		Luint32 u32RM4_EMIF__CS2_Read(void);
		Luint32 u32RM4_EMIF__CS3_Read(void);
		Luint32 u32RM4_EMIF__CS4_Read(void);
		Luint32 u32RM4_EMIF__CS2_Read_Addx(Luint32 u32Addx);
		Luint32 u32RM4_EMIF__CS3_Read_Addx(Luint32 u32Addx);
		Luint32 u32RM4_EMIF__CS4_Read_Addx(Luint32 u32Addx);


		//special
		Luint8 u8RM4_EMIF_SPECIAL__IsBusy(void);
		void vRM4_EMIF_SPECIAL__TxBuffer(Luint32 u32DMAChannel, RM4_EMIF__SPECIAL_CS_REGION_T eRegion, const Luint32 * pu32Source, Luint32 u32Size, Luint8 u8FlowControl);
		void vRM4_EMIF_SPECIAL__TxConstant(Luint32 u32DMAChannel, RM4_EMIF__SPECIAL_CS_REGION_T eRegion, Luint16 u16Constant, Luint32 u32Size, Luint8 u8FlowControl);
		void vRM4_EMIF_SPECIAL__RxConstant(Luint32 u32DMAChannel, RM4_EMIF__SPECIAL_CS_REGION_T eRegion, Luint32 u32Offset, Luint32 u32Size);
		void vRM4_EMIF_SPECIAL__Signal_FrameTxComplete(void);
		void vRM4_EMIF_SPECIAL__Continue(void);

		//pin testing
		void vRM4_EMIF_PINS__Test(void);

		//packet read/write
		#if C_LOCALDEF__LCCM107__ENABLE_ENCAP == 1U
			void vRM4_EMIF_ENCAP__Init(void);
			void vRM4_EMIF_ENCAP__WritePacket(Luint16 * pu16Data);
			void vRM4_EMIF_ENCAP__ReadPacket(Luint8 * pu8Buffer);
		#endif //C_LOCALDEF__LCCM107__ENABLE_ENCAP

		#ifndef C_LOCALDEF__LCCM107__ENABLE_ENCAP
			#error
		#endif
	
		#if C_LOCALDEF__LCCM107__TEST_SPEC == 1
			void vLCCM107_TS_001(void);
			void vLCCM107_TS_002(void);
			void vLCCM107_TS_003(void);
			void vLCCM107_TS_004(void);
		#endif

	#endif //C_LOCALDEF__LCCM107__ENABLE_THIS_MODULE==1
	
	#ifndef C_LOCALDEF__LCCM107__ENABLE_THIS_MODULE
		#error
	#endif

	
#endif //__RM4_EMIF_H__

