#ifndef _LCCM641__00__FAULT_FLAGS_H_
#define _LCCM641__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * A general fault has occurred. 
 * 
 * @tool
 * [CORE]|[00]|[GENERAL ]|[A general fault has occurred. ]
*/
#define C_LCCM641__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM641__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * DEVICE STATUS FAIL 
 * 
 * @note
 * The device failed a status read during Init(). 
 * 
 * @tool
 * [CORE]|[01]|[DEVICE STATUS FAIL ]|[The device failed a status read during Init(). ]
*/
#define C_LCCM641__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM641__CORE__FAULT_INDEX_MASK__01			0x00000002U

#endif //#ifndef _LCCM641__FAULT_FLAGS_H_

