//networking Rx

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U

extern struct _strPWRNODE sPWRNODE;

//rx a standard UDP packet
void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{

}


//rx a SafetyUDP
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

/*
			case NET_PKT__FCU_ACCEL__REQUEST_CAL_DATA:
				//Host wants us to transmit the calibration data for the accelerometers system
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__FCU_ACCEL__TX_CAL_DATA;
				break;
*/

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
