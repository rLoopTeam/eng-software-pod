
/* BOARD SUPPORT HEADER FOR LPCB234R0 (POWER CONTROL NODE + RM48CNCD)
 * 
 * SIGNAL NAME			DIRECTION		RM4 FUNCTION
 * ----------------------------------------------------------------------
 * CHARGE CURRENT		INPUT			AD1:08
 * BATTERY VOLTAGE		INPUT			AD1:09
 * CHARGE VOLTAGE		INPUT			AD1:10
 * CHARGE BUS TIE		OUT				GIOA:1
 * DC/DC WDOG PULSE		OUT				GIOA:0
 * BMS PWR AVAIL		IN				GIOA:5
 * BMS NCS				OUTPUT			GIOB:4
 * BMS PWR DISABLE		OUTPUT			GIOB:2
 * BMS MISO				INPUT			SPI1MISO
 * BMS MOSI				OUT				SPI1SIMO
 * BMS SCK				OUT				SPI1CLK
 * BMS IRQ				IN				GIOA:4
 * CAN RX				IN				CAN1
 * CAN TX				OUT				CA1
 * I2C SDA				BI				I2C
 * I2C SCL				OUT				I2C
*/



#ifndef _LPCB234R0_BOARD_SUPPORT_H_
#define _LPCB234R0_BOARD_SUPPORT_H_

/*******************************************************************************
RM4 MAIN SYSTEM SETUP
Place this at the top of your Localdef file
Change the build settings:
1. Enable GCC extensions under advanced options -> language options
2. Enable unaligned loads and stores to on
3. Make sure designate enum type is packed.

*******************************************************************************/
	/*lint -e950 */
	/*lint -e621 */
	//data types
	#include <RM4/LCCM105__RM4__BASIC_TYPES/basic_types.h>

	//set this to 1 to disable all common startups as would be used by a bootloader
	#define C_LOCALDEF__SYSTEM__DISABLE_ALL_FOR_BOOTLOADER					(0U)

	//change osc freq to match the osc on your board
	//valid values are 10 and 16MHZ
	#define C_LOCALDEF__SYSTEM__OSCILLATOR_FREQ     						(16000000U)

	//This is the HCLK frequency, it is not defined here, but is a result of the
	//PLL1 setup.  Standard range is 200MHZ to 220MHZ (952 part)
	//Valid Is:
	//220
	//200 (Standard)
	//150 (Low Power)
	//100 (Low Power)
	#define C_LOCALDEF__SYSTEM__HCLK_FREQ_MHZ								(200U)

	//normal bus division is either 1 or 2
	//In 1x mode, VCLK1 is 100MHZ, in 2x mode VCLK is 50MHZ
	//you may only need 2x mode if you need ultra lo SPI comms, etc.
	#define C_LOCALDEF__SYSTEM__VCLK1_DIVISOR								(2U)


	//just here because of no EMIF
	//if ou are using EMIF, then remove this line
	#define C_LOCALDEF__LCCM107__EMIF_CLOCK_DIVISOR							(1U)


	//we have the ability to use the ECLK pin to generate a high frequency divided
	//clock signal, possibly faster than we can do with PWM
	#define C_LOCALDEF__SYSTEM__ENABLE_ECLK									(0U)

	//The divisor is VCLK1 /x so a value of 40x = 2.5MHZ ECLK
	#define C_LOCALDEF__SYSTEM__ECLK_DIVISOR								(40U)

	//other includes
	#include <RM4/LCCM219__RM4__SYSTEM/rm4_system.h>

	#include <RM4/LCCM364__RM4__FIRMWARE_VERSION/rm4_firmware_version.h>

/*******************************************************************************
RM4 CRC MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM226__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM226__RM4__CRC/rm4_crc.h>

	#endif //C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE


/*******************************************************************************
FLASH MODULE
Even if you don't want in system programming or firmware update features
include this to get access to the flash registers and setup features
*******************************************************************************/
#ifdef PCLINT_ENABLED
	#define C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE							(0U)
#else
	#define C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE							(1U)
