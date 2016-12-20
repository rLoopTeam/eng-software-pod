/**
 * @file		FCU__FLIGHT_CONTROL__CONTRAST_NAV.C
 * @brief		Contrast sensor navigation
 * 				This module is the fusion of all contrast sensor nav theories
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
 * @addtogroup FCU__FLIGHT_CTL__CONSTAST_NAV
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U

//the structure
extern struct _strFCU sFCU;

//init contrast sensor navigation
void vFCU_FLIGHTCTL_CONTRASTNAV__Init(void)
{


}

//process nav tasks
void vFCU_FLIGHTCTL_CONTRASTNAV__Process(void)
{

}


//returns our current pod position in mm
Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_Position_mm(void)
{
	return 0;
}

//immediate return of a fault condition in the nav.
Luint8 u8FCU_FLIGHTCTL_CONTRASTNAV__Get_IsFault(void)
{
	return 0;
}

//return the list of fault flag conditions.
Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_FaultFlags(void)
{
	return 0;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV
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

