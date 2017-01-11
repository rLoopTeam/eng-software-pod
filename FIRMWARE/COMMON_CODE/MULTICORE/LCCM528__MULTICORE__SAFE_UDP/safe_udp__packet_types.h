/**
 * @file		SAFE_UDP__PACKET_TYPES.H
 * @brief		Packet type defines for the entire safeUDP system
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM528R0.FILE.010
 */



#ifndef _SAFE_UDP__PACKET_TYPES_H_
#define _SAFE_UDP__PACKET_TYPES_H_

	/** globally defined packet types */
	typedef enum
	{
		SAFE_UDP__NONE = 0U,

		////////////////////////////////////////////////
		// LCCM111 - ADV7180 CAMERA
		// 0x1100 - 0x11FF
		////////////////////////////////////////////////

		/** Request an image from board to Host */
		SAFE_UDP__LCCM111__REQUEST_IMAGE = 0x1100U,

		/** device returning an image chunk */
		SAFE_UDP__LCCM111__RETURN_IMAGER_CHUNK = 0x1101U,


        ////////////////////////////////////////////////
        // LCCM662 - DAQ
        // 0x1200 - 0x12FF
        ////////////////////////////////////////////////
        SAFE_UDP__LCCM662__DAQ_STREAMING_CONTROL = 0x1200U,

        //support 64 streams
        SAFE_UDP__LCCM662__DAQ_DATA_PACKET_START = 0x1210U,
        SAFE_UDP__LCCM662__DAQ_DATA_PACKET_END = 0x1290U,

		////////////////////////////////////////////////
		// LCCM659
        // 0x1300 - 0x13FF
		////////////////////////////////////////////////

		/** Streaming control, Block0: = 0,1 */
        SAFE_UDP__LCCM659__ENABLE_ETH_STREAMING = 0x1300U,

		/** Device to Host, transmit a streaming data packet */
        SAFE_UDP__LCCM659__TX_STREAM_DATA = 0x1301U,



		////////////////////////////////////////////////
		// LCCM293 - CNC MACHINE - XYZ
		// 0x2100 - 0x21FF
		////////////////////////////////////////////////
		/** 6 Axis move packet */
		SAFE_UDP__LCCM293__MOVE_6_AXIS = 0x2100U,

		/** Task has been completed */
		SAFE_UDP__LCCM293__TASK_COMPLETE = 0x2101U,

		/** FIFO has accepted the task */
		SAFE_UDP__LCCM293__FIFO_ACK = 0x2102U,

		/** FIFO has been popped and we can get a result code */
		SAFE_UDP__LCCM293__FIFO_POP = 0x2103U,

		/** host PC requests motor settings from us */
		SAFE_UDP__LCCM293__REQUEST_MOTOR_SETTINGS = 0x2104U,

		/** host PC sends settings to us */
		SAFE_UDP__LCCM293__UPDATE_MOTOR_SETTINGS = 0x2105U,

		/** We send motor settings to PC */
		SAFE_UDP__LCCM293__SEND_MOTOR_SETTINGS = 0x2106U,

		/** We send update to PC */
		SAFE_UDP__LCCM293__POSITION_UPDATE = 0x2107U,

		SAFE_UDP__LCCM293_SET_ZERO = 0x2108U,

		SAFE_UDP__LCCM293_SET_HOME_ZERO = 0x2109U,



		////////////////////////////////////////////////
		// LCCM493 - CNC MACHINE - PNP HEAD
		// 0x2200 - 0x22FF
		////////////////////////////////////////////////

		/** switch the vac on in order to pick up a part */
		SAFE_UDP__LCCM493__VAC_ON = 0x2200U,

		/** switch the vac off and vent in order to drop a part */
		SAFE_UDP__LCCM493__VENT_ON = 0x2201U,

		/** Vac Off, vent vac from line and then use air pressure to
		 * break the vac. Air pressure time is only a few ms. */
		SAFE_UDP__LCCM493__VENT_BREAK = 0x2202U,

		/** switch the vac off and vent in order to drop a part
		 * ONLY do this after reception of a valid task ID from the other controller */
		SAFE_UDP__LCCM493__VENT_ON_AFTER_TASK = 0x2203U,

		/** From device to PC */
		SAFE_UDP__LCCM493__RETURN_TASK_STATUS = 0x2204U,

		/** From device to PC */
		SAFE_UDP__LCCM493__RETURN_GENERAL_STATUS = 0x2205U,

		/** from device to PC, returning the pressure in the pump */
		SAFE_UDP__LCCM493__RETURN_PRESSURE = 0x2206U,


		/** Blank Task */
		SAFE_UDP__LCCM493__TASK_NONE = 0x22FEU,

		////////////////////////////////////////////////
		// LCCM494 - CNC MACHINE - REFLOW OVEN
		// 0x2300 - 0x23FF
		////////////////////////////////////////////////

		/** Start the reflow oven process */
		SAFE_UDP__LCCM494__START_PROCESS = 0x2300U,

		/** Stop the oven */
		SAFE_UDP__LCCM494__STOP_PROCESS = 0x2301U,

		/** Send the current temperature*/
		SAFE_UDP__LCCM494__TX_TEMPERATURE = 0x2302U,


		////////////////////////////////////////////////
		// LCCM312 - MICROLMS - ECU
		// 0x2900 - 0x31FF
		////////////////////////////////////////////////
		/** Request a full packet to be sent with the pressure details */
		SAFE_UDP__LCCM312__ECU__PRESSURE_REQUEST_FULL = 0x3000U,

		/** Request a pressure settings packet to be sent */
		SAFE_UDP__LCCM312__ECU__PRESSURE_REQUEST_SETTINGS = 0x3001U,

		/** Set the AD7730 user zero */
		SAFE_UDP__LCCM312__ECU__PRESSURE_SET_AD7730_ZERO = 0x3002U,

		/** Set the AD7730 user span */
		SAFE_UDP__LCCM312__ECU__PRESSURE_SET_AD7730_SPAN = 0x3003U,
		SAFE_UDP__LCCM312__ECU__PRESSURE_REQUEST_CYL_SETTINGS = 0x3004U,
		SAFE_UDP__LCCM312__ECU__PRESSURE_SET_CYL_ROD_DIA = 0x3005U,
		SAFE_UDP__LCCM312__ECU__PRESSURE_SET_CYL_BORE_DIA = 0x3006U,
		SAFE_UDP__LCCM312__ECU__PRESSURE_SET_CYL_ANNULUS = 0x3007U,
		SAFE_UDP__LCCM312__ECU__PRESSURE_SET_CYL_EFFY = 0x3008U,

		/** Adjust the zero of the sensor */
		SAFE_UDP__LCCM312__ECU__PRESSURE_ADJUST_SENSOR_ZERO = 0x3009U,

		/** return a full packet of sensor data */
		SAFE_UDP__LCCM312__ECU__PRESSURE_RETURN_FULL = 0x300AU,

		/** return a full pressure sensor settings packet */
		SAFE_UDP__LCCM312__ECU__PRESSURE_RETURN_SETTINGS = 0x300BU,


		/** ECU to send settings for cylinders to host */
		SAFE_UDP__LCCM312__ECU__PRESSURE_RETURN_CYLINDERS = 0x300CU,

		/** Spare Slots */


		/** Adjust the fine zero of an individual sensor */
		SAFE_UDP__LCCM312__ECU__ACCEL_SET_FINE_ZERO = 0x3010U,

		/** adjust coarse zero on accel sensor is avail */
		SAFE_UDP__LCCM312__ECU__ACCEL_SET_COARSE_ZERO = 0x3011U,

		/** Auto zero of an individual sensor */
		SAFE_UDP__LCCM312__ECU__ACCEL_SET_AUTO_ZERO = 0x3012U,

		/** Set the live pitch angle based on the current hardware readings */
		SAFE_UDP__LCCM312__ECU__PITCH_SET_LIVE_ZERO = 0x3013U,

		/** Set the live roll angle */
		SAFE_UDP__LCCM312__ECU__ROLL_SET_LIVE_ZERO = 0x3014U,

		/** Set a fine zero on the Gyro */
		SAFE_UDP__LCCM312__ECU__GYRO_SET_FINE_ZERO = 0x3015U,

		/** Spare Slots */

		/** Set the current attach ID (attach change */
		SAFE_UDP__LCCM312__ECU__SET_ATTACH_INDEX = 0x3020U,

		/** Set the chassis zero */
		SAFE_UDP__LCCM312__ECU__SET_CHASSIS_ZERO = 0x3021U,
		SAFE_UDP__LCCM312__ECU__RETURN_CHASSIS_ZERO_ACK = 0x3022U,

		/** Set the boom zero */
		SAFE_UDP__LCCM312__ECU__SET_BOOM_ZERO = 0x3023U,
		SAFE_UDP__LCCM312__ECU__RETURN_BOOM_ZERO_ACK = 0x3024U,

		/** Set the carriage zero load */
		SAFE_UDP__LCCM312__ECU__SET_CARRIAGE_ZERO = 0x3025U,
		SAFE_UDP__LCCM312__ECU__RETURN_CARRIAGE_ZERO_ACK = 0x3026U,

		/** Span the boom length */
		SAFE_UDP__LCCM312__ECU__SPAN_LENGTH = 0x3027U,
		SAFE_UDP__LCCM312__ECU__RETURN_SPAN_LENGTH_ACK = 0x3028U,

		/** Spare slots */

		/** request a full packet of accel data */
		SAFE_UDP__LCCM312__ECU__ACCEL_REQUEST_FULL = 0x3030U,

		/** ECT to send to the host a full packet of data */
		SAFE_UDP__LCCM312__ECU__ACCEL_RETURN_FULL_DATA = 0x3031U,

		/** request a full packet of accel caldata */
		SAFE_UDP__LCCM312__ECU__ACCEL_REQUEST_CAL_DATA = 0x3032U,

		/** ECT to send host the accel cal data */
		SAFE_UDP__LCCM312__ECU__ACCEL_RETURN_CAL_DATA = 0x3033U,


		/** request a full packet of boom sensor data */
		SAFE_UDP__LCCM312__ECU__BOOMSENSOR_REQUEST_DATA = 0x3040U,

		/** ECU to send host the boom sensor data */
		SAFE_UDP__LCCM312__ECU__BOOMSENSOR_RETURN_DATA = 0x3041U,

		/** request a full packet of boom length data */
		SAFE_UDP__LCCM312__ECU__BOOMLENGTH_REQUEST_DATA = 0x3042,

		/** ECT to send host the boom length data */
		SAFE_UDP__LCCM312__ECU__BOOMLENGTH_RETURN_DATA = 0x3043U,


		/** request a full packet general (all systems) data from the ECU */
		SAFE_UDP__LCCM312__ECU__DISPLAY_REQUEST_GENERAL_DATA = 0x3050U,

		/** ECU to send host a full packet general (all systems) data*/
		SAFE_UDP__LCCM312__ECU__DISPLAY_RETURN_GENERAL_DATA = 0x3051U,

		/** request a ECU firmware versions */
		SAFE_UDP__LCCM312__ECU__REQUEST_ECU_VERSION = 0x3052U,

		/** ECU to send host its version data*/
		SAFE_UDP__LCCM312__ECU__RETURN_ECU_VERSION = 0x3053U,

		/** request a full packet of display data from the ECU */
		SAFE_UDP__LCCM312__ECU__REQUEST_DISPLAY_DATA = 0x3054U,

		/** ECU to send host a display data packet*/
		SAFE_UDP__LCCM312__ECU__RETURN_DISPLAY_DATA = 0x3055U,

		/** Length diagnostics packet from the ECU */
		//SAFE_UDP__LCCM312__ECU__REQUEST_LENGTH_DIAG_DATA = 0x3056U,

		/** Length diagnostics packet from the ECU */
		//SAFE_UDP__LCCM312__ECU__RETURN_LENGTH_DIAG_DATA = 0x3057U,


		SAFE_UDP__LCCM312__ECU__REQUEST_CAL_SETTINGS = 0x3060U,
		SAFE_UDP__LCCM312__ECU__RETURN_CAL_SETTINGS = 0x3061U,


		SAFE_UDP__LCCM312__ECU__REQUEST_GEOM_DATA = 0x3062U,
		SAFE_UDP__LCCM312__ECU__RETURN_GEOM_DATA = 0x3063U,
		SAFE_UDP__LCCM312__ECU__REQUEST_GEOM_SETTINGS = 0x3064U,
		SAFE_UDP__LCCM312__ECU__RETURN_GEOM_SETTINGS = 0x3065U,

		SAFE_UDP__LCCM312__ECU__REQUEST_PITCHROLL_DATA = 0x3066U,
		SAFE_UDP__LCCM312__ECU__RETURN_PITCHROLL_DATA = 0x3067U,

		SAFE_UDP__LCCM312__ECU__REQUEST_GYRO_DATA = 0x3068U,
		SAFE_UDP__LCCM312__ECU__RETURN_GYRO_DATA = 0x3069U,

		SAFE_UDP__LCCM312__ECU__REQUEST_INPUTS_DATA = 0x306AU,
		SAFE_UDP__LCCM312__ECU__RETURN_INPUTS_DATA = 0x306BU,

		SAFE_UDP__LCCM312__ECU__REQUEST_OUTPUTS_DATA = 0x306CU,
		SAFE_UDP__LCCM312__ECU__RETURN_OUTPUTS_DATA = 0x306DU,

		SAFE_UDP__LCCM312__ECU__REQUEST_CAN_ENUM_DATA = 0x3070U,
		SAFE_UDP__LCCM312__ECU__RETURN_CAN_ENUM_DATA = 0x3071U,
		SAFE_UDP__LCCM312__ECU__REQUEST_CAN_SLAVE_STAT_DATA = 0x3072U,
		SAFE_UDP__LCCM312__ECU__RETURN_CAN_SLAVE_STATE_DATA = 0x3073U,

		SAFE_UDP__LCCM312__ECU__REQUEST_CAN_STREAMING = 0x3080U,
		SAFE_UDP__LCCM312__ECU__RETURN_CAN_STREAMING = 0x3081U,

		SAFE_UDP__LCCM312__ECU__REQUEST_LOAD_CALC_DATA = 0x3082U,
		SAFE_UDP__LCCM312__ECU__RETURN_LOAD_CALC_DATA = 0x3083U,
		SAFE_UDP__LCCM312__ECU__REQUEST_RATING_CHART_DATA = 0x3084U,
		SAFE_UDP__LCCM312__ECU__RETURN_RATING_CHART_DATA = 0x3085U,


		SAFE_UDP__LCCM312__ECU__OUTPUTS_OPEN = 0x3090U,
		SAFE_UDP__LCCM312__ECU__OUTPUTS_CLOSE = 0x3091U,

		SAFE_UDP__LCCM312__ECU__SOLENOID_OPEN = 0x3092U,
		SAFE_UDP__LCCM312__ECU__SOLENOID_CLOSE = 0x3093U,

		SAFE_UDP__LCCM312__ECU__CAN_CLEAR_SLAVE_DATA = 0x30A0U,
		SAFE_UDP__LCCM312__ECU__CAN_SET_SERIAL_NUM = 0x30A1U,
		SAFE_UDP__LCCM312__ECU__CAN_REQUEST_DATA_VALUE = 0x30A2U,
		SAFE_UDP__LCCM312__ECU__CAN_REQUEST_PERSIST_DATA = 0x30A3U,
		SAFE_UDP__LCCM312__ECU__CAN_CANCEL_PERSIST_DATA = 0x30A4U,
		SAFE_UDP__LCCM312__ECU__CAN_SET_DATA_VALUE = 0x30A5U,
		SAFE_UDP__LCCM312__ECU__CAN_CLEAR_SESSION_DATA = 0x30A6U,
		SAFE_UDP__LCCM312__ECU__CAN_STREAM_PACKETS = 0x30A7U,


		SAFE_UDP__LCCM312__ECU__SET_MACHINE_PARAM = 0x30B0U,
		SAFE_UDP__LCCM312__ECU__UPDATE_GEOM_FILE = 0x30B1U,
		SAFE_UDP__LCCM312__ECU__RETURN_GEOM_FILE_STATUS = 0x30B2U,
		SAFE_UDP__LCCM312__ECU__UPDATE_MACHINE_CAL_FILE = 0x30B3U,
		SAFE_UDP__LCCM312__ECU__RETURN_MACHINE_CAL_FILE_STATUS = 0x30B4U,
		SAFE_UDP__LCCM312__ECU__UPDATE_MACHINE_SETTINGS_FILE = 0x30B5U,
		SAFE_UDP__LCCM312__ECU__RETURN_MACHINE_SETTINGS_FILE_STATUS = 0x30B6U,
		SAFE_UDP__LCCM312__ECU__UPDATE_ATTACH_PAK_FILE = 0x30B7U,
		SAFE_UDP__LCCM312__ECU__RETURN_ATTACH_PAK_FILE_STATUS = 0x30B8U,
		SAFE_UDP__LCCM312__ECU__UPDATE_RATING_LIST_FILE = 0x30B9U,
		SAFE_UDP__LCCM312__ECU__RETURN_RATING_LIST_FILE_STATUS = 0x30BAU,
		SAFE_UDP__LCCM312__ECU__UPDATE_SPAN_MAP_FILE = 0x30BBU,
		SAFE_UDP__LCCM312__ECU__RETURN_SPAN_MAP_FILE_STATUS = 0x30BCU,
		SAFE_UDP__LCCM312__ECU__UPDATE_ZERO_MAP_FILE = 0x30BDU,
		SAFE_UDP__LCCM312__ECU__RETURN_ZERO_MAP_FILE_STATUS = 0x30BEU,



		SAFE_UDP__LCCM312__ECU__ENABLE_TIMED_PACKET = 0x30C0U,
		SAFE_UDP__LCCM312__ECU__ENABLE_ALTERNATE_TIMED_PACKET = 0x30C1U,




		////////////////////////////////////////////////
		// LCCM423 - RM4 FIRMWARE UPDATE
		// 0x9000 - 0x9FFF
		////////////////////////////////////////////////

		/** Command to put application into bootloader mode KEY = 12345678 */
		SAFE_UDP__LCCM423__START_BOOTLOADER = 0x9000U,

		/** Command to request the bootloader version from the application */
		SAFE_UDP__LCCM423__GET_BOOT_VERSION = 0x9001U,

		/** Application returning the bootloader version */
		SAFE_UDP__LCCM423__RETURN_BOOT_VERSION = 0x9002U,

		/** Command from host to erase bootloader KEY = AABBCCDD */
		SAFE_UDP__LCCM423__ERASE_BOOTLOADER = 0x9003U,

		/** Application returning the bootloader FLASH status */
		SAFE_UDP__LCCM423__RETURN_BOOT_STATUS = 0x9004U,

		/** Command from host to send next chunk for bootloader update */
		SAFE_UDP__LCCM423__BOOT_UPDATE_CHUNK = 0x9005U,

		/** Command to request the bootloader CRC from the application */
		SAFE_UDP__LCCM423__GET_BOOT_CRC = 0x9007U,

		/** Application returning the bootloader version */
		SAFE_UDP__LCCM423__RETURN_BOOT_CRC = 0x9008U,


		/** Command to request the app version from the application */
		SAFE_UDP__LCCM423__GET_APP_VERSION = 0x9A01U,

		/** Application returning the App version */
		SAFE_UDP__LCCM423__RETURN_APP_VERSION = 0x9A02U,

		/** Command from host to erase app KEY = EEFF0011*/
		SAFE_UDP__LCCM423__ERASE_APP = 0x9A03U,

		/** Boot returning the App FLASH status */
		SAFE_UDP__LCCM423__RETURN_APP_STATUS = 0x9A04U,

		/** Command from host to send next chunk for app update */
		SAFE_UDP__LCCM423__APP_UPDATE_CHUNK = 0x9A05U,

		/** Command to request the App CRC from the host */
		SAFE_UDP__LCCM423__GET_APP_CRC = 0x9A07U,

		/** Boot returning the App version */
		SAFE_UDP__LCCM423__RETURN_APP_CRC = 0x9A08U,

		/** When in bootloader mode we can reset the CPU */
		SAFE_UDP__LCCM423__BOOT_RESET = 0x9A09U,


		////////////////////////////////////////////////
		// LCCM498 - ACPS ADC INTERFACE
		// 0xA000 - 0xA0FF
		////////////////////////////////////////////////
		/** The slave returns the channel results packets */
		SAFE_UDP__LCCM498__ADC_ETH__TX_CHANNEL_RESULTS = 0xA000,

		/** The host PC is asking our module how many channels we have in our system */
		SAFE_UDP__LCCM498__ADC_ETH__REQUEST_CHANNEL_DETAILS = 0xA001,

		/** The slave device returns this packet type with the details */
		SAFE_UDP__LCCM498__ADC_ETH__TX_CHANNEL_DETAILS = 0xA002,

		/** The host PC is requesting an immediate sample run */
		SAFE_UDP__LCCM498__ADC_ETH__REQUEST_START_SAMPLER = 0xA003,

		/** Host PC is setting ad9850 frequency */
		SAFE_UDP__LCCM498__ADC_ETH__SET_AD9850_FREQ = 0xA004,

		/** The host PC is requesting a start and wait for trigger */
		SAFE_UDP__LCCM498__ADC_ETH__REQUEST_START_TRIGGER = 0xA005,

		////////////////////////////////////////////////
		// LCCM501 - ACPS ADC INTERFACE
		// 0xB000 - 0xB0FF
		////////////////////////////////////////////////
		/** The host PC is asking our module how many channels we have in our system */
		SAFE_UDP__LCCM501__BEAM_ETH__REQUEST_CHANNEL_DETAILS = 0xB001,

		/** The slave device returns this packet type with the details */
		SAFE_UDP__LCCM501__BEAM_ETH__TX_CHANNEL_DETAILS = 0xB002,

		/** Host to set the number of pulses per transmission */
		SAFE_UDP__LCCM501__BEAM_ETH__SET__NUM_TX_PULSES = 0xB003,

		/** Host to set the bit barker code format for the array */
		SAFE_UDP__LCCM501__BEAM_ETH__SET__BARKER_CODE = 0xB004,

		/** Host to set the element delay for each transmitter */
		SAFE_UDP__LCCM501__BEAM_ETH__SET__ELEMENT_DELAY = 0xB005,

		/** Host to start a single transmit */
		SAFE_UDP__LCCM501__BEAM_ETH__START_SINGLE_TX = 0xB006,

		/** Start a transmit but supply details such as pulses, delays and channel */
		SAFE_UDP__LCCM501__BEAM_ETH__START_SINGLE_COMPLEX_TX = 0xB007,

		/** Set a 2D steering angle and media speed */
		SAFE_UDP__LCCM501__BEAM_ETH__SET__2D_STEERING = 0xB008,

		////////////////////////////////////////////////
		// LCCM528 - SAFEUDP VISION
		// 0xC000 - 0xC0FF
		////////////////////////////////////////////////
		/** Image Transmission, set image params on host to receive a new image */
		SAFE_UDP__LCCM528__SAFEUDP_IMGTX__SET_IMAGE_PARAMS = 0xC000,

		/** Actual image data from slave to host */
		SAFE_UDP__LCCM528__SAFEUDP_IMGTX__IMAGE_DATA = 0xC001,

		SAFE_UDP__LCCM528__SAFEUDP_VISION__IMAGE_DATA = 0xC002





	}SAFE_UDP__PACKET_T;



#endif /* _SAFE_UDP__PACKET_TYPES_H_ */
