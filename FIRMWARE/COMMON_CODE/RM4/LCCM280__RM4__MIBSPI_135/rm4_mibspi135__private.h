/**
 * @file		rm4_mibspi135__private.h
 * @brief		Private structures for SPI135
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM280R0.FILE.004
 */

#ifndef _RM4_MIBSPI135_PRIVATE_H_
#define _RM4_MIBSPI135_PRIVATE_H_


	/* Mibspi Register Frame Definition */
	/** @struct mibspiBase
	* @brief MIBSPI Register Definition
	*
	* This structure is used to access the MIBSPI module registers.
	*/
	/** @typedef mibspiBASE_t
	* @brief MIBSPI Register Frame Type Definition
	*
	* This type is used to access the MIBSPI Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct
	{
		Luint32 GCR0;	 /**< 0x0000: Global Control 0 */
		Luint32 GCR1;	 /**< 0x0004: Global Control 1 */
		Luint32 INT0;	 /**< 0x0008: Interrupt Register */
		Luint32 LVL;	 /**< 0x000C: Interrupt Level */
		Luint32 FLG;	 /**< 0x0010: Interrupt flags */
		Luint32 PC0;	 /**< 0x0014: Function Pin Enable */
		Luint32 PC1;	 /**< 0x0018: Pin Direction */
		Luint32 PC2;	 /**< 0x001C: Pin Input Latch */
		Luint32 PC3;	 /**< 0x0020: Pin Output Latch */
		Luint32 PC4;	 /**< 0x0024: Output Pin Set */
		Luint32 PC5;	 /**< 0x0028: Output Pin Clr */
		Luint32 PC6;	 /**< 0x002C: Open Drain Output Enable */
		Luint32 PC7;	 /**< 0x0030: Pullup/Pulldown Disable */
		Luint32 PC8;	 /**< 0x0034: Pullup/Pulldown Selection */
		Luint32 DAT0;	 /**< 0x0038: Transmit Data */
		Luint32 DAT1;	 /**< 0x003C: Transmit Data with Format and Chip Select */
		Luint32 BUF;	 /**< 0x0040: Receive Buffer */
		Luint32 EMU;	 /**< 0x0044: Emulation Receive Buffer */
		Luint32 DELAY;	 /**< 0x0048: Delays */
		Luint32 DEF;	 /**< 0x004C: Default Chip Select */
		Luint32 FMT0;	 /**< 0x0050: Data Format 0 */
		Luint32 FMT1;	 /**< 0x0054: Data Format 1 */
		Luint32 FMT2;	 /**< 0x0058: Data Format 2 */
		Luint32 FMT3;	 /**< 0x005C: Data Format 3 */
		Luint32 INTVECT0;	 /**< 0x0060: Interrupt Vector 0 */
		Luint32 INTVECT1;	 /**< 0x0064: Interrupt Vector 1 */
		Luint32 SRSEL;	 /**< 0x0068: Slew Rate Select */
		Luint32 PMCTRL;	 /**< 0x006C: Parallel Mode Control */
		Luint32 MIBSPIE;	 /**< 0x0070: Multi-buffer Mode Enable */
		Luint32 TGITENST;	 /**< 0x0074: TG Interrupt Enable Set */
		Luint32 TGITENCR;	 /**< 0x0078: TG Interrupt Enable Clear */
		Luint32 TGITLVST;	 /**< 0x007C: Transfer Group Interrupt Level Set */
		Luint32 TGITLVCR;	 /**< 0x0080: Transfer Group Interrupt Level Clear */
		Luint32 TGINTFLG;	 /**< 0x0084: Transfer Group Interrupt Flag */
		Luint32 rsvd1[2U];	 /**< 0x0088: Reserved */
		Luint32 TICKCNT;	 /**< 0x0090: Tick Counter */
		Luint32 LTGPEND;	 /**< 0x0090: Last TG End Pointer */
		Luint32 TGCTRL[16U];	/**< 0x0098 - 0x00D4: Transfer Group Control */
		Luint32 DMACTRL[8U];	/**< 0x00D8 - 0x00F4: DMA Control */
		Luint32 DMACOUNT[8U]; /**< 0x00F8 - 0x0114: DMA Count */
		Luint32 DMACNTLEN;	/**< 0x0118 - 0x0114: DMA Control length */
		Luint32 rsvd2;	 /**< 0x011C: Reserved */
		Luint32 UERRCTRL;	 /**< 0x0120: Multi-buffer RAM Uncorrectable Parity Error Control */
		Luint32 UERRSTAT;	 /**< 0x0124: Multi-buffer RAM Uncorrectable Parity Error Status */
		Luint32 UERRADDRRX;	 /**< 0x0128: RXRAM Uncorrectable Parity Error Address */
		Luint32 UERRADDRTX;	 /**< 0x012C: TXRAM Uncorrectable Parity Error Address */
		Luint32 RXOVRN_BUF_ADDR; /**< 0x0130: RXRAM Overrun Buffer Address */
		Luint32 IOLPKTSTCR;	 /**< 0x0134: IO loopback */
		Luint32 EXT_PRESCALE1;	/**< 0x0138: */
		Luint32 EXT_PRESCALE2;	/**< 0x013C: */
	} RM4_MIBSPI135__BASE_T;


	/** @def mibspiREG3
	* @brief MIBSPI3 Register Frame Pointer
	*
	* This pointer is used by the MIBSPI driver to access the mibspi module registers.
	*/
	#define mibspiREG1 ((RM4_MIBSPI135__BASE_T *)0xFFF7F400U)
	#define mibspiREG3 ((RM4_MIBSPI135__BASE_T *)0xFFF7F800U)
	#define mibspiREG5 ((RM4_MIBSPI135__BASE_T *)0xFFF7FC00U)


	/** @struct mibspiRamBase
	* @brief MIBSPI Buffer RAM Definition
	*
	* This structure is used to access the MIBSPI buffer memory.
	*/
	/** @typedef mibspiRAM_t
	* @brief MIBSPI RAM Type Definition
	*
	* This type is used to access the MIBSPI RAM.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct spi3R
	{
		struct
		{
			Luint16 data; /**< tx buffer data */
			Luint16 control; /**< tx buffer control */
		} tx[128];
		struct
		{
			Luint16 data; /**< rx buffer data */
			Luint16 flags; /**< rx buffer flags */
		} rx[128];
	} RM4_MIBSPI135__RAM_T;



	/** @def mibspiRAM3
	* @brief MIBSPI3 Buffer RAM Pointer
	*
	* This pointer is used by the MIBSPI driver to access the mibspi buffer memory.
	*/
	#define mibspiRAM1 ((RM4_MIBSPI135__RAM_T *)0xFF0E0000U)
	#define mibspiRAM3 ((RM4_MIBSPI135__RAM_T *)0xFF0C0000U)
	#define mibspiRAM5 ((RM4_MIBSPI135__RAM_T *)0xFF0A0000U)

	/** @def mibspiPARRAM3
	* @brief MIBSPI3 Buffer RAM PARITY Pointer
	*
	* This pointer is used by the MIBSPI driver to access the mibspi buffer memory.
	*/
	#define mibspiPARRAM1 (*(volatile Luint32 *)(0xFF0E0000U + 0x00000400U))
	#define mibspiPARRAM3 (*(volatile Luint32 *)(0xFF0C0000U + 0x00000400U))
	#define mibspiPARRAM5 (*(volatile Luint32 *)(0xFF0A0000U + 0x00000400U))



#endif //_RM4_SPI3_PRIVATE_H_
