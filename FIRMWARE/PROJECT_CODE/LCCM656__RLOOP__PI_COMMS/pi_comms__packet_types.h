
#ifndef RLOOP_LCCM656__RLOOP__PI_COMMS_PI_COMMS__PACKET_TYPES_H_
#define RLOOP_LCCM656__RLOOP__PI_COMMS_PI_COMMS__PACKET_TYPES_H_


	/** Picomms standard packet types */
	typedef enum
	{

		/** unlock the pod safe command
		 * U32 */
		PI_PACKET__PWRNODE__POD_SAFE_UNLOCK_KEY = 0xA000U,

		/** Execute the pod safe command
		 * U32 */
		PI_PACKET__PWRNODE__POD_SAFE_COMMAND = 0xA001U,


		/** Node temperature streaming control
		 * U8 */
		PI_PACKET__PWRNODE__NODE_TEMP_STREAM_CONTROL = 0xA100U,

		/** Node temperature data
		 * F32, Degrees C
		 */
		PI_PACKET__PWRNODE__NODE_TEMP_RETURN = 0xA101U,


	}E_PICOMMS__PACKET_TYPES_T;



#endif /* RLOOP_LCCM656__RLOOP__PI_COMMS_PI_COMMS__PACKET_TYPES_H_ */
