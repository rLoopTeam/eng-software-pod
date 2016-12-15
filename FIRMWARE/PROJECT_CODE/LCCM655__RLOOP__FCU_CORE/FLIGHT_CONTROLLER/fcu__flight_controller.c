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
 * @st_funcMD5		6A8640501290621A78E7305AA6289E1F
 * @st_funcID		LCCM655R0.FILE.035.FUNC.001
 */
void vFCU_FLIGHTCTL__Init(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		vFCU_FLIGHTCLT_LASERORIENT__Init();
	#endif

}


/***************************************************************************//**
 * @brief
 * Process the flight controller
 * 
 * @st_funcMD5		6047E1D02AACBBFF0B83B8AE27608ECD
 * @st_funcID		LCCM655R0.FILE.035.FUNC.002
 */
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

