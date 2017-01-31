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

#include <../../../BOARD_SUPPORT/lpcb234r0__board_support.h>

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
