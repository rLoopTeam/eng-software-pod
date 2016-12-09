/**
 * @file		FCU_CORE__NET__TX.C
 * @brief		Network Tx portion
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__CORE_NET_TX
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any network transmission stuff
 * 
 * @st_funcMD5		A045D43577055558C4337E5A72E5B4B6
 * @st_funcID		LCCM655R0.FILE.019.FUNC.001
 */
void vFCU_NET_TX__Init(void)
{
	//Clear the timer flag
	sFCU.sUDPDiag.u810MS_Flag = 0U;

	//set our default packet types
	sFCU.sUDPDiag.eTxPacketType = FCU_PKT__NONE;
	sFCU.sUDPDiag.eTxStreamingType = FCU_PKT__NONE;
}


/***************************************************************************//**
 * @brief
 * Process network transmission and do any transmission as required.
 * 
 * @st_funcMD5		195225AD0B954EDBA13250B3414B88AB
 * @st_funcID		LCCM655R0.FILE.019.FUNC.002
 */
void vFCU_NET_TX__Process(void)
{
	Luint8 u8Flag;
	E_FCU_NET_PACKET_TYPES eType;

	//see if we have a streaming flag set
	if(sFCU.sUDPDiag.eTxStreamingType != FCU_PKT__NONE)
	{
		//yes we do

		//do we have a timer flag?
		if(sFCU.sUDPDiag.u810MS_Flag == 1U)
		{
			//set it
			eType = sFCU.sUDPDiag.eTxStreamingType;

			//clear the flag now
			sFCU.sUDPDiag.u810MS_Flag = 0U;
		}
		else
		{
			//nope
			eType = FCU_PKT__NONE;
		}


	}
	else
	{
		//no streaming, but just harmlessly set the tx type incase it was
		//requested by the host
		eType = sFCU.sUDPDiag.eTxPacketType;
	}


	//detemrine the packet type
	switch(eType)
	{
		case FCU_PKT__ACCEL__TX_CAL_DATA:
			vFCU_ACCEL_ETH__Transmit(FCU_PKT__ACCEL__TX_CAL_DATA);
			sFCU.sUDPDiag.eTxPacketType = FCU_PKT__NONE;
			break;

		case FCU_PKT__ACCEL__TX_FULL_DATA:
			vFCU_ACCEL_ETH__Transmit(FCU_PKT__ACCEL__TX_FULL_DATA);
			sFCU.sUDPDiag.eTxPacketType = FCU_PKT__NONE;
			break;

		default:
			//do nothing
			break;

	}//switch(eType)
}


/***************************************************************************//**
 * @brief
 * To be called from the 10ms timer routine
 * Sets a flag to allow this module to determine that 10ms has elapsed
 * 
 * @st_funcMD5		3A00D72EA0E8E8896C26BBDFA0E4F006
 * @st_funcID		LCCM655R0.FILE.019.FUNC.003
 */
void vFCU_NET_TX__10MS_ISR(void)
{
	sFCU.sUDPDiag.u810MS_Flag = 1U;
}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */

