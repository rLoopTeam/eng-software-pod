#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	/*lint -e950*/
	/** BMS PCB VERSION
	 *
	 * 1 = RM48 (Lachlan - Pod V1)
	 * 2 = RM57 (David - Pod V2)
	 */

	#define C_LOCALDEF__BMS_REVISION 		(2U)

	//The launchpad
#ifndef WIN32
	#include <../../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
	#include <../../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#else
	#include <../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
	#include <../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#endif

/*******************************************************************************
SIL3 - RM4 MiBSPI 1,3 and 5 Common Driver
*******************************************************************************/
	#define C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE == 1U

		//enable specific channels
		#define C_LOCALDEF__LCCM280__ENABLE_MIBSPI_1						(1U)
		#define C_LOCALDEF__LCCM280__ENABLE_MIBSPI_3						(1U)
		#define C_LOCALDEF__LCCM280__ENABLE_MIBSPI_5						(1U)

		//set to 1 to use interrupts
		#define C_LOCALDEF__LCCM280__ENABLE_INTERRUPTS						(1U)

		//setup the data formats
		#if C_LOCALDEF__LCCM280__ENABLE_MIBSPI_1 == 1U

			#define C_LOCALDEF__LCCM280__ENABLE_MULTIBUFFERED_MODE_1		(0U)

			//the transfer length of up to 16 bits
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_0__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_1__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_2__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_3__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS

			//set the speed of each format
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_0__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_1__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_2__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_3__SPEED			MIBSPI135_SPEED__5MHZ

			//clock phase
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_0__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_1__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_2__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_3__CPHA			MIBSPI135_CPHA__1

			//clock polarity
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_0__CPOL			MIBSPI135_CPOL__0
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_1__CPOL			MIBSPI135_CPOL__0
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_2__CPOL			MIBSPI135_CPOL__0
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_3__CPOL			MIBSPI135_CPOL__0


		#endif //C_LOCALDEF__LCCM280__ENABLE_MIBSPI_1

		#if C_LOCALDEF__LCCM280__ENABLE_MIBSPI_3 == 1U

			#define C_LOCALDEF__LCCM280__ENABLE_MULTIBUFFERED_MODE_3		(0U)

			//pinmux options
			//Enable in place of GIO B2
			#define C_LOCALDEF__LCCM280__ENABLE_PIN__MIBSPI3_NCS0			(0U)

			//the transfer length of up to 16 bits
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_0__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_1__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_2__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_3__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS

			//set the speed of each format
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_0__SPEED			MIBSPI135_SPEED__400K
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_1__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_2__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_3__SPEED			MIBSPI135_SPEED__5MHZ

			//clock phase
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_0__CPHA			MIBSPI135_CPHA__0
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_1__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_2__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_3__CPHA			MIBSPI135_CPHA__1

		#endif //C_LOCALDEF__LCCM280__ENABLE_MIBSPI_3

		#if C_LOCALDEF__LCCM280__ENABLE_MIBSPI_5 == 1U

			#define C_LOCALDEF__LCCM280__ENABLE_MULTIBUFFERED_MODE_5		(0U)

			//the transfer length of up to 16 bits
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_0__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_1__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_2__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_3__TXLEN_BITS	MIBSPI135_DATAFORMAT__8BITS

			//set the speed of each format
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_0__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_1__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_2__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_3__SPEED			MIBSPI135_SPEED__5MHZ

			//clock phase
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_0__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_1__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_2__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_5__DATAFMT_3__CPHA			MIBSPI135_CPHA__1

		#endif //C_LOCALDEF__LCCM280__ENABLE_MIBSPI_5

		/** Tesing Options */
		#define C_LOCALDEF__LCCM280__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM280__RM4__MIBSPI_135/rm4_mibspi135.h>

	#endif //C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE

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
RM4 - I2C DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE == 1U

		//The bus freq (100K, 400K, 1MHZ)
		#define C_LOCALDEF__LCCM215__BUS_FREQUENCY_HZ   					(100000U)

		#define C_LOCALDEF__LCCM215__OWN_ADDRESS                        	(0x50)

		/** Number of loops to wait for the timeout*/
		#define C_LOCALDEF__LCCM215__TIMEOUT_CYCLES   						(1000000U)

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
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_CALLBACK					vPWRNODE__RTI_10MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_CALLBACK					vPWRNODE__RTI_100MS_ISR()
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
SIL3 - SAFETY UDP LAYER
*******************************************************************************/
	#define C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

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
		#define C_LOCALDEF__LCCM644__MAX_DEVICES							(250U)

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
TSYS01 - DIGITAL TEMP SENSOR
*******************************************************************************/
	#define C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

		//Architecture
		#define C_LOCALDEF__LCCM647__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM647__USE_ON_MSP430							(0U)

        /** Size of filter */
        #define C_LOCALDEF__LCCM647__MAX_FILTER_SAMPLES                     (8U)

		/** The number of main program loops to wait for conversion */
		#define C_LOCALDEF__LCCM647__NUM_CONVERSION_LOOPS					(10000U)

		/** the I2C address on the bus */
		#if C_LOCALDEF__BMS_REVISION == 1U
			#define C_LOCALDEF__LCCM647__BUS_ADDX								(0x77U)
		#elif C_LOCALDEF__BMS_REVISION == 2U
			#define C_LOCALDEF__LCCM647__BUS_ADDX								(0x76U)
		#else
			#error
		#endif

		/** Testing Options */
		#define C_LOCALDEF__LCCM647__ENABLE_TEST_SPEC						(0U)


		/** Enable datasheet values to test math
		 * DO NOT put this in production */
		#define C_LOCALDEF__LCCM647__ENABLE_DS_VALUES						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>

	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U


