/*
 * fcu__asi_types.h
 *
 *  Created on: Dec 9, 2016
 *      Author: Lachlan
 */

#ifndef _FCU__ASI_TYPES_H_
#define _FCU__ASI_TYPES_H_

	// modbus frame size for read/write register commands
	#define C_ASI__RW_FRAME_SIZE				(8)


		typedef enum
		{
			FUCNTION_CODE__READ_COILS = 0x01U,
			FUNCTION_CODE__READ_DISCRETE_INPUTS = 0x02U,
			FUNCTION_CODE__READ_HOLDING_REGS = 0x03U,
			FUNCTION_CODE__READ_INPUT_REGS = 0x04U,
			FUNCTION_CODE__WRITE_SINGLE_COIL = 0x05U,
			FUNCTION_CODE__WRITE_SINGLE_REG = 0x06U

		}E_FCU_ASI__FUNCTION_CODE_T;

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
			E_NONE = 0U,
			E_SLAVE_MISMATCH,
			E_CRC_CHECK_FAILED,
			E_REPLY_TIMEOUT_EXPIRED,
			E_ERROR_RESPONSE
		} E_ERR_TYPE;


		/** ASI command parameter register address */
		// see ASI BAC object Dictionary document for more
		typedef enum
		{
			C_FCU_ASI__OVER_TEMP_THRESHOLD = 90U,
			C_FCU_ASI__FOLDBACK_STARING_TEMP = 91U,
			C_FCU_ASI__FOLDBACK_END_TEMP = 92U,
			C_FCU_ASI__COMMAND_SOURCE = 208U,
			C_FCU_ASI__CONTROLLER_STATUS = 257U,
			C_FCU_ASI__FAULTS = 0x0102U,
			C_FCU_ASI__CONT_TEMP = 259U,
			C_FCU_ASI__TEMPERATURE = 261U,
			C_FCU_ASI__MOTOR_CURRENT = 262U,
			C_FCU_ASI__MOTOR_RPM = 263U,
			C_FCU_ASI__LAST_FAULT = 269U,
			C_FCU_ASI__RAW_SENSOR_TEMPERATURE = 273U,
			C_FCU_ASI__SAVE_SETTINGS = 511U

		}E_FCU_ASI_BAC_OBJECT_TYPES__T;


		/** ASI controller modbus read/write register command structure */
		struct _strASICmd
		{
			/** The slave address, for all purposes this can be 1*/
			Luint8 u8SlaveAddress;

			/** Modbus function code */
			E_FCU_ASI__FUNCTION_CODE_T eFunctionCode;

			/** The tyype of BAC object we want */
			E_FCU_ASI_BAC_OBJECT_TYPES__T eObjectType;

			/** for reading, this is num of registers to read, set to 1 */
			Luint16 u16ParamValue;

			/** The command ready to transmit */
			Luint8 framedCmd[C_ASI__RW_FRAME_SIZE];

			/** assuming we always read only one register */
			Luint8 u8Response[C_ASI__RW_FRAME_SIZE];

			/** The returned destination variable */
			union
			{
				Luint8 u8[4];
				Lint8 s8[4];
				Luint16 u16[2];
				Lint16 s16[2];
			}unDestVar;

			E_VAR_TYPE eDestVarType;
			E_ERR_TYPE eErrorType;
		};


#endif /* _FCU__ASI_TYPES_H_ */
