/**
 * @file		power_code__module_def.h
 * @brief		Main header for Module definition
 * @author		Edward Chan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID
 */

/*******************************************************************************
Defines
*******************************************************************************/
#define C_MODULEDEF__NUM_OF_DS18B20_TERMINAL 				(12U)
#define C_MODULEDEF__NUM_OF_DS18B20_CELL 					(3U)

/*******************************************************************************
Structures
*******************************************************************************/

typedef struct
{
	Luint8 u8SensorId[8];  // 8 bytes
	//Luint8 channelIdx; ??
}sPWR_CORE__MODULE_SENSORS;

typedef struct
{
	Luint8 u8ModuleSerialNumber[2U];
	sPWR_CORE__MODULE_SENSORS moduleTerminalSensors[C_MODULEDEF__NUM_OF_DS18B20_TERMINAL]; 	// Each module has 12 terminal sensors
	sPWR_CORE__MODULE_SENSORS moduleModuleSensors[C_MODULEDEF__NUM_OF_DS18B20_CELL]; 		// Each module has 3 cell sensors
}sPWR_CORE__MODULE;

#define MODULE_3506		{ \
							{0x35, 0x06}, \
							{ \
								{0x28, 0xFF, 0x70, 0xF7, 0xA0, 0x16, 0x03, 0x80}, \
								{0x28, 0xFF, 0x08, 0xF4, 0xA0, 0x16, 0x05, 0x86}, \
								{0x28, 0xFF, 0x0C, 0xA1, 0xA0, 0x16, 0x03, 0x1D}, \
								{0x28, 0xFF, 0x9C, 0xBA, 0xA0, 0x16, 0x03, 0x06}, \
								{0x28, 0xFF, 0x5C, 0xB8, 0xA0, 0x16, 0x04, 0xA0}, \
								{0x28, 0xFF, 0xFA, 0x8D, 0xA0, 0x16, 0x05, 0x98}, \
								{0x28, 0xFF, 0xC6, 0xC8, 0xA0, 0x16, 0x04, 0x02}, \
								{0x28, 0xFF, 0x36, 0xD9, 0xA0, 0x16, 0x05, 0x4D}, \
								{0x28, 0xFF, 0xAE, 0x7F, 0xA0, 0x16, 0x03, 0xB9}, \
								{0x28, 0xFF, 0xEE, 0xD0, 0xA0, 0x16, 0x03, 0x63}, \
								{0x28, 0xFF, 0x3D, 0xBC, 0xA0, 0x16, 0x03, 0xF1}, \
								{0x28, 0xFF, 0x17, 0xA8, 0xA0, 0x16, 0x05, 0x5F}, \
							}, \
							{ \
								{0x28, 0xFF, 0x63, 0x6B, 0x82, 0x16, 0x04, 0x19}, \
								{0x28, 0xFF, 0xCA, 0x84, 0xA0, 0x16, 0x04, 0xD1}, \
								{0x28, 0xFF, 0x3C, 0x8B, 0xA0, 0x16, 0x05, 0x2F}, \
							}, \
						}


sPWR_CORE__MODULE _strModules[18U] =
{
		MODULE_3506,
		MODULE_3506,
};
