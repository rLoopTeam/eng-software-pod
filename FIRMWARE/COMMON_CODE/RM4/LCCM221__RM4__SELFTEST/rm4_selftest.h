/**
 * @file		rm4_selftest.h
 * @brief		Selftest functions header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM221R0.FILE.002
 */

#ifndef _RM4_SELFTEST_H_
#define _RM4_SELFTEST_H_


	#include <localdef.h>
	#include <RM4/LCCM221__RM4__SELFTEST/rm4_selftest__fault_flags.h>
	#include <MULTICORE/lccm284__multicore__fault_tree/fault_tree__public.h>

	/** Selftest Structure */
	struct _strRM4ST
	{
		FAULT_TREE__PUBLIC_T sFaultFlags;

	};


	#define flash1bitError	(*(volatile Luint32 *)(0xF00803F0U))
	#define flash2bitError	(*(volatile Luint32 *)(0xF00803F8U))

	#define tcramA1bitError	(*(volatile Luint32 *)(0x08400000U))
	#define tcramA2bitError (*(volatile Luint32 *)(0x08400010U))

	#define tcramB1bitError	(*(volatile Luint32 *)(0x08400008U))
	#define tcramB2bitError (*(volatile Luint32 *)(0x08400018U))

	#define tcramA1bit		(*(volatile Luint64 *)(0x08000000U))
	#define tcramA2bit		(*(volatile Luint64 *)(0x08000010U))

	#define tcramB1bit		(*(volatile Luint64 *)(0x08000008U))
	#define tcramB2bit		(*(volatile Luint64 *)(0x08000018U))

	#define flashBadECC		(*(volatile Luint32 *)(0x20000000U))

	#define CCMSR 			(*(volatile Luint32 *)(0xFFFFF600U))
	#define CCMKEYR			(*(volatile Luint32 *)(0xFFFFF604U))


	#define DMA_PARCR		(*(volatile Luint32 *)(0xFFFFF1A8U))
	#define DMA_PARADDR		(*(volatile Luint32 *)(0xFFFFF1ACU))

	#define DMARAMLOC		(*(volatile Luint32 *)(0xFFF80000U))
	#define DMARAMPARLOC	(*(volatile Luint32 *)(0xFFF80A00U))


	/** @enum pbistPort
	* @brief Alias names for pbist Port number
	*
	* This enumeration is used to provide alias names for the pbist Port number
	*	 - PBIST_PORT0
	*	 - PBIST_PORT1
	*/
	/*****************************************************************************
	*****************************************************************************/
	enum pbistPort
	{
		PBIST_PORT0 = 0U, /**< Alias for PBIST Port 0 */
		PBIST_PORT1 = 1U /**< Alias for PBIST Port 1 */
	};
	/** @enum pbistAlgo
	* @brief Alias names for pbist Algorithm
	*
	* This enumeration is used to provide alias names for the pbist Algorithm
	*	 - PBIST_TripleReadSlow
	*	 - PBIST_TripleReadFast
	*	 - PBIST_March13N_DP
	*	 - PBIST_March13N_SP
	*	 - PBIST_DOWN1a_DP
	*	 - PBIST_DOWN1a_SP
	*	 - PBIST_MapColumn_DP
	*	 - PBIST_MapColumn_SP
	*	 - PBIST_Precharge_DP
	*	 - PBIST_Precharge_SP
	*	 - PBIST_DTXN2a_DP
	*	 - PBIST_DTXN2a_SP
	*	 - PBIST_PMOSOpen_DP
	*	 - PBIST_PMOSOpen_SP
	*	 - PBIST_PPMOSOpenSlice1_DP
	*	 - PBIST_PPMOSOpenSlice1_SP
	*	 - PBIST_PPMOSOpenSlice2_DP
	*	 - PBIST_PPMOSOpenSlice2_SP

	*/
	/*****************************************************************************
	*****************************************************************************/
	enum pbistAlgo
	{
		PBIST_TripleReadSlow	 = 0x00000001U,
		PBIST_TripleReadFast	 = 0x00000002U,
		PBIST_March13N_DP		= 0x00000004U,
		PBIST_March13N_SP		= 0x00000008U,
		PBIST_DOWN1a_DP		 = 0x00000010U,
		PBIST_DOWN1a_SP		 = 0x00000020U,
		PBIST_MapColumn_DP	 = 0x00000040U,
		PBIST_MapColumn_SP	 = 0x00000080U,
		PBIST_Precharge_DP	 = 0x00000100U,
		PBIST_Precharge_SP	 = 0x00000200U,
		PBIST_DTXN2a_DP		 = 0x00000400U,
		PBIST_DTXN2a_SP		 = 0x00000800U,
		PBIST_PMOSOpen_DP		= 0x00001000U,
		PBIST_PMOSOpen_SP		= 0x00002000U,
		PBIST_PPMOSOpenSlice1_DP = 0x00004000U,
		PBIST_PPMOSOpenSlice1_SP = 0x00008000U,
		PBIST_PPMOSOpenSlice2_DP = 0x00010000U,
		PBIST_PPMOSOpenSlice2_SP = 0x00020000U
	};
	/* PBIST configuration registers */
	/*****************************************************************************
	*****************************************************************************/
	typedef struct pbist_config_reg
	{
		Luint32 CONFIG_RAMT;
		Luint32 CONFIG_DLR;
		Luint32 CONFIG_PACT;
		Luint32 CONFIG_PBISTID;
		Luint32 CONFIG_OVER;
		Luint32 CONFIG_FSRDL1;
		Luint32 CONFIG_ROM;
		Luint32 CONFIG_ALGO;
		Luint32 CONFIG_RINFOL;
		Luint32 CONFIG_RINFOU;
	} pbist_config_reg_t;

	/* PBIST and STC ROM - PBIST RAM GROUPING */
	#define PBIST_ROM_PBIST_RAM_GROUP   1U
	#define STC_ROM_PBIST_RAM_GROUP     2U

	/* PBIST congiruration registers initial value */
	#define PBIST_RAMT_CONFIGVALUE 0U
	#define PBIST_DLR_CONFIGVALUE 0U
	#define PBIST_PACT_CONFIGVALUE 0U
	#define PBIST_PBISTID_CONFIGVALUE 0U
	#define PBIST_OVER_CONFIGVALUE 0U
	#define PBIST_FSRDL1_CONFIGVALUE 0U
	#define PBIST_ROM_CONFIGVALUE 0U
	#define PBIST_ALGO_CONFIGVALUE 0U
	#define PBIST_RINFOL_CONFIGVALUE 0U
	#define PBIST_RINFOU_CONFIGVALUE 0U



	typedef volatile struct stcBase
	{
		Luint32 STCGCR0;		/**< 0x0000: STC Control Register 0	*/
		Luint32 STCGCR1;		/**< 0x0004: STC Control Register 1 */
		Luint32 STCTPR;		/**< 0x0008: STC Self-Test Run Timeout Counter Preload Register	*/
		Luint32 STCCADDR;		/**< 0x000C: STC Self-Test Current ROM Address Register */
		Luint32 STCCICR;		/**< 0x0010: STC Self-Test Current Interval Count Register */
		Luint32 STCGSTAT;		/**< 0x0014: STC Self-Test Global Status Register */
		Luint32 STCFSTAT;		/**< 0x0018: STC Self-Test Fail Status Register */
		Luint32 CPU1_CURMISR3;	/**< 0x001C: STC CPU1 Current MISR Register */
		Luint32 CPU1_CURMISR2;	/**< 0x0020: STC CPU1 Current MISR Register */
		Luint32 CPU1_CURMISR1;	/**< 0x0024: STC CPU1 Current MISR Register */
		Luint32 CPU1_CURMISR0;	/**< 0x0028: STC CPU1 Current MISR Register */
		Luint32 CPU2_CURMISR3;	/**< 0x002C: STC CPU1 Current MISR Register */
		Luint32 CPU2_CURMISR2;	/**< 0x0030: STC CPU1 Current MISR Register */
		Luint32 CPU2_CURMISR1;	/**< 0x0034: STC CPU1 Current MISR Register */
		Luint32 CPU2_CURMISR0;	/**< 0x0038: STC CPU1 Current MISR Register */
		Luint32 STCSCSCR;		/**< 0x003C: STC Signature Compare Self-Check Register */
	} stcBASE_t;

	#define stcREG   ((stcBASE_t *)0xFFFFE600U)

	/* STC General Definitions */

	/* STC Test Intervals supported in the Device */
	#define STC_INTERVAL 24U
	#define STC_MAX_TIMEOUT 0xFFFFFFFFU



	/* Configuration registers */
	typedef struct stc_config_reg
	{
		Luint32 CONFIG_STCGCR0;
		Luint32 CONFIG_STCGCR1;
		Luint32 CONFIG_STCTPR;
		Luint32 CONFIG_STCSCSCR;
	} stc_config_reg_t;

	/* Configuration registers initial value */
	#define STC_STCGCR0_CONFIGVALUE	0xFFFF0000U
	#define STC_STCGCR1_CONFIGVALUE	0x5U
	#define STC_STCTPR_CONFIGVALUE	0xFFFFFFFFU
	#define STC_STCSCSCR_CONFIGVALUE 0x5U




	#define INPUT_ENABLE		 0x0000000FU
	#define INPUT_DISABLE		0x00000000U

	#define SYS_WS_READ_STATES 0x00000000U


	#define SYS_REPAIR_EN_0	 0x00000000U
	#define SYS_REPAIR_EN_3	 0x00000100U
	#define SYS_REPAIR_EN_5	 0x00000200U

	#define SYS_DEID_AUTOLOAD_EN 0x00000400U

	#define EFC_FDI_EN			0x00000800U
	#define EFC_FDI_DIS		 0x00000000U

	#define SYS_ECC_OVERRIDE_EN 0x00001000U
	#define SYS_ECC_OVERRIDE_DIS 0x00000000U

	#define SYS_ECC_SELF_TEST_EN 0x00002000U
	#define SYS_ECC_SELF_TEST_DIS 0x00000000U

	#define OUTPUT_ENABLE		 0x0003C000U
	#define OUTPUT_DISABLE		0x00000000U

	/*********** OUTPUT **************/

	#define EFC_AUTOLOAD_ERROR_EN	0x00040000U
	#define EFC_INSTRUCTION_ERROR_EN 0x00080000U
	#define EFC_INSTRUCTION_INFO_EN 0x00100000U
	#define EFC_SELF_TEST_ERROR_EN 0x00200000U


	#define EFC_AUTOLOAD_ERROR_DIS	0x00000000U
	#define EFC_INSTRUCTION_ERROR_DIS 0x00000000U
	#define EFC_INSTRUCTION_INFO_DIS 0x00000000U
	#define EFC_SELF_TEST_ERROR_DIS 0x00000000U

	#define DISABLE_READ_ROW0		 0x00800000U

	/********************************************************************/

	#define SYS_REPAIR_0		 0x00000010U
	#define SYS_REPAIR_3		 0x00000010U
	#define SYS_REPAIR_5		 0x00000020U

	#define SYS_DEID_AUTOLOAD	0x00000040U
	#define SYS_FCLRZ			0x00000080U
	#define EFC_READY			0x00000100U
	#define SYS_ECC_OVERRIDE	 0x00000200U
	#define EFC_AUTOLOAD_ERROR 0x00000400U
	#define EFC_INSTRUCTION_ERROR 0x00000800U
	#define EFC_INSTRUCTION_INFO 0x00001000U
	#define SYS_ECC_SELF_TEST	0x00002000U
	#define EFC_SELF_TEST_ERROR 0x00004000U
	#define EFC_SELF_TEST_DONE 0x00008000U

	/************** 0x3C error status register ******************************************************/

	#define TIME_OUT 0x01
	#define AUTOLOAD_NO_FUSEROM_DATA	 0x02U
	#define AUTOLOAD_SIGN_FAIL			0x03U
	#define AUTOLOAD_PROG_INTERRUPT	 0x04U
	#define AUTOLOAD_TWO_BIT_ERR		 0x05U
	#define PROGRAME_WR_P_SET			 0x06U
	#define PROGRAME_MNY_DATA_ITERTN	 0x07U
	#define PROGRAME_MNY_CNTR_ITERTN	 0x08U
	#define UN_PROGRAME_BIT_SET		 0x09U
	#define REDUNDANT_REPAIR_ROW		 0x0AU
	#define PROGRAME_MNY_CRA_ITERTN	 0x0BU
	#define PROGRAME_SAME_DATA			0x0CU
	#define PROGRAME_CMP_SKIP			 0x0DU
	#define PROGRAME_ABORT				0x0EU
	#define PROGRAME_INCORRECT_KEY		 0x0FU
	#define FUSEROM_LASTROW_STUCK		 0x10U
	#define AUTOLOAD_SINGLE_BIT_ERR		 0x15U
	#define DUMPWORD_TWO_BIT_ERR		 0x16U
	#define DUMPWORD_ONE_BIT_ERR		 0x17U
	#define SELF_TEST_ERROR			 0x18U

	#define INSTRUCTION_DONE			 0x20U

	/************** Efuse Instruction set ******************************************************/

	#define TEST_UNPROGRAME_ROM 0x01000000U
	#define PROGRAME_CRA		 0x02000000U
	#define DUMP_WORD			0x04000000U
	#define LOAD_FUSE_SCAN_CHAIN 0x05000000U
	#define PROGRAME_DATA		0x07000000U
	#define RUN_AUTOLOAD_8	 0x08000000U
	#define RUN_AUTOLOAD_A	 0x0A000000U

	/* Configuration registers */
	typedef struct efc_config_reg
	{
		Luint32 CONFIG_BOUNDARY;
		Luint32 CONFIG_PINS;
		Luint32 CONFIG_SELFTESTCYCLES;
		Luint32 CONFIG_SELFTESTSIGN;
	}efc_config_reg_t;

	/* Configuration registers initial value */
	#define EFC_BOUNDARY_CONFIGVALUE	0x0000200FU
	#define EFC_PINS_CONFIGVALUE		0x000082E0U
	#define EFC_SELFTESTCYCLES_CONFIGVALUE	0x00000258U
	#define EFC_SELFTESTSIGN_CONFIGVALUE	0x5362F97FU


	//failure flag defines
	#define CCMSELFCHECK_FAIL1			1U
	#define CCMSELFCHECK_FAIL2			2U
	#define CCMSELFCHECK_FAIL3			3U
	#define CCMSELFCHECK_FAIL4			4U
	#define PBISTSELFCHECK_FAIL1		 5U
	#define EFCCHECK_FAIL1				6U
	#define EFCCHECK_FAIL2				7U
	#define FMCECCCHECK_FAIL1			 8U
	#define CHECKB0RAMECC_FAIL1		 9U
	#define CHECKB1RAMECC_FAIL1		 10U
	#define CHECKFLASHECC_FAIL1		 11U
	#define VIMPARITYCHECK_FAIL1		 12U
	#define DMAPARITYCHECK_FAIL1		 13U
	#define HET1PARITYCHECK_FAIL1		14U
	#define HTU1PARITYCHECK_FAIL1		15U
	#define HET2PARITYCHECK_FAIL1		16U
	#define HTU2PARITYCHECK_FAIL1		17U
	#define ADC1PARITYCHECK_FAIL1		18U
	#define ADC2PARITYCHECK_FAIL1		19U
	#define CAN1PARITYCHECK_FAIL1		20U
	#define CAN2PARITYCHECK_FAIL1		21U
	#define CAN3PARITYCHECK_FAIL1		22U
	#define MIBSPI1PARITYCHECK_FAIL1	 23U
	#define MIBSPI3PARITYCHECK_FAIL1	 24U
	#define MIBSPI5PARITYCHECK_FAIL1	 25U
	#define CHECKRAMECC_FAIL1			26U
	#define CHECKRAMECC_FAIL2			27U
	#define CHECKCLOCKMONITOR_FAIL1	 28U
	#define CHECKFLASHEEPROMECC_FAIL1	29U
	#define CHECKFLASHEEPROMECC_FAIL2	31U
	#define CHECKFLASHEEPROMECC_FAIL3	32U
	#define CHECKFLASHEEPROMECC_FAIL4	33U
	#define CHECKPLL1SLIP_FAIL1		 34U
	#define CHECKRAMADDRPARITY_FAIL1	 35U
	#define CHECKRAMADDRPARITY_FAIL2	 36U
	#define CHECKRAMUERRTEST_FAIL1	 37U
	#define CHECKRAMUERRTEST_FAIL2	 38U
	#define FMCBUS1PARITYCHECK_FAIL1	 39U
	#define FMCBUS1PARITYCHECK_FAIL2	 40U

	/* lint -e762*/
	
	//function protos
	void vRM4_SELFTEST__Init(void);
	Luint32 u32RM4_SELFTEST__Get_FaultFlags(void);
	void vRM4_SELFTEST__STC_Check(void);
	void vRM4_SELFTEST__CPU_Test(Luint32 no_of_intervals, Luint32 max_timeout, Luint8 restart_test);
	void vRM4_SELFTEST__EnableParity(void);
	void vRM4_SELFTEST__DisableParity(void);
	void vRM4_SELFTEST__CCM_Check(void);

	void vRM4_SELFTEST__Set_FailNotification(Luint32 flag);
	void vRM4_SELFTEST__EFuse_Check(void);
	void vRM4_SELFTEST__EFuse_SelfTest(void);
	Luint8 u8RM4_SELFTEST__EFuse_StuckZeroTest(void);
	Luint8 u8RM4_SELFTEST__EFuse_CheckSelfTest(void);
	void vRM4_SELFTEST__MemoryInit(Luint32 ram);
	void vRM4_SELFTEST__Check_RAMECC(void);

	void vRM4_SELFTEST__DMA_ParityCheck(void);
	void vRM4_SELFTEST__VIM_ParityCheck(void);
	void vRM4_SELFTEST__MIBSPI1_ParityCheck(void);
	void vRM4_SELFTEST__MIBSPI3_ParityCheck(void);
	void vRM4_SELFTEST__MIBSPI5_ParityCheck(void);
	void vRM4_SELFTEST__N2HET1_ParityCheck(void);
	void vRM4_SELFTEST__N2HET2_ParityCheck(void);
	void vRM4_SELFTEST__CAN1_ParityCheck(void);
	void vRM4_SELFTEST__CAN2_ParityCheck(void);
	void vRM4_SELFTEST__CAN3_ParityCheck(void);
	void vRM4_SELFTEST__ADC1_ParityCheck(void);
	void vRM4_SELFTEST__ADC2_ParityCheck(void);

	/* lint +e762*/
	
#endif
