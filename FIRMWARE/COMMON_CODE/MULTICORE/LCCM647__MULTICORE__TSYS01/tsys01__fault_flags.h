#ifndef _LCCM647__00__FAULT_FLAGS_H_
#define _LCCM647__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * A general fault has occured 
 * 
 * @tool
 * [CORE]|[00]|[GENERAL ]|[A general fault has occured ]
*/
#define C_LCCM647__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM647__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * GUARDING FAULT 
 * 
 * @note
 * A memory guarding fault has occurred. 
 * 
 * @tool
 * [CORE]|[01]|[GUARDING FAULT ]|[A memory guarding fault has occurred. ]
*/
#define C_LCCM647__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM647__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * RESET ERROR 
 * 
 * @note
 * An error occurred during reset. 
 * 
 * @tool
 * [CORE]|[02]|[RESET ERROR ]|[An error occurred during reset. ]
*/
#define C_LCCM647__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM647__CORE__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * READ K VALUES FAULT 
 * 
 * @note
 * An error occurred during reading the K values from the device. 
 * 
 * @tool
 * [CORE]|[03]|[READ K VALUES FAULT ]|[An error occurred during reading the K values from the device. ]
*/
#define C_LCCM647__CORE__FAULT_INDEX__03				0x00000003U
#define C_LCCM647__CORE__FAULT_INDEX_MASK__03			0x00000008U

#endif //#ifndef _LCCM647__FAULT_FLAGS_H_

