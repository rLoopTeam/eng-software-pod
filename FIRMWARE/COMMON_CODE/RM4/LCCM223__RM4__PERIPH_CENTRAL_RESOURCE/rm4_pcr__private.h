/**
 * @file		RM4_PCR__PRIVATE.H
 * @brief		Private defs for the PCR.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM223R0.FILE.003
 */


#ifndef RM4_PC4__PRIVATE_H_
#define RM4_PC4__PRIVATE_H_

	/* Pcr Register Frame Definition */
	/** @struct pcrBase
	*   @brief Pcr Register Frame Definition
	*
	*   This type is used to access the Pcr Registers.
	*/
	/** @typedef pcrBASE_t
	*   @brief PCR Register Frame Type Definition
	*
	*   This type is used to access the PCR Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
#if C_LOCALDEF__SYSTEM__USE_ON_RM57 == 1U
	typedef volatile struct pcrBase
	{
		Luint32 PMPROTSET0;    /* 0x0000 */
		Luint32 PMPROTSET1;    /* 0x0004 */
		Luint32 rsvd1[2U];     /* 0x0008 */
		Luint32 PMPROTCLR0;    /* 0x0010 */
		Luint32 PMPROTCLR1;    /* 0x0014 */
		Luint32 rsvd2[2U];     /* 0x0018 */
		Luint32 PPROTSET0;     /* 0x0020 */
		Luint32 PPROTSET1;     /* 0x0024 */
		Luint32 PPROTSET2;     /* 0x0028 */
		Luint32 PPROTSET3;     /* 0x002C */
		Luint32 rsvd3[4U];     /* 0x0030 */
		Luint32 PPROTCLR0;     /* 0x0040 */
		Luint32 PPROTCLR1;     /* 0x0044 */
		Luint32 PPROTCLR2;     /* 0x0048 */
		Luint32 PPROTCLR3;     /* 0x004C */
		Luint32 rsvd4[4U];     /* 0x0050 */
		Luint32 PCSPWRDWNSET0; /* 0x0060 */
		Luint32 PCSPWRDWNSET1; /* 0x0064 */
		Luint32 rsvd5[2U];     /* 0x0068 */
		Luint32 PCSPWRDWNCLR0; /* 0x0070 */
		Luint32 PCSPWRDWNCLR1; /* 0x0074 */
		Luint32 rsvd6[2U];     /* 0x0078 */
		Luint32 PSPWRDWNSET0;  /* 0x0080 */
		Luint32 PSPWRDWNSET1;  /* 0x0084 */
		Luint32 PSPWRDWNSET2;  /* 0x0088 */
		Luint32 PSPWRDWNSET3;  /* 0x008C */
		Luint32 rsvd7[4U];     /* 0x0090 */
		Luint32 PSPWRDWNCLR0;  /* 0x00A0 */
		Luint32 PSPWRDWNCLR1;  /* 0x00A4 */
		Luint32 PSPWRDWNCLR2;  /* 0x00A8 */
		Luint32 PSPWRDWNCLR3;  /* 0x00AC */
		Luint32 rsvd8[4U];     /* 0x00B0 */
		Luint32 PDPWRDWNSET;   /* 0x00C0 */
		Luint32 PDPWRDWNCLR;   /* 0x00C4 */
		Luint32 rsvd9[78U];    /* 0x00C8 */
		Luint32 MSTIDWRENA;    /* 0x0200 */
		Luint32 MSTIDENA;      /* 0x0204 */
		Luint32 MSTIDDIAGCTRL; /* 0x0208 */
		Luint32 rsvd10[61U];   /* 0x020C */
		struct
		{
			Luint32 PSxMSTID_L;
			Luint32 PSxMSTID_H;
		}PSxMSTID[32];            /* 0x0300 */
		struct
		{
			Luint32 PPSxMSTID_L;
			Luint32 PPSxMSTID_H;
		}PPSxMSTID[8];            /* 0x0400 */
		struct
		{
			Luint32 PPSExMSTID_L;
			Luint32 PPSExMSTID_H;
		}PPSExMSTID[32];            /* 0x0440 */
		Luint32 PCSxMSTID[32];    /* 0x0540 */
		Luint32 PPCSxMSTID[8];    /* 0x05C0 */
	} pcrBASE_t;

	/** @def pcrREG1
	*   @brief Pcr1 Register Frame Pointer
	*
	*   This pointer is used by the system driver to access the Pcr1 registers.
	*/
	#define pcrREG1 ((pcrBASE_t *)0xFFFF1000U)

	//RM48 backward
	#define pcrREG ((pcrBASE_t *)0xFFFF1000U)

	/** @def pcrREG2
	*   @brief Pcr2 Register Frame Pointer
	*
	*   This pointer is used by the system driver to access the Pcr2 registers.
	*/
	#define pcrREG2 ((pcrBASE_t *)0xFCFF1000U)

	/** @def pcrREG3
	*   @brief Pcr3 Register Frame Pointer
	*
	*   This pointer is used by the system driver to access the Pcr3 registers.
	*/
	#define pcrREG3 ((pcrBASE_t *)0xFFF78000U)

