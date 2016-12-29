//networking Rx

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

extern struct _strPWRNODE sPWRNODE;

//rx a standard UDP packet
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u16DestPort		## Desc ##
 * @param[in]		u16Length		## Desc ##
 * @param[in]		*pu8Buffer		## Desc ##
 * @st_funcMD5		54B96758BB5EA2CBA78EBC1004396A94
 * @st_funcID		LCCM653R0.FILE.018.FUNC.001
 */
void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{

}


//rx a SafetyUDP
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u16Fault		## Desc ##
 * @param[in]		u16DestPort		## Desc ##
 * @param[in]		ePacketType		## Desc ##
 * @param[in]		u16PayloadLength		## Desc ##
 * @param[in]		*pu8Payload		## Desc ##
 * @st_funcMD5		DBCD15F1783E9EDE9922A451109D7218
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
