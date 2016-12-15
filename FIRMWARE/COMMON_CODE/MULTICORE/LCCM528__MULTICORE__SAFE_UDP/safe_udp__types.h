/**
 * @file		SAFE_UDP__TYPES.H
 * @brief		SAFE UDP types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM528R0.FILE.009
 */

#ifndef __SAFE_UDP_SAFE_UDP__TYPES_H_
#define __SAFE_UDP_SAFE_UDP__TYPES_H_


		typedef enum
		{
			/** No fault has occurred */
			UDP_FAULT__NONE = 0x00U,

			/** A repetition fault occurred in the data stream */
			UDP_FAULT__REPEAT = 0x01U,

			/** A packet loss fault occurred */
			UDP_FAULT__LOSS = 0x02U,

			/** A packet insert fault occurred */
			UDP_FAULT__INSERT = 0x04U,

			/** A packet sequence fault occurred */
			UDP_FAULT__SEQUENCE = 0x08U,

			/** A packet corrupt fault occurred */
			UDP_FAULT__CORRUPT = 0x10U,

			/** A packet delayed fault occurred */
			UDP_FAULT__DELAY = 0x20U

		}SAFE_UDP__FAULTS_T;



#endif /* __SAFE_UDP_SAFE_UDP__TYPES_H_ */
