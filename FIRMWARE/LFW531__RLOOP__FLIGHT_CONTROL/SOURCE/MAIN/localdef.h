#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	//The PCB's main files
	#include <../../../BOARD_SUPPORT/lpcb235r0__board_support.h>


/*******************************************************************************
NUMERICAL MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM118__USE_ON_DSPIC   						(0U)

		/** set to 1 to include TRIG */
		#define C_LOCALDEF__LCCM118__ENABLE_TRIG							(1U)

		/** enable x^y */
		#define C_LOCALDEF__LCCM118__ENABLE_POWER							(0U)

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
