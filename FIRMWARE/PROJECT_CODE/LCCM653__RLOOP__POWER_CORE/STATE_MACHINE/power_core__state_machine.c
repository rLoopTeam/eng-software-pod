/**
 * @file		POWER_CORE__STATE_MACHINE.C
 * @brief		Main state machine layer for the Power Node
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.003
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__STATE_MACHINE
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

extern struct _strPWRNODE sPWRNODE;


/***************************************************************************//**
 * @brief
 * Init any of the main application state machine items
 * 
 * @st_funcMD5		A40323662C84BEFCABD28662D11DA6D2
 * @st_funcID		LCCM653R0.FILE.003.FUNC.001
 */
void vPWRNODE_SM__Init(void)
{

	//init
	sPWRNODE.eMainState = RUN_STATE__RESET;

}

/***************************************************************************//**
 * @brief
 * Process
 * 
 * @st_funcMD5		CBFBEEF04FB99B08A430376E00D99348
 * @st_funcID		LCCM653R0.FILE.003.FUNC.002
 */
void vPWRNODE_SM__Process(void)
{
	Luint8 u8Test;

	switch(sPWRNODE.eMainState)
	{
		case RUN_STATE__RESET:
			//we have just reset
			sPWRNODE.eMainState = RUN_STATE__IDLE;
			break;

		case RUN_STATE__IDLE:
			//We sit in idle state waiting to transition to charge state */
			break;


		case RUN_STATE__CHARGE_START:

			//start the charger
			vPWRNODE_CHG__Start();

			sPWRNODE.eMainState = RUN_STATE__CHARGE_PROCESS;
			break;

		case RUN_STATE__CHARGE_PROCESS:
			u8Test = u8PWRNODE_CHG__Is_Busy();
			if(u8Test == 1U)
			{
				//stay in state
			}
			else
			{
				//move back to idle
				sPWRNODE.eMainState = RUN_STATE__IDLE;
			}
			break;

		case RUN_STATE__CHARGE_STOP:
			//abort the charging
			vPWRNODE_CHG__Abort();

			//go back to idle.
			sPWRNODE.eMainState = RUN_STATE__IDLE;
			break;

		case RUN_STATE__TEST:

			break;

	}//switch(sPWRNODE.eMainState)

}


//call this to configure charging state.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		A4102DAE2BA37B460B55A31632AE4AC5
 * @st_funcID		LCCM653R0.FILE.003.FUNC.003
 */
void vPWRNODE_SM__Enable_ChargingState(void)
{

	sPWRNODE.eMainState = RUN_STATE__CHARGE_START;

}

//stop charging immediate
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		CD45124CCD72755256E22880758DBE25
 * @st_funcID		LCCM653R0.FILE.003.FUNC.004
 */
void vPWRNODE_SM__Stop_ChargingState(void)
{
	sPWRNODE.eMainState = RUN_STATE__CHARGE_STOP;
}


#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

