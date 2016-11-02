/**
 * @file		rm4_firmware_version.h
 * @brief		Firmware version marker header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM364R0.FILE.002
 */

#ifndef __RM4_FIRMWARE_VERSION_H_
#define __RM4_FIRMWARE_VERSION_H_

	/*lint -e537*/
	#include <localdef.h>
	


	//function protos
	Luint16 u16RM4_FWVER__Get_LFWXXX(void);
	Luint8 u8RM4_FWVER__Get_Major(void);
	Luint8 u8RM4_FWVER__Get_Minor(void);
	Luint8 u8RM4_FWVER__Get_Debug(void);

#endif //__RM4_FIRMWARE_VERSION_H_