#else
	typedef volatile struct pcrBase
	{
		Luint32 PMPROTSET0;    /* 0x0000 */
		Luint32 PMPROTSET1;    /* 0x0004 */
		Luint32   u32PCR_rsvd1[2U];    /* 0x0008 */
		Luint32 PMPROTCLR0;    /* 0x0010 */
		Luint32 PMPROTCLR1;    /* 0x0014 */
		Luint32    u32PCR_rsvd2[2U];    /* 0x0018 */
		Luint32 PPROTSET0;     /* 0x0020 */
		Luint32 PPROTSET1;     /* 0x0024 */
		Luint32 PPROTSET2;     /* 0x0028 */
		Luint32 PPROTSET3;     /* 0x002C */
		Luint32    u32PCR_rsvd3[4U];    /* 0x0030 */
		Luint32 PPROTCLR0;     /* 0x0040 */
		Luint32 PPROTCLR1;     /* 0x0044 */
		Luint32 PPROTCLR2;     /* 0x0048 */
		Luint32 PPROTCLR3;     /* 0x004C */
		Luint32    u32PCR_rsvd4[4U];    /* 0x0050 */
		Luint32 PCSPWRDWNSET0; /* 0x0060 */
		Luint32 PCSPWRDWNSET1; /* 0x0064 */
		Luint32    u32PCR_rsvd5[2U];    /* 0x0068 */
		Luint32 PCSPWRDWNCLR0; /* 0x0070 */
		Luint32 PCSPWRDWNCLR1; /* 0x0074 */
		Luint32    u32PCR_rsvd6[2U];    /* 0x0078 */
		Luint32 PSPWRDWNSET0;  /* 0x0080 */
		Luint32 PSPWRDWNSET1;  /* 0x0084 */
		Luint32 PSPWRDWNSET2;  /* 0x0088 */
		Luint32 PSPWRDWNSET3;  /* 0x008C */
		Luint32    u32PCR_rsvd7[4U];    /* 0x0090 */
		Luint32 PSPWRDWNCLR0;  /* 0x00A0 */
		Luint32 PSPWRDWNCLR1;  /* 0x00A4 */
		Luint32 PSPWRDWNCLR2;  /* 0x00A8 */
		Luint32 PSPWRDWNCLR3;  /* 0x00AC */
	} pcrBASE_t;

	/** @def pcrREG
	*   @brief Pcr Register Frame Pointer
	*
	*   This pointer is used by the system driver to access the Pcr registers.
	*/
	#define pcrREG ((pcrBASE_t *)0xFFFFE000U)
	/* PCR General Definitions */
