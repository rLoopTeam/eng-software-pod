/**
 * @file		FCU__FLIGHT_CONTROL__GIMBAL_CONTROL.C
 * @brief		Gimbal Control Subsystem
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
 * @addtogroup FCU__FLIGHT_CTL__GIMBAL_CONTROL
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_GIMBAL_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_FLIGHTCTL_GIMBAL__Init(void)
{


}



void vFCU_FLIGHTCTL_GIMBAL__Process(void)
{

}



#endif //C_LOCALDEF__LCCM655__ENABLE_GIMBAL_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_GIMBAL_CONTROL
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

