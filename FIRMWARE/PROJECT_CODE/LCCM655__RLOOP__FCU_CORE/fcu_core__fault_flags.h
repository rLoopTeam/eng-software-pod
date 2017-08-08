#ifndef _LCCM655__14__FAULT_FLAGS_H_
#define _LCCM655__14__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * A general fault has occurred, check the other flags for more information. 
 * 
 * 
 * @tool
 * [CORE]|[00]|[GENERAL ]|[A general fault has occurred, check the other flags for more information. 
]
*/
#define C_LCCM655__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * GUARDING_FAULT 
 * 
 * @note
 * A memory guarding fault has occurred and the FCU data structure could be 
 * corrupt. 
 * 
 * @tool
 * [CORE]|[01]|[GUARDING_FAULT ]|[A memory guarding fault has occurred and the FCU data structure could be 
corrupt. ]
*/
#define C_LCCM655__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__CORE__FAULT_INDEX_MASK__01			0x00000002U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

