/**
 * @file		LGU__CLUTCHES.H
 * @brief		Clutch Control Layer
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
 * @addtogroup LGU__CLUTCHES
 * @ingroup LGU
 * @{ */
 
#include "../lgu.h"

#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM667__LGU_ENABLE_CLUTCHES == 1U

void vLGU_CLUTCH__Init(void)
{
	
}

void vLGU_CLUTCH__Process(void)
{
	
}

#endif //C_LOCALDEF__LCCM667__LGU_ENABLE_CLUTCHES
#ifndef C_LOCALDEF__LCCM667__LGU_ENABLE_CLUTCHES
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


