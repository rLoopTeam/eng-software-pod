/**
 * @file		rm4_vim.h
 * @brief		RM4 VIM Main header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM225R0.FILE.002
 */

#ifndef _RM4_VIM_H_
#define _RM4_VIM_H_
#ifndef WIN32

	/*lint -e537*/
	#include <localdef.h>

	/** @enum systemInterrupt
	*   @brief Alias names for clock sources
	*
	*   This enumeration is used to provide alias names for the clock sources:
	*     - IRQ
	*     - FIQ
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef enum
	{
		SYS_IRQ, /**< Alias for IRQ interrupt */
		SYS_FIQ  /**< Alias for FIQ interrupt */
	}RM4_VIM__SYSTEM_INTERRUPT_T;

	/* Vim Register Frame Definition */
	/** @struct vimBase
	*   @brief Vim Register Frame Definition
	*
	*   This type is used to access the Vim Registers.
	*/
	/** @typedef vimBASE_t
	*   @brief VIM Register Frame Type Definition
	*
	*   This type is used to access the VIM Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
#if C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 0U
	typedef volatile struct vimBase
	{
		Luint32      IRQINDEX;         /* 0x0000        */
		Luint32      FIQINDEX;         /* 0x0004        */
		Luint32        rsvd1;          /* 0x0008        */
		Luint32        rsvd2;          /* 0x000C        */
		Luint32      FIRQPR0;          /* 0x0010        */
		Luint32      FIRQPR1;          /* 0x0014        */
		Luint32      FIRQPR2;          /* 0x0018        */
		Luint32      FIRQPR3;          /* 0x001C        */
		Luint32      INTREQ0;          /* 0x0020        */
		Luint32      INTREQ1;          /* 0x0024        */
		Luint32      INTREQ2;          /* 0x0028        */
		Luint32      INTREQ3;          /* 0x002C        */
		Luint32      REQMASKSET0;      /* 0x0030        */
		Luint32      REQMASKSET1;      /* 0x0034        */
		Luint32      REQMASKSET2;      /* 0x0038        */
		Luint32      REQMASKSET3;      /* 0x003C        */
		Luint32      REQMASKCLR0;      /* 0x0040        */
		Luint32      REQMASKCLR1;      /* 0x0044        */
		Luint32      REQMASKCLR2;      /* 0x0048        */
		Luint32      REQMASKCLR3;      /* 0x004C        */
		Luint32      WAKEMASKSET0;     /* 0x0050        */
		Luint32      WAKEMASKSET1;     /* 0x0054        */
		Luint32      WAKEMASKSET2;     /* 0x0058        */
		Luint32      WAKEMASKSET3;     /* 0x005C        */
		Luint32      WAKEMASKCLR0;     /* 0x0060        */
		Luint32      WAKEMASKCLR1;     /* 0x0064        */
		Luint32      WAKEMASKCLR2;     /* 0x0068        */
		Luint32      WAKEMASKCLR3;     /* 0x006C        */
		Luint32      IRQVECREG;        /* 0x0070        */
		Luint32      FIQVECREG;        /* 0x0074        */
		Luint32      CAPEVT;           /* 0x0078        */
		Luint32        rsvd3;          /* 0x007C        */
		Luint32      CHANCTRL[24U];    /* 0x0080-0x017C */
	} vimBASE_t;

	#define vimREG ((vimBASE_t *)0xFFFFFE00U)
#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U
	typedef volatile struct vimBase
	{
	    Luint32      rsvd1[59U];       /* 0x0000 - 0x00E8 Reserved */
	    Luint32      ECCSTAT;          /* 0x00EC        */
	    Luint32      ECCCTL;           /* 0x00F0        */
	    Luint32      UERRADDR;         /* 0x00F4        */
	    Luint32      FBVECADDR;        /* 0x00F8        */
	    Luint32      SBERRADDR;        /* 0x00FC        */
	    Luint32      IRQINDEX;         /* 0x0100        */
	    Luint32      FIQINDEX;         /* 0x0104        */
	    Luint32      rsvd2;            /* 0x0108        */
	    Luint32      rsvd3;            /* 0x010C        */
	    Luint32      FIRQPR0;          /* 0x0110        */
	    Luint32      FIRQPR1;          /* 0x0114        */
	    Luint32      FIRQPR2;          /* 0x0118        */
	    Luint32      FIRQPR3;          /* 0x011C        */
	    Luint32      INTREQ0;          /* 0x0120        */
	    Luint32      INTREQ1;          /* 0x0124        */
	    Luint32      INTREQ2;          /* 0x0128        */
	    Luint32      INTREQ3;          /* 0x012C        */
	    Luint32      REQMASKSET0;      /* 0x0130        */
	    Luint32      REQMASKSET1;      /* 0x0134        */
	    Luint32      REQMASKSET2;      /* 0x0138        */
	    Luint32      REQMASKSET3;      /* 0x013C        */
	    Luint32      REQMASKCLR0;      /* 0x0140        */
	    Luint32      REQMASKCLR1;      /* 0x0144        */
	    Luint32      REQMASKCLR2;      /* 0x0148        */
	    Luint32      REQMASKCLR3;      /* 0x014C        */
	    Luint32      WAKEMASKSET0;     /* 0x0150        */
	    Luint32      WAKEMASKSET1;     /* 0x0154        */
	    Luint32      WAKEMASKSET2;     /* 0x0158        */
	    Luint32      WAKEMASKSET3;     /* 0x015C        */
	    Luint32      WAKEMASKCLR0;     /* 0x0160        */
	    Luint32      WAKEMASKCLR1;     /* 0x0164        */
	    Luint32      WAKEMASKCLR2;     /* 0x0168        */
	    Luint32      WAKEMASKCLR3;     /* 0x016C        */
	    Luint32      IRQVECREG;        /* 0x0170        */
	    Luint32      FIQVECREG;        /* 0x0174        */
	    Luint32      CAPEVT;           /* 0x0178        */
	    Luint32      rsvd4;            /* 0x017C        */
	    Luint32      CHANCTRL[32U];    /* 0x0180-0x02FC */
	} vimBASE_t;

	#define vimREG ((vimBASE_t *)0xFFFFFD00U)

#else
#error
#endif
	/* VIM Type Definitions */

	/** @typedef t_isrFuncPTR
	*   @brief ISR Function Pointer Type Definition
	*
	*   This type is used to access the ISR handler.
	*/
	typedef void (*t_isrFuncPTR)(void);

	/* USER CODE BEGIN (1) */
	/* USER CODE END */


	/* VIM General Configuration */
#if C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 0U
	#define VIM_CHANNELS 96U
#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U
	#define VIM_CHANNELS 128U
#else
	#error
#endif

	/* USER CODE BEGIN (2) */
	/* USER CODE END */

	/* Interrupt Handlers */

	extern void phantomInterrupt(void);
	extern void esmHighInterrupt(void);

	/* USER CODE BEGIN (3) */
	/* USER CODE END */

	#define VIM_PARFLG		(*(volatile Luint32 *)0xFFFFFDECU)
	#define VIM_PARCTL		(*(volatile Luint32 *)0xFFFFFDF0U)
	#define VIM_ADDERR		(*(volatile Luint32 *)0xFFFFFDF4U)
	#define VIM_FBPARERR	(*(volatile Luint32 *)0xFFFFFDF8U)

	#define VIM_ECCSTAT			(*(volatile uint32 *)0xFFFFFDECU)
	#define VIM_ECCCTL			(*(volatile uint32 *)0xFFFFFDF0U)
	#define VIM_UERRADDR		(*(volatile uint32 *)0xFFFFFDF4U)
	#define VIM_FBVECADDR		(*(volatile uint32 *)0xFFFFFDF8U)
	#define VIM_SBERRADDR		(*(volatile uint32 *)0xFFFFFDFCU)

	#define VIMRAMPARLOC	(*(volatile Luint32 *)0xFFF82400U)
	#define VIMRAMLOC		(*(volatile Luint32 *)0xFFF82000U)

	/* Configuration registers */
	typedef struct vim_config_reg
	{
		Luint32 CONFIG_FIRQPR0;
		Luint32 CONFIG_FIRQPR1;
		Luint32 CONFIG_FIRQPR2;
		Luint32 CONFIG_FIRQPR3;
		Luint32 CONFIG_REQMASKSET0;
		Luint32 CONFIG_REQMASKSET1;
		Luint32 CONFIG_REQMASKSET2;
		Luint32 CONFIG_REQMASKSET3;
		Luint32 CONFIG_WAKEMASKSET0;
		Luint32 CONFIG_WAKEMASKSET1;
		Luint32 CONFIG_WAKEMASKSET2;
		Luint32 CONFIG_WAKEMASKSET3;
		Luint32 CONFIG_CAPEVT;
		Luint32 CONFIG_CHANCTRL[24U];
	} vim_config_reg_t;



	#define VIM_WAKEMASKSET0_CONFIGVALUE	0xFFFFFFFFU
	#define VIM_WAKEMASKSET1_CONFIGVALUE	0xFFFFFFFFU
	#define VIM_WAKEMASKSET2_CONFIGVALUE	0xFFFFFFFFU
	#define VIM_WAKEMASKSET3_CONFIGVALUE	0U
	#define VIM_CAPEVT_CONFIGVALUE	    	0U

	#define VIM_CHANCTRL0_CONFIGVALUE		0x00010203U
	#define VIM_CHANCTRL1_CONFIGVALUE		0x04050607U
	#define VIM_CHANCTRL2_CONFIGVALUE		0x08090A0BU
	#define VIM_CHANCTRL3_CONFIGVALUE		0x0C0D0E0FU
	#define VIM_CHANCTRL4_CONFIGVALUE		0x10111213U
	#define VIM_CHANCTRL5_CONFIGVALUE		0x14151617U
	#define VIM_CHANCTRL6_CONFIGVALUE		0x18191A1BU
	#define VIM_CHANCTRL7_CONFIGVALUE		0x1C1D1E1FU
	#define VIM_CHANCTRL8_CONFIGVALUE		0x20212223U
	#define VIM_CHANCTRL9_CONFIGVALUE		0x24252627U
	#define VIM_CHANCTRL10_CONFIGVALUE		0x28292A2BU
	#define VIM_CHANCTRL11_CONFIGVALUE		0x2C2D2E2FU
	#define VIM_CHANCTRL12_CONFIGVALUE		0x30313233U
	#define VIM_CHANCTRL13_CONFIGVALUE		0x34353637U
	#define VIM_CHANCTRL14_CONFIGVALUE		0x38393A3BU
	#define VIM_CHANCTRL15_CONFIGVALUE		0x3C3D3E3FU
	#define VIM_CHANCTRL16_CONFIGVALUE		0x40414243U
	#define VIM_CHANCTRL17_CONFIGVALUE		0x44454647U
	#define VIM_CHANCTRL18_CONFIGVALUE		0x48494A4BU
	#define VIM_CHANCTRL19_CONFIGVALUE		0x4C4D4E4FU
	#define VIM_CHANCTRL20_CONFIGVALUE		0x50515253U
	#define VIM_CHANCTRL21_CONFIGVALUE		0x54555657U
	#define VIM_CHANCTRL22_CONFIGVALUE		0x58595A5BU
	#define VIM_CHANCTRL23_CONFIGVALUE		0x5C5D5E5FU

	//function protos
	void vRM4_VIM__Init(void);
	void vRM4_VIM__ChannelMap(Luint32 u32Request, Luint32 u32Channel, t_isrFuncPTR handler);
	void vRM4_VIM__EnableInterrupt(Luint32 u32Channel, RM4_VIM__SYSTEM_INTERRUPT_T eType);
	void vRM4_VIM__DisableInterrupt(Luint32 u32Channel);
	void vRM4_VIM__MasterEnable(void);
	void vRM4_VIM__MasterDisable(void);
	Luint32 u32RM4_VIM__Get_MasterStatus(void);
	void vRM4_VIM_ISR__ParityErrorHandler(void);
	void vRM4_VIM__Enable_USB(void);

#endif //WIN32
#endif //RM4_VIM
