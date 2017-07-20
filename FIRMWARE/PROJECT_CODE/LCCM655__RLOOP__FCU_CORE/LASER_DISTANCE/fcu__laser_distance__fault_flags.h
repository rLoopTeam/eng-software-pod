#ifndef _LCCM655__08__FAULT_FLAGS_H_
#define _LCCM655__08__FAULT_FLAGS_H_
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
 * [LASER_DISTANCE]|[00]|[GENERAL ]|[A general fault has occurred. ]
*/
#define C_LCCM655__LASER_DISTANCE__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__LASER_DISTANCE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * NO BYTES 
 * 
 * @note
 * No bytes were seen from the laser in 500ms 
 * 
 * @tool
 * [LASER_DISTANCE]|[01]|[NO BYTES ]|[No bytes were seen from the laser in 500ms ]
*/
#define C_LCCM655__LASER_DISTANCE__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__LASER_DISTANCE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * NO PACKETS 
 * 
 * @note
 * No packets were seen from the laser in 500ms 
 * 
 * @tool
 * [LASER_DISTANCE]|[02]|[NO PACKETS ]|[No packets were seen from the laser in 500ms ]
*/
#define C_LCCM655__LASER_DISTANCE__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__LASER_DISTANCE__FAULT_INDEX_MASK__02			0x00000004U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

