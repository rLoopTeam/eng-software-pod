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
 * @st_funcMD5		F22223ECE290EE71D79DD969F6F9BFD0
 * @st_funcID		LCCM653R0.FILE.019.FUNC.001
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
 * @st_funcMD5		C8F5AD7CFC44AD1FF97722827F69FE08
 * @st_funcID		LCCM653R0.FILE.019.FUNC.002
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

	//detemrine the packet type
	switch(eType)
	{
		case NET_PKT__PWR_TEMP__TX_CURRENT_TEMPS:
			#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
				vPWRNODE_BAATTEMP_ETH__Transmit(eType);
			#endif

			sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__PWR_TEMP__TX_SENSOR_LOCATION_DATA:
			#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
				vPWRNODE_BAATTEMP_ETH__Transmit(eType);
			#endif

			sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__PWR_TEMP__TX_ROMID_INDEX:
			#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
				vPWRNODE_BAATTEMP_ETH__Transmit_ROMID(sPWRNODE.sUDPDiag.u32Block0);
			#endif

			sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__PWR_BMS__TX_BMS_STATUS:
			#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
				vPWR_BMS_ETH__Transmit(eType);
			#endif
			sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__PWR_COOLING__TX_COOLING_STATUS:
			#if C_LOCALDEF__LCCM653__ENABLE_COOLING == 1U
				vPWR_COOLING_ETH__Transmit(eType);
			#endif
			sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__NONE;
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
 * @st_funcMD5		F52227B3D966EC01608AE852390D8324
 * @st_funcID		LCCM653R0.FILE.019.FUNC.003
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

