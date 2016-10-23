/**
 * @file		RM4_DMA__PRIVATE.H
 * @brief		Private Types and Defines for RM4 DMA module.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
  * 
 * @st_fileID	LCCM229R0.FILE.004
 */


#ifndef RM4_DMA__PRIVATE_H_
#define RM4_DMA__PRIVATE_H_

		#define C_RM4_DMA__MAX_CHANNELS		16


		/* 16.2.3 Addressing Modes
			There are three addressing modes supported by the DMA controller that can be setup independent for the
			source and the destination address:
				* Constant -- source and/or destination addresses do not change.
				* Post incremented -- source and/or destination address are post-incremented by the element size.
				* Indexed -- source and/or destination address is post-incremented as defined in the Element Index
					Offset Register (Section 16.3.2.5) and the Frame Index Offset Register (Section 16.3.2.6).
			An unaligned address with respect to the element size is not supported. An address chosen during
			transfer must be divisible by the element size.
		*/
		typedef enum
		{
			/** Fixed addressing mode */
			ADDX_MODE__FIXED = 0U,

			/** Post increment addressing mode */
			ADDX_MODE__POST_INCREMENT = 1U,

			/** Offset addressing mode */
			ADDX_MODE__OFFSET = 3U

		}RM4_DMA__ADDRESSING_MODE_E;


	/* DMA Register Frame Definition */
		/** @struct dmaBase
		* @brief DMA Register Frame Definition
		*
		* This type is used to access the DMA Registers.
		*/
		/** @struct RM4_DMA__BASE_T
		* @brief DMA Register Definition
		*
		* This structure is used to access the DMA module egisters.
		*/
		typedef volatile struct dmaBase
		{

			Luint32 GCTRL;	 /**< 0x0000: Global Control Register				*/
			Luint32 PEND;	 /**< 0x0004: Channel Pending Register			 */
			Luint32 FBREG;	 /**< 0x0008: Fall Back Register					 */
			Luint32 DMASTAT;	/**< 0x000C: Status Register						*/
			Luint32 u32RM4_DMA_BASE__rsvd1;	 /**< 0x0010: Reserved							 */
			Luint32 HWCHENAS; /**< 0x0014: HW Channel Enable Set				 */
			Luint32 u32RM4_DMA_BASE__rsvd2;	 /**< 0x0018: Reserved							 */
			Luint32 HWCHENAR; /**< 0x001C: HW Channel Enable Reset				*/
			Luint32 u32RM4_DMA_BASE__rsvd3;	 /**< 0x0020: Reserved							 */
			Luint32 SWCHENAS; /**< 0x0024: SW Channel Enable Set				 */
			Luint32 u32RM4_DMA_BASE__rsvd4;	 /**< 0x0028: Reserved							 */
			Luint32 SWCHENAR; /**< 0x002C: SW Channel Enable Reset				*/
			Luint32 u32RM4_DMA_BASE__rsvd5;	 /**< 0x0030: Reserved							 */
			Luint32 CHPRIOS;	/**< 0x0034: Channel Priority Set				 */
			Luint32 u32RM4_DMA_BASE__rsvd6;	 /**< 0x0038: Reserved							 */
			Luint32 CHPRIOR;	/**< 0x003C: Channel Priority Reset				 */
			Luint32 u32RM4_DMA_BASE__rsvd7;	 /**< 0x0040: Reserved							 */
			Luint32 GCHIENAS; /**< 0x0044: Global Channel Interrupt Enable Set	*/
			Luint32 u32RM4_DMA_BASE__rsvd8;	 /**< 0x0048: Reserved							 */
			Luint32 GCHIENAR; /**< 0x004C: Global Channel Interrupt Enable Reset */
			Luint32 u32RM4_DMA_BASE__rsvd9;	 /**< 0x0050: Reserved							 */
			Luint32 DREQASI[8U];/**< 0x0054 - 0x70: DMA Request Assignment Register */
			Luint32 rsvd10[8U];/**< 0x0074 - 0x90: Reserved						*/
			Luint32 PAR[4U];	/**< 0x0094 - 0xA0: Port Assignment Register		*/
			Luint32 rsvd11[4U];/**< 0x00A4 - 0xB0: Reserved						*/
			Luint32 FTCMAP;	 /**< 0x00B4: INTERRUPT__FRAME_TX_COMPLETE Interrupt Mapping Register		 */
			Luint32 rsvd12;	/**< 0x00B8: Reserved							 */
			Luint32 LFSMAP;	 /**< 0x00BC: INTERRUPT__LAST_FRAME_START Interrupt Mapping Register		 */
			Luint32 rsvd13;	/**< 0x00C0: Reserved							 */
			Luint32 HBCMAP;	 /**< 0x00C4: INTERRUPT__HALF_BLOCK_COMPLETE Interrupt Mapping Register		 */
			Luint32 rsvd14;	/**< 0x00C8: Reserved							 */
			Luint32 BTCMAP;	 /**< 0x00CC: INTERRUPT__BLOCK_TX_COMPLETE Interrupt Mapping Register		 */
			Luint32 rsvd15;	/**< 0x00D0: Reserved							 */
			Luint32 BERMAP;	 /**< 0x00D4: BER Interrupt Mapping Register		 */
			Luint32 rsvd16;	/**< 0x00D8: Reserved							 */
			Luint32 FTCINTENAS; /**< 0x00DC: INTERRUPT__FRAME_TX_COMPLETE Interrupt Enable Set			 */
			Luint32 rsvd17;	/**< 0x00E0: Reserved							 */
			Luint32 FTCINTENAR; /**< 0x00E4: INTERRUPT__FRAME_TX_COMPLETE Interrupt Enable Reset			 */
			Luint32 rsvd18;	/**< 0x00E8: Reserved							 */
			Luint32 LFSINTENAS; /**< 0x00EC: INTERRUPT__LAST_FRAME_START Interrupt Enable Set			 */
			Luint32 rsvd19;	/**< 0x00F0: Reserved							 */
			Luint32 LFSINTENAR; /**< 0x00F4: INTERRUPT__LAST_FRAME_START Interrupt Enable Reset			 */
			Luint32 rsvd20;	/**< 0x00F8: Reserved							 */
			Luint32 HBCINTENAS; /**< 0x00FC: INTERRUPT__HALF_BLOCK_COMPLETE Interrupt Enable Set			 */
			Luint32 rsvd21;	/**< 0x0100: Reserved							 */
			Luint32 HBCINTENAR; /**< 0x0104: INTERRUPT__HALF_BLOCK_COMPLETE Interrupt Enable Reset			 */
			Luint32 rsvd22;	/**< 0x0108: Reserved							 */
			Luint32 BTCINTENAS; /**< 0x010C: INTERRUPT__BLOCK_TX_COMPLETE Interrupt Enable Set			 */
			Luint32 rsvd23;	/**< 0x0110: Reserved							 */
			Luint32 BTCINTENAR; /**< 0x0114: INTERRUPT__BLOCK_TX_COMPLETE Interrupt Enable Reset			 */
			Luint32 rsvd24;	/**< 0x0118: Reserved							 */
			Luint32 GINTFLAG; /**< 0x011C: Global Interrupt Flag Register		 */
			Luint32 rsvd25;	/**< 0x0120: Reserved							 */
			Luint32 FTCFLAG;	/**< 0x0124: INTERRUPT__FRAME_TX_COMPLETE Interrupt Flag Register			*/
			Luint32 rsvd26;	/**< 0x0128: Reserved							 */
			Luint32 LFSFLAG;	/**< 0x012C: INTERRUPT__LAST_FRAME_START Interrupt Flag Register			*/
			Luint32 rsvd27;	/**< 0x0130: Reserved							 */
			Luint32 HBCFLAG;	/**< 0x0134: INTERRUPT__HALF_BLOCK_COMPLETE Interrupt Flag Register			*/
			Luint32 rsvd28;	/**< 0x0138: Reserved							 */
			Luint32 BTCFLAG;	/**< 0x013C: INTERRUPT__BLOCK_TX_COMPLETE Interrupt Flag Register			*/
			Luint32 rsvd29;	/**< 0x0140: Reserved							 */
			Luint32 BERFLAG;	/**< 0x0144: BER Interrupt Flag Register			*/
			Luint32 rsvd30;	/**< 0x0148: Reserved							 */
			Luint32 FTCAOFFSET; /**< 0x014C: FTCA Interrupt Channel Offset Register */
			Luint32 LFSAOFFSET; /**< 0x0150: LFSA Interrupt Channel Offset Register */
			Luint32 HBCAOFFSET; /**< 0x0154: HBCA Interrupt Channel Offset Register */
			Luint32 BTCAOFFSET; /**< 0x0158: BTCA Interrupt Channel Offset Register */
			Luint32 BERAOFFSET; /**< 0x015C: BERA Interrupt Channel Offset Register */
			Luint32 FTCBOFFSET; /**< 0x0160: FTCB Interrupt Channel Offset Register */
			Luint32 LFSBOFFSET; /**< 0x0164: LFSB Interrupt Channel Offset Register */
			Luint32 HBCBOFFSET; /**< 0x0168: HBCB Interrupt Channel Offset Register */
			Luint32 BTCBOFFSET; /**< 0x016C: BTCB Interrupt Channel Offset Register */
			Luint32 BERBOFFSET; /**< 0x0170: BERB Interrupt Channel Offset Register */
			Luint32 rsvd31;	/**< 0x0174: Reserved							 */
			Luint32 PTCRL;	 /**< 0x0178: Port Control Register				 */
			Luint32 RTCTRL;	 /**< 0x017C: RAM Test Control Register			 */
			Luint32 DCTRL;	 /**< 0x0180: Debug Control						 */
			Luint32 WPR;		/**< 0x0184: Watch Point Register				 */
			Luint32 WMR;		/**< 0x0188: Watch Mask Register					*/
			Luint32 PAACSADDR; /**< 0x018C:		 */
			Luint32 PAACDADDR; /**< 0x0190:		 */
			Luint32 PAACTC;	 /**< 0x0194:		 */
			Luint32 PBACSADDR; /**< 0x0198: Port B Active Channel Source Address Register	 */
			Luint32 PBACDADDR; /**< 0x019C: Port B Active Channel Destination Address Register */
			Luint32 PBACTC;	 /**< 0x01A0: Port B Active Channel Transfer Count Register	 */
			Luint32 rsvd32;	/**< 0x01A4: Reserved							 */
			Luint32 DMAPCR;	 /**< 0x01A8: Parity Control Register				*/
			Luint32 DMAPAR;	 /**< 0x01AC: DMA Parity Error Address Register	 */
			Luint32 DMAMPCTRL; /**< 0x01B0: DMA Memory Protection Control Register */
			Luint32 DMAMPST;	/**< 0x01B4: DMA Memory Protection Status Register */
			/*****************************************************************************
			*****************************************************************************/
			struct
			{
				Luint32 STARTADD; /**< 0x01B8, 0x01C0, 0x01C8, 0x1D0: DMA Memory Protection Region Start Address Register */
				Luint32 ENDADD; /**< 0x01B8, 0x01C0, 0x01C8, 0x1D0: DMA Memory Protection Region Start Address Register */
			}DMAMPR[4U];
		} RM4_DMA__BASE_T;


		/** @def dmaREG
		* @brief DMA1 Register Frame Pointer
		*
		* This pointer is used by the DMA driver to access the DMA module registers.
		*/
		#define dmaREG ((RM4_DMA__BASE_T *)0xFFFFF000U)

		/** @def BLOCK_TRANSFER
		* @brief Alias name for DMA Block transfer
		* @note This value should be used while setting the DMA control packet
		*/
		#define BLOCK_TRANSFER	 1U

		/** @def FRAME_TRANSFER
		* @brief Alias name for DMA Frame transfer
		* @note This value should be used while setting the DMA control packet
		*/
		#define FRAME_TRANSFER	 0U

		/** @def AUTOINIT_ON
		* @brief Alias name for Auto Initialization ON
		* @note This value should be used while setting the DMA control packet
		*/
		#define AUTOINIT_ON		 1U

		/** @def AUTOINIT_OFF
		* @brief Alias name for Auto Initialization OFF
		* @note This value should be used while setting the DMA control packet
		*/
		#define AUTOINIT_OFF		0U




		/** @def INTERRUPT_ENABLE
		* @brief Alias name for Interrupt enable
		* @note @note This value should be used for API argument @a intenable
		*/
		#define INTERRUPT_ENABLE	1U

		/** @def INTERRUPT_DISABLE
		* @brief Alias name for Interrupt disable
		* @note @note This value should be used for API argument @a intenable
		*/
		#define INTERRUPT_DISABLE	0U


		/** @def DMA_GCTRL_BUSBUSY
		* @brief Bit mask for BUS BUSY in GCTRL Register
		* @note @note This value should be used for API argument @a intenable
		*/
		#define DMA_GCTRL_BUSBUSY	((Luint32)1U << 14U)

		/** @enum dmaREQTYPE
		* @brief DMA TRANSFER Type definitions
		*
		* Used to define DMA transfer type
		*/
		typedef enum
		{
			/**< Hardware trigger */
			DMA_HW = 0x0U,

			/**< Software trigger */
			DMA_SW = 0x1U

		}RM4_DMA__REQUEST_TYPE_T;


		/** @enum RM4_DMA__CHANNEL_E
		* @brief DMA CHANNEL definitions
		*
		* Used to define DMA Channel Number
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum eDMACH
		{
			DMA_CH0 = 0x00U,
			DMA_CH1 = 0x01U,
			DMA_CH2 = 0x02U,
			DMA_CH3 = 0x03U,
			DMA_CH4 = 0x04U,
			DMA_CH5 = 0x05U,
			DMA_CH6 = 0x06U,
			DMA_CH7 = 0x07U,
			DMA_CH8 = 0x08U,
			DMA_CH9 = 0x09U,
			DMA_CH10 = 0x0AU,
			DMA_CH11 = 0x0BU,
			DMA_CH12 = 0x0CU,
			DMA_CH13 = 0x0DU,
			DMA_CH14 = 0x0EU,
			
			#if C_RM4_DMA__MAX_CHANNELS > 16
			DMA_CH15 = 0x0FU,
				DMA_CH16 = 0x10U,
				DMA_CH17 = 0x11U,
				DMA_CH18 = 0x12U,
				DMA_CH19 = 0x13U,
				DMA_CH20 = 0x14U,
				DMA_CH21 = 0x15U,
				DMA_CH22 = 0x16U,
				DMA_CH23 = 0x17U,
				DMA_CH24 = 0x18U,
				DMA_CH25 = 0x19U,
				DMA_CH26 = 0x1AU,
				DMA_CH27 = 0x1BU,
				DMA_CH28 = 0x1CU,
				DMA_CH29 = 0x1DU,
				DMA_CH30 = 0x1EU,
				DMA_CH31 = 0x1FU,
				DMA_CH32 = 0x20U
			#else
			DMA_CH15 = 0x0FU
			#endif
		}RM4_DMA__CHANNEL_E;

		/** @enum dmaACCESS
		* @brief DMA ACESS WIDTH definitions
		*
		* Used to define DMA access width
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum dmaACCESS
		{
		 ACCESS_8_BIT = 0U,
		 ACCESS_16_BIT = 1U,
		 ACCESS_32_BIT = 2U,
		 ACCESS_64_BIT = 3U
		}RM4_DMA__ACCESS_T;


		/** @enum dmaPRIORITY
		* @brief DMA Channel Priority
		*
		* Used to define to which priority queue a DMA channel is assigned to
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum dmaPRIORITY
		{
			PRIORITY_LOW = 0U,
			PRIORITY_HIGH = 1U
		}RM4_DMA__PRIORITY_T;


		/** @enum dmaREGION
		* @brief DMA Memory Protection Region
		*
		* Used to define DMA Memory Protection Region
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum dmaREGION
		{
			DMA_REGION0 = 0U,
			DMA_REGION1 = 1U,
			DMA_REGION2 = 2U,
			DMA_REGION3 = 3U
		}RM4_DMA__REGION_T;


		/** @enum dmaRegionAccess
		* @brief DMA Memory Protection Region Access
		*
		* Used to define access permission of DMA memory protection regions
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum dmaRegionAccess
		{
			FULLACCESS = 0U,
			READONLY = 1U,
			WRITEONLY = 2U,
			NOACCESS = 3U
		}RM4_DMA__REGION_ACCESS_T;


		/** @enum dmaInterrupt
		* @brief DMA Interrupt
		*
		* Used to define DMA interrupts
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef enum dmaInterrupt
		{
			/**< Frame transfer complete Interrupt	 */
			INTERRUPT__FRAME_TX_COMPLETE = 1U,

			/**< Last frame transfer started Interrupt */
			INTERRUPT__LAST_FRAME_START = 2U,

			/**< First half of block complete Interrupt */
			INTERRUPT__HALF_BLOCK_COMPLETE = 3U,

			/**< Block transfer complete Interrupt	 */
			INTERRUPT__BLOCK_TX_COMPLETE = 4U

		}RM4_DMA__INTERRUPT_T;

		/** @struct RM4_DMA__CONTROL_T
		* @brief Interrupt u32Mode globals
		*
		*/
		/*****************************************************************************
		*****************************************************************************/
		typedef struct
		{
			/** 16.2.4.1 Initial Source Address
				This field stores the absolute 32-bit source address of the DMA transfer. */
			Luint32 SADD;

			/** 16.2.4.2 Initial Destination Address
				This field stores the absolute 32-bit destination address of the DMA transfer.*/
			Luint32 DADD;

			/** 16.3.2.4 Channel Control Register (CHCTRL)*/
			Luint32 CHCTRL;

			/* frame count					*/
			Luint32 FRCNT;

			/* element count					*/
			Luint32 ELCNT;

			/** Destination address element index. These bits define the offset to be added to the
				destination address after each element transfer.*/
			Luint32 ELDOFFSET;

			/* Source address element index. These bits define the offset to be added to the source
				address after each element transfer.			*/
			Luint32 ELSOFFSET;

			/* frame detination offset		 */
			Luint32 FRDOFFSET;

			/* frame source offset			 */
			Luint32 FRSOFFSET;

			/* dma port						 */
			Luint32 PORTASGN;

			/* read element size				*/
			Luint32 RDSIZE;

			/* write element size			 */
			Luint32 WRSIZE;

			/* trigger type - frame/block	 */
			Luint32 TTYPE;

			/* addresssing u32Mode for source	 */
			Luint32 ADDMODERD;

			/* addresssing u32Mode for destination */
			Luint32 ADDMODEWR;

			/* auto-init u32Mode				 */
			Luint32 AUTOINIT;

			/* next ctrl packet trigger		 */
			Luint32 COMBO;
		} RM4_DMA__CONTROL_T;

		/*****************************************************************************
		*****************************************************************************/
		typedef volatile struct
		{

			/*****************************************************************************
			*****************************************************************************/
			 struct									 /* 0x000-0x400 */
			 {
				//16.2.4.1 Initial Source Address
				//This field stores the absolute 32-bit source address of the DMA transfer.
				Luint32 ISADDR;

				//16.2.4.2 Initial Destination Address
				//This field stores the absolute 32-bit destination address of the DMA transfer.
				Luint32 IDADDR;

				//16.2.4.3 Initial Transfer Count
				//The transfer count field is composed of two parts. The frame transfer count value and the element transfer
				//count value. Each count value is 13 bits wide. As a Single Block transfer maximum of 512 Mbytes of data
				//can be transferred. Element count and frame count are programmed according to the source data
				//structure.
				//The total transfer size is calculated as stated below:
				//Tsz = Ersz * Etc * Ftc
				//where
				//Tsz = Total Transfer Size
				//Ersz = Read Element Size
				//Etc = Element Transfer Count
				//Ftc = Frame Transfer Count
				Luint32 ITCOUNT;


				Luint32 u32RM4_DMA_PCP__rsvd1;

				//16.2.4.4 Channel Configuration Word
				//The channel configuration defines the following individual parameters
				//* Read element size
				//* Write element size
				//* Trigger type (frame or block)
				//* Addressing u32Mode for source
				//* Addressing u32Mode for destination
				//* Auto-initiation u32Mode
				//* Next control packet to be triggered at control packet finish (Channel Chaining)
				Luint32 CHCTRL;

				//16.2.4.5 Element/Frame Index Pointer
				//There are 4 index pointers that allow the creation of different types of buffers in RAM and address
				//registers in a structured manner: an element index pointer for source and destination and a frame index
				//pointer for source and destination.
				//The element index pointer for source and/or destination defines the offset to be added after each element
				//transfer to the source and/or destination address. The frame index pointer for source and/or destination
				//defines the offset to be added to the source and/or destination address after the element count reaches
				//zero. The element and frame index pointers must be defined in terms of the number of bytes of offset. The
				//DMA controller does not adjust the element/frame index number according to the element size. An index
				//of 2 means increment the address by 2 and not by 16 when the element size is 64 bits.
				Luint32 EIOFF;

				Luint32 FIOFF;

				Luint32 u32RM4_DMA_PCP__rsvd2;
			 }PCP[32U];

			/*****************************************************************************
			*****************************************************************************/
			 struct									 /* 0x400-0x800 */
			 {
				 Luint32 res[256U];
			 } RESERVED;

			/*****************************************************************************
			*****************************************************************************/
			 struct									 /* 0x800-0xA00 */
			 {
				//16.2.4.6 Current Source Address
				//The current source address field contains the current working source address during a DMA transaction.
				//The current source address is incremented during post increment addressing u32Mode or indexing u32Mode.
				Luint32 CSADDR;

				//16.2.4.7 Current Destination Address
				//The current destination address field contains the current working destination address during a DMA
				//transaction. The current destination address is incremented during post-increment addressing u32Mode or
				//indexing u32Mode.
				Luint32 CDADDR;

				//16.2.4.8 Current Transfer Count
				//The current transfer count stores the remaining number of elements to be transferred in a block. It is
				//decremented by one for each element read from the source location.
				Luint32 CTCOUNT;

				Luint32 u32RM4_DMA_RAMBASE__rsvd3;
			 }WCP[32U];

		} RM4_DMA__RAMBASE_T;

		#define dmaRAMREG ((RM4_DMA__RAMBASE_T *)0xFFF80000U)


#endif /* RM4_DMA__PRIVATE_H_ */
