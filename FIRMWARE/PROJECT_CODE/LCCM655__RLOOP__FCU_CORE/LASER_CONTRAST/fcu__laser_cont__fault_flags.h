#ifndef _LCCM655__06__FAULT_FLAGS_H_
#define _LCCM655__06__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * A general fault has occurred in the laser contrast module. 
 * 
 * @tool
 * [LASER CONTRAST]|[00]|[GENERAL ]|[A general fault has occurred in the laser contrast module. ]
*/
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX_MASK__00			0x00000001U

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
 * [LASER CONTRAST]|[01]|[GUARDING FAULT ]|[A memory guarding fault has occurred. ]
*/
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * TIMING LIST EXCEED 
 * 
 * @note
 * The amount of edges has exceed the timing list capacity, this is a big 
 * problem. 
 * 
 * @tool
 * [LASER CONTRAST]|[02]|[TIMING LIST EXCEED ]|[The amount of edges has exceed the timing list capacity, this is a big 
problem. ]
*/
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * INDEXING FAULT 
 * 
 * @note
 * The software tried to access an array index that was out of bounds. Need 
 * to recheck the software logic. 
 * 
 * @tool
 * [LASER CONTRAST]|[03]|[INDEXING FAULT ]|[The software tried to access an array index that was out of bounds. Need 
to recheck the software logic. ]
*/
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX__03				0x00000003U
#define C_LCCM655__LASER CONTRAST__FAULT_INDEX_MASK__03			0x00000008U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

