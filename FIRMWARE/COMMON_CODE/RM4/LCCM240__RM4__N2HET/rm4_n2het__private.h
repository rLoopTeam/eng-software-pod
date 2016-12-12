/**
 * @file		RM4_N2HET__PRIVATE.H
 * @brief		Private defines for RM4_N2HET
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @st_fileID	LCCM240R0.FILE.004
 */
 
#ifndef _RM4_HET_PRIVATE_H_
#define _RM4_HET_PRIVATE_H_

	/** Timestamping Options*/
	typedef enum
	{
		/** Rising edges only */
		TIMESTAMP_TYPE__RISING = 0U,

		/** Falling edges only */
		TIMESTAMP_TYPE__FALLING,

		/** Both edges */
		TIMESTAMP_TYPE__BOTH,

	}RM4_N2HET__TIMESTAMP_T;

	/** Capture program types */
	typedef enum
	{
		/** Count low pulse duration on selected pin */
		CAP_TYPE__FALL2RISE = 0U,
		/** Count high pulse duration on selected pin */
		CAP_TYPE__RISE2FALL,
		/** Count period between falling edges on selected pin */
		CAP_TYPE__FALL2FALL,
		/** Count period between rising edges  */
		CAP_TYPE__RISE2RISE

	}RM4_N2HET__CAPTURE_T;


	/** Event coding for ECNT instruction */
	typedef enum
	{
		EDGE_TYPE__NAF = 0U,

		/** Falling edge on selected pin */
		EDGE_TYPE__FALLING = 1U,

		/** Rising edge on selected pin */
		EDGE_TYPE__RISING = 2U,

		/** Both rising and falling edges */
		EDGE_TYPE__BOTH = 3U

	}RM4_N2HET__EDGE_EDGE_T;


	/** This type is used to access the HET Registers. */
	typedef volatile struct hetBase
	{
		Luint32 GCR;	 /**< 0x0000: Global control register			 */
		Luint32 PFR;	 /**< 0x0004: Prescale factor register			 */
		Luint32 ADDR;	/**< 0x0008: Current address register			 */
		Luint32 OFF1;	/**< 0x000C: Interrupt offset register 1		 */
		Luint32 OFF2;	/**< 0x0010: Interrupt offset register 2		 */
		Luint32 INTENAS; /**< 0x0014: Interrupt enable set register		*/
		Luint32 INTENAC; /**< 0x0018: Interrupt enable clear register	 */
		Luint32 EXC1;	/**< 0x001C: Exception control register 1		 */
		Luint32 EXC2;	/**< 0x0020: Exception control register 2		 */
		Luint32 PRY;	 /**< 0x0024: Interrupt priority register		 */
		Luint32 FLG;	 /**< 0x0028: Interrupt flag register			 */
		Luint32 AND;	 /**< 0x002C: AND share control register		 */
		Luint32 u32RM4_HET__rsvd1; /**< 0x0030: Reserved							 */
		Luint32 HRSH;	/**< 0x0034: High resolution share register		*/
		Luint32 XOR;	 /**< 0x0038: XOR share register				 */
		Luint32 REQENS; /**< 0x003C: Request enable set register		 */
		Luint32 REQENC; /**< 0x0040: Request enable clear register		*/
		Luint32 REQDS; /**< 0x0044: Request destination select register */
		Luint32 u32RM4_HET__rsvd2; /**< 0x0048: Reserved							 */
		Luint32 DIR;	 /**< 0x004C: Direction register				 */
		Luint32 DIN;	 /**< 0x0050: Data input register				 */
		Luint32 DOUT;	/**< 0x0054: Data output register				 */
		Luint32 DSET;	/**< 0x0058: Data output set register			 */
		Luint32 DCLR;	/**< 0x005C: Data output clear register		 */
		Luint32 PDR;	 /**< 0x0060: Open drain register				 */
		Luint32 PULDIS; /**< 0x0064: Pull disable register				*/
		Luint32 PSL;	 /**< 0x0068: Pull select register				 */
		Luint32 u32RM4_HET__rsvd3; /**< 0x006C: Reserved							 */
		Luint32 u32RM4_HET__rsvd4; /**< 0x0070: Reserved							 */
		Luint32 PCR; /**< 0x0074: Parity control register			 */
		Luint32 PAR;	 /**< 0x0078: Parity address register			 */
		Luint32 PPR;	 /**< 0x007C: Parity pin select register		 */
		Luint32 SFPRLD; /**< 0x0080: Suppression filter preload register */
		Luint32 SFENA; /**< 0x0084: Suppression filter enable register */
		Luint32 u32RM4_HET__rsvd5; /**< 0x0088: Reserved							 */
		Luint32 LBPSEL; /**< 0x008C: Loop back pair select register	 */
		Luint32 LBPDIR; /**< 0x0090: Loop back pair direction register	*/
		Luint32 PINDIS; /**< 0x0094: Pin disable register				 */
	} RM4_HET__BASE_T;


	/** @def hetREG1
	* @brief HET Register Frame Pointer
	*
	* This pointer is used by the HET driver to access the het module registers.
	*/
	#define hetREG1 ((RM4_HET__BASE_T *)0xFFF7B800U)


	/** @def hetPORT1
	* @brief HET GIO Port Register Pointer
	*
	* Pointer used by the GIO driver to access I/O PORT of HET1
	* (use the GIO drivers to access the port pins).
	*/
	#define hetPORT1 ((gioPORT_t *)0xFFF7B84CU)


	/** @def hetREG2
	* @brief HET2 Register Frame Pointer
	*
	* This pointer is used by the HET driver to access the het module registers.
	*/
	#define hetREG2 ((RM4_HET__BASE_T *)0xFFF7B900U)


	/** @def hetPORT2
	* @brief HET2 GIO Port Register Pointer
	*
	* Pointer used by the GIO driver to access I/O PORT of HET2
	* (use the GIO drivers to access the port pins).
	*/
	#define hetPORT2 ((gioPORT_t *)0xFFF7B94CU)

	#define hetRAM1 ((RM4_HET__RAMBASE_T *)0xFF460000U)

	#define hetRAM2 ((RM4_HET__RAMBASE_T *)0xFF440000U)

	#define NHET1RAMPARLOC	(*(volatile Luint32 *)0xFF462000U)
	#define NHET1RAMLOC		(*(volatile Luint32 *)0xFF460000U)

	#define NHET2RAMPARLOC	(*(volatile Luint32 *)0xFF442000U)
	#define NHET2RAMLOC		(*(volatile Luint32 *)0xFF440000U)


	/* htu Register Frame Definition */
	/** @struct htuBase
	* @brief HTU Base Register Definition
	*
	* This structure is used to access the HTU module registers.
	*/
	/** @typedef htuBASE_t
	* @brief HTU Register Frame Type Definition
	*
	* This type is used to access the HTU Registers.
	*/
	typedef volatile struct htuBase
	{
		Luint32 GC;				/** 0x00 */
		Luint32 CPENA;			/** 0x04 */
		Luint32 BUSY0;			/** 0x08 */
		Luint32 BUSY1;			/** 0x0C */
		Luint32 BUSY2;			/** 0x10 */
		Luint32 BUSY3;			/** 0x14 */
		Luint32 ACPE;			/** 0x18 */
		Luint32 u32RM4_HTUBASE__rsvd1;			/** 0x1C */
		Luint32 RLBECTRL;		/** 0x20 */
		Luint32 BFINTS;			/** 0x24 */
		Luint32 BFINTC;			/** 0x28 */
		Luint32 INTMAP;			/** 0x2C */
		Luint32 u32RM4_HTUBASE__rsvd2; 			/** 0x30 */
		Luint32 INTOFF0;			/** 0x34 */
		Luint32 INTOFF1;			/** 0x38 */
		Luint32 BIM;				/** 0x3C */
		Luint32 RLOSTFL;			/** 0x40 */
		Luint32 BFINTFL;			/** 0x44 */
		Luint32 BERINTFL;		/** 0x48 */
		Luint32 MP1S;			/** 0x4C */
		Luint32 MP1E;			/** 0x50 */
		Luint32 DCTRL;			/** 0x54 */
		Luint32 WPR;				/** 0x58 */
		Luint32 WMR;				/** 0x5C */
		Luint32 ID;				/** 0x60 */
		Luint32 PCR;				/** 0x64 */
		Luint32 PAR;				/** 0x68 */
		Luint32 u32RM4_HTUBASE__rsvd3; 			/** 0x6C */
		Luint32 MPCS;			/** 0x70 */
		Luint32 MP0S;			/** 0x74 */
		Luint32 MP0E;			/** 0x78 */
	} htuBASE_t;

	typedef volatile struct htudcp
	{
		Luint32 IFADDRA;
		Luint32 IFADDRB;
		Luint32 IHADDRCT;
		Luint32 ITCOUNT;
	} htudcp_t;

	typedef volatile struct htucdcp
	{
		Luint32 CFADDRA;
		Luint32 CFADDRB;
		Luint32 CFCOUNT;
		Luint32 u32RM4_HTUCDCP__rsvd4;
	} htucdcp_t;

	#define htuREG1 ((htuBASE_t *)0xFFF7A400U)
	#define htuREG2 ((htuBASE_t *)0xFFF7A500U)

	#define htuDCP1 ((htudcp_t *)0xFF4E0000U)
	#define htuDCP2 ((htudcp_t *)0xFF4C0000U)

	#define htuCDCP1 ((htucdcp_t *)0xFF4E0100U)
	#define htuCDCP2 ((htucdcp_t *)0xFF4C0100U)

	/* USER CODE BEGIN (1) */
	/* USER CODE END */


	#define HTU1PARLOC		(*(volatile Luint32 *)0xFF4E0200U)
	#define HTU2PARLOC		(*(volatile Luint32 *)0xFF4C0200U)

	#define HTU1RAMLOC		(*(volatile Luint32 *)0xFF4E0000U)
	#define HTU2RAMLOC		(*(volatile Luint32 *)0xFF4C0000U)

	/** To be used in the register select part of the instruction */
	typedef enum
	{
		N2HET_PROG__REG_A = 0U,
		N2HET_PROG__REG_B = 1U,
		N2HET_PROG__REG_T = 2U,
		N2HET_PROG__REG_NONE = 3U

	}RM4_N2HET_PROG__REGISTER_SELECT_T;

	/*
	Action
	(4 Action Option) Either sets, clears, pulse high or pulse low on the pin. Set/clear are
	single pin actions, pulse high/low include the opposite pin action.
	Default: Clear
	 */
	typedef enum
	{
		/** Set low on match */
		N2HET_PROG__ACTION_CLEAR = 0U,

		/** Set high on match */
		N2HET_PROG__ACTION_SET = 1U,

		/** Set low on match + reset to high on Z=1 (opposite action) */
		N2HET_PROG__ACTION_PULSE_LO = 2U,

		/** Set high on match + reset to low on Z=1 (opposite action) */
		N2HET_PROG__ACTION_PULSE_HI = 3U

	}RM4_N2HET_PROG__ACTION_T;


	/* Table 20-63. Move Type Encoding Selection */
	typedef enum
	{
		/** Immediate data field Register A, B, or T
		 * 1 Cycle */
		N2HET_PROG__IM_TO_REG = 0U,

		/** Immediate data field Remote data field & register A, B, or T */
		N2HET_PROG__IMTOREG_AND_REMOTE = 1U,

		/** Register A, B, or T Remote data field */
		N2HET_PROG__REG_TO_REMOTE = 2U,

		/** Remote data field Register A, B, or T
		 * 2 Cycles */
		N2HET_PROG__REMOTE_TO_REG = 3U

	}RM4_N2HET_PROG__MOVE_TYPE_T;

#endif //_RM4_HET_PRIVATE_H_

