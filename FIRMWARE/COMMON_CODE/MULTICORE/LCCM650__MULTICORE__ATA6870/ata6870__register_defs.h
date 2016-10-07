/**
 * @file		ATA6870__REGISTER_DEFS.H
 * @brief		Register definitions for the ATA6870 device.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.004
 */

 /*lint -e950*/
 
#ifndef _ATA6870_REG_DEFS_H_
#define _ATA6870_REG_DEFS_H_

	/**
	Table 7-24. Register Mapping
	Register	Control Field	Control Field	Register Name	Access	Type	Function
	Address		Read Mode		Write Mode
	------------------------------------------------------------------------------------------------
	0x00		0x00 			- 				RevID 			R 		8 bits 	Revision ID/value Mfirst, pow_on
	0x01 		0x02 			0x03 			Ctrl 			RW 		8 bits 	Control register
	0x02 		0x04 			0x05 			Operation 		RW 		8 bits 	Operation request
	0x03 		0x06 			- 				OpStatus 		R 		8 bits 	Operation status
	0x04 		- 				0x09 			Rstr 			W 		8 bits 	Software reset
	0x05 		0x0A 			0x0B 			IrqMask 		RW 		8 bits 	Mask interrupt sources
	0x06 		0x0C 			- 				Status 			R 		8 bits 	Status interrupt sources
	0x08 		0x10 			- 				ChannelUdvSts 	R 		8 bits	Channels undervoltage status
	0x09 		0x12 			0x13 			ChannelDischSel	RW 		8 bits	Select channel to discharge
	0x0A 		0x14 			0x15 			ChannelReadSel 	RW 		8 bits 	Select channel to read
	0x0B 		0x16 			0x17 			LFTimer 		RW 		8 bits 	Low frequency timer control
	0x0C 		0x18 			- 				CalibStatus 	R 		8 bits 	Reserved
	0x0D 		0x1A 			0x1B 			FuseCtrl 		RW 		8 bits 	Reserved
	0x10 		0x20 			0x21 			UdvThresh 		RW 		16 bits Undervoltage detection threshold
	0x11 		0x22 			- 				DataRd16 		R 		16 bits Single access to selected channel value
	0x12 		0x24 			0x25 			ATA6870NTest 	RW 		16 bits Reserved
	0x7F 		0xFE 			- 				DataRd16Burst 	R 		112 bits Burst Access to the whole channels (6 voltage and 1 temperature)
	*/
	typedef enum
	{
		ATA6870_REG__REV_ID = 0x00U,
		ATA6870_REG__CONTROL = 0x01U,
		ATA6870_REG__OPERATION = 0x02U,
		ATA6870_REG__OP_STATUS = 0x03U,
		ATA6870_REG__SW_RESET = 0x04U,
		ATA6870_REG__IRQ_MASK = 0x05U,
		ATA6870_REG__IRQ_STATUS = 0x06U,
		ATA6870_REG__CH_UNDERVOLT_STATUS = 0x08U,
		ATA6870_REG__CH_DISCHARGE = 0x09U,
		ATA6870_REG__CH_SELECT = 0x0AU,
		ATA6870_REG__LF_TIMER = 0x0BU,
		ATA6870_REG__CAL_STATUS = 0x0CU,
		ATA6870_REG__FUSE_CONTROL = 0x0DU,
		ATA6870_REG__UNDERVOLT_THRESH = 0x10U,
		ATA6870_REG__DATA_RD16 = 0x12U,
		ATA6870_REG__DATA_RD16_BURST = 0x7FU
	
	
	}ATA6870_REGS_T;

#endif //_ATA6870_REG_DEFS_H_


