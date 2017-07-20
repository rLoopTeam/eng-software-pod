/**
 * @file		rm4_sci__provate.h
 * @brief		Private RM4 strcuts
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM282R0.FILE.004
 */


#ifndef RM4_SCI__PRIVATE_H_
#define RM4_SCI__PRIVATE_H_

	typedef volatile struct sciBase
	{
		Luint32 GCR0;          /**< 0x0000 Global Control Register 0 */
		Luint32 GCR1;          /**< 0x0004 Global Control Register 1 */
		Luint32 rsdv1;         /**< 0x0008 Global Control Register 2 */
		Luint32 SETINT;       /**< 0x000C Set Interrupt Enable Register */
		Luint32 CLEARINT;      /**< 0x0010 Clear Interrupt Enable Register */
		Luint32 SETINTLVL;    /**< 0x0014 Set Interrupt Level Register */
		Luint32 CLEARINTLVL;   /**< 0x0018 Set Interrupt Level Register */
		Luint32 FLR;           /**< 0x001C Interrupt Flag Register */
		Luint32 INTVECT0;      /**< 0x0020 Interrupt Vector Offset 0 */
		Luint32 INTVECT1;      /**< 0x0024 Interrupt Vector Offset 1 */
		Luint32 FORMAT;        /**< 0x0028 Format Control Register */
		Luint32 BRS;           /**< 0x002C Baud Rate Selection Register */
		Luint32 ED;            /**< 0x0030 Emulation Register */
		Luint32 RD;            /**< 0x0034 Receive Data Buffer */
		Luint32 TD;            /**< 0x0038 Transmit Data Buffer */
		Luint32 PIO0;          /**< 0x003C Pin Function Register */
		Luint32 PIO1;          /**< 0x0040 Pin Direction Register */
		Luint32 PIO2;          /**< 0x0044 Pin Data In Register */
		Luint32 PIO3;          /**< 0x0048 Pin Data Out Register */
		Luint32 PIO4;          /**< 0x004C Pin Data Set Register */
		Luint32 PIO5;          /**< 0x0050 Pin Data Clr Register */
		Luint32 PIO6;          /**< 0x0054: Pin Open Drain Output Enable Register */
		Luint32 PIO7;          /**< 0x0058: Pin Pullup/Pulldown Disable Register */
		Luint32 PIO8;          /**< 0x005C: Pin Pullup/Pulldown Selection Register */
		Luint32 rsdv2[12U];    /**< 0x0060: Reserved                               */
		Luint32 IODFTCTRL;     /**< 0x0090: I/O Error Enable Register */
	} RM4_SCI__BASE_T;





    #if C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 0U

		/** @def sciREG
		*   @brief  Register Frame Pointer
		*
		*   This pointer is used by the SCI driver to access the sci module registers.
		*/
		#define sciREG ((RM4_SCI__BASE_T *)0xFFF7E500U)


		/** @def sciPORT
		*   @brief SCI GIO Port Register Pointer
		*
		*   Pointer used by the GIO driver to access I/O PORT of SCI
		*   (use the GIO drivers to access the port pins).
		*/
		#define sciPORT ((gioPORT_t *)0xFFF7E540U)


		/** @def scilinREG
		*   @brief SCILIN (LIN - Compatibility Mode)  Register Frame Pointer
		*
		*   This pointer is used by the SCI driver to access the sci module registers.
		*/
		#define scilinREG ((RM4_SCI__BASE_T *)0xFFF7E400U)


		/** @def scilinPORT
		*   @brief SCILIN (LIN - Compatibility Mode)  Register Frame Pointer
		*
		*   Pointer used by the GIO driver to access I/O PORT of LIN
		*   (use the GIO drivers to access the port pins).
		*/
		#define scilinPORT ((gioPORT_t *)0xFFF7E440U)
	#else

		//1
		#define sciREG1 ((RM4_SCI__BASE_T *)0xFFF7E400U)
		#define sciPORT1 ((gioPORT_t *)0xFFF7E440U)

		//2
		#define sciREG2 ((RM4_SCI__BASE_T *)0xFFF7E600U)
		#define sciPORT2 ((gioPORT_t *)0xFFF7E640U)

		//3
		#define sciREG3 ((RM4_SCI__BASE_T *)0xFFF7E500U)
		#define sciPORT3 ((gioPORT_t *)0xFFF7E540U)

		//4
		#define sciREG4 ((RM4_SCI__BASE_T *)0xFFF7E700U)
		#define sciPORT4 ((gioPORT_t *)0xFFF7E740U)

    #endif

#endif /* RM4_SCI__PRIVATE_H_ */
