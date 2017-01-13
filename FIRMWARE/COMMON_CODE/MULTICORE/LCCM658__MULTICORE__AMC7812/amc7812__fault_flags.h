#ifndef _LCCM658__00__FAULT_FLAGS_H_
#define _LCCM658__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * A general fault has occurred. 
*/
#define C_LCCM658__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM658__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * DAC INDEXING FAULT 
 * 
 * The index for a specific DAC channel was beyond the number of available 
 * DAC channels. 
*/
#define C_LCCM658__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM658__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * I2C FAULT 
 * 
 * The device has experienced an I2C fault that it could not recover from. 
 * 
*/
#define C_LCCM658__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM658__CORE__FAULT_INDEX_MASK__02			0x00000004U

#endif //#ifndef _LCCM658__FAULT_FLAGS_H_

