/**
 * @file		RM4_FLASH__PRIVATE.H
 * @brief		Private types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @st_fileID	LCCM135R0.FILE.023
 */

#ifndef _RM4_FLASH_PRIVATE_H_
#define _RM4_FLASH_PRIVATE_H_


	/* Flash Register Frame Definition */
	/** @struct flashWBase
	*   @brief Flash Wrapper Register Frame Definition
	*
	*   This type is used to access the Flash Wrapper Registers.
	*/
	/** @typedef flashWBASE_t
	*   @brief Flash Wrapper Register Frame Type Definition
	*
	*   This type is used to access the Flash Wrapper Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct flashWBase
	{
		Luint32 FRDCNTL;     /* 0x0000 */
		Luint32   rsvd1;       /* 0x0004 */
		Luint32 FEDACCTRL1;  /* 0x0008 */
		Luint32 FEDACCTRL2;  /* 0x000C */
		Luint32 FCORERRCNT;  /* 0x0010 */
		Luint32 FCORERRADD;  /* 0x0014 */
		Luint32 FCORERRPOS;  /* 0x0018 */
		Luint32 FEDACSTATUS; /* 0x001C */
		Luint32 FUNCERRADD;  /* 0x0020 */
		Luint32 FEDACSDIS;   /* 0x0024 */
		Luint32 FPRIMADDTAG; /* 0x0028 */
		Luint32 FREDUADDTAG; /* 0x002C */
		Luint32 FBPROT;      /* 0x0030 */
		Luint32 FBSE;        /* 0x0034 */
		Luint32 FBBUSY;      /* 0x0038 */
		Luint32 FBAC;        /* 0x003C */
		Luint32 FBFALLBACK;  /* 0x0040 */
		Luint32 FBPRDY;      /* 0x0044 */
		Luint32 FPAC1;       /* 0x0048 */
		Luint32 FPAC2;       /* 0x004C */
		Luint32 FMAC;        /* 0x0050 */
		Luint32 FMSTAT;      /* 0x0054 */
		Luint32 FEMUDMSW;    /* 0x0058 */
		Luint32 FEMUDLSW;    /* 0x005C */
		Luint32 FEMUECC;     /* 0x0060 */
		Luint32 FLOCK;       /* 0x0064 */
		Luint32 FEMUADDR;    /* 0x0068 */
		Luint32 FDIAGCTRL;   /* 0x006C */
		Luint32 FRAWDATAH;   /* 0x0070 */
		Luint32 FRAWDATAL;   /* 0x0074 */
		Luint32 FRAWECC;     /* 0x0078 */
		Luint32 FPAROVR;     /* 0x007C */
		Luint32   rsvd2[16U];  /* 0x009C */
		Luint32 FEDACSDIS2;  /* 0x00C0 */
		Luint32   rsvd3[15U]; /* 0x00C4 */
		Luint32   rsvd4[13U];   /* 0x0100 */
		Luint32   rsvd5[85U]; /* 0x0134 */
		Luint32 FSMWRENA;    /* 0x0288 */
		Luint32   rsvd6[6U];  /* 0x028C */
		Luint32 FSMSECTOR;   /* 0x02A4 */
		Luint32   rsvd7[4U];  /* 0x02A8 */
		Luint32 EEPROMCONFIG;/* 0x02B8 */
		Luint32   rsvd8[19U]; /* 0x02BC */
		Luint32 EECTRL1;     /* 0x0308 */
		Luint32 EECTRL2;     /* 0x030C */
		Luint32 EECORRERRCNT;/* 0x0310 */
		Luint32 EECORRERRADD;/* 0x0314 */
		Luint32 EECORRERRPOS;/* 0x0318 */
		Luint32 EESTATUS;    /* 0x031C */
		Luint32 EEUNCERRADD; /* 0x0320 */
	} flashWBASE_t;

	/** @def flashWREG
	*   @brief Flash Wrapper Register Frame Pointer
	*
	*   This pointer is used by the system driver to access the flash wrapper registers.
	*/
	#define flashWREG ((flashWBASE_t *)(0xFFF87000U))


	/** @enum flashWPowerModes
	*   @brief Alias names for flash bank power modes
	*
	*   This enumeration is used to provide alias names for the flash bank power modes:
	*     - sleep
	*     - standby
	*     - active
	*/
	/*****************************************************************************
	*****************************************************************************/
	enum flashWPowerModes
	{
		SYS_SLEEP   = 0U, /**< Alias for flash bank power u32Mode sleep   */
		SYS_STANDBY = 1U, /**< Alias for flash bank power u32Mode standby */
		SYS_ACTIVE  = 3U  /**< Alias for flash bank power u32Mode active  */
	};

	/* USER CODE BEGIN (2) */
	/* USER CODE END */


	#define FSM_WR_ENA_HL		(*(volatile Luint32 *)0xFFF87288U)
	#define EEPROM_CONFIG_HL	(*(volatile Luint32 *)0xFFF872B8U)

#endif //_RM4_FLASH_PRIVATE_H_
