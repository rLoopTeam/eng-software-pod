/**
 * @file        power_core__bms__fault_flags.h
 * @brief       BMS system fault Flags
 * @author
 * @copyright   rLoop Inc.
 */

#ifndef _BMS__00__FAULT_FLAGS_H_
#define _BMS__00__FAULT_FLAGS_H_

/*
 * @fault_index
 * 00
 *
 * @brief
 * GENERAL
 *
 * A general fault has occurred.
*/
#define C_BMS__FAULT_INDEX__00               0x00000000U
#define C_BMS__FAULT_INDEX_MASK__00          0x00000001U

/*
 * @fault_index
 * 00
 *
 * @brief
 * GENERAL
 *
 * Undervoltage condition
*/
#define C_BMS__FAULT_INDEX__01               0x00000001U
#define C_BMS__FAULT_INDEX_MASK__01          0x00000002U

/*
 * @fault_index
 * 00
 *
 * @brief
 * GENERAL
 *
 * Overvoltage condition
*/
#define C_BMS__FAULT_INDEX__02               0x00000002U
#define C_BMS__FAULT_INDEX_MASK__02          0x00000004U

/*
 * @fault_index
 * 00
 *
 * @brief
 * GENERAL
 *
 * No voltage updates
*/
#define C_BMS__FAULT_INDEX__03               0x00000003U
#define C_BMS__FAULT_INDEX_MASK__03          0x00000008U

#endif /* _LCCM653__00__FAULT_FLAGS_H_ */
