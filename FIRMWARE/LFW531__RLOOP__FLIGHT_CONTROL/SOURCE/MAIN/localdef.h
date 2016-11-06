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


		/** Testing Options */
		#define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U


#endif /* LOCALDEF_H_ */
