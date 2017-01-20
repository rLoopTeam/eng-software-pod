#ifndef _LCCM655__12__FAULT_FLAGS_H_
#define _LCCM655__12__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * A general fault has occurred in the track database module. 
*/
#define C_LCCM655__FCTL_TRACKDB__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__FCTL_TRACKDB__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * STRUCT SIZE MISMATCH 
 * 
 * There was a compile time mismatch between the defined structure size and 
 * the sizeof() structure size. This is a fatal error. 
*/
#define C_LCCM655__FCTL_TRACKDB__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__FCTL_TRACKDB__FAULT_INDEX_MASK__01			0x00000002U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

