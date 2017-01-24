#ifndef LOCALDEF_H_
#define LOCALDEF_H_

/*lint -e950*/

	//The control card
	#include <../../../BOARD_SUPPORT/lpcb234r0__board_support.h>

/*******************************************************************************
ETHERNET TRANSPORT
*******************************************************************************/
	#define C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

		//CPU Support
#ifndef WIN32
		#define C_LOCALDEF__LCCM325__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM325__USE_ON_XILINX							(0U)
		#define C_LOCALDEF__LCCM325__USE_ON_WIN32							(0U)
		#define C_LOCALDEF__LCCM325__USE_ON_MSP430							(0U)
#else
		#define C_LOCALDEF__LCCM325__USE_ON_RM4								(0U)
		#define C_LOCALDEF__LCCM325__USE_ON_XILINX							(0U)
		#define C_LOCALDEF__LCCM325__USE_ON_WIN32							(1U)
		#define C_LOCALDEF__LCCM325__USE_ON_MSP430							(0U)
#endif


		//various protocol options
		//DHCP Client
		#define C_LOCALDEF__LCCM325__ENABLE_DHCP_CLIENT						(0U)
		//Link Layer Discovery Protocol
		#define C_LOCALDEF__LCCM325__ENABLE_LLDP							(0U)
		#define C_LOCALDEF__LCCM325__ENABLE_SNMP							(0U)

		//UDP Rx
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,dest_port)	vPWRNODE_NET_RX__RxUDP(buffer, length, dest_port)
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

		/* Architecture Options*/
		#define C_LOCALDEF__LCCM528__USE_ON_XILINX							(0U)
		#define C_LOCALDEF__LCCM528__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM528__USE_ON_WIN32							(0U)

		/** User Rx Callback
		* Payload, Length, Type, DestPort, Faults
		*/
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vPWRNODE_NET_RX__RxSafeUDP(p,l,t,d,f)

		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(9110U)
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER2					(9111U)

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
RLOOP - PI COMMUNICATIONS MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE							(0U)
	#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

		//arch
		#define C_LOCALDEF__LCCM656__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM656__USE_ON_WIN32							(0U)

		/** enable the receiver side? */
		#define C_LOCALDEF__LCCM656__ENABLE_RX								(1U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM656__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM656__RLOOP__PI_COMMS/pi_comms.h>
	#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
ATA6870N - BATTERY MANAGEMENT DEVICE
*******************************************************************************/
	#define C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

		//architecture
		#define C_LOCALDEF__LCCM650__USE_ON_RM4								(1U)

		/** number of devices in series */
		#define C_LOCALDEF__LCCM650__NUM_DEVICES							(3U)

		/** Use checksum support on the ATA comms or not? */
		#define C_LOCALDEF__LCCM650__ENABLE_CRC								(0U)

		/** Average window, set to 0 for averaging off */
		#define C_LOCALDEF__LCCM650__AVERAGE_WINDOW							(16U)

		//setup for functions
		#define M_LOCALDEF__LCCM650__NCS_TRIS(dir)							{if(dir == 0U) vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 4U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 4U, GIO_DIRECTION__INPUT);}
		#define M_LOCALDEF__LCCM650__NCS_LATCH(val)							{vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 4U, val);}
		#define M_LOCALDEF__LCCM650__SPI_TX_U8(x)							u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__1, MIBSPI135_DATA_FORMAT__0, MIBSPI135_CS__NONE, x)

		#define M_LOCALDEF__LCCM650__POWER_ENABLE_TRIS(x)					{if(x == 0U) vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 2U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 2U, GIO_DIRECTION__INPUT); }
		#define M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(x)					{vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 2U, x); }

		#define M_LOCALDEF__LCCM650__POWER_AVAIL_TRIS(x)					{if(x == 0U) vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 5U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 5U, GIO_DIRECTION__INPUT); }
		#define M_LOCALDEF__LCCM650__POWER_AVAIL_PORT()						u32RM4_GIO__Get_Bit(RM4_GIO__PORT_B, 5U)

		
		/** Testing Options */
		#define C_LOCALDEF__LCCM650__ENABLE_TEST_SPEC						(0U)


		/** Main include file */
		#include <MULTICORE/LCCM650__MULTICORE__ATA6870/ata6870.h>
	#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
