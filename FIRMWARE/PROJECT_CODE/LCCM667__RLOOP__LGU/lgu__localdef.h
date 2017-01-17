#if 0

/*******************************************************************************
RLOOP - LANDING GEAR UNIT
*******************************************************************************/
	#define C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		/** Clutch control*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_CLUTCHES					(0U)

		/** Motor Cooling*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_COOLING						(0U)

		/** Gimbal Subsystem*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_GIMBALS						(0U)

		/** Lift Mechanisms*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_LIFT						(0U)

		/** PV Pressure Control System*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_PVPRESS						(0U)

		/** FCU Serial Link*/
		#define C_LOCALDEF__LCCM667__LGU_SERIAL								(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM667__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM667__RLOOP__LGU/lgu.h>
	#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

#endif //#if 0

