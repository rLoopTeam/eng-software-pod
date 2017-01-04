/**
 * @file		FCU__BRAKES__ETHERNET.C
 * @brief		Eth diagnostics for brakes system
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
 * @addtogroup FCU__BRAKES__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_BRAKES_ETH__Init(void)
{

}


void vFCU_BRAKES_ETH__Process(void)
{


}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET

#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