MS5607 - PRESSURE SENSOR
*******************************************************************************/
	#define C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U

		/** MS5607 Device Address */
		#define C_LOCALDEF__LCCM648__BUS_ADDX								(0x76U)

		/** The number of main program loops to wait for conversion */
		#define C_LOCALDEF__LCCM648__NUM_CONVERSION_LOOPS					(10000U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM648__ENABLE_TEST_SPEC						(0U)

		/** Enable datasheet values to test math
		 * DO NOT put this in production */
		#define C_LOCALDEF__LCCM648__ENABLE_DS_VALUES						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM648__MULTICORE__MS5607/ms5607.h>

	#endif //#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
DS2482S - I2C TO 1-WIRE CONVERTER
*******************************************************************************/
	#define C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

		//CPU Architecture
		#define C_LOCALDEF__LCCM641__USE_ON_RM4								(1U)

		/** Max number of DS2482 devices on the same I2C Bus */
		#define C_LOCALDEF__LCCM641__NUM_DEVICS								(2U)

		/** Use table based LUT CRC or slow computed CRC */
		#define C_LOCALDEF__LCCM641__USE_TABLE_CRC							(1U)

		/** When waiting in loops, we need a program loop timeout value */
		#define C_LOCALDEF__LCCM641__MAX_TIMEOUT_LOOPS						(100000U)

		// I2C MACROS
		#define M_LOCALDEF__LCCM641__I2C_RX_REG(device, reg)				s16RM4_I2C_USER__RxReg(device, reg)
		#define M_LOCALDEF__LCCM641__I2C_TX_REG(device, reg)				s16RM4_I2C_USER__TxReg(device, reg)
		#define M_LOCALDEF__LCCM641__I2C_TX_BYTE(device, reg, value)		s16RM4_I2C_USER__TxByte(device, reg, value)
		#define M_LOCALDEF__LCCM641__I2C_RX_BYTE(device, reg, value)		s16RM4_I2C_USER__RxByte(device, reg, value)


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
		#define C_LOCALDEF__LCCM644__MAX_DEVICES							(600U)

		/** Define the number of I2C channels available in the system
		 * If using the DS2482 we can support 4 devices on the one I2C bus
		 * Which means we can support hundreds of devices per channel
		 */
		#define C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS						(2U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM644__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM644__MULTICORE__DS18B20/ds18b20.h>
	#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
TSYS01 - DIGITAL TEMP SENSOR
*******************************************************************************/
	#define C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

		/** The number of main program loops to wait for conversion */
		#define C_LOCALDEF__LCCM647__NUM_CONVERSION_LOOPS					(10000U)

		/** the I2C address on the bus */
		#define C_LOCALDEF__LCCM647__BUS_ADDX								(0x77U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM647__ENABLE_TEST_SPEC						(0U)


		/** Enable datasheet values to test math
		 * DO NOT put this in production */
		#define C_LOCALDEF__LCCM647__ENABLE_DS_VALUES						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>

	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RLOOP - POWER NODE CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

		/** Enable or disable the PiComms layer */
		#define C_LOCALDEF__LCCM653__ENABLE_PI_COMMS						(0U)

		/** Enable the battery temperature measurement system */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP						(1U)

		/** Enable or disable battery temp search */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP_SEARCH				(0U)

		/** Enable the BMS Subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_BMS								(1U)

		/** Enable the PV temp system using TSYS01 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP						(1U)

		/** Node pressure using MS5607 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS						(1U)

		/** Enable the DC/DC converter subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER					(1U)
		//when the DC/DC is enabled we can implement a timeout timer from
		//heartbeat (or any GS comms)
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER__HEART_TIMEOUT		(0U)

		//define the max amount of 100ms increments before the WDT turns off
		#define C_LOCALDEF__LCCM653__DC_CONVERTER__HEART_TIMER_MAX			(30U)

		/** Enable the charger subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_CHARGER							(1U)

		/** Enable Ethernet */
		#define C_LOCALDEF__LCCM653__ENABLE_ETHERNET						(1U)

		/** Enable Pressure Vesel Repress System */
		#define C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS						(1U)

		/** Enable HE and Brakes Cooling System */
		#define C_LOCALDEF__LCCM653__ENABLE_COOLING							(1U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM653__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM653__RLOOP__POWER_CORE/power_core.h>

	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

#endif /* LOCALDEF_H_ */
