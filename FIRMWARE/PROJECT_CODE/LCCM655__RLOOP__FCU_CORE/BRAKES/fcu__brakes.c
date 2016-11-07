/**
 * @file		FCU__BRAKES.C
 * @brief		Brake control subsystem for the FCU
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
 * @addtogroup FCU__BRAKES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

/***************************************************************************//**
 * @brief
 * Init any brakes variables, etc.
 * 
 *
 */
void vFCU_BRAKES__Init(void)
{

}


/***************************************************************************//**
 * @brief
 * Process any brakes tasks.
 * 
 */
void vFCU_BRAKES__Process(void)
{

}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

