

#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	/*lint -e950*/

	//Run on RM48 CNCD
	#include <../../../../../BOARD_SUPPORT/lpcb234r0__board_support.h>

    //switch off unwanted systems
    #undef C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE
    #define C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE 0

    #undef C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE
    #define C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE 0

    #undef C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE
    #define C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE 0

    #undef C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE
    #define C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE 0

    #undef C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE
    #define C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE 0

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
		#define M_LOCALDEF__LCCM641__I2C_TX_REG(device, reg)				s16RM4_I2C_USER__TxReg(device, reg)
		#define M_LOCALDEF__LCCM641__I2C_RX_REG(device, reg)				s16RM4_I2C_USER__RxReg(device, reg)
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
        #define C_LOCALDEF__LCCM644__USE_ON_MSP430                          (0U)

        /** Specific the required resoltuion 9, 10, 11 or 12 bit
         * Each resolution takes longer to convert
         */
        #define C_LOCALDEF__LCCM644__RESOLUTION_SETTING                     (9U)

        /** If we have access to a 10ms ISR then we don't need to wait
         * for the conversion to finish. If we don't have an ISR then
         * set this to 0
         */
        #define C_LOCALDEF__LCCM644__USE_10MS_ISR                           (0U)

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
		#define C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS						(C_LOCALDEF__LCCM641__NUM_DEVICS)

		/** Testing Options */
		#define C_LOCALDEF__LCCM644__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM644__MULTICORE__DS18B20/ds18b20.h>

	#endif //#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U



	/*lint +e950*/
	


#endif /* LOCALDEF_H_ */
