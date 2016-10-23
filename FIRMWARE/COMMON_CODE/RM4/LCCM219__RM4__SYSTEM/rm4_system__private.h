/**
 * @file		rm4_system__private.h
 * @brief		Private defs
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM219R0.FILE.007
 */



#ifndef RM4_SYSTEM__PRIVATE_H_
#define RM4_SYSTEM__PRIVATE_H_


	/* Tcram Register Frame Definition */
	/** @struct tcramBase
	*   @brief TCRAM Wrapper Register Frame Definition
	*
	*   This type is used to access the TCRAM Wrapper Registers.
	*/
	/** @typedef tcramBASE_t
	*   @brief TCRAM Wrapper Register Frame Type Definition
	*
	*   This type is used to access the TCRAM Wrapper Registers.
	*/

	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct tcramBase
	{
		Luint32 RAMCTRL;		    /* 0x0000 */
		Luint32 RAMTHRESHOLD;      /* 0x0004 */
		Luint32 RAMOCCUR;			/* 0x0008 */
		Luint32 RAMINTCTRL;		/* 0x000C */
		Luint32 RAMERRSTATUS;		/* 0x0010 */
		Luint32 RAMSERRADDR;		/* 0x0014 */
		Luint32   rsvd1;			/* 0x0018 */
		Luint32 RAMUERRADDR;		/* 0x001C */
		Luint32   rsvd2[4U];		/* 0x0020 */
		Luint32 RAMTEST;			/* 0x0030 */
		Luint32   rsvd3;			/* 0x0034 */
		Luint32 RAMADDRDECVECT;	/* 0x0038 */
		Luint32 RAMPERADDR;        /* 0x003C */
	} tcramBASE_t;

	#define tcram1REG ((tcramBASE_t *)(0xFFFFF800U))
	#define tcram2REG ((tcramBASE_t *)(0xFFFFF900U))


