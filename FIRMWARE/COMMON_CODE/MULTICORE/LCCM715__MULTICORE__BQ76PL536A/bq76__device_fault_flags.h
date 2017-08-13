#ifndef _LCCM715__02__FAULT_FLAGS_H_
#define _LCCM715__02__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * A device specific general fault occurred. 
 * 
 * @tool
 * [DEVICE]|[00]|[GENERAL ]|[A device specific general fault occurred. ]
*/
#define C_LCCM715__DEVICE__FAULT_INDEX__00				0x00000000U
#define C_LCCM715__DEVICE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * ADDX SET FAULT 
 * 
 * @note
 * We could not set the addx on a specific device. 
 * 
 * @tool
 * [DEVICE]|[01]|[ADDX SET FAULT ]|[We could not set the addx on a specific device. ]
*/
#define C_LCCM715__DEVICE__FAULT_INDEX__01				0x00000001U
#define C_LCCM715__DEVICE__FAULT_INDEX_MASK__01			0x00000002U

#endif //#ifndef _LCCM715__FAULT_FLAGS_H_

