/*
 * fcu_core__net__packet_types.h
 *
 *  Created on: Dec 9, 2016
 *      Author: Lachlan
 */

#ifndef __NET__PACKET_TYPES_H_
#define __NET__PACKET_TYPES_H_





	/** rLoop UDP network packet types
	* http://confluence.rloop.org/display/SD/Packet+Types
	*/
	typedef enum
	{

		/** null packet type */
		NET_PKT__NONE = 0x000U,

		//////////////////////////////////////////////////////
		//FCU: GENERAL (0x0000)
		//////////////////////////////////////////////////////

		/** Pod stop command */
		NET_PKT__FCU_GEN__POD_STOP_COMMAND = 0x0001U,

		/** Allow us to emulate pod sensor data */
		NET_PKT__FCU_GEN__POD_EMULATION_CONTROL = 0x0002U,

		/** Request from the host to enter the Pre Run phase from the Post Run phase */
		NET_PKT__FCU_GEN__ENTER_PRE_RUN_PHASE_COMMAND = 0x0003U,

		/** Switch on or off DAQ streaming */
		NET_PKT__FCU_GEN__DAQ_ENABLE = 0x00FEU,

		/** Force a flush of the DAQ system */
		NET_PKT__FCU_GEN__DAQ_FLUSH = 0x00FFU,

		/** Flight control data streaming */
		NET_PKT__FCU_GEN__STREAMING_CONTROL = 0x0100U,

		/** Transmit the mission data */
		NET_PKT__FCU_GEN__TX_MISSION_DATA = 0x0200U,

		/** All system fault flags */
		NET_PKT__FCU_GEN__TX_ALL_FAULT_FLAGS = 0x0300U,

		/** GS Hearbeat */
		NET_PKT__FCU_GEN__GS_HEARTBEAT = 0x0400U,
		
		/** Node Reset */
		NET_PKT__FCU_GEN__GS_NODE_RESET = 0x0401U,

		/** Pod State Machine Command */
		NET_PKT__FCU_GEN__POD_COMMAND = 0x0500U,

		/** Pod State Machine Force State (FOR DEBUGGING ONLY) */
		NET_PKT__FCU_GEN__MAINSM_DEBUG_FORCE_STATE = 0x0590U,


		//////////////////////////////////////////////////////
		//FCU: ACCEL (0x1000)
		//////////////////////////////////////////////////////

		/** Request from the host to send the Acclelerometer calibration data */
		NET_PKT__FCU_ACCEL__REQUEST_CAL_DATA = 0x1000U,

		/** Transmit the accel calibration data to the host */
		NET_PKT__FCU_ACCEL__TX_CAL_DATA = 0x1001U,

		/** request a full data stream from our devices */
		NET_PKT__FCU_ACCEL__REQUEST_FULL_DATA = 0x1002U,

		/** Transmit the full available accel data to the host */
		NET_PKT__FCU_ACCEL__TX_FULL_DATA = 0x1003U,

		/** enter auto calibration mode */
		NET_PKT__FCU_ACCEL__AUTO_CALIBRATE = 0x1004U,

		/** Fine adjustment on Any */
		NET_PKT__FCU_ACCEL__FINE_ZERO_ADJUSTMENT = 0x1005U,

		/** Enable ethernet injection */
		NET_PKT__FCU_ACCEL__ENAB_ETH_INJECTION = 0x1006U,

		/** Eth Injection Data */
		NET_PKT__FCU_ACCEL__INJECTION_DATA = 0x1007U,


		//////////////////////////////////////////////////////
		//FCU: LASER OPTONCDT (0x1100)
		//////////////////////////////////////////////////////

		/** Request from the host to send the laser data */
		NET_PKT__LASER_OPTO__REQUEST_LASER_DATA = 0x1100U,

		/** FCU to Host, return laser data */
		NET_PKT__LASER_OPTO__TX_LASER_DATA = 0x1101U,

		/** Set the laser height */
		NET_PKT__LASER_OPTO__CAL_LASER_HEIGHT = 0x1102U,

		/** Enable ethernet injection */
		NET_PKT__LASER_OPTO__ENABLE_ETH_INJ = 0x1103U,

		/** Enable ethernet injection */
		NET_PKT__LASER_OPTO__ETH_INJ_PACKET = 0x1104U,


		//////////////////////////////////////////////////////
		//FCU: LASER DISTANCE (0x1200)
		//////////////////////////////////////////////////////

		/** Request from the host to send the laser data */
		NET_PKT__LASER_DIST__REQUEST_LASER_DATA = 0x1200U,

		/** FCU to Host, return laser data */
		NET_PKT__LASER_DIST__TX_LASER_DATA = 0x1201U,

		/** Enable emu mode, with key 0x01010202U for block 0, and 1 for block 1 */
		NET_PKT__LASER_DIST__ENABLE_EMULATION_MODE = 0x1202U,

		/** Inject a raw emulation value into the laser */
		NET_PKT__LASER_DIST__RAW_EMULATION_VALUE = 0x1203U,



		//////////////////////////////////////////////////////
		//FCU: LASER CONTRAST (0x1300)
		//////////////////////////////////////////////////////

		/** Request from the host to send the laser data */
		NET_PKT__LASER_CONT__REQUEST_LASER_DATA = 0x1300U,

		/** FCU to Host, return laser data */
		NET_PKT__LASER_CONT__TX_LASER_DATA_0 = 0x1301U,
		NET_PKT__LASER_CONT__TX_LASER_DATA_1 = 0x1302U,
		NET_PKT__LASER_CONT__TX_LASER_DATA_2 = 0x1303U,


		//////////////////////////////////////////////////////
		//FCU: BRAKES (0x1400)
		//////////////////////////////////////////////////////

		/** Permit brake development mode */
		NET_PKT__FCU_BRAKES__ENABLE_DEV_MODE = 0x1400U,

		/** Perform a raw motor move */
		NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW = 0x1401U,

		/** Send out the brake Tx data */
		NET_PKT__FCU_BRAKES__TX_DATA = 0x1402U,

		/** Move the brakes relative to the I-Beam */
		NET_PKT__FCU_BRAKES__MOVE_IBEAM = 0x1403U,

		/** Allow us to update the motor parameters */
		NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM = 0x1404U,

		/** Host wants a motor param packet */
		NET_PKT__FCU_BRAKES__REQ_MOTOR_PARAM = 0x1405U,

		/** Transmit motor param packet to host */
		NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM = 0x1406U,

		/** Start the brakes cal mode, only works when in Dev mode */
		NET_PKT__FCU_BRAKES__START_CAL_MODE = 0x1407U,

		/** Init the brake sub system once its out of reset */
		NET_PKT__FCU_BRAKES__INIT = 0x1408U,

		/** perform a zero/span on the MLP */
		NET_PKT__FCU_BRAKES__MLP_ZEROSPAN = 0x1409U,

		/** Set either the veloc or accel */
		NET_PKT__FCU_BRAKES__VELOC_ACCEL_SET = 0x140AU,

		//////////////////////////////////////////////////////
		//FCU: THROTTLES (0x1500)
		//////////////////////////////////////////////////////

		/** Switch on Throttles dev mode */
		NET_PKT__FCU_THROTTLE__ENABLE_DEV_MODE = 0x1500U,

		/** Set the raw throttle value */
		NET_PKT__FCU_THROTTLE__SET_RAW_THROTTLE = 0x1501U,

		/** Request from the host to send the Throttle data */
		NET_PKT__FCU_THROTTLE__REQUEST_DATA = 0x1502U,

		/** FCU to Host, return Throttle data */
		NET_PKT__FCU_THROTTLE__TX_DATA = 0x1503U,

		//////////////////////////////////////////////////////
		//FCU: FLIGHT (0x1600)
		//////////////////////////////////////////////////////

		/** Stream Navigation Progress Data */
		NET_PKT__FCU_NAV__TX_NAV_PROGRESS = 0x1600U,

		/** Host to send the FCU a track database packet */
		NET_PKT__FCU_FLT__TX_TRACK_DB_CHUNK = 0x1601U,

		/** FCU to ACK track DB chunk upload */
		NET_PKT__FCU_FLT__ACK_TRACK_DB_CHUNK = 0x1602U,

		/** Select track database */
		NET_PKT__FCU_FLT__SELECT_TRACK_DB = 0x1603U,

		/** Request the geometry data */
		NET_PKT__FCU_FLT__REQUEST_GEOM_DATA = 0x1604U,

		/** FCU to host to tx geom data */
		NET_PKT__FCU_FLT__TX_GEOM_DATA = 0x1605U,

		/** Host to set a GEOM parameter */
		NET_PKT__FCU_FLT__SET_GEOM_DATA = 0x1606U,


		//////////////////////////////////////////////////////
		//FCU: ASI LAYER (0x1700)
		//////////////////////////////////////////////////////

		/** Request from the host to send the ASI data */
		NET_PKT__FCU_ASI__REQUEST_ASI_DATA = 0x1700U,

		/** FCU to Host, return ASI data */
		NET_PKT__FCU_ASI__TX_ASI_DATA = 0x1701U,

		/** FCU to Host, return ASI data */
		NET_PKT__FCU_ASI__SET_THROTTLE = 0x1702U,

		/** Inhibit the RS485 interface */
		NET_PKT__FCU_ASI__SET_INHIBIT_RS485 = 0x1703U,

		/** Use faster scanning times */
		NET_PKT__FCU_ASI__FAST_RS485 = 0x1704U,


		//////////////////////////////////////////////////////
		//FCU: PUSHER (0x1800)
		//////////////////////////////////////////////////////

		/** Request from the host to send the pusher data */
		NET_PKT__FCU_PUSH__REQUEST_PUSHER_DATA = 0x1800U,

		/** FCU to Host, return pusher data */
		NET_PKT__FCU_PUSH__TX_PUSHER_DATA = 0x1801U,

		//////////////////////////////////////////////////////
		//FCU: LANDING GEAR UNIT (0x1900)
		//////////////////////////////////////////////////////

		/** Set Direction */
		NET_PKT__FCU_LIFTMECH__SET_DIR = 0x1900U,

		/** Set speed */
		NET_PKT__FCU_LIFTMECH__SET_SPEED = 0x1901U,

		/** Set Group Dir */
		NET_PKT__FCU_LIFTMECH__SET_GROUP_DIR = 0x1902U,

		/** Set Group Speed */
		NET_PKT__FCU_LIFTMECH__SET_GROUP_SPEED = 0x1903U,

		/** Release the Lift Mech */
		NET_PKT__FCU_LIFTMECH__RELEASE = 0x1904U,
		
		
		
		//////////////////////////////////////////////////////
		//APU: CLUTCH CONTROL(0x2100 - 0x21FF)
		//////////////////////////////////////////////////////
		NET_PKT__APU_CLUTCH__MANUAL = 0x2100U,

		/** Manual Motor Directoin Control */
		NET_PKT__APU_MOTOR__DIRECTION_MANUAL = 0x2101U,

		/** Manual speed control for the APU */
		NET_PKT__APU_MOTOR__SPEED_MANUAL = 0x2102U,


		/** Status packet sent to host about APU status */
		NET_PKT__APU__STATUS_PACKET = 0x2103U,

		/** Manual enable control */
		NET_PKT__APU_MOTOR__ENABLE_MANUAL = 0x2104U,



		//////////////////////////////////////////////////////
		//POWER: GENERAL (0x3000)
		//////////////////////////////////////////////////////

		/** Pod safe command */
		NET_PKT__PWR_GEN__POD_SAFE_COMMAND = 0x3000U,

		/** Allow us to emulate pod sensor data */
		NET_PKT__PWR_GEN__POD_EMULATION_CONTROL = 0x3001U,

		/** Power Node data streaming */
		NET_PKT__PWR_GEN__STREAMING_CONTROL = 0x3010U,

		/** Charger Control */
		NET_PKT__PWR_GEN__CHARGER_CONTROL = 0x3020U,

		/** Manually Balance */
		NET_PKT__PWR_GEN__MANUAL_BALANCE_CONTROL = 0x3021U,

		/** Latch */
		NET_PKT__PWR_GEN__LATCH = 0x3030U,

		/** Power node personality */
		NET_PKT__PWR_GEN__POWER_PERSONALITY = 0x3031U,

		/** Power node repress system */
		NET_PKT__PWR_GEN__PV_REPRESS = 0x3040U,

		/** Power node cooling system */
		NET_PKT__PWR_GEN__COOLING = 0x3041U,

		/** Heartbeat Command **/
		NET_PKT__PWR_GEN__HEARTBEAT = 0x3FFFU,

		//////////////////////////////////////////////////////
		//POWER: TEMPERATURE SYSTEM (0x3200)
		//////////////////////////////////////////////////////

		/** Request a temperature packet */
		NET_PKT__PWR_TEMP__REQ_CURRENT_TEMPS = 0x3200U,

		/** Send an entire temperature sensor packet */
		NET_PKT__PWR_TEMP__TX_CURRENT_TEMPS = 0x3201U,

		/** Host wants sensor loc data */
		NET_PKT__PWR_TEMP__REQ_SENSOR_LOCATION = 0x3202U,

		/** Send the location data */
		NET_PKT__PWR_TEMP__TX_SENSOR_LOCATION_DATA = 0x3203U,

		/** Request a ROMID based on an index */
		NET_PKT__PWR_TEMP__REQ_ROMID_INDEX = 0x3204U,

		/** Send the ROMID based on an index */
		NET_PKT__PWR_TEMP__TX_ROMID_INDEX = 0x3205U,

		/** Set the ROMID by sensor index */
		NET_PKT__PWR_TEMP__SET_ROMID_INDEX = 0x3206U,

		/** Set the User Data by Sensor Index*/
		NET_PKT__PWR_TEMP__SET_USERDATA_INDEX = 0x3207U,


		//////////////////////////////////////////////////////
		//POWER: BMS SYSTEM (0x3400)
		//////////////////////////////////////////////////////
		/** Request a BMS packet */
		NET_PKT__PWR_BMS__REQ_BMS = 0x3400U,

		/** Send BMS status */
		NET_PKT__PWR_BMS__TX_BMS_STATUS = 0x3401U,

		/** Setup the charger values */
		NET_PKT__PWR_BMS__SET_CHG_VALUES = 0x3402U,

		//////////////////////////////////////////////////////
		//POWER: COOLING SYSTEM (0x3600)
		//////////////////////////////////////////////////////
		/** Request a Cooling System packet */
		NET_PKT__PWR_COOLING__REQ_COOLING = 0x3600U,

		/** Send COOLING status */
		NET_PKT__PWR_COOLING__TX_COOLING_STATUS = 0x3601U,

		/** Test Cooling System Solennoid #1 */
		NET_PKT__PWR_COOLING__RX_TEST_COOLING_01 = 0x3602U,

		/** Test Cooling System Solennoid #2 */
		NET_PKT__PWR_COOLING__RX_TEST_COOLING_02 = 0x3603U,

		/** Test Cooling System Solennoid #3 */
		NET_PKT__PWR_COOLING__RX_TEST_COOLING_03 = 0x3604U,

		/** Test Cooling System Solennoid #4 */
		NET_PKT__PWR_COOLING__RX_TEST_COOLING_04 = 0x3605U,

		/** Test Cooling System Solennoid #5 */
		NET_PKT__PWR_COOLING__RX_TEST_COOLING_05 = 0x3606U,

		//////////////////////////////////////////////////////
		//POWER: CURRENT SENSOR (0x3800)
		//////////////////////////////////////////////////////
		/** Request a Current Reading packet */
		NET_PKT__PWR_CURRENT__REQ_CURRENT = 0x3800U,

		/** Send Current Reading */
		NET_PKT__PWR_CURRENT__TX_CURRENT_STATUS = 0x3801U,

		//////////////////////////////////////////////////////
		//DAQ (0x4000)
		//////////////////////////////////////////////////////

		/** Flight control DAQ offset */
		NET_PKT__FCU_DAQ__OFFSET_INDEX = 0x4000U,
		NET_PKT__POWERA_DAQ__OFFSET_INDEX = 0x4100U,
		NET_PKT__POWERB_DAQ__OFFSET_INDEX = 0x4200U,
		NET_PKT__LGU_DAQ__OFFSET_INDEX = 0x4300U,
		NET_PKT__HE_THERM_DAQ__OFFSET_INDEX = 0x4400U,


		//////////////////////////////////////////////////////
		//XILINX HYPERLOOP SIMULATION (0x5000)
		//////////////////////////////////////////////////////

		/** simulation control on the ML507 board */
		NET_PKT__XILINX_SIM__SIMULATION_CONTROL = 0x5000U,

		/** Allow us to manually change the state of the laser pin.
		 * Only works if the run is stopped */
		NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL = 0x5001U,

		/** Transmit a progress update to the host */
		NET_PKT__XILINX_SIM__TX_PROGRESS_UPDATE = 0x5002U,


		//////////////////////////////////////////////////////
		//HE THERMAL UNIT - 0x6000 - 0x6FFF
		//////////////////////////////////////////////////////

		NET_PKT__HET__REQUEST_THERM_PACKET = 0x6000U,

		/** Return a full thermal data packet */
		NET_PKT__HET__SEND_THERM_PACKET = 0x6001U,

		/** Manual control of the solenoids */
		NET_PKT__HET__MANUAL_CONTROL = 0x6002U,


		//////////////////////////////////////////////////////
		//LANDING GEAR UNIT - 0x7000 - 0x7FFF
		//////////////////////////////////////////////////////

		/** Permit network based streaming control */
		NET_PKT__LGU__STREAMING_CONTROL = 0x7000U,

		/** Manual control over the actuator */
		NET_PKT__LGU__MANUAL_MODE = 0x7001U,

		/** Transmit the LGU status packet over the network */
		NET_PKT__LGU__TX_STATUS_PACKET = 0x7002U,

		/** Transmit the LGU ADC Calibration Data */
		NET_PKT__LGU__TX_ADC_CAL_PACKET = 0x7003U,


        //////////////////////////////////////////////////////
        //IPS CHARGER DATA
        //////////////////////////////////////////////////////
		NET_PKT__IPS__STATUS = 0x9125U,

	}E_NET__PACKET_T;




#endif /* __NET__PACKET_TYPES_H_ */
