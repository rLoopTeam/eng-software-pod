/**
 * @file		RM4_SPI24__PRIVATE.H
 * @brief		Private types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM108R0.FILE.004
 */

#ifndef _RM4_SPI2_PRIVATE_H_
#define _RM4_SPI2_PRIVATE_H_

	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct spiBase
	{
	    Luint32  GCR0;                 /**< 0x0000: Global Control 0 */
	    Luint32  GCR1;                 /**< 0x0004: Global Control 1 */
	    Luint32  INT0;                 /**< 0x0008: Interrupt Register */
	    Luint32  LVL;                  /**< 0x000C: Interrupt Level */
	    Luint32  FLG;                  /**< 0x0010: Interrupt flags */
	    Luint32  PC0;                  /**< 0x0014: Function Pin Enable */
	    Luint32  PC1;                  /**< 0x0018: Pin Direction */
	    Luint32  PC2;                  /**< 0x001C: Pin Input Latch */
	    Luint32  PC3;                  /**< 0x0020: Pin Output Latch */
	    Luint32  PC4;                  /**< 0x0024: Output Pin Set */
	    Luint32  PC5;                  /**< 0x0028: Output Pin Clr */
	    Luint32  PC6;                  /**< 0x002C: Open Drain Output Enable */
	    Luint32  PC7;                  /**< 0x0030: Pullup/Pulldown Disable */
	    Luint32  PC8;                  /**< 0x0034: Pullup/Pulldown Selection */
	    Luint32  DAT0;                 /**< 0x0038: Transmit Data */
	    Luint32  DAT1;                 /**< 0x003C: Transmit Data with Format and Chip Select */
	    Luint32  BUF;                  /**< 0x0040: Receive Buffer */
	    Luint32  EMU;                  /**< 0x0044: Emulation Receive Buffer */
	    Luint32  DELAY;                /**< 0x0048: Delays */
	    Luint32  DEF;                  /**< 0x004C: Default Chip Select */
	    Luint32  FMT0;                 /**< 0x0050: Data Format 0 */
	    Luint32  FMT1;                 /**< 0x0054: Data Format 1 */
	    Luint32  FMT2;                 /**< 0x0058: Data Format 2 */
	    Luint32  FMT3;                 /**< 0x005C: Data Format 3 */
	    Luint32  INTVECT0;             /**< 0x0060: Interrupt Vector 0 */
	    Luint32  INTVECT1;             /**< 0x0064: Interrupt Vector 1 */
	    Luint32  RESERVED[51U];        /**< 0x0068 to 0x0130: Reserved */
	    Luint32  IOLPKTSTCR;           /**< 0x0134: IO loopback */
	} RM4_SPI24__BASE_T;



	#define spiREG2 ((RM4_SPI24__BASE_T *)0xFFF7F600U)
	#define spiREG4 ((RM4_SPI24__BASE_T *)0xFFF7FA00U)

	#define spiPORT2 ((gioPORT_t *)0xFFF7F618U)
	#define spiPORT4 ((gioPORT_t *)0xFFF7FA18U)


#endif //_RM4_SPI2_PRIVATE_H_
