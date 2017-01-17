/**
 * @file		LGU__COOLING.H
 * @brief		Cooling Control System
 * @author		Lachlan, Frank
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup LGU__COOLING
 * @ingroup LGU
 * @{ */
 
 
#include "../lgu.h"
#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM667__LGU_ENABLE_COOLING == 1U

void vLGU_COOLING__Init(void)
{
	
}

void vLGU_COOLING__Process(void)
{
	
}

#endif //C_LOCALDEF__LCCM667__LGU_ENABLE_COOLING
#ifndef C_LOCALDEF__LCCM667__LGU_ENABLE_COOLING
	#error
#endif
#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


