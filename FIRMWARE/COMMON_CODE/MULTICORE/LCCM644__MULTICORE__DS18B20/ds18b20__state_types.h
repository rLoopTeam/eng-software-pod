/**
 * @file		DS18B20__STATE_TYPES.H
 * @brief		State type defines
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.009
 */



#ifndef __DS18B20_DS18B20__STATE_TYPES_H_
#define __DS18B20_DS18B20__STATE_TYPES_H_

	/** Main SM Types */
	typedef enum
	{

		/** Reset state */
		DS18B20_STATE__IDLE = 0U,

		/** Before we can use the devices we need to configure their resolutions */
		DS18B20_STATE__CONFIGURE_RESOLUTION,

		/** read back the resolution settings */
		DS18B20_STATE__READ_RESOLUTION,


		/** Start to convert all sensors */
		DS18B20_STATE__START_CONVERT_ALL,

		/** Wait for the conversion to finish, if needed. */
		DS18B20_STATE__WAIT_CONVERT,

		/** Read all the sensors */
		DS18B20_STATE__READ_SENSORS,

		/** Apply some delay between sensor reads to reduce bus time */
		DS18B20_STATE__READ_SENSOR_STATE_DELAY,

		/** Done reading the sensors, do any post processing */
		DS18B20_STATE__READ_DONE


	}E_DS18B20__MAIN_STATES;


	/** Seach for devices state types */
	typedef enum
	{

		/** Idle state, not doing anything */
		SEARCH_STATE__IDLE = 0U,

		/** Start searching, reset what we need to */
		SEARCH_STATE__START,

		/** running the search */
		SEARCH_STATE__RUN,

		/** Increment the channel counter */
		SEARCH_STATE__INC_CHANNEL,

		/** Cleanup the system and we are done */
		SEARCH_STATE__CLEANUP

	}E_DS18B20_SEARCH_T;

#endif /* __DS18B20_DS18B20__STATE_TYPES_H_ */
