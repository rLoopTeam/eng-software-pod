/**
 * @file		LGU__LOCALDEF.H
 * @brief		Localdef Template
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.002
 */

#if 0

/*******************************************************************************
RLOOP - LANDING GEAR UNIT
*******************************************************************************/
	#define C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		/** Clutch control*/
		#define C_LOCALDEF__LCCM667__ENABLE_CLUTCHES						(1U)

		/** Lift Mechanisms*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_LIFT						(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM667__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM667__RLOOP__LGU/lgu.h>
	#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

#endif //#if 0

