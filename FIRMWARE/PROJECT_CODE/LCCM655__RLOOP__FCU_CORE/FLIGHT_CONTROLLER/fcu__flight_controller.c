/**
 * @file		FCU__FLIGHT_CONTROLLER.C
 * @brief		The actual flight control algo's
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
 * @addtogroup FCU__FLIGHT_CTL
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 *
 */
void vFCU_FLIGHTCTL__Init(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		vFCU_FLIGHTCLT_LASERORIENT__Init();
	#endif

}


void vFCU_FLIGHTCTL__Process(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		vFCU_FLIGHTCLT_LASERORIENT__Process();
	#endif

}


#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
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

