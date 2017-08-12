#ifndef _LCCM487__00__FAULT_FLAGS_H_
#define _LCCM487__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * General Fault 
 * 
 * @tool
 * [CORE]|[00]|[GENERAL ]|[General Fault ]
*/
#define C_LCCM487__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM487__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * RX OVERFLOW 
 * 
 * @note
 * The Rx FIFO has overflowed. 
 * 
 * @tool
 * [CORE]|[01]|[RX OVERFLOW ]|[The Rx FIFO has overflowed. ]
*/
#define C_LCCM487__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM487__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * DEVICE INDEX FAULT 
 * 
 * @note
 * A device inded was attempted that is out of the range of number of devices. 
 * 
 * 
 * @tool
 * [CORE]|[02]|[DEVICE INDEX FAULT ]|[A device inded was attempted that is out of the range of number of devices. 
]
*/
#define C_LCCM487__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM487__CORE__FAULT_INDEX_MASK__02			0x00000004U

#endif //#ifndef _LCCM487__FAULT_FLAGS_H_

