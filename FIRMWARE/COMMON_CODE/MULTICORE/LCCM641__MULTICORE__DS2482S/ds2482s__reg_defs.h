/**
 * @file		DS2482S__REG_DEFS.H
 * @brief		Main register definitions from the datasheet.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.003
 */

#ifndef _DS2482S_REG_DEFS_H_
#define _DS2482S_REG_DEFS_H_

	/*lint -e950*/

	typedef enum
	{

		/**
		 * Device Reset
		 * Command Code				F0h
		 * Command Parameter		None
		 * Description				Performs a global reset of device state machine logic. Terminates any ongoing 1-Wire
		 * 							communication.
		 * Typical Use 				Device initialization after power-up; reinitialization (reset) as desired.
		 * Restriction 				None (can be executed at any time).
		 * Error Response 			None
		 * Command Duration 		Maximum 525ns. Counted from falling SCL edge of the command code acknowledge bit.
		 * 1-Wire Activity 			Ends maximum 262.5ns after the falling SCL edge of the command code acknowledge bit.
		 * Read Pointer Position 	Status Register (for busy polling).
		 * Status Bits Affected 	RST set to 1; 1WB, PPD, SD, SBR, TSB, DIR set to 0.
		 * Config Bits Affected 	1WS, APU, SPU set to 0.
		 */
		DS2482_REGS__COMMAND_RESET	= 0xF0U,


		/**
		 * Set Read Pointer
		 * Command Code 			E1h
		 * Command Parameter 		Pointer Code (see Table 1)
		 * Description				Sets the read pointer to the specified register. Overwrites the read pointer position of any 1-Wire
		 * 							communication command in progress.
		 * Typical Use				To prepare reading the result from a 1-Wire Read Byte command; random read access of
		 * 							registers.
		 * Restriction None 		(can be executed at any time).
		 * Error Response 			If the pointer code is not valid, the pointer code is not acknowledged and the command is ignored.
		 * Command Duration 		None. The read pointer is updated on the rising SCL edge of the pointer code acknowledge bit.
		 * 							1-Wire Activity Not affected.
		 * Read Pointer Position 	As specified by the pointer code.
		 * Status Bits Affected		None
		 * Config Bits Affected 	None
		 */
		DS2482_REGS__COMMAND_SET_READ_POINTER	= 0xE1U,

		/**
		 * Write Configuration
		 * Command Code 			D2h
		 * Command Parameter 		Configuration Byte
		 * Description				Writes a new configuration byte. The new settings take effect immediately. Note: When writing to
		 * 							the Configuration Register, the new data is accepted only if the upper nibble (bits 7 to 4) is the
		 * 							one's complement of the lower nibble (bits 3 to 0). When read, the upper nibble is always 0h.
		 * Typical Use 				Defining the features for subsequent 1-Wire communication.
		 * Restriction 				1-Wire activity must have ended before the DS2482-100 can process this command.
		 * Error Response			Command code and parameter are not acknowledged if 1WB = 1 at the time the command code
		 * 							is received and the command is ignored.
		 * Command Duration			None. The Configuration Register is updated on the rising SCL edge of the configuration-byte
		 * 							acknowledge bit.
		 * 1-Wire Activity 			None
		 * Read Pointer Position 	Configuration Register (to verify write).
		 * Status Bits Affected 	RST set to 0.
		 * Config Bits Affected 	1WS, SPU, APU updated.
		 */
		DS2482_REGS__COMMAND_WRITE_CONFIG	= 0xD2U,

		/**
		 * 1-Wire Reset
		 * Command Code				B4h
		 * Command Parameter 		None
		 * Description				Generates a 1-Wire reset/presence-detect cycle (Figure 4) at the 1-Wire line. The state of the
		 * 							1-Wire line is sampled at tSI and tMSP and the result is reported to the host processor through the
		 * 							Status Register, bits PPD and SD.
		 * Typical Use 				To initiate or end any 1-Wire communication sequence.
		 * Restriction				1-Wire activity must have ended before the DS2482-100 can process this command. Strong
		 * 							pullup (see the SPU bit) should not be used in conjunction with the 1-Wire Reset command. If SPU
		 * 							is enabled, the PPD bit may not be valid and may cause a violation of the devices absolute
		 * 							maximum rating.
		 * Error Response			Command code is not acknowledged if 1WB = 1 at the time the command code is received and
		 * 							the command is ignored.
		 * Command Duration			tRSTL + tRSTH + maximum 262.5ns, counted from the falling SCL edge of the command code
		 * 							acknowledge bit.
		 * 1-Wire Activity 			Begins maximum 262.5ns after the falling SCL edge of the command code acknowledge bit.
		 * Read Pointer Position 	Status Register (for busy polling).
		 * Status Bits Affected 	1WB (set to 1 for tRSTL + tRSTH), PPD is updated at tRSTL + tMSP, SD is updated at tRSTL + tSI.
		 * Config Bits Affected 	1WS, APU, SPU apply.
		 */
		DS2482_REGS__COMMAND_1_WIRE_RESET	= 0xB4U,

		/**
		 * 1-Wire Single Bit
		 * Command Code 			87h
		 * Command Parameter 		Bit Byte
		 * Description				Generates a single 1-Wire time slot with a bit value  as specified by the bit byte at the 1-Wire
		 * 							line (see Table 2). A value of 0b generates a write-zero time slot (Figure 5); a value of 1b
		 * 							generates a write-one time slot, which also functions as a read-data time slot (Figure 6). In either
		 * 							case, the logic level at the 1-Wire line is tested at tMSR and SBR is updated.
		 * Typical Use				To perform single-bit writes or reads at the 1-Wire line when single bit communication is
		 *							necessary (the exception).
		 * Restriction 				1-Wire activity must have ended before the DS2482-100 can process this command.
		 * Error Response			Command code and bit byte are not acknowledged if 1WB = 1 at the time the command code is
		 * 							received and the command is ignored.
		 * Command Duration 		tSLOT + maximum 262.5ns, counted from the falling SCL edge of the first bit (MSB) of the bit byte.
		 * 1-Wire Activity 			Begins maximum 262.5ns after the falling SCL edge of the MSB of the bit byte.
		 * Read Pointer Position 	Status Register (for busy polling and data reading).
		 * Status Bits Affected 	1WB (set to 1 for tSLOT), SBR is updated at tMSR, DIR (may change its state).
		 * Config Bits Affected 	1WS, APU, SPU apply.
		 */
		DS2482_REGS__COMMAND_1_WIRE_SINGLE_BIT	= 0x87U,

		/**
		 * 1-Wire Write Byte
		 * Command Code				A5h
		 * Command Parameter 		Data Byte
		 * Description 				Writes a single data byte to the 1-Wire line.
		 * Typical Use				To write commands or data to the 1-Wire line. Equivalent to executing eight 1-Wire Single Bit
		 * 							commands, but faster due to less I2C traffic.
		 * Restriction 				1-Wire activity must have ended before the DS2482-100 can process this command.
		 * Error Response			Command code and data byte are not acknowledged if 1WB = 1 at the time the command code is
		 * 							received and the command is ignored.
		 * Command Duration 		8 x tSLOT + maximum 262.5ns, counted from falling edge of the last bit (LSB) of the data byte.
		 * 1-Wire Activity			Begins maximum 262.5ns after falling SCL edge of the LSB of the data byte (i.e., before the data
		 * 							byte acknowledge). Note: The bit order on the I2C bus and the 1-Wire line is different (1-Wire: LSB
		 * 							first; I2C: MSB first). Therefore, 1-Wire activity cannot begin before the DS2482-100 has received
		 * 							the full data byte.
		 * Read Pointer Position 	Status Register (for busy polling).
		 * Status Bits Affected 	1WB (set to 1 for 8 x tSLOT).
		 * Config Bits Affected 	1WS, SPU, APU apply.
		 */
		DS2482_REGS__COMMAND_1_WIRE_WRITE_BYTE	= 0xA5U,

		/**
		 * 1-Wire Read Byte
		 * Command Code 			96h
		 * Command Parameter 		None
		 * Description				Generates eight read-data time slots on the 1-Wire line and stores result in the Read Data
		 * 							Register.
		 * Typical Use				To read data from the 1-Wire line. Equivalent to executing eight 1-Wire Single Bit commands with
		 * 							V = 1 (write-one time slot), but faster due to less I2C traffic.
		 * Restriction 				1-Wire activity must have ended before the DS2482-100 can process this command.
		 * Error Response			Command code is not acknowledged if 1WB = 1 at the time the command code is received and
		 * 							the command is ignored.
		 * Command Duration			8 x tSLOT + maximum 262.5ns, counted from the falling SCL edge of the command code
		 * 							acknowledge bit.
		 * 1-Wire Activity 			Begins maximum 262.5ns after the falling SCL edge of the command code acknowledge bit.
		 * Read Pointer Position	Status Register (for busy polling). Note: To read the data byte received from the 1-Wire line, issue
		 * 							the Set Read Pointer command and select the Read Data Register. Then access the DS2482-100
		 * 							in read mode.
		 * Status Bits Affected 	1WB (set to 1 for 8 x tSLOT).
		 * Config Bits Affected 	1WS, APU apply.
		 */
		DS2482_REGS__COMMAND_1_WIRE_READ_BYTE	= 0x96U,

		/**
		 * 1-Wire Triplet
		 * Command Code 			78h
		 * Command Parameter		Direction Byte
		 * Description				Generates three time slots: two read time slots and one write time slot at the 1-Wire line. The type
		 * 							of write time slot depends on the result of the read time slots and the direction byte. The direction
		 * 							byte determines the type of write time slot if both read time slots are 0 (a typical case). In this
		 * 							case, the DS2482-100 generates a write-one time slot if = 1 and a write-zero time slot if = 0.
		 * 							See Table 3.
		 * 							* If the read time slots are 0 and 1, they are followed by a write-zero time slot.
		 * 							* If the read time slots are 1 and 0, they are followed by a write-one time slot.
		 * 							* If the read time slots are both 1 (error case), the subsequent write time slot is a write-one.
		 * Typical Use				To perform a 1-Wire Search ROM sequence; a full sequence requires this command to be
		 * 							executed 64 times to identify and address one device.
		 * Restriction 				1-Wire activity must have ended before the DS2482-100 can process this command.
		 * Error Response			Command code and direction byte is not acknowledged if 1WB = 1 at the time the command
		 * 							code is received and the command is ignored.
		 * Command Duration 		3 x tSLOT + maximum 262.5ns, counted from the falling SCL edge of the first bit (MSB) of the
		 * 							direction byte.
		 * 1-Wire Activity 			Begins maximum 262.5ns after the falling SCL edge of the MSB of the direction byte.
		 * Read Pointer Position 	Status Register (for busy polling).
		 * Status Bits Affected		1WB (set to 1 for 3 x tSLOT), SBR is updated at the first tMSR, TSB and DIR are updated at the
		 * 							second tMSR (i.e., at tSLOT + tMSR).
		 * Config Bits Affected 	1WS, APU apply.
		 */
		DS2482_REGS__COMMAND_1_WIRE_TRIPLET	= 0x78U


	}E_DS2482_REGS;


	/** Set read pointer types */
	typedef enum
	{

		DS2482_POINTER__STATUS = 0xF0U,
		DS2482_POINTER__DATA = 0xE1U,
		DS2482_POINTER__CONFIG = 0xC3U


	}E_DS2482_POINTER_T;



#endif //_DS2482S_REG_DEFS_H_
