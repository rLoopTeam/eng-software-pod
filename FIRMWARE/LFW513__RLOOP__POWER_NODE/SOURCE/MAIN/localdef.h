#ifndef LOCALDEF_H_
#define LOCALDEF_H_

/*lint -e950*/

	//The control card
	#include <../../../BOARD_SUPPORT/lpcb234r0__board_support.h>



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

		
		//setup for functions
		#define M_LOCALDEF__LCCM650__NCS_TRIS(dir)							{if(dir == 0U) vRM4_GIO__Set_BitDirection(gioPORTB, 4U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(gioPORTB, 4U, GIO_DIRECTION__INPUT);}
		#define M_LOCALDEF__LCCM650__NCS_LATCH(val)							{vRM4_GIO__Set_Bit(gioPORTB, 4U, val);}
		#define M_LOCALDEF__LCCM650__SPI_TX_U8(x)							u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__1, MIBSPI135_DATA_FORMAT__0, MIBSPI135_CS__NONE, x)

		#define M_LOCALDEF__LCCM650__POWER_ENABLE_TRIS(x)					{if(x == 0U) vRM4_GIO__Set_BitDirection(gioPORTB, 2U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(gioPORTB, 2U, GIO_DIRECTION__INPUT); }
		#define M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(x)					{vRM4_GIO__Set_Bit(gioPORTB, 2U, x); }

		#define M_LOCALDEF__LCCM650__POWER_AVAIL_TRIS(x)					{if(x == 0U) vRM4_GIO__Set_BitDirection(gioPORTB, 5U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(gioPORTB, 5U, GIO_DIRECTION__INPUT); }
		#define M_LOCALDEF__LCCM650__POWER_AVAIL_PORT()						u32RM4_GIO__Get_Bit(gioPORTB, 5U)

		
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


		/** Testing Options */
		#define C_LOCALDEF__LCCM648__ENABLE_TEST_SPEC							(0U)

		/** Main include file */
		#include <MULTICORE/LCCM648__MULTICORE__MS5607/ms5607.h>

	#endif //#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
TSYS01 - DIGITAL TEMP SENSOR
*******************************************************************************/
	#define C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U


		/** Testing Options */
		#define C_LOCALDEF__LCCM647__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>

	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

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
TSYS01 - DIGITAL TEMP SENSOR
*******************************************************************************/
	#define C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

		/** the I2C address on the bus */
		#define C_LOCALDEF__LCCM647__BUS_ADDX								(0xEEU)

		/** Testing Options */
		#define C_LOCALDEF__LCCM647__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>

	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RLOOP - POWER NODE CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U


		/** Testing Options */
		#define C_LOCALDEF__LCCM653__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM653__RLOOP__POWER_CORE/power_core.h>

	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

#endif /* LOCALDEF_H_ */
