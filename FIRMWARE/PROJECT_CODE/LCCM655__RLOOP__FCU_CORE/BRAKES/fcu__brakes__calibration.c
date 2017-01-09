/**
 * @file		FCU__BRAKES__CALIBRATION.C
 * @brief		Brake Calibration Routines
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
 * @addtogroup FCU__BRAKES__CAL
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

//the structure
extern struct _strFCU sFCU;

void vFCU_BRAKES_CAL__Init(void)
{

	//set initial states
	sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__IDLE;
}


void vFCU_BRAKES_CAL__Process(void)
{

	switch(sFCU.sBrakesGlobal.sCalibration.eState)
	{

		case BRAKE_CAL_STATE__IDLE:
			break;

		default:
			//?
			break;

	}//switch(sFCU.sBrakesGlobal.sCalibration.eState)

}


#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

