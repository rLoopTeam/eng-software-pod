/**
 * @file		POWER_CORE__NODE_PRESSURE.C
 * @brief		Node Baro Pressure Sensor interface layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.006
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__NODE_PRESSURE
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM652__ENABLE_NODE_PRESS == 1U

void vPWRNODE_NODEPRESS__Init(void)
{
	#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
	#endif
}

void vPWRNODE_NODEPRESS__Process(void)
{

}

#endif //C_LOCALDEF__LCCM652__ENABLE_NODE_PRESS
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

