#ifndef _LCCM220__02__FAULT_FLAGS_H_
#define _LCCM220__02__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 *  
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__00				0x00000000U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * CCMR4 
 * 
 *  
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__01				0x00000001U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * FMC 
 * 
 * ncorrectable error (address parity on bus1 accesses) Group2 4 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__02				0x00000002U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * B0TCM 
 * 
 * RAM even bank (B0TCM) - uncorrectable error Group2 6 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__03				0x00000003U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__03			0x00000008U

/*
 * @fault_index
 * 04
 * 
 * @brief
 * B1TCM 
 * 
 * RAM odd bank (B1TCM) - uncorrectable error Group2 8 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__04				0x00000004U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__04			0x00000010U

/*
 * @fault_index
 * 05
 * 
 * @brief
 * B0TCM_ADDX 
 * 
 * RAM even bank (B0TCM) - address bus parity error Group2 10 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__05				0x00000005U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__05			0x00000020U

/*
 * @fault_index
 * 06
 * 
 * @brief
 * B1TCM_ADDX 
 * 
 * RAM odd bank (B1TCM) - address bus parity error Group2 12 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__06				0x00000006U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__06			0x00000040U

/*
 * @fault_index
 * 07
 * 
 * @brief
 * FLASH_ATCM 
 * 
 * Flash (ATCM) - ECC live lock detect Group2 16 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__07				0x00000007U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__07			0x00000080U

/*
 * @fault_index
 * 08
 * 
 * @brief
 * RTI_WWD_NMI 
 * 
 * RTI_WWD_NMI Group2 24 
*/
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX__08				0x00000008U
#define C_LCCM220__GROUP2_NON_MASKABLE__FAULT_INDEX_MASK__08			0x00000100U

#endif //#ifndef _LCCM220__FAULT_FLAGS_H_

