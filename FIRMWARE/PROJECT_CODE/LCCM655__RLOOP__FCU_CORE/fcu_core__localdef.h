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

#endif //#if 0

