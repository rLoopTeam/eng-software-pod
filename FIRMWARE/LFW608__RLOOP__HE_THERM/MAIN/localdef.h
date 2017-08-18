#ifndef LOCALDEF_H_
#define LOCALDEF_H_

/*lint -e950*/

	//The launchpad
#ifndef WIN32
	#include <../../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
	#include <../../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#else
	#include <../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
	#include <../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#endif

/*******************************************************************************
RM4 GIO MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS						(0U)

		#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U

			#define GIOA_PIN_0_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_1_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_2_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_3_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_4_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_5_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_6_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_7_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_0_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_1_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_2_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_3_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_4_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_5_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_6_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_7_ISR()										vRM4_GIO_ISR__DefaultRoutine()

		#endif //#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U

		//Testing options
		#define C_LOCALDEF__LCCM133__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM133__RM4__GIO/rm4_gio.h>

	#endif //#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1

/*******************************************************************************
RM4 - RTI MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

		//globally switch on the WDT
		#define C_LOCALDEF__LCCM124__ENABLE_WDT								(0U)

		/** RTI CLOCK FREQUENCY
		 * Based on our standard system, valid values are div(2,4,8):
		 * 100 	(100MHZ)
		 * 75 	(75MHZ - ONLY ON RM57)
		 * 50	(50MHZ)
		 * 25	(25MHZ)
		 * */
		#define C_LOCALDEF__LCCM124__RTI_CLK_FREQ							(75U)

		/** RTCLK0 feeds counter 0 and is used for general purpose compare times */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER0_PRESCALER					(10U)

		/** RTCLK1 feeds counter 1 and can be used for 64bit timing */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER1_PRESCALER					(1U)


		//Sets up the time periods for each compare. Must be defined in microSeconds.
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_PERIOD_US 				(10000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_PERIOD_US 				(100000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_PERIOD_US 				(1000000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_PERIOD_US 				(1000000U)

		//these are the interrupt handlers which should point
		//to a function, otherwise leave as default
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_CALLBACK					vHETHERM_TIMERS__10MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_CALLBACK					vHETHERM_TIMERS__100MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()

		//Testing options
		#define C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC	 					(0U)

		#include <RM4/LCCM124__RM4__RTI/rm4_rti.h>

	#endif //#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
SIL3 - ETHERNET TRANSPORT
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
SIL3 - SAFETY UDP LAYER
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
RM4 - I2C DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE == 1U

		//The bus freq (100K, 400K, 1MHZ)
		#define C_LOCALDEF__LCCM215__BUS_FREQUENCY_HZ   					(100000U)

		#define C_LOCALDEF__LCCM215__OWN_ADDRESS                        	(0x50)

		/** Number of loops to wait for the timeout*/
		#define C_LOCALDEF__LCCM215__TIMEOUT_CYCLES   						(10000000U)

		#define C_LOCALDEF__LCCM215__USE_INTERRUPTS 						(0U)

		#if C_LOCALDEF__LCCM215__USE_INTERRUPTS == 1U

			#define C_LOCALDEF__LCCM215__ISR_ARBITRATION_LOST_ENABLE 		(1U)
			#define C_LOCALDEF__LCCM215__ISR_NACK_ENABLE					(1U)
			#define C_LOCALDEF__LCCM215__ISR_ACCESS_READY_ENABLE 			(1U)
			#define C_LOCALDEF__LCCM215__ISR_RECEIVE_ENABLE					(1U)
			#define C_LOCALDEF__LCCM215__ISR_TRANSMIT_ENABLE 				(1U)
			#define C_LOCALDEF__LCCM215__ISR_STOP_ENABLE					(1U)
			#define C_LOCALDEF__LCCM215__ISR_ADDRESS_AS_SLAVE_ENABLE 		(1U)

			//Callbacks to handle I2C interrupts
			#if C_LOCALDEF__LCCM215__ISR_ARBITRATION_LOST_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_ARBITRATION_LOST() 		vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_NACK_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_NACK() 					vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_ACCESS_READY_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_ACCESS_READY() 			vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_RECEIVE_ENABLE == 1U
				#define C_LOCALDEF__LCCM215__ISR_RECEIVE() 					vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_TRANSMIT_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_TRANSMIT() 				vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_STOP_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_STOP() 					vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_ADDRESS_AS_SLAVE_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_ADDRESS_AS_SLAVE() 		vRM4_I2C_ISR__DefaultRoutine()
			#endif
		#endif

		/** Testing Options */
		#define C_LOCALDEF__LCCM215__ENABLE_TEST_SPEC						(0U)


		//main include file
		#include <RM4/LCCM215__RM4__I2C/rm4_i2c.h>

	#endif //C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE


/*******************************************************************************
DS2482S - I2C TO 1-WIRE CONVERTER
*******************************************************************************/
	#define C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

		/** Max number of DS2482 devices on the same I2C Bus */
		#define C_LOCALDEF__LCCM641__NUM_DEVICS								(2U)

		/** Use table based LUT CRC or slow computed CRC */
		#define C_LOCALDEF__LCCM641__USE_TABLE_CRC							(1U)

		/** When waiting in loops, we need a program loop timeout value */
		#define C_LOCALDEF__LCCM641__MAX_TIMEOUT_LOOPS						(100000U)

		// I2C MACROS
		#define M_LOCALDEF__LCCM641__I2C_RX_REG(device, reg)				s16RM4_I2C_USER__RxReg(RM4_I2C_CH__1, device, reg)
		#define M_LOCALDEF__LCCM641__I2C_TX_REG(device, reg)				s16RM4_I2C_USER__TxReg(RM4_I2C_CH__1, device, reg)
		#define M_LOCALDEF__LCCM641__I2C_TX_BYTE(device, reg, value)		s16RM4_I2C_USER__Tx_U8(RM4_I2C_CH__1, device, reg, value)
		#define M_LOCALDEF__LCCM641__I2C_RX_BYTE(device, reg, value)		s16RM4_I2C_USER__Rx_U8(RM4_I2C_CH__1, device, reg, value)


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
		#define C_LOCALDEF__LCCM644__MAX_DEVICES							(24U)

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

#endif /* LOCALDEF_H_ */
