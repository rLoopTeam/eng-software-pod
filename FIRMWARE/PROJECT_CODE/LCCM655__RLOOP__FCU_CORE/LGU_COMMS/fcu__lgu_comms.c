/**
 * @file		FCU__LGU_COMMS.C
 * @brief		Landing Gear communication interface
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
 * @addtogroup FCU__LGU
 * @ingroup FCU
 * @{ */


#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		A93FE719DA5923B4B04B785B755724C5
 * @st_funcID		LCCM655R0.FILE.080.FUNC.001
 */
void vFCU_LGU__Init(void)
{

	//int our variables
	sFCU.sLGU.eCommsState = LGU_COMMS_STATE__IDLE;

}


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		1893F9E9F9E79EEC289C564DE5CB757A
 * @st_funcID		LCCM655R0.FILE.080.FUNC.002
 */
void vFCU_LGU__Process(void)
{

	//handle the state machine
	switch(sFCU.sLGU.eCommsState)
	{
		case LGU_COMMS_STATE__IDLE:
			//do nothing
			break;
	}//switch(sFCU.sLGU.eCommsState)

}


//rx a byte from the network
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u8Value		## Desc ##
 * @st_funcMD5		E3739ED00B54EFF5AA8A0A4EC64ED32E
 * @st_funcID		LCCM655R0.FILE.080.FUNC.003
 */
void vFCU_LGU__Rx_Byte(Luint8 u8Value)
{

}

#endif //C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM
#ifndef C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM
	#error
#endif

/** @} */
/** @} */
/** @} */

