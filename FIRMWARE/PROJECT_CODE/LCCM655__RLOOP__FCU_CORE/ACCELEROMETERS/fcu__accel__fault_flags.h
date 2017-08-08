#ifndef _LCCM655__16__FAULT_FLAGS_H_
#define _LCCM655__16__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL FAULT
 
 * 
 * @note
 * A General fault has occurred in the accel subsystem. 
 * 
 * @tool
 * [ACCEL]|[00]|[GENERAL FAULT
 ]|[A General fault has occurred in the accel subsystem. ]
*/
#define C_LCCM655__ACCEL__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__ACCEL__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * MMA INIT FAULT 
 * 
 * @note
 * A fault occurred while trying to init the MMA device chain. Inspect individual 
 * flags for more information. 
 * 
 * @tool
 * [ACCEL]|[01]|[MMA INIT FAULT ]|[A fault occurred while trying to init the MMA device chain. Inspect individual 
flags for more information. ]
*/
#define C_LCCM655__ACCEL__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__ACCEL__FAULT_INDEX_MASK__01			0x00000002U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

