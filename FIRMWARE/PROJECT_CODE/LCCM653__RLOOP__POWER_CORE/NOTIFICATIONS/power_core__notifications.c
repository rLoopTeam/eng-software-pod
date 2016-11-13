/**
 * @file		POWER_CORE__NOTIFICATIONS.C
 * @brief		RM4 system level notifications
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
 * @addtogroup POWER_NODE__NOTIFICATIONS
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

void vRM4_SCI_INT__Notification(RM4_SCI__CHANNEL_T eChannel, Luint32 u32Flags)
{
	Luint8 u8Array[1];
	switch(eChannel)
	{
		case SCI_CHANNEL__2:

			//pass off to PI
			u8Array[0] = u8RM4_SCI__Get_Rx_Value(SCI_CHANNEL__2);
#if C_LOCALDEF__LCCM656__ENABLE_RX == 1U
			PICOMMS_RX_receiveBytes(&u8Array[0], 1);
#endif
			break;

	}//switch(eChannel)
}


#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

