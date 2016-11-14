/**
 * @file		FCU_CORE__LOCALDEF.H
 * @brief		Local definitions template for the FCU
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.002
 */


#if 0

/*******************************************************************************
RLOOP - FLIGHT CONTROL UNIT - CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

		/** Enable or disable the PiComms layer */
		#define C_LOCALDEF__LCCM655__ENABLE_PI_COMMS						(1U)

		/** Enable the OptoNCDT laser interface */
		#define C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT					(1U)

		/** Number of OptoNCDT lasers, must be in order from A0:2, B0:2*/
		#define C_LOCALDEF__LCCM655__NUM_LASER_OPTONCDT						(1U)


		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER				(20U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO				(21U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN				(22U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO				(23U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN				(24U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC				(25U)

		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC				(26U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL				(27U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC				(28U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL				(29U)
		#define C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC					(30U)

		/** ADC Sample Limits */
		#define C_LOCALDEF__LCCM655__ADC_SAMPLE__LOWER_BOUND					(300U)
		#define C_LOCALDEF__LCCM655__ADC_SAMPLE__UPPER_BOUND					(3000U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

#endif //#if 0

