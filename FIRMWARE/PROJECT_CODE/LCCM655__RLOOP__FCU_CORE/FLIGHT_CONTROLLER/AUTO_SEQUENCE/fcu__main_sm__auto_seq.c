/**
 * @file		FCU__MAIN_SM__AUTO_SEQ.C
 * @brief		Auto sequence functional tests.
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
 * @addtogroup FCU__MAIN_SM_AUTO
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the auto sequence system
 * 
 * @st_funcMD5		1551C289FFBD59697C35BA24059C46F1
 * @st_funcID		LCCM655R0.FILE.032.FUNC.001
 */
void vFCU_MAINSM_AUTO__Init(void)
{
	sFCU.eAutoSeqState = AUTOSEQ_STATE__RESET;

}


/***************************************************************************//**
 * @brief
 * Process the main state machine
 * 
 * @st_funcMD5		D7C64FED25A5476346946F581CF443BB
 * @st_funcID		LCCM655R0.FILE.032.FUNC.002
 */
void vFCU_MAINSM_AUTO__Process(void)
{
	Luint8 u8Counter;

	//hande the state machine.
	switch(sFCU.eAutoSeqState)
	{

		case AUTOSEQ_STATE__RESET:
			//we have just come out of reset here.

			//change state.
			sFCU.eAutoSeqState = AUTOSEQ_STATE__IDLE;
			break;

		case AUTOSEQ_STATE__IDLE:

			break;

		case AUTOSEQ_STATE__TEST_FUNCTION_X:

			/* Todo:
			 * Check function X
			 * If X = OK then move to next state, else abort state.
			 *
			 *
			 */

			break;


		default:
			//should not get here
			break;

	}//switch(sFCU.eRunState)
}


/***************************************************************************//**
 * @brief
 * Are we busy in the auto sequence
 * 
 * @return			0 = not busy, 1 = busy
 * @st_funcMD5		AC6581920B5F232BBDE88D0B8D60E7AB
 * @st_funcID		LCCM655R0.FILE.032.FUNC.003
 */
Luint8 u8FCU_MAINSM_AUTO__Is_Busy(void)
{
	Luint8 u8Return;

	if(sFCU.eAutoSeqState == AUTOSEQ_STATE__IDLE)
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
	}

	return u8Return;
}


/***************************************************************************//**
 * @brief
 * Do we need to do an immediate abort?
 * 
 * @return			1 = Immediate abort, 0 = no issue
 * @st_funcMD5		A4431A735C6F0C1AA502E235E9BEC53B
 * @st_funcID		LCCM655R0.FILE.032.FUNC.004
 */
Luint8 u8FCU_MAINSM_AUTO__Is_Abort(void)
{
	return 0;
}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

