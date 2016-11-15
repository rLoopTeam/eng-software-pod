/**
 * @file		FCU__THROTTLES.C
 * @brief		Throttle Controller
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__THROTTLES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_THROTTLE__Init(void)
{


}


/***************************************************************************//**
 * @brief
 * Process any Throttle tasks
 * 
 */
void vFCU_THROTTLE__Process(void)
{


}

#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLE
#ifndef C_LOCALDEF__LCCM655__ENABLE_THROTTLE
	#error
#endif
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

