/*
 * fcu__asi_types.h
 *
 *  Created on: Dec 9, 2016
 *      Author: Lachlan
 */

#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_ASI_RS485_FCU__ASI_TYPES_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_ASI_RS485_FCU__ASI_TYPES_H_

	// modbus frame size for read/write register commands
	#define C_ASI__RW_FRAME_SIZE				(8)

		/** variable type to set requested variable to ASI response */
		typedef enum
		{
			E_INT8 = 0X11,
			E_UINT8 = 0X12,
			E_INT16 = 0X21,
			E_UINT16 = 0X22,
			E_INT32 = 0X41,
			E_UINT32 = 0X42,
			E_INT64 = 0X81,
			E_UINT64 = 0X82
		} E_VAR_TYPE;

		/** variable type to set requested variable to ASI response */
		typedef enum
		{
			E_NONE,
			E_SLAVE_MISMATCH,
			E_CRC_CHECK_FAILED,
			E_REPLY_TIMEOUT_EXPIRED,
			E_ERROR_RESPONSE
		} E_ERR_TYPE;

		/** ASI controller modbus read/write register command structure */
		struct _strASICmd
		{
			Luint8 u8SlaveAddress;
			Luint8 fncCode;			// C_ASI__READ_INPUT_REGISTER or C_ASI__WRITE_SINGLE_REGISTER
			Luint16 paramAddress;
			Luint16 paramValue;		// for reading, this is num of registers to read, set to 1
			Luint8 framedCmd[C_ASI__RW_FRAME_SIZE];
			Luint8 response[C_ASI__RW_FRAME_SIZE];	// assuming we always read only one register
			void* destVar;
			E_VAR_TYPE eDestVarType;
			Lint8 retry;
			E_ERR_TYPE eErrorType;
		};


#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_ASI_RS485_FCU__ASI_TYPES_H_ */