#endif
	#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U

		//enable F021
		#define C_LOCALDEF__LCCM135__ENABLE_F021							(1U)

		//testing options
		#define C_LOCALDEF__LCCM135__ENABLE_TEST_SPEC						(0U)

		#include <RM4/LCCM135__RM4__FLASH/rm4_flash.h>

	#endif //#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U
	
/*******************************************************************************
RM4 DELAY ROUTINES
*******************************************************************************/
	#define C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE == 1U

		//Testing options
		#define C_LOCALDEF__LCCM228__ENABLE_TEST_SPEC						(0U)

		//enable the PMU if needed
		#define C_LOCALDEF__LCCM288__ENABLE_PMU_FOR_DEBUG					(0U)

		//main include file
		#include <RM4/LCCM228__RM4__DELAYS/rm4_delays.h>

	#endif //C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE
	
/*******************************************************************************
ERROR SIGNALLING MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM220__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM220__RM4__ERROR_SIGNAL_MODULE/rm4_esm.h>

	#endif //C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE


/*******************************************************************************
RM4 DMA Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM229__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM229__RM4__DMA/rm4_dma.h>

	#endif //C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE

/*******************************************************************************
RM4 PIN MUX SYSTEM
*******************************************************************************/
	#define C_LOCALDEF__LCCM222__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM222__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM222__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM222__RM4__PIN_MUX/rm4_pinmux.h>

	#endif //C_LOCALDEF__LCCM222__ENABLE_THIS_MODULE	
	
