/**
 * @file		POWER__CHARGER__ALGORITHM.C
 * @brief		Implements the battery charger algo.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__CHARGER
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

extern struct _strPWRNODE sPWRNODE;



void vPWRNODE_CHG__Init(void)
{

	//set to idle.
	sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__IDLE;

	//setup the charger relay
	vPWRNODE_CHG_RELAY__Init();

	//setup the current and voltage measurement
	vPWRNODE_CHG_IV__Init();

}


void vPWRNODE_CHG__Process(void)
{

	//process charger relay control
	vPWRNODE_CHG_RELAY__Process();

	//process charger current and voltage measurement
	vPWRNODE_CHG_IV__Process();

	//handle the charger state machine.
	switch(sPWRNODE.sCharger.sAlgo.eState)
	{
		case CHG_STATE__IDLE:
			//we are in idle state, do nothing until we want to start charging.
			break;

		case CHG_STATE__START:
			//need to ensure the charger is switched off.
			//todo: disable charger
			break;

		case CHG_STATE__CHECK_BALANCE:

			//check the balance of the cells and discharge until either thermal limit
			//of the resistors or cells are discharged within spec.
			break;

		case CHG_STATE__CLOSE_CONTACTOR_RELAY:
			//switch the realy on.
			vPWRNODE_CHG_RELAY__On();
			break;

		//switch on the charger




	}//switch(sPWRNODE.sCharger.sAlgo.eState)

}


//start charging
void vPWRNODE_CHG__Start(void)
{
	//move to start state
	sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__START;

}


#endif //C_LOCALDEF__LCCM653__ENABLE_CHARGER
#ifndef C_LOCALDEF__LCCM653__ENABLE_CHARGER
	#error
#endif
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

