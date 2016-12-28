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

Luint8 u8TestMsg[] = {0xD5, 0xD0, 0x00, 0x0D, 0xD5, 0xD3, 0x43, 0x00, 0x05, 0x40, 0x49, 0x0F, 0xD0, 0xD5, 0xD8, 0x9E, 0x00};


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
 * @st_funcMD5		A4CC59DE21CBBFA6ECDBCB7C1A9D331D
 * @st_funcID		LCCM653R0.FILE.003.FUNC.002
 */
void vPWRNODE_SM__Process(void)
{
	Luint8 u8Counter;

	switch(sPWRNODE.eMainState)
	{
		case RUN_STATE__RESET:
			//we have just reset
			sPWRNODE.eMainState = RUN_STATE__TEST;
			break;

		case RUN_STATE__IDLE:

			break;

		case RUN_STATE__TEST:

			//test a message into the Rx unit.
			for(u8Counter = 0U; u8Counter < 17U; u8Counter++)
			{
				vPICOMMS_RX__Receive_Bytes(&u8TestMsg[u8Counter], 1);
			}

			sPWRNODE.eMainState = RUN_STATE__IDLE;
			break;

	}//switch(sPWRNODE.eMainState)

}


#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

