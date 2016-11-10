#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	//The PCB's main files
	#include <../../../BOARD_SUPPORT/lpcb235r0__board_support.h>



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
RLOOP - FLIGHT CONTROL UNIT - CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U


<<<<<<< Updated upstream
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER			(40U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO				(41U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN				(42U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO				(43U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN				(44U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC				(45U)

		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC				(46U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL				(47U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC				(48U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL				(49U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC				(50U)

=======

		/** ADC Sample Limits */
		#define C_LOCALDEF__LCCM655__ADC_SAMPLE__LOWER_BOUND					(300U)
		#define C_LOCALDEF__LCCM655__ADC_SAMPLE__UPPER_BOUND					(3000U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U


#endif /* LOCALDEF_H_ */
