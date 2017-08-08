#ifndef _LCCM655__02__FAULT_FLAGS_H_
#define _LCCM655__02__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * @note
 * General fault has occured. 
 * 
 * @tool
 * [LASER_OPTO_LASER]|[00]|[GENERAL ]|[General fault has occured. ]
*/
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX__00				0x00000000U
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * TRANSCEIVER FAIL 
 * 
 * @note
 * The transceiver associated with this channel has failed. 
 * 
 * @tool
 * [LASER_OPTO_LASER]|[01]|[TRANSCEIVER FAIL ]|[The transceiver associated with this channel has failed. ]
*/
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX__01				0x00000001U
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * BYTE TIMEOUT 
 * 
 * @note
 * No bytes were received from the laser. Could indicate wiring or laser config. 
 * 
 * 
 * @tool
 * [LASER_OPTO_LASER]|[02]|[BYTE TIMEOUT ]|[No bytes were received from the laser. Could indicate wiring or laser config. 
]
*/
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX__02				0x00000002U
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * PACKET TIMEOUT 
 * 
 * @note
 * There was a timeout on the packets, either no packets recieved, or many 
 * corrupted packets. 
 * 
 * @tool
 * [LASER_OPTO_LASER]|[03]|[PACKET TIMEOUT ]|[There was a timeout on the packets, either no packets recieved, or many 
corrupted packets. ]
*/
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX__03				0x00000003U
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX_MASK__03			0x00000008U

/*
 * @fault_index
 * 04
 * 
 * @brief
 * PACKET BYTE 1 COUNTER HIGH 
 * 
 * @note
 * A high number of packets failed on the first byte. 
 * 
 * @tool
 * [LASER_OPTO_LASER]|[04]|[PACKET BYTE 1 COUNTER HIGH ]|[A high number of packets failed on the first byte. ]
*/
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX__04				0x00000004U
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX_MASK__04			0x00000010U

/*
 * @fault_index
 * 05
 * 
 * @brief
 * OUT OF RANGE 
 * 
 * @note
 * Laser out of range error.

Note: This error is clearable. 
 * 
 * @tool
 * [LASER_OPTO_LASER]|[05]|[OUT OF RANGE ]|[Laser out of range error.

Note: This error is clearable. ]
*/
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX__05				0x00000005U
#define C_LCCM655__LASER_OPTO_LASER__FAULT_INDEX_MASK__05			0x00000020U

#endif //#ifndef _LCCM655__FAULT_FLAGS_H_

