#ifndef _LCCM215__00__FAULT_FLAGS_H_
#define _LCCM215__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERIC 
 * 
 * @description
 * GENERIC 
*/
#define C_LCCM215__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM215__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * WRITE TIME OUT 
 * 
 * @description
 * A timeout occurred during a write. 
*/
#define C_LCCM215__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM215__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * READ TIME OUT 
 * 
 * @description
 * A timeout occurred during a read. 
*/
#define C_LCCM215__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM215__CORE__FAULT_INDEX_MASK__02			0x00000004U

#endif //#ifndef _LCCM215__FAULT_FLAGS_H_

