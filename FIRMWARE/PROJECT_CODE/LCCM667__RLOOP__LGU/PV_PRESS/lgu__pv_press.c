/**
 * @file		LGU__PV_PRESS.H
 * @brief		Pressure Vessel re-press system
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
 * @addtogroup LGU__PV_PRESS
 * @ingroup LGU
 * @{ */
 
#include "../lgu.h"

#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM667__LGU_ENABLE_PVPRESS == 1U

void vLGU_PVPRESS__Init(void)
{
	
}

void vLGU_PVPRESS__Process(void)
{
	
}

#endif //C_LOCALDEF__LCCM667__LGU_ENABLE_PVPRESS
#ifndef C_LOCALDEF__LCCM667__LGU_ENABLE_PVPRESS
	#errir
#endif 
#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

