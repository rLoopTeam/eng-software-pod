#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	//The PCB's main files
	#include <../../../BOARD_SUPPORT/lpcb235r0__board_support.h>

/*******************************************************************************
GENERAL PURPOSE
SOFTWARE FIFO
*******************************************************************************/
	#define C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo.h>

	#endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE

/*******************************************************************************
AMC7812
*******************************************************************************/
	#define C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

		/** Num devices on the bus */
		#define C_LOCALDEF__LCCM658__NUM_DEVICES							(1U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM658__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM658__MULTICORE__AMC7812/amc7812.h>
	#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U


/*******************************************************************************
SC16IS741 - UART TO SPI MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U

		//architecture
		#define C_LOCALDEF__LCCM487__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM487__USE_ON_MSP430							(0U)

		//configure the number of devices in the system
		#define C_LOCALDEF__LCCM487__NUM_DEVICES							(8U)

		/** If we have multiple devices we can choose to have a common hardware
		reset line */
		#define C_LOCALDEF__LCCM487__HAVE_COMMON_HW_RESET					(1U)

		//HW reset tristate
		//Serial A, Serial B, ASI Serial
		#define M_LOCALDEF__LCCM487__HW_RESET__TRIS(index)					{vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 1U); \
																			 vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 2U); \
																			 vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 23U);}

		//Serial A, Serial B, ASI Serial
		#define M_LOCALDEF__LCCM487__HW_RESET__LATCH(value)					{vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 1U, value); \
																			 vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 2U, value);	\
																			 vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 23U, value);	}

		//CS indexing
		//A0, A1, A2
		//B0, B1, B2, B3
		//ASI0
		#define M_LOCALDEF__LCCM487__HW_CHIPSELECT__TRIS(index) 			{\
																			if(index == 0U)			vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS0);\
																			else if(index == 1U) 	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__ENA);\
																			else if(index == 2U) 	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__CS3); \
																			else if(index == 3U) 	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SIMO1); \
																			else if(index == 4U) 	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SOMI1); \
																			else if(index == 5U) 	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 3U); \
																			else if(index == 6U) 	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SIMO3); \
																			else if(index == 7U) 	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SOMI3); \
																			}


		//Chip select latch pin
		#define M_LOCALDEF__LCCM487__HW_CHIPSELECT__LATCH(index, value) 	{\
																			if(index == 0U)			vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS0, value); \
																			else if(index == 1U) 	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__ENA, value); \
																			else if(index == 2U) 	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__CS3, value); \
																			else if(index == 3U) 	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SIMO1, value); \
																			else if(index == 4U) 	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SOMI1, value); \
																			else if(index == 5U) 	vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 3U, value); \
																			else if(index == 6U) 	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SIMO3, value); \
																			else if(index == 7U) 	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__SOMI3, value); \
																			}

		#define M_LOCALDEF__LCCM487__HW_INTERUPTPIN__TRIS(index) 			{ \
																			if(index == 0U) 		vRM4_GIO__Set_BitDirection(gioPORTA, 2, GIO_DIRECTION__INPUT); \
																			else if(index == 1U) 	vRM4_GIO__Set_BitDirection(gioPORTA, 3, GIO_DIRECTION__INPUT); \
																			else if(index == 2U) 	vRM4_GIO__Set_BitDirection(gioPORTA, 4, GIO_DIRECTION__INPUT); \
																			else if(index == 3U) 	vRM4_GIO__Set_BitDirection(gioPORTB, 1, GIO_DIRECTION__INPUT); \
																			else if(index == 4U) 	vRM4_GIO__Set_BitDirection(gioPORTB, 3, GIO_DIRECTION__INPUT); \
																			else if(index == 5U) 	vRM4_GIO__Set_BitDirection(gioPORTB, 6, GIO_DIRECTION__INPUT); \
																			else if(index == 6U) 	vRM4_GIO__Set_BitDirection(gioPORTB, 0, GIO_DIRECTION__INPUT); \
																			else if(index == 7U) 	vRM4_GIO__Set_BitDirection(gioPORTB, 7, GIO_DIRECTION__INPUT); \
																			}


		//SPI Interface
		#define M_LOCALDEF__LCCM487__SPI__TX_U8(u8Value)					u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__1, MIBSPI135_DATA_FORMAT__0, MIBSPI135_CS__NONE, u8Value)

		//testing
		#define C_LOCALDEF__LCCM487__ENABLE_TEST_SPEC							(1U)


		//main include file
		#include <MULTICORE/LCCM487__MULTICORE__SC16IS741/sc16.h>
	#endif //#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U

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
RLOOP - FLIGHT CONTROL UNIT - CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U


		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER			(0U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO				(1U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN				(2U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO				(3U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN				(4U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC				(5U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U


#endif /* LOCALDEF_H_ */
