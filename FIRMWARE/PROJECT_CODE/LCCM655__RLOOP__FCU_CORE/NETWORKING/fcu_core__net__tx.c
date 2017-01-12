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
 * @st_funcMD5		ABD3145988312367E93F1F22D96F7A42
 * @st_funcID		LCCM655R0.FILE.019.FUNC.001
 */
void vFCU_NET_TX__Init(void)
{
	//Clear the timer flag
	sFCU.sUDPDiag.u810MS_Flag = 0U;

	//set our default packet types
	sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
	sFCU.sUDPDiag.eTxStreamingType = NET_PKT__NONE;

	#if C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY == 1U
		vFCU_NET_SPACEX_TX__Init();
	#endif
}


/***************************************************************************//**
 * @brief
 * Process network transmission and do any transmission as required.
 * 
 * @st_funcMD5		CC51B5F1A0B55EC4C0976DE4FB083F76
 * @st_funcID		LCCM655R0.FILE.019.FUNC.002
 */
void vFCU_NET_TX__Process(void)
{
	Luint8 u8Flag;
	E_NET__PACKET_T eType;

	//Do we need a timed spaceX packet
	#if C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY == 1U
		vFCU_NET_SPACEX_TX__Process();
	#endif

	//see if we have a streaming flag set
	if(sFCU.sUDPDiag.eTxStreamingType != NET_PKT__NONE)
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
			eType = NET_PKT__NONE;
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
		case NET_PKT__FCU_GEN__TX_MISSION_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
				#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
					vFCU_FCTL_ETH__Transmit(eType);
				#endif
			#endif
			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__FCU_ACCEL__TX_CAL_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL_ETH__Transmit(eType);
			#endif

			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__FCU_ACCEL__TX_FULL_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL_ETH__Transmit(eType);
			#endif
			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__LASER_OPTO__TX_LASER_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
				vFCU_LASEROPTO_ETH__Transmit(eType);
			#endif
			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__LASER_DIST__TX_LASER_DATA:
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
				vFCU_LASERDIST_ETH__Transmit(eType);
			#endif
			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__LASER_CONT__TX_LASER_DATA_0:
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
				vFCU_LASERCONT_ETH__Transmit(eType);
			#endif
			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__FCU_NAV__TX_NAV_PROGRESS:

			sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
			break;

		case NET_PKT__FCU_BRAKES__TX_DATA:
		case NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM:
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vFCU_BRAKES_ETH__Transmit(eType);
			#endif
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
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

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		EAD22CC59DC6AF2FAD5C3B84720BB133
 * @st_funcID		LCCM655R0.FILE.019.FUNC.004
 */
void vFCU_NET_TX__100MS_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY == 1U
		vFCU_NET_SPACEX_TX__100MS_ISR();
	#endif
}

//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY
	#error
#endif

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */

