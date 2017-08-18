/**
 * @file		FCU__FCTL__MAIN_SM.C
 * @brief		Main state machine for the flight control unit
 * @author		Lachlan Grogan, Marek Gutt-Mostowy
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
 * @addtogroup FCU__FCTL__MAIN_SM
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		5224534176289DBD9FF1B39936308C7E
 * @st_funcID		LCCM655R0.FILE.020.FUNC.001
 */
void vFCU_FCTL_MAINSM__Init(void)
{
	//startup in the init phase
	sFCU.sStateMachine.eMissionPhase = POD_STATE__INIT;

}


/***************************************************************************//**
 * @brief
 * Process the main state machine
 * 
 * @st_funcMD5		2C23D1564E9845C3BED5E00B06C0BBB3
 * @st_funcID		LCCM655R0.FILE.020.FUNC.002
 */
void vFCU_FCTL_MAINSM__Process(void)
{

	//handle the SM guarding system

	//handle the state machine.
	switch(sFCU.sStateMachine.eMissionPhase)
	{

		case POD_STATE__NULL:
			//we must never be here
			break;

		case POD_STATE__INIT:
			break;

		case POD_STATE__IDLE:
			break;

		case POD_STATE__TEST_MODE:
			break;

		case POD_STATE__DRIVE:
			break;

		case POD_STATE__ARMED_WAIT:
			break;

		case POD_STATE__FLIGHT_PREP:
			break;

		case POD_STATE__READY:
			break;

		case POD_STATE__ACCEL:
			break;

		case POD_STATE__COAST_INTERLOCK:
			break;

		case POD_STATE__BRAKE:
			break;

		case POD_STATE__SPINDOWN:
			break;

		default:
			//
			break;


	}//switch(sFCU.eRunState)

}


void vFCU_FCTL_MAINSM__10MS_ISR(void)
{

}

void vFCU_FCTL_MAINSM__100MS_ISR(void)
{

}





#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

