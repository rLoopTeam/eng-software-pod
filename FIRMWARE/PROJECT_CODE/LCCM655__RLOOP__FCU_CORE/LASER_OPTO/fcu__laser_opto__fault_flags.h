#ifndef _LCCM655__10__FAULT_FLAGS_H_
#define _LCCM655__10__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * A General Fault Has Occured 
 * 
 * @tool
 * [LASER_OPTO]|[00]|[GENERAL ]|[A General Fault Has Occured ]
*/
#define C_LCCM655__LASER_OPTO__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__LASER_OPTO__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * CRC RELOAD 
 * 
 * @note
 * The CRC data was reloaded during INIT. Calibration could be invalid. 
 * 
 * @tool
 * [LASER_OPTO]|[01]|[CRC RELOAD ]|[The CRC data was reloaded during INIT. Calibration could be invalid. ]
*/
#define C_LCCM655__LASER_OPTO__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__LASER_OPTO__FAULT_INDEX_MASK__01			0x00000002U

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
 * [LASER_OPTO]|[02]|[GUARDING FAULT ]|[Memory Guarding Fault ]
*/
#define C_LCCM655__LASER_OPTO__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__LASER_OPTO__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * INJECTION ENABLED 
 * 
 * @note
 * Injection mode enabled, laser inputs are off line. 
 * 
 * @tool
 * [LASER_OPTO]|[03]|[INJECTION ENABLED ]|[Injection mode enabled, laser inputs are off line. ]
*/
#define C_LCCM655__LASER_OPTO__FAULT_INDEX__03				0x00000003U
#define C_LCCM655__LASER_OPTO__FAULT_INDEX_MASK__03			0x00000008U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