/* System Register Frame 1 Definition */
	/** @struct systemBase1
	*   @brief System Register Frame 1 Definition
	*
	*   This type is used to access the System 1 Registers.
	*/
	/** @typedef systemBASE1_t
	*   @brief System Register Frame 1 Type Definition
	*
	*   This type is used to access the System 1 Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct systemBase1
	{
		Luint32 SYSPC1;                 /* 0x0000 */
		Luint32 SYSPC2;                 /* 0x0004 */
		Luint32 SYSPC3;                 /* 0x0008 */
		Luint32 SYSPC4;                 /* 0x000C */
		Luint32 SYSPC5;                 /* 0x0010 */
		Luint32 SYSPC6;                 /* 0x0014 */
		Luint32 SYSPC7;                 /* 0x0018 */
		Luint32 SYSPC8;                 /* 0x001C */
		Luint32 SYSPC9;                 /* 0x0020 */
		Luint32 SSWPLL1;                /* 0x0024 */
		Luint32 SSWPLL2;                /* 0x0028 */
		Luint32 SSWPLL3;                /* 0x002C */
		Luint32 CSDIS;                  /* 0x0030 */
		Luint32 CSDISSET;               /* 0x0034 */
		Luint32 CSDISCLR;               /* 0x0038 */
		Luint32 CDDIS;                  /* 0x003C */
		Luint32 CDDISSET;               /* 0x0040 */
		Luint32 CDDISCLR;               /* 0x0044 */
		Luint32 GHVSRC;                 /* 0x0048 */
		Luint32 VCLKASRC;               /* 0x004C */
		Luint32 RCLKSRC;                /* 0x0050 */
		Luint32 CSVSTAT;                /* 0x0054 */
		Luint32 MSTGCR;                 /* 0x0058 */
		Luint32 MINITGCR;               /* 0x005C */
		Luint32 MSINENA;                /* 0x0060 */
		Luint32 MSTFAIL;                /* 0x0064 */
		Luint32 MSTCGSTAT;              /* 0x0068 */
		Luint32 MINISTAT;               /* 0x006C */
		Luint32 PLLCTL1;                /* 0x0070 */
		Luint32 PLLCTL2;                /* 0x0074 */
		Luint32 UERFLAG;                /* 0x0078 */
		Luint32 DIEIDL;                 /* 0x007C */
		Luint32 DIEIDH;                 /* 0x0080 */
		Luint32 VRCTL;                  /* 0x0084 */
		Luint32 LPOMONCTL;              /* 0x0088 */
		Luint32 CLKTEST;                /* 0x008C */
		Luint32 DFTCTRLREG1;            /* 0x0090 */
		Luint32 DFTCTRLREG2;            /* 0x0094 */
		Luint32   u32RM4_SYSBASE1__rsvd1;                /* 0x0098 */
		Luint32   u32RM4_SYSBASE1__rsvd2;                /* 0x009C */
		Luint32 GPREG1;                 /* 0x00A0 */
		Luint32 BTRMSEL;                /* 0x00A4 */
		Luint32 IMPFASTS;               /* 0x00A8 */
		Luint32 IMPFTADD;               /* 0x00AC */
		Luint32 SSISR1;                 /* 0x00B0 */
		Luint32 SSISR2;                 /* 0x00B4 */
		Luint32 SSISR3;                 /* 0x00B8 */
		Luint32 SSISR4;                 /* 0x00BC */

		Luint32 RAMGCR;                 /* 0x00C0 */
		Luint32 BMMCR1;                 /* 0x00C4 */
		Luint32 BMMCR2;                 /* 0x00C8 ACTUALLY RESERVED*/

		Luint32 MMUGCR;                 /* 0x00CC ACTUALL CPURSTCR CPU Reset Control Register*/
		Luint32 CLKCNTL;                /* 0x00D0 */
		Luint32 ECPCNTL;                /* 0x00D4 */

		Luint32 DSPGCR;                 /* 0x00D8 */
		Luint32 DEVCR1;                 /* 0x00DC */
		Luint32 SYSECR;                 /* 0x00E0 */
		Luint32 SYSESR;                 /* 0x00E4 */
		Luint32 SYSTASR;                /* 0x00E8 */
		Luint32 GBLSTAT;                /* 0x00EC */
		Luint32 DEV;                    /* 0x00F0 */
		Luint32 SSIVEC;                 /* 0x00F4 */
		Luint32 SSIF;                   /* 0x00F8 */
	} systemBASE1_t;


	/** @def systemREG1
	*   @brief System Register Frame 1 Pointer
	*
	*   This pointer is used by the system driver to access the system frame 1 registers.
	*/
	#define systemREG1 ((systemBASE1_t *)0xFFFFFF00U)

	/** @def systemPORT
	*   @brief ECLK GIO Port Register Pointer
	*
	*   Pointer used by the GIO driver to access I/O PORT of System/Eclk
	*   (use the GIO drivers to access the port pins).
	*/
	#define systemPORT ((RM4_GIO__PORT_T *)0xFFFFFF04U)

	/* USER CODE BEGIN (0) */
	/* USER CODE END */

	/* System Register Frame 2 Definition */
	/** @struct systemBase2
	*   @brief System Register Frame 2 Definition
	*
	*   This type is used to access the System 2 Registers.
	*/
	/** @typedef systemBASE2_t
	*   @brief System Register Frame 2 Type Definition
	*
	*   This type is used to access the System 2 Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct systemBase2
	{
		Luint32 PLLCTL3;        /* 0x0000 */
		Luint32   u32RM4_SYSBASE2__rsvd1;        /* 0x0004 */
		Luint32 STCCLKDIV;      /* 0x0008 */
		Luint32   u32RM4_SYSBASE2__rsvd2[6U];     /* 0x000C */
		Luint32 ECPCNTRL0;      /* 0x0024 */
		Luint32   u32RM4_SYSBASE2__rsvd3[5U];     /* 0x0028 */
		Luint32 CLK2CNTL;       /* 0x003C */
		Luint32 VCLKACON1;      /* 0x0040 */
		Luint32  u32RM4_SYSBASE2__rsvd4[11U];     /* 0x0044 */
		Luint32  CLKSLIP;       /* 0x0070 */
		Luint32  u32RM4_SYSBASE2__rsvd5[30U];   	 /* 0x0074 */
		Luint32  EFC_CTLEN;     /* 0x00EC */
		Luint32  DIEIDL_REG0;   /* 0x00F0 */
		Luint32  DIEIDH_REG1;   /* 0x00F4 */
		Luint32  DIEIDL_REG2;   /* 0x00F8 */
		Luint32  DIEIDH_REG3;   /* 0x00FC */
	} systemBASE2_t;

	/** @def systemREG2
	*   @brief System Register Frame 2 Pointer
	*
	*   This pointer is used by the system driver to access the system frame 2 registers.
	*/
	#define systemREG2 ((systemBASE2_t *)0xFFFFE100U)

#endif /* RM4_SYSTEM__PRIVATE_H_ */
