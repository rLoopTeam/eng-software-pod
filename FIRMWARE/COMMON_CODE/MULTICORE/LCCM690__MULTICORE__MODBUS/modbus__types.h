/**
 * @file		MODBUS__TYPES.H
 * @brief		Type Defines
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM690R0.FILE.004
 */

#ifndef _MODBUS_TYPES_H_
#define _MODBUS_TYPES_H_

	/** Modbus master states */
	typedef enum
	{

		/** Idle out of reset */
		MASTER_STATE__IDLE = 0U,

		/** User wants to issue a command to a slave, start the transmission process */
		MASTER_STATE__START_TX,

		/** Wait for the Tx to complete */
		MASTER_STATE__WAIT_TX,

		
		/** Wait Rx after a read command */
		MASTER_STATE__WAIT_RX_READ,

		/** We passed the Rx frame check */
		MASTER_STATE__RX_FRAME_CHECK_DONE,

		/** The CRC check has now been completed */
		MASTER_STATE__RX_CRC_CHECK_DONE,


	}TE_MODBUS__MASTER_STATES;


	/** Modbus Function Codes */
	typedef enum
	{
		
		/** Access: 1 bit
		 * Read Internal Bits or Physical Coils
		 */
		MODBUS_FUNCCODE__READ_COILS = 1U,
		
		/** Access: 1 bit
		 * Read Physical Discrete Inputs
		 */		
		MODBUS_FUNCCODE__READ_DISCRETE_INPUTS = 2U,
		
		/** Access: 16 bit
		 * Internal Registers or Physical Output Registers
		 */
		 MODBUS_FUNCCODE__READ_MULTIPLE_HOLDING_REGS = 3U,
		
		/** Access: 16 bit
		 * Read Physical Input Registers
		 */
		MODBUS_FUNCCODE__READ_INPUT_REGS = 4U,
		
		/** Access: 1 bit
		 * Write Internal Bits or Physical Coils
		 */
		MODBUS_FUNCCODE__WRITE_SINGLE_COIL = 5U,

		/** Access: 16 bit
		 * Write Internal Registers or Physical Output Registers
		 */
		MODBUS_FUNCCODE__WRITE_SINGLE_HOLDING_REG = 6U,

		/** Access: 1 bit
		 * Write Internal Bits or Physical Coils
		 */
		MODBUS_FUNCCODE__WRITE_MULTIPLE_COILS = 15U,
		
		/** Access: 16 bit
		 * Internal Registers or Physical Output Registers
		 */
		MODBUS_FUNCCODE__WRITE_MULTIPLE_HOLDING_REGS = 16U,
		
		/** Access: 16 bit
		 * Internal Registers or Physical Output Registers
		 */
		MODBUS_FUNCCODE__WRITE_REG = 22U,
		
		/** Access: 16 bit
		 * Internal Registers or Physical Output Registers
		 */
		MODBUS_FUNCCODE__WRITE_MULTIPLE_REGS = 23U,
		
		
	}TE_MODBUS__FUNCTION_CODE;

	
	/** Modbus Variable Types */
	typedef enum
	{
		MODBUS_VARTYPE_INT8 = 0X11,
		MODBUS_VARTYPE_UINT8 = 0X12,
		MODBUS_VARTYPE_INT16 = 0X21,
		MODBUS_VARTYPE_UINT16 = 0X22,
		MODBUS_VARTYPE_INT32 = 0X41,
		MODBUS_VARTYPE_UINT32 = 0X42,
		MODBUS_VARTYPE_INT64 = 0X81,
		MODBUS_VARTYPE_UINT64 = 0X82
	}TS_MODBUS__VARIABLE_TYPE;

#endif //_MODBUS_TYPES_H_