/*******************************************************************************
SCI / LIN Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

		//if you have to do debugging
		//#define DEBUG_PRINT(x)												vRM4_SCI_HELPERS__DisplayText(SCI_CHANNEL__1, x, 100)
		#define DEBUG_PRINT(x)

		//enable interrupts, else use polling Mode
		#define C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS						(1U)

		/** Switch on DMA functions */
		#define C_LOCALDEF__LCCM282__ENABLE_DMA								(1U)

		//determine which SCI module to enable
		//SCI1 shares pins with EMAC and on RM48 CNCD with resistors removed is not avail
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_1							(0U)

		//SCI 2 is also LIN and uses the LIN pins on ZWT Package
		//SCI2 is Pi Comms
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_2							(1U)

		//testing
		#define C_LOCALDEF__LCCM282__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM282__RM4__SCI/rm4_sci.h>

	#else
		#define DEBUG_PRINT(x)
	#endif //C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE
	
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
RM4 MiB SPI 1,3 and 5 Common Driver
*******************************************************************************/
	#define C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE == 1U

		//enable specific channels
		#define C_LOCALDEF__LCCM280__ENABLE_MIBSPI_1						(1U)
		#define C_LOCALDEF__LCCM280__ENABLE_MIBSPI_3						(0U)
		#define C_LOCALDEF__LCCM280__ENABLE_MIBSPI_5						(0U)

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
			//ATA6870N Clock Max = 0.5xFclk = 250KHZ!!! Max
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_0__SPEED			MIBSPI135_SPEED__400K
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_1__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_2__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_3__SPEED			MIBSPI135_SPEED__5MHZ

			//clock phase
			//ATA6870N is phase 0
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_0__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_1__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_2__CPHA			MIBSPI135_CPHA__1
			#define C_LOCALDEF__LCCM280__MIBSPI_1__DATAFMT_3__CPHA			MIBSPI135_CPHA__1

			//clock polarity
			//ATA6870 is polarity 0
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
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_0__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_1__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_2__SPEED			MIBSPI135_SPEED__5MHZ
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_3__SPEED			MIBSPI135_SPEED__5MHZ

			//clock phase
			#define C_LOCALDEF__LCCM280__MIBSPI_3__DATAFMT_0__CPHA			MIBSPI135_CPHA__1
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
RM4 I2C
*******************************************************************************/
	#define C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE == 1U

		//The bus freq (100K, 400K, 1MHZ)
		#define C_LOCALDEF__LCCM215__BUS_FREQUENCY_HZ   					(400000U)

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
RTI MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

		//globally switch on the WDT
		#define C_LOCALDEF__LCCM124__ENABLE_WDT								(1U)

		/** RTI CLOCK FREQUENCY
		 * Based on our standard system, valid values are div(2,4,8):
		 * 100 	(100MHZ)
		 * 50	(50MHZ)
		 * 25	(25MHZ)
		 * */
		#define C_LOCALDEF__LCCM124__RTI_CLK_FREQ							(25U)

		/** RTCLK1 feeds counter 1 and can be used for 64bit timing */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER1_PRESCALER					(1U)


		//Sets up the time periods for each compare. Must be defined in microSeconds.
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_PERIOD_US 				(100000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_PERIOD_US 				(10000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_PERIOD_US 				(1000000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_PERIOD_US 				(1000000U)

		//these are the interrupt handlers which should point
		//to a function, otherwise leave as default
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_CALLBACK					vPWRNODE__RTI_100MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_CALLBACK					vPWRNODE__RTI_10MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()

		//These values need to be updated if the HALCoGen file is modified
		#define GCLK_FREQ		 											(200)
		#define HCLK_FREQ													(200)
		#define VCLK1_FREQ													(100)
		#define VCLK2_FREQ													(100)
		#define VCLK3_FREQ													(100)
		#define VCLKA1_FREQ	 												(100)
		#define VCLKA4_FREQ	 												(100)

		//Testing options
		#define C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC	 					(0U)

		#include <RM4/LCCM124__RM4__RTI/rm4_rti.h>

	#endif //#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
SafeTool Branch Analysis Support
*******************************************************************************/
	#define C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE							(0U)
	#if C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE == 1U

		/** The maximum number of branch calls permissible, adjust as necessary
		 * depening on function size and test environment.
		 */
		#define C_LOCALDEF__LCCM517__MAX_BRANCH_CALLS						(16U)


		/** Testing Options */
		#define C_LOCALDEF__LCCM517__ENABLE_TEST_SPEC						(0U)


		/** Main include file */
		#include <MULTICORE/LCCM517__MULTICORE__SAFETOOL_BRANCH/safetool_branch.h>
	#else
		//placeholder
		#define SAFETOOL_BRANCH(stFuncID)
	#endif //#if C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE == 1U
	
/*******************************************************************************
SOFTWARE MULTIPURPOSE FAULT TREE HANDLER
*******************************************************************************/
	#define C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM284__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree.h>

	#endif //C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE

	

/*******************************************************************************
NUMERICAL MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM118__USE_ON_DSPIC   						(0U)

		/** set to 1 to include TRIG */
		#define C_LOCALDEF__LCCM118__ENABLE_TRIG							(1U)

		/** enable x^y */
		#define C_LOCALDEF__LCCM118__ENABLE_POWER							(1U)

		/** enable vector math */
		#define C_LOCALDEF__LCCM118__ENABLE_VECTORS							(0U)

		/** DISABLES */
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__S16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__U16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__U32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__S32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__F32					(0U)

		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__S16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__S32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__F32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__F64					(0U)

		/** Testing options */
		#define	C_LOCALDEF__LCCM118__ENABLE_TEST_SPEC						(0U)

		//main include
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical.h>
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE

/*******************************************************************************
SOFTWARE BASED CRC
*******************************************************************************/
	#define C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

		//set to 1 to enable test specification code
		#define C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC						(0U)

		//types of CRC
		#define C_LOCALDEF__LCCM012__ENABLE_CRC7							(0U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC8							(1U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC16							(1U)

		//set to 1 to enable table based CRC16
		//Note: Not possible on PIC18 due to page sizes
		#define C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC					(1U)


		#if C_LOCALDEF__LCCM012__ENABLE_CRC16 == 1U

			//if using tables, define any alignment issues
			#if C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC == 1U
				#ifndef WIN32
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[] __attribute__ ((aligned (128)))
				#else
					//no alignment possible on win32.
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[]
				#endif
			#endif //C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC
		#endif

		#include <MULTICORE/LCCM012__MULTICORE__SOFTWARE_CRC/software_crc.h>

	#endif

/*******************************************************************************
DP83640 - Ethernet PHY with IEE1588
*******************************************************************************/
	#define C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U

		/** CPU Architecture */
		#define C_LOCALDEF__LCCM515__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM515__USE_ON_XILINX							(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM515__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM515__MULTICORE__DP83640/dp83640.h>

	#endif //#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U


/*******************************************************************************
EMAC Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE == 1U

		//on some dev boards we need to use RMII mode, not MII mode
		//RMII on RM48CNCD cards
		#define C_LOCALDEF__LCCM254__ENABLE_RMII_MODE						(1U)


		//set to 1 if you have an external reset pin to the EMAC
#ifndef WIN32
		#define C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET					(0U)
#else
		#define C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET					(0U)
#endif

		#if C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET == 1U
			#define C_LOCALDEF__LCCM254__NRESET_PIN__TRIS()					vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 0U)
			#define C_LOCALDEF__LCCM254__NRESET_PIN__LATCH(x)				vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 0U, x)
		#endif


		//use LWIP or not
		#define C_LOCALDEF__LCCM254__USE_WITH_LWIP							(0U)
		#define C_LOCALDEF__LCCM254__USE_WITH_LCCM325						(1U)

		//testing options
		#define C_LOCALDEF__LCCM254__ENABLE_TEST_SPEC						(0U)
		#define C_LOCALDEF__LCCM254__ENABLE_IO_PIN_TESTING					(0U)

		//main include file
		#include <RM4/LCCM254__RM4__EMAC/rm4_emac.h>

	#endif //C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE


/*******************************************************************************
ADC Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U

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
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN0						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN1						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN2						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN3						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN4						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN5						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN6						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN7						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN8						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN9						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN10						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN11						(1U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN12						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN13						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN14						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN15						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN16						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN17						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN18						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN19						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN20						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN21						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN22						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN23						(0U)

		/** The number of connected devices to the ADC's
		 * We store a local copy of our ADC results in a user addressable
		 * structure to reduce the complexity of finding our result
		 * Value can be from 1 to 24
		 */
		#define C_LOCALDEF__LCCM414__NUM_CONNECTED_DEVICES					(1U)

		/** For each device we determine the location of the device within our strucrture
		 * You must configure an index from 0 to NUM_CONNECTED_DEVICES - 1
		 * No two units may have the same index
		 * Example MAP ADC1_IN0 to Device (1)
		 */
		#define C_LOCALDEF__LCCM414__ADC1_IN0__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN1__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN2__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN3__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN4__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN5__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN6__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN7__INDEX						(0U)
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
		#define C_LOCALDEF__LCCM414__ADC1_IN18__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN19__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN20__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN21__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN22__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN23__INDEX						(0U)

		/** Enable voltage conversion to return the voltage value
		 * for a device.  This reduces the external workload to compute the
		 * voltage based on VREF
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_VOLTAGE_CALC					(1U)


		#define C_LOCALDEF__LCCM414__ENABLE_INTERRUPTS						(0U)

		#define C_LOCALDEF__LCCM414__ENABLE_TEST_SPEC						(0U)



		//main include file
		#include <RM4/LCCM414__RM4__ADC/rm4_adc.h>
	#endif //C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE

/*******************************************************************************
GENERAL PURPOSE
SOFTWARE FIFO
*******************************************************************************/
	#define C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U

		/** Software FIFO depth size, U8 = 255 or U16 = 65K, not both */
		#define C_LOCALDEF__LCCM357__FIFO_DEPTH_U8							(0U)
		#define C_LOCALDEF__LCCM357__FIFO_DEPTH_U16							(1U)

		//testing options
		#define C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo.h>

	#endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE


/*******************************************************************************
RM48 - CPU LOAD MEASUREMENT
*******************************************************************************/
	#define C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

		/** The filtering size for the percentage trend */
		#define C_LOCALDEF__LCCM663__FILTER_WINDOW							(4U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM663__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <RM4/LCCM663__RM4__CPU_LOAD/rm4_cpuload.h>
	#endif //#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RM4 High End Timers (HET)
General Configuration
HR Clock = 100MHZ
VCLK2 = 100Mhz, Actual HR Clock = 100MHZ
Loop Time = 100ns
LR Time = 160ns
*******************************************************************************/
	#define C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE							(1U)
 	 #if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U

		//Module Enables
		#define C_LOCALDEF__LCCM240__ENABLE_N2HET1							(1U)
		#define C_LOCALDEF__LCCM240__ENABLE_N2HET2							(0U)

		//enable interrupts or not
		#define C_LOCALDEF__LCCM240__ENABLE_INTERRUPTS						(1U)


		//HET Options
		#define C_LOCALDEF__LCCM240__ENABLE_INPUT_CAPTURE					(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_EDGE_CAPTURE					(1U)
		#define C_LOCALDEF__LCCM240__ENABLE_PWM								(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_TIMESTAMPING					(0U)

		//testing
		#define C_LOCALDEF__LCCM240__ENABLE_TEST_SPEC						(0U)

 	 	//main include
 	 	#include <RM4/LCCM240__RM4__N2HET/rm4_n2het.h>

 	 #endif //C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE


/*******************************************************************************
RM4 EEPROM EMULATION
You'll need the flash access module for this
*******************************************************************************/
	#define C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE							(1U)
 	 #if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM230__ENABLE_TEST_SPEC						(0U)

 	 	//main include
 	 	#include <RM4/LCCM230__RM4__EEPROM/rm4_eeprom.h>

 	 #endif //C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE


/*******************************************************************************
EEPROM BASIC PARAMETERS
*******************************************************************************/
	#define C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U

		//select your architecture
		#define C_LOCALDEF__LCCM188__USE_ON_PIC18							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_PIC32							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_DSPIC							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_RM4 							(1U)
		#define C_LOCALDEF__LCCM188__USE_ON_MSP430 							(0U)
		#define C_LOCALDEF__LCCM188__USE_ON_WIN32 							(0U)

		/** Use the EEPRARAMS module with an external FLASH */
		#define C_LOCALDEF__LCCM188__USE_WITH_LCCM013						(0U)

		/** Define the number of parameters in the system */
		#define C_LOCALDEF__LCCM188__NUM_PARAMETERS							(128U)

		/** set to 1 if you want to enable CRC's across the entire paramter
		range.  If so you will loose one paramter at the end to store theCRC
		*/
		#define C_LOCALDEF__LCCM188__ENABLE_CRC								(1U)

		/** Offset to start in memory */
		#define C_LOCALDEF__LCCM188__EEPROM_START_OFFSET					(0U)

		/** DISABLES */
		#define C_LOCALDEF__LCCM188__DISABLE__U16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__U32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__F32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__MAC							(0U)

		/** Testing options */
		#define C_LOCALDEF__LCCM188__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM188__MULTICORE__EEPROM_PARAMS/eeprom_params.h>

	#endif //C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE

/*******************************************************************************
SOFTWARE BASED CRC
*******************************************************************************/
	#define C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

		//set to 1 to enable test specification code
		#define C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC						(0U)

		//types of CRC
		#define C_LOCALDEF__LCCM012__ENABLE_CRC7							(0U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC8							(1U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC16							(1U)

		//set to 1 to enable table based CRC16
		//Note: Not possible on PIC18 due to page sizes
		#define C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC					(1U)


		#if C_LOCALDEF__LCCM012__ENABLE_CRC16 == 1U

			//if using tables, define any alignment issues
			#if C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC == 1U
				#ifndef WIN32
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[] __attribute__ ((aligned (128)))
				#else
					//no alignment possible on win32.
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[]
				#endif
			#endif //C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC
		#endif

		#include <MULTICORE/LCCM012__MULTICORE__SOFTWARE_CRC/software_crc.h>

	#endif

#endif //_LPCB234R0_BOARD_SUPPORT_H_