#endif


	typedef Luint32 peripheralFrame_CS_t;

	#define PeripheralFrame_CS0 0U
	#define PeripheralFrame_CS1 1U
	#define PeripheralFrame_CS2 2U
	#define PeripheralFrame_CS3 3U
	#define PeripheralFrame_CS4 4U
	#define PeripheralFrame_CS5 5U
	#define PeripheralFrame_CS6 6U
	#define PeripheralFrame_CS7 7U
	#define PeripheralFrame_CS8 8U
	#define PeripheralFrame_CS9 9U
	#define PeripheralFrame_CS10 10U
	#define PeripheralFrame_CS11 11U
	#define PeripheralFrame_CS12 12U
	#define PeripheralFrame_CS13 13U
	#define PeripheralFrame_CS14 14U
	#define PeripheralFrame_CS15 15U
	#define PeripheralFrame_CS16 16U
	#define PeripheralFrame_CS17 17U
	#define PeripheralFrame_CS18 18U
	#define PeripheralFrame_CS19 19U
	#define PeripheralFrame_CS20 20U
	#define PeripheralFrame_CS21 21U
	#define PeripheralFrame_CS22 22U
	#define PeripheralFrame_CS23 23U
	#define PeripheralFrame_CS24 24U
	#define PeripheralFrame_CS25 25U
	#define PeripheralFrame_CS26 26U
	#define PeripheralFrame_CS27 27U
	#define PeripheralFrame_CS28 28U
	#define PeripheralFrame_CS29 29U
	#define PeripheralFrame_CS30 30U
	#define PeripheralFrame_CS31 31U

	/* USER CODE BEGIN (1) */
	/* USER CODE END */


	typedef Luint32 quadrant_Select_t;
	#define Quadrant0 1U
	#define Quadrant1 2U
	#define Quadrant2 4U
	#define Quadrant3 8U

	/* USER CODE BEGIN (2) */
	/* USER CODE END */

	/** @typedef RM4_PCR__FRAME_SELECT_T
	*   @brief PCR Peripheral Frame Type Definition
	*
	*   This type is used to access the PCR peripheral Frame configuration register.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef struct peripheral_Frame_Select
	{
		peripheralFrame_CS_t Peripheral_CS;
		quadrant_Select_t Peripheral_Quadrant;
	}RM4_PCR__FRAME_SELECT_T;

	/* USER CODE BEGIN (3) */
	/* USER CODE END */

	/** @typedef RM4_PCR__QUAD_CHIPSELECT_T
	*   @brief PCR Peripheral Frame registers Type Definition
	*
	*   This type is used to access all the PCR peripheral Frame configuration registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef struct peripheral_Quad_ChipSelect
	{
		Luint32 Peripheral_Quad0_3_CS0_7;
		Luint32 Peripheral_Quad4_7_CS8_15;
		Luint32 Peripheral_Quad8_11_CS16_23;
		Luint32 Peripheral_Quad12_15_CS24_31;
	}RM4_PCR__QUAD_CHIPSELECT_T;

	/* USER CODE BEGIN (4) */
	/* USER CODE END */

	/** @typedef RM4_PCR__MEMORY_CHIPSELECT_T
	*   @brief PCR Peripheral Memory Frame registers Type Definition
	*
	*   This type is used to access all the PCR peripheral Memory Frame configuration registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef struct peripheral_Memory_ChipSelect
	{
		Luint32 Peripheral_Mem_CS0_31;
		Luint32 Peripheral_Mem_CS32_63;
	}RM4_PCR__MEMORY_CHIPSELECT_T;

	/* USER CODE BEGIN (5) */
	/* USER CODE END */

	typedef Luint32 RM4_PCR__MEMORY_FRAME_CS_T;

	#define PeripheralMemoryFrame_CS0 0U
	#define PeripheralMemoryFrame_CS1 1U
	#define PeripheralMemoryFrame_CS2 2U
	#define PeripheralMemoryFrame_CS3 3U
	#define PeripheralMemoryFrame_CS4 4U
	#define PeripheralMemoryFrame_CS5 5U
	#define PeripheralMemoryFrame_CS6 6U
	#define PeripheralMemoryFrame_CS7 7U
	#define PeripheralMemoryFrame_CS8 8U
	#define PeripheralMemoryFrame_CS9 9U
	#define PeripheralMemoryFrame_CS10 10U
	#define PeripheralMemoryFrame_CS11 11U
	#define PeripheralMemoryFrame_CS12 12U
	#define PeripheralMemoryFrame_CS13 13U
	#define PeripheralMemoryFrame_CS14 14U
	#define PeripheralMemoryFrame_CS15 15U
	#define PeripheralMemoryFrame_CS16 16U
	#define PeripheralMemoryFrame_CS17 17U
	#define PeripheralMemoryFrame_CS18 18U
	#define PeripheralMemoryFrame_CS19 19U
	#define PeripheralMemoryFrame_CS20 20U
	#define PeripheralMemoryFrame_CS21 21U
	#define PeripheralMemoryFrame_CS22 22U
	#define PeripheralMemoryFrame_CS23 23U
	#define PeripheralMemoryFrame_CS24 24U
	#define PeripheralMemoryFrame_CS25 25U
	#define PeripheralMemoryFrame_CS26 26U
	#define PeripheralMemoryFrame_CS27 27U
	#define PeripheralMemoryFrame_CS28 28U
	#define PeripheralMemoryFrame_CS29 29U
	#define PeripheralMemoryFrame_CS30 30U
	#define PeripheralMemoryFrame_CS31 31U
	#define PeripheralMemoryFrame_CS32 32U
	#define PeripheralMemoryFrame_CS33 33U
	#define PeripheralMemoryFrame_CS34 34U
	#define PeripheralMemoryFrame_CS35 35U
	#define PeripheralMemoryFrame_CS36 36U
	#define PeripheralMemoryFrame_CS37 37U
	#define PeripheralMemoryFrame_CS38 38U
	#define PeripheralMemoryFrame_CS39 39U
	#define PeripheralMemoryFrame_CS40 40U
	#define PeripheralMemoryFrame_CS41 41U
	#define PeripheralMemoryFrame_CS42 42U
	#define PeripheralMemoryFrame_CS43 43U
	#define PeripheralMemoryFrame_CS44 44U
	#define PeripheralMemoryFrame_CS45 45U
	#define PeripheralMemoryFrame_CS46 46U
	#define PeripheralMemoryFrame_CS47 47U
	#define PeripheralMemoryFrame_CS48 48U
	#define PeripheralMemoryFrame_CS49 49U
	#define PeripheralMemoryFrame_CS50 50U
	#define PeripheralMemoryFrame_CS51 51U
	#define PeripheralMemoryFrame_CS52 52U
	#define PeripheralMemoryFrame_CS53 53U
	#define PeripheralMemoryFrame_CS54 54U
	#define PeripheralMemoryFrame_CS55 55U
	#define PeripheralMemoryFrame_CS56 56U
	#define PeripheralMemoryFrame_CS57 57U
	#define PeripheralMemoryFrame_CS58 58U
	#define PeripheralMemoryFrame_CS59 59U
	#define PeripheralMemoryFrame_CS60 60U
	#define PeripheralMemoryFrame_CS61 61U
	#define PeripheralMemoryFrame_CS62 62U
	#define PeripheralMemoryFrame_CS63 63U



#endif /* RM4_PC4__PRIVATE_H_ */
