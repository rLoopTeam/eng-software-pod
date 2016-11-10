#ifndef _LCCM655__00__FAULT_FLAGS_H_
#define _LCCM655__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * A general fault has occurred. 
*/
#define C_LCCM655__BRAKES__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__BRAKES__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * MLP_RANGE_LIMIT_LOW 
 * 
 * The MLP sensor has a low range reading. 
*/
#define C_LCCM655__BRAKES__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__BRAKES__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * MLP_RANGE_LIMIT_HIGH 
 * 
 * The MLP sensor has a high range reading. 
*/
#define C_LCCM655__BRAKES__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__BRAKES__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * CALIBRATION DATA RELOAD
 
 * 
 * The calibration data was reloaded. This could indicate the cal data is 
 * invalid. 
*/
#define C_LCCM655__BRAKES__FAULT_INDEX__03				0x00000003U
#define C_LCCM655__BRAKES__FAULT_INDEX_MASK__03			0x00000008U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

