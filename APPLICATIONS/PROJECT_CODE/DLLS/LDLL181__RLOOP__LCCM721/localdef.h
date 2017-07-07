#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

	#include "sil3_generic__cpu.h"

	//our basic defines
	#include <WIN32/BASIC_TYPES/basic_types.h>
	#include <WIN32/DEBUG_PRINTF/debug_printf.h>

	//some placeholders
	#define SAFETOOL_BRANCH(stFuncID)

	#ifndef WIN32
		#include <../../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
		#include <../../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
	#else
		#include <../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
		#include <../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
	#endif

/*******************************************************************************
ETHERNET TRANSPORT
*******************************************************************************/
	#define C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

		//various protocol options
		//DHCP Client
		#define C_LOCALDEF__LCCM325__ENABLE_DHCP_CLIENT						(0U)
		//Link Layer Discovery Protocol
		#define C_LOCALDEF__LCCM325__ENABLE_LLDP							(0U)
		#define C_LOCALDEF__LCCM325__ENABLE_SNMP							(0U)

		//UDP Rx
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,dest_port)	vHETHERM_ETH__RxUDP(buffer, length, dest_port)
		/*vECU_ETHERNET_RX__UDPPacket*/

		//testing options
		#define C_LOCALDEF__LCCM325__ENABLE_TEST_SPEC						(0U)

		//protocol specific options
		//set to 1 to consider port numbers
		#define C_LOCALDEF__LCCM325__PROTO_UDP__ENABLE_PORT_NUMBERS			(1U)

		//main include file
		#include <MULTICORE/LCCM325__MULTICORE__802_3/eth.h>

	#endif //C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE

/*******************************************************************************
SAFETY UDP LAYER
*******************************************************************************/
	#define C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

		/** User Rx Callback
		* Payload, Length, Type, DestPort, Faults
		*/
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vHETHERM_ETH__RxSafeUDP(p,l,t,d,f)

		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(C_RLOOP_NET_PORT__HETHERM)
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER2					(0U)

		/** Vision over SafeUDP Options */
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_TX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_RX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__MAX_BUFFER_SIZE				(640UL * 480UL * 2UL)


		/** Testing Options */
		#define C_LOCALDEF__LCCM528__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp.h>
	#endif //#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
DS2482S - I2C TO 1-WIRE CONVERTER
*******************************************************************************/
	#define C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

		//CPU Architecture
		#define C_LOCALDEF__LCCM641__USE_ON_RM4								(1U)

		/** Max number of DS2482 devices on the same I2C Bus */
		#define C_LOCALDEF__LCCM641__NUM_DEVICS								(1U)

		/** Use table based LUT CRC or slow computed CRC */
		#define C_LOCALDEF__LCCM641__USE_TABLE_CRC							(1U)

		/** When waiting in loops, we need a program loop timeout value */
		#define C_LOCALDEF__LCCM641__MAX_TIMEOUT_LOOPS						(100000U)

		// I2C MACROS
		#define M_LOCALDEF__LCCM641__I2C_RX_REG(device, reg)				s16RM4_I2C_USER__RxReg(device, reg)
		#define M_LOCALDEF__LCCM641__I2C_TX_REG(device, reg)				s16RM4_I2C_USER__TxReg(device, reg)
		#define M_LOCALDEF__LCCM641__I2C_TX_BYTE(device, reg, value)		s16RM4_I2C_USER__Tx_U8(device, reg, value)
		#define M_LOCALDEF__LCCM641__I2C_RX_BYTE(device, reg, value)		s16RM4_I2C_USER__Rx_U8(device, reg, value)


		/** Testing Options */
		#define C_LOCALDEF__LCCM641__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM641__MULTICORE__DS2482S/ds2482s.h>

	#endif //#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
DS18B20 - 1-Wire Temperature Sensor
*******************************************************************************/
	#define C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

		//processor options
		#define C_LOCALDEF__LCCM644__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM644__USE_ON_XILINX							(0U)
		#define C_LOCALDEF__LCCM644__USE_ON_MSP430							(0U)

		/** Specific the required resoltuion 9, 10, 11 or 12 bit
		 * Each resolution takes longer to convert
		 */
		#define C_LOCALDEF__LCCM644__RESOLUTION_SETTING						(9U)

		/** If we have access to a 10ms ISR then we don't need to wait
		 * for the conversion to finish. If we don't have an ISR then
		 * set this to 0
		 */
		#define C_LOCALDEF__LCCM644__USE_10MS_ISR							(1U)

		//connectivity options
		//1-Wire software library
		#define C_LOCALDEF__LCCM644__CONNECT_LCCM236						(0U)
		//DS2482S I2C Device
		#define C_LOCALDEF__LCCM644__CONNECT_LCCM641						(1U)

		//max supported devices
		#define C_LOCALDEF__LCCM644__MAX_DEVICES							(32U)

		/** Define the number of I2C channels available in the system
		 * If using the DS2482 we can support 4 devices on the one I2C bus
		 * Which means we can support hundreds of devices per channel
		 */
		#define C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS						(1U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM644__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM644__MULTICORE__DS18B20/ds18b20.h>
	#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
rLOOP - HOVER ENGINE THERMAL MANAGEMENT
*******************************************************************************/
	#define C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

		//special needs for DAQ compile time
		#include <LCCM721__RLOOP__HE_THERM/DAQ/he_therm__daq_settings.h>

		/** Enable the DAQ module for development */
		#define C_LOCALDEF__LCCM721__ENABLE_DAQ								(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM721__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM721__RLOOP__HE_THERM/he_therm.h>

	#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

#endif //LOCALDEF
