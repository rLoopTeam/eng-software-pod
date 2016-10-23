/**
 * @file		RM4_SYSTEM__PMU.H
 * @brief		PMU header
 * 				Performance Measurement Unit (PMU) Cycle Count (Cortex-R4F only)
 * 				The PMU cycle count method uses the Cortex-R4F performance measurement unit (PMU) to count
 * 				CPUCLK cycles during the time the measured code is running. The code execution time can then be
 * 				calculated by multiplying the counted CPU clock cycles with the clock period.
 * 				The PMU consists of four counters: one only counting clock cycles and three for counting selectable
 * 				events. The example code use event counter 0 to count the clock cycles; so the PMU configuration can be
 * 				easily changed to count any other event type (see 'enum pmuEvent' in the sys_pmu.h source code). Since
 * 				the CPU runs with system frequency (CPU clock MCLK, fMCLK = fHCLK), HCLK is used as the timebase for
 * 				the measurements. In the given code example, event counter 0 of the PMU is set up to count CPU clock
 * 				cycles (Event = PMU_CYCLE_COUNT).
 *
 *
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM219R0.FILE.009
 */

//RM4 Cortex RF4 Performance Measurement Unit
#ifndef _RM4_SYSTEM__PMU_H_
#define _RM4_SYSTEM__PMU_H_

	/** @def pmuCOUNTER0
	*   @brief pmu event counter 0
	*
	*   Alias for pmu event counter 0
	*/
	#define pmuCOUNTER0 0x00000001U

	/** @def pmuCOUNTER1
	*   @brief pmu event counter 1
	*
	*   Alias for pmu event counter 1
	*/
	#define pmuCOUNTER1 0x00000002U

	/** @def pmuCOUNTER2
	*   @brief pmu event counter 2
	*
	*   Alias for pmu event counter 2
	*/
	#define pmuCOUNTER2 0x00000004U

	/** @def pmuCYCLE_COUNTER
	*   @brief pmu cycle counter
	*
	*   Alias for pmu event counter
	*/
	#define pmuCYCLE_COUNTER 0x80000000U

	/** @enum pmuEvent
	*   @brief pmu event
	*
	*   Alias for pmu event counter increment source
	*/
	enum pmuEvent
	{
		PMU_INST_CACHE_MISS                     = 0x01U,
		PMU_DATA_CACHE_MISS                     = 0x03U,
		PMU_DATA_CACHE_ACCESS                   = 0x04U,
		PMU_DATA_READ_ARCH_EXECUTED             = 0x06U,
		PMU_DATA_WRITE_ARCH_EXECUTED            = 0x07U,
		PMU_INST_ARCH_EXECUTED                  = 0x08U,
		PMU_EXCEPTION_TAKEN                     = 0x09U,
		PMU_EXCEPTION_RETURN_ARCH_EXECUTED      = 0x0AU,
		PMU_CHANGE_TO_CONTEXT_ID_EXECUTED       = 0x0BU,
		PMU_SW_CHANGE_OF_PC_ARCH_EXECUTED       = 0x0CU,
		PMU_BRANCH_IMM_INST_ARCH_EXECUTED       = 0x0DU,
		PMU_PROC_RETURN_ARCH_EXECUTED           = 0x0EU,
		PMU_UNALIGNED_ACCESS_ARCH_EXECUTED      = 0x0FU,
		PMU_BRANCH_MISSPREDICTED                = 0x10U,
		PMU_CYCLE_COUNT                         = 0x11U,
		PMU_PREDICTABLE_BRANCHES                = 0x12U,
		PMU_INST_BUFFER_STALL                   = 0x40U,
		PMU_DATA_DEPENDENCY_INST_STALL          = 0x41U,
		PMU_DATA_CACHE_WRITE_BACK               = 0x42U,
		PMU_EXT_MEMORY_REQUEST                  = 0x43U,
		PMU_LSU_BUSY_STALL                      = 0x44U,
		PMU_FORCED_DRAIN_OFSTORE_BUFFER         = 0x45U,
		PMU_FIQ_DISABLED_CYCLE_COUNT            = 0x46U,
		PMU_IRQ_DISABLED_CYCLE_COUNT            = 0x47U,
		PMU_ETMEXTOUT_0                         = 0x48U,
		PMU_ETMEXTOUT_1                         = 0x49U,
		PMU_INST_CACHE_TAG_ECC_ERROR            = 0x4AU,
		PMU_INST_CACHE_DATA_ECC_ERROR           = 0x4BU,
		PMU_DATA_CACHE_TAG_ECC_ERROR            = 0x4CU,
		PMU_DATA_CACHE_DATA_ECC_ERROR           = 0x4DU,
		PMU_TCM_FATAL_ECC_ERROR_PREFETCH        = 0x4EU,
		PMU_TCM_FATAL_ECC_ERROR_LOAD_STORE      = 0x4FU,
		PMU_STORE_BUFFER_MERGE                  = 0x50U,
		PMU_LSU_STALL_STORE_BUFFER_FULL         = 0x51U,
		PMU_LSU_STALL_STORE_QUEUE_FULL          = 0x52U,
		PMU_INTEGER_DIV_EXECUTED                = 0x53U,
		PMU_STALL_INTEGER_DIV                   = 0x54U,
		PMU_PLD_INST_LINE_FILL                  = 0x55U,
		PMU_PLD_INST_NO_LINE_FILL               = 0x56U,
		PMU_NON_CACHEABLE_ACCESS_AXI_MASTER     = 0x57U,
		PMU_INST_CACHE_ACCESS                   = 0x58U,
		PMU_DOUBLE_DATA_CACHE_ISSUE             = 0x59U,
		PMU_DUAL_ISSUE_CASE_A                   = 0x5AU,
		PMU_DUAL_ISSUE_CASE_B1_B2_F2_F2D        = 0x5BU,
		PMU_DUAL_ISSUE_OTHER                    = 0x5CU,
		PMU_DP_FLOAT_INST_EXCECUTED             = 0x5DU,
		PMU_DUAL_ISSUED_PAIR_INST_ARCH_EXECUTED = 0x5EU,
		PMU_DATA_CACHE_DATA_FATAL_ECC_ERROR     = 0x60U,
		PMU_DATA_CACHE_TAG_FATAL_ECC_ERROR      = 0x61U,
		PMU_PROCESSOR_LIVE_LOCK                 = 0x62U,
		PMU_ATCM_MULTI_BIT_ECC_ERROR            = 0x64U,
		PMU_B0TCM_MULTI_BIT_ECC_ERROR           = 0x65U,
		PMU_B1TCM_MULTI_BIT_ECC_ERROR           = 0x66U,
		PMU_ATCM_SINGLE_BIT_ECC_ERROR           = 0x67U,
		PMU_B0TCM_SINGLE_BIT_ECC_ERROR          = 0x68U,
		PMU_B1TCM_SINGLE_BIT_ECC_ERROR          = 0x69U,
		PMU_TCM_COR_ECC_ERROR_LOAD_STORE        = 0x6AU,
		PMU_TCM_COR_ECC_ERROR_PREFETCH          = 0x6BU,
		PMU_TCM_FATAL_ECC_ERROR_AXI_SLAVE       = 0x6CU,
		PMU_TCM_COR_ECC_ERROR_AXI_SLAVE         = 0x6DU
	};

	/** @fn void _pmuInit_(void)
	*   @brief Initialize Perfprmance Monitor Unit
	*/
	void _pmuInit_(void);

	/** @fn void _pmuEnableCountersGlobal_(void)
	*   @brief Enable and reset cycle counter and all 3 event counters
	*/
	void _pmuEnableCountersGlobal_(void);

	/** @fn void _pmuDisableCountersGlobal_(void)
	*   @brief Disable cycle counter and all 3 event counters
	*/
	void _pmuDisableCountersGlobal_(void);

	/** @fn void _pmuResetCycleCounter_(void)
	*   @brief Reset cycle counter
	*/
	void _pmuResetCycleCounter_(void);

	/** @fn void _pmuResetEventCounters_(void)
	*   @brief Reset event counters 0-2
	*/
	void _pmuResetEventCounters_(void);

	/** @fn void _pmuResetCounters_(void)
	*   @brief Reset cycle counter and event counters 0-2
	*/
	void _pmuResetCounters_(void);

	/** @fn void _pmuStartCounters_(unsigned counters)
	*   @brief Starts selected counters
	*   @param[in] counters - Counter mask
	*/
	void _pmuStartCounters_(Luint32 counters);

	/** @fn void _pmuStopCounters_(unsigned counters)
	*   @brief Stops selected counters
	*   @param[in] counters - Counter mask
	*/
	void _pmuStopCounters_(Luint32 counters);

	/** @fn void _pmuSetCountEvent_(unsigned counter, unsigned event)
	*   @brief Set event counter count event
	*   @param[in] counter - Counter select 0..2
	*   @param[in] event   - Count event
	*/
	void _pmuSetCountEvent_(Luint32 counter, Luint32 event);

	/** @fn unsigned _pmuGetCycleCount_(void)
	*   @brief Returns current cycle counter value
	*
	*   @return cycle count.
	*/
	Luint32 _pmuGetCycleCount_(void);

	/** @fn unsigned _pmuGetEventCount_(unsigned counter)
	*   @brief Returns current event counter value
	*   @param[in] counter - Counter select 0..2
	*
	*   @return event counter count.
	*/
	Luint32 _pmuGetEventCount_(Luint32 counter);

	/** @fn unsigned _pmuGetOverflow_(void)
	*   @brief Returns current overflow register and clear flags
	*
	*   @return overflow flags.
	*/
	Luint32 _pmuGetOverflow_(void);


#endif
