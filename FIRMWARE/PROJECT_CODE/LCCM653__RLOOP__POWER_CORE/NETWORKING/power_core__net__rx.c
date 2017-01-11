/**
 * @file		POWER_CORE__NET__RX.C
 * @brief		Network Rx portion of the power core
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
 * @addtogroup POWER_NODE__NETWORK__RX
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Rx a standard UDP packet
 * 
 * @param[in]		u16DestPort			The desination UDP port
 * @param[in]		u16Length			The UDP Length
 * @param[in]		*pu8Buffer			Pointer to the UDP packet data
 * @st_funcMD5		54B96758BB5EA2CBA78EBC1004396A94
 * @st_funcID		LCCM653R0.FILE.018.FUNC.001
 */
void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSAFE_UDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}



/***************************************************************************//**
 * @brief
 * Rx a SafetyUDP
 * 
 * @param[in]		u16Fault				Fault details (if any)
 * @param[in]		u16DestPort				The destination port in the UDP packet
 * @param[in]		ePacketType				SafeUDP Packet Type
 * @param[in]		u16PayloadLength		SafeUDP Payload Length
 * @param[in]		*pu8Payload				Pointer to SafeUDP Payload
 * @st_funcMD5		6B62E5DDB6D7BDC7180F3EED6DA76908
 * @st_funcID		LCCM653R0.FILE.018.FUNC.002
 */
void vPWRNODE_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

	Luint32 u32Block[4];

	//make sure we are rx'ing on our port number
	if(u16DestPort == C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER)
	{

		//blocks are good for putting into functions
		//this is inhernet in the safetyUDP layer
		u32Block[0] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet that came in
		switch((E_NET__PACKET_T)ePacketType)
		{


			case NET_PKT__PWR_GEN__POD_SAFE_COMMAND:
				if(u32Block[0] == 0x75643210U)
				{
					//Safe the pod

				}
				else
				{
					//maybe should log this error.
				}
				break;

			case NET_PKT__PWR_GEN__POD_EMULATION_CONTROL:

				break;

			case NET_PKT__PWR_GEN__STREAMING_CONTROL:
				//if the host wants to stream data packets.
				if(u32Block[0] == 1U)
				{
					//streaming on
					sPWRNODE.sUDPDiag.eTxStreamingType = (E_NET__PACKET_T)u32Block[1];
				}
				else
				{
					//streaming off
					sPWRNODE.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
				}

				break;

			case NET_PKT__PWR_TEMP__REQ_CURRENT_TEMPS:
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_TEMP__TX_CURRENT_TEMPS;
				break;

			case NET_PKT__PWR_TEMP__REQ_SENSOR_LOCATION:
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_TEMP__TX_SENSOR_LOCATION_DATA;
				break;

			case NET_PKT__PWR_TEMP__REQ_ROMID_INDEX:
				sPWRNODE.sUDPDiag.u32Block0 = u32Block[0];
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_TEMP__TX_ROMID_INDEX;
				break;

			case NET_PKT__PWR_TEMP__SET_ROMID_INDEX:
				#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
					vPWRNODE_BATTEMP_MEM__Set_ROMID(u32Block[0], u32Block[1], u32Block[2]);
				#endif
				break;

			case NET_PKT__PWR_TEMP__SET_USERDATA_INDEX:
				#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
					vPWRNODE_BATTEMP_MEM__Set_UserData(u32Block[0], u32Block[1], u32Block[2], u32Block[3]);
				#endif
				break;

			default:
				//do nothing
				break;

		}//switch((E_FCU_NET_PACKET_TYPES)ePacketType)
	}
	else
	{
		//not for us
	}

}


#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */

