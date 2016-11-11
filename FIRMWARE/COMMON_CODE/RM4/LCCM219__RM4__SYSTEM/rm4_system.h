/**
 * @file		rm4_system.h
 * @brief		System header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM219R0.FILE.002
 */

#ifndef _RM4_SYSTEM_H_
#define _RM4_SYSTEM_H_

	/*lint -e793*/
	//Info 793: ANSI limit of 8 'conditional inclusion levels' exceeded  processing is unaffected
	
	/*lint -e537*/
	#include <localdef.h>

	#ifndef C_LOCALDEF__SYSTEM__HCLK_FREQ_MHZ
		#error
	#endif

	//we are always using 1:2 ratio for H/VCLK
	#define C_LOCALDEF__SYSTEM__VCLK_FREQ_MHZ								(C_LOCALDEF__SYSTEM__HCLK_FREQ_MHZ / 2U)

	//This is the VCLK2 frequency in MHZ.  VCLK2 is used for HET and HTU units
	//Never change it from 100MHZ
	#define C_LOCALDEF__SYSTEM__VCLK2_FREQ_MHZ								(C_LOCALDEF__SYSTEM__VCLK_FREQ_MHZ)


	#ifndef C_LOCALDEF__SYSTEM__VCLK1_DIVISOR
		#error
	#endif
	#define C_LOCALDEF__SYSTEM__VCLK1_FREQ_MHZ								(C_LOCALDEF__SYSTEM__VCLK_FREQ_MHZ / C_LOCALDEF__SYSTEM__VCLK1_DIVISOR)

	/** @enum loopBackType
	*   @brief Loopback type definition
	*/
	/** @typedef loopBackType_t
	*   @brief Loopback type Type Definition
	*
	*   This type is used to select the module Loopback type Digital or Analog loopback.
	*/
/*
	typedef enum loopBackType
	{
		SPI3_LOOPBACK__DIGITAL = 0U,
		SPI3_LOOPBACK__ANALOG = 1U
	}loopBackType_t;
*/

	/** @enum config_value_type
	*   @brief config type definition
	*/
	/** @typedef config_value_type_t
	*   @brief config type Type Definition
	*
	*   This type is used to specify the Initial and Current value.
	*/
	typedef enum config_value_type
	{
		InitialValue,
		CurrentValue
	}config_value_type_t;

	#include <RM4/LCCM219__RM4__SYSTEM/rm4_system__private.h>

	#include <RM4/LCCM223__RM4__periph_central_resource/rm4_pcr.h>
	#include <RM4/LCCM222__RM4__pin_mux/rm4_pinmux.h>
	#include <RM4/LCCM221__RM4__selftest/rm4_selftest.h>
	//included as its own module
	//#include <RM4/LCCM220__RM4__error_signal_module/rm4_esm.h>
	#include <RM4/LCCM224__RM4__efuse/rm4_efuse.h>
	#include <RM4/LCCM225__RM4__vectored_isr_mgr/rm4_vim.h>
	#include <RM4/LCCM219__RM4__system/rm4_system__mpu.h>
	#include <RM4/LCCM227__RM4__bist/rm4_bist.h>
	#include <RM4/LCCM219__RM4__system/rm4_system__pmu.h>



	typedef enum
	{
		AlignmentFault                      = 0x0001U,
		BackgroundFault                     = 0x0000U,
		PermissionFault                     = 0x000DU,
		DebugEvent                          = 0x0002U,
		SynchronousExternalAbort            = 0x0008U,
		MemoryAccessSynchronousParityError  = 0x0409U,
		AsynchronousExternalAbort           = 0x0406U,
		MemoryAccessAsynchronousParityError = 0x0408U
	} t_eDfsrFs;

	/*lint -e960*/
	/*lint -e970*/
	//Note 960: Violates MISRA 2004 Required Rule 18.4, unions shall not be used
	//Reviewed LG
	
	typedef union
	{
		unsigned Word;
		struct
		{
			unsigned : 19;
			unsigned ExT : 1;
			unsigned WnR : 1;

			t_eDfsrFs Fs : 11;
			//unsigned FS4 : 1;
			//unsigned : 6;
			//unsigned FS3_0 : 4;
		} Bits;
	} t_uDfsr;

	typedef enum
	{
		AXIMaster = 0x00U, /* ..or.. */
		Cache     = 0x00U,
		ATCM      = 0x01U,
		BTCM      = 0x02U,
		Reserved  = 0x03U
	}t_eADfsrSide;

	typedef union
	{
		unsigned Word;
		struct
		{
			unsigned : 4;
			unsigned CacheWay : 4;			/* Unpredictable, The value returned in this field indicates the cache way or ways in which the error occurred */
			t_eADfsrSide Side : 2;			/* The value returned in this field indicates the source of the error. */
			unsigned RecoverableError : 1; 	/* The value returned in this field indicates if the error is recoverable: */
											/* 0 = Unrecoverable error. */
											/* 1 = Recoverable error. This includes all correctable parity/ECC errors and recoverable TCM external errors. */
			unsigned : 7;
			unsigned Index : 9; /* On the AIFSR, and for TCM accesses, this field SBZ. This field returns the index value for the access giving the error.*/
			unsigned : 5;
		} Bits;
	} t_uADfsr; /* Auxiliary Data Fault Status Register */

	typedef t_uADfsr t_uAIfsr; /* Auxiliary Instruction Fault Status Register */

	/*lint +e960*/
	/*lint +e970*/



	/** @enum systemClockSource
	*   @brief Alias names for clock sources
	*
	*   This enumeration is used to provide alias names for the clock sources:
	*     - Oscillator
	*     - Pll1
	*     - External1
	*     - Low Power Oscillator Low
	*     - Low Power Oscillator High
	*     - PLL2
	*     - External2
	*     - Synchronous VCLK1
	*/
	/*****************************************************************************
	*****************************************************************************/
	enum systemClockSource
	{
		SYS_OSC       		= 0U,  /**< Alias for oscillator clock Source                */
		SYS_PLL1      		= 1U,  /**< Alias for Pll1 clock Source                      */
		SYS_EXTERNAL1  		= 3U,  /**< Alias for external clock Source                  */
		SYS_LPO_LOW   		= 4U,  /**< Alias for low power oscillator low clock Source  */
		SYS_LPO_HIGH  		= 5U,  /**< Alias for low power oscillator high clock Source */
		SYS_PLL2    		= 6U,  /**< Alias for Pll2 clock Source                      */
		SYS_EXTERNAL2 		= 7U,  /**< Alias for external 2 clock Source                */
		SYS_VCLK      		= 9U   /**< Alias for synchronous VCLK1 clock Source         */
	};

	/** @def SYS_PRE1
	*   @brief Alias name for RTI1CLK PRE clock source
	*
	*   This is an alias name for the RTI1CLK pre clock source.
	*   This can be either:
	*     - Oscillator
	*     - Pll
	*     - 32 kHz Oscillator
	*     - External
	*     - Low Power Oscillator Low
	*     - Low Power Oscillator High
	*     - Flexray Pll
	*/
	/*SAFETYMCUSW 79 S MR:19.4 <APPROVED> " Value comes from GUI drop down option " */
	#define SYS_PRE1 (SYS_PLL1)

	/** @def SYS_PRE2
	*   @brief Alias name for RTI2CLK pre clock source
	*
	*   This is an alias name for the RTI2CLK pre clock source.
	*   This can be either:
	*     - Oscillator
	*     - Pll
	*     - 32 kHz Oscillator
	*     - External
	*     - Low Power Oscillator Low
	*     - Low Power Oscillator High
	*     - Flexray Pll
	*/
	/*SAFETYMCUSW 79 S MR:19.4 <APPROVED> " Value comes from GUI drop down option " */
	#define SYS_PRE2 (SYS_PLL1)


	#define C_RM4SYSTEM__SYS_DOZE_MODE        0x000F3F02U
	#define C_RM4SYSTEM__SYS_SNOOZE_MODE      0x000F3F03U
	#define C_RM4SYSTEM__SYS_SLEEP_MODE       0x000FFFFFU
	#define C_RM4SYSTEM__LPO_TRIM_VALUE       (((*(volatile Luint32 *)0xF00801B4U) & 0xFFFF0000U)>>16U)
	#define C_RM4SYSTEM__SYS_EXCEPTION        (*(volatile Luint32 *)0xFFFFFFE4U)

	#define C_RM4SYSTEM__POWERON_RESET        0x8000U
	#define C_RM4SYSTEM__OSC_FAILURE_RESET    0x4000U
	#define C_RM4SYSTEM__WATCHDOG_RESET       0x2000U
	#define C_RM4SYSTEM__ICEPICK_RESET        0x2000U
	#define C_RM4SYSTEM__CPU_RESET            0x0020U
	#define C_RM4SYSTEM__SW_RESET             0x0010U

	#define C_RM4SYSTEM__WATCHDOG_STATUS     (*(volatile Luint32 *)0xFFFFFC98U)
	#define C_RM4SYSTEM__DEVICE_ID_REV       (*(volatile Luint32 *)0xFFFFFFF0U)




	//function protos
	void vRM4_SYSTEM__Init(void);

	Luint8 u8RM4_SYSTEM_OSC__Is_OscFail(void);
	Luint8 u8RM4_SYSTEM_OSC__Is_PLLFail(void);

	void vRM4_SYSTEM__SetupPLL(void);
	void vRM4_SYSTEM__InitPerip(void);
	void vRM4_SYSTEM__MapClocks(void);
	void vRM4_SYSTEM__SetupFlash(void);
	void vRM2_SYSTEM__PowerDown(Luint32 mode);
	void vRM4_SYSTEM__TrimLPO(void);

	/* System Core Interface Functions */

	/** @fn void _coreInitRegisters_(void)
	*   @brief Initialize Core register
	*/
	void _rm4_system_core__InitRegisters_(void);

	/** @fn void _rm4_system_core__InitStackPointer_(void)
	*   @brief Initialize Core stack pointer
	*/
	void _rm4_system_core__InitStackPointer_(void);

	/** @fn void _getCPSRValue_(void)
	*   @brief Get CPSR Value
	*/
	Luint32 _getCPSRValue_(void);

	/** @fn void _gotoCPUIdle_(void)
	*   @brief Take CPU to Idle state
	*/
	void _gotoCPUIdle_(void);

	/** @fn void _coreEnableIrqVicOffset_(void)
	*   @brief Enable Irq offset propagation via Vic controller
	*/
	void _coreEnableIrqVicOffset_(void);

	/** @fn void _coreEnableVfp_(void)
	*   @brief Enable vector floating point unit
	*/
	void _coreEnableVfp_(void);

	/** @fn void _coreEnableEventBusExport_(void)
	*   @brief Enable event bus export for external monitoring modules
	*   @note It is required to enable event bus export to process ecc issues.
	*
	*   This function enables event bus exports to external monitoring modules
	*   like tightly coupled RAM wrapper, Flash wrapper and error signaling module.
	*/
	void _coreEnableEventBusExport_(void);

	/** @fn void _coreDisableEventBusExport_(void)
	*   @brief Disable event bus export for external monitoring modules
	*
	*   This function disables event bus exports to external monitoring modules
	*   like tightly coupled RAM wrapper, Flash wrapper and error signaling module.
	*/
	void _coreDisableEventBusExport_(void);

	/** @fn void _coreEnableRamEcc_(void)
	*   @brief Enable external ecc error for RAM odd and even bank
	*   @note It is required to enable event bus export to process ecc issues.
	*/
	void _coreEnableRamEcc_(void);

	/** @fn void _coreDisableRamEcc_(void)
	*   @brief Disable external ecc error for RAM odd and even bank
	*/
	void _coreDisableRamEcc_(void);

	/** @fn void _coreEnableFlashEcc_(void)
	*   @brief Enable external ecc error for the Flash
	*   @note It is required to enable event bus export to process ecc issues.
	*/
	void _coreEnableFlashEcc_(void);

	/** @fn void _coreDisableFlashEcc_(void)
	*   @brief Disable external ecc error for the Flash
	*/
	void _coreDisableFlashEcc_(void);

	/** @fn Luint32 _coreGetDataFault_(void)
	*   @brief Get core data fault status register
	*   @return The function will return the data fault status register value:
	*           - bit [10,3..0]:
	*                            - 0b00001: Alignment                -> address is valid
	*                            - 0b00000: Background               -> address is valid
	*                            - 0b01101: Permission               -> address is valid
	*                            - 0b01000: Precise External Abort   -> address is valid
	*                            - 0b10110: Imprecise External Abort -> address is unpredictable
	*                            - 0b11001: Precise ECC Error        -> address is valid
	*                            - 0b11000: Imprecise ECC Error      -> address is unpredictable
	*                            - 0b00010: Debug                    -> address is unchanged
	*           - bit [11]:
	*                            - 0: Read
	*                            - 1: Write
	*           - bit [12]:
	*                            - 0: AXI Decode Error (DECERR)
	*                            - 1: AXI Slave Error (SLVERR)
	*/
	Luint32 _coreGetDataFault_(void);

	/** @fn void _coreClearDataFault_(void)
	*   @brief Clear core data fault status register
	*/
	void _coreClearDataFault_(void);

	/** @fn Luint32 _coreGetInstructionFault_(void)
	*   @brief Get core instruction fault status register
	*   @return The function will return the instruction fault status register value:
	*           - bit [10,3..0]:
	*                            - 0b00001: Alignment                -> address is valid
	*                            - 0b00000: Background               -> address is valid
	*                            - 0b01101: Permission               -> address is valid
	*                            - 0b01000: Precise External Abort   -> address is valid
	*                            - 0b10110: Imprecise External Abort -> address is unpredictable
	*                            - 0b11001: Precise ECC Error        -> address is valid
	*                            - 0b11000: Imprecise ECC Error      -> address is unpredictable
	*                            - 0b00010: Debug                    -> address is unchanged
	*           - bit [12]:
	*                            - 0: AXI Decode Error (DECERR)
	*                            - 1: AXI Slave Error (SLVERR)
	*/
	Luint32 _coreGetInstructionFault_(void);

	/** @fn void _coreClearInstructionFault_(void)
	*   @brief Clear core instruction fault status register
	*/
	void _coreClearInstructionFault_(void);

	/** @fn Luint32 _coreGetDataFaultAddress_(void)
	*   @brief Get core data fault address register
	*   @return The function will return the data fault address:
	*/
	Luint32 _coreGetDataFaultAddress_(void);

	/** @fn void _coreClearDataFaultAddress_(void)
	*   @brief Clear core data fault address register
	*/
	void _coreClearDataFaultAddress_(void);

	/** @fn Luint32 _coreGetInstructionFaultAddress_(void)
	*   @brief Get core instruction fault address register
	*   @return The function will return the instruction fault address:
	*/
	Luint32 _coreGetInstructionFaultAddress_(void);

	/** @fn void _coreClearInstructionFaultAddress_(void)
	*   @brief Clear core instruction fault address register
	*/
	void _coreClearInstructionFaultAddress_(void);

	/** @fn Luint32 _coreGetAuxiliaryDataFault_(void)
	*   @brief Get core auxiliary data fault status register
	*   @return The function will return the auxiliary data fault status register value:
	*           - bit [13..5]:
	*                            - Index value for access giving error
	*           - bit [21]:
	*                            - 0: Unrecoverable error
	*                            - 1: Recoverable error
	*           - bit [23..22]:
	*                            - 0: Side cache
	*                            - 1: Side ATCM (Flash)
	*                            - 2: Side BTCM (RAM)
	*                            - 3: Reserved
	*           - bit [27..24]:
	*                            - Cache way or way in which error occurred
	*/
	Luint32 _coreGetAuxiliaryDataFault_(void);

	/** @fn void _coreClearAuxiliaryDataFault_(void)
	*   @brief Clear core auxiliary data fault status register
	*/
	void _coreClearAuxiliaryDataFault_(void);

	/** @fn Luint32 _coreGetAuxiliaryInstructionFault_(void)
	*   @brief Get core auxiliary instruction fault status register
	*   @return The function will return the auxiliary instruction fault status register value:
	*           - bit [13..5]:
	*                            - Index value for access giving error
	*           - bit [21]:
	*                            - 0: Unrecoverable error
	*                            - 1: Recoverable error
	*           - bit [23..22]:
	*                            - 0: Side cache
	*                            - 1: Side ATCM (Flash)
	*                            - 2: Side BTCM (RAM)
	*                            - 3: Reserved
	*           - bit [27..24]:
	*                            - Cache way or way in which error occurred
	*/
	Luint32 _coreGetAuxiliaryInstructionFault_(void);

	/** @fn void _coreClearAuxiliaryInstructionFault_(void)
	*   @brief Clear core auxiliary instruction fault status register
	*/
	void _coreClearAuxiliaryInstructionFault_(void);

	/** @fn void _disable_interrupt_(void)
	*   @brief Disable IRQ and FIQ Interrupt u32Mode in CPSR register
	*
	*   This function disables IRQ and FIQ Interrupt u32Mode in CPSR register.
	*/
	void _disable_interrupt_(void);

	/** @fn void _disable_IRQ_interrupt_(void)
	*   @brief Disable IRQ Interrupt u32Mode in CPSR register
	*
	*   This function disables IRQ Interrupt u32Mode in CPSR register.
	*/
	void _disable_IRQ_interrupt_(void);

	/** @fn void _disable_FIQ_interrupt_(void)
	*   @brief Disable FIQ Interrupt u32Mode in CPSR register
	*
	*   This function disables IRQ Interrupt u32Mode in CPSR register.
	*/
	void _disable_FIQ_interrupt_(void);

	/** @fn void _enable_interrupt_(void)
	*   @brief Enable IRQ and FIQ Interrupt u32Mode in CPSR register
	*
	*   This function Enables IRQ and FIQ Interrupt u32Mode in CPSR register.
	*   User must call this function to enable Interrupts in non-OS environments.
	*/
	void _enable_interrupt_(void);

	/** @fn void _esmCcmErrorsClear_(void)
	*   @brief Clears ESM Error caused due to CCM Errata in RevA Silicon
	*
	*   This function Clears ESM Error caused due to CCM Errata
	*   in RevA Silicon immediately after powerup.
	*/
	void _rm4_system_core__esmCcmErrorsClear_(void);

	/** @fn void _errata_CORTEXR4_66_(void)
	*   @brief Work Around for Errata CORTEX-R4#66
	*
	*   This function Disable out-of-order completion for divide
	*   instructions in Auxiliary Control register.
	*/
	void _errata_CORTEXR4_66_(void);

	/** @fn void _errata_CORTEXR4_57_(void)
	*   @brief Work Around for Errata CORTEX-R4#57
	*
	*   Disable out-of-order single-precision floating point
	*   multiply-accumulate instruction completion.
	*/
	void _errata_CORTEXR4_57_(void);

	void custom_dabort(void);

	void vRM4_SYSTEM__After_STC(void);

#endif //_RM4_SYSTEM_H_




