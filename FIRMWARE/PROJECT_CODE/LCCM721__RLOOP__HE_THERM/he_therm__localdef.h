/**
 * @file		HE_THERM__LOCALDEF.H
 * @brief		Localdef Template
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.002
 */

#if 0

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

#endif //#if 0

