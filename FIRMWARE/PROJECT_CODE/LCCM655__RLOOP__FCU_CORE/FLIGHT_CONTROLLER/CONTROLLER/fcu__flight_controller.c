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

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		FED0062F6B73B20B0F3C694DC29503FB
 * @st_funcID		LCCM655R0.FILE.035.FUNC.001
 */
void vFCU_FCTL__Init(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		//setup laser orientation module
		vFCU_FLIGHTCLT_LASERORIENT__Init();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U
		//setup contrast sensor nav module
		vFCU_FLIGHTCTL_CONTRASTNAV__Init();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
		vFCU_FCTL_TRACKDB__Init();
	#endif

}


/***************************************************************************//**
 * @brief
 * Process the flight controller
 * 
 * @st_funcMD5		2111AE504D0BAC2BA86A479BB729D51D
 * @st_funcID		LCCM655R0.FILE.035.FUNC.002
 */
void vFCU_FCTL__Process(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		vFCU_FLIGHTCLT_LASERORIENT__Process();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U
		vFCU_FLIGHTCTL_CONTRASTNAV__Process();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
		vFCU_FCTL_TRACKDB__Process();
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

