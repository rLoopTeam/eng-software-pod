#ifndef _LCCM135__00__FAULT_FLAGS_H_
#define _LCCM135__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL
 
 * 
 * A general fault has occurred in the module, inspect other flags for details. 
 * 
*/
#define C_LCCM135__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * INIT BANKS FAILED 
 * 
 * Failed to init the flash banks during init. 
*/
#define C_LCCM135__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * FSM BUSY 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * ERROR FAIL 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__03				0x00000003U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__03			0x00000008U

/*
 * @fault_index
 * 04
 * 
 * @brief
 * NULL POINTER 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__04				0x00000004U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__04			0x00000010U

/*
 * @fault_index
 * 05
 * 
 * @brief
 * INVALID COMMAND 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__05				0x00000005U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__05			0x00000020U

/*
 * @fault_index
 * 06
 * 
 * @brief
 * INVALID ECC ADDX 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__06				0x00000006U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__06			0x00000040U

/*
 * @fault_index
 * 07
 * 
 * @brief
 * OTP CHECKSUM 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__07				0x00000007U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__07			0x00000080U

/*
 * @fault_index
 * 08
 * 
 * @brief
 * INVALID HCLK 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__08				0x00000008U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__08			0x00000100U

/*
 * @fault_index
 * 09
 * 
 * @brief
 * INVALID BANK 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__09				0x00000009U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__09			0x00000200U

/*
 * @fault_index
 * 10
 * 
 * @brief
 * INVALID ADDX 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__10				0x0000000AU
#define C_LCCM135__CORE__FAULT_INDEX_MASK__10			0x00000400U

/*
 * @fault_index
 * 11
 * 
 * @brief
 * INVALID READ MODE 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__11				0x0000000BU
#define C_LCCM135__CORE__FAULT_INDEX_MASK__11			0x00000800U

/*
 * @fault_index
 * 12
 * 
 * @brief
 * DATA BUFFER LENGTH 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__12				0x0000000CU
#define C_LCCM135__CORE__FAULT_INDEX_MASK__12			0x00001000U

/*
 * @fault_index
 * 13
 * 
 * @brief
 * ECC BUFF MISMATCH 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__13				0x0000000DU
#define C_LCCM135__CORE__FAULT_INDEX_MASK__13			0x00002000U

/*
 * @fault_index
 * 14
 * 
 * @brief
 * ERROR NOT AVAILABLE 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__14				0x0000000EU
#define C_LCCM135__CORE__FAULT_INDEX_MASK__14			0x00004000U

/*
 * @fault_index
 * 15
 * 
 * @brief
 * GENERIC FAIL 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__15				0x0000000FU
#define C_LCCM135__CORE__FAULT_INDEX_MASK__15			0x00008000U

/*
 * @fault_index
 * 16
 * 
 * @brief
 * ECC BUFFER LENGTH 
 * 
 *  
*/
#define C_LCCM135__CORE__FAULT_INDEX__16				0x00000010U
#define C_LCCM135__CORE__FAULT_INDEX_MASK__16			0x00010000U

#endif //#ifndef _LCCM135__FAULT_FLAGS_H_

