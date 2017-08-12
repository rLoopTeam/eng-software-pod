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
 * A general fault has occurred. 
 * 
 * @tool
 * [ASI]|[00]|[GENERAL ]|[A general fault has occurred. ]
*/
#define C_LCCM655__ASI__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__ASI__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * PHY FAIL 
 * 
 * @note
 * A phy associated with the ASI subsystem has failed. 
 * 
 * @tool
 * [ASI]|[01]|[PHY FAIL ]|[A phy associated with the ASI subsystem has failed. ]
*/
#define C_LCCM655__ASI__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__ASI__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * GUARDING FAULT 
 * 
 * @note
 * Memory Guarding Fault 
 * 
 * @tool
 * [ASI]|[02]|[GUARDING FAULT ]|[Memory Guarding Fault ]
*/
#define C_LCCM655__ASI__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__ASI__FAULT_INDEX_MASK__02			0x00000004U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

