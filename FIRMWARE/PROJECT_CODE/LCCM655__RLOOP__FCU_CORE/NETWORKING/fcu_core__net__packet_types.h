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

		/** Flight control data streaming */
		NET_PKT__FCU_GEN__STREAMING_CONTROL = 0x0100U,

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


		//////////////////////////////////////////////////////
		//FCU: LASER OPTONCDT (0x1100)
		//////////////////////////////////////////////////////

		/** Request from the host to send the laser data */
		NET_PKT__LASER_OPTO__REQUEST_LASER_DATA = 0x1100U,

		/** FCU to Host, return laser data */
		NET_PKT__LASER_OPTO__TX_LASER_DATA = 0x1101U,



		//////////////////////////////////////////////////////
		//FCU: LASER DISTANCE (0x1200)
		//////////////////////////////////////////////////////

		/** Request from the host to send the laser data */
		NET_PKT__LASER_DIST__REQUEST_LASER_DATA = 0x1200U,

		/** FCU to Host, return laser data */
		NET_PKT__LASER_DIST__TX_LASER_DATA = 0x1201U,



		//////////////////////////////////////////////////////
		//FCU: LASER CONTRAST (0x1300)
		//////////////////////////////////////////////////////

		/** Request from the host to send the laser data */
		NET_PKT__LASER_CONT__REQUEST_LASER_DATA = 0x1300U,

		/** FCU to Host, return laser data */
		NET_PKT__LASER_CONT__TX_LASER_DATA = 0x1301U,



		//////////////////////////////////////////////////////
		//POWER: GENERAL (0x3000)
		//////////////////////////////////////////////////////

		/** Pod safe command */
		NET_PKT__PWR_GEN__POD_SAFE_COMMAND = 0x3000U,

		/** Allow us to emulate pod sensor data */
		NET_PKT__PWR_GEN__POD_EMULATION_CONTROL = 0x3001U,

		/** Power Node data streaming */
		NET_PKT__PWR_GEN__STREAMING_CONTROL = 0x3010U,

		//////////////////////////////////////////////////////
		//XILINX HYPERLOOP SIMULATION (0x5000)
		//////////////////////////////////////////////////////

		/** simulation control on the ML507 board */
		NET_PKT__XILINX_SIM__SIMULATION_CONTROL = 0x5000U


	}E_NET__PACKET_T;




#endif /* __NET__PACKET_TYPES_H_ */
