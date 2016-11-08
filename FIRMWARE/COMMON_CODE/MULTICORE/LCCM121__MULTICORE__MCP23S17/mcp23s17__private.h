/**
 * @file		MCP23S17__PRIVATE.H
 * @brief		Private Definitions.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571). This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM121R0.FILE.004
 */

#ifndef C_MCP23S17__REGISTER___PRIVATE_H_
#define C_MCP23S17__REGISTER___PRIVATE_H_

	typedef enum
	{
		MCP23S17_PORT__A = 0U,
		MCP23S17_PORT__B = 1U
	}MCP23S17__PORT_E;

	/*******************************************************************************
	REGISTER DEFS
	*******************************************************************************/
	#define C_MCP23S17__REGISTER__IODIRA 										(0x00U)
	#define C_MCP23S17__REGISTER__IODIRB										(0x01U)
	#define C_MCP23S17__REGISTER__IPOLA											(0x02U)
	#define C_MCP23S17__REGISTER__IPOLB											(0x03U)
	#define C_MCP23S17__REGISTER__GPINTENA										(0x04U)
	#define C_MCP23S17__REGISTER__GPINTENB										(0x05U)
	#define C_MCP23S17__REGISTER__DEFVALA										(0x06U)
	#define C_MCP23S17__REGISTER__DEFVALB										(0x07U)
	#define C_MCP23S17__REGISTER__INTCONA										(0x08U)
	#define C_MCP23S17__REGISTER__INTCONB										(0x09U)
	#define C_MCP23S17__REGISTER__IOCON											(0x0AU)
	#define C_MCP23S17__REGISTER__GPPUA											(0x0CU)
	#define C_MCP23S17__REGISTER__GPPUB											(0x0DU)
	#define C_MCP23S17__REGISTER__INTFA											(0x0EU)
	#define C_MCP23S17__REGISTER__INTFB											(0x0FU)
	#define C_MCP23S17__REGISTER__INTCAPA										(0x10U)
	#define C_MCP23S17__REGISTER__INTCAPB										(0x11U)
	#define C_MCP23S17__REGISTER__GPIOA											(0x12U)
	#define C_MCP23S17__REGISTER__GPIOB											(0x13U)
	#define C_MCP23S17__REGISTER__OLATA											(0x14U)
	#define C_MCP23S17__REGISTER__OLATB											(0x15U)


#endif
