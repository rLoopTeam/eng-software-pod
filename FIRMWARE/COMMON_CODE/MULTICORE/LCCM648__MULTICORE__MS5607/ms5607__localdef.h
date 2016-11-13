#if 0

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

#endif //#if 0

