#ifndef _LCCM655__04__FAULT_FLAGS_H_
#define _LCCM655__04__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * A General Fault has Occurred 
*/
#define C_LCCM655__THROTTLES__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__THROTTLES__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * AMC7812 FAULT 
 * 
 * A fault has occurred on the AMC7812 device, check its flags. 
*/
#define C_LCCM655__THROTTLES__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__THROTTLES__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * INDEXING FAULT 
 * 
 * A request was made to index something out of range. 
*/
#define C_LCCM655__THROTTLES__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__THROTTLES__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * THROTTLE NOT IN RUN MODE 
 * 
 * The throttles have not transitioned to RUN mode, this is a big issue. This 
 * flag should be cleared after reset. 
*/
#define C_LCCM655__THROTTLES__FAULT_INDEX__03				0x00000003U
#define C_LCCM655__THROTTLES__FAULT_INDEX_MASK__03			0x00000008U

/*
 * @fault_index
 * 04
 * 
 * @brief
 * DEV MODE ENABLED 
 * 
 * We are in development mode, this must not appear in flight. 
*/
#define C_LCCM655__THROTTLES__FAULT_INDEX__04				0x00000004U
#define C_LCCM655__THROTTLES__FAULT_INDEX_MASK__04			0x00000010U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

