/**
 * @file		FCU__FLIGHT_CONTROL__AERO_DRAG.C
 * @brief		Aerodynamic Drag System
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
 * @addtogroup FCU__FLIGHT_CTL__AERO_DRAG
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_AERO_DRAG == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init the aero drag system
 */
void vFCU_FLIGHTCTL_AERODRAG__Init(void)
{


}


/***************************************************************************//**
 * @brief
 * Process HE drag system
 */
void vFCU_FLIGHTCTL_AERODRAG__Process(void)
{

}



#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_AERO_DRAG
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_AERO_DRAG
	#error
#endif

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

