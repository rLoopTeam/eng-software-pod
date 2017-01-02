/**
 * @file		FCU__FLIGHT_CONTROL__HE_DRAG.C
 * @brief		Hover Engine drag tables
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
 * @addtogroup FCU__FLIGHT_CTL__HE_DRAG
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_HE_DRAG == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init the HE drag system
 */
void vFCU_FLIGHTCTL_HEDRAG__Init(void)
{


}


/***************************************************************************//**
 * @brief
 * Process HE drag system
 */
void vFCU_FLIGHTCTL_HEDRAG__Process(void)
{

}

//gets the drag from the HE in Newtons
Luint32 u32FCU_FLIGHTCTL_HEDRAG__Get_Drag(Luint32 u32Veloc_mms, Luint32 u32RPM, Luint32 u32Height)
{
	return 0;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_HE_DRAG
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_HE_DRAG
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

