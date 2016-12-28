/**
 * @file		POWER_CORE__NET__TX.C
 * @brief		Network Tx portion of the power core
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
 * @addtogroup POWER_NODE__NETWORK__TX
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init any network transmission stuff
 * 
 */
void vPWRNODE_NET_TX__Init(void)
{
	//Clear the timer flag
	sPWRNODE.sUDPDiag.u810MS_Flag = 0U;

	//set our default packet types
	sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
	sPWRNODE.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
}


/***************************************************************************//**
 * @brief
 * Process network transmission and do any transmission as required.
 * 
 */
void vPWRNODE_NET_TX__Process(void)
{
	Luint8 u8Flag;
	E_NET__PACKET_T eType;

	//see if we have a streaming flag set
	if(sPWRNODE.sUDPDiag.eTxStreamingType != NET_PKT__NONE)
	{
		//yes we do

		//do we have a timer flag?
		if(sPWRNODE.sUDPDiag.u810MS_Flag == 1U)
		{
			//set it
			eType = sPWRNODE.sUDPDiag.eTxStreamingType;

			//clear the flag now
			sPWRNODE.sUDPDiag.u810MS_Flag = 0U;
		}
		else
		{
			//nope
			eType = NET_PKT__NONE;
		}


	}
	else
	{
		//no streaming, but just harmlessly set the tx type incase it was
		//requested by the host
		eType = sPWRNODE.sUDPDiag.eTxPacketType;
	}

/*
	//detemrine the packet type
	switch(eType)
	{
		case NET_PKT__FCU_ACCEL__TX_CAL_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL_ETH__Transmit(eType);
			#endif

				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__FCU_ACCEL__TX_FULL_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL_ETH__Transmit(eType);
			#endif
			sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		default:
			//do nothing
			break;

	}//switch(eType)
*/

}


/***************************************************************************//**
 * @brief
 * To be called from the 10ms timer routine
 * Sets a flag to allow this module to determine that 10ms has elapsed
 * 
 */
void vPWRNODE_NET_TX__10MS_ISR(void)
{
	sPWRNODE.sUDPDiag.u810MS_Flag = 1U;
}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE

/** @} */
/** @} */
/** @} */