/*******************************************************************************
SIL3 - RM4 ADC DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U

		/** Vref constant used for voltage calc 5V/(2^12)*/
		#define C_LOCALDEF__LCCM414__VREF_CONSTANT							(0.001220703125)

		/** The number of ADC channels (modules) being used
		 * Keep a 1 for now
		 */
		#define C_LOCALDEF__LCCM414__NUM_ADC_MODULES						(1U)

		/** Continuous Conversion Mode:  When enabled the ADC
		 * Will always keep making samples of the configured channels
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_CONTINUOUS_CONVERSION			(0U)

		/** Averaging is enabled across all channels.
		 * It can consume serious CPU time for a fully enabled ADC
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_AVERAGING						(1U)

		/** The number of samples for each channels ADC averager */
		#define C_LOCALDEF__LCCM414__AVERAGE_MAX_SAMPLES					(4U)


		/** Determine which of ADC1 to enable */

		//charge volts
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN0						(1U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN1						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN2						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN3						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN4						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN5						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN6						(0U)
		//battery current
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN7						(1U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN8						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN9						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN10						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN11						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN12						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN13						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN14						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN15						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN16						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN17						(0U)
		//batt current reference
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN18						(1U)
		//batt voltage
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN19						(1U)
		//charge current ref
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN20						(1U)
		//charge current.
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN21						(1U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN22						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN23						(0U)

		/** The number of connected devices to the ADC's
		 * We store a local copy of our ADC results in a user addressable
		 * structure to reduce the complexity of finding our result
		 * Value can be from 1 to 24
		 */
		#define C_LOCALDEF__LCCM414__NUM_CONNECTED_DEVICES					(6U)

		/** For each device we determine the location of the device within our strucrture
		 * You must configure an index from 0 to NUM_CONNECTED_DEVICES - 1
		 * No two units may have the same index
		 * Example MAP ADC1_IN0 to Device (1)
		 */
		//charge voltage
		#define C_LOCALDEF__LCCM414__ADC1_IN0__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN1__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN2__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN3__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN4__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN5__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN6__INDEX						(0U)
		//battery current
		#define C_LOCALDEF__LCCM414__ADC1_IN7__INDEX						(1U)
		#define C_LOCALDEF__LCCM414__ADC1_IN8__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN9__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN10__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN11__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN12__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN13__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN14__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN15__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN16__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN17__INDEX						(0U)
		//battery current ref
		#define C_LOCALDEF__LCCM414__ADC1_IN18__INDEX						(2U)
		//battery voltage
		#define C_LOCALDEF__LCCM414__ADC1_IN19__INDEX						(3U)
		//charge current ref
		#define C_LOCALDEF__LCCM414__ADC1_IN20__INDEX						(4U)
		//charge current
		#define C_LOCALDEF__LCCM414__ADC1_IN21__INDEX						(5U)
		#define C_LOCALDEF__LCCM414__ADC1_IN22__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN23__INDEX						(0U)

		/** Enable voltage conversion to return the voltage value
		 * for a device.  This reduces the external workload to compute the
		 * voltage based on VREF
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_VOLTAGE_CALC					(1U)

		/** Use interrupts */
		#define C_LOCALDEF__LCCM414__ENABLE_INTERRUPTS						(0U)

		//testing
		#define C_LOCALDEF__LCCM414__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM414__RM4__ADC/rm4_adc.h>

	#endif //C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE

/*******************************************************************************
BQ76PL536A - BMS DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

		/** number of devices in series */
		#define C_LOCALDEF__LCCM715__NUM_DEVICES							(3U)

		/** Use checksum support on the comms or not? */
		#define C_LOCALDEF__LCCM715__ENABLE_CRC								(0U)

		/** Average window, set to 0 for averaging off */
		#define C_LOCALDEF__LCCM715__AVERAGE_WINDOW							(16U)


		/** SPI TX / RX */
		#define M_LOCALDEF__LCCM715__SPI_TX_U8(x)							u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__3, MIBSPI135_DATA_FORMAT__0, MIBSPI135_CS__NONE, x)

		/** Chip Select */
		#define M_LOCALDEF__LCCM715__LATCH__CS(x)							{vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS1, x);}

		/** Convert Control */
		#define M_LOCALDEF__LCCM715__LATCH__CONV(x)							{vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 2U, x);}

		/** Data Ready Input (if not using interrupts) */
		#define M_LOCALDEF__LCCM715__PORT__DRDY()							u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 16U)

		/** Fault Input (if not using interrupts) */
		#define M_LOCALDEF__LCCM715__PORT__FAULT()							u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 18U)

		/** Alert Input (if not using interrupts) */
		#define M_LOCALDEF__LCCM715__PORT__ALERT()							u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 22U)


		/** Testing Options */
		#define C_LOCALDEF__LCCM715__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>

	#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RLOOP - POWER NODE CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

		/** Enable the battery temperature measurement system */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP						(0U)

		/** Enable or disable battery temp search */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP_SEARCH				(0U)

		/** Enable the BMS Subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_BMS								(1U)

		/** Enable the PV temp system using TSYS01 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP						(0U)

		/** Node pressure using MS5607 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS						(0U)

		/** Enable the DC/DC converter subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER					(0U)
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
		#define C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS						(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM653__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM653__RLOOP__POWER_CORE/power_core.h>

	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

#endif /* LOCALDEF_H_ */
